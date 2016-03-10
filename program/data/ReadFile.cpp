#include "ReadFile.h"
#include <iostream>

ReadFile::ReadFile (ifstream* is)
{
  my_is= is;
  readFile();
}

void ReadFile::readFile ()
{
  streampos size;
  size = my_is->tellg() ;
  std::cout << size << std::endl;
  my_size = size;
  my_memblock = new char [size];
  my_is->seekg (0, ios::beg);
  my_is->read(my_memblock,my_size);
  my_is->close();
}

double* ReadFile::get_input(double* data)
{
  data = new double [get_sampleSize()];
  data = (double*)my_memblock;
  return data;
}
