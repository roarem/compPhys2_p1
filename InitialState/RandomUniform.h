#pragma once
#include "InitialState.h"
#include <chrono>
#include <random>
#include <vector>

class RandomUniform : public InitialState
{

  public:
    RandomUniform ( System* system,
		    int nDimensions, 
		    int nParticles);

    void setupInitialState ();

  protected:
  
    unsigned  seed;
    typedef   std::chrono::high_resolution_clock clock;
    clock::time_point my_start = clock::now();

};
