/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is library that provides for multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library is designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@iahu.ca, http://math.libtomcrypt.org
 */
#include <tommath.h>

/* shift right a certain amount of digits */
void
mp_rshd (mp_int * a, int b)
{
  int     x;

  /* if b <= 0 then ignore it */
  if (b <= 0) {
    return;
  }

  /* if b > used then simply zero it and return */
  if (a->used < b) {
    mp_zero (a);
    return;
  }

  {
    register mp_digit *tmpa, *tmpaa;

    /* shift the digits down */

    /* base */
    tmpa = a->dp;
    
    /* offset into digits */
    tmpaa = a->dp + b;
    
    /* this is implemented as a sliding window where the window is b-digits long
     * and digits from the top of the window are copied to the bottom
     *
     * e.g.
     
     b-2 | b-1 | b0 | b1 | b2 | ... | bb |   ---->
                 /\                   |      ---->
                  \-------------------/      ---->
    */         
    for (x = 0; x < (a->used - b); x++) {
      *tmpa++ = *tmpaa++;
    }

    /* zero the top digits */
    for (; x < a->used; x++) {
      *tmpa++ = 0;
    }
  }
  mp_clamp (a);
}
