#pragma once
#include "Particle.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../WaveFunction/WaveFunction.h"
#include <vector>

class System
{
 
  public:

    void set_nDimensions	    (int nDimensions);
    void set_nParticles	  	    (int nParticles);
    void set_nCycles	  	    (int nCycles);
    void set_stepLength		    (double stepLength);
    void set_equilibrationFraction  (double equilibractionFraction);
    
    int get_nDimensions	    (){return my_nDimensions;}
    int get_nParticles	    (){return my_nParticles;}

    std::vector<class Particle*>  get_particles {return my_particles;}

    class Hamiltonian*	    get_hamiltonian()	{return my_hamiltonian;}
    class WaveFunction*	    get_waveFunction()	{return my_waveFunction;}
    
  private:

    int my_nDimensions		  = 0;
    int my_nParticles		  = 0;
    int my_nCycles		  = 0;
    double my_stepLength	  = 0;
    double equilibrationFraction  = 0;

    class Hammiltonian*	    my_hamiltonian    = nullptr;
    class WaveFunction*	    my_waveFunction   = nullptr;

    std::vector<class Particle*> my_particles = std::vector<class Particle*>();

};
