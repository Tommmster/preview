#ifndef __INTC_H__
#define __INTC_H__

#define INTC_BASE_ADDRESS 0XFFF00400

/*
 * Pointer to the 1K area where the interrupt controller
 * is located.
 */
#define INTC_BASE_POINTER (void*)INTC_BASE_ADDRESS

#define IPR_INTLEVEL(ipr) ((ipr >> 30) & 0x3)

/*
 * Handler offset used to give the address of 
 * the interrupt handler.
 * The lsb is 0 to give halfword alignment.
 */ 
#define IPR_AUTOVECTOR(ipr) (ipr & 0x3ffe)

#endif /* __INTC_H__ */
