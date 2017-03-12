#ifndef POKE_MONSTER
#define POKE_MONSTER

#include<stdio.h>
#include<string.h>
#include "types.h"

class monster
{
 public:
  monster(monster *copy)
    {
      primary_type=copy->get_primary();
      secondary_type=copy->get_secondary();
      hp=(copy->get_max_hp()-110)/2;
      health=copy->get_health();
      att=(copy->get_attack()-5)/2;
      def=(copy->get_defense()-5)/2;
      spatt=(copy->get_specialattack()-5)/2;
      spdef=(copy->get_specialdefense()-5)/2;
      speed=(copy->get_speed()-5)/2;
    };
  monster(const int in_primary,const int in_secondary,
	  const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed)
    {
      primary_type=in_primary;
      secondary_type=in_secondary;

      if(primary_type==secondary_type)
	secondary_type=N_P_TYPES;
      hp=inhp;
      health=2*hp+110;
      att=inatt;
      def=indef;
      spatt=inspatt;
      spdef=inspdef;
      speed=inspeed;
    };
    monster(const int in_primary,
	    const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed)
    {
      primary_type=in_primary;
      secondary_type=N_P_TYPES;
      hp=inhp;
      health=2*hp+110;
      att=inatt;
      def=indef;
      spatt=inspatt;
      spdef=inspdef;
      speed=inspeed;
    };
    monster(const char in_primary[], const char in_secondary[],
	    const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed)
    {
      int i;
      primary_type=-1;
      secondary_type=-1;
      for(i=0;i<N_P_TYPES;i++)
	if(strcmp(in_primary,P_TYPES[i])==0)
	  primary_type=i;
      
      for(i=0;i<N_P_TYPES;i++)
	if(strcmp(in_secondary,P_TYPES[i])==0)
	  secondary_type=i;
      if(primary_type==-1 || secondary_type==-1)
	printf("please input a valid type");
      if(primary_type==secondary_type)
	secondary_type=N_P_TYPES;

      hp=inhp;
      health=2*hp+110;
      att=inatt;
      def=indef;
      spatt=inspatt;
      spdef=inspdef;
      speed=inspeed;
    };
    monster(const char in_primary[],
	    const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed)
    {
      int i;
      primary_type=-1;
      for(i=0;i<N_P_TYPES;i++)
	if(strcmp(in_primary,P_TYPES[i])==0)
	  primary_type=i;
      if(primary_type==-1)
	printf("please input a valid type");
      secondary_type=N_P_TYPES;
      hp=inhp;
      health=2*hp+110;
      att=inatt;
      def=indef;
      spatt=inspatt;
      spdef=inspdef;
      speed=inspeed;
    };

  int get_primary()
  {
    return primary_type;
  };
  int get_secondary()
  {
    return secondary_type;
  };
  int get_attack()
  {
    return 2*att+5;
  };
  int get_defense()
  {
    return 2*def+5;
  };
  int get_specialattack()
  {
    return 2*spatt+5;
  };
  int get_specialdefense()
  {
    return 2*spdef+5;
  };
  int get_speed()
  {
    return 2*speed+5;
  };
  int get_health()
  {
    return health;
  };
  int get_max_hp()
  {
    return 2*hp+110;
  }
  void take_damage(int damage_recieved)
  {
    health-=damage_recieved;
  };
  void heal()
  {
    health=2*hp+110;
  }
  void print()
  {
    printf("%s %s\n%i %i %i %i %i %i\n",P_TYPES[primary_type],P_TYPES[secondary_type],
	  health, 2*att+5, 2*def+5, 2*spatt+5,2*spdef+5,2*speed+5);
  }
  void print(FILE *file)
  {
    fprintf(file,"%s %s\n%i %i %i %i %i %i\n",P_TYPES[primary_type],P_TYPES[secondary_type],
	    health, 2*att+5, 2*def+5, 2*spatt+5,2*spdef+5,2*speed+5);
  }
 private:
  int primary_type,secondary_type;
  int hp, att, def, spatt, spdef, speed; //base stats
  int health;
};

/*
void po::use_move(attack *attack, pokemon *target)
{
  double basedamage;
  if(attack->get_physical())
    basedamage=2*210./250.*(this->get_attack()/target->get_defense())*attack->get_power()+2;
  else
    basedamage=2*210./250.*(this->get_specialattack()/target->get_specialdefense())*attack->get_power()+2;
  int attacktype=attack->get_type();
  double stab, eff, crit, random;
  if( attacktype==primary_type || (attacktype==secondary_type && secondary_type!=N_P_TYPES))
    stab=1.5;
  else
    stab=1.;
  eff=P_EFFECTIVENESS[attacktype][target->get_primary()]*P_EFFECTIVENESS[attacktype][target->get_secondary()];
  random=double(rand())/RAND_MAX;
  if(random<.0625)
    crit=1.5;
  else
    crit=1;
  random=1-(double(rand())/RAND_MAX)*.15;
  int damage=int(floor(basedamage*stab*eff*crit*random));
  if(damage==0)
    damage=1;
  if(double(rand())/RAND_MAX>(100.0-attack->get_accuracy())/100.0 || attack->get_accuracy()==100)
    target->take_damage(damage);
};
*/
#endif
