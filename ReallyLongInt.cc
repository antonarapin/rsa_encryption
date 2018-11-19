#include "ReallyLongInt.h"

#include <cmath>
#include <string>
#include <iostream>
#include <climits>
#include <stdlib.h>  
ReallyLongInt::ReallyLongInt(){
	isNeg=false;
	unsigned int* int_array = new unsigned int[1];
	int_array[0]=0;
	digits=int_array;
	numDigits=1;
}
ReallyLongInt::ReallyLongInt(long long num){
	if (num<0){
		isNeg=true;
		num = num*(-1);
	} else{
		isNeg=false;
	}
	int sz=1+(int)(log10(num));
	long long tmp_num=num;
	long long current_factor=1;
	if (num==0){
		sz=1;
	}
	numDigits=sz;
	unsigned int* int_array = new unsigned int[sz+1];
	for (int i=1; i<=sz;i++){
		current_factor=current_factor*10;
		long long mod_num=(tmp_num%current_factor)/(current_factor/10);
		int_array[sz-i]=(int)(mod_num);
		tmp_num=tmp_num-mod_num;
	}
	
	digits=int_array;
}
void ReallyLongInt::removeLeadingZeros(unsigned* x, unsigned& xSize){
	bool done=false;
	while(!done){
		if (xSize==1){
			done=true;
		} else if(x[0]==0){
			for(int i=0; i<(xSize-1); i++){
				x[i]=x[i+1];
			}
			--xSize;
		} else{
			done=true;
		}
	}
}
ReallyLongInt::ReallyLongInt(const string& numString){
	int string_size = numString.size();
	numDigits = string_size;
	unsigned int* int_array = new unsigned int[string_size+1];
	int i=0;
	char c=numString[0];
	if (c=='-'){
		isNeg=true;
		i=1;
		int_array[0]=0;
	} else{
		isNeg=false;
	}
	
	for (i; i<string_size; i++){
		c=numString[i];
		int_array[i]=atoi(&c);
	}
	ReallyLongInt::removeLeadingZeros(int_array, numDigits);
	if (numDigits==1 && int_array[0]==0){
		isNeg=false;
	}
	digits=int_array;
}
ReallyLongInt::~ReallyLongInt(){
	delete[] digits;
}
ostream& ReallyLongInt::print(ostream& out) const{
	if (isNeg){
		out<<"-";
	}
	for (int i=0;i<numDigits;i++){
		out<<digits[i];
	}
	return out;
}
ostream& operator<<(ostream& out, const ReallyLongInt& x){
	x.print(out);
	return out;
}
void ReallyLongInt::swap(ReallyLongInt other){
	std::swap(this->digits,other.digits);
	std::swap(this->isNeg,other.isNeg);
	std::swap(this->numDigits,other.numDigits);

}
ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other){
	swap(other);
	return *this;
}
ReallyLongInt::ReallyLongInt(const ReallyLongInt& other){
	numDigits=other.numDigits;
	isNeg=other.isNeg;
	unsigned int* int_array = new unsigned int[numDigits+1];

	for (int i=0; i<numDigits;i++){
		int_array[i]=other.digits[i];
	}
	digits=int_array;
}
ReallyLongInt::ReallyLongInt(unsigned* digitArr, unsigned arrSize, bool isNeg){
	removeLeadingZeros(digitArr,arrSize);
	this->digits = digitArr;
	this->numDigits = arrSize;
	if (digitArr[0]==0){
		this->isNeg=false;
	} else{
		this->isNeg = isNeg;
	}
}
bool ReallyLongInt::equal(const ReallyLongInt& other) const{
	if(this->numDigits!=other.numDigits){
		return false;
	} else if(this->isNeg!=other.isNeg){
		return false;
	} else{
		for (int i=0;i<other.numDigits;i++){
			if (this->digits[i]!=other.digits[i]){
				return false;
			}
		}
		return true;
	}
}
bool ReallyLongInt::absGreater(const ReallyLongInt& other) const{
	if(this->numDigits<other.numDigits){
		return false;
	} else if(this->numDigits>other.numDigits){
		return true;
	} /*else if(this->equal(other)){
		return false;
	}*/ else{
		for (int i=0;i<other.numDigits;i++){
			if(this->digits[i]<other.digits[i]){
				return false;
			} else if(this->digits[i]>other.digits[i]){
				return true;
			} else{
				if(i==other.numDigits-1){
					return false;
				}
			}
		}
	}
}
bool ReallyLongInt::greater(const ReallyLongInt& other) const{
	if(this->isNeg && !other.isNeg){
		return false;
	} else if(!this->isNeg && other.isNeg){
		return true;
	} else if(this->isNeg && other.isNeg){
		return !this->absGreater(other);
	} else{
		return this->absGreater(other);
	}
}
bool operator==(const ReallyLongInt& x, const ReallyLongInt& y){
	return x.equal(y);
}
bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y){
	return !x.equal(y);
}
bool operator>(const ReallyLongInt& x, const ReallyLongInt& y){
	return x.greater(y);
}
bool operator<(const ReallyLongInt& x, const ReallyLongInt& y){
	return !x.greater(y) && !x.equal(y);
}
bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y){
	return (x.greater(y) || x.equal(y));
}
bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y){
	return (!x.greater(y) || x.equal(y));
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const{
	int numD;
	if(this->numDigits==other.numDigits){
		numD=this->numDigits+1;
	} else if(this->numDigits>other.numDigits){
		numD=this->numDigits+1;
	} else{
		numD=other.numDigits+1;
	}
	unsigned int* int_array = new unsigned int[numD];
	for(int ii=0;ii<numD;ii++){
		int_array[ii]=0;
	}
	int res;
	for (int i =1; i <(numD); i++){
		if(i>(this->numDigits) && i>(other.numDigits)){
			res=0;
		} else if(i>(this->numDigits)){
			res=other.digits[other.numDigits-i];
		} else if(i>(other.numDigits)){
			res=this->digits[this->numDigits-i];
		} else{
			res=this->digits[this->numDigits-i]+other.digits[other.numDigits-i];
		}
		int_array[numD-i]=int_array[numD-i]+res;
		if(int_array[numD-i]>=10){
			int_array[numD-i]=int_array[numD-i]-10;
			int_array[numD-i-1]=int_array[numD-i-1]+1;
		}
	}

	return ReallyLongInt(int_array,numD,false);
}
ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const{
	bool neg_sign;
	const ReallyLongInt* bigger;
	const ReallyLongInt* smaller;
	if (this->absGreater(other)){
		bigger=this;
		smaller=&other;
		neg_sign=false;
	} else{
		bigger=&other;
		smaller=this;
		neg_sign=true;
	}

	int numD;
	
	numD=bigger->numDigits;
	
	unsigned int* int_array = new unsigned int[numD];
	for(int ii=0;ii<numD;ii++){
		int_array[ii]=0;
	}
	int i = bigger->numDigits - smaller->numDigits;
	int diff=i;
	int res;
	for (int j=0; j<i; j++){
		int_array[j] = bigger->digits[j];
	}
	for(i; i<numD; i++){
		if (smaller->digits[i-diff]>(bigger->digits[i])){
			
			int jj=i-1;
			while(int_array[jj]==0){
				jj=jj-1;				
			}
			int_array[jj]=int_array[jj]-1;
			int jjj=jj+1;
			while(jjj<i){
				int_array[jjj]=int_array[jjj]+9;
				jjj=jjj+1;
			}
			res=10+(bigger->digits[i])-smaller->digits[i-diff];
		} else{
			res=(bigger->digits[i])-smaller->digits[i-diff];
		}

		int_array[i]=int_array[i]+res;
	}
	return ReallyLongInt(int_array,numD,neg_sign);

}
void ReallyLongInt::flipSign(){
	if (this->digits[0]==0){
		this->isNeg=false;
	} else{
		this->isNeg=!this->isNeg;
	}
}
ReallyLongInt ReallyLongInt::operator-() const{
	ReallyLongInt newone(*this);
	
	newone.flipSign();
	return newone;
}
ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const{
	if (this->isNegative() && other.isNegative()){
		ReallyLongInt res = (this->absAdd(other));
		res.flipSign();
		return res;
	} else if(!this->isNegative() && other.isNegative()){
		return (this->absSub(other));
	} else if(this->isNegative() && !other.isNegative()){
		ReallyLongInt res = (this->absSub(other));
		res.flipSign();
		return res;
	} else{
		return (this->absAdd(other));
	}
}
ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const{
	if (this->isNegative() && other.isNegative()){
		ReallyLongInt res = (this->absSub(other));
		res.flipSign();
		return res;
	} else if(!this->isNegative() && other.isNegative()){
		return (this->absAdd(other));
	} else if(this->isNegative() && !other.isNegative()){
		ReallyLongInt res = this->absAdd(other);
		res.flipSign();
		return res;
	} else{
		return (this->absSub(other));
	}
}
ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y){
	return x.add(y);
}
ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y){
	return x.sub(y);
}
ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other){
	*this = *this+other;
	return *this;
}
ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other){
	*this = *this-other;
	return *this;
}
ReallyLongInt& ReallyLongInt::operator++(){
	*this+=1;
	return *this;
}
ReallyLongInt& ReallyLongInt::operator--(){
	*this-=1;
	return *this;
}
ReallyLongInt ReallyLongInt::operator++(int dummy){
	ReallyLongInt tmp(*this);
	*this+=1;
	return tmp;
}
ReallyLongInt ReallyLongInt::operator--(int dummy){
	ReallyLongInt tmp(*this);
	*this-=1;
	return tmp;
}
ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const{
	int numD=this->numDigits + other.numDigits;
	unsigned int* int_array = new unsigned int[numD];
	for(int i=0; i<numD;i++){
		int_array[i]=0;
	}
	int c;
	int d;
	int s;
	for (int i =0; i<(this->numDigits);i++){
		c=0;
		for (int j=0; j<(other.numDigits); j++){
			d=numD-i-j-1;
			s=int_array[d]+(this->digits[(this->numDigits)-1-i])*(other.digits[(other.numDigits)-1-j])+c;
			int_array[d]=s%10;
			c=(s/10);
		}
		int_array[(this->numDigits)-i-1]=int_array[this->numDigits-1-i]+c;
	}

	return ReallyLongInt(int_array,numD,false);
}
ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const{
	if (this->isNegative() == other.isNegative()){
		return (this->absMult(other));
	} else{
		ReallyLongInt res = (this->absMult(other));
		res.flipSign();
		return res;
	}
}
ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y){
	return (x.mult(y));
}
ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other){
	*this = *this * other;
	return *this;
}
void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const{
	remainder = 0;
	int d;
	unsigned int* int_array_q = new unsigned int[this->numDigits];
	for (int i=0; i<(this->numDigits); i++){
		remainder = remainder*10;
		remainder += this->digits[i];
		d=0;
		ReallyLongInt tmp_int(other);
		tmp_int.flipSign();
		while (remainder.absGreater(other) || (remainder.equal(other) || remainder.equal(tmp_int))){
			remainder = remainder.absSub(other);
			d=d+1;
		}
		int_array_q[i] = d;
	}
	quotient = ReallyLongInt(int_array_q,this->numDigits,false);
}
void ReallyLongInt::div(const ReallyLongInt& denominator, ReallyLongInt& quotient, ReallyLongInt& remainder) const{
	if(this->isNegative()==denominator.isNegative()){
		this->absDiv(denominator,quotient,remainder);
	} else if(this->isNegative()){
		this->absDiv(denominator,quotient,remainder);
		quotient.flipSign();
		remainder.flipSign();
	} else{
		this->absDiv((-denominator),quotient,remainder);
		quotient.flipSign();
	}
}
ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y){
	ReallyLongInt q;
	ReallyLongInt r;
	x.div(y,q,r);
	return q;
}
ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y){
	ReallyLongInt q;
	ReallyLongInt r;
	x.div(y,q,r);
	return r;
}
ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other){
	ReallyLongInt q;
	ReallyLongInt r;
	div(other,q,r);
	*this=q;
	return *this;
}
ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other){
	ReallyLongInt q;
	ReallyLongInt r;
	div(other,q,r);
	*this=r;
	return *this;
}
long long ReallyLongInt::toLongLong() const{
	ReallyLongInt longestlong(LLONG_MAX);
	longestlong+=1;
	ReallyLongInt result_rlint((*this)%longestlong);
	long long result=0;
	for(int i =0; i<(result_rlint.numDigits); i++){
		long long tmp_num=1;
		for (int j=0; j< (result_rlint.numDigits-1 - i);j++){
			tmp_num*=10;
		}
		result+=result_rlint.digits[i]*tmp_num;
		//result+=result_rlint.digits[i]*pow (10,(result_rlint.numDigits-1 - i));
	}
	if(result_rlint.isNegative()){
		result*=(-1);
	}
	return result;
}





