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

#ifndef _TRAP_H_
#define _TRAP_H_

/* XXXAVR32 Put absolute values */

#define T_BUS_ERR_LD_ST	(0x08 >> 2)		/* Bus error data fetch */
#define T_BUS_ERR_IFETCH	(0x0C >> 2)		/* Bus error instruction fetch */
#define T_BREAK	(0X1C >> 2)	/* Breakpoint */
#define T_FPE	(0x2C >> 2)	/* Floating-point */
#define T_COP_UNUSABLE (0x30 >> 2)		/* Coprocessor absent */
#define T_ADDR_ERR_LD	(0x34 >> 2)
#define T_ADDR_ERR_ST	(0x38 >> 2)

#define T_TLB_MOD	(0x44 >> 2)		/* TLB Modified */
#define T_TLB_LD_MISS	(0x60 >> 2)		/* TLB Miss on load or ifetch */
#define T_TLB_ST_MISS	(0x70 >> 2)		/* TLB Miss on store */


#endif /* _TRAP_H_ */

