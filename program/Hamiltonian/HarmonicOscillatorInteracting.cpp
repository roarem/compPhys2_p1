#include "HarmonicOscillatorInteracting.h"
#include <iomanip>

HarmonicOscillatorInteracting::HarmonicOscillatorInteracting(System* system,
							     double bosonSize):
  HarmonicOscillator(system)
{
  my_bosonSize = bosonSize;
  my_bosonSize2 = bosonSize*bosonSize;
}

double HarmonicOscillatorInteracting::computeLocalEnergy ()
{

  int nP	= my_system->get_nParticles();
  int nD	= my_system->get_nDimensions();
  double Vint	= 0;
  double Vext	= 0;
  double Laplacian = 0;
  double alpha  = my_system->get_parameters()[0];
  double omega2 = my_system->get_parameters()[1]*
		  my_system->get_parameters()[1];
  double gamma2 = my_system->get_parameters()[2]*
                  my_system->get_parameters()[2];
  double beta   = my_system->get_parameters()[3];

  double alpha2 = alpha*alpha;
  double boson  = my_bosonSize;

if (my_system->get_analytical()){
  double first_of_all	= 0;
  double first_sum	= 0;
  double ij_sum		= 0;
  double last_sum	= 0;
  double r		= 0;

  for (int k = 0 ; k < nP-1 ; k++){

    const double xk = my_system->get_particle()[k]->get_position()[0];
    const double yk = my_system->get_particle()[k]->get_position()[1];
    const double zk = my_system->get_particle()[k]->get_position()[2];

    r += xk*xk + yk*yk + zk*zk*gamma2;

    const double doubleDeriv = 2*alpha*(2*alpha*(xk*xk + yk*yk + beta*beta*zk*zk) - 
			      2 - beta);

    first_of_all += doubleDeriv;

    for (int j = k + 1 ; j < nP ; j++){
      const double xkj	      = xk - my_system->get_particle()[j]->get_position()[0];
      const double ykj 	      = yk - my_system->get_particle()[j]->get_position()[1];
      const double zkj 	      = zk - my_system->get_particle()[j]->get_position()[2];
      const double rkj 	      = sqrt(xkj*xkj + ykj*ykj + zkj*zkj);
      const double ukj_mark   = u_mark (rkj);
      const double ukj_2mark  = u_2mark (rkj);

      const double grad_dot_rkj = -(xk*xkj + yk*ykj + beta*zk*zkj);

      first_sum += grad_dot_rkj*ukj_mark/rkj;
      last_sum	+= ukj_2mark + 2*ukj_mark/rkj;
      
      Vint += (rkj*rkj < my_bosonSize2)*1e10;

      for (int i = k + 1 ; i < nP ; i++){
        const double xki = xk - my_system->get_particle()[i]->get_position()[0];
        const double yki = yk - my_system->get_particle()[i]->get_position()[1];
        const double zki = zk - my_system->get_particle()[i]->get_position()[2];
	const double rki = sqrt(xki*xki + yki*yki + zki*zki);

	const double rki_dot_rkj  = xki*xkj + yki*ykj + zki*zkj;
	const double uki_mark	  = u_mark(rki);

	ij_sum += rki_dot_rkj*uki_mark/rki;
      }
      ij_sum *= ukj_mark/rkj;
    }
    first_sum *= -2*alpha;
  }
  const double xk = my_system->get_particle()[nP-1]->get_position()[0];
  const double yk = my_system->get_particle()[nP-1]->get_position()[1];
  const double zk = my_system->get_particle()[nP-1]->get_position()[2];

  r	+= xk*xk + yk*yk + zk*zk*gamma2;
  Vext	= 0.5*r;

  //cout << ij_sum << "  " << last_sum << "  " << first_sum << "  " << first_of_all << endl;
  Laplacian=  ij_sum + last_sum + 2*first_sum + first_of_all;
  
  //const double analytical = -0.5*Laplacian + Vint + Vext;
}  
//Laplacian = 0;
//Vint	  = 0;
//Vext	  = 0;
else{
  const double waveFunctionCurrent = my_system->get_waveFunction()->evaluate();
  double laplacian = 0;
  Vint = 0;
  Vext = 0;
  for(int p = 0 ; p < nP ; p++){
    double r2  = 0;

    for (int k = p+1 ; k < nP ; k++){
      double xsep2 = 0;

      for (int d = 0 ; d < nD ; d++){
	const double x1 = my_system->get_particle()[p]->get_position()[d];
	const double x2 = my_system->get_particle()[k]->get_position()[d];
	xsep2 += (x1 - x2)*(x1 - x2);
      }
      Vint += (xsep2 < my_bosonSize2)*1e10;
    }
    for (int d = 0 ; d < nD ; d++){
      const double x = my_system->get_particle()[p]->get_position()[d];
      r2 += x*x*(d != 2 ? 1 : gamma2);
      laplacian += my_system->get_waveFunction()->computeDoubleDerivative(p,d,waveFunctionCurrent);
    }
    Vext += 0.5*r2;
  }
  Laplacian = laplacian/waveFunctionCurrent;
}
//  const double numerical = -0.5*Laplacian + Vint + Vext;
  //cout << numerical-analytical << endl;
  //cout << energy << "  " << Laplacian << "  " << Vint << "  " << Vext << endl;
  double energy = -0.5*Laplacian + Vint + Vext;
 // energy = analytical;
  return energy;
}

double HarmonicOscillatorInteracting::u_mark (double r)
{
  return my_bosonSize/(r*(r - my_bosonSize));
}

double HarmonicOscillatorInteracting::u_2mark (double r)
{
  double value = (my_bosonSize*(my_bosonSize - 2*r)) / (r*r*(r-my_bosonSize)*(r - my_bosonSize));
  return value;
}
