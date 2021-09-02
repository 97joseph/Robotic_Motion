#include "SymplecticEuler.h"

bool SymplecticEuler::stepScene( TwoDScene& scene, scalar dt )
{
  // Your code goes here!
  

  const VectorXs& m = scene.getM();  
  
  VectorXs& x = scene.getX();

  
  VectorXs& v = scene.getV();

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


  //x = x + dt*v; 
  

  

  // Para la segunda ecuación hay que dividir la Fuerza por la masa porque no tenemos el momento sino la velocidad.
  
   //cout << "1----------- F0: " << F[0] << "  F1: " << F[1] << "   F2: " << F[2] << "   F3: " << F[3] << endl;
  
  
  F.array() /= m.array();  // F.array()  = F.array / m.array()
  
         //cout << "2 ------- F0: " << F[0] << "   F1: " << F[1] << "   F2: " << F[2] << "   F3: " << F[3] << endl;
    
  x = x + dt*(v + dt*F);
  v = v + dt*F;
  
         //cout << "2 ------- V0: " << v[0] << "   V1: " << v[1] << "   V2: " << v[2] << "   V3: " << v[3] << endl;

  
 
  

  return true;
}






