#include <NTL/ZZ_pXFactoring.h>
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




struct FlintFac {
   fmpz_mod_poly_factor_t value;

   FlintFac() { fmpz_mod_poly_factor_init(value); }
   ~FlintFac() { fmpz_mod_poly_factor_clear(value); }

};

int main()
{
   setbuf(stdout, NULL);

   for (long l = 256; l <= 2048; l *= 2) {
      // for (long n = 256; n <= 16384; n *= 2) {
      for (long idx = 0; idx < 7; idx ++) {
         long n  = 256*(1L << idx/2);
         if (idx & 1) n += n/2;
         SetSeed((ZZ(l) << 64) + ZZ(n));

	 ZZ p;

	 RandomPrime(p, l);
	 ZZ_p::init(p);

         ZZ_pX f;
      
         random(f, n);
         SetCoeff(f, n);
      
         Vec< Pair<ZZ_pX, long> > fac;
      
      
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
      
         FlintZZ_pX f_f(f);
         FlintFac f_fac;
      
         t = GetTime();
         for (long i = 0; i < iter; i++) fmpz_mod_poly_factor_kaltofen_shoup(f_fac.value, f_f.value);
         t = GetTime()-t;
         double FlintTime = t;
      
         printf("%8.2f", FlintTime/NTLTime);
      }

      printf("\n");
   }
}


