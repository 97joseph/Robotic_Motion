#include "SpringForce.h"
#include <iostream>
using namespace std;

void SpringForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
  assert( x.size() == v.size() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );

  // Your code goes here!
  
  
  cout <<  " --- "  << endl;
  
}

void SpringForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );

  // Your code goes here!
  
   ///m_endpoints es del tipo pair
   
   
   //cout << x[2] << " -- " << x[3] << " -- "<< x [4] << " -- " << x[5] << endl;
   cout << sqrt(  ( (x[6] - x[2])*(x[6] - x[2]) + (x[7] - x[3])*(x[7] - x[3])  )  ) << endl;
  
  //l es la distancia entre los dos vectores.
  //n es el vector normalizado.
  //k --> m_k
  //m_b
  
  //vector normalizado
  //numerador  =  X(1x) - X(2x), X(1y) - X(2y) 
  
  scalar normX = x[2*m_endpoints.second]-x[2*m_endpoints.first];
  scalar normY = x[2*m_endpoints.second+1]-x[2*m_endpoints.first+1];
  scalar modulo = sqrt( ( (x[2*m_endpoints.second]-x[2*m_endpoints.first]) * (x[2*m_endpoints.second]-x[2*m_endpoints.first]) ) + 
  ( (x[2*m_endpoints.second+1]-x[2*m_endpoints.first+1]) * (x[2*m_endpoints.second+1]-x[2*m_endpoints.first+1]) ));
  
  normX = normX/modulo;
  normY = normY/modulo;
  
  //cout << normX << " --- " << normY << endl;
  
  scalar l = modulo;
  
  scalar dU1x = -m_k*(l-m_l0)*normX;
  scalar dU1y = -m_k*(l-m_l0)*normY;
  scalar dU2x = -dU1x;
  scalar dU2y = -dU1y;
  
  //   Fuerza disipativa.    Beta*(n producto escalar (xj-xi)) n
   
  scalar restaX = v[2*m_endpoints.second]-v[2*m_endpoints.first];
  scalar restaY = v[2*m_endpoints.second+1]-v[2*m_endpoints.first+1];  
  
  scalar prod_escalar = m_b * (normX*restaX + normY*restaY);
  
  scalar eU1x = prod_escalar * normX;
  scalar eU1y = prod_escalar * normY;
  scalar eU2x = -eU1x;
  scalar eU2y = -eU1y;  
  
  gradE[2*m_endpoints.second] += dU2x;
  gradE[2*m_endpoints.second+1] += dU2y;
  gradE[2*m_endpoints.first] += dU1x;
  gradE[2*m_endpoints.first+1] += dU1y;
  
  //cout << dU2y << " --- "  << eU2y << " --- " << dU1y << " -- " << eU1y << endl;
  
  gradE[2*m_endpoints.second] -= eU2x;
  gradE[2*m_endpoints.second+1] -= eU2y;
  gradE[2*m_endpoints.first] -= eU1x;
  gradE[2*m_endpoints.first+1] -= eU1y;
  
  
   
}















