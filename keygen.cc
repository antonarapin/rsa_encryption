#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ReallyLongInt.h"
#include "numberTheory.h"


using namespace std;
int main(int argc, char* argv[]){
	
	ReallyLongInt p = atoll(argv[1]);
	ReallyLongInt q = atoll(argv[2]);
	ofstream public_file(argv[3]);
	ofstream private_file(argv[4]);

	if(p>100000 || q>100000){
		cout<<" Numbers are too large. Primality is not being verified."<<endl;
	} else{
		if ((!isPrime(p)) || (!isPrime(q))){
			cout<<"Passed in numbers are not Prime."<<endl;
			return 1;
		}
	}

	ReallyLongInt n = p*q;

	if(n<256){
		cout<<"Passed in numbers are not big enough."<<endl;
		return 1;
	}

	ReallyLongInt t = (p-1)*(q-1);
	ReallyLongInt e = 2;
	bool e_found = false;
	ReallyLongInt x;
	ReallyLongInt y;
	while(!e_found && e<t){
		if (extendedEuclid(e,t,&x,&y)==1){
			e_found=true;
		} else{
			++e;
		}
	}
	
	ReallyLongInt d = x;
	if (d<0){
		d=d+t;
	}
	public_file<<e<<" "<<n<<endl;
	private_file<<d<<" "<<n<<endl;
	public_file.close();
	private_file.close();
	return 0;
}