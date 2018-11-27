#include <bits/stdc++.h>
//Cairo University Faculty of Engineering Computer Engineering Department MTH 325 
//Numerical Analysis semester Fall 2018
//name Yahia Ali Sec:2 BN:32
//problem 3.17
//this code for solve Integration (ln(x)*ln(y/M))/(sqrt(x*y/M)) dxdy, x from start to end and y from M*start to M*end >>> Integration f(x)*f(y/M) dxdy 
//using Simpson’s 1/3 formula with n=N where N is even number
double const infinte= 10e9; //define infinte for double numbers = 1000000000.0
double const zero=10e-6; //define zero for double numbers =0.000001
double func(double x) // our f= ln(x)/sqrt(x) in this problem
{
	if(x<=zero) //stop if input causes error (x is negative or zero)
		return infinte;
	return log(x)/sqrt(x);
}
template<class T>
double solve(double start,double end, int N,double M, T f)
{
	if(N&1 || N<1) //if N is odd or negative stop  
		return infinte;
	double result=0.0; //final result will store here
	double sumeven=0.0; // summation of all f(x) with even index 
	double sumodd=0.0; // summation of all f(x) with odd index, first and last index (1,N+1) didn't include
	double h=(end-start)/double(N); //calculate h
	double x=start+h; //store current x
	for(int index=2;index<=N;index++) //start from index 2 to index N
	{
		if(index&1) //if index is odd add f(x) to sumodd
			sumodd+=f(x);
		else //else add f(x) to sumeven
			sumeven+=f(x);
		x+=h; //increase x by h
	}
	result=f(start)+(4.0*sumeven)+(2.0*sumodd)+f(end);
	result=result*h/3.0; // now result contain Integration = (ln(x)/sqrt(x))dx from start to end >> I simp1/3
	result= (result*result)*M; //calculate M* (I simp1/3)^2
	return result;
}
int main()
{
	//test for start=1,end=2,n=8 and M=2 and f=func
	printf("%.10f",solve(1.0,2.0,8,2.0,func)); //print the result to 10 digit after fraction (.)
	//result:0.18441274016615306	
	return 0;
}


