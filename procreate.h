#ifndef POKE_EVOLUTION
#define POKE_EVOLUTION

#include "types.h"

pokemon* procreate(pokemon *mom, pokemon *dad, int iteration)
{
  int base_stat_total=750, max_stat=300;
  int primary_type, secondary_type;
  int hp,att,def,spatt,spdef,speed;
  int q=rand()%64;
  if(q%2)
    att=(mom->get_attack()-5)/2;
  else
    att=(dad->get_attack()-5)/2;
  if((q%4)/2)
    def=(mom->get_defense()-5)/2;
  else
    def=(dad->get_defense()-5)/2;
  if((q%8)/4)
    def=(mom->get_defense()-5)/2;
  else
    def=(dad->get_defense()-5)/2;
  if((q%16)/8)
    spatt=(mom->get_specialattack()-5)/2;
  else
    spatt=(dad->get_specialattack()-5)/2;
  if((q%32)/16)
    spdef=(mom->get_specialdefense()-5)/2;
  else
    spdef=(dad->get_specialdefense()-5)/2;
  if(q/32)
    speed=(mom->get_speed()-5)/2;
  else
    speed=(dad->get_speed()-5)/2;
  
  
  q=rand()%21-10;
  att+=q;
  if(att<0)
    att=0;
  else if(att>max_stat)
    att=max_stat;
  q=rand()%21-10;
  def+=q;
  if(def<0)
    def=0;
  else if(def>max_stat)
    def=max_stat;
  q=rand()%21-10;
  spatt+=q;
  if(spatt<0)
    spatt=0;
  else if(spatt>max_stat)
    spatt=max_stat;
  q=rand()%21-10;
  spdef+=q;
  if(spdef<0)
    spdef=0;
  else if(spdef>max_stat)
    spdef=max_stat;
  q=rand()%21-10;
  speed+=q;
  if(speed<0)
    speed=0;
  else if(speed>max_stat)
    speed=max_stat;
  
  hp=base_stat_total-speed-att-def-spatt-spdef;
  if(hp<0)
    {
      hp=base_stat_total-hp;
      att*=base_stat_total;
      def*=base_stat_total;
      spatt*=base_stat_total;
      spdef*=base_stat_total;
      speed*=base_stat_total;
      att/=hp;
      def/=hp;
      spatt/=hp;
      spdef/=hp;
      speed/=hp;
      hp=base_stat_total-att-def-spatt-spdef-speed;
    }
  if(hp>max_stat)
    {
      //printf("%i %i\n",hp, att+def+spatt+spdef+speed);
      hp=5*max_stat-base_stat_total+hp;
      
      att=max_stat-att;
      def=max_stat-def;
      spatt=max_stat-spatt;
      spdef=max_stat-spdef;
      speed=max_stat-speed;
      //      printf("%i %i\n",hp, att+def+spatt+spdef+speed);

      att*=6*max_stat-base_stat_total;
      def*=6*max_stat-base_stat_total;
      spatt*=6*max_stat-base_stat_total;
      spdef*=6*max_stat-base_stat_total;
      speed*=6*max_stat-base_stat_total;
      att/=hp;
      def/=hp;
      spatt/=hp;
      spdef/=hp;
      speed/=hp;

      att=max_stat-att;
      def=max_stat-def;
      spatt=max_stat-spatt;
      spdef=max_stat-spdef;
      speed=max_stat-speed;

      hp=base_stat_total-att-def-spatt-spdef-speed;
    }

  if(mom->get_primary()==dad->get_primary() && mom->get_secondary()==dad->get_secondary()||
     mom->get_primary()==dad->get_secondary() && mom->get_secondary()==dad->get_primary())
    {
      primary_type=mom->get_primary();
      secondary_type=mom->get_secondary();
    }
  
  else if(mom->get_secondary()!=N_P_TYPES && dad->get_secondary()!=N_P_TYPES)
    {
      q=rand()%8;
      switch(q)
	{
	case(0):
	  primary_type=mom->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(1):
	  primary_type=mom->get_secondary();
	  secondary_type=MONOTYPE;
	  break;
	case(2):
	  primary_type=dad->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(3):
	  primary_type=dad->get_secondary();
	  secondary_type=MONOTYPE;
	  break;
	case(4):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_primary();
	  break;
	case(5):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_secondary();
	  break;
	case(6):
	  primary_type=mom->get_secondary();
	  secondary_type=dad->get_primary();
	  break;
	case(7):
	  primary_type=mom->get_secondary();
	  secondary_type=dad->get_secondary();
	  break;
	}
    }
  else if(mom->is_monotype() && dad->is_monotype())
    {
      q=rand()%4;
      switch(q)
	{
	case(0):
	  primary_type=mom->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(1):
	  primary_type=dad->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	default:
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_primary();
	  break;
	}
    }
  else if(mom->is_monotype() && !dad->is_monotype())
    {
      q=rand()%8;
      switch(q)
	{
	case(0):
	  primary_type=mom->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(1):
	  primary_type=mom->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(2):
	  primary_type=dad->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(3):
	  primary_type=dad->get_secondary();
	  secondary_type=MONOTYPE;
	  break;
	case(4):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_primary();
	  break;
	case(5):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_primary();
	  break;
	case(6):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_secondary();
	  break;
	case(7):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_secondary();
	  break;
	}
    }
  else if(!mom->is_monotype() && dad->is_monotype())
    {
      q=rand()%8;
      switch(q)
	{
	case(0):
	  primary_type=mom->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(1):
	  primary_type=mom->get_secondary();
	  secondary_type=MONOTYPE;
	  break;
	case(2):
	  primary_type=dad->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(3):
	  primary_type=dad->get_primary();
	  secondary_type=MONOTYPE;
	  break;
	case(4):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_primary();
	  break;
	case(5):
	  primary_type=mom->get_secondary();
	  secondary_type=dad->get_primary();
	  break;
	case(6):
	  primary_type=mom->get_primary();
	  secondary_type=dad->get_primary();
	  break;
	case(7):
	  primary_type=mom->get_secondary();
	  secondary_type=dad->get_primary();
	  break;
	}
    }
  
  if((rand()%10==0))// && iteration < 50) ||
     //(rand()%10==0 && iteration >= 50 && iteration<100)||
     //(rand()%2==0 && iteration >= 100 && iteration<150)||
     //(rand()%10==0 && iteration >= 150 && iteration<200))
    {
      //printf("Mutation!\n");
      secondary_type=rand()%N_P_TYPES;
    }
  
  q=rand()%16;
  move *move1, *move2, *move3, *move4;
  if(q%2)
    move1 = mom->get_moves()[0];
  else
    move1 = dad->get_moves()[0];
  if((q%4)/2)
    move2 = mom->get_moves()[1];
  else
    move2 = dad->get_moves()[1];
  if((q%8)/4)
    move3 = mom->get_moves()[2];
  else
    move3 = dad->get_moves()[2];
  if(q/8)
    move4 = mom->get_moves()[3];
  else
    move4 = dad->get_moves()[3];
  if(rand()%40==0)
    move1->change_p_type(rand()%N_P_TYPES);
  if(rand()%40==0)
    move2->change_p_type(rand()%N_P_TYPES);
  if(rand()%40==0)
    move3->change_p_type(rand()%N_P_TYPES);
  if(rand()%40==0)
    move4->change_p_type(rand()%N_P_TYPES);
  if(rand()%100==0)
    {
      q=spatt;
      spatt=att;
      att=q;
      move1->change_physical();
      move2->change_physical();
      move3->change_physical();
      move4->change_physical();
    }

  return new pokemon(primary_type,secondary_type,
		     hp,att,def,spatt,spdef,speed,
		     move1,move2,move3,move4);
};
  
#endif
