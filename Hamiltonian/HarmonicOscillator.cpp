#include "HarmonicOscillator.h"


HarmonicOscillator::HarmonicOscillator (System* system, double omega) :
  Hamiltonian(system)
{
  my_omega = omega;
}

double HarmonicOscillator::computeLocalEnergy (std::vector<Particle*> particles)
{

