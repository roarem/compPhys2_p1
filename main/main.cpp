#include <armadillo>
#include <iostream>
#include <chrono>
#include "../VMCSolver/VMCSolver.h"
using namespace std;

int main (){

  VMCSolver Monty;
  Monty.MonteCarloIntegration();
  cout << "Ferdig!\n";
 
  return 0;

}

/*

class WaveFunction {
  public:
    WaveFunction(VMCSolver* solver) { m_solver = solver; }
    virtual double evaluate() = 0;

  protected:
    VMCSolver* m_solver = nullptr;
}


class HO_NON : public WaveFunction {
  public:
    HO_MON(VMCSolver* solver, double omega) : WaveFunction(solver) { m_omega = omega; }
    double evaluate() { return ... }

  private:
    double m_omega;
}

class HO_INT : public WaveFunction {
  double evaluate() { return ... }
}

class SlaterDet : public WaveFunction {
  double evaluate() { return det.. }
}


class Hamil... {
  virtual double computeLocalEnergy() = 0;
}

class HO_Hamil : public Hamil .. {
  
}

#include "wf.h"
class WaveFunction;

class VMCSolver {
  public:
    void setWaveFunction(WaveFuntion* wf) { m_waveFunction = wf; }
    
    void metropolis();
  private:
    WaveFunction* m_waveFunction;

}


void VMCSolsver::metropolis() {

  double wf = m_waveFunction->evaluate();

  double el = m_hamiltonian->computeLocalEnergy();

  double ratio = wf/wfold;

}

*/

