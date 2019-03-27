//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: hw10driver.cpp       Section: B
//Purpose: Main for hw10.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "town.h"
#include "activist.h"
#include "polluter.h"
#include "roots.h"
#include "hw10_header.h"
using namespace std;

// # of random moves by the activist & polluter to test
const int NUM_RANDOM_MOVES = 4;

//Town's grid size
const short TOWN_SIZE = 7;

int main()
{
  srand(time(NULL));
	
  //Varables to be read in from config file.
  short grid_size = 0;
  short num_roots = 0;
  short num_cops = 0;
  short num_days = 0;
  short dig_loss_cop = 0;
  short dig_loss_wall = 0;
  
  //ending type stats
  short times_exited = 0;
  short times_gone = 0;
  short times_caught = 0;
  short times_died = 0;
  short end_type;
  
  //Read from config file into variables  
  ifstream fin;
  fin.open(CONFIG_FILE.c_str());
  fin >> grid_size;
  fin >> num_roots;
  fin >> num_cops;
  fin >> num_days;
  fin >> dig_loss_wall;
  fin >> dig_loss_cop;
  fin.close();
	
  cout << "**********************************************" << endl;
  cout << "*WELCOME TO A.S.S. Activist Safety Simulation*" << endl;
  cout << "**********************************************" << endl;
  
  cout << endl;
  cout << "Starting simulations..." << endl;
	
  for(short i = 0; i < num_days; i++)
  {
    end_type = simulation(grid_size, num_roots, num_cops, 
                          dig_loss_cop, dig_loss_wall); 	  
    
    switch (end_type)
    {
      case ENDYTPE_EXIT:
        times_exited++;
        break;
        
      case ENDTYPE_GONE:
        times_gone++;
        break;
			
      case ENDTYPE_CAUGHT:
        times_caught++;
        break;
      
      case ENDTYPE_DEAD: 
        times_died++;
        break;
    }
  }
	
  //Output stats/percentages
  cout << endl << endl;
  cout << "Statistics for all simulations: " << endl;
  cout << "---------------------------------" << endl;
  cout << "Chance of hitting an exit: "
       << static_cast<float>(times_exited)/num_days * PERCENT_MULTIPLIER
       << "%" << endl;
  cout << "Chance of over-intoxication: "
       << static_cast<float>(times_gone)/num_days * PERCENT_MULTIPLIER
       << "%" << endl; 
  cout << "Chance of capturing polluter: "
       << static_cast<float>(times_caught)/num_days * PERCENT_MULTIPLIER
       << "%" << endl;   	
  cout << "Chance of dying from supreme indignity: "
       << static_cast<float>(times_died)/num_days * PERCENT_MULTIPLIER
       << "%" << endl << endl; 	
	
  cout << "Good luck on your quest!" << endl;
	
  //End of Program
  return 0;  
}                                                                                                                                           
