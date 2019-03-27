//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: town_functs.cpp       Section: B
//Purpose: functions for town class.

#include <iostream>
#include "town.h"
#include "hw10_header.h"

using namespace std;

town::town(const short grid_size)
{
  m_town_size = grid_size;
	
  //Replaces garbage in array with blank spaces.
  clear();
	
  //Place walls and exits
  if(m_town_size < MAX)
  {
    build(m_town_size);	  
  }
  
  //Defaults to MAX-1 if size is too big.  
  else if(m_town_size >= MAX)
  {
    build(m_town_size - 1);
  }
	
}

char town::getChar(const short row, const short col) const
{
  return m_grid[row][col];
}

void town::setChar(const char c, const short row, const short col)
{
  m_grid[row][col] = c;	
  return;
}

void town::clear()
{
  for(short i = 0; i < MAX; i++)
  {
    for(short j = 0; j < MAX; j++)
    {
      m_grid[i][j] = ' ';
    }
  }	
  
  return;
}

void town::build(const short size)
{
  //Builds the walls.
  for(short i = 0; i < size; i++)
  {
    for(short j = 0; j < size; j++)
    {
      if(j ==0 || i == 0 || j == size - 1 || i == size - 1)
      {
        m_grid[i][j]= WALL_SYMBOL;
      }
      else
      {
        m_grid[i][j] = ' ';		  
      }
    }
  }	
  
  //Places exits in the middle of each wall.
  m_grid[0][static_cast<short>((size - 1)/(EXIT_SPLITER))] = EXIT_SYMBOL;
  m_grid[(size - 1)][static_cast<short>((size - 1)/(EXIT_SPLITER))] 
    = EXIT_SYMBOL;
  m_grid[static_cast<short>((size - 1)/(EXIT_SPLITER))][0] = EXIT_SYMBOL;
  m_grid[static_cast<short>((size - 1)/(EXIT_SPLITER))][(size - 1)] 
    = EXIT_SYMBOL;

  return;
}

short town::getSize() const
{
  return m_town_size;
}
