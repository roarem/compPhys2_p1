#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class ReadFile
{
  public:
    ReadFile (ifstream* is);
    void    readFile	    ();
    int	    get_size	    ()  {return my_size;}
    int	    get_sampleSize  ()  {return my_size/8;}
    double* get_input	    (double* data);

  protected:
    ifstream* my_is	  = nullptr;
    int	      my_size	  = 0;
    double*   my_inData	  = nullptr;
    char*     my_memblock = nullptr;

};
