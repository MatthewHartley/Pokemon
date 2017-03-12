#ifndef POKE_BATTLES
#define POKE_BATTLES

#include<stdlib.h>
#include"pokemon.h"
#include"moves.h"
#include"types.h"

void pokemon_battle(pokemon *pokemon1, pokemon *pokemon2)
{
  move **pokemon1moves=pokemon1->get_moves();
  move **pokemon2moves=pokemon2->get_moves();
  move *currentmove;
  int i, damage1[4], damage2[4], max, bestattack1, bestattack2;
  int speed1=pokemon1->get_speed(),speed2=pokemon2->get_speed();
  
  for(i=0;i<4;i++)
    {
      currentmove=pokemon1moves[i];
      if(currentmove->get_m_type()==ATTACK)
      {
	if(currentmove->is_physical())
	  damage1[i]=100*pokemon1->get_attack()/pokemon2->get_defense();
	else
	  damage1[i]=100*pokemon1->get_specialattack()/pokemon2->get_specialdefense();
	damage1[i]*=100*currentmove->get_power();
	damage1[i]/=currentmove->get_accuracy();
	
	if(currentmove->get_p_type()==pokemon1->get_primary() ||
	   currentmove->get_p_type()==pokemon1->get_secondary())
	  damage1[i]*=1.5;

	damage1[i]*=P_EFFECTIVENESS[currentmove->get_p_type()][pokemon2->get_primary()];
	damage1[i]*=P_EFFECTIVENESS[currentmove->get_p_type()][pokemon2->get_secondary()];
      }
      else
	damage1[i]=-1;
    }

  for(i=0;i<4;i++)
    {
      currentmove=pokemon2moves[i];
      if(currentmove->get_m_type()==ATTACK)
      {
	if(currentmove->is_physical())
	  damage2[i]=100*pokemon2->get_attack()/pokemon1->get_defense();
	else
	  damage2[i]=100*pokemon2->get_specialattack()/pokemon1->get_specialdefense();
	damage2[i]*=currentmove->get_accuracy()*currentmove->get_power();
 	
	if(currentmove->get_p_type()==pokemon2->get_primary() ||
	   currentmove->get_p_type()==pokemon2->get_secondary())
	  damage2[i]*=1.5;

	damage2[i]*=P_EFFECTIVENESS[currentmove->get_p_type()][pokemon1->get_primary()];
	damage2[i]*=P_EFFECTIVENESS[currentmove->get_p_type()][pokemon1->get_secondary()];
      }
      else
	damage2[i]=-1;
    }
  max=-1;
  for(i=0;i<4;i++)
    if(damage1[i]>max)
      {
	max=damage1[i];
	bestattack1=i;
      }
  //printf("firewater will use attack %i\n",bestattack1);
  max=-1;
  for(i=0;i<4;i++)
    if(damage2[i]>max)
      {
	max=damage2[i];
	bestattack2=i;
      }
  //printf("rock will use attack %i\n",bestattack2);
  while(pokemon1->is_alive() && pokemon2->is_alive())
    {
      if(speed1>speed2 || (speed1==speed2 && rand()%2))
	{
	  //	  printf("firewater moves first\n");
	  pokemon1->use_moves(bestattack1,pokemon2);
	  if(pokemon2->is_alive())
	    pokemon2->use_moves(bestattack2,pokemon1);
	}
      else
	{
	  //printf("rock moves first\n");
	  pokemon2->use_moves(bestattack2,pokemon1);
	  if(pokemon1->is_alive())
	    pokemon1->use_moves(bestattack1,pokemon2);
	}
    }
};
#endif
