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

/* set a 32-bit const */
int
mp_set_int (mp_int * a, unsigned long b)
{
  int     x, res;

  mp_zero (a);

  /* set four bits at a time, simplest solution to the what if DIGIT_BIT==7 case */
  for (x = 0; x < 8; x++) {

    /* shift the number up four bits */
    if ((res = mp_mul_2d (a, 4, a)) != MP_OKAY) {
      return res;
    }

    /* OR in the top four bits of the source */
    a->dp[0] |= (b >> 28) & 15;

    /* shift the source up to the next four bits */
    b <<= 4;

    /* ensure that digits are not clamped off */
    a->used += 32 / DIGIT_BIT + 1;
  }

  mp_clamp (a);
  return MP_OKAY;
}
