#define max 100

void getdata(char filename[],double arr[20], int n)
{
    int i=0;
    FILE *fp;
    fp=fopen(filename,"r");
    for(i=0;i<n;i++)
        fscanf(fp,"%lf",&arr[i]);
    fclose(fp);

}

int getisog(char filename[], double left[][2], double right[][2], int n){
        double data[max][2], Tmax;
        FILE *fp;
        int idx=n, i, j;
        fp = fopen(filename, "r");
        for(i=0;i<n-1;i++)
        {
                fscanf(fp,"%lf\t%lf", &data[i][0], &data[i][1]);
        }

        //congruent maxima
                Tmax = data[0][1];
                idx = 0;
                for(i=0; i<n-1; i++){
                        if(data[i][1] > Tmax){
                                Tmax = data[i][1];
                                idx = i;
                        }
                }
                for(i=0; i<idx; i++){
                        left[i][0] = data[i][0];
                        left[i][1] = data[i][1];
                }
                for(i=idx, j=0; i<n-1; i++, j++){
                        right[j][0] = data[i][0];
                        right[j][1] = data[i][1];
                }
                

        return idx;
}

void writedata(char filename[],double data[][3],int n1)
{
    int i=0;
    FILE *fp;
    fp=fopen(filename,"w");
    for(i=0;i<n1-1;i++)
    {
        fprintf(fp,"%lf\t\t%lf\t%lf", data[i][0], data[i][1], data[i][2]);
        fprintf(fp,"\n");
    }

    fclose(fp);

}
