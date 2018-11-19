#include "ReallyLongInt.h"
#include <iostream>
#include <cmath>


int main(int argc, char *argv[]){
	ReallyLongInt num(argv[1]);
	ReallyLongInt counter =1;
	ReallyLongInt result =1;
	while(counter!=(num+1)){
		result*=counter;
		counter+=1;
	}
	cout<<result<<endl;
}