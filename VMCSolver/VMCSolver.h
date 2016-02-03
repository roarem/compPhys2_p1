#ifndef VMCSOLVER_H
#define VMCSOLVER_H
#include <random>
#include <armadillo>
#include <cmath>
#include <iostream>
#include <functional>
#include <chrono>

using namespace std;
using namespace arma;

class VMCSolver
{
  public:
    VMCSolver();
    void MonteCarloIntegration();
    double waveFunction(const mat &r);
    double localEnergyNumerical(const mat &r);
    double localEnergyAnalytical(const mat &r);

  private:
    unsigned seed;

    int nDimensions;
    int nParticles;
    int nCycles;

    double alpha;
    double beta;
    double stepLength;
    double h;
    double h2;
    double waveFunctionNew;
    double waveFunctionOld;

    mat rOld;
    mat rNew;

    typedef chrono::high_resolution_clock klokka;
    klokka::time_point start = klokka::now();
    default_random_engine generator;
    uniform_real_distribution<double> uniform;

};
#endif //VMCSOLVER_H
