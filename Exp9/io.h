void get_data(char file_name[], double coeff[50][3], int *n);
void write_data(char file_name[], double data[50], int n);
//reads n no of data points from the file file_name and stores in the array coeff
void get_data(char file_name[], double coeff[50][3], int *n)
{       int i=0;
        FILE *fp;
        fp=fopen(file_name,"r");   //Openining the file for reading purpose
        fscanf(fp, "%d", n);
        for(i=0; i<*n; ++i)
        {
                fscanf(fp,"%lf %lf %lf", &coeff[i][0], &coeff[i][1], &coeff[i][2]);  //Reading the data from the file and storing
        }
        fclose(fp);    //Closing the file opened
}

//writes n no of data points to the file file_name from the two dimensional array data
void write_data(char file_name[], double data[50], int n)
{
        int i=0;
        FILE *fp;
        fp=fopen(file_name,"w"); //Openining the file for writing purpose
        for(i=0;i<n;i++)
        {
                
                fprintf(fp,"%lf\n", data[i]); //Writing the data to the file
        }
        fclose(fp); //Closing the file opened
}
