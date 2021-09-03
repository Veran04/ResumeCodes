#include <stdio.h>                  /*  Marr-Hildreth.c  (or marrh.c) */
#include <math.h>
#include <string.h>
#define  PICSIZE 256
#define  MAXMASK 100

         int    pic[PICSIZE][PICSIZE];
         double outpic1[PICSIZE][PICSIZE];
         double outpic2[PICSIZE][PICSIZE];
         double cand[PICSIZE][PICSIZE];
         int Histogram[255];
         double candTemp[PICSIZE][PICSIZE];
         double final[PICSIZE][PICSIZE];
         int    edgeflag[PICSIZE][PICSIZE];
         double maskx[MAXMASK][MAXMASK];
         double masky[MAXMASK][MAXMASK];
         double conv[PICSIZE][PICSIZE];

main(argc,argv)
int argc;
char **argv;
{
        int     i,j,p,q,s,t,mr,centx,centy;
        double ival[PICSIZE][PICSIZE];
        double ival1[PICSIZE][PICSIZE];
        double  maskval, cutoff, sum1, sum2, sig, maxival,minival,maxval,ZEROTOL, slope, HiThresh, LoThresh;
        FILE    *fo1, *fo2, *fo3, *fp1, *fopen();
        char    *foobar;
        char sigString[PICSIZE];
        char percentString[PICSIZE];
        int moretodo=1;
        int Histosize;
        double percent = .005;
        int AreaofTops = 0;
        printf("\nfile name for input:");
        scanf(" %s", pic);
        if((fp1=fopen(pic, "rb"))==NULL) printf("can't open input file.\n");

	      printf("\nfile name for magnitude:");
        scanf(" %s", pic);
        if((fo1=fopen(pic, "wb"))==NULL) printf("can't open output file.\n");

        printf("\nfile name for peaks:");
        scanf(" %s", pic);
        if((fo2=fopen(pic, "wb"))==NULL) printf("can't open output file.\n");

        printf("\nfile name for finalEdges:");
        scanf(" %s", pic);
        if((fo3=fopen(pic, "wb"))==NULL) printf("can't open output file.\n");

        printf("\nWhat is the sigma value?");
        scanf(" %s", sigString);
        sig = atoi(sigString);

     
        
        

        fprintf(fo1, "P5\n");
        fprintf(fo1, "%d %d\n", 256, 256);
        fprintf(fo1, "255\n");
        fprintf(fo2, "P5\n");
        fprintf(fo2, "%d %d\n", 256, 256);
        fprintf(fo2, "255\n");
        fprintf(fo3, "P5\n");
        fprintf(fo3, "%d %d\n", 256, 256);
        fprintf(fo3, "255\n");

        
        mr = (int)(sig * 3);
        centx = (MAXMASK / 2);
        centy = (MAXMASK / 2);

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
                {
                  pic[i][j]  =  getc (fp1);
                }
        }

        for (p=-mr;p<=mr;p++)
        {  for (q=-mr;q<=mr;q++)
           {
              maskval = ((-q)*(exp(-1*(((p*p)+(q*q))/(2*(sig*sig))))));
              (maskx[p+centy][q+centx]) = maskval;
              maskval = ((-p)*(exp(-1*(((p*p)+(q*q))/(2*(sig*sig))))));
              (masky[p+centy][q+centx]) = maskval;
           }
        }

        for (i=mr;i<=255-mr;i++)
        { for (j=mr;j<=255-mr;j++)
          {
             sum1 = 0;
             sum2 = 0;
             for (p=-mr;p<=mr;p++)
             {
                for (q=-mr;q<=mr;q++)
                {
                   sum1 += pic[i+p][j+q] * maskx[p+centy][q+centx];
                   sum2 += pic[i+p][j+q] * masky[p+centy][q+centx];
                }
             }
             outpic1[i][j] = sum1;
             outpic2[i][j] = sum2;                                     
             
          }
        }

        maxval  = 0;
        maxival = 0;
        minival = 255;

        for (i=mr;i<256-mr;i++)
        { for (j=mr;j<256-mr;j++)
          {
          ival[i][j]=sqrt((double)((outpic1[i][j]*outpic1[i][j]) +
                                      (outpic2[i][j]*outpic2[i][j])));
          ival1[i][j]=sqrt((double)((outpic1[i][j]*outpic1[i][j]) +
                                      (outpic2[i][j]*outpic2[i][j])));
                                      if (ival[i][j] > maxival)
                                      {
                                        maxival = ival[i][j];
                                      }
                                     
          }
        }
        if (fabs(maxival) > fabs(minival))
           maxval = fabs(maxival);
        else
           maxval = fabs(minival);

        for (i=0;i<256;i++)
        { for (j=0;j<256;j++)
          {
             ival[i][j] = (ival[i][j] / maxival) * 255;
             //outpic1[i][j] = ((((outpic1[i][j]) / maxval) + 1) * 127);
             fprintf(fo1,"%c",(char)((int)(ival[i][j])));
          }
        }


        //outpic2 (cannypeaks)
        for (i=mr;i<=255-mr;i++)
        {  for (j=mr;j<=255-mr;j++)
           {
              
             cand[i][j] = 0;            
             if (outpic1[i][j] ==0.0 ) 
             {
               outpic1[i][j] = .00001;
             }
             slope = outpic2[i][j] / outpic1[i][j]; 
             if((slope <= .4142) && (slope > -.4142)) {
               if((ival[i][j] > ival[i][j-1]) && (ival[i][j] > ival[i][j+1])) {
                 cand[i][j] = 255;
               }
             }

             else if((slope <= 2.4142) && (slope > .4142)) {
               if((ival[i][j] > ival[i-1][j-1]) && (ival[i][j] > ival[i+1][j+1])) {
                 cand[i][j] = 255;
               }
             }

             else if((slope <= -.4142) && (slope > -2.4142)) {
               if((ival[i][j] > ival[i+1][j-1]) && (ival[i][j] > ival[i-1][j+1])) {
                 cand[i][j] = 255;
               }
             }

             else{
               if((ival[i][j] > ival[i-1][j]) && (ival[i][j] > ival[i+1][j])) {
                 cand[i][j] = 255;
               }
             }
           }
        }
