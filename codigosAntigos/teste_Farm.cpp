#include <iostream>
#include <complex.h>

#include "ppm.h"
#include "Esqueleto_Farm.h"
ppm_t* imagem;
int width = 640;
int height = 380;
int iterations = 3000;
int num_threads =64;
  
class Para_in{
  private:
    int id;
  public:
  
    Para_in(){
      this->id=0; 
    }
    
    Para_in(const Para_in &e){
      this->id=e.id;
    }
    
    Para_in(int id){
      this->id=id;
    }
    
    void setId(int id){
      this->id=id;
    }
    
    int getId(){
      return this->id;
    }
};

template<class IN, class OUT>
class MyFarm: public Farm<IN,OUT>{
  public:
    
    MyFarm(OUT* (&func)(IN*),IN *data_in, OUT *data_out, int num_th) : Farm<IN,OUT>(func, data_in, data_out, num_th){}
   ~MyFarm(){ };
   
   IN * split(IN *data_in,int n_thread) const{
     Para_in* in = new Para_in(n_thread);
     return in;
   }
   
   OUT * merge(OUT *list_out, int n_thread,  OUT split_out)const {

   }
};

Para_in* mandelbrot(Para_in* p){
  int i;
  int j;
  int k;
//   printf("ptr %d \n",ptr);
  int iter;
  complex float c;
  complex float z;
  int ptr=p->getId();
  
  
  iter = width / num_threads * (ptr + 1);

  for(i = (width / num_threads * ptr); i < iter; i++){
    for(j = 0; j < height; j++){
      c = (-2 + ((3. / (width - 1)) * i)) + ((-1 + ((2. / (height - 1)) * j)) * I);
      z = 0 + 0 * I;
      k = 0;
      
      while((cabsf(z) < 2) && (k < iterations)){
	z = z * z + c;
	k++;
      }
     ppm_insert(imagem, j, i, ((iterations - k) * 25));
    }
  }
  return p;
}

int main(){
  Para_in *p_in = new Para_in();
  Para_in *p_out = new Para_in();
  imagem = ppm_init(width, height, iterations);
  MyFarm<Para_in,Para_in> *my = new MyFarm<Para_in,Para_in>(mandelbrot,p_in,p_out,64);
  my->run();  
  ppm_write(imagem, "mandelbrot.ppm");
  ppm_close(imagem);
  return 0;
}