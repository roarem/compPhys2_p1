#include "TrialWaveFunction.h"

TrialWaveFunction::TrialWaveFunction (System* system,
				      double  alpha):
  WaveFunction(system){
    my_nParameters	    = 1;
    my_paramaters.reserve    (1);
    my_parameters.push_back  (alpha);
  }

double TrialWaveFunction::evaluate ()
{
  double wave	= 0;
  double r2	= 0;

  std::vector<double> position(system->my_nDimensions);

  for (int i = 0 ; i < system->my_nParticles ; i++){

       position = system->particles[i].get_position();

    for (int j = 0 ; j < system->my_nDimensions ; j++){

      r2 += system->my_particles[i].get_position()[j]*
	system->my_particles[i].get_position()[j]
    }
    wave -= my_parameters[0]*r2;
  }

  return exp(wave);
}

double TrialWaveFunction::computeEnergy ()
{
  double doubleDerivative     = 0;
  double waveFunctionPlus     = 0;
  double waveFunctionMinus    = 0;
  double potEnergy	      = 0;
  double kinEnergy	      = 0;
  double waveFunctionCurrent  = 0;
 
  waveFunctionCurrent = evaluate(particles);

  for (int i = 0 ; i < my_system->my_nParticles ; i++){
    for (int j = 0 ; j < my_system->my_nDimensions ; j++){

      system->mu_particles.changePosition(j, system->derivateStep);
      waveFunctionPlus = evaluate();

      system->my_particles.changePosition(j, -2*system->derivateStep);
      waveFunctionMinus = evaluate();

      system->my_particles.changePosition(j, -system->derivateStep);
     
      doubeDerivative += waveFunctionPlus + waveFunctionMinus - 2*waveFunctionCurrent;

      potEnergy += system->my_particle.get_position()[j]*
	system->my_particle.get_position()[j];
    }
  }

  kinEnergy = -0.5 / (waveFunctionCurrent * system->derivativeStep2);
  potEnergy = 0.5 * potEnergy;

  return kinEnergy + potEnergy;
}
