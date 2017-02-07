#include "Element.hh"

//#define debug

Element::Element()
{
}

Element::Element(char* el)
{
  int length = strlen(el);
  if(length == 0)
    {
		 std::cerr<<"ERROR, tried to create Element with empty string!"<<std::endl;
      exit(1);
    }

  int first_digit = length;
  int first_letter = length;
  int code_length = 0;
  int i;

  if(isdigit(el[0]))
    {
      first_digit = 0;
    }
  else if(isalpha(el[0]))
    {
      first_letter = 0;
    }
  else
    {
		 std::cerr<<"ERROR, tried to create Element with string that doesn't start with an alphanumerial ("<<el<<")!"<<std::endl;
      exit(1);
    }

#ifdef debug
  std::cout<<"first_digit: "<<first_digit<<" and first_letter: "<<first_letter<<std::endl;
#endif

  for(i=0;i<length;i++)
    {
      if(isdigit(el[i]) && first_letter == 0) //found first digit in a string that started with letters
	{
	  first_digit = i;
	  code_length = i + 1;
	  break;
	}
      if(isalpha(el[i]) && first_digit == 0) //found first letter in a string that started with digits
	{
	  first_letter = i;
	  code_length = length - i + 1;
	  break;
	}
    }

  if(i == length)
    {
      if(first_digit == 0) //string contains only digits
	{
		std::cerr<<"ERROR, tried to create Element with string that contains only digits ("<<el<<")!"<<std::endl;
	  exit(1);
	}
      if(first_letter == 0) //string contains only letters
	{
	  code = new char[length+1];
	  strcpy(code, el);
	  
	  proton_number = get_charge(code);
	  mass = get_mass(proton_number);
	  natural = true;
	}
    }
  else
    {
      code = new char[code_length];
      strncpy(code, el+first_letter, code_length - 1);
      code[code_length - 1] = '\0';
      
      proton_number = get_charge(code);
      neutron_number = atoi(el+first_digit) - proton_number;
      mass_excess = 0.;
      mass = atof(el+first_digit)*931.494034+mass_excess;
      natural = false;
    }

#ifdef debug
  std::cout<<"Created instance of class element("<<el<<"): "<<flush<<A()<<Name()<<std::endl;
  std::cout<<"mass = "<<mass<<", Z = "<<proton_number<<", N = "<<neutron_number<<", mass_excess = "<<mass_excess<<", index = "<<index<<std::endl;
#endif
}

Element::Element(int z,int n,double m,double m_ex,double dm,char* cd,int ind)
{
  proton_number = z;
  neutron_number = n;
  mass = m;
  mass_excess = m_ex;
  dmass = dm;
  code = new char[strlen(cd)+1];
  strcpy(code,cd);
  index = ind;
  natural = false;
#ifdef debug
  std::cout<<"Created instance of class element("<<z<<", "<<n<<", "<<m<<", "<<m_ex<<", "<<dm<<", "<<cd<<", "<<ind<<"): "<<flush<<A()<<Name()<<std::endl;
  std::cout<<"mass = "<<mass<<", Z = "<<proton_number<<", N = "<<neutron_number<<", mass_excess = "<<mass_excess<<", index = "<<index<<std::endl;
#endif
}

Element::~Element()
{
  if(code != NULL)
    {
      delete[] code;
    }
}

int Element::get_charge(char* code)
{
  char codes[105][3] = {"H","HE","LI","BE","B","C","N","O","F","NE","NA","MG","AL","SI","P","S","CL","AR","K","CA","SC","TI","V","CR","MN","FE","CO","NI","CU","ZN","GA","GE","AS","SE","BR","KR","RB","SR","Y","ZR","NB","MO","TC","RU","RH","PD","AG","CD","IN","SN","SB","TE","F","XE","CS","BA","LA","CE","PR","ND","PM","SM","EU","GD","TB","DY","HO","ER","TM","YB","LU","HF","TA","W","RE","OS","IR","PT","AU","HG","TI","PB","BI","PO","AT","RN","FR","RA","AC","TH","PA","U","NP","PU","AM","CM","BK","CF","ES","FM","MD","NO","LR","RF","HA"};

  char* tmp;

  int length = strlen(code);

  tmp = new char[length+1];

  for(int i=0;i<length;i++)
    {
      tmp[i] = toupper(code[i]);
    }
  tmp[length] = '\0';

  for(int i=0;i<105;i++)
    {
      if(strcmp(tmp,codes[i]) == 0)
	{
	  delete[] tmp;
	  return i+1;
	}
    }

  delete[] tmp;
  return 0;
}

double Element::get_mass(int proton_number)
{
  double mass[106] = {1,1.00797,4.0026,6.939,9.0122,10.818,12.01115,14.0067,15.9994,18.99984,20.183,22.9898,24.312,26.9815,28.086,30.9738,32.064,35.453,39.948,39.102,40.08,44.956,47.90,50.942,51.996,54.938,55.847,58.933,58.71,63.54,65.37,69.72,72.59,74.922,78.96,79.909,83.80,85.47,87.62,88.909,91.22,92.906,95.94,98.,101.07,102.905,106.4,107.87,112.4,114.82,118.69,121.75,127.60,126.904,131.3,132.905,137.34,138.91,140.12,140.907,144.24,146.,150.35,151.96,157.25,158.924,162.50,164.93,167.26,168.934,173.04,174.97,178.49,180.948,183.85,186.2,190.2,192.2,195.09,196.967,200.59,204.37,207.19,208.98,210.,210.,222.,223.,226.,227.,232.038,231.,238.03,237.,242.,243.,247.,247.,249.,254.,253.,256.,254.,259.,257.,260.};

  if(0 <= proton_number && proton_number < 106)
    {
      return mass[proton_number];
    }
  else
    {
      return -1.;
    }
}

