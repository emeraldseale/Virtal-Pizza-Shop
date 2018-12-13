/*********************************************************************************************************************************************************** Program: menu.h
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds the Menu class and all its member variables and function definitions
** Input: None
** Output: None
*********************************************************************************************************************************************************/

#include "pizza.h"
#include <string>

using namespace std;

class Menu {

	private:
		int numPizzas;
		Pizza* pizzas;
	public:
		Menu (); //Default constructor
		Menu (int); //Non-default constructor
		Menu (const Menu&); //Copy constructor
		~Menu (); //Destructor
		const Menu& operator= (const Menu&); //Assignment operator overload
		//Accessors:
		int get_num_pizzas ();
		Pizza* get_pizzas ();
		//Mutators:
		void set_num_pizzas (int);
		void set_pizzas (int);
		//Other functions:
		Menu search_pizza_by_cost (int, string);
		Menu search_pizza_by_ingredients_to_include (string*, int);
		Menu search_pizza_by_ingredients_to_exclude (string*, int);
		void add_to_menu (Pizza);
		void remove_from_menu (int);
};