/*
  for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
              Histogram[i] = 0;
            }
          }
          */
         
          
  for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
              //(Histogram[(int)ival[i][j]])++;
              Histogram[i] = 5;
            }
          }
          
    
  cutoff = percent*256*256;
  for(i=256; i>=1; i--){
    AreaofTops += Histogram[i];
    
    if(AreaofTops > cutoff){
      
      break;
    }
  }
  HiThresh = i;
  LoThresh = .15 * i;

  for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
              
              candTemp[i][j] = cand[i][j];
              final[i][j] = 0;
              if(cand[i][j] == 255){
                if(ival[i][j] > HiThresh){
                  
                  cand[i][j] = 0;
                  final[i][j] = 255;
                  
                }
                else if(ival[i][j] < LoThresh){
                  //printf("/n here3");
                  cand[i][j]=0;
                  final[i][j]=0;
                  //printf("/n here4");
                }
              }
            }
          }
  while(moretodo == 1){
    moretodo = 0;
    for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
              if(cand[i][j] == 255){
                for(p=-1; p<=1; p++){
                  for(q=-1; q<=1; q++){
                    if(final[i+p][j+q] == 255){
                      cand[i][j] = 0;
                      final[i][j] = 255;
                      moretodo = 1;
                    }
                  }
                }
              }
            }
          }
  } 
  for (i=0;i<256;i++)
          { for (j=0;j<256;j++)
            {
                     
             fprintf(fo1,"%c",(char)((int)(ival[i][j])));
             fprintf(fo2,"%c",(char)((int)(candTemp[i][j])));
             fprintf(fo3,"%c",(char)((int)(final[i][j])));
            }
          }
          fclose(fo1);
          fclose(fo2);
          fclose(fo3);
}

