#include <stdlib.h>
#include "../System/System.h"
#include "../System/Particle.h"
#include "../Sampler/Sampler.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../WaveFunction/WaveFunction.h"
#include "../InitialState/InitialState.h"
#include "../Hamiltonian/HarmonicOscillator.h"
#include "../Hamiltonian/HarmonicOscillatorInteracting.h"
#include "../WaveFunction/TrialWaveFunction.h"
#include "../WaveFunction/TrialWaveFunctionInteracting.h"
#include "../InitialState/RandomUniform.h"

using std::cout;


void analytical(bool,int,int,int,double,double,std::vector<double>);
void metropolis(bool,bool,int,int,int,double,double,double,std::vector<double>);
void importanceSampling(bool,bool,int,int,int,double,double,double,std::vector<double>);
void interacting(bool,bool,int,int,int,double,double,double,double,std::vector<double>);

 
int main (int argc,char* argv[]){

  bool File;
  bool analytical;
  int  nDimensions;
  int  nParticles;
  if (argc == 5)
  {
    File	= atoi(argv[4]);
    analytical  = atoi(argv[3]);
    nDimensions = atoi(argv[1]);
    nParticles  = atoi(argv[2]);
  }
  else if (argc == 4)
  {
    File	      = false;
    analytical  = atoi(argv[3]);
    nDimensions = atoi(argv[1]);
    nParticles  = atoi(argv[2]);
  }
  else if (argc == 3)
  {
    File        = false;
    analytical  = true;
    nDimensions = atoi(argv[1]);
    nParticles  = atoi(argv[2]);
  }
  else 
  {
    cout << "Usage: ./program Ndim Npart (analytical writeToFile)\n";
    exit (EXIT_FAILURE);
  }
  int 	  nCycles	  = (int) 1e5;

  double  omega		  = 1.0;
  double  alpha		  = 0.5;
  double  gamma		  = 1.0;
  double  beta		  = 2.82843;
  double  bosonSize	  = 0.0043;
  double  stepLength	  = 0.005;
  double  equilibration	  = 0.1;
  double  derivativeStep  = 0.001;

  std::vector<double> parameters {alpha, omega, gamma, beta};

  int chosenOne = 2;

  switch (chosenOne)
  {
    case 0:
      metropolis(File,analytical,nCycles,nParticles,nDimensions,
		 stepLength,equilibration,derivativeStep,
		 parameters);
      break;

    case 1:
      importanceSampling(File,analytical,nCycles,nParticles,nDimensions,                   
			 stepLength,equilibration,derivativeStep,
			 parameters);
      break;

    case 2:
      parameters[2] = 2.82843;
      
      interacting(File,analytical,nCycles,nParticles,nDimensions,
		  stepLength,equilibration,derivativeStep,bosonSize,
		  parameters);
      break;
  }

  return 0;
}

void metropolis(bool File,
		bool analytical,
		int nCycles,
		int nParticles,
		int nDimensions,
		double stepLength,
		double equilibration,
		double derivativeStep,
		std::vector<double>parameters)
{
/* Brute forece Metropolis */

  cout << "Initializing brute force Metropolis system...\n";

  System* system = new System(File);
   
  system->set_parameters		(parameters);
  system->set_stepLength		(stepLength);
  system->set_equilibrationFraction	(equilibration);
  system->set_derivativeStep		(derivativeStep);
  system->set_nCycles                   (nCycles);
  system->set_analytical		(analytical);

  system->set_InitialState	(new RandomUniform	 (system, nDimensions, nParticles));
  system->set_Hamiltonian	(new HarmonicOscillator  (system));
  system->set_WaveFunction	(new TrialWaveFunction   (system));
  system->set_Timer		(new Timer               (system));
  
  cout << "Starting timer...\n";
  system->get_timer()->startTimer	();
  system->runMetropolis		();
  system->get_timer()->stopTimer	();
  cout << "----------------------------------\n";
  cout << "              Timers              \n";
  cout << "            Brute force           \n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",system->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",system->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",system->get_timer()->elapsedTimeMicro());
  cout << "----------------------------------\n\n\n";
}

void importanceSampling(bool File,
			bool analytical,
			int nCycles,
			int nParticles,
			int nDimensions,
			double stepLength,
			double equilibration,
			double derivativeStep,
			std::vector<double>parameters)
{
/* Importance Sampling */
  cout << "Initializing Importance Sampling system...\n";
  System* system = new System(File);

  system->set_parameters		(parameters);
  system->set_stepLength		(stepLength);
  system->set_equilibrationFraction	(equilibration);
  system->set_derivativeStep		(derivativeStep);
  system->set_nCycles			(nCycles);
  system->set_analytical		(analytical);

  system->set_InitialState	    (new RandomUniform		  (system, nDimensions, nParticles));
  system->set_Hamiltonian	    (new HarmonicOscillator       (system));
  system->set_WaveFunction	    (new TrialWaveFunction	  (system));
  system->set_Timer		    (new Timer			  (system));

  cout << "Starting timer...\n";
  
  system->get_timer()->startTimer  ();
  system->runImportanceSampling    ();
  system->get_timer()->stopTimer   ();
  cout << "----------------------------------\n";
  cout << "              Timers              \n";
  cout << "       Importance Sampling        \n";
  cout << "----------------------------------\n";

  printf("Seconds     : %i \n",system->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",system->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",system->get_timer()->elapsedTimeMicro());
}

void interacting(bool File,
		 bool analytical,
		 int nCycles,
	         int nParticles,
		 int nDimensions,
		 double stepLength,
		 double equilibration,
		 double derivativeStep,
		 double bosonSize,
		 std::vector<double>parameters)
{
/* Interacting */
  
  cout << "Initializing interacting harmonic oscillator...\n";

  System* system = new System(File);

  system->set_parameters		(parameters);
  system->set_stepLength		(stepLength);
  system->set_equilibrationFraction	(equilibration);
  system->set_derivativeStep		(derivativeStep);
  system->set_nCycles			(nCycles);
  system->set_analytical		(analytical);

  system->set_InitialState	    (new RandomUniform			(system, nDimensions, nParticles));
  system->set_Hamiltonian	    (new HarmonicOscillatorInteracting  (system, bosonSize));
  system->set_WaveFunction	    (new TrialWaveFunctionInteracting	(system, bosonSize));
  system->set_Timer		    (new Timer			  	(system));


  cout << "Starting timer...\n";
  
  system->get_timer()->startTimer  ();
  //system->runMetropolis		   ();
  system->runImportanceSampling	   ();
  system->get_timer()->stopTimer   ();
  cout << "----------------------------------\n";
  cout << "              Timers              \n";
  cout << "            Interacting           \n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",system->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",system->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",system->get_timer()->elapsedTimeMicro());
}  
