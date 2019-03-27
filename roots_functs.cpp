//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price		Class: cs1570
//File: roots_functs.cpp	Section: B
//Purpose: functions for roots class

#include "roots.h"
#include "hw10_header.h"
#include "town.h"
roots::roots()
{
  short sign = my_rand(SET_NEGATIVE, SET_POSITIVE);
  
  //Negative Effect
  if(sign == SET_NEGATIVE)
  {
    m_effect = static_cast<float>(-1)/
               (my_rand(MIN_NEG_EFFECT_DIVISOR, MAX_NEG_EFFECT_DIVISOR));
    m_type = NEG_ROOT;
  }
  
  //Positive Effect
  else if(sign == SET_POSITIVE)
  {
    m_effect = static_cast<float>(1)/
               (my_rand(MIN_POS_EFFECT_DIVISOR, MAX_POS_EFFECT_DIVISOR));
    m_type = POS_ROOT;
  }
	
}

void roots::place_me(town& t)
{
  //place polluter in town within dimensions of town
  //and not on top of anything else
  char sym;
  short rand_spawn_col;
  short rand_spawn_row;
  char pos_char;
  
  //determine town dimensions
  short index = 0;
  do
  {
    sym = t.getChar(0, index);  
    index++;
  } while(sym == WALL_SYMBOL || sym == EXIT_SYMBOL);
  
  //set polluter coords
  do
  {
    rand_spawn_col = my_rand(MIN_COL, index - 2);
    rand_spawn_row = my_rand(MIN_ROW, index - 2);
    pos_char = t.getChar(rand_spawn_col, rand_spawn_row);
  } while(pos_char != ' ');
  
  m_row_pos = rand_spawn_col;
  m_col_pos = rand_spawn_row;
  
  //place the activist in the middle of town's grid
  t.setChar(ROOT_SYMBOL, m_row_pos, m_col_pos);
  return;
}

float roots::getEffect() const
{
  return m_effect;
}
