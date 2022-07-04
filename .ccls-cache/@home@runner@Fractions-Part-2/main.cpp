#include <iostream>
#include <string>

using namespace std;

class Fraction{
public:
  Fraction(int numer, int denom);
  string toString(int num, int den);
  double toDouble(int num, int den);
  // the functions below do not change the object
  // on which they are called, they produce a new object

  // not sure what types these functions should be
  Fraction plus(Fraction that);
  Fraction minus(Fraction that);
  Fraction times(Fraction that);
  Fraction by(Fraction that);
  Fraction negatives(Fraction that);
  void print(Fraction that);
  string improperFrac(Fraction that);
private:
  int numerator;
  int denominator;
  Fraction reduce(Fraction Final);
  bool negative = false;

  int A;
  int B;
  int gcd;

  int improper = 0;
};

Fraction::Fraction(int numer, int denom){
  numerator = numer;
  denominator = denom;
}

string Fraction::toString(int num, int den)
{
  return to_string(num) + "/" + to_string(den);
}

double Fraction::toDouble(int num, int den)
{
  // numerator and denominator are ints 
  //have to force at least one to be float
  return num / (1.0 * den);
}
// example input
// 3 / 4
// 1 / 3

//example output
// 3/4 + 1/3 = 1 1/12
// 3/4 - 1/3 = 5/123/4 * 1/3 = 1/4
// 3/4 / 1/3 = 2 1/4

Fraction Fraction::times(Fraction that)
{
  int num = this->numerator * that.numerator;
  int den = this->denominator * that.denominator;
  Fraction result(num, den);
  // we could call result.reduce() here
  // or use it just before it is neccessary
  result = reduce(result);
  result = negatives(result);
  return result;
// implement other Fraction methods
  }

Fraction Fraction::reduce(Fraction Final)
{
  //may not be reducing because of negatives, check
  if(Final.numerator < 0 || Final.denominator < 0)
  {
    negative = true;
  }
  else
  {
    negative = false;
  }
  A = abs(Final.numerator);
  B = abs(Final.denominator);
  for(int i = 1; i <= A && i <= B; i++)
  {
    if(A % i == 0 && B % i == 0)
    {
      gcd = i;
    }
  } 
  Final.numerator = Final.numerator / gcd;
  Final.denominator = Final.denominator / gcd;
  if(negative)
  {
  Final.numerator *= -1;
  }
  return Final;
}

// Mr.Byrn's version of gcd
//   int gcd(int a, int b) {
// 	//Must use the abs of a and b
// 	a = abs(a);
// 	b = abs(b);
// 	while(a!=b) {
// 		if(a>b) {
// 			a -= b;
// 		} else {
// 			b -= a;
// 		}
// 	}
// 	return a;
// }
  
  // if(Final.numerator > Final.denominator){
  //   improper = Final.numerator / Final.denominator;
  //   Final.numerator = Final.numerator % Final.denominator;
  //   //return to_string(improper) + " " + toString(Final.numerator, Final.denominator);
  // }
  //return(toString(Final.numerator, Final.denominator))


Fraction Fraction::negatives(Fraction that){
// don't think I need this
  // if((this -> numerator < 0) && (this -> denominator < 0))
  // {
  //   this -> numerator = this -> numerator * -1;
  //   this -> denominator = this -> denominator * -1;
  // }
  
  if((that.numerator < 0) && (that.denominator < 0))
  {
    that.numerator = that.numerator * -1;
    that.denominator = that.denominator * -1;
  }

  if((that.denominator < 0) && (that.numerator > 0))
  {
    that.denominator *= -1;
    that.numerator *= -1;
  }
// don't think I need this 
  // if((this -> numerator > 0) && (this -> denominator < 0))
  // {
  //   this -> numerator *= -1;
  //   this -> denominator *= -1;
  // }
  return that;
  
}

Fraction Fraction::by(Fraction that){
  //// Take the reciprocal 
  // numerator * that.denominator
  // denominator * that.numerator
  //reduce
  int num = this->numerator * that.denominator;
  int den = this->denominator * that.numerator;
  
  Fraction result(num, den);
  result = reduce(result);
  result = negatives(result);
  result = reduce(result);
  return result;
}

Fraction Fraction::plus(Fraction that){
  // numerator + that numerator
  int lhsNum = numerator * that.denominator;
  int rhsNum = that.numerator * denominator;
  int num = lhsNum+rhsNum;
  int den = this->denominator * that.denominator;
  // reduce again
  Fraction result(num,den);
  result = reduce(result);
  result = negatives(result);
  result = reduce(result);
  return result;  
}

Fraction Fraction::minus(Fraction that){

  // numerator - that numerator
  // reduce again
  int lhsNum = numerator * that.denominator;
  int rhsNum = that.numerator * denominator;
  int num = lhsNum - rhsNum;
  int den = this->denominator * that.denominator;

  Fraction result(num, den);
  result = reduce(result);
  result = negatives(result);
  result = reduce(result);
  return result;
}

void Fraction::print(Fraction that)
{
  cout << toString(that.numerator, that.denominator) << " + " << toString(numerator, denominator) << " = " << improperFrac(plus(that)) << endl;
  
  cout << toString(that.numerator, that.denominator) << " - " << toString(numerator, denominator) << " = " << improperFrac(minus(that)) << endl;

  cout << toString(that.numerator, that.denominator) << " * " << toString(numerator, denominator) << " = " << improperFrac(times(that)) << endl;

  cout << toString(that.numerator, that.denominator) << " / " << toString(numerator, denominator) << " = " << improperFrac(by(that)) << endl;
    
}

string Fraction::improperFrac(Fraction that){
  if(that.numerator > that.denominator){
    improper = that.numerator / that.denominator;

    that.numerator = that.numerator % that.denominator;
    negatives(that);
    if( that.numerator < 0){
      improper *= -1;
      that.numerator *= -1;
    }
    return to_string(improper) + " " + toString(that.numerator, that.denominator);
  }
  else
    improper = 0;
  that = negatives(that);
  return toString(that.numerator, that.denominator);
}
int main(){
cout << "Please enter your first fraction" << endl;
string command;
getline(cin, command);
int numer1, denom1;
numer1 = stoi(command.substr(0, command.find('/')));
denom1 = stoi(command.substr(command.find('/') + 1));
  
cout << "Please enter your second fraction" << endl;
getline(cin, command);
int numer2, denom2;
numer2 = stoi(command.substr(0, command.find('/')));
denom2 = stoi(command.substr(command.find('/') + 1));
Fraction frac1(numer1, denom1);
Fraction frac2(numer2, denom2);

frac1.print(frac2);
}
