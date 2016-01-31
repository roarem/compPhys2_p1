#include <armadillo>
#include <iostream>
#include "../VMCSolver/VMCSolver.h"

using namespace std;

int main (){

  VMCSolver Monty;
  Monty.MonteCarloIntegration();
  cout << "Ferdig!\n";
  
  return 0;

}
