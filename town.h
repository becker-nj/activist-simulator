//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: town.h                  Section: B
//Purpose: class header for town.

#ifndef TOWN_H
#define TOWN_H
#include <iostream>
using namespace std;

/*~~~~CLASS CONSTANTS~~~~*/
//The maximum dimension of the town 2-D array.
const short MAX = 25;

//How to divide each wall and place an exit.
//2 means half way down the wall.
const float EXIT_SPLITER = 2;

/*~~MEMBER FUNCTION DOCUMENTATION~~*/
//Desc: The town() constructor sets the size of the town array,
//clears the map of any symbols, and builds perimeter the town.
//Pre: The grid_size read in from the config file needs to be at least
//greater than 3 to accomodate both the polluter and the activist.
//Post: The town class is built.

//Desc: The getChar() function returns the character in the 
//m_grid[row][col] position.
//Pre: m_grid should contain the [row][col]
//Post: The character in the m_grid is returned to the calling function.

//Desc: The setChar() function replaces the character in the m_grid array
//at m_grid[row][col]with the parameter character.
//Pre: m_grid should contain [row][col]
//Post: The m_grid[row][col] character is updated.

//Desc: The clear() function replaces all chars in the town array
//with white spaces.
//Pre: None.
//Post: The town array contains no garbage characters.

//Desc: The build() function sets the walls and exits 
//of the town array based on the passed size. 
//Pre: size > 0, size < MAX
//Post: The town array is filled with walls and exits.	

class town
{
  public:
    town(const short grid_size = MAX);
    char getChar(const short row, const short col) const;
    void setChar(const char c, const short row, const short col);    
		 short getSize() const;
    friend ostream& operator << (ostream& o, const town& t);

  private:
    void clear();
    void build(const short size);
		
    //A 2D array to store the town and characters to represent
    //objects in the town.
    char m_grid [MAX][MAX];

    //Stores size of town to be built.
    short m_town_size;
};

#endif
