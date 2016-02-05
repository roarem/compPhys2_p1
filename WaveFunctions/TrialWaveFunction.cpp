#include "TrialWaveFunction.h"

TrialWaveFunction::TrialWaveFunction (System* system,
				      double  alpha):
  WaveFunction(system){
    my_nParameters	    = 1;
    my_paramaters.reserve    (1);
    my_parameters.push_back  (alpha);
  }

double TrialWaveFunction::evaluate (std::vector<class Particle*> particles)
{
  double wave	= 0;
  double r	= 0;

  std::vector<double> position(my_system->my_nDimensions);

  for (int i = 0 ; i < my_system->my_nParticles ; i++){
       position = particles[i].get_position();
    for (int j = 0 ; j < my_system->my_nDimensions ; j++){
      r += position(j)*position(j);
    }
    wave -= my_parameters[0]*r;
  }

  return exp(wave);
}

double TrialWaveFunction::secondDerivative (std::vector<class Particle*> particles)
{
  double kinEnergy	      = 0;
  double potEnergy	      = 0;
  double waveFunctionPlus     = 0;
  double waveFunctionMinus    = 0;
  double waveFunctionCurrent  = 0;

  std::vector<double> rPlus	(my_system->nDimensions);
  std::vector<double> rminus	(my_system->nDimensions);
 
  waveFunctionCurrent = evaluate(particles);

  for (int i = 0 ; i < my_system->my_nParticles ; i++){
    for (int j = 0 ; j < my_system->my_nDimensions ; j++){
    }
  }
  return 0;
}
