#include <iostream>
#include <cinttypes>
#include <mcblas0.hpp>
#include <mcblas3.hpp>

#define ARCH_X86 1
//#define ARCH_ARM 1

#ifdef ARCH_X86
extern __inline__ uint64_t rdtsc(void)
{
  uint64_t a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}
#endif
#ifdef ARCH_ARM
extern __inline__ uint64_t rdtsc(void)
{
    u64 val;
    asm volatile("mrs %0, cntvct_el0" : "=r" (val));
    return val;
}
#endif

int main(int argc, char **argv)
{
  int Size=8;
  if (argc>1)
  {
    Size = atoi(argv[1]);
  }

  uint64_t timestamp_start = 0;
  uint64_t timestamp_stop = 0;


  // Création des vecteurs
  float **m1=mmsalloc(Size, Size);
  float **m2=mmsalloc(Size, Size);
  float **m3=mmsalloc(Size, Size);


  // Initialisation des Vecteurs
  mmsinit(Size,Size,m1,1.0,0.0);
  mmsinit(Size,Size,m2,1.0,0.0);
  mmsinit(Size,Size,m3,1.0,0.0);

  if (Size<64){
    std::cout << "\n\n===============================\n";
    std::cout << "Matrices before ssgemm: \n";
    mmsdump(Size, Size, m1);
    mmsdump(Size, Size, m2);
    mmsdump(Size, Size, m3);
  }

  timestamp_start = rdtsc();

  ssgemm(Size, Size, Size, 1.0, m1, m2, 1.0, m3);

  timestamp_stop = rdtsc();

  if (Size<64){
    std::cout << "\n\n===============================\n";
    std::cout << "Matrices after ssgemm: \n";
    mmsdump(Size, Size, m1);
    mmsdump(Size, Size, m2);
    mmsdump(Size, Size, m3);
  }

  mmsfree(m1, Size, Size);
  mmsfree(m2, Size, Size);
  mmsfree(m3, Size, Size);

  std::cout << Size << "   \t\t\t" << timestamp_stop - timestamp_start << "\n";

  return 0;
}
