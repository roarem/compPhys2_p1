#include "TrialWaveFunctionAna.h"
#include <iostream>

using std::cout;
using std::endl;

TrialWaveFunctionAna::TrialWaveFunctionAna (System* system,
				      double  alpha,
				      double  omega):
  WaveFunction(system){
    my_nParameters = 2;

    std::vector<double> parameters(my_nParameters);
    parameters[0] = alpha;
    parameters[1] = omega;
    my_system->set_parameters(parameters);
  }

double TrialWaveFunctionAna::evaluate ()
{
  double wave	= 0;
  double r2	= 0;

  for (int i = 0 ; i < my_system->get_nParticles() ; i++){
    for (int j = 0 ; j < my_system->get_nDimensions() ; j++){

      r2 += my_system->get_particle()[i]->get_position()[j]*
	    my_system->get_particle()[i]->get_position()[j];
    }
  }
  wave -= my_system->get_parameters()[0]*r2;

  return exp(wave);
}

double TrialWaveFunctionAna::computeEnergy()
{
  double kinEnergy	= 0;
  double potEnergy	= 0;
  double r2		= 0;
  
  for (int i = 0 ; i < my_system->get_nParticles() ; i++){
    for (int j = 0 ; j < my_system->get_nDimensions() ; j++){
      
      r2 =  my_system->get_particle()[i]->get_position()[j]*
	    my_system->get_particle()[i]->get_position()[j];
      }
      kinEnergy -= (2*my_system->get_parameters()[0]*r2 - my_system->get_nDimensions());
      potEnergy += r2;
      //cout << my_system->get_particle()[i]->get_position()[0] << endl;
  }

  kinEnergy = kinEnergy *my_system->get_parameters()[0];
  potEnergy = my_system->get_parameters()[1] *my_system->get_parameters()[1] * potEnergy * 0.5;
  //cout << "potential energy = " << potEnergy << ", kinetic energy = " << kinEnergy << endl;
  return kinEnergy + potEnergy;
}

