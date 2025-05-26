#include<stdio.h>
#include<omp.h>

const double ln2=0.6931471805599453;

double func(double x){
  return (1.0/x);
}

int main(){

  omp_set_dynamic(0);
  int cores=omp_get_num_procs();
  printf("Available cores in this machine: %d\n",cores);
  omp_set_num_threads(cores);

  double lower_limit=1;
  double upper_limit=2;
  int n=10000;
  double h=(double)(upper_limit-lower_limit)/n;

  double sum=0.0;
  sum+=(func(lower_limit)+func(upper_limit));

  #pragma omp parallel reduction(+:sum)
  {
    #pragma omp for 
    for(int i=1;i<n;i+=2){
      sum+=(4*func(lower_limit+i*h));  
    }

    #pragma omp for
    for(int i=2;i<n;i+=2){
      sum+=(2*func(lower_limit+i*h));
    }
  }


  sum=(sum*(h/3.0));
  
  printf("\nEstimated natural logarithm of 2 calculated using Simpson's Rule is %.16f\n",sum);

  printf("\nThe correct natural logarithm of 2 truncated at 16 decimal places is %.16f\n",ln2);
  return 0;
}
