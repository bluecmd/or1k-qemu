/*
 * OpenRISC interrupt.
 *
 * Copyright (c) 2011-2012 Jia Liu <proljc@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "cpu.h"
#include "qemu-common.h"
#include "exec/gdbstub.h"
#include "qemu/host-utils.h"
#ifndef CONFIG_USER_ONLY
#include "hw/loader.h"
#endif

void openrisc_cpu_do_interrupt(CPUState *cs)
{
    OpenRISCCPU *cpu = OPENRISC_CPU(cs);
    CPUOpenRISCState *env = &cpu->env;
#ifndef CONFIG_USER_ONLY

    env->epcr = env->pc;
    if (env->flags & D_FLAG) {
        env->flags &= ~D_FLAG;
        env->sr |= SR_DSX;
        env->epcr -= 4;
    }
    if (env->exception_index == EXCP_SYSCALL) {
        env->epcr += 4;
    }

    env->esr = ENV_GET_SR(env);
    env->sr &= ~SR_DME;
    env->sr &= ~SR_IME;
    env->sr |= SR_SM;
    env->sr &= ~SR_IEE;
    env->sr &= ~SR_TEE;
    env->tlb->cpu_openrisc_map_address_data = &cpu_openrisc_get_phys_nommu;
    env->tlb->cpu_openrisc_map_address_code = &cpu_openrisc_get_phys_nommu;

    if (env->exception_index > 0 && env->exception_index < EXCP_NR) {
        env->pc = (env->exception_index << 8);
    } else {
        cpu_abort(env, "Unhandled exception 0x%x\n", env->exception_index);
    }
#endif

    env->exception_index = -1;
}
