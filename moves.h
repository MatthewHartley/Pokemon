#ifndef POKE_MOVES
#define POKE_MOVES
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"monster.h"

#define ATTACK 0
#define STATUS 1
#define DUMMY -1
class move
{
 public:
  move(const int inm_type, const int inp_type,
	 const int inpower, const int in_accuracy, const bool inphysical)
    {
      m_type=inm_type;
      if(m_type==ATTACK)
	{
	  p_type=inp_type;
	  power=inpower;
	  accuracy=in_accuracy;
	  physical=inphysical;
	}
      else
	printf("No status moves\n");
    };
  move(const int inm_type, const char inp_type[],
	 const int inpower, const int in_accuracy, const bool inphysical)
    {
      int i;
      m_type=inm_type;
      if(m_type==ATTACK)
	{
	  p_type=-1;
	  for(i=0;i<N_P_TYPES;i++)
	    if(strcmp(inp_type,P_TYPES[i])==0)
	      p_type=i;
	  if(p_type==-1)
	    printf("Please enter a valid move type, input type: %s",inp_type);
	    
	  power=inpower;
	  accuracy=in_accuracy;
	  physical=inphysical;
	}
      else
	printf("No Status Moves");
    };
  move(move *copy)
    {
      m_type=copy->get_m_type();
      p_type=copy->get_p_type();
      power=copy->get_power();
      accuracy=copy->get_accuracy();
      physical=copy->is_physical();
    };
  move()
    {
      m_type=DUMMY;
      p_type=0;
      power=0;
      accuracy=0;
      physical=false;
    }
  int get_p_type()
  {
    return p_type;
  };
  int get_m_type()
  {
    return m_type;
  }
  int get_power()
  {
    return power;
  };
  int get_accuracy()
  {
    return accuracy;
  };
  bool is_physical()
  {
    return physical;
  };
  void use(monster *user, monster *target)
  {
    if(m_type==ATTACK)
      attack(user,target);
    else
      printf("Sorry, no status moves, yet\n");
  };
  void print()
  {
    if(physical)
      printf("%s\n %i %i physical\n",P_TYPES[p_type],power,accuracy);
    else
      printf("%s\n %i %i special\n",P_TYPES[p_type],power,accuracy);
  }
  void change_p_type(int newtype)
  {
    p_type=newtype;
  }
  void change_physical()
  {
    physical=!physical; 
  }
  void print(FILE *file)
  {
    if(physical)
      fprintf(file,"%s\n %i %i physical\n",P_TYPES[p_type],power,accuracy);
    else
      fprintf(file,"%s\n %i %i special\n",P_TYPES[p_type],power,accuracy);
  }
 private:
  void attack(monster *user, monster *target);

  bool physical;
  int power;
  int accuracy;
  int p_type;
  int m_type;
};


void move::attack(monster *user, monster *target)
{
  //  printf("You just used an attacking move!\n");
  int damage, random;
  double stab, eff, crit;
  if( p_type==user->get_primary() || (p_type==user->get_secondary() && p_type!=N_P_TYPES))
    stab=1.5;
  else
    stab=1.;
  eff=P_EFFECTIVENESS[p_type][target->get_primary()]*P_EFFECTIVENESS[p_type][target->get_secondary()];
  if(double(rand())/RAND_MAX<.0625)
    {
      //printf("critical hit!\n");
      crit=1.5;
    }
  else
    crit=1.;
  random=100-rand()%16;
  if(physical)
    {
      //printf("Attack: %i\nDefense: %i\nPower: %i\n",user->get_attack(),target->get_defense(),power);
      damage=42*user->get_attack()*power;
      damage/=target->get_defense();
      damage/=50;
      damage+=2;
    }
  else
    {
      //printf("Attack: %i\nDefense: %i\nPower: %i\n",user->get_specialattack(),target->get_specialdefense(),power);
      damage=42*user->get_specialattack()*power;
      damage/=target->get_specialdefense();
      damage/=50;
      damage+=2;
    }

  damage*=stab;
  damage*=eff;
  damage*=crit;
  damage*=random;
  damage/=100;
  //  int damage=int(floor(basedamage*stab*eff*crit*random));
  if(damage==0)
    damage=1;
  //printf("stab: %lf\neff: %lf\ncrit: %lf\nDamage: %i\n",
  //stab,eff,crit,damage);
  if(double(rand())/RAND_MAX>(100.0-accuracy)/100.0 || accuracy==100)
    target->take_damage(damage);
};


#endif
