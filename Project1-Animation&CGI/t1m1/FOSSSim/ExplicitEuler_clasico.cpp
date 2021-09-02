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

  
  //scene.time_stamp += dt;
  
  //cout << scene.pepe << endl;

  VectorXs& x = scene.getX();

  
  VectorXs& v = scene.getV();
  
  
  const VectorXs& m = scene.getM();
  
  VectorXs F(x.size());
  
  F.setZero();
  
  
  scene.accumulateGradU(F);   //le aplica la fuerza del XML??

  F *= -1.0;  //multiplica por menos uno  F *= -1.0  --> F = F * (-1.0)
  
  
 


  
  
  //quitamos la fuerza a los que son fijos
  int i;
  

  
  for(i=0;i<scene.getNumParticles();i++)
  {
	if(scene.isFixed(i))
		{
			int pos = i*2;
			     
		F.segment(pos,2).setZero();
		}
  
  
  }


  
  //calculamos Explicit Euler con velocidad


  x = x + dt*v; 
  

  

 
  
   cout << "1----------- F0: " << F[0] << "  F1: " << F[1] << "   F2: " << F[2] << "   F3: " << F[3] << endl;
  
  
  F.array() /= m.array();  // F.array()  = F.array / m.array()
  
         //cout << "2 ------- F0: " << F[0] << "   F1: " << F[1] << "   F2: " << F[2] << "   F3: " << F[3] << endl;
    
  v = v + dt*F;
  
         //cout << "2 ------- V0: " << v[0] << "   V1: " << v[1] << "   V2: " << v[2] << "   V3: " << v[3] << endl;

  
 
  
  
  
  

    return true;
}
