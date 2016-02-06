#pragma once
#include "Particle.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../WaveFunction/WaveFunction.h"
#include "../InitialState/InitialState.h"
#include <vector>
#include <chrono>
#include <random>

class System
{
 
  public:
    bool metropolis		    ();
    void runMetropolis		    (int nCycles);
    void set_nDimensions	    (int nDimensions);
    void set_nParticles	  	    (int nParticles);
    void set_nCycles	  	    (int nCycles);
    void set_stepLength		    (double stepLength);
    void set_derivativeStep	    (double h);
    void set_equilibrationFraction  (double equilibractionFraction);
    void set_Hamiltonian	    (Hamiltonian* hamiltonian);
    void set_WaveFunction	    (WaveFunction* waveFunction);
    void set_InitialState	    (InitialState* initalState);
    
    int get_nDimensions	    (){return my_nDimensions;}
    int get_nParticles	    (){return my_nParticles;}



    class Hamiltonian*	    get_hamiltonian()	{return my_hamiltonian;}
    class WaveFunction*	    get_waveFunction()	{return my_waveFunction;}
    class Particle*	    get_particle()	{return my_particles;}
    class Sampler*	    get_sampler()	{return	my_sampler;}

  private:

    int my_nDimensions		  = 0;
    int my_nParticles		  = 0;
    int my_nCycles		  = 0;
    double my_stepLength	  = 0.0;
    double derivativeStep	  = 0.0;
    double derivativeStep2	  = 0.0;
    double equilibrationFraction  = 0.0;

    class Hamiltonian*	    my_hamiltonian    = nullptr;
    class WaveFunction*	    my_waveFunction   = nullptr;
    class InitialState*	    my_initialState   = nullptr;
    //class Particle*	    my_particles      = nullptr;
    class Sampler*	    my_sampler	      = nullptr;

    std::vector<class Particle*> my_particles = std::vector<class Particle*>();
    /*
    typedef std::chrono::high_resolution_clock clock;
    clock::time_point my_start = clock::now();
    std::uniform_real_distribution<double> my_uniform (0.0,1.0);
    std::default_random_engine my_generator;
    */

};
