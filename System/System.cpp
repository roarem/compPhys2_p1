#include "System.h"



bool System::metropolis ()
{
  bool	    accepted		  = false;
  unsigned  seed;
  int	    chosenParticle	  = 0;
  int	    chosenDimension	  = 0;
  double    waveFunctionOld	  = 0;
  double    waveFunctionNew	  = 0;
  double    waveFunctionsCompared = 0;
  double    randomMove		  = 0;
 
  std::uniform_int_distribution<int> particle  (0,my_nParticles-1);
  std::uniform_int_distribution<int> dimension (0,my_nDimensons-1);

  clock::duration d = clock.now() - start;
  seed = d.count();
  my_generator.seed(seed);
  
  randomMove	  = my_stepLength*(my_uniform(my_generator)-0.5);
  chosenParticle  = particle(my_generator);
  chosenDimension = dimension(my_generator);

  waveFunctionOld = my_waveFunction->evaluate(); 

  my_particles[chosenParticle].changePosition(chosenDimension, randomMove);

  waveFunctionNew = my_waveFunction->evaluate();

  waveFunctionsCompared = (waveFunctionNew*waveFunctionNew)/
		         (waveFunctionOld*waveFunctionOld);
  
  if (waveFunctionsCompared < 1.0){
    if (waveFunctionsCompared < my_uniform(my_generator)){
      my_particles[chosenParticle].changePosition(chosenDimension, -randomMove);
      return false;
    }
  }
  return true;
}


void System::runMetropolis (int nCycles)
{
  bool accepted = false;

  for (int cycle = 0 ; cycle < my_nCycles ; cycle++){
    accepted = metropolis();
    
    if (cycle > equilibrationFraction * my_nCycles)
    {
      my_sampler->sample(accepted);
    }
  }

  return 0;
}

void System::set_nDimensions (int nDimensions)
{
  my_nDimensions = nDimensions;
}

void System::set_nParticles (int nParticles)
{
  my_nParticles = nParticles;
}

void System::set_nCycles (int nCycles)
{
  my_nCycles = nCycles;
}

void System::set_stepLength (double stepLength)
{
  my_stepLength = stepLength;
}

void System::set_derivativeStep (double h);
{
  my_derivativeStep = h;
}

void System::set_equilibrationFraction (double equilibraFraction)
{
  my_euilibraFraction = equilibraFraction;
}

void System::set_Hamiltonian (Hamiltonian* hamiltonian)
{
  my_hamiltonian = hamiltonian;
}

void System::set_WaveFunction (WaveFunction* waveFunction)
{
  my_waveFunction = waveFunction;
}

void System::set_InitialState (InitialState* initialState)
{
  my_initialState = initialState;
}


