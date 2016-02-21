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
  int 	  nParticles      = 5;
  int 	  nCycles	  = (int) 2e3;

  double  omega		  = 1.0;
  double  alpha		  = omega/2.0;
  double  stepLength	  = 0.5;
  double  equilibration	  = 0.1;
  double  derivativeStep  = 0.0001;

/* Brute forece Metropolis */
  cout << "Initializing brute force Metropolis system...\n";

  System* metSystem = new System();

  metSystem->set_stepLength		(stepLength);
  metSystem->set_equilibrationFraction	(equilibration);
  metSystem->set_derivativeStep		(derivativeStep);
  metSystem->set_nCycles		(nCycles);

  metSystem->set_InitialState	    (new RandomUniform		  (metSystem, nDimensions, nParticles));
  metSystem->set_Hamiltonian	    (new HarmonicOscillator       (metSystem, omega));
  metSystem->set_WaveFunction	    (new TrialWaveFunction        (metSystem, alpha, omega));
  metSystem->set_Timer		    (new Timer                    (metSystem));
  
  cout << "Starting brute force timer...\n";
  metSystem->get_timer()->startTimer	();
  metSystem->runMetropolis		();
  metSystem->get_timer()->stopTimer	();
  cout << "----------------------------------\n";
  cout << "Timers for the brute force method \n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",metSystem->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",metSystem->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",metSystem->get_timer()->elapsedTimeMicro());
  cout << "----------------------------------\n\n\n";
////////////////////////////////////////////////////////////////////////////////////////////////////


/* Importance Sampling */
  cout << "Initializing Importance Sampling system...\n";
  System* impSystem = new System();

  impSystem->set_stepLength		(stepLength);
  impSystem->set_equilibrationFraction	(equilibration);
  impSystem->set_derivativeStep		(derivativeStep);
  impSystem->set_nCycles		(nCycles);

  impSystem->set_InitialState	    (new RandomUniform		  (impSystem, nDimensions, nParticles));
  impSystem->set_Hamiltonian	    (new HarmonicOscillator       (impSystem, omega));
  impSystem->set_WaveFunction	    (new TrialWaveFunction	  (impSystem, alpha, omega));
  impSystem->set_Timer		    (new Timer			  (impSystem));

  cout << "Starting Importance Sampint timer...\n";
  
  impSystem->get_timer()->startTimer  ();
  impSystem->runImportanceSampling    ();
  impSystem->get_timer()->stopTimer   ();
  cout << "----------------------------------\n";
  cout << "Timers for the Importance Sampling\n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",impSystem->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",impSystem->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",impSystem->get_timer()->elapsedTimeMicro());

  return 0;
}

