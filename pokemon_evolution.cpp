#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>

#include "types.h"
#include "moves.h"
#include "pokemon.h"
#include "battle.h"
#include "procreate.h"

bool compare(pokemon *first, pokemon *second)
{
  return first->get_losses()*(second->get_wins()+second->get_losses()) < second->get_losses()*(first->get_wins()+first->get_losses());
};

int main(int argc, char **argv)
{
  srand(time(NULL));
  const int n_pokemon=10000, n_moves=8*N_P_TYPES;
  pokemon *population[n_pokemon], *children[n_pokemon], *swap;
  float survival_probability[n_pokemon], survival_sum;
  bool survived[n_pokemon];
  int n_survivors;
  int mating_probability[n_pokemon], affinity=N_P_TYPES, mating_sum;
  int n_children, fertility=4;
  move *moves[n_moves],*move1,*move2,*move3,*move4;
  int i,j,k, q, primary_type, secondary_type;
  int max, best;
  int n_generations, iteration;
  int popstat[N_P_TYPES+1][N_P_TYPES+1],movestat[N_P_TYPES];
  bool outputall;
  FILE *output;
  char filename[20];
  if(argc==1)
    n_generations=1;
  if(argc>1)
    n_generations=atoi(argv[1]);
  

  for(i=0;i<n_moves;i++)
    {
      primary_type=i/8;
      switch(i%8)
	{
	default:
	  moves[i]= new move(ATTACK,primary_type,80,100,true);
	  break;
	case(1):
	  moves[i]= new move(ATTACK,primary_type,80,100,false);
	  break;
	case(2):
	  moves[i]= new move(ATTACK,primary_type,100,80,true);
	  break;
	case(3):
	  moves[i]= new move(ATTACK,primary_type,100,80,false);
	  break;
	case(4):
	  moves[i]= new move(ATTACK,primary_type,125,64,true);
	  break;
	case(5):
	  moves[i]= new move(ATTACK,primary_type,125,64,false);
	  break;
	case(6):
	  moves[i]= new move(ATTACK,primary_type,160,50,true);
	  break;
	case(7):
	  moves[i]= new move(ATTACK,primary_type,160,50,false);
	  break;
	}
    }
  //  for(i=0;i<n_moves;i++)
  // moves[i]->print();
  for(i=0;i<n_pokemon;i++)
    {      
      primary_type=rand()%N_P_TYPES;
      secondary_type=rand()%N_P_TYPES;
      if(primary_type==15)
      primary_type=16;
      if(secondary_type==15)
      secondary_type=16;
      q=rand()%8;
      move1=moves[primary_type*8+q];
      q=rand()%8;
      move2=moves[secondary_type*8+q];
      q=rand()%n_moves;
      move3=moves[q];
      q=rand()%n_moves;
      move4=moves[q];
      population[i] = new pokemon(primary_type,secondary_type,
				  125,125,125,125,125,125,
				  move1,move2,move3,move4);
    }
  for(iteration=0;iteration<n_generations;iteration++)
    {
      for(i=0;i<n_pokemon;i++)
	for(j=0;j<100;j++)
	  {
	    q=i;
	    while(q==i)
	      q=rand()%n_pokemon;
	    
	    pokemon_battle(population[i],population[q]);
	    //	printf("Still Working\n");
	    
	    if(population[i]->is_alive())
	      {
		population[i]->add_win();
		population[q]->add_loss();
	      }
	    else
	      {
		population[q]->add_win();
		population[i]->add_loss();
	      }
	    population[i]->heal();
	    population[q]->heal();
	  }

      std::sort(population, population+n_pokemon, compare);
      /*
      for(i=0;i<n_pokemon;i++)
	{
	  population[i]->print();
	  printf("%i %i\n",population[i]->get_wins(),population[i]->get_losses());
	}
      */
      /*
      survival_sum=0;
      for(i=0;i<n_pokemon;i++)
	{
	  survival_probability[i]=1/(1+exp(-1*(i-n_pokemon/fertility)/(n_pokemon/10)));
	  survival_sum+=survival_probability[i];
	}
      for(i=0;i<n_pokemon;i++)
	{
	  survival_probability[i]/=(survival_sum); //average value should be 1/fertility
	  survival_probability[i]*=n_pokemon;
	  survival_probability[i]/=fertility;
	}
      */
      n_survivors=0;
      
      for(i=0;i<n_pokemon;i++)
	{
	  survived[i]=false;
	  /*
	  if(double(rand())/RAND_MAX<survival_probability[i])
	    {
	      survived[i]=true;
	      n_survivors++;
	    }
	  */
	}
      
      if(n_survivors<n_pokemon/fertility)
	{
	  for(i=0;n_survivors<n_pokemon/fertility;i++)
	    if(survived[i]==false)
	      {
		survived[i]=true;
		n_survivors++;
	      }
	}
      /*
      if(n_survivors>n_pokemon/fertility)
	{
	  for(i=n_pokemon-1;n_survivors>n_pokemon/fertility;i--)
	    if(survived[i]==true)
	      {
		survived[i]=false;
		n_survivors--;
	      }
	}
      */
      /*
      for(i=0;i<n_pokemon;i++)
	{
	  if(survived[i])
	    printf("%f alive\n",survival_probability[i]);
	  else
      	    printf("%f dead\n",survival_probability[i]);
	}
      */
      n_children=0;
      for(i=0;i<n_pokemon;i++)
	{
	  if(survived[i])
	    {

	      primary_type=population[i]->get_primary();
	      secondary_type=population[i]->get_secondary();
	      mating_sum=0;
	      for(j=0;j<n_pokemon;j++)
		{
		  if(survived[j])
		    mating_probability[j]=1;
		  else
		    mating_probability[j]=0;
		  if(i==j)
		    mating_probability[j]=0;
		  if(primary_type==population[j]->get_primary() ||
		     primary_type==population[j]->get_secondary())
		    mating_probability[j]*=affinity;
		  if(secondary_type==population[j]->get_primary() ||
		     secondary_type==population[j]->get_secondary())
		    mating_probability[j]*=affinity;
		  mating_sum+=mating_probability[j];
		}

	      for(k=0;k<fertility;k++)
		{
		  q=rand()%mating_sum+1;
		  for(j=0;q>0;j++)
		    q-=mating_probability[j];
		  j--;
		  children[n_children]=procreate(population[i],population[j], iteration);
		  n_children++;
		}
	    }
	}
      for(i=0;i<N_P_TYPES+1;i++)
	for(j=0;j<N_P_TYPES+1;j++)
	  popstat[i][j]=0;
      for(i=0;i<n_pokemon;i++)
	{
	  popstat[population[i]->get_primary()][population[i]->get_secondary()]++;
	  popstat[population[i]->get_secondary()][population[i]->get_primary()]++;
	}

      for(i=0;i<N_P_TYPES;i++)
	movestat[i]=0;
      for(i=0;i<n_pokemon;i++)
	{
	  for(j=0;j<4;j++)
	    movestat[population[i]->get_moves()[j]->get_p_type()]++;
	}
      //printf("           Nor  Fir  Wat  Gra  Ele  Ice  Fig  Fly  Bug  Roc  Gro  Poi  Psy  Gho  Dar  Fai  Dra  Ste\n");
      printf("%i ", iteration);
      for(i=0;i<N_P_TYPES;i++)
	{
	  //printf("\n%10s ",P_TYPES[i]);
	  for(j=i+1;j<N_P_TYPES+1;j++)
	    printf("%4i ",popstat[i][j]);
	}
      //printf("\n           ");
      for(i=0;i<N_P_TYPES;i++)
	printf("%4i ",movestat[i]);
     printf("\n");
     outputall=false;
     for(i=0;i<N_P_TYPES;i++)
       for(j=i+1;j<N_P_TYPES;j++)
	 if(popstat[i][j]>n_pokemon/2)
	   outputall=true;
     if(outputall)
       {
	 sprintf(filename,"All_Pokemon_%i_%i.txt",iteration,n_generations);
	 output=fopen(filename,"w");
	 for(i=0;i<n_pokemon;i++)
	   {
	     population[i]->print(output);
	     fprintf(output,"%i %i\n\n",population[i]->get_wins(),population[i]->get_losses());
	   }
	 fclose(output);
       }

     for(i=0;i<n_pokemon;i++)
       delete(population[i]);
     for(i=0;i<n_pokemon;i++)
       population[i] = new pokemon(children[i]);
     for(i=0;i<n_pokemon;i++)
       delete(children[i]);
    
	  /*
      max=0;
      best=0;
      for(i=0;i<n_pokemon;i++)
	{
	  if(max<population[i]->get_losses())
	    {
	      max=population[i]->get_losses();
	      best=i;
	    }
	}
      population[best]->print();
      max=0;
      best=0;
      for(i=0;i<n_pokemon;i++)
	{
	  if(max<population[i]->get_wins())
	    {
	      max=population[i]->get_wins();
	      best=i;
	    }
	}
      population[best]->print();
      */

    }
  
  for(i=0;i<N_P_TYPES+1;i++)
    for(j=0;j<N_P_TYPES+1;j++)
      popstat[i][j]=0;
  for(i=0;i<n_pokemon;i++)
    {
      popstat[population[i]->get_primary()][population[i]->get_secondary()]++;
      popstat[population[i]->get_secondary()][population[i]->get_primary()]++;
    }
  
  for(i=0;i<N_P_TYPES;i++)
    movestat[i]=0;
  for(i=0;i<n_pokemon;i++)
    {
      for(j=0;j<4;j++)
	movestat[population[i]->get_moves()[j]->get_p_type()]++;
    }
  //printf("           Nor  Fir  Wat  Gra  Ele  Ice  Fig  Fly  Bug  Roc  Gro  Poi  Psy  Gho  Dar  Fai  Dra  Ste\n");
  printf("%i ", iteration);
  for(i=0;i<N_P_TYPES;i++)
    {
      //printf("\n%10s ",P_TYPES[i]);
      for(j=i+1;j<N_P_TYPES+1;j++)
	printf("%4i ",popstat[i][j]);
    }
  //printf("\n           ");
  for(i=0;i<N_P_TYPES;i++)
    printf("%4i ",movestat[i]);
  printf("\n");
  sprintf(filename,"Final_Pokemon_%i.txt",iteration,n_generations);
  output=fopen(filename,"w");
  for(i=0;i<n_pokemon;i++)
    {
      population[i]->print(output);
      fprintf(output,"%i %i\n\n",population[i]->get_wins(),population[i]->get_losses());
    }
  fclose(output);

  
  for(i=0;i<n_pokemon;i++)
    delete(population[i]);
  for(i=0;i<n_moves;i++)
    delete(moves[i]);

}
