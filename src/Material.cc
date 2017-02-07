#include <stdio.h>
#include <ctype.h>
#include <iostream>

#include "Material.hh"

//#define debug

Material::Material()
{
}

Material::Material(char* code_in)
{
  int length = strlen(code_in);

  code = new char[length+1];

  for(int i=0;i<length;i++)
    {
      code[i] = toupper(code_in[i]);
    }
  code[length] = '\0';

  if(strstr(code,"PE") != 0)
    {
      if(isalpha(code[0]))
	{
	  number_of_elements = 2;
	  gaseous = false;
	  elements = new Element*[2];
	  fractions = new double[2];
	  
	  elements[0] = new Element("12C");
	  elements[1] = new Element("2H");
	  fractions[0] = 1./3.*elements[0]->Mass()/(1./3.*elements[0]->Mass()+2./3.*elements[1]->Mass());
	  fractions[1] = 2./3.*elements[1]->Mass()/(1./3.*elements[0]->Mass()+2./3.*elements[1]->Mass());
	  //mass = elements[0]->Mass()+2.*elements[1]->Mass();
	  mass = 2. * elements[0]->Mass() + 4.*elements[1]->Mass();
	}
      else
	{
	  double ratio = atof(code);
	  if(ratio < 0 || ratio > 1)
	    {
	      std::cout<<"Error, only ratios between 0 and 1 are allowed, tried to build "<<code<<" with deuteron/proton ratio = "<<ratio<<std::endl;
	      exit(1);
	    }
	  if(ratio == 0)
	    {
	      number_of_elements = 2;
	      gaseous = false;
	      elements = new Element*[2];
	      fractions = new double[2];
	      
	      elements[0] = new Element("12C");
	      elements[1] = new Element("1H");
	      fractions[0] = 1./3.*elements[0]->Mass()/(1./3.*elements[0]->Mass()+2./3.*elements[1]->Mass());
	      fractions[1] = 2./3.*elements[1]->Mass()/(1./3.*elements[0]->Mass()+2./3.*elements[1]->Mass());
	      //mass = elements[0]->Mass()+2.*elements[1]->Mass();
	      mass = 2. * elements[0]->Mass() + 4.*elements[1]->Mass();
	    }
	  else if(ratio == 1)
	    {
	      number_of_elements = 2;
	      gaseous = false;
	      elements = new Element*[2];
	      fractions = new double[2];
	      
	      elements[0] = new Element("12C");
	      elements[1] = new Element("2H");
	      fractions[0] = 1./3.*elements[0]->Mass()/(1./3.*elements[0]->Mass()+2./3.*elements[1]->Mass());
	      fractions[1] = 2./3.*elements[1]->Mass()/(1./3.*elements[0]->Mass()+2./3.*elements[1]->Mass());
	      //mass = elements[0]->Mass()+2.*elements[1]->Mass();
	      mass = 2. * elements[0]->Mass() + 4.*elements[1]->Mass();
	    }
	  else
	    {
	      number_of_elements = 3;
	      gaseous = false;
	      elements = new Element*[3];
	      fractions = new double[3];
	      
	      elements[0] = new Element("12C");
	      elements[1] = new Element("1H");
	      elements[2] = new Element("2H");
	      fractions[0] = 1./3.*elements[0]->Mass()/(1./3.*elements[0]->Mass()+(1-ratio)*2./3.*elements[1]->Mass()+ratio*2./3.*elements[2]->Mass());
	      fractions[1] = (1-ratio)*2./3.*elements[1]->Mass()/(1./3.*elements[0]->Mass()+(1-ratio)*2./3.*elements[1]->Mass()+ratio*2./3.*elements[2]->Mass());
	      fractions[2] = ratio*2./3.*elements[2]->Mass()/(1./3.*elements[0]->Mass()+(1-ratio)*2./3.*elements[1]->Mass()+ratio*2./3.*elements[2]->Mass());
	      //mass = elements[0]->Mass()+(1-ratio)*2.*elements[1]->Mass()+ratio*2.*elements[2]->Mass();
	      mass = 2.* elements[0]->Mass()+(1-ratio)*4.*elements[1]->Mass()+ratio*4.*elements[2]->Mass();
	    }
	}
    }
  else if(strstr(code,"MY") != 0)
    {
      number_of_elements = 3;
      gaseous = false;
      elements = new Element*[3];

      elements[0] = new Element("12C");
      elements[1] = new Element("1H");
      elements[2] = new Element("16O");
      fractions[0] = 10./3.*elements[0]->Mass()/(10./3.*elements[0]->Mass()+8./3.*elements[1]->Mass()+4./3.*elements[2]->Mass());
      fractions[1] =  8./3.*elements[1]->Mass()/(10./3.*elements[0]->Mass()+8./3.*elements[1]->Mass()+4./3.*elements[2]->Mass());
      fractions[2] =  4./3.*elements[2]->Mass()/(10./3.*elements[0]->Mass()+8./3.*elements[1]->Mass()+4./3.*elements[2]->Mass());
      mass = 10.*elements[0]->Mass()+8.*elements[1]->Mass()+4.*elements[2]->Mass();
    }
  else
    {
      std::cerr<<"Material::Material(code): code = "<<code<<" ("<<code_in<<") not implemented yet!"<<std::endl;
    }
  std::cout << "creating Materials -----------------------" << std::endl;
#ifdef debug
  std::cout<<"Created instance of class Material("<<code<<") with "<<this->NumberOfElements()<<" elements:"<<std::endl;
  for(int i=0;i<this->NumberOfElements();i++)
    {
      std::cout<<"    "<<i<<".: "<<this->A(i)<<this->Name(i)<<"/"<<elements[i]->A()<<elements[i]->Name()<<" (Z = "<<elements[i]->Z()<<", N = "<<elements[i]->N()<<")"<<std::endl;
    }
#endif
}

