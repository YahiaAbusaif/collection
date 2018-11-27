#include <bits/stdc++.h>
//Yahia Ali
//this code for solve Integration f(X1/M1)*f(X2/M2)... dx1dx2..., x1 from M1*start to M1*end and X2 from M2*start to M2*end ....
//using Simpson’s 1/3 formula with n=N where N is even number , maximum number of points =2147483646
double const infinte= 10e9; //define infinte for double numbers = 1000000000.0
double const zero=10e-6; //define zero for double numbers =0.000001

template<class T>
double Simpson1_3(double start,double end, int N,vector<double> M, T f) //complixty = O(N*F)+ O(M) where F complixty of f 
{
	if(N&1 || N<1) //if N is odd or negative stop  
		return infinte;
	double result=0.0; //final result of one Integration will store here
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
	result=result*h/3.0; // now result contain Integration from start to end >> I simp1/3
	double fin=1.0;
	for(int i=0;i<M.size();i++)
		fin*=result*M[i];
	return fin;
}
double func(double x) // test on f= ln(x)/sqrt(x) 
{
	if(x<=zero) //stop if input causes error (x is negative or zero)
		return infinte;
	return log(x)/sqrt(x);
}
int main()
{
	//test for start=1,end=2,n=8 and M1=1,M2=2 and f=func
	vector<double> Con;
	Con.push_back(1.0);
	Con.push_back(2.0);
	printf("%.10f",Simpson1_3(1.0,2.0,8,Con,func)); //print the result to 10 digit after fraction (.)
	//output:0.18441274016615306	
	return 0;
}
