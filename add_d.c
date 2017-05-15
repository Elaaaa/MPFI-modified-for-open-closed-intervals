/* add_d.c -- Interval translation.

Copyright 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2010,
                     Spaces project, Inria Lorraine
                     and Salsa project, INRIA Rocquencourt,
                     and Arenaire project, Inria Rhone-Alpes, France
                     and Lab. ANO, USTL (Univ. of Lille),  France

This file is part of the MPFI Library.

The MPFI Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFI Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFI Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
MA 02110-1301, USA. */

#include "mpfi-impl.h"

int
mpfi_add_d (mpfi_ptr a, mpfi_srcptr b, const double c)
{
  int inexact_left, inexact_right, inexact = 0;
 
  /**Adding code to support both open and closed intervals**/  
     a->left_open = b->left_open;
     a->right_open = b->right_open;
  /**Adding code to support both open and closed intervals**/ 
  inexact_left  = mpfr_add_d (&(a->left), &(b->left), c, MPFI_RNDD);
  inexact_right = mpfr_add_d (&(a->right), &(b->right), c, MPFI_RNDU);

  /* do not allow -0 as lower bound */
  if (mpfr_zero_p (&(a->left)) && mpfr_signbit (&(a->left))) {
    mpfr_neg (&(a->left), &(a->left), MPFI_RNDU);
  }
  /* do not allow +0 as upper bound */
  if (mpfr_zero_p (&(a->right)) && !mpfr_signbit (&(a->right))) {
    mpfr_neg (&(a->right), &(a->right), MPFI_RNDD);
  }

  if (MPFI_NAN_P (a))
    MPFR_RET_NAN;

  if (inexact_left)
      inexact += 1;
  if (inexact_right)
      inexact += 2;

  return inexact;
}
