#include <iostream>
using namespace std;

void message(int);

int factorial(int);

int fib(int);

//Function prototype to demo
//gcd
int gcd(int, int);

int main(int argc, char **argv){
	int value = 10;
	//int num1, num2;
	/*
	Program to demonstrate a recursive 
	function to calculate the greatest 
	common divisor (gcd) of two numbers
	*/
	//cout << "Enter two integers ";
	//cin >> num1 >> num2;

	//Display the gcd of the two numbers
	//cout << "GCD of " << num1 << " and "
	//	 << num2 << " is:\n";
	//cout << gcd(num1, num2) << endl;

	//First, a very basic recursive function
	//message(value);
	//cout << "\nEntering factorial" << endl;
	//factorial(value);

	/*
	Program demonstrates a recursive function
	that calculates fibonacci nums
	Would be fun to compare this 
	to my non-recursive alg for proj euler
	*/
	cout << "The first 10 fibonacci nums: ";
	for(int x = 0; x < 10; x++)
		cout << fib(x) << " ";
	cout << endl;

	return 0;
}

int fib(int n){
	if(n <= 0)
		return 0;
	else if(n == 1)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

int gcd(int x, int y){
	if(x % y == 0)
		return y; //base case
	else 
		return gcd(y, x % y); //recursive case
}

int factorial(int n){
	int val;
	if(n == 0)
		return 1;//base case
	else{
		cout << endl << n << endl;
		val = n * factorial(n-1);
		//return n * factorial(n-1);//recursive case
	}
	cout << endl << n << endl;

	return val;
}

void message(int times){
	if(times > 0){
		cout << "This is a recursive function";
		cout << " " << times << endl;
		message(times - 1);
	}

	cout << "message returning with " << times;
	cout << " in times.\n";
}