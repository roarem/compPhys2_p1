#include "VMCSolver.h"

VMCSolver::VMCSolver() : uniform(0.0,1.0)
{
  typedef chrono::high_resolution_clock klokka;
  klokka::time_point start = klokka::now();
  default_random_engine generator;
  //uniform_real_distribution<double> uniform(0.0,1.0);

   nDimensions	     = 1;
   nParticles  	     = 2;
   nCycles     	     = 1000000;
   alpha      	     = 1;
   beta	      	     = 1;
   stepLength  	     = 1.0;
   h		     = 0.001;
   deltaE      	     = 0;
   energySum	     = 0;
   energySumSquared  = 0;

  klokka::duration d = klokka::now() - start;
  seed = d.count();
  generator.seed(seed);
}

void VMCSolver::MonteCarloIntegration()
{
  double energySquared	= 0;
  double energy		= 0;
  double waveCompared	= 0;
  deltaE	      	= 0;
  energySumSquared    	= 0;
  energySum	      	= 0; 

  rOld = zeros<mat>(nParticles, nDimensions);
  rNew = zeros<mat>(nParticles, nDimensions);

  //Makes random placement in positions
  for (int i = 0 ; i < nParticles ; i++){
    for (int j = 0 ; j < nDimensions; j++){
      rOld(i,j) = stepLength * (uniform(generator) - 0.5);
    }
  }
  rNew = rOld;

  for (int cycle = 0 ; cycle < nCycles ; cycle++){
    waveFunctionOld = waveFunction(rOld);
    
    for (int i = 0 ; i < nParticles ; i++){
      for (int j = 0 ; j < nDimensions ; j++){
	rNew(i,j) = rOld(i,j) + stepLength * (uniform(generator) - 0.5);
	}
      waveFunctionNew = waveFunction(rNew);
      waveCompared = (waveFunctionNew*waveFunctionNew)/(waveFunctionOld*waveFunctionOld);
      if (uniform(generator) <= waveCompared){
	for (int j = 0 ; j < nDimensions ; j++){
	  rOld(i,j) = rNew(i,j);
	  waveFunctionOld = waveFunctionNew;
	}
      }
      else{
	for (int j = 0 ; j < nDimensions ; j++){
	  rNew(i,j) = rOld(i,j);
	}
      }
      deltaE = localEnergy(rNew);
      energySum += deltaE;
      energySumSquared += deltaE*deltaE;
    }
  }
  energy = energySum/(nCycles * nParticles);
  energySquared = energySumSquared/(nCycles*nParticles);
  cout << "Energy: " << energy << " Energy^2: " << energySquared << endl;
}

double VMCSolver::waveFunction (const mat &r)
{
  double return_value = 0;
  double particle     = 0;
  for (int i=0 ; i<nParticles ; i++){ 
    for (int j=0 ; j<nDimensions ; j++){
      particle += r(i,j)*r(i,j);
    }
    return_value += exp(-alpha*particle);
  }
  return return_value;
}

double VMCSolver::localEnergy (const mat &r)
{
  mat rPlus		    = zeros<mat>(nParticles, nDimensions);
  mat rMinus		    = zeros<mat>(nParticles, nDimensions);
  double waveFunctionMinus  = 0;
  double waveFunctionPlus   = 0;
  double waveFunctionCurrent= waveFunction (r);
  double kineticEnergy	    = 0; 
  //double potentialEnergy    = 0;
  rPlus = rMinus = r;

  for (int i = 0 ; i < nParticles ; i++){
    for (int j = 0 ; j < nDimensions ; j++){
      rPlus(i,j) += h;
      rMinus(i,j) -= h;

      waveFunctionPlus = waveFunction (rPlus);
      waveFunctionMinus = waveFunction (rMinus);
      
      kineticEnergy -= (waveFunctionPlus + waveFunctionMinus - 2*waveFunctionCurrent);

      rPlus(i,j) = r(i,j);
      rMinus(i,j) = r(i,j);
    }
  }
  kineticEnergy = 0.5 * h * kineticEnergy / waveFunctionCurrent;

  return kineticEnergy;
}

























  









