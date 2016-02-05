#include "RandomUniform.h"

RandomUniform::RandomUniform( System system*,
			      int nDimensions,
			      int nParticles):
			      InitialState(system)
{
  
  my_nDimensions  = nDimensions;
  my_nParticles	  = nParticles;

  my_system->set_nDimensions  (nDimensions);
  my_system->set_nParticles   (nParticles);
  
  setupInitialState();
}

UniformRandom::setupInitialState ()
{
  
  std::default_random_engine		  generator;
  std::uniform_real_distribution<double>  uniform(0.0,1.0);
  clock::duration dur = clock::now() - start;
  seed = dur.count();
  generator.seed(seed);

  for (int i = 0 ; i < my_nParticles ; i++){
    std::vector<double> position = std::vector<double>();
    
    for(int j = 0 ; j < my_nDimensions ; j++){
      position.push_back  (uniform(generator) - 0.5);
    }
  my_particles.push_back	      (new Particle());
  my_particles.at(i)->set_nDimensions (my_nDimensions);
  my_particles.at(i)->set_position    (position);
  }
}
