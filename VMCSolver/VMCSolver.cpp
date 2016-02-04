#include "VMCSolver.h"

VMCSolver::VMCSolver() : uniform(0.0,1.0)
{
   accepted	= 0;
   nDimensions	= 3;
   nParticles  	= 10;
   nCycles     	= 1e5;
   omega	= 1;
   alpha      	= 0.5*omega;
   beta	      	= 1;
   stepLength  	= 1.0;
   h		= 0.001;
   h2		= h*h;
}

void VMCSolver::MonteCarloIntegration()
{
  double energySquared	  = 0;
  double energy		  = 0;
  double waveCompared	  = 0;
  double deltaE	      	  = 0;
  double energySumSquared = 0;
  double energySum	  = 0; 


  rOld = zeros<mat>(nParticles, nDimensions);
  rNew = zeros<mat>(nParticles, nDimensions);

  klokka::duration d = klokka::now() - start;
  seed = d.count();
  generator.seed(seed);

  //Makes random placement in positions
  for (int i = 0 ; i < nParticles ; i++){
    for (int j = 0 ; j < nDimensions; j++){
      rOld(i,j) = stepLength * (uniform(generator) - 0.5);
    }
  }
  rNew = rOld;

  waveFunctionOld = waveFunction(rOld);
  for (int cycle = 0 ; cycle < nCycles ; cycle++){

    if (cycle%(10000) == 0){cout << "cycle #: " << cycle << endl;}

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
	accepted += 1;
      }
      else{
	for (int j = 0 ; j < nDimensions ; j++){
	  rNew(i,j) = rOld(i,j);
	}
      }

      deltaE = localEnergyNumerical(rNew);
      //deltaE = localEnergyAnalytical(rNew);
      energySum += deltaE;
      energySumSquared += deltaE*deltaE;
    }
  }
  energy = energySum/(nCycles*nParticles);
  energySquared = energySumSquared/(nCycles*nParticles);
  
  cout << "Mean(Energy) = " << (energy) << " Mean(Energy^2) = " << energySquared << endl;
  cout << "Mean(Energy)^2 - Mean(Energy^2) = " << energySquared- (energy*energy)<< endl;
  cout << "Accepted ratio: " << accepted/(nParticles*nCycles) << endl;
}

double VMCSolver::waveFunction (const mat &r)
{
  double wave	    = 0;
  double particle   = 0;

  for (int i=0 ; i<nParticles ; i++){ 
    particle = 0;

    for (int j=0 ; j<nDimensions ; j++){
      particle += r(i,j)*r(i,j);
    }
    wave += (-alpha*particle);
  }
  return exp(wave);
}

double VMCSolver::localEnergyNumerical (const mat &r)
{
  mat rPlus		    = zeros<mat>(nParticles, nDimensions);
  mat rMinus		    = zeros<mat>(nParticles, nDimensions);
  double waveFunctionMinus  = 0;
  double waveFunctionPlus   = 0;
  double waveFunctionCurrent= waveFunction (r);
  double kinEnergy	    = 0; 
  double potEnergy	    = 0;
  rPlus = rMinus = r;

  for (int i = 0 ; i < nParticles ; i++){
    for (int j = 0 ; j < nDimensions ; j++){

      rPlus(i,j) += h;
      rMinus(i,j) -= h;

      waveFunctionPlus = waveFunction (rPlus);
      waveFunctionMinus = waveFunction (rMinus);
      
      kinEnergy -= (waveFunctionPlus + waveFunctionMinus - 2*waveFunctionCurrent);

      rPlus(i,j) = r(i,j);
      rMinus(i,j) = r(i,j);

      potEnergy += r(i,j)*r(i,j);    
    }
  }

  kinEnergy = 0.5 * kinEnergy / (h2 * waveFunctionCurrent);
  potEnergy = 0.5 * potEnergy;

  return kinEnergy + potEnergy;
}

double VMCSolver::localEnergyAnalytical (const mat &r)
{
  double kinEnergy	= 0;
  double potEnergy	= 0;
  double particle	= 0;

  for (int i = 0 ; i < nParticles ; i++){
    particle = 0;
    for (int j = 0 ; j < nDimensions ; j++){
      particle += r(i,j)*r(i,j);
    }
    kinEnergy -= (2*alpha*particle - nDimensions);
    potEnergy += particle;  
  }

  kinEnergy	= kinEnergy*alpha;
  potEnergy	= omega * omega * potEnergy * 0.5;

  return kinEnergy + potEnergy;
}























  









