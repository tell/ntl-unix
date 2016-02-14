#include <NTL/ZZ_pX.h>
#include <flint/fmpz.h>
#include <flint/fmpz_mod_poly.h>
#include <cstdio>

NTL_CLIENT

struct FlintZZ {
   fmpz_t value;

   explicit
   FlintZZ(const ZZ& a)
   {
      long n = NumBits(a);
   
      fmpz_init(value);
   
      for (long i = 0; i < n; i++)
         if (bit(a, i)) fmpz_setbit(value, i);
   
      if (a < 0)
         fmpz_neg(value, value);

   }

   ~FlintZZ() { fmpz_clear(value); }

};



   



struct FlintZZ_pX {
   fmpz_mod_poly_t value;

   explicit
   FlintZZ_pX(const ZZ_pX& a)
   {
      long da = deg(a);
      FlintZZ f_p(ZZ_p::modulus());
      fmpz_mod_poly_init2(value, f_p.value, da+1);

      for (long i = 0; i <= da; i++) {
         FlintZZ f_c(rep(a[i]));
         fmpz_mod_poly_set_coeff_fmpz(value, i, f_c.value);
      }
   }

   ~FlintZZ_pX() { fmpz_mod_poly_clear(value); }
};

int main()
{
   setbuf(stdout, NULL);

   for (long l = 256; l <= 16384; l *= 2) {
      // for (long n = 256; n <= 16384; n *= 2) {
      for (long idx = 0; idx < 13; idx ++) {
         long n  = 256*(1L << idx/2);
         if (idx & 1) n += n/2;

           SetSeed((ZZ(l) << 64) + ZZ(n));

	   ZZ p;

	   RandomLen(p, l);
           if (!IsOdd(p)) p++;
	   ZZ_p::init(p);


	   ZZ_pX a, b, c;

	   random(a, n);
	   random(b, n);

	   long da = deg(a);
	   long db = deg(b);

	   double t;

	   mul(c, a, b); // FFTMul(c, a, b);

	   long iter = 1;
	   do {
	      t = GetTime();
	      for (long i = 0; i < iter; i++) mul(c, a, b); // FFTMul(c, a, b);
	      t = GetTime() - t;
	      iter *= 2;
	   } while (t < 3);
	   iter /= 2;

	   t = GetTime();
	   for (long i = 0; i < iter; i++) mul(c, a, b); // FFTMul(c, a, b);
	   t = GetTime()-t;
	   double NTLTime = t;


	   FlintZZ_pX f_a(a), f_b(b), f_c(c);


	   fmpz_mod_poly_mul(f_c.value, f_a.value, f_b.value);
	   t = GetTime();
	   for (long i = 0; i < iter; i++) fmpz_mod_poly_mul(f_c.value, f_a.value, f_b.value);
	   t = GetTime()-t;
	   double FlintTime = t;

           printf("%8.2f", FlintTime/NTLTime);
      }

      printf("\n");
   }
}


