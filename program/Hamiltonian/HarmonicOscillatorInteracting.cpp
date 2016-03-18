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

  int nP	= my_system->get_nParticles();
  int nD	= my_system->get_nDimensions();
  double Vint	= 0;
  double Vext	= 0;

  double alpha  = my_system->get_parameters()[0];
  double omega2 = my_system->get_parameters()[1]*
		  my_system->get_parameters()[1];
  double gamma2 = my_system->get_parameters()[2]*
                  my_system->get_parameters()[2];
  double beta   = my_system->get_parameters()[3];

  double alpha2 = alpha*alpha;
  double boson  = my_bosonSize;

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

    const double doubleDeriv = 4*alpha2*(xk*xk + yk*yk + beta*beta*zk*zk)
				- 2 - beta;

    first_of_all += doubleDeriv;

    for (int j = k + 1 ; j < nP ; j++){
      const double xkj	      = xk - my_system->get_particle()[j]->get_position()[0];
      const double ykj 	      = yk - my_system->get_particle()[j]->get_position()[1];
      const double zkj 	      = zk - my_system->get_particle()[j]->get_position()[2];
      const double rkj 	      = sqrt(xkj*xkj + ykj*ykj + zkj*zkj);
      const double ukj_mark   = u_mark (rkj);
      const double ukj_2mark  = u_2mark (rkj);

      const double grad_dot_rkj = xk*xkj + yk*ykj + beta*zk*zkj;
      first_sum += grad_dot_rkj*ukj_mark/rkj;


      last_sum += ukj_2mark + 2*ukj_mark/rkj;
      
      if (rkj < my_bosonSize)
	Vint += 1e10;

      const double rij	= 0;

      for (int i = k + 1 ; i < nP ; i++){
        const double xki = xk - my_system->get_particle()[i]->get_position()[0];
        const double yki = yk - my_system->get_particle()[i]->get_position()[1];
        const double zki = zk - my_system->get_particle()[i]->get_position()[2];
	const double rki = sqrt(xki*xki + yki*yki + zki*zki);

	const double rki_rkj_dot = xki*xkj + yki*ykj + zki*zkj;
	const double uki_mark = u_mark(rki);

	ij_sum += rki_rkj_dot*uki_mark/rki;
      }
      ij_sum *= ukj_mark/rkj;
    }
    first_sum *= -2*alpha;
  }
  const double xk = my_system->get_particle()[nP-1]->get_position()[0];
  const double yk = my_system->get_particle()[nP-1]->get_position()[1];
  const double zk = my_system->get_particle()[nP-1]->get_position()[2];
  r += xk*xk + yk*yk + zk*zk*gamma2;
  Vext = 0.5*r;

  double Laplacian=  ij_sum + last_sum + first_sum + first_of_all;
   
  return Vext + Vint + Laplacian;
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
