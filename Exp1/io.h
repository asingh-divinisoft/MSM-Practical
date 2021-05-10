void get_data(char file_name[], double coeff[6], int n);
void write_data(char file_name[], double data[50][2], int n);
//reads n no of data points from the file file_name and stores in the array coeff
void get_data(char file_name[], double coeff[6], int n)
{
	int i = 0;
	FILE *fp;
	fp = fopen(file_name, "r"); //Openining the file for reading purpose
	for (i = 0; i <= 5; i = i + 1)
	{
		fscanf(fp, "%lf", &coeff[i]); //Reading the data from the file and storing
	}
	fclose(fp); //Closing the file opened
}

//writes n no of data points to the file file_name from the two dimensional array data
void write_data(char file_name[], double data[50][2], int n)
{
	int i = 0;
	FILE *fp;
	fp = fopen(file_name, "w"); //Openining the file for writing purpose
	for (i = 0; i < n; i = i + 1)
	{
		fprintf(fp, "%lf, %lf\n", data[i][0], data[i][1]); //Writing the data to the file
	}
	fclose(fp); //Closing the file opened
}
