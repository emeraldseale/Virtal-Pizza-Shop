/*********************************************************************************************************************************************************** Program: driver.cpp
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds the main function that runs the entire program
** Input:
** Output:
*********************************************************************************************************************************************************/

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "restaurant.h"

using namespace std;


int main () {

	Restaurant r;
	r.load_data();	
	char choice = r.intro();
	r.choice_select(choice);		
	//check pass and id

	return 0;
}
