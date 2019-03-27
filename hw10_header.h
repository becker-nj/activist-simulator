//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: hw10_header.h       Section: B
//Purpose: header for hw10.

#include <iostream>
#include <unistd.h>
#include "activist.h"
#include "town.h"
#include "roots.h"
#include <ctime>
#include <cstdlib>
using namespace std;

/*~~~~CONSTANTS~~~~~*/
//config file name
const string CONFIG_FILE = "config.dat";

//Names and Symbols for Activist and Polluter
const char ACTIVIST_SYMBOL = 'L';
const string ACTIVIST_NAME = "Lisa";
const char POLLUTER_SYMBOL = 'H';
const string POLLUTER_NAME = "Homer";

//Symbols to represent objects in town
const char WALL_SYMBOL = 'W';
const char EXIT_SYMBOL = 'E';
const char COP_SYMBOL = 'C';
const char ROOT_SYMBOL = 'R';
const short MAX_ROOTS = 20;
const short MIN_COL = 1;
const short MIN_ROW = 1;

//Endtype Values
const short ENDYTPE_EXIT = 1;
const short ENDTYPE_GONE = 2;
const short ENDTYPE_CAUGHT = 3;
const short ENDTYPE_DEAD = 4;

const short PERCENT_MULTIPLIER = 100;
const short SIMS_TO_PRINT = 1;

//Output Delay in micro-seconds
const long PRINT_TIME = 200000;

/*~~~~MAIN FUNCTIONS~~~~*/
//The << operator is overloaded to output an activist object.
//Pre:  None
//Post: A description of the activist's current state is output
//to the screen.
ostream& operator << (ostream& o, const activist& a);

//The << operator is overloaded to output a town object.
//Pre:  None
//Post: The "grid" display for the town is output to the screen.
ostream& operator << (ostream& o, const town& t);

//Desc: The simulation() function simulates one day in the
//      town for the activist
//and returns a value representing how the simulation ended.
//Pre:  All values should be positive.
//Post: Returns the end value for the simulated day.
short simulation(const short size, const short num_roots, const short cops, 
                 const short cop_dig, const short wall_dig);

//Desc: The my_rand() returns a short between min and max.
//Pre:  max > min
//Post: A value betwen min and max is returned to the calling function.
short my_rand(const short min, const short max);
 
//Desc: The print_town() function outpupts the town array to the screen.
//Pre:  None
//Post: The town map is output to the screen.
void print_town(const town& city);

//Desc: The place_roots() function randomly places root symbols in
//      the town array.
//Pre:  root_count >= 0
//Post: Root symbol(s) are placed in the town array.
void place_roots(town& city, roots list[], const short root_count);

//Desc: The place_cops() function randomly places cop symbols
//      in the town array.
//Pre:  cops >= 0
//Post: Cop symbol(s) are placed in the town array.
void place_cops(town& t, const short cops);
