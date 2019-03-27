//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: activist_functs.cpp       Section: B
//Purpose: functions for activist class.

#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "activist.h"
#include "town.h"
#include "hw10_header.h"
using namespace std;

activist::activist(const string id, const char rep)
{
  m_name = id;
  m_symbol = rep;
  m_toxicity = DEF_TOX;
  m_dignity = DEF_DIG;
  m_row_pos = DEF_ACT_ROW;
  m_col_pos = DEF_ACT_COL;
  m_normal = true;
  m_cool = false; 
}

void activist::place_me(town& t)
{
  char sym;
  
  //determine town dimensions
  short index = 0;
	
  do
  {
    sym = t.getChar(0, index);  
    index++;
  } while(sym == WALL_SYMBOL || sym == EXIT_SYMBOL);
	
  //set activist coords
  m_row_pos = 1; //static_cast<int>((index - 1) / SPAWN_SPLIT);
  m_col_pos = 1; //static_cast<int>((index - 1) / SPAWN_SPLIT);
	
  //place the activist in the middle of town's grid
  t.setChar(ACTIVIST_SYMBOL, m_col_pos, m_row_pos);

  return;
}

void activist::rand_walk(town& t, const short cop_loss, const short wall_loss,
                         short& endtype, const roots list[], short& rt_count)
{
  short direction;
  char pos_char;
  short start_row_pos = m_row_pos;
  short start_col_pos = m_col_pos;
	
  //clear original activist location
  t.setChar(' ', m_row_pos, m_col_pos);

  //pick random direction to move up, right, left down
  //1: Move North
  //2: Move East
  //3: Move South
  //4: Move West
	
  direction = my_rand(ACT_DIRECTION_MIN, ACT_DIRECTION_MAX);
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
		
  //Checks if there is something in the way.
  pos_char = t.getChar(m_row_pos, m_col_pos);
  check_new_pos(endtype, t, pos_char, wall_loss, cop_loss, start_row_pos,
                start_col_pos, list, rt_count);
  
  //change town location of activist
	if(pos_char != WALL_SYMBOL)
    t.setChar(m_symbol, m_row_pos, m_col_pos);

  return;
}

void activist::turn_move(short& endtype, polluter& pol, town& t,
                         const short cop_loss, const short wall_loss,
                         const roots list[], const short num_roots)
{
  static short rt_count = num_roots - 1;
	
  if(m_normal)
  {
   targeted_walk(endtype, t, pol, cop_loss, wall_loss, list, rt_count);
  }	
  else if(m_cool)
  {
    rand_walk(t, cop_loss, wall_loss, endtype, list, rt_count);
  }
	
  if(rt_count == 0)
    rt_count = num_roots - 1;
	
  return;
}

void activist::check_new_pos(short& endtype, town& t, const char pos_char,
                             const short wall_loss, const short cop_loss,
                             const short start_row, const short start_col,
                             const roots list[], short& rt_count )
{
  static bool was_cop = false;
	
  if(was_cop == true)
  {
    t.setChar(COP_SYMBOL, start_row, start_col);
    was_cop = false;
  }
	
  if(pos_char == WALL_SYMBOL)
  {
    //reduce dignity
    m_dignity -= wall_loss;
    if(m_dignity <= MIN_DIGNITY)
      endtype = ENDTYPE_DEAD;
cout<<'\a';cout.flush();
cout<<'\a';			
    //move back
    m_row_pos = start_row;
    m_col_pos = start_col;
    t.setChar(m_symbol, m_row_pos, m_col_pos);
  }
	
  else if(pos_char == EXIT_SYMBOL)
  {
    endtype = ENDYTPE_EXIT;
  }
	
  else if(pos_char == ROOT_SYMBOL)
  {  
    *this += list[rt_count];
    rt_count--;
		
    if (m_toxicity > GONE_TOX_LIM)
      endtype = ENDTYPE_GONE;		
    else if(m_toxicity >= COOL_TOX_LIM && m_toxicity < GONE_TOX_LIM)
    {
      m_normal = false;
      m_cool = true;
    }	
  }	
	
  else if(pos_char == COP_SYMBOL)
  {
    m_dignity -= cop_loss;
		
    if(m_dignity <= MIN_DIGNITY)
      endtype = ENDTYPE_DEAD;
		
    was_cop = true;	
  }
  else if(pos_char == POLLUTER_SYMBOL)
  {
   endtype = ENDTYPE_CAUGHT;
  }	
	
  return;
}

void activist::operator+=(const roots rt)
{
  m_toxicity += rt.getEffect();
	
  //Prevent negative toxicity values
  if (m_toxicity < MIN_TOXICITY)
    m_toxicity = MIN_TOXICITY;
	
  return;
}

void activist::targeted_walk(short& endtype, town& t, polluter& pol,
                             const short cop_loss, const short wall_loss,
                             const roots list[], short& rt_count)
{
  short row_distance;
  short col_distance;
  short start_row_pos = m_row_pos;
  short start_col_pos = m_col_pos;
  char pos_char;
  bool move_up = false;
  bool move_left = false;

  t.setChar(' ', m_row_pos, m_col_pos);

  //Finds distance between row positions	
  if(pol.getRow() == m_row_pos)
    row_distance = 0;
  else if(pol.getRow() > m_row_pos)
    row_distance = pol.getRow() - m_row_pos;
  else
  {
    row_distance = m_row_pos - pol.getRow();		
    move_up = true;
  }	
	
  //Finds distance between column positions
  if(pol.getCol() == m_col_pos)
    col_distance = 0;
  else if(pol.getCol() > m_col_pos)
    col_distance = pol.getCol() - m_col_pos;
  else
  {
    col_distance = m_col_pos - pol.getCol();
    move_left = true;
  }	
		
  //Moves the activist in the closest direction of the polluter 
  if (col_distance == 0 && row_distance == 0)
    endtype = ENDTYPE_CAUGHT;
  else if(row_distance > col_distance)
  {
    //Activist moves horizontally
    if(col_distance == 0)
    {
      //Move up or down if on same column
      if(move_up)
        m_row_pos = start_row_pos - 1;
      
      else
        m_row_pos = start_row_pos + 1;
    }	
 	     	 
    else if(move_left && col_distance != 0)
      //Move left
      m_col_pos = start_col_pos - 1;		  
     else
      //Move right		
      m_col_pos = start_col_pos + 1;	
			
    pos_char = t.getChar(m_row_pos, m_col_pos);
    check_new_pos(endtype, t, pos_char, wall_loss, cop_loss, start_row_pos, 
                  start_col_pos, list, rt_count);		
  }
	
  else
  {
    //Activist moves vertically
    if (row_distance == 0)
    {
      //Move left or right if on same row
      if(move_left)
        m_col_pos = start_col_pos - 1;
      else
        m_col_pos = start_col_pos + 1;
    }
    else if(move_up && row_distance != 0)
      //Move up
      m_row_pos = start_row_pos - 1;

    else
      //Move down
      m_row_pos = start_row_pos + 1;
    
      pos_char = t.getChar(m_row_pos, m_col_pos);
      check_new_pos(endtype, t, pos_char, wall_loss, cop_loss, start_row_pos,
                    start_col_pos, list, rt_count);
  }
	
  if(pos_char != WALL_SYMBOL)
  t.setChar(m_symbol, m_row_pos, m_col_pos);
	
  return;
}

short activist::getDignity() const
{
  return m_dignity;
}

float activist:: getTox() const
{
  return m_toxicity;
}
