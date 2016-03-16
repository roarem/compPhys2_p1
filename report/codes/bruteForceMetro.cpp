randomMove	  = normalDistribution;
waveFunctionOld = my_waveFunction->evaluate(); 

my_particles[chosenParticle]->changePosition(chosenDimension, randomMove);

waveFunctionNew = my_waveFunction->evaluate();

waveFunctionsCompared = (waveFunctionNew*waveFunctionNew)/
      	         (waveFunctionOld*waveFunctionOld);

if (waveFunctionsCompared < uniformDistribution{
  my_particles[chosenParticle]->changePosition(chosenDimension, -randomMove);
  return false;
}
return true;
