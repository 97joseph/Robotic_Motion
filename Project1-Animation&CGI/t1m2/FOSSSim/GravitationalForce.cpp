#include "GravitationalForce.h"

void GravitationalForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size()%2 == 0 );
  assert( m_particles.first >= 0 );  assert( m_particles.first < x.size()/2 );
  assert( m_particles.second >= 0 ); assert( m_particles.second < x.size()/2 );

  // Your code goes here!
}

void GravitationalForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
  assert( m_particles.first >= 0 );  assert( m_particles.first < x.size()/2 );
  assert( m_particles.second >= 0 ); assert( m_particles.second < x.size()/2 );

  // Your code goes here!
   
  //l es la distancia entre los dos vectores.
  //n es el vector normalizado.
  //k --> m_k
  //m_G es la gravedad
  
  //vector normalizado
  //numerador  =  X(1x) - X(2x), X(1y) - X(2y) 
  
  scalar normX = x[2*m_particles.second]-x[2*m_particles.first];
  scalar normY = x[2*m_particles.second+1]-x[2*m_particles.first+1];
  scalar modulo = sqrt( ( (x[2*m_particles.second]-x[2*m_particles.first]) * (x[2*m_particles.second]-x[2*m_particles.first]) ) + 
  ( (x[2*m_particles.second+1]-x[2*m_particles.first+1]) * (x[2*m_particles.second+1]-x[2*m_particles.first+1]) ));
  
  normX = normX/modulo;
  normY = normY/modulo;
  
  //cout << normX << " --- " << normY << endl;
  
  scalar l = modulo;
  
  scalar dU1x = -m_G*m[2*m_particles.first]*m[2*m_particles.second]*normX/(l*l);
  scalar dU1y = -m_G*m[2*m_particles.first]*m[2*m_particles.second]*normY/(l*l);
  scalar dU2x = -dU1x;
  scalar dU2y = -dU1y;
  
  gradE[2*m_particles.second] += dU2x;
  gradE[2*m_particles.second+1] += dU2y;
  gradE[2*m_particles.first] += dU1x;
  gradE[2*m_particles.first+1] += dU1y;
  
  
  
}
