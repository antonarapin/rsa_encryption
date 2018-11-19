#include <fstream>
#include <iostream>
#include "ReallyLongInt.h"
#include "numberTheory.h"



using namespace std;

int main(int argc, char* argv[]){
	ifstream fin(argv[1]);
	ReallyLongInt d;
	ReallyLongInt n;
	string tmp_d;
	string tmp_n;
	fin>>tmp_d;
	fin>>tmp_n;
	d=tmp_d;
	n=tmp_n;
	fin.close();
	ifstream encin(argv[2]);
	ofstream decout(argv[3]);
	ReallyLongInt y;
	string tmp_y;
	encin>>tmp_y;
	y=tmp_y;
	while (!encin.eof()){
		long long tmp_x = (modPower(y,d,n)).toLongLong();
		char x = (char)tmp_x;
		decout<<x;
		encin>>tmp_y;
		y=tmp_y;
	}
	encin.close();
	decout.close();
	return 0;
}