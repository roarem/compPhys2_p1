#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <string>
#include "Particle.h"
#include "../Sampler/Sampler.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../WaveFunction/WaveFunction.h"
#include "../InitialState/InitialState.h"

using std::cout;
using std::endl;
class System
{
 
  public:
    bool metropolis		    ();
    bool importanceSampling	    ();
    void runMetropolis		    ();
    void runImportanceSampling	    ();
    void set_nDimensions	    (int nDimensions);
    void set_nParticles	  	    (int nParticles);
    void set_nCycles	  	    (int nCycles);
    void set_stepLength		    (double stepLength);
    void set_derivativeStep	    (double h);
    void set_equilibrationFraction  (double equilibractionFraction);
    //void set_timeStep		    (double timeStep);
    void set_Hamiltonian	    (class Hamiltonian* hamiltonian);
    void set_WaveFunction	    (class WaveFunction* waveFunction);
    void set_InitialState	    (class InitialState* initalState);
    void set_Timer		    (class Timer* timer);
    void set_parameters		    (std::vector<double> parameters);
    
    int	    get_nDimensions		(){return my_nDimensions;}
    int     get_nParticles	    	(){return my_nParticles;}
    int	    get_nCycles			(){return my_nCycles;}
    //double  get_timeStep		(){return my_timeStep;}
    double  get_stepLength	    	(){return my_stepLength;}
    double  get_derivativeStep	    	(){return my_derivativeStep;}
    double  get_derivativeStep2	    	(){return my_derivativeStep2;}

    std::vector<double>& get_parameters	(){return my_parameters;}
    //std::ofstream get_oFile		(){return my_oFile;}


    class Hamiltonian*		  get_hamiltonian()	{return my_hamiltonian;}
    class WaveFunction*		  get_waveFunction()	{return my_waveFunction;}
    class Sampler*		  get_sampler()		{return	my_sampler;}
    class Timer*		  get_timer()		{return my_timer;}
    std::vector<class Particle*>&  get_particle()	{return my_particles;}

    void  add_particle (class Particle* particle); 
    
  protected:
    //std::ofstream my_oFile;
    int my_nDimensions		     = 0;
    int my_nParticles		     = 0;
    int my_nCycles		     = 0;
    //double my_timeStep		     = 0.0;
    double my_stepLength	     = 0.0;
    double my_derivativeStep	     = 0.0;
    double my_derivativeStep2	     = 0.0;
    double my_equilibrationFraction  = 0.0;
    
    //std::vector<double> oldPosition     = std::vector<double>();
    //std::vector<double> quantumForceOld = std::vector<double>();
    //std::vector<double> randomMove      = std::vector<double>();
    std::vector<double> my_parameters	= std::vector<double>();

    class Hamiltonian*	    my_hamiltonian	= nullptr;
    class WaveFunction*	    my_waveFunction   	= nullptr;
    class InitialState*	    my_initialState   	= nullptr;
    class Sampler*	    my_sampler	      	= nullptr;
    class Timer*	    my_timer		= nullptr;

    std::vector<class Particle*> my_particles = std::vector<class Particle*>();

    typedef std::chrono::high_resolution_clock clock;
    clock::time_point my_start = clock::now();
    std::uniform_real_distribution<double> my_uniform {std::uniform_real_distribution<double>(0.0,1.0)};
    std::normal_distribution<double> my_normal {std::normal_distribution<double>(0,1.0/sqrt(2))};
    std::default_random_engine my_generator;
};


