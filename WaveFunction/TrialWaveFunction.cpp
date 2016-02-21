#include "TrialWaveFunction.h"
#include <iostream>

using std::cout;
using std::endl;

TrialWaveFunction::TrialWaveFunction (System* system) :
  WaveFunction(system){
  }

double TrialWaveFunction::evaluate ()
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


double TrialWaveFunction::computeDoubleDerivative(int p, int d, double waveFunctionCurrent)
{
  double doubleDerivative     = 0;
  double waveFunctionPlus     = 0;
  double waveFunctionMinus    = 0;
 

  my_system->get_particle()[p]->changePosition(d, my_system->get_derivativeStep());
  waveFunctionPlus = evaluate();

  my_system->get_particle()[p]->changePosition(d, -2*my_system->get_derivativeStep());
  waveFunctionMinus = evaluate();

  my_system->get_particle()[p]->changePosition(d, my_system->get_derivativeStep());
  
  doubleDerivative += waveFunctionPlus + waveFunctionMinus - 2*waveFunctionCurrent;
  
  doubleDerivative = doubleDerivative/my_system->get_derivativeStep2();
  
  return doubleDerivative;
}

double TrialWaveFunction::computeDerivative(int p, int d, double waveFunctionCurrent)
{
  double derivative	    = 0;
  double waveFunctionPlus   = 0;

  my_system->get_particle()[p]->changePosition(d, my_system->get_derivativeStep());
  waveFunctionPlus = evaluate();

  my_system->get_particle()[p]->changePosition(d,-my_system->get_derivativeStep());

  derivative = (waveFunctionPlus - waveFunctionCurrent)/my_system->get_derivativeStep();

  return derivative;
}

double TrialWaveFunction::computeQuantumForce(int p, int d, double waveFunctionCurrent)
{
  double quantumForce	= 0;

  quantumForce = 2*computeDerivative(p,d,waveFunctionCurrent)/waveFunctionCurrent;

  return quantumForce;
}

