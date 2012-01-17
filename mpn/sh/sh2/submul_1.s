! SH2 __gmpn_submul_1 -- Multiply a limb vector with a limb and subtract
! the result from a second limb vector.

! Copyright 1995, 2000, 2011 Free Software Foundation, Inc.

! This file is part of the GNU MP Library.

! The GNU MP Library is free software; you can redistribute it and/or modify
! it under the terms of the GNU Lesser General Public License as published by
! the Free Software Foundation; either version 3 of the License, or (at your
! option) any later version.

! The GNU MP Library is distributed in the hope that it will be useful, but
! WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
! or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
! License for more details.

! You should have received a copy of the GNU Lesser General Public License
! along with the GNU MP Library.  If not, see http://www.gnu.org/licenses/.


! INPUT PARAMETERS
! res_ptr	r4
! s1_ptr	r5
! size		r6
! s2_limb	r7

	.text
	.align 1
	.global	___gmpn_submul_1
___gmpn_submul_1:
	mov	#0,r2		! cy_limb = 0
	mov	#0,r0		! Keep r0 = 0 for entire loop
	clrt

Loop:	mov.l	@r5+,r3
	dmulu.l	r3,r7
	sts	macl,r1
	addc	r2,r1		! lo_prod += old cy_limb
	sts	mach,r2		! new cy_limb = hi_prod
	mov.l	@r4,r3
	addc	r0,r2		! cy_limb += T, T = 0
	subc	r1,r3
	addc	r0,r2		! cy_limb += T, T = 0
	dt	r6
	mov.l	r3,@r4
	bf.s	Loop
	add	#4,r4

	rts
	mov	r2,r0
