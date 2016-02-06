#include "TrialWaveFunction.h"

TrialWaveFunction::TrialWaveFunction (System* system,
				      double  alpha,
				      double  omega):
  WaveFunction(system){
    my_nParameters	      = 2;
    my_paramaters.reserve     (2);
    my_parameters.push_back   (alpha);
    my_parameters.push_back   (omega);
  }

double TrialWaveFunction::evaluate ()
{
  double wave	= 0;
  double r2	= 0;

  std::vector<double> position(my_system->my_nDimensions);

  for (int i = 0 ; i < my_system->my_nParticles ; i++){

       position = my_system->particles[i].get_position();

    for (int j = 0 ; j < my_system->my_nDimensions ; j++){

      r2 += my_system->my_particles[i].get_position()[j]*
	my_system->my_particles[i].get_position()[j]
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

      my_system->mu_particles.changePosition(j, my_system->derivateStep);
      waveFunctionPlus = evaluate();

      my_system->my_particles.changePosition(j, -2*my_system->derivateStep);
      waveFunctionMinus = evaluate();

      my_system->my_particles.changePosition(j, -my_system->derivateStep);
     
      doubeDerivative += waveFunctionPlus + waveFunctionMinus - 2*waveFunctionCurrent;

      potEnergy += my_system->my_particle.get_position()[j]*
	my_system->my_particle.get_position()[j];
    }
  }

  kinEnergy = -0.5 / (waveFunctionCurrent * my_system->derivativeStep2);
  potEnergy = 0.5 * potEnergy;

  return kinEnergy + potEnergy;
}



