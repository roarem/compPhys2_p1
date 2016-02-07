#pragma once
#include "Particle.h"
#include "Sampler.h"
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
    void set_Hamiltonian	    (class Hamiltonian* hamiltonian);
    void set_WaveFunction	    (class WaveFunction* waveFunction);
    void set_InitialState	    (class InitialState* initalState);
    void set_parameters		    (std::vector<double> parameters);
    
    int	    get_nDimensions		(){return my_nDimensions;}
    int     get_nParticles	    	(){return my_nParticles;}
    double  get_stepLength	    	(){return my_stepLength;}
    double  get_derivativeStep	    	(){return my_derivativeStep;}
    double  get_derivativeStep2	    	(){return my_derivativeStep2;}
    std::vector<double> get_parameters	(){return my_parameters;}


    class Hamiltonian*		  get_hamiltonian()	{return my_hamiltonian;}
    class WaveFunction*		  get_waveFunction()	{return my_waveFunction;}
    class Sampler*		  get_sampler()		{return	my_sampler;}
    std::vector<class Particle*>  get_particle()	{return my_particles;}

    void  add_particle (class Particle* particle); 
    
  protected:
    int my_nDimensions		     = 0;
    int my_nParticles		     = 0;
    int my_nCycles		     = 0;
    double my_stepLength	     = 0.0;
    double my_derivativeStep	     = 0.0;
    double my_derivativeStep2	     = 0.0;
    double my_equilibrationFraction  = 0.0;

    std::vector<double> my_parameters = std::vector<double>();
    
    class Hamiltonian*	    my_hamiltonian    = nullptr;
    class WaveFunction*	    my_waveFunction   = nullptr;
    class InitialState*	    my_initialState   = nullptr;
    //class Particle*	    my_particles      = nullptr;
    class Sampler*	    my_sampler	      = nullptr;

    std::vector<class Particle*> my_particles = std::vector<class Particle*>();

    typedef std::chrono::high_resolution_clock clock;
    clock::time_point my_start = clock::now();
    std::uniform_real_distribution<double> my_uniform {std::uniform_real_distribution<double>(0.0,1.0)};
    std::default_random_engine my_generator;

};


