/****************************************************
  This file contains the code for handling the mass tables.
 ******************************************************/
#include "Isotopes.hh"
#include <fstream>

//#define debug
//#define debug_all
//#define debug_transfer

Isotopes::Isotopes() {
	amu = 931.494043;//error is 0.000080

	char temp[256],*cptr;
	int i = 0,n,z;
	double emass,dmass;
	std::ifstream mass_file;
	mass_file.open("./mass.dat",std::ios::in);

	while(!mass_file.bad() && !mass_file.eof() && i < 5012) {
		mass_file>>z;
		mass_file>>n;
		mass_file>>emass;
		mass_file>>dmass;
		mass_file.width(6);
		mass_file>>temp;
		cptr = temp;
		while( *cptr == ' ') {
			cptr++;
		}
		while(isdigit(*cptr)) {
			cptr++;
		}
		IsotopeTable[i] = new Element(z,n,((double)(n+z)*amu)+emass/1000.,emass/1000.,dmass/1000.,cptr,i);
		i++;
		mass_file.ignore(256,'\n');
#ifdef debug_all
		std::cout<<i<<". read: "<<z<<" "<<n<<" "<<emass<<" "<<dmass<<" "<<temp<<"/"<<cptr<<std::endl;
#endif
	}
	max_elements=i;

	mass_file.close();
}

Isotopes::Isotopes(const char* MassFile) {
	amu = 931.494043;//error is 0.000080

	char temp[256],*cptr;
	int i = 0,n,z;
	double emass,dmass;
	std::ifstream mass_file;
	mass_file.open(MassFile,std::ios::in);

	while(!mass_file.bad() && !mass_file.eof() && i < 5012) {
		mass_file>>z;
		mass_file>>n;
		mass_file>>emass;
		mass_file>>dmass;
		mass_file.width(6);
		mass_file>>temp;
		cptr = temp;
		while( *cptr == ' ')	{
			cptr++;
		}
		while(isdigit(*cptr)) {
			cptr++;
		}
		IsotopeTable[i] = new Element(z,n,((double)(n+z)*amu)+emass/1000.,emass/1000.,dmass/1000.,cptr,i);
		i++;
		mass_file.ignore(256,'\n');
#ifdef debug_all
		std::cout<<"read: "<<z<<" "<<n<<" "<<emass<<" "<<dmass<<" "<<temp<<"/"<<cptr<<std::endl;
#endif
	}
	max_elements=i;

	mass_file.close();
}

Isotopes::~Isotopes() {
	for(int i=0;i<max_elements;i++) {
		if(IsotopeTable[i] != NULL) {
			delete IsotopeTable[i];
		}
	}
}

double Isotopes::Mass(int z, int n) {
#ifdef debug
	std::cout<<"start Mass("<<z<<","<<n<<")"<<std::endl;
#endif

	int i = 0;

	while(IsotopeTable[i]->Z() != z || IsotopeTable[i]->N() != n) {
#ifdef debug
		std::cout<<i<<". "<<IsotopeTable[i]->Z()<<" "<<IsotopeTable[i]->N()<<"("<<z<<", "<<n<<")"<<std::endl;
#endif
		i++;
		if(i == max_elements) {
			return -1;
		}
	}

	return IsotopeTable[i]->Mass();
}

double Isotopes::MassExcess(int z, int n) {
#ifdef debug
	std::cout<<"start MassExcess("<<z<<","<<n<<")"<<std::endl;
#endif

	int i = 0;

	while(IsotopeTable[i]->Z() != z || IsotopeTable[i]->N() != n) {
#ifdef debug
		std::cout<<i<<". "<<IsotopeTable[i]->Z()<<" "<<IsotopeTable[i]->N()<<"("<<z<<", "<<n<<")"<<std::endl;
#endif
		i++;
		if(i == max_elements) {
			return -1;
		}
	}

	return IsotopeTable[i]->MassExcess();
}

Element* Isotopes::Search(char* c) {
#ifdef debug
	std::cout<<"start SearchTable("<<c<<")"<<std::endl;
#endif
	int i,n;
	char* cptr;
	char* tmp;
	double a;

	cptr = c;

	//check whether c starts with numbers
	if(isalpha(*cptr)) {
		std::cerr<<"Error in search_table: string "<<c<<" doesn't start with mass number"<<std::endl;
		exit(1);
	}

	//get number of digits in c and move cptr to first non-digit
	n = 0;

	while(isdigit(*cptr)) {
		n++;
		cptr++;
	}

	//copy letters from c to cptr and convert to lower (except for first letter)
	tmp = cptr;
	cptr = new char[strlen(cptr)+1];
	strcpy(cptr,tmp);
	i = 1;
	while (*(cptr+i)) {
		*(cptr+i)=tolower(*(cptr+i));
		i++;
	}

	//copy digits from c to tmp and convert to double
	tmp = new char[n+1];
	strncpy(tmp,c,n);
	tmp[n] = '\0';
	a = atof(tmp);

	i = 0;
	while(i<max_elements) {
		if(strcmp(IsotopeTable[i]->Name(),cptr)==0) {
#ifdef debug
			std::cout<<"Search::A(): "<<IsotopeTable[i]->A()<<std::endl;
#endif
			while(IsotopeTable[i]->A() != a && i<max_elements)	{
#ifdef debug
				std::cout<<a<<" != "<<IsotopeTable[i]->A()<<" ("<<i<<")"<<std::endl;
#endif
				i++;
			}
			break;
		}
		i++;
	}

	delete[] cptr;
	delete[] tmp;

	if(i < max_elements) {
		return IsotopeTable[i];
	} else {
		return NULL;
	}
}

