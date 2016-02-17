#include "../System/System.h"
#include "../System/Sampler.h"
#include "../System/Particle.h"
#include "../System/Timer.h"
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

  int	  nDimensions     = 3;
  int 	  nParticles      = 2;
  int 	  nCycles	  = (int) 1e4;

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
  anaSystem->set_Timer		    (new Timer                    (anaSystem));
  
  cout << "Starting Metropolis Timer...\n";
  anaSystem->get_timer()->startTimer	();
  anaSystem->runMetropolis		(nCycles);
  anaSystem->get_timer()->stopTimer	();
  cout << "----------------------------------\n";
  cout << "Timers for the analytical solution\n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",anaSystem->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",anaSystem->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",anaSystem->get_timer()->elapsedTimeMicro());
  cout << "----------------------------------\n\n\n";
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
  numSystem->set_Timer		    (new Timer			  (numSystem));

  cout << "Starting Metropolis Timer...\n";
  
  numSystem->get_timer()->startTimer  ();
//  numSystem->runMetropolis	      (nCycles);
  numSystem->runImportanceSampling    (nCycles);
  numSystem->get_timer()->stopTimer   ();
  cout << "----------------------------------\n";
  cout << "Timers for the numerical solution\n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",numSystem->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",numSystem->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",numSystem->get_timer()->elapsedTimeMicro());
  cout << "Numerical run is complete!\n";

  return 0;
}

