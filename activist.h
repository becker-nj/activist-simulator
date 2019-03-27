//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: activist.h              Section: B
//Purpose: class header for activist.

#ifndef ACTIVIST_H
#define ACTIVIST_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "town.h"
#include "polluter.h"
#include "roots.h"
using namespace std;

/*~~~~CLASS CONSTANTS~~~~*/

//The default activist stat variables
const float DEF_TOX = 0.05;
const short DEF_DIG = 100;
const short DEF_ACT_ROW = -1;
const short DEF_ACT_COL = -1;
const char DEF_ACT_SYM = 'A';

//Used to place activist in the middle.
//column and row is divided by this to find center
//of the town array.
const short SPAWN_SPLIT = 2;

//Limits for determing direction to move activist.
const short ACT_DIRECTION_MIN = 1;
const short ACT_DIRECTION_MAX = 4;
const float COOL_TOX_LIM = 0.08;
const float GONE_TOX_LIM = 0.25;
const short MIN_DIGNITY = 0;
const float MIN_TOXICITY = 0.0;


/*~~~MEMBER FUNCTION DOCUMENTATION~~~~*/
//Desc: The activist() constructor sets the name and symbol for the 
//activist object to the parameters and sets the other memeber variables
//to pre-set constant values. 
//Pre:  None
//Post: An activist object is constructed.

//Desc: The place_me() function places the activist symbol in the middle
//of the town.
//Pre:  None.
//Post: Activist's symbol is placed in the center of
//the town in the array.

//Desc: The rand_walk() function picks a random direction to move and
//updates the activist symbol position in the town and
//in the activist object.
//Pre:  None.
//Post: The town array is updated with the new symbol position and 
//the activist position in the object is updated.

//Desc: The targeted_walk() function moves the 
//activist towards the polluter in the town.
//Pre:  rt_count, and loss values > 0
//Post: The activist moves it's position in the town towards the polluter.

//Desc: The turn_move() function determines if the activist
//should move in a targeted or random fashion based on toxicity level.
//Pre:  rt_count and loss values > 0
//Post: The targeted walk or random walk function is called.

//Desc: The check_new_pos() function determines what character the activist 
//will step on, and updates endtype accordingly along with activist variables.
//Pre:  rt_count and loss values > 0
//Post: The activist variables are updated depending
//      on which space it moves to.

//Desc: The getDignity() function returns the activist's current dignity value.
//Pre:  None.
//Post: The activist's dignity value is returned.

//Desc: The getTox() function returns the activist's current toxicity value.
//Pre: None.
//Post: The activist's toxicity value is returned.

//Desc: The += operator is overloaded to add a root effect 
//to the activist toxicity.
//Pre:  None.
//Post: The activist's toxicity is updated.

class activist
{
  public:
    activist(const string id, const char rep = 'A');
    void place_me(town& t);
    void rand_walk(town& t, const short cop_loss, const short wall_loss,
                   short& endtype, const roots list[], short& rt_count);
    void targeted_walk(short& endtype, town& t, polluter& pol,
                       const short cop_loss, const short wall_loss,
                       const roots list[], short& rt_count);
    void turn_move(short& endtype, polluter& pol, town& t, const short cop_dig,
                   const short wall_dig, const roots list[],
                   const short num_roots);
    void check_new_pos(short& endtype, town& t, const char pos_char,
                       const short wall_loss, const short cop_loss,
                       const short start_row, const short start_col, 
                       const roots list[], short& rt_count);
    short getDignity() const;
    float getTox() const;
		
    void operator+=(const roots rt);
    friend ostream& operator << (ostream& o, const activist& a);
	
  private:
    //The name of the activist.
    string m_name;
    //The symbol to represent the activist in the town array.
    char m_symbol;

    //The row the activist is in.
    short m_row_pos;
    //The column the activist is in.
    short m_col_pos;
 
    //Is the activist normal(true/false).
    bool m_normal;
    //Is the activist cool(true/false).
    bool m_cool;
 
    //The dignity level of the activist.
    short m_dignity;
    //The toxicity level of the activist.
    float m_toxicity;
};

#endif