int Element::Z()
{
  return proton_number;
}

int Element::N()
{
  return neutron_number;
}

double Element::A()
{
  if(natural)
    {
#ifdef debug
		 std::cout<<"Element::A(): natural"<<std::endl;
#endif
      return mass;
    }
  else
    {
#ifdef debug
		 std::cout<<"Element::A(): not natural"<<std::endl;
#endif
      return ((double) (proton_number+neutron_number));
    }
}

double Element::Mass()
{
  if(natural)
    {
      return mass*931.494034;
    }
  else
    {
      return mass;
    }
}

double Element::MassExcess()
{
  return mass_excess;
}

double Element::DMass()
{
  return dmass;
}

char* Element::Name()
{
  return code;
}

int Element::Index()
{
  return index;
}

//  switch(proton_number)
//    {
//    case 1:
//      return 1.00797;
//    case 2:
//      return 4.0026;
//    case 3:
//      return 6.939;
//    case 4:
//      return 9.0122;
//    case 5:
//      return 10.818;
//    case 6:
//      return 12.01115;
//    case 7:
//      return 14.0067;
//    case 8:
//      return 15.9994;
//    case 9:
//      return 18.99984;
//    case 10:
//      return 20.183;
//    case 11:
//      return 22.9898;
//    case 12:
//      return 24.312;
//    case 13:
//      return 26.9815;
//    case 14:
//      return 28.086;
//    case 15:
//      return 30.9738;
//    case 16:
//      return 32.064;
//    case 17:
//      return 35.453;
//    case 18:
//      return 39.948;
//    case 19:
//      return 39.102;
//    case 20:
//      return 40.08;
//    case 21:
//      return 44.956;
//    case 22:
//      return 47.90;
//    case 23:
//      return 50.942;
//    case 24:
//      return 51.996;
//    case 25:
//      return 54.938;
//    case 26:
//      return 55.847;
//    case 27:
//      return 58.933;
//    case 28:
//      return 58.71;
//    case 29:
//      return 63.54;
//    case 30:
//      return 65.37;
//    case 31:
//      return 69.72;
//    case 32:
//      return 72.59;
//    case 33:
//      return 74.922;
//    case 34:
//      return 78.96;
//    case 35:
//      return 79.909;
//    case 36:
//      return 83.80;
//    case 37:
//      return 85.47;
//    case 38:
//      return 87.62;
//    case 39:
//      return 88.909;
//    case 40:
//      return 91.22;
//    case 41:
//      return 92.906;
//    case 42:
//      return 95.94;
//    case 43:
//      return 98.;
//    case 44:
//      return 101.07;
//    case 45:
//      return 102.905;
//    case 46:
//      return 106.4;
//    case 47:
//      return 107.87;
//    case 48:
//      return 112.4;
//    case 49:
//      return 114.82;
//    case 50:
//      return 118.69;
//    case 51:
//      return 121.75;
//    case 52:
//      return 127.60;
//    case 53:
//      return 126.904;
//    case 54:
//      return 131.3;
//    case 55:
//      return 132.905;
//    case 56:
//      return 137.34;
//    case 57:
//      return 138.91;
//    case 58:
//      return 140.12;
//    case 59:
//      return 140.907;
//    case 60:
//      return 144.24;
//    case 61:
//      return 146.;
//    case 62:
//      return 150.35;
//    case 63:
//      return 151.96;
//    case 64:
//      return 157.25;
//    case 65:
//      return 158.924;
//    case 66:
//      return 162.50;
//    case 67:
//      return 164.93;
//    case 68:
//      return 167.26;
//    case 69:
//      return 168.934;
//    case 70:
//      return 173.04;
//    case 71:
//      return 174.97;
//    case 72:
//      return 178.49;
//    case 73:
//      return 180.948;
//    case 74:
//      return 183.85;
//    case 75:
//      return 186.2;
//    case 76:
//      return 190.2;
//    case 77:
//      return 192.2;
//    case 78:
//      return 195.09;
//    case 79:
//      return 196.967;
//    case 80:
//      return 200.59;
//    case 81:
//      return 204.37;
//    case 82:
//      return 207.19;
//    case 83:
//      return 208.98;
//    case 84:
//      return 210.;
//    case 85:
//      return 210.;
//    case 86:
//      return 222.;
//    case 87:
//      return 223.;
//    case 88:
//      return 226.;
//    case 89:
//      return 227.;
//    case 90:
//      return 232.038;
//    case 91:
//      return 231.;
//    case 92:
//      return 238.03;
//    case 93:
//      return 237.;
//    case 94:
//      return 242.;
//    case 95:
//      return 243.;
//    case 96:
//      return 247.;
//    case 97:
//      return 247.;
//    case 98:
//      return 249.;
//    case 99:
//      return 254.;
//    case 100:
//      return 253.;
//    case 101:
//      return 256.;
//    case 102:
//      return 254.;
//    case 103:
//      return 259.;
//    case 104:
//      return 257.;
//    case 105:
//      return 260.;
//    default:
//      return -1;
//    }
//}
