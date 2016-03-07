#include "../System/System.h"
#include "../System/Particle.h"
#include "../Sampler/Sampler.h"
#include "../Hamiltonian/Hamiltonian.h"
#include "../WaveFunction/WaveFunction.h"
#include "../InitialState/InitialState.h"
#include "../Hamiltonian/HarmonicOscillatorAna.h"
#include "../Hamiltonian/HarmonicOscillator.h"
#include "../Hamiltonian/HarmonicOscillatorInteracting.h"
#include "../WaveFunction/TrialWaveFunctionAna.h"
#include "../WaveFunction/TrialWaveFunction.h"
#include "../WaveFunction/TrialWaveFunctionInteracting.h"
#include "../InitialState/RandomUniform.h"

using std::cout;


void analytical(bool,int,int,int,double,double,std::vector<double>);
void metropolis(bool,int,int,int,double,double,double,std::vector<double>);
void importanceSampling(bool,int,int,int,double,double,double,std::vector<double>);
void interacting(bool,int,int,int,double,double,double,double,std::vector<double>);

 
int main (){

  bool	  File		  = true;

  int	  nDimensions     = 3;
  int 	  nParticles      = 100;
  int 	  nCycles	  = (int) 1e6;

  double  omega		  = 1.0;
  double  alpha		  = 0.5;
  double  gamma		  = 2.82843;
  //double  gamma		  = 1.0;
  double  beta		  = gamma;
  double  bosonSize	  = 0.0043;
  double  stepLength	  = 0.1;
  //double  timeStep	  = 0.01;
  double  equilibration	  = 0.1;
  double  derivativeStep  = 0.001;

  std::vector<double> parameters {alpha, omega, gamma, beta};

  int chosenOne = 5;

  switch (chosenOne)
  {
    case 0:
      analytical(File,nCycles,nParticles,nDimensions,
		 stepLength,equilibration,
		 parameters);
      break;

    case 1:
      metropolis(File,nCycles,nParticles,nDimensions,
		 stepLength,equilibration,derivativeStep,
		 parameters);
      break;
    case 2:
      importanceSampling(File,nCycles,nParticles,nDimensions,                   
			 stepLength,equilibration,derivativeStep,
			 parameters);
      break;

    case 3:
      metropolis(File,nCycles,nParticles,nDimensions,
		 stepLength,equilibration,derivativeStep,
		 parameters);

      importanceSampling(File,nCycles,nParticles,nDimensions,                   
			 stepLength,equilibration,derivativeStep,
			 parameters);
      break;

    case 4:
      metropolis(File,nCycles,nParticles,nDimensions,
		 stepLength,equilibration,derivativeStep,
		 parameters);
      interacting(File,nCycles,nParticles,nDimensions,
		  stepLength,equilibration,derivativeStep,bosonSize,
		  parameters);
      break;

    case 5:
      interacting(File,nCycles,nParticles,nDimensions,
		  stepLength,equilibration,derivativeStep,bosonSize,
		  parameters);
      break;
  }

  return 0;
}

void analytical(bool File,
		int nCycles,
		int nParticles,
		int nDimensions,
		double stepLength,
		double equilibration,
		std::vector<double>parameters)
{
  cout << "Initializing analytical Metropolis system...\n";

  System* system = new System(File);
   
  system->set_parameters		(parameters);
  system->set_stepLength		(stepLength);
  system->set_equilibrationFraction	(equilibration);
  system->set_nCycles			(nCycles);

  system->set_InitialState	(new RandomUniform	    (system, nDimensions, nParticles));
  system->set_Hamiltonian	(new HarmonicOscillatorAna  (system));
  system->set_WaveFunction	(new TrialWaveFunctionAna   (system));
  system->set_Timer		(new Timer		    (system));
  
  cout << "Starting timer...\n";
  system->get_timer()->startTimer	();
  system->runMetropolis		();
  system->get_timer()->stopTimer	();
  cout << "----------------------------------\n";
  cout << "              Timers              \n";
  cout << "             Analytical           \n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",system->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",system->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",system->get_timer()->elapsedTimeMicro());
  cout << "----------------------------------\n\n\n";
}

void metropolis(bool File,
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

  system->set_InitialState	    (new RandomUniform			(system, nDimensions, nParticles));
  system->set_Hamiltonian	    (new HarmonicOscillatorInteracting  (system, bosonSize));
  system->set_WaveFunction	    (new TrialWaveFunctionInteracting	(system, bosonSize));
  system->set_Timer		    (new Timer			  	(system));

  cout << "Starting timer...\n";
  
  system->get_timer()->startTimer  ();
  system->runMetropolis		   ();
  //system->runImportanceSampling	   ();
  system->get_timer()->stopTimer   ();
  cout << "----------------------------------\n";
  cout << "              Timers              \n";
  cout << "            Interacting           \n";
  cout << "----------------------------------\n";
  printf("Seconds     : %i \n",system->get_timer()->elapsedTimeSeconds());
  printf("Milliseconds: %i \n",system->get_timer()->elapsedTimeMilli());
  printf("Microseconds: %i \n",system->get_timer()->elapsedTimeMicro());
}  
