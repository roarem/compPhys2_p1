#include "TrialWaveFunctionInteracting.h"

using std::cout;
using std::endl;

TrialWaveFunctionInteracting::TrialWaveFunctionInteracting (System* system,double  bosonSize) :
  TrialWaveFunction(system){
    my_bosonSize = bosonSize;
  }

double TrialWaveFunctionInteracting::evaluate ()
{
  double r2		     = 0;
  double r	     	     = 0;
  double seperation 	     = 0;
  double correlationFunction = 0;
  const double alpha = my_system->get_parameters()[0];

  for (int p1 = 0 ; p1 < my_system->get_nParticles()-1 ; p1++){
    for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
      const double x = my_system->get_particle()[p1]->get_position()[d];
      r2 += x*x;
    }

    for (int p2 =  p1 + 1; p2 < my_system->get_nParticles() ; p2++){
      r = 0;
      for (int d = 0 ; d < my_system->get_nDimensions() ; d++){
	seperation = my_system->get_particle()[p1]->get_position()[d] -
		     my_system->get_particle()[p2]->get_position()[d];
	r += seperation*seperation;
      }
      correlationFunction = (r > my_bosonSize) * (1 -my_bosonSize/r);
    }
  }

  return exp(-alpha*r2) * correlationFunction;
}

/*
double TrialWaveFunctionInteracting::computeDoubleDerivative(int p, int d, double waveFunctionCurrent)
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

double TrialWaveFunctionInteracting::computeDerivative(int p, int d, double waveFunctionCurrent)
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

double TrialWaveFunctionInteracting::computeQuantumForce(int p, int d, double waveFunctionCurrent)
{
  double quantumForce	= 0;
  quantumForce = 2*computeDerivative(p,d,waveFunctionCurrent)/waveFunctionCurrent;
  
  return quantumForce;
}
*/
