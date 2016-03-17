#include "HarmonicOscillatorInteracting.h"

HarmonicOscillatorInteracting::HarmonicOscillatorInteracting(System* system, 
							     double bosonSize):
  HarmonicOscillator(system)
{
  my_bosonSize = bosonSize;
  my_bosonSize2 = bosonSize*bosonSize;
}

double HarmonicOscillatorInteracting::computeLocalEnergy ()
{
  double r		      =   0;
  double vInt		      =	  0;

  double vExt = HarmonicOscillator::computeLocalEnergy();

  for (int p1 = 0 ; p1 < my_system->get_nParticles()-1 ; p1++){
    for (int p2 = p1 + 1 ; p2 < my_system->get_nParticles() ; p2++){
      r = 0;
      for (int d = 0 ; d < my_system->get_nDimensions() ; d++){

	 const double seperation = my_system->get_particle()[p1]->get_position()[d] -
				   my_system->get_particle()[p2]->get_position()[d];

	 r += seperation*seperation;
      }
      r = sqrt(r);
      if (r < my_bosonSize2){
	vInt += 1e10;
      }
      //cout << vInt << endl;
    }
  }
  return vInt + vExt;
}
     
double HarmonicOscillatorInteracting::correlationFunction ()
{
  
  int nP    = my_system->get_nParticles();
  int nD    = my_system->get_nDimensions();
  
  const double alpha  = my_system->get_parameters()[0];
  const double beta   = my_system->get_parameters()[3];
  const double alpha2 = alpha*alpha;
  const double abterm = 4*alpha - 2*alpha*beta;
  const double boson  = my_bosonSize;
  const double boson2 =	my_bosonSize2;

  for (int p1 = 0 ; p1 < nP-1 ; p1++){
    
    for (int p2 = p1 + 1 ; p2 < nP ; p2++){
      const double rij	= 0;
      const double x1 = my_system->get_particle()[p1]->get_postition()[0];
      const double x2 = my_system->get_particle()[p1]->get_postition()[0];
      const double y1 = my_system->get_particle()[p1]->get_postition()[1];
      const double y2 = my_system->get_particle()[p1]->get_postition()[1];
      const double z1 = my_system->get_particle()[p1]->get_postition()[2];
      const double z2 = my_system->get_particle()[p1]->get_postition()[2];
      const double sep  = (x1-x2+ y1-y2 +z1-z2)*(x1-x2+ y1-y2 +z1-z2);

      rij = sqrt(sep);

      const double Deriv       = -2*alpha*(2*x1+2*y1+beta*z1)
      const double doubleDeriv = 4*alpha2*(x1*x1 + y1*y1 + beta*beta*z1*z1)-
				 abterm;
      const double u_mark      = -my_bosonSize/(2*rij*(my_bosonSize - sqrt(rij)));
      const double u_2mark     = boson*(boson*(-boson + sqrt(r)) + 3*(boson - sqrt(r))**2)/(4*r**2*(boson - sqrt(r))**3) ;


    }
  }
}