Element* Isotopes::Search(int z, int n) {
#ifdef debug
	std::cout<<"start SearchTable("<<z<<", "<<n<<")"<<std::endl;
#endif
	int i;

	i = 0;
	while(i<max_elements) {
		if(IsotopeTable[i]->Z() == z) {
#ifdef debug
			std::cout<<"Search::N(): "<<IsotopeTable[i]->N()<<std::endl;
#endif
			while(IsotopeTable[i]->N() != n) {
				i++;
			}
			break;
		}
		i++;
	}

	if(i < max_elements) {
		return IsotopeTable[i];
	} else {
		return NULL;
	}
}

void Isotopes::ProjectileOneNeutronGain(Element*& ejectile, Element*& recoil) {
#ifdef debug_transfer
	std::cout<<"called Isotopes::ProjectileOneNeutronGain("<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<")"<<std::endl;
#endif
	ejectile = this->Reaction(ejectile,0,1);
	recoil   = this->Reaction(recoil,0,-1);
#ifdef debug_transfer
	std::cout<<"returned: "<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<std::endl;
#endif
}

void Isotopes::ProjectileOneNeutronLoss(Element*& ejectile, Element*& recoil) {
#ifdef debug_transfer
	std::cout<<"called Isotopes::ProjectileOneNeutronLoss("<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<")"<<std::endl;
#endif
	ejectile = this->Reaction(ejectile,0,-1);
	recoil   = this->Reaction(recoil,0,1);
#ifdef debug_transfer
	std::cout<<"returned: "<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<std::endl;
#endif
}

void Isotopes::ProjectileTwoNeutronGain(Element*& ejectile, Element*& recoil) {
#ifdef debug_transfer
	std::cout<<"called Isotopes::ProjectileTwoNeutronGain("<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<")"<<std::endl;
#endif
	ejectile = this->Reaction(ejectile,0,2);
	recoil   = this->Reaction(recoil,0,-2);
#ifdef debug_transfer
	std::cout<<"returned: "<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<std::endl;
#endif
}

void Isotopes::ProjectileTwoNeutronLoss(Element*& ejectile, Element*& recoil) {
#ifdef debug_transfer
	std::cout<<"called Isotopes::ProjectileTwoNeutronLoss("<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<")"<<std::endl;
#endif
	ejectile = this->Reaction(ejectile,0,-2);
	recoil   = this->Reaction(recoil,0,2);
#ifdef debug_transfer
	std::cout<<"returned: "<<ejectile->A()<<ejectile->Name()<<", "<<recoil->A()<<recoil->Name()<<std::endl;
#endif
}

Element* Isotopes::Reaction(Element* el, int proton_change, int neutron_change) {
#ifdef debug_transfer
	std::cout<<"called Isotopes::Reaction("<<el->A()<<el->Name()<<", "<<proton_change<<", "<<neutron_change<<")"<<std::endl;
#endif
	int new_proton_number, new_neutron_number, index;

	if(proton_change == 0 && neutron_change == 0) {
		return el;
	}

	new_proton_number = el->Z() + proton_change;
	new_neutron_number = el->N() + neutron_change;
	index = el->Index();

#ifdef debug_transfer
	std::cout<<"new_proton_number: "<<new_proton_number<<", new_neutron_number: "<<new_neutron_number<<", index: "<<index<<std::endl;
#endif

	if(proton_change >= 0 && neutron_change >= 0) {
		while(IsotopeTable[index]->Z() != new_proton_number || IsotopeTable[index]->N() != new_neutron_number) {
			index++;
#ifdef debug_transfer
			std::cout<<"increment index: "<<index<<std::endl;
#endif
		}
	} else {
		while(IsotopeTable[index]->Z() != new_proton_number || IsotopeTable[index]->N() != new_neutron_number) {
			index--;
#ifdef debug_transfer
			std::cout<<"decrement index: "<<index<<std::endl;
#endif
		}
	}

#ifdef debug_transfer
	std::cout<<"final index: "<<index<<" = "<<IsotopeTable[index]->A()<<IsotopeTable[index]->Name()<<std::endl;
#endif

	return IsotopeTable[index];
}

int CalculateQ(Element** particle,double* q,double* dq) {
	double dummy;
	/*********** calculate q-value *******************************/
	*q = -1.0*(particle[2]->MassExcess()+particle[3]->MassExcess());
	*q += (particle[0]->MassExcess()+particle[1]->MassExcess());
	//printf("CaluculateQ: q = %f + %f - %f - %f (%.0f%s + %.0f%s - %.0f%s - %.0f%s)\n",particle[0]->MassExcess(),particle[1]->MassExcess(),particle[2]->MassExcess(),particle[3]->MassExcess(),particle[0]->A(),particle[0]->Name(),particle[1]->A(),particle[1]->Name(),particle[2]->A(),particle[2]->Name(),particle[3]->A(),particle[3]->Name());
	dummy = particle[0]->DMass();
	*dq = dummy*dummy;
	dummy = particle[1]->DMass();
	*dq += dummy*dummy;
	dummy = particle[2]->DMass();
	*dq += dummy*dummy;
	dummy = particle[3]->DMass();
	*dq += dummy*dummy;
	*dq = (double)sqrt(*dq);

	return 0;
}

