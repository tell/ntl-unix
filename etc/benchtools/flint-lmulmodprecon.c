#include <NTL/lzz_pX.h>
#include <flint/nmod_poly.h>
#include <cstdio>

NTL_CLIENT



struct Flintzz_pX {
   nmod_poly_t value;

   explicit
   Flintzz_pX(const zz_pX& a)
   {
      long da = deg(a);
      nmod_poly_init2(value, zz_p::modulus(), da+1);

      for (long i = 0; i <= da; i++) {
         nmod_poly_set_coeff_ui(value, i, rep(a[i]));
      }
   }


   Flintzz_pX()
   {
      nmod_poly_init(value, zz_p::modulus());
   }


   ~Flintzz_pX() { nmod_poly_clear(value); }
};

int main()
{
   setbuf(stdout, NULL);

   for (long l = 5; l <= 60; l += 5) {
      // for (long n = 1024; n <= 65536; n *= 2) {
      for (long idx = 0; idx < 13; idx ++) {
         long n  = 1024*(1L << idx/2);
         if (idx & 1) n += n/2;
           SetSeed((ZZ(l) << 64) + ZZ(n));

	   long p;

	   RandomLen(p, l);
           if (p % 2 == 0) p++;
	   zz_p::init(p);


	   zz_pX a, b, c, f;

	   random(a, n);
	   random(b, n);
           random(f, n);
           SetCoeff(f, n);

           zz_pXModulus F(f);
           zz_pXMultiplier B(b, F);

	   double t;

	   MulMod(c, a, B, F);

	   long iter = 1;
	   do {
	      t = GetTime();
	      for (long i = 0; i < iter; i++) MulMod(c, a, B, F);
	      t = GetTime() - t;
	      iter *= 2;
	   } while (t < 3);
	   iter /= 2;

	   t = GetTime();
	   for (long i = 0; i < iter; i++) MulMod(c, a, B, F);
	   t = GetTime()-t;
	   double NTLTime = t;



         Flintzz_pX f_a(a), f_b(b), f_c, f_f(f), f_finv;
         nmod_poly_reverse(f_finv.value, f_f.value, f_f.value->length);
         nmod_poly_inv_series_newton(f_finv.value, f_finv.value, f_f.value->length);

         nmod_poly_mulmod_preinv(f_c.value, f_a.value, f_b.value, f_f.value, f_finv.value);


         t = GetTime();
         for (long i = 0; i < iter; i++)
            nmod_poly_mulmod_preinv(f_c.value, f_a.value, f_b.value, f_f.value, f_finv.value);
         t = GetTime()-t;
         double FlintTime = t;


         printf("%8.2f", FlintTime/NTLTime);
      }

      printf("\n");
   }
}


