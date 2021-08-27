#include <stdio.h>                          /* Sobel.c */
#include <math.h>

        int pic[256][256];
        int outpicx[256][256];
        int outpicy[256][256];
        int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        double ival[256][256];
        double ival1[256][256];
        double ival2[256][256];
        int maxival;

main(argc,argv)
int argc;
char **argv;
{
        int i,j,p,q,mr,sum1,sum2;
        char thresholdString[256];
        char thresholdString1[256];
        int thresholdLow, thresholdHigh;
        FILE *fo1, *fo2, *fo3, *fp1, *fopen();
        char *foobar;

        printf("\nfile name for input:");
        scanf(" %s", pic);
        if((fp1=fopen(pic, "rb"))==NULL) printf("can't open input file.\n");

	      printf("\nfile name for first output:");
        scanf(" %s", pic);
        if((fo1=fopen(pic, "wb"))==NULL) printf("can't open output file.\n");

        printf("\nfile name for second output:");
        scanf(" %s", pic);
        if((fo2=fopen(pic, "wb"))==NULL) printf("can't open output file.\n");

        printf("\nfile name for third output:");
        scanf(" %s", pic);
        if((fo3=fopen(pic, "wb"))==NULL) printf("can't open output file.\n");

        
        

        printf("\nWhat is the lower threshold?(Integer)");
        
        scanf(" %s", thresholdString);
       
        thresholdLow = atoi(thresholdString);

        printf("\nWhat is the higher threshold?(Integer)");
        
        scanf(" %s", thresholdString1);
        thresholdHigh = atoi(thresholdString1);

     

        fprintf(fo1, "P5\n");
        fprintf(fo1, "%d %d\n", 256, 256);
        fprintf(fo1, "255\n");
        fprintf(fo2, "P5\n");
        fprintf(fo2, "%d %d\n", 256, 256);
        fprintf(fo2, "255\n");
        fprintf(fo3, "P5\n");
        fprintf(fo3, "%d %d\n", 256, 256);
        fprintf(fo3, "255\n");
        
      

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                  pic[i][j]  &= 0377;
                }
        }

        mr = 1;
        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             sum1 = 0;
             sum2 = 0;
             for (p=-mr;p<=mr;p++)
             {
                for (q=-mr;q<=mr;q++)
                {
                   sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
                   sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
                }
             }
             outpicx[i][j] = sum1;
             outpicy[i][j] = sum2;
          }
        }


                //this I will copy paste and need to edit out the magnitude function to instead compare to a threshold and either mark ival[i][j] as 0 or 255
        maxival = 0;
        int maxivalLow = 0;
        int maxivalHigh = 0;
        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
             ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                      (outpicy[i][j]*outpicy[i][j])));
             ival1[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                      (outpicy[i][j]*outpicy[i][j])));
             ival2[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                      (outpicy[i][j]*outpicy[i][j])));
             if(ival[i][j] <= thresholdLow)
                ival[i][j] = 0;
             else if(ival[i][j] > thresholdLow)
                ival[i][j] = 255;
             if (ival1[i][j] > maxival){
                maxival = ival1[i][j];
             }
             if(ival2[i][j] <= thresholdHigh)
                ival2[i][j] = 0;
             else if(ival2[i][j] > thresholdHigh)
                ival2[i][j] = 255;

             
             maxivalLow = 255;
             maxivalHigh = 255;

           }
        }


        //this function I will copy paste and edit. No changes need to be made except for the file pointer.
        for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
             ival[i][j] = (ival[i][j] / maxivalLow) * 255;
             ival1[i][j] = (ival1[i][j] / maxival) * 255;
             ival2[i][j] = (ival2[i][j] / maxivalHigh) * 255;             
             fprintf(fo1,"%c",(char)((int)(ival[i][j])));
             fprintf(fo2,"%c",(char)((int)(ival1[i][j])));
             fprintf(fo3,"%c",(char)((int)(ival2[i][j])));
            }
          }
          fclose(fo1);
          fclose(fo2);
          fclose(fo3);
}
