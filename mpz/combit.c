/* mpz_combit -- complement a specified bit.

Copyright 2002 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include "gmp.h"
#include "gmp-impl.h"

void
mpz_combit (mpz_ptr d, unsigned long int bit_index)
{
  mp_size_t dsize = ABSIZ(d);
  mp_ptr dp = LIMBS(d);
  
  mp_size_t limb_index = bit_index / BITS_PER_MP_LIMB;
  mp_limb_t bit = ((mp_limb_t) 1 << (bit_index % BITS_PER_MP_LIMB));

  if (limb_index >= dsize)
    {
      MPZ_REALLOC(d, limb_index + 1);
      dp = LIMBS(d);
      
      MPN_ZERO(dp + dsize, limb_index + 1 - dsize);
      dsize = limb_index + 1;
    }
    
  if (SIZ(d) >= 0)
    {
      dp[limb_index] ^= bit;
      MPN_NORMALIZE (dp, dsize);
      SIZ(d) = dsize;
    }
  else
    {
      mp_limb_t x = ~(dp[limb_index]) + 1;

      if (x & bit)
	{
	  /* Clearing the bit increases the magitude. We might need a carry. */
	  dsize++;
	  MPZ_REALLOC(d, dsize);
	  dp = LIMBS(d);

	  mpn_add_1(dp+limb_index, dp+limb_index, dsize + limb_index, bit);
	}
      else
	/* Setting the bit decreases the magnitude */
	mpn_sub_1(dp+limb_index, dp+limb_index, dsize + limb_index, bit);

      MPN_NORMALIZE (dp, dsize);
      SIZ(d) = -dsize;
    }
}