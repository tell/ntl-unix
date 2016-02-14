#include <NTL/ZZ_pXFactoring.h>
#include <NTL/BasicThreadPool.h>
#include "argmapping.h"

#include <cstdio>
#include <cstdlib>

#include <sys/time.h>
#include <sys/resource.h>


NTL_CLIENT



//namespace NTL { extern double ip_time; }

int main(int argc, char **argv)
{
   ArgMapping amap;

   long n = 1024;
   amap.arg("n", n, "degree bound");

   long l = 1024;
   amap.arg("l", l, "coeff bound");

   long nt = 1;
   amap.arg("nt", nt, "num threads");

   amap.parse(argc, argv);

   cerr << "\n\n=============================\n\n";

   cerr << "n=" << n << "\n";
   cerr << "l=" << l << "\n";
   cerr << "nt=" << nt << "\n";

   SetSeed(ZZ(0));

   SetNumThreads(nt);

   ZZ p;

   RandomPrime(p, l);
   ZZ_p::init(p);


   ZZ_pX f;

   random(f, n);
   SetCoeff(f, n);

   Vec< Pair<ZZ_pX, long> > fac;


   double t;

   ZZ_pXFileThresh = 1e9;



   FILE *fp;
   unsigned long A[4], B[4];
   int loadavg;

   fp = fopen("/proc/stat","r");
   fscanf(fp,"cpu %lu %lu %lu %lu",&A[0],&A[1],&A[2],&A[3]);
   fclose(fp);
   
   
   t = GetTime();
   CanZass(fac, f, 1);
   t = GetTime()-t;
   double NTLTime = t;

   fp = fopen("/proc/stat","r");
   fscanf(fp,"cpu %lu %lu %lu %lu",&B[0],&B[1],&B[2],&B[3]);
   fclose(fp);
   
   // we multiply by 20 -- that's the total number of cores
   loadavg = int(100.0*20.0*double((B[0]+B[1]+B[2]) - (A[0]+A[1]+A[2])) / 
      double((B[0]+B[1]+B[2]+B[3]) - (A[0]+A[1]+A[2]+A[3])));
   fprintf(stderr, "CPU utilization: %d\%\n",loadavg);

   struct rusage rusage;
   getrusage( RUSAGE_SELF, &rusage );

   cerr << "MAX_RSS="<<rusage.ru_maxrss <<  "KB" << endl;
   cerr << "Fac: " << t << "\n";

   //cerr << "ip_time: " << ip_time << "\n";

   delete NTLThreadPool;
   NTLThreadPool = 0;


}


