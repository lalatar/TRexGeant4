#ifndef ISOTOPES
#define ISOTOPES

#include <math.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

#include "Element.hh"

int CalculateQ(Element**,double*,double*);

class Isotopes : Element {
public:
  Isotopes();
  Isotopes(const char*);
  ~Isotopes();
  Element* Search(char*);
  Element* Search(int,int);
  double Mass(int,int);
  double MassExcess(int,int);
  void ProjectileOneNeutronGain(Element*&,Element*&);
  void ProjectileOneNeutronLoss(Element*&,Element*&);
  void ProjectileTwoNeutronGain(Element*&,Element*&);
  void ProjectileTwoNeutronLoss(Element*&,Element*&);
  Element* Reaction(Element*,int,int);
  int NumberOfIsotopes() { return max_elements; }

private:
  Element* IsotopeTable[5012];
  double amu;
  int max_elements;

  //ClassDef(Isotopes, 1);
};

#endif
