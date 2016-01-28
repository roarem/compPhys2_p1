#include <armadillo>
#include <random>

using namespace std;
using namespace arma;

default_random_engine generator;
uniform_real_distribution<double> uniform(0.0,1.0);

void MonteCarloIntegration()
{

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
	for (int j = 0 : j < nDimensions ; j++){
	  rNew(i,j) = rOld(i,j);
	}
      }
      deltaE = localEnergy(rNew);
      energySum += deltaE;
      energySquaredSum += deltaE*deltaE;
    }
  }
  double energy = energySum/(nCycles * nParticles);
  double energySquared = energySquaredSum/(nCycles*nParticles);
  cout << "Energy: " << energy << " Energy^2: " << energySquared << endl;
}




int main (){


  return 0;

}
