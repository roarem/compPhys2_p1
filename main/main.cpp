#include "../System/System.h"
#include "../System/Sampler.h"
#include "../System/Particle.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../Hamiltonian/HarmonicOscillatorAna.h"
#include "../Hamiltonian/HarmonicOscillator.h"
#include "../WaveFunction/WaveFunction.h"
#include "../WaveFunction/TrialWaveFunctionAna.h"
#include "../WaveFunction/TrialWaveFunction.h"
#include "../InitialState/InitialState.h"
#include "../InitialState/RandomUniform.h"
#include <iostream>

using std::cout;

int main (){

  int	  nDimensions     = 1;
  int 	  nParticles      = 5;
  int 	  nCycles	  = (int) 1e3;

  double  omega		  = 1.0;
  double  alpha		  = omega/2.0;
  double  stepLength	  = 1.0;
  double  equilibration	  = 0.1;
  double  derivativeStep  = 0.001;

/* Analytical */
  cout << "Initializing analytical system...\n";

  System* anaSystem = new System();

  anaSystem->set_stepLength		(stepLength);
  anaSystem->set_equilibrationFraction	(equilibration);
  anaSystem->set_derivativeStep		(derivativeStep);

  anaSystem->set_InitialState	    (new RandomUniform		  (anaSystem, nDimensions, nParticles));
  anaSystem->set_Hamiltonian	    (new HarmonicOscillatorAna    (anaSystem, omega));
  anaSystem->set_WaveFunction	    (new TrialWaveFunctionAna     (anaSystem, alpha, omega));
  
  cout << "Starting Metropolis...\n";
  anaSystem->runMetropolis		    (nCycles);
  cout << "Analytical run is complete!\n\n\n";
////////////////////////////////////////////////////////////////////////////////////////////////////


/* Numerical derivation */
  cout << "Initializing numerical system...\n";
  System* numSystem = new System();

  numSystem->set_stepLength		(stepLength);
  numSystem->set_equilibrationFraction	(equilibration);
  numSystem->set_derivativeStep		(derivativeStep);

  numSystem->set_InitialState	    (new RandomUniform		  (numSystem, nDimensions, nParticles));
  numSystem->set_Hamiltonian	    (new HarmonicOscillator       (numSystem, omega));
  numSystem->set_WaveFunction	    (new TrialWaveFunction	  (numSystem, alpha, omega));

  cout << "Starting Metropolis...\n";
  numSystem->runMetropolis		    (nCycles);
  cout << "Numerical run is complete!\n";
  return 0;

}

