#include <stdio.h>
#include <stdlib.h>

int fib(int n){
  if (n == 1) return 1;                             
  else if (n == 2) return 1;                 
  else return fib(n - 1) + fib(n - 2);
}

int main(int argc, char **argv){
  int n=atoi(argv[1]);
  int i;
  for(i=1; i<=n;i++) { 
  	printf("%d ",fib(i));
  	 }
  printf("\n");	
   return 0;
}


