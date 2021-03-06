#include "LinearizedImplicitEuler.h"
#include <iostream>
using namespace std;

//bool LinearizedImplicitEuler::stepScene( TwoDScene& scene, scalar dt )
//{
//  VectorXs& x = scene.getX();
//  VectorXs& v = scene.getV();
//  const VectorXs& m = scene.getM();
//  assert(x.size() == v.size());
//  assert(x.size() == m.size());

  // Your code goes here!
  
//  return true;
//}


bool LinearizedImplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
  VectorXs& x = scene.getX();
  VectorXs& v = scene.getV();
  const VectorXs& m = scene.getM();
  assert(x.size() == v.size());
  assert(x.size() == m.size());



  int nn = x.size();
  VectorXs dx = dt*v;
  VectorXs dv(nn);
  MatrixXs fdx(nn,nn);
  MatrixXs fdv(nn,nn);
  scene.accumulateddUdxdx(fdx, dx, dv);
  scene.accumulateddUdxdv(fdv, dx, dv);
  
  VectorXs gradU(nn);
  scene.accumulateGradU(gradU, dx, dv);  //F

  MatrixXs M = m.asDiagonal();
  
  //matriz A  
  
  MatrixXs A = M + dt*dt * fdx + dt * fdv;
  
  //resolvemos A*deltax = b
  
  VectorXs delta = A.fullPivLu().solve(-dt * gradU); // Compute the solution to A*x = b
  
    for(i=0;i<scene.getNumParticles();i++)
  {
	if(scene.isFixed(i))
		{
			int pos = i*2;
			     
		gradU.segment(pos,2).setZero();
		
		//falta pasar los puntos A a zero.
		
		}
  
  
  }

  v = v + delta;
  x = x + dt * v;

  return true;
}




