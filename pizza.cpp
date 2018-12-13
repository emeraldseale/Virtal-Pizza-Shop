/*********************************************************************************************************************************************************** Program: pizza.cpp
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds all function bodies for the Pizza class
** Input:
** Output:
*********************************************************************************************************************************************************/

#include "pizza.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/*********************************************************************************************************************************************************** Function: Pizza
** Description: Default constructor for the Pizza class
** Parameters: None
** Pre-Conditions: An object of the Pizza class is initialized 
** Post-Conditions: An object is created and all its member variables are initialized to default
*********************************************************************************************************************************************************/
Pizza::Pizza () {

	name = "Default";
	smallCost = 0;
	mediumCost = 0;
	largeCost = 0;
	numIngredients = 0;
	ingredients = NULL;
}

/*********************************************************************************************************************************************************** Function: Pizza
** Description: Non-default constructor for the Pizza class
** Parameters: String n, int sc, int mc, int lc, and int i
** Pre-Conditions: An object of the Pizza class is initialized with inputs
** Post-Conditions: An object is created and all of its member variables are set to the input
*********************************************************************************************************************************************************/
Pizza::Pizza (string n, int sc, int mc, int lc, int i) {

	name = n;
	smallCost = sc;
	mediumCost = mc;
	largeCost = lc;
	numIngredients = i;
	ingredients = new string[numIngredients];
	for (int i = 0; i < numIngredients; i++) {
		ingredients[i] = "Default";
	}
}

/*********************************************************************************************************************************************************** Function: Pizza
** Description: Copy constructor for the Pizza class
** Parameters: Constant parameter Pizza copy by reference
** Pre-Conditions: A Pizza object is passed or returned by value
** Post-Conditions: The object goes through a deep copy as opposed to a shallow one
*********************************************************************************************************************************************************/
Pizza::Pizza (const Pizza& copy) {

	name = copy.name;
	smallCost = copy.smallCost;
	mediumCost = copy.mediumCost;
	largeCost = copy.largeCost;
	numIngredients = copy.numIngredients;
	if (numIngredients == 0) {
		ingredients = NULL;
	} else {
		ingredients = new string[numIngredients];
		for (int i = 0; i < numIngredients; i++) {
			ingredients[i] = copy.ingredients[i];
		}
	}
}

/*********************************************************************************************************************************************************** Function: ~Pizza
** Description: Destructor for the Pizza class
** Parameters: None
** Pre-Conditions: A Pizza object goes out of scope
** Post-Conditions: The object is destroyed and its memory is freed from the heap
*********************************************************************************************************************************************************/Pizza::~Pizza () {
	
	delete [] ingredients;
}

/*********************************************************************************************************************************************************** Function: operator=
** Description: Assignment operator overload 
** Parameters: Constant Student copy by reference
** Pre-Conditions: A Pizza object is assigned the value of another Pizza object
** Post-Conditions: The Pizza object's member variables are equal to what it was assigned, a deep copy not shallow
*********************************************************************************************************************************************************/
const Pizza& Pizza::operator= (const Pizza& copy) {

	name = copy.name;
	smallCost = copy.smallCost;
	mediumCost = copy.mediumCost;
	largeCost = copy.largeCost;
	numIngredients = copy.numIngredients;
	if (ingredients != NULL) {
		delete [] ingredients;	
	}
	if (numIngredients == 0) {
		ingredients = NULL;
	} else {
		ingredients = new string[numIngredients];
		for (int i = 0; i < numIngredients; i++) {
			ingredients[i] = copy.ingredients[i];
		}
	}
	return *this;
}

/*********************************************************************************************************************************************************** Functions: All accessor functions (get_blank)
** Description: Gets a value from the private portion of the Pizza class and returns it
** Parameters: None
** Pre-Conditions: The variable is in the private sphere and unaccessable
** Post-Conditions: The variable is returned and accessable
*********************************************************************************************************************************************************/string Pizza::get_name () const { return name; }
int Pizza::get_small_cost () const { return smallCost; }
int Pizza::get_medium_cost () const { return mediumCost; }
int Pizza::get_large_cost () const { return largeCost; }
int Pizza::get_num_ingredients () const { return numIngredients; }
string* Pizza::get_ingredients () const { return ingredients; }

/*********************************************************************************************************************************************************** Functions: All mutator functions (set_blank)
** Description: Changes a value from the private portion of the Pizza class
** Parameters: String n, int sc, int mc, int lc, int ni, string* i
** Pre-Conditions: The variable in the private sphere is unaccessable and unchangeable, remains default
** Post-Conditions: The variable is mutated
*********************************************************************************************************************************************************/void Pizza::set_name (string n) { name = n; }
void Pizza::set_small_cost (int sc) { smallCost = sc; }
void Pizza::set_medium_cost (int mc) { mediumCost = mc; }
void Pizza::set_large_cost (int lc) { largeCost = lc; }
void Pizza::set_num_ingredients (int ni) { numIngredients = ni; }
void Pizza::set_ingredients (string* i) { ingredients = i; }

/*********************************************************************************************************************************************************** Function: pop_pizza
** Description: Populates a Pizza object with information read from a file
** Parameters: ifstream object f passed by reference
** Pre-Conditions: The Pizza object is populated by default values
** Post-Conditions: The Pizza object is populated with information from the file
*********************************************************************************************************************************************************/void Pizza::pop_pizza (ifstream& f) {

	f >> name;
	f >> smallCost;
	f >> mediumCost;
	f >> largeCost;
	f >> numIngredients;
	ingredients = new string[numIngredients];
	for (int i = 0; i < numIngredients; i++) {
		f >> ingredients[i];	
	}
}
