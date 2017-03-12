#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types.h"
int main (int argc, char **argv)
{
  int i, type1=-1, type2=-1;
  double damagemodifier;
  if (argc>1 && argc<4)
    {
      for(i=0;i<N_P_TYPES;i++)
	if(strcmp(argv[1],P_TYPES[i])==0)
	  type1=i;
      if(argc==3)
	{
	for(i=0;i<N_P_TYPES;i++)
	  if(strcmp(argv[2],P_TYPES[i])==0)
	    type2=i;
	}
      else
	type2=N_P_TYPES; 
      if(type1==-1 || (type2==-1 && argc==2))
	printf("please give one or two valid types\n");
      else
	{
	  printf("Type effectiveness against %s %s type pokemon:\n",P_TYPES[type1],P_TYPES[type2]);
	  printf("nor fir wat gra ele ice fig fly bug roc gro poi psy gho dar fai dra ste\n");
	  for(i=0;i<N_P_TYPES;i++)
	    {
	      damagemodifier=P_EFFECTIVENESS[i][type1]*P_EFFECTIVENESS[i][type2];
	      if(damagemodifier==1)
		printf(" 1  ");
	      if(damagemodifier==2)
		printf(" 2  ");
	      if(damagemodifier==4)
		printf(" 4  ");
	      if(damagemodifier==0)
		printf(" 0  ");
	      if(damagemodifier==.5)
		printf(".5  ");
	      if(damagemodifier==.25)
		printf(".25 ");


	    }
	  printf("\n");
	}
    }
    //  for(i=0;i<ntypes;i++)
    //printf("%s\n",types[i]);
}
