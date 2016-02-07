#include "../System/System.h"
#include "../System/Sampler.h"
#include "../System/Particle.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../Hamiltonian/HarmonicOscillatorAna.h"
#include "../WaveFunction/WaveFunction.h"
#include "../WaveFunction/TrialWaveFunctionAna.h"
#include "../InitialState/InitialState.h"
#include "../InitialState/RandomUniform.h"
#include <iostream>

int main (){

  int	  nDimensions     = 1;
  int 	  nParticles      = 2;
  int 	  nCycles	  = (int) 1e6;

  double  omega		  = 1.0;
  double  alpha		  = 0.5;
  double  stepLength	  = 1.0;
  double  equilibration	  = 0.1;
  //double  derivativeStep  = 0.001;

  System* system = new System();

  system->set_Hamiltonian	  (new HarmonicOscillatorAna    (system, omega));
  system->set_WaveFunction	  (new TrialWaveFunctionAna     (system, alpha, omega));
  system->set_InitialState	  (new RandomUniform		(system, nDimensions, nParticles));
  system->set_equilibrationFraction (equilibration);
  system->set_stepLength	  (stepLength);
  //system->set_derivativeStep	  (derivativeStep);
 
  return 0;

}

