#ifndef POKEMON
#define POKEMON
#include "types.h"
#include "monster.h"
#include "moves.h"

class pokemon
{
 public:
  pokemon(pokemon *copy)
    {
      mon=new monster(copy->get_monster());
      move **copymoves=copy->get_moves();
      int i;
      for(i=0;i<4;i++)
	moves[i]=new move(copymoves[i]);
      wins=copy->get_wins();
      losses=copy->get_losses();
    }
  pokemon(monster *inmonster,
	  move *move1, move *move2, move *move3, move *move4)
    {
      mon=new monster(inmonster);
      moves[0]=new move(move1);
      moves[1]=new move(move2);
      moves[2]=new move(move3);
      moves[3]=new move(move4);
      wins=0;
      losses=0;
    };
   pokemon(const int in_primary,const int in_secondary,
	   const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed,
	   move *move1, move *move2, move *move3, move *move4)
     {
       mon = new monster(in_primary,in_secondary,inhp,inatt,indef,inspatt,inspdef,inspeed);
       moves[0]=new move(move1);
       moves[1]=new move(move2);
       moves[2]=new move(move3);
       moves[3]=new move(move4);
       wins=0;
       losses=0;
     }
   pokemon(const int in_primary,
	   const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed,
	   move *move1, move *move2, move *move3, move *move4)
     {
       mon = new monster(in_primary,inhp,inatt,indef,inspatt,inspdef,inspeed);
       moves[0]=new move(move1);
       moves[1]=new move(move2);
       moves[2]=new move(move3);
       moves[3]=new move(move4);
       wins=0;
       losses=0;
     }
   pokemon(const char in_primary[], const char in_secondary[],
	   const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed,
	   move *move1, move *move2, move *move3, move *move4)
     {
       mon = new monster(in_primary,in_secondary,inhp,inatt,indef,inspatt,inspdef,inspeed);
       moves[0]=new move(move1);
       moves[1]=new move(move2);
       moves[2]=new move(move3);
       moves[3]=new move(move4);
       wins=0;
       losses=0;
     }
   pokemon(const char in_primary[],
	   const int inhp, const int inatt, const int indef, const int inspatt, const int inspdef, const int inspeed,
	   move *move1, move *move2, move *move3, move *move4)
     {
       mon = new monster(in_primary,inhp,inatt,indef,inspatt,inspdef,inspeed);
       moves[0]=new move(move1);
       moves[1]=new move(move2);
       moves[2]=new move(move3);
       moves[3]=new move(move4);
       wins=0;
       losses=0;
     }
   
   ~pokemon()
     {
       delete mon;
       delete moves[0];
       delete moves[1];
       delete moves[2];
       delete moves[3];
     }
   
  int get_primary()
  {
    return mon->get_primary();
  };
  int get_secondary()
  {
    return mon->get_secondary();
  };
  bool is_monotype()
  {
    return mon->get_secondary()==N_P_TYPES;
  };
  bool is_alive()
  {
    return mon->get_health()>0;
  };
  int get_health()
  {
    return mon->get_health();
  };
  int get_max_hp()
  {
    return mon->get_max_hp();
  };
  int get_attack()
  {
    return mon->get_attack();
  };
  int get_defense()
  {
    return mon->get_defense();
  };
  int get_specialattack()
  {
    return mon->get_specialattack();
  };
  int get_specialdefense()
  {
    return mon->get_specialdefense();
  };
  int get_speed()
  {
    return mon->get_speed();
  };
  void take_damage(int damage)
  {
    mon->take_damage(damage);
  }
  void heal()
  {
    mon->heal();
  }
  monster *get_monster()
  {
    return mon;
  };
  move** get_moves()
  {
    return moves;
  }
  void use_moves(int i, pokemon *target)
  {
    moves[i]->use(mon,target->get_monster());
  };
  void print()
  {
    mon->print();
    for(int i=0;i<4;i++)
      moves[i]->print();
  };
  void print(FILE *file)
  {
    mon->print(file);
    for(int i=0;i<4;i++)
      moves[i]->print(file);
  };
  void add_win()
  {
    wins++;
  }
  void add_loss()
  {
    losses++;
  }
  int get_wins()
  {
    return wins;
  }
  int get_losses()
  {
    return losses;
  }
private:
  monster *mon;
  move* moves[4];
  int wins,losses;
};


#endif
