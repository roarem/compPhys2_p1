#pragma once
#include <cmath>

using namespace std;

class Statistics
{
  public:
    Statistics			(double* data, int nSamples);
    double    mean		(double* values, int nValues);
    void      meanAndVariance	(double* values, int nSamples);
    void      Blocking		(int minBlockSize, int maxBlockSize, int nBlockSamples); 

    int	      get_nSamples	()  {return my_nSamples;}
    double    get_mean		()  {return my_mean;}
    double    get_variance	()  {return my_variance;}
    double    get_standardDev	()  {return my_standardDev;}
    double*   get_data		()  {return my_data;}
    

  protected:
    int	    my_nSamples	    = 0;
    double  my_mean	    = 0;
    double  my_variance	    = 0;
    double  my_standardDev  = 0;
    double* my_data	    = nullptr;
    double* blockValues	    = nullptr;

};
