#include "SimpleGravityForce.h"
#include <iostream>
using namespace std;

void SimpleGravityForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
    assert( x.size() == v.size() ); // verificar tamaños vectores
    assert( x.size() == m.size() ); // verificar tamaños vectores
    assert( x.size()%2 == 0 );      // verificar que el vector tiene tamaño par.
    
    // Your code goes here!
    
  int num_particles = x.size() / 2;
     
    VectorXs gradU(x.size()); 
    gradU.setZero();
    
    scalar U=0;
    
    
    
    for (int i = 0; i < num_particles; ++i) {
    	
    	      //Multiplicamos masa por gravedad coeficiente a coeficiente --> (1,1) * (0,-9.81)   El vector m_gravity es (0,-9.81) y viene dado por el XML.
        // Resultado es (0,-9.81)
        //Como es negativo --> (0,9.81)
        
        //cout << m_gravity << endl;
        //cout << m_gravity.size() << endl;
 
    	  
    	  U = U - (-1) * m[2*i] * m_gravity[0] * x[2*i] + (-1) * m[2*i+1] * m_gravity[1] + x[2*i+1];
    	      	



    }
    
    E = E + U;
}

void SimpleGravityForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
    assert( x.size() == v.size() );
    assert( x.size() == m.size() );
    assert( x.size() == gradE.size() );
    assert( x.size()%2 == 0 );
    
    // Your code goes here!
    
    //cout << m.array() << endl;
    
    
    int num_particles = x.size() / 2;
     
    VectorXs gradU(x.size()); 
    gradU.setZero();
    
    
    for (int i = 0; i < num_particles; ++i) {
    	
    
    	       
        //Multiplicamos masa por gravedad coeficiente a coeficiente --> (1,1) * (0,-9.81)   El vector m_gravity es (0,-9.81) y viene dado por el XML.
        // Resultado es (0,-9.81)
        //Como es negativo --> (0,9.81)
        
        //cout << m_gravity << endl;
        //cout << m_gravity.size() << endl;
        
        gradU[2*i] = (-1) * m[2*i] * m_gravity[0];
    	  gradU[2*i+1] = (-1) * m[2*i+1] * m_gravity[1];

        
    }
    
    gradE = gradE + gradU;
}
