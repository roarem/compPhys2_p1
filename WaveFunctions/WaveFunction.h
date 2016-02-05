#pragma once
#include "../System/Particle.h"
#include <vector>

class WaveFunction
{
  public:
    WaveFunction (class System* system);

    virtual double evaluate	    (std::vector<class Particle*> particles) = 0;
    virtual double secondDerivative (std::vector<class Particle*> particles) = 0;

    int get_nParameters () {return my_nParameters;}

    std::vector<double> get_parameters() {return my_parameters;}

  protected:
    
    int	my_nParameters	= 0;
    std::vector<double> my_paramters = std::vector<double>();
    class System* my_system = nullptr;

};
