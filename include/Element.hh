#ifndef ELEMENT
#define ELEMENT

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <cstring>

class Element
{
public:
  Element();
  Element(char*);
  Element(int,int,double,double,double,char*,int);
  ~Element();
  
  int Z();
  int N();
  double A();
  double Mass();
  double MassExcess();
  double DMass();
  char* Name();
  int Index();
  
private:
  int get_charge(char*);
  double get_mass(int);
  
  double mass;
  int proton_number;
  int neutron_number;
  double mass_excess;
  double dmass;
  char* code;
  int index;
  bool natural;

  //ClassDef(Element, 1);
};

#endif
