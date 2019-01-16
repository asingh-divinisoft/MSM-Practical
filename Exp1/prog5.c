/*C Program to calculate Gibbs energy of alpha and beta phases for Sc-Zr system at xB=0.6 and T=1500K */
#include<stdio.h>
#include<math.h>
#include "io.h"
#include "calGmix.h" //including user defined header file
#define R 8.3144 //defining R as global variable
int main() {
	//define and initiate variables
	double Gmix=0.0;
	double T = 1500.0;
	double xB=0;
	char inputFileName[]="inputData_beta.txt"; //file name to read input data
	char outputFileName[]="outputData_beta.txt"; //file name to write output data
	double a_set[6]; //to store the r-k polynomial data
	
	//get data from the file
	double interval = 0;
	printf("Enter the interval size: ");
	scanf("%lf", &interval); //get interval size form user
	
	printf("Enter the Temperature: ");
	scanf("%lf", &T);  //get Temperature from user

	int size = 1 / interval;
	double output[size][2]; //for storing output data

	get_data(inputFileName,a_set,6); //ref to the header file for details
	
	//Write data to the file
	int i = 0;
	for(i=0; i<size; i++){
		xB += interval;
		Gmix = g_mix(a_set,T,xB);
		output[i][0]=xB;
		output[i][1]= Gmix;
		//Print result to the screen
		printf("Gibbs energy of beta phase at T=%lf and xB=%lf is %lf J/mol\n",T,xB,Gmix);
	}
	write_data(outputFileName, output,size);

	return 0;
}
