#pragma once
#include "../System/System.h"
#include "../System/Particle.h"
#include <vector>

class WaveFunction
{
  public:
  WaveFunction (class System* system);

    virtual double evaluate		      () = 0;
    virtual double computeDoubleDerivative    (int p, int d, double waveFunctionCurrent) = 0;
    virtual double computeDerivative	      (int p, int d, double waveFunctionCurrent) = 0;
    virtual double computeQuantumForce	      (int p, int d, double waveFunctionCurrent) = 0;
    virtual double computeEnergy	      () = 0;
    //int get_nParameters () {return my_nParameters;}

    //std::vector<double> get_parameters() {return my_parameters;}

  protected:
    
    //std::vector<double> my_parameters = std::vector<double>();
    class System* my_system = nullptr;

};
