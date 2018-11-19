#include <fstream>
#include <iostream>
#include "ReallyLongInt.h"
#include "numberTheory.h"

using namespace std;


int main(int argc, char* argv[]){
	ifstream fin(argv[1]);
	ReallyLongInt e;
	ReallyLongInt n;
	string tmp_e;
	string tmp_n;
	fin>>tmp_e;
	fin>>tmp_n;
	e=tmp_e;
	n=tmp_n;
	fin.close();
	ifstream txtin(argv[2]);
	ofstream encout(argv[3]);
	char c;
	while (txtin.get(c)){
		unsigned long long long_c =(unsigned long long)c;
		ReallyLongInt rlint_c = long_c;
		ReallyLongInt y=modPower(rlint_c,e,n);
		encout<<y<<"\n";
	}
	txtin.close();
	encout.close();
	return 0;
}