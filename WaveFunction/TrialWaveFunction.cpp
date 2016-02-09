#include "TrialWaveFunction.h"
#include <iostream>

using std::cout;
using std::endl;

TrialWaveFunction::TrialWaveFunction (System* system,
				      double  alpha,
				      double  omega):
  WaveFunction(system){
    my_nParameters = 2;
    
    std::vector<double> parameters(my_nParameters);
    parameters[0] = alpha;
    parameters[0] = omega;
    my_system->set_parameters(parameters);
  }

double TrialWaveFunction::evaluate ()
{
  double wave	= 0;
  double r2	= 0;

  std::vector<double> position(my_system->get_nDimensions());

  for (int i = 0 ; i < my_system->get_nParticles() ; i++){
    for (int j = 0 ; j < my_system->get_nDimensions() ; j++){

      r2 += my_system->get_particle()[i]->get_position()[j]*
	my_system->get_particle()[i]->get_position()[j];
    }
    wave -= my_system->get_parameters()[0]*r2;
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
 
  waveFunctionCurrent = evaluate();

  for (int i = 0 ; i < my_system->get_nParticles() ; i++){
    for (int j = 0 ; j < my_system->get_nDimensions() ; j++){

      my_system->get_particle()[i]->changePosition(j, my_system->get_derivativeStep());
      waveFunctionPlus = evaluate();

      my_system->get_particle()[i]->changePosition(j, -2*my_system->get_derivativeStep());
      waveFunctionMinus = evaluate();

      my_system->get_particle()[i]->changePosition(j, my_system->get_derivativeStep());
     
      doubleDerivative += waveFunctionPlus + waveFunctionMinus - 2*waveFunctionCurrent;

      potEnergy += my_system->get_particle()[i]->get_position()[j]*
	my_system->get_particle()[i]->get_position()[j];
    }
  }
  
  kinEnergy = -0.5 * doubleDerivative / (waveFunctionCurrent * my_system->get_derivativeStep2());
  potEnergy = 0.5 * potEnergy * my_system->get_parameters()[1] * my_system->get_parameters()[1];
  return kinEnergy + potEnergy;
}



