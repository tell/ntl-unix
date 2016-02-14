#include <NTL/lzz_pXFactoring.h>
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


struct FlintFac {
   nmod_poly_factor_t value;

   FlintFac() { nmod_poly_factor_init(value); }
   ~FlintFac() { nmod_poly_factor_clear(value); }

};

int main()
{
   setbuf(stdout, NULL);

   for (long l = 5; l <= 60; l += 5) {
      if (!(l == 5 || l == 10 || l == 15 || l== 30 || l == 60)) continue;

      // for (long n = 1024; n <= 16384; n *= 2) {
      for (long idx = 0; idx < 9; idx ++) {
         long n  = 1024*(1L << idx/2);
         if (idx & 1) n += n/2;
         SetSeed((ZZ(l) << 64) + ZZ(n));

	 long p;

	 p = RandomPrime_long(l);
	 zz_p::init(p);

         zz_pX f;
      
         random(f, n);
         SetCoeff(f, n);
      
         Vec< Pair<zz_pX, long> > fac;
      
      
         double t;
      
         t = GetTime();
         CanZass(fac, f);
         t = GetTime()-t;
         double NTLTime = t;

         long iter = 1;
         if (NTLTime < 5) {
            t = NTLTime;
            while (t < 5) {
               t += NTLTime;
               iter += 1;
            }

            t = GetTime();
            for (long i = 0; i < iter; i++) CanZass(fac, f);
            t = GetTime()-t;
            NTLTime = t;
         }
      
         Flintzz_pX f_f(f);
         FlintFac f_fac;
      
         t = GetTime();
         for (long i = 0; i < iter; i++) nmod_poly_factor_kaltofen_shoup(f_fac.value, f_f.value);
         t = GetTime()-t;
         double FlintTime = t;
      
         printf("%8.2f", FlintTime/NTLTime);
      }

      printf("\n");
   }
}


