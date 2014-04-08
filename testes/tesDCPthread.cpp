#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "compute_time.c"
int *a;

typedef struct node {
    int i;
    int j;
} NODE;

void merge(int i, int j)
{
        int mid = (i+j)/2;
        int ai = i;
        int bi = mid+1;

        int newa[j-i+1], newai = 0;

        while(ai <= mid && bi <= j) {
                if (a[ai] > a[bi])
                        newa[newai++] = a[bi++];
                else                    
                        newa[newai++] = a[ai++];
        }

        while(ai <= mid) {
                newa[newai++] = a[ai++];
        }

        while(bi <= j) {
                newa[newai++] = a[bi++];
        }

        for (ai = 0; ai < (j-i+1) ; ai++)
                a[i+ai] = newa[ai];

}

void * mergesort(void *a)
{
  NODE *p = (NODE *)a;
  if(p->i >= p->j)  return NULL;

  NODE n1, n2;
  int mid = (p->i+p->j)/2;
     pthread_t tid1, tid2;
     int ret;

     n1.i = p->i;
     n1.j = mid;

     n2.i = mid+1;
     n2.j = p->j;

     pthread_create(&tid1, NULL, mergesort, &n1);
     //pthread_create(&tid2, NULL, mergesort, &n2);
     mergesort(&n2);      
     pthread_join(tid1, NULL);
    //pthread_join(tid2, NULL);

    merge(p->i, p->j);
}

void mergesortSeq(int inicio, int fim)
{
  if (inicio == fim) return ;
    int meio = (inicio+fim)/2;
    mergesortSeq(inicio,meio);
    mergesortSeq(meio+1,fim);
    merge(inicio, fim);
    
}


int main(int argc, char **argv){
  int n=atoi(argv[1]);
  a = new int[n];
  int i;

  for(i=0;i<n;i++) a[i]=n-i;
  int meio=(0+(n-1))/2;
  NODE m;
  m.i = 0;
  m.j = meio;
  pthread_t tid;
  int ret; 

  time_log_start(); 
  pthread_create(&tid, NULL, mergesort, &m);
  mergesortSeq(meio+1,n-1);
  pthread_join(tid, NULL);
  merge(0,n-1);
  time_log_stop();

  printf("\n");
  delete a;
  return 0;
}
