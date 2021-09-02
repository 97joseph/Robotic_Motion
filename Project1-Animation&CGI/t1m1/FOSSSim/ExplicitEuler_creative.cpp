#include <iostream>
using namespace std;

#include "ExplicitEuler.h"
#include <typeinfo>

Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");


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

  VectorXs& x = scene.getX();

  
  VectorXs& v = scene.getV();
  
  VectorXs E(x.size());
  E.setZero();

  //Añado velocidad dinamicamente
  
  double power = 5.0;
  
  //velocidad inicial
  
   if(scene.time_stamp == dt){
  for(int k=0;k<179;k++)
  
  {
  	
  double p;
  
  //p = (double)k*10 + 10;
  p = (double)k-89;
  //if(k > 4){p = (double)k*10;}
  //if(k == 4){p = 45.0;}
  
  p = p*3.1416/180.0;
  
 
   if(E[k]==0.0) {

    v[k*2] = power*sin(p); 
    v[k*2+1] = power*cos(p);    
  
  }

  }
  }
  const VectorXs& m = scene.getM();
  

  //cout << x.size();

  
  VectorXs F(x.size());
  
  // Vector fuerza: f0, f0, f1, f1, ...
    
  F.setZero();
  
  
  scene.accumulateGradU(F);   //le aplica la fuerza del XML??

  F *= -1.0;  //multiplica por menos uno  F *= -1.0  --> F = F * (-1.0)
  
  
  //cout << F.format(CleanFmt) << endl;
  
  //cout << "----------------------" << endl;
  
  //cout << F.array() << endl;
  
  
    //cout << "1**********************" << endl;


  
    //cout << typeid(F.array()).name() << endl;

  //calculamos Explicit Euler con velocidad
  
  
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
    int finalposY = -2.0;
    
    //cout << v[1] << endl;
    
     if(x[posY]<finalposY && v[posY] < 0){
     	
     	
     	v[posY]=0.0;
     	v[posX]=0.0;   
     	F[posY]=0.0;
     	F[posX]=0.0;
     	x[posY]=finalposY;
     	E[posX]=1.0;
     	
     	//cout << "end" << endl;
     	}
  
  } 


  x = x + dt*v; 
  

  
  

  

  // Para la segunda ecuación hay que dividir la Fuerza por la masa porque no tenemos el momento sino la velocidad.
  
  
  F.array() /= m.array();  // F.array()  = F.array / m.array()
  
      
    
  v = v + dt*F;
  
  

  
 
  
  
  
  

    return true;
}
