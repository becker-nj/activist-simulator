//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price		Class: cs1570
//File: roots.h			Section: B
//Purpose: clas header for roots

#ifndef ROOTS_H
#define ROOTS_H

#include <iostream>
#include "town.h"
using namespace std;

/*~~~~CLASS CONSTANTS~~~~*/
const string NEG_ROOT = "square";
const string POS_ROOT = "truffle";

//RANDOM VALUE LIMITS
const short SET_NEGATIVE = 0;
const short SET_POSITIVE = 1;
const short MIN_NEG_EFFECT_DIVISOR = 100; 
const short MAX_NEG_EFFECT_DIVISOR = 1000;
const short MIN_POS_EFFECT_DIVISOR = 10;
const short MAX_POS_EFFECT_DIVISOR = 20;

/*~~~~MEMBER FUNCTION DOCUMENTATION~~~~*/
//Desc: The roots() constructor randomly assigns the effect
//(+ or -) and names it accordingly
//Pre:  None.
//Post: A root object is constructed.

//Desc: The place_me() function places the root symbol in the town array
//in a random location not occupied by another symbol.
//Pre:  None.
//Post: A root symbol is placed in the town array.

//Desc: The getEffect() function returns the efffect of the 
//calling root object.
//Pre:  None.
//Post: The effect of the root object is returned.

class roots
{
  public:
    roots();
    void place_me(town& t);
    float getEffect() const;
	
  private:
    //Name of the root(square or truffle).
    string m_type;
		
    //Position variables.
    short m_row_pos;
    short m_col_pos;

    //negative = square, positive = truffle,
    float m_effect;

};

#endif
