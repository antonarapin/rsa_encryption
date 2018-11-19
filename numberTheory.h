#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H
template <class X>
bool isPrime(const X& num){
	if (num==1 || num==0){
		return false;
	} else{
		if (num==2){
			return true;
		}
		X maxnum=(num/2);
		int i = 2;
		while (i<=maxnum){
			if (num % i ==0){
				return false;
			}
			if(i%2==0){
				i+=1;
			} else{
				i+=2;
			}
		}
		return true;
	}
}
template <class X>
X modPower(const X& base, const X& exponent, const X& modulus){
	if (exponent==1){
		return (base % modulus);
	} else if (exponent==0){
		return (1 % modulus);
	} else{
		X result;
		X halfexp;
		if (exponent % 2 == 0){
			halfexp=modPower(base,(exponent/2),modulus);
			result=(halfexp*halfexp)%modulus;
			return result;
		} else{
			halfexp=modPower(base,((exponent-1)/2),modulus);
			
			result=((((base*halfexp)%modulus)*halfexp)%modulus);
			return result;
		}
	}
}
template <class X>
X extendedEuclid(const X& a, const X& b, X* x, X* y){
	if (b==0){
		*x=1;
		*y=0;
		return a;
	} else{
		X xx;
		X yy;
		X result=extendedEuclid(b,(a%b),&xx,&yy);
		
		*x=yy;
		*y=(xx-yy*(a/b));

		return result;
		
	}
}


#endif
