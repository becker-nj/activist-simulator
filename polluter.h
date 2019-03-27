//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: polluter.h              Section: B
//Purpose: class header for polluter

#ifndef POLLUTER_H
#define POLLUTER_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "town.h"
using namespace std;

/*~~~~CLASS CONSTANTS~~~~*/

//The default polluter position variables
const short DEF_POL_ROW = -1;
const short DEF_POL_COL = -1;

//Limits for determing direction to move polluter.
const short POL_DIRECTION_MIN = 1;
const short POL_DIRECTION_MAX = 4;
//The default symbol for polluter.
const char DEF_POL_SYM = 'P';


/*~~~MEMBER FUNCTION DOCUMENTATION~~~~*/
//Desc: The polluter() constructor sets the name and symbol for the 
//polluter object to the parameters and sets the other memeber variables
//to pre-set constant values. 
//Pre:  None
//Post: A polluter object is constructed.

//Desc: The place_me() function randomly places the polluter
//in the town array into a position not occupied by another symbol
//Pre: None.
//Post: The polluter symbol is placed in the town and the polluter
//position is updated.

//Desc: The random_move() function picks a random direction to move 
//and updates the polluter symbol position in the town and in 
//the polluter object.
//Pre: None.
//Post: The town array is updated with the new symbol position and 
//the polluter position in the object is updated.

//Desc: The getRow() function returns the row position of the calling object.
//Pre:  None.
//Post: The row position for the polluter object is returned.

//Desc: The getCol() function returns the column position of the
//      calling object.
//Pre:  None.
//Post: The column position for the polluter object is returned.

//Desc: The check_new_pos() function determines what character the polluter 
//will step on and adjusts the position variables accrodingly 
//Pre:  None
//Post: The polluter variables are updated depending on which space
//      it moves to.

class polluter
{
  public:
    polluter(const string id, const char rep = DEF_POL_SYM);
    void place_me(town& t);
    void random_move(town& t);
    short getRow() const;
    short getCol() const;
    void check_new_pos(const char pos_char, town& t, const short start_row, 
                       const short start_col, bool& is_caught);

  private:
    //The name of the polluter.
    string m_name;
    //The symbol for the polluter.
    char m_symbol;
		
    //The row position of the polluter.
    short m_row_pos;
    //The column position of the polluter.
    short m_col_pos;
	
    //Tells if the polluter has been caught by a cop.
    bool is_caught;
};

#endif
