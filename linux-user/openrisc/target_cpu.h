/*
 * OpenRISC specific CPU ABI and functions for linux-user
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

#ifndef TARGET_CPU_H
#define TARGET_CPU_H

#define OR1K_ATOMIC_SWAP        1
#define OR1K_ATOMIC_CMPXCHG     2
#define OR1K_ATOMIC_XCHG        3
#define OR1K_ATOMIC_ADD         4
#define OR1K_ATOMIC_DECPOS      5
#define OR1K_ATOMIC_AND         6
#define OR1K_ATOMIC_OR          7
#define OR1K_ATOMIC_UMAX        8
#define OR1K_ATOMIC_UMIN        9

static inline void cpu_clone_regs(CPUOpenRISCState *env, target_ulong newsp)
{
    if (newsp) {
        env->gpr[1] = newsp;
    }
    env->gpr[11] = 0;
}

static inline void cpu_set_tls(CPUOpenRISCState *env, target_ulong newtls)
{
    env->gpr[10] = newtls;
}

#endif
