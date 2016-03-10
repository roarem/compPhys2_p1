#include "Sampler.h"

using std::cout;
using std::endl;

Sampler::Sampler(System* system, bool File){
  my_system	= system;
  my_stepNumber = 0;
  if (File)
    my_oFile.open("energies.out", std::ios::out | std::ios::binary);
}

void Sampler::sample (bool accepted)
{
  if (my_stepNumber == 0)
  {
    cumulativeEnergy	      = 0;
    cumulativeEnergy2	      = 0;
    cumulativeAcceptanceRate  = 0;
  }

  double localEnergy = my_system->get_hamiltonian()->computeLocalEnergy();

  if (my_oFile.is_open())
  {
    my_oFile.write(reinterpret_cast<char *>(&localEnergy),sizeof(double));
  }
  else
  {
    cumulativeEnergy	    += localEnergy;
    cumulativeEnergy2	    += localEnergy*localEnergy;
    cumulativeAcceptanceRate  += accepted;
    my_stepNumber		    += 1;
  }
} 

void Sampler::printResults ()
{
  if (my_oFile.is_open()){
    my_oFile.close();
  }
  else
  {
    int	 nParticles	       = my_system->get_nParticles();
    int	 nDimensions	       = my_system->get_nDimensions(); 
    double nCycles	       = my_system->get_nCycles();
    double alpha	       = my_system->get_parameters()[0];
    double omega	       = my_system->get_parameters()[1];
    double gamma	       = my_system->get_parameters()[2];
//    double timeStep	       = my_system->get_timeStep();
    double stepLength	       = my_system->get_stepLength();
    double derivativeStep      = my_system->get_derivativeStep();
    double expectationValue    = cumulativeEnergy/(double)my_stepNumber;
    double expectationValue2   = cumulativeEnergy2/(double)my_stepNumber;
    double variance	       = (expectationValue2 - expectationValue * expectationValue);
    double acceptanceRatio     = cumulativeAcceptanceRate/(double)my_stepNumber;

    printf("\n");
    printf("\033[1;44m====================  System Data ====================\033[1;m\n");
    printf("\033[0;93mNumber of particles:     %i\033[0;m\n",nParticles);
    printf("\033[0;93mNumber of dimensions:    %i\033[0;m\n",nDimensions);
    printf("\033[0;93mNumber of cycles:        %0.1e\033[0;m\n",nCycles);
    printf("\033[0;93mAlpha:                   %f\033[0;m\n",alpha);
    printf("\033[0;93mOmega:                   %f\033[0;m\n",omega);
    printf("\033[0;93mGamma:                   %f\033[0;m\n",gamma);
    printf("\033[0;93mStep length:             %f\033[0;m\n",stepLength);
    printf("\033[0;93mNumber of steps:	       %i\033[0;m\n",my_stepNumber);
//    printf("\033[0;93mTime step:               %f\033[0;m\n",timeStep);
    printf("\033[0;93mDerivative step:         %f\033[0;m\n",derivativeStep);
    printf("\033[1;105m~~~~~~~~~~~~~~~~~~~~~ Results ~~~~~~~~~~~~~~~~~~~~~~~~\033[1;m\n");
    printf("\033[0;91mExpectation Value:       %e\033[0;m\n",expectationValue);
    printf("\033[0;91mVariance:                %e\033[0;m\n",variance);
    printf("\033[0;91mAcceptance ratio:        %f\033[0;m\n",acceptanceRatio);
  }
}
