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


switch (nDimensions) {

  case 1:
    double wFuncCall (rowvec &pos) {return exp(-alpha*pos(0)*pos(0));}
  case 2:
    double wFuncCall (rowvec &pos) {return exp(-alpha*(pos(0)*pos(0) + pos(1)*pos(1)));}
  case 3:
    double wFuncCall (rowvec &pos) {return exp(-alpha*(pos(0)*pos(0) + pos(1)*pos(1) + beta*pos(2)*pos(2)));}
}

double waveFunction (const mat &r)
{
  double return_value = 0;
  
  for (int i = 0 ; i < nParticles ; i++){
    return_value += wFuncCall (r.row(i));
    //return_value += exp(-alpha*(r(i,0)*r(i,0) + r(i,1)*r(i,1) + 


int main (){


  return 0;

}
