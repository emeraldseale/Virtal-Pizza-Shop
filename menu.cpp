/*********************************************************************************************************************************************************** Program: menu.cpp
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds all function bodies for the Menu class
** Input:
** Output:
*********************************************************************************************************************************************************/

#include "menu.h"
#include <iostream>
#include <fstream>

using namespace std;

/*********************************************************************************************************************************************************** Function: Menu
** Description: Default constructor for the Menu class
** Parameters: None
** Pre-Conditions: An object of the Menu class is initialized 
** Post-Conditions: An object is created and all its member variables are initialized to default
*********************************************************************************************************************************************************/
Menu::Menu () {

	numPizzas = 0;
	pizzas = NULL;
}

/*********************************************************************************************************************************************************** Function: Menu
** Description: Non-default constructor for the Menu class
** Parameters: Integer numPizzas
** Pre-Conditions: An object of the Pizza class is initialized with inputs
** Post-Conditions: An object is created and all of its member variables are set to the input
*********************************************************************************************************************************************************/
Menu::Menu (int np) {

	numPizzas = np;
	pizzas = new Pizza[numPizzas];
}

/*********************************************************************************************************************************************************** Function: Menu
** Description: Copy constructor for the Menu class
** Parameters: Constant parameter Menu copy by reference
** Pre-Conditions: A Menu object is passed or returned by value
** Post-Conditions: The object goes through a deep copy as opposed to a shallow one
*********************************************************************************************************************************************************/
Menu::Menu (const Menu& copy) {

	numPizzas = copy.numPizzas;
	if (numPizzas == 0) {
		pizzas = NULL;
	} else {
		pizzas = new Pizza[numPizzas];
		for (int i = 0; i < numPizzas; i++) {
			pizzas[i] = copy.pizzas[i];
		}
	}
}

/*********************************************************************************************************************************************************** Function: ~Menu
** Description: Destructor for the Menu class
** Parameters: None
** Pre-Conditions: A Menu object goes out of scope
** Post-Conditions: The object is destroyed and its memory is freed from the heap
*********************************************************************************************************************************************************/Menu::~Menu () {
	
	delete [] pizzas;
}

/*********************************************************************************************************************************************************** Function: operator=
** Description: Assignment operator overload 
** Parameters: Constant Menu copy by reference
** Pre-Conditions: A Menu object is assigned the value of another Pizza object
** Post-Conditions: The Menu object's member variables are equal to what it was assigned, a deep copy not shallow
*********************************************************************************************************************************************************/
const Menu& Menu::operator= (const Menu& copy) {

	numPizzas = copy.numPizzas;
	if (pizzas != NULL) {
		delete [] pizzas;	
	}
	if (numPizzas == 0) {
		pizzas = NULL;
	} else {
		pizzas = new Pizza[numPizzas];
		for (int i = 0; i < numPizzas; i++) {
			pizzas[i] = copy.pizzas[i];
		}
	}
	return *this;
}

/*********************************************************************************************************************************************************** Functions: All accessor functions (get_blank)
** Description: Gets a value from the private portion of the Menu class and returns it
** Parameters: None
** Pre-Conditions: The variable is in the private sphere and unaccessable
** Post-Conditions: The variable is returned and accessable
*********************************************************************************************************************************************************/int Menu::get_num_pizzas () { return numPizzas; }
Pizza* Menu::get_pizzas () { return pizzas; }

/*********************************************************************************************************************************************************** Functions: All mutator functions (set_blank)
** Description: Changes a value from the private portion of the Menu class
** Parameters: Integer np and array of Pizzas p
** Pre-Conditions: The variable in the private sphere is unaccessable and unchangeable, remains default
** Post-Conditions: The variable is mutated
*********************************************************************************************************************************************************/void Menu::set_num_pizzas (int np) { numPizzas = np; }

void Menu::set_pizzas (int numPizzas) { 
	
	ifstream f;
	f.open("menu.txt");
	pizzas = new Pizza[numPizzas]; 
	for (int i = 0; i < numPizzas; i++) {
		pizzas[i].pop_pizza(f);
	}
	f.close();
}
