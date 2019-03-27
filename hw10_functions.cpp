//Programmer: Nathan Becker and Evan Moak     Date: 12/07/2016
//Instructor: Price             Class: cs1570
//File: hw10_functions.cpp       Section: B
//Purpose: functions for hw10.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "hw10_header.h"
#include "town.h"
#include "activist.h"
#include "polluter.h"
#include "roots.h"
using namespace std;

ostream& operator << (ostream& o, const activist& a)
{
  //Each member variable of the activist object is output.
  o << "Activist Name: " << a.m_name << endl
    << "Symbol: " << a.m_symbol << endl
    << "Final Toxicity: " << a.m_toxicity << endl
    << "Final Dignity: " << a.m_dignity << endl;
  return o;
}

ostream& operator << (ostream& o, const town& t)
{
  //The town array is output in a visual fashion with each 
  //character in the array.
  for(short i=0; i < t.getSize(); ++i)
    o << "----";
  o<<'-'<<endl;
  for(short i = 0; i < t.getSize(); i++)
  {
    for(short j = 0; j < t.getSize(); j++)
    {
      o << " | " << t.getChar(i,j);
    }
    o << " | " << endl;
    for(short j=0; j < t.getSize(); ++j)
      o << "----";
    o<<'-'<<endl;
          
  }	
	
  return o;
}

short simulation(const short size, const short num_roots, const short cops,
                 const short cop_dig, const short wall_dig)
{
  short end_type = 0;
  static short sim_count = 1;
	
  town springfield(size);
  activist lisa(ACTIVIST_NAME, ACTIVIST_SYMBOL);
  polluter homer(POLLUTER_NAME, POLLUTER_SYMBOL);
  roots root_list[MAX_ROOTS];

  //place activist
  lisa.place_me(springfield);
  //place polluter
  homer.place_me(springfield);
	
  //place roots 
  place_roots(springfield, root_list, num_roots);
		
  //place cops
  place_cops(springfield, cops);
	
  //Outputs town before any moves
  if(sim_count <= SIMS_TO_PRINT)
    print_town(springfield);
	
  do
  {
    //Move Polluter
    homer.random_move(springfield);
    if(sim_count <= SIMS_TO_PRINT)
    {
      print_town(springfield);
      cout << ACTIVIST_NAME << "'s Dignity: " << lisa.getDignity();
      cout << " " << ACTIVIST_NAME << "'s Toxicity: " << lisa.getTox()
           << endl << endl;
    }
		
    //Move Acitivst
    lisa.turn_move(end_type, homer, springfield, cop_dig, wall_dig,
                   root_list, num_roots);
    
    if(sim_count <= SIMS_TO_PRINT)
    {
      print_town(springfield);
      cout << ACTIVIST_NAME << "'s Dignity: " << lisa.getDignity();
      cout << " " << ACTIVIST_NAME << "'s Toxicity: " << lisa.getTox()
           << endl << endl;
    }
		
  } while(end_type == 0);
	
  //Print Simulation results
  if(sim_count <= SIMS_TO_PRINT)
  {
    cout << endl;
    cout << "Simulation Results: " << endl;
    cout << "-------------------------" << endl;
    cout << lisa;
    cout << "Simulation End Type: " << endl;
    
    switch (end_type)
    {
      case ENDYTPE_EXIT:
        cout << "Activist exited the town and was caught by the EPA." << endl;
        break;
		  
      case ENDTYPE_GONE:
        cout << "Activist became too intoxicated on roots and gave"
             << " up on the search." << endl;
        break;
      
      case ENDTYPE_CAUGHT:
        cout << "Activist successfully captured the polluter." << endl;
        break;
			
      case ENDTYPE_DEAD: 
        cout << "Activist died of supreme indignity." << endl;
        break;
    }
  }
	
  sim_count++;
  return end_type;
}

void print_town(const town& city)
{
  usleep(PRINT_TIME);
  cout << city << endl;
	
  return;
}

void place_roots(town& city, roots list[], const short root_count)
{
  for(int i = 0; i < root_count; i++)
  {
    list[i].place_me(city);
  }
	
  return;
}

void place_cops(town& t, const short cops)
{
  for(int i = 0; i < cops; i++)
  t.setChar(COP_SYMBOL, my_rand(1, t.getSize() - 2),
            my_rand(1, t.getSize() - 2));
	
  return;
}

short my_rand(const short min, const short max)
{
  return min + rand() % (max + 1 - min);
}
