#include <NTL/ZZX.h>
#include <flint/fmpz.h>
#include <flint/fmpz_poly.h>
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



   



struct FlintZZX {
   fmpz_poly_t value;

   explicit
   FlintZZX(const ZZX& a)
   {
      long da = deg(a);
      fmpz_poly_init2(value, da+1);

      for (long i = 0; i <= da; i++) {
         FlintZZ f_c(a[i]);
         fmpz_poly_set_coeff_fmpz(value, i, f_c.value);
      }
   }

   ~FlintZZX() { fmpz_poly_clear(value); }
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

	   ZZX a, b, c;

           a.SetLength(n);
           for (long i = 0; i < n; i++) RandomBits(a[i], l);
           a.normalize();

           b.SetLength(n);
           for (long i = 0; i < n; i++) RandomBits(b[i], l);
           b.normalize();


	   double t;

	   mul(c, a, b);

	   long iter = 1;
	   do {
	      t = GetTime();
	      for (long i = 0; i < iter; i++) mul(c, a, b);
	      t = GetTime() - t;
	      iter *= 2;
	   } while (t < 3);
	   iter /= 2;

	   t = GetTime();
	   for (long i = 0; i < iter; i++) mul(c, a, b);
	   t = GetTime()-t;
	   double NTLTime = t;


	   FlintZZX f_a(a), f_b(b), f_c(c);


	   fmpz_poly_mul(f_c.value, f_a.value, f_b.value);
	   t = GetTime();
	   for (long i = 0; i < iter; i++) fmpz_poly_mul(f_c.value, f_a.value, f_b.value);
	   t = GetTime()-t;
	   double FlintTime = t;

           printf("%8.2f", FlintTime/NTLTime);
      }

      printf("\n");
   }
}


