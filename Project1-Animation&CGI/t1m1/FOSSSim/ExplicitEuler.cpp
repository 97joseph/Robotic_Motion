#include <iostream>
using namespace std;

#include "ExplicitEuler.h"
#include <typeinfo>




bool ExplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
    // Your code goes here!
    
    // Some tips on getting data from TwoDScene:
    // A vector containing all of the system's position DoFs. x0, y0, x1, y1, ...
    //VectorXs& x = scene.getX();
    // A vector containing all of the system's velocity DoFs. v0, v0, v1, v1, ...
    //VectorXs& v = scene.getV();
    // A vector containing the masses associated to each DoF. m0, m0, m1, m1, ...
    //const VectorXs& m = scene.getM();
    // Determine if the ith particle is fixed
    // if( scene.isFixed(i) )

  scene.time_stamp += dt;

  const VectorXs& m = scene.getM();  
  
  VectorXs& x = scene.getX();

  
  VectorXs& v = scene.getV();
  
  VectorXs E(x.size());
  E.setZero();

  //Añado velocidad dinamicamente
  
  double power = 15.0;
  double delta_time_1 = 1.0;  //espera a que empiecen los fuegos
  
  
  
  //velocidad inicial
  

  	double pp = scene.time_stamp*100.0;

  int a = (int)pp;
  int b = a%50;
  int cc = a/50-1;
  //double z = a/5;
  //int b = (int)a % 5;
  
  //cout << scene.time_stamp << "----------" << pp << " -- " << a << " --- " << b << "--------------" << endl;

  if(b == 0 && cc < 80){  
  
  ////cout << scene.time_stamp << " -- " << a << " -- " << b << endl;

  int k;
  
  k = a / 50 - 1;


  cout << k << endl;
  
  if(k<19){    // primeros fuegos
  
  double ang1;

   
  ang1 = (double)k;


  double p1 = ang1*3.1416/180.0;
  
  v[k*4] = power*sin(p1); 
  v[k*4+1] = power*cos(p1);
  v[k*4+2] = (-1)*power*sin(p1); 
  v[k*4+3] = power*cos(p1);
  
      //cout << m[k*4] << " -1-- " << m[k*4+1] <<endl;     


   
     }  
     
     if(k>19){
     	
     	  double ang12 = (double)k;
     	
     	  double p2 = ang12*3.1416/180.0;
     
  v[k*4] = (-1)*power*sin(p2); 
  v[k*4+1] = power*cos(p2);
  v[k*4+2] = power*sin(p2); 
  v[k*4+3] = power*cos(p2);
     
     //cout << m[k*4] << " -2-- " << m[k*4+1] <<endl;
     
     
     }
     
     
     
     
     
 
 }
  

  
  
  

  //cout << x.size();

  
  VectorXs F(x.size());
  
  // Vector fuerza: f0, f0, f1, f1, ...
    
  F.setZero();
  
  
  scene.accumulateGradU(F);   //le aplica la fuerza del XML??

  F *= -1.0;  //multiplica por menos uno  F *= -1.0  --> F = F * (-1.0)
  
  
  //cout << F.format(CleanFmt) << endl;
  
  //cout << "----------------------" << endl;
  
  


  
  
  //quitamos la fuerza a los que son fijos
  
  int i;
  

  
  for(i=0;i<scene.getNumParticles();i++)
  {
	if(scene.isFixed(i))
		{
			int pos = i*2;
			      //cout << "12**********************" << endl;
			            //cout << F.segment(pos,2) << endl;
		F.segment(pos,2).setZero();
		}
  
  
  }

    // quito la fuerza para los que han llegado al suelo. (si están en posicion cero y con velocidad negativa)
  
  for(i=0;i<scene.getNumParticles();i++)
  
  {
    int posY = i*2+1;
    int posX = i*2;
    int finalposY = 0.001;
    
    //cout << v[1] << endl;
    
     if(x[posY]<finalposY && v[posY] < 0){
     	
     	
     	v[posY]=0.0;
     	v[posX]=0.0;   
     	F[posY]=0.0;
     	F[posX]=0.0;
     	x[posY]=finalposY;
     	
     	
     	//cout << "end" << endl;
     	}
  
  } 


  x = x + dt*v; 
  

  
  

  

  // Para la segunda ecuación hay que dividir la Fuerza por la masa porque no tenemos el momento sino la velocidad.
  
  
  F.array() /= m.array();  // F.array()  = F.array / m.array()
  
      
    
  v = v + dt*F;
  
  

  
 
  
  
  
  

    return true;
}
