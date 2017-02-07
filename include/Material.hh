#ifndef MATERIAL
#define MATERIAL 1

#include <stdio.h>
#include <ctype.h>
#include <iostream>

#include "Element.hh"

class Material
 {
 public:
   Material();
   Material(char*);
   Material(char*, bool);
   Material(int, char**, double*, bool);
   ~Material();

   int NumberOfElements();
   bool Gaseous();
   char* Name();
   double Mass();
   Element* GetElement(int);
   double Fraction(int);
   double A(int);
   double Mass(int);
   int Z(int);
   char* Name(int);

 private:
   char* code;
   int number_of_elements;
   Element** elements;
   double* fractions;
   bool gaseous;
   double mass;

   //ClassDef(Material, 1);
 };

#endif
