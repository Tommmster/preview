/* 	$NetBSD$	 */

/*-
 * Copyright (c) 2013 The NetBSD Foundation, Inc.
 * All rights reserved.
 * 
 * This code is derived from software contributed to The NetBSD Foundation
 * by 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <avr32/asm.h>
#include <avr32/cpuregs.h>

#include "assym.h"

/*
 * void MachTLBUpdate(u_int tlbehi, u_int ptentry)
 */
	.text
	.align 1
	.globl MachTLBUpdate
	.type MachTLBUpdate,@function

MachTLBUpdate:
	stm --sp, lr

	/* Remove the SW-based bit. */
	andh	r11, hi(~(AVR32_PTE_WIRED | AVR32_PTE_VALID))
     
	mtsr	SR_TLBEHI, r12
	mtsr	SR_TLBELO, r11

	tlbw

	ldm sp++, pc	
	.size MachTLBUpdate, . - MachTLBUpdate

/*
 * void avr32_compare_write(u_int32_t n);
 * 	Set the value of the COMPARE register.
 */
	.text
	.align 1
	.globl avr32_compare_write
	.type avr32_compare_write,@function

avr32_compare_write:
	stm --sp, lr
	mtsr SR_COMPARE, r12
	ldm sp++, pc
	.size avr32_compare_write, . - avr32_compare_write

/*
 * void avr32_count_write(u_int32_t n);
 * 	Set the value of the COUNT register.
 */
	.text
	.align 1
	.globl avr32_count_write
	.type avr32_count_write, @function

avr32_count_write:
	stm	--sp, lr
	mtsr	SR_COUNT, r12
	ldm	sp++, pc
	.size avr32_count_write, . - avr32_count_write

/*
 * u_int32_t avr32_count_read(void)
 * 	Return the value of the COUNT register.
 */
	.text
	.align 1
	.globl avr32_count_read
	.type avr32_count_read, @function

avr32_count_read:
	mfsr	r12, SR_COUNT
	mov	pc, lr
	.size avr32_count_read, . - avr32_count_read

/*
 * void cpu_switch_resume(struct lwp *newlwp)
 *
 * Wiredown the USPACE of newlwp in tlb entry #0
 */
	.align 1
	.text
	.globl cpu_switch_resume

cpu_switch_resume:

	stm	--sp, lr
	#XXXAVR32 Should invalidate relevant entries only.
	mfsr	r0, SR_MMUCR	
	sbr	r0, 0x2
	
	ld.w	r0, r12[L_MD]
	ld.w	r1, r0[MD_UPTE_0]

	ld.w	r0, r12[L_ADDR]
	
	#XXXAVR32 Watch out for those bits (wired, global)
	mtsr	SR_TLBELO, r1	
	mtsr	SR_TLBEHI, r0
	
	ldm	sp++, pc
	.size cpu_switch_resume, . - cpu_switch_resume

#if notyet
/*
 * Invalidate TLB entries belong to per process user spaces while
 * leaving entries for kernel entries for kernel space marked global intact.
 */
	.globl avr32_tbiap
	.type avr32_tbiap,@function
	.text
	.align 1
avr32_tbiap:
	
1:	cp.w r12, 32
	brge 2f

	#TODO Update DRP
	tlbr

	mfsr r8, SR_TLBEHI
	mfsr r7, SR_TLBELO

	andl r7, lo(AVR32_PG_GLOBAL)
	breq 3 #global entry

	/* Entry is not marked as global, invalidate. */
	andl r8, lo(~AVR32_PG_VALID)
	
	mtsr SR_TLBEHI, r8
	mtsr SR_TLBELO, r7

	tlbw
	
3:
2:	nop
	.end avr32_tbiap
#endif
