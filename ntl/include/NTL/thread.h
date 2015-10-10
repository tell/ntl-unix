
#ifndef NTL_thread__H
#define NTL_thread__H

#include <NTL/tools.h>
#include <string>

#ifdef NTL_THREADS

#include <atomic>
#include <mutex>

#endif

NTL_OPEN_NNS


#ifdef NTL_THREADS

class AtomicLong {
private:
   NTL_SNS atomic_long data;

   AtomicLong(const AtomicLong& other); // disabled
   AtomicLong& operator=(const AtomicLong& other); // disabled

public:
   
   explicit AtomicLong(const long& _data) : data(_data) { }
   AtomicLong& operator=(const long& _data) 
   { 
      data.store(_data, NTL_SNS memory_order_release);
      return *this; 
   }
   operator long() const { return data.load( NTL_SNS memory_order_acquire); }
};


class AtomicBool {
private:
   NTL_SNS atomic_bool data;

   AtomicBool(const AtomicBool& other); // disabled
   AtomicBool& operator=(const AtomicBool& other); // disabled

public:
   
   explicit AtomicBool(const bool& _data) : data(_data) { }
   AtomicBool& operator=(const bool& _data) 
   { 
      data.store(_data, NTL_SNS memory_order_release);
      return *this; 
   }
   operator bool() const { return data.load( NTL_SNS memory_order_acquire); }
};





class AtomicRefCount {
private:
   NTL_SNS atomic_long cnt;

public:
   AtomicRefCount() : cnt(0) { }
   void inc() { cnt.fetch_add(1, NTL_SNS memory_order_relaxed); }
   bool dec() 
   {  
      if (cnt.fetch_sub(1, NTL_SNS memory_order_release) == 1) {
         NTL_SNS atomic_thread_fence(NTL_SNS memory_order_acquire);
         return true;
      }
      else
         return false;
   }
};

class MutexProxy { 
private:
   NTL_SNS mutex mtx;

   MutexProxy(const MutexProxy&); // disabled
   void operator=(const MutexProxy&); // disabled

public:
   MutexProxy() { }

   friend class GuardProxy;
};

class GuardProxy {
private:
   NTL_SNS unique_lock<NTL_SNS mutex> lck;


   GuardProxy(const GuardProxy&); // disabled
   void operator=(const GuardProxy&); // disabled

public:
   GuardProxy(MutexProxy& mtx) : lck(mtx.mtx, NTL_SNS defer_lock) { }
   void lock() { lck.lock(); }
};


#else

class AtomicLong {
private:
   long data;

   AtomicLong(const AtomicLong& other); // disabled
   AtomicLong& operator=(const AtomicLong& other); // disabled

public:
   
   explicit AtomicLong(const long& _data) : data(_data) { }
   AtomicLong& operator=(const long& _data) { data = _data; return *this; }
   operator long() const { return data; }
};


class AtomicBool {
private:
   bool data;

   AtomicBool(const AtomicBool& other); // disabled
   AtomicBool& operator=(const AtomicBool& other); // disabled

public:
   
   explicit AtomicBool(const bool& _data) : data(_data) { }
   AtomicBool& operator=(const bool& _data) { data = _data; return *this; }
   operator bool() const { return data; }
};

class AtomicRefCount {
private:
   long cnt;

public:
   AtomicRefCount() : cnt(0) { }
   void inc() { cnt++; }
   bool dec() { cnt--; return cnt == 0; }
};

class MutexProxy { 
private:
   MutexProxy(const MutexProxy&); // disabled
   void operator=(const MutexProxy&); // disabled

public:
   MutexProxy() { }
};

class GuardProxy {
private:
   GuardProxy(const GuardProxy&); // disabled
   void operator=(const GuardProxy&); // disabled

public:
   GuardProxy(MutexProxy&) { }
   void lock() { }
};

#endif




const NTL_SNS string& CurrentThreadID();


/*********************************************************************

NOTES: See 


http://preshing.com/20120913/acquire-and-release-semantics/
http://preshing.com/20130922/acquire-and-release-fences/
http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
http://preshing.com/20131125/acquire-and-release-fences-dont-work-the-way-youd-expect/

for general information on C++11 atomics.


Also see

http://www.chaoticmind.net/~hcb/projects/boost.atomic/doc/atomic/usage_examples.html#boost_atomic.usage_examples.example_reference_counters

for reference counting in a multi-threaded environment.

*********************************************************************/


NTL_CLOSE_NNS

#endif
