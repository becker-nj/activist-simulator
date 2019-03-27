//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: polluter_functs.cpp       Section: B
//Purpose: functions for polluter class.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "polluter.h"
#include "town.h"
#include "hw10_header.h"
using namespace std;

polluter::polluter(const string id, const char rep)
{
  m_name = id;
  m_row_pos = DEF_POL_ROW;
  m_col_pos = DEF_POL_COL;
  m_symbol = rep;
}

void polluter::place_me(town& t)
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
  t.setChar(POLLUTER_SYMBOL, m_row_pos, m_col_pos);
	
  return;
}

void polluter::random_move(town& t)
{
  //pick a random direction, change polluter coords and town cords
  short direction;
  char pos_char;
	
  short start_row_pos = m_row_pos;
  short start_col_pos = m_col_pos;
	
  static bool is_caught = false;
  
  //pick random direction to move up, right, left down
  //1: Move North
  //2: Move East
  //3: Move South
  //4: Move West

  if(!is_caught)
  {
    //clear original polluter location
    t.setChar(' ', m_row_pos, m_col_pos);

    m_row_pos = start_row_pos;
    m_col_pos = start_col_pos;
    direction = my_rand(POL_DIRECTION_MIN, POL_DIRECTION_MAX);
    switch (direction)
    {
      case 1:
        m_row_pos = start_row_pos - 1;
        break;
      
      case 2:
        m_col_pos = start_col_pos + 1;
        break;
      
      case 3:
        m_row_pos = start_row_pos + 1;
        break;
      
      case 4:
        m_col_pos = start_col_pos - 1;
        break;
    }
	
    pos_char = t.getChar(m_row_pos, m_col_pos);
    check_new_pos(pos_char, t, start_row_pos, start_col_pos, is_caught);
    
    //change town location of polluter
    if(pos_char != WALL_SYMBOL && pos_char != EXIT_SYMBOL)
      t.setChar(m_symbol, m_row_pos, m_col_pos);
  }
  	
  return;
}

short polluter::getRow() const
{
  return m_row_pos;
}

short polluter::getCol() const
{
  return m_col_pos;
}

void polluter::check_new_pos(const char pos_char, town& t,
                             const short start_row, const short start_col,
                             bool& is_caught)
{
  static bool was_root = false;
	
  if(was_root == true)
  {
    t.setChar(ROOT_SYMBOL, start_row, start_col);
    was_root = false;
  }
	
  if(pos_char == WALL_SYMBOL)
  {
    m_row_pos = start_row;
    m_col_pos = start_col;
    t.setChar(m_symbol, m_row_pos, m_col_pos);
cout<<'\a';
  }
		
  else if(pos_char == EXIT_SYMBOL)
  {
    m_row_pos = start_row;
    m_col_pos = start_col;
    t.setChar(m_symbol, m_row_pos, m_col_pos);
  }
	
  else if(pos_char == ROOT_SYMBOL)
  {  
    was_root = true;	
  }

  else if(pos_char == COP_SYMBOL)
  {
    is_caught = true;
    t.setChar(m_symbol, m_row_pos, m_col_pos);
  }
	
  else if(pos_char == ACTIVIST_SYMBOL)
  {
    is_caught = true;
  }
	
  return;
}
