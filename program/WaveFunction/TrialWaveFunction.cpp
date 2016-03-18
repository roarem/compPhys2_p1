#include "TrialWaveFunction.h"

using std::cout;
using std::endl;

TrialWaveFunction::TrialWaveFunction (System* system) :
  WaveFunction(system){
  }

double TrialWaveFunction::evaluate ()
{
  double r2	= 0;

  const double alpha = my_system->get_parameters()[0];

  for (int p = 0 ; p < my_system->get_nParticles() ; p++){
    for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
      const double x = my_system->get_particle()[p]->get_position()[d];
      r2 += x*x;
    }
  }
  return exp(-alpha*r2);
}

/*
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
cout << doubleDerivative << endl;
  return doubleDerivative;
}
*/
double TrialWaveFunction::computeDerivative(int p, int d, double waveFunctionCurrent)
{
  double derivative	    = 0;
  double waveFunctionPlus   = 0;

  my_system->get_particle()[p]->changePosition(d, my_system->get_derivativeStep());
  waveFunctionPlus = evaluate();

  my_system->get_particle()[p]->changePosition(d,-my_system->get_derivativeStep());
  //cout << waveFunctionPlus - waveFunctionCurrent << "   ";
  derivative = (waveFunctionPlus - waveFunctionCurrent)/my_system->get_derivativeStep();

  return derivative;
}

double TrialWaveFunction::computeQuantumForce(int p, int d, double waveFunctionCurrent)
{
  double quantumForce	= 0;
  quantumForce = 2*computeDerivative(p,d,waveFunctionCurrent)/waveFunctionCurrent;
  
  return quantumForce;
}

