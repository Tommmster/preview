/*	$NetBSD$	*/
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

#include <sys/cdefs.h>
#include <sys/systm.h>

#include <avr32/cpuregs.h>
#include <avr32/locore.h>

void 
show_dtlb_entry(unsigned int index)
{
	unsigned int tlbehi, tlbehi_save, tlbelo, mmucr, mmucr_save;
	unsigned long flags;

	mmucr_save = AVR32_MFSR(SR_MMUCR);
	tlbehi_save = AVR32_MFSR(SR_TLBEHI);
	mmucr &= ~AVR32_MMUCR_DRP_MASK;
	mmucr |= AVR32_MMUCR_DRP(index);
	AVR32_MTSR(SR_MMUCR, mmucr);

	asm volatile("tlbr" : : : "memory");

	tlbehi = AVR32_MFSR(SR_TLBEHI);
	tlbelo = AVR32_MFSR(SR_TLBELO);

	printf("%2u: %c %c %02x   %05x %05x %o  %o  %c %c %c %c\n",
	       index,
	       (tlbehi & 0x200)?'1':'0',
	       (tlbelo & 0x100)?'1':'0',
	       (tlbehi & 0xff),
	       (tlbehi >> 12), (tlbelo >> 12),
	       (tlbelo >> 4) & 7, (tlbelo >> 2) & 3,
	       (tlbelo & 0x200)?'1':'0',
	       (tlbelo & 0x080)?'1':'0',
	       (tlbelo & 0x001)?'1':'0',
	       (tlbelo & 0x002)?'1':'0');

	AVR32_MTSR(SR_MMUCR, mmucr_save);
	AVR32_MTSR(SR_TLBEHI, tlbehi_save);
}

void 
dump_dtlb_6620(void)
{
	unsigned int i=0;
		
	printf("ID  V G ASID VPN   PFN   AP SZ C B W D\n");
	for (; i < 32; i++)
		show_dtlb_entry(i);
}