Material::Material(char* element, bool gas)
{
  number_of_elements = 1;
  gaseous = gas;
  elements = new Element*[1];
  fractions = new double[1];

  elements[0] = new Element(element);
  fractions[0] = 1;

  mass = elements[0]->Mass();

  code = new char[strlen(element)];
  strcpy(code,element);
}

Material::Material(int nofel, char* el[], double fr[], bool gas)
{
  double sum_of_fractions;

  number_of_elements = nofel;
  gaseous = gas;
  elements = new Element*[nofel];
  fractions = new double[nofel];

  sum_of_fractions = 0;
  mass = 0;

  for(int i=0;i<nofel;i++)
    {
      elements[i] = new Element(el[i]);
      fractions[i] = fr[i];
      sum_of_fractions += fr[i];
    }

  for(int i=0;i<nofel;i++)
    {
      fractions[i] /= sum_of_fractions;
      mass += elements[i]->Mass()*fractions[i];
    }

  code = new char[3];
  code[0] = 'X';
  code[1] = 'X';
  code[2] = '\0';
}

Material::~Material()
{
  if(fractions != NULL)
    {
      delete[] fractions;
    }

  if(elements != NULL)
    {
      for(int i=0;i<number_of_elements;i++)
	{
	  if(elements[i] != NULL)
	    {
	      delete elements[i];
	    }
	}
      delete[] elements;
    }

  if(code != NULL)
    {
      delete[] code;
    }
}

int Material::NumberOfElements()
{
  return number_of_elements;
}

bool Material::Gaseous()
{
  return gaseous;
}

char* Material::Name()
{
  return code;
}

double Material::Mass()
{
  return mass;
}

Element* Material::GetElement(int n_el)
{
  if(n_el < this->number_of_elements)
    return elements[n_el];
  else
    return NULL;
}

double Material::Fraction(int n_el)
{
  return fractions[n_el];
}

double Material::A(int n_el)
{
  return elements[n_el]->A();
}

double Material::Mass(int n_el)
{
  return elements[n_el]->Mass();
}

int Material::Z(int n_el)
{
  return elements[n_el]->Z();
}

char* Material::Name(int n_el)
{
  return elements[n_el]->Name();
}
