void getdata(char filename[],double arr[20], int n)
{
    int i=0;
    FILE *fp;
    fp=fopen(filename,"r");
    for(i=0;i<n;i++)
        fscanf(fp,"%lf",&arr[i]);
    fclose(fp);
}

void writedata(char filename[],double data[20][20],int ar, int ac)
{
    int i=0, j=0;
    FILE *fp;
    fp=fopen(filename,"w");
    for(i=0;i<ar;i++)
    {
	for(j=0; j<ac; j++ ){
        	fprintf(fp,"%lf ", data[i][j]);
	}
        fprintf(fp,"\n");
    }

    fclose(fp);

}
