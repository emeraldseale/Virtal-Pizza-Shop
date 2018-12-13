/*********************************************************************************************************************************************************** Program: pizza.h
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds the Pizza class and all its member variables and function defintions
** Input: None
** Output: None
*********************************************************************************************************************************************************/

#include <string>

using namespace std;

class Pizza {

	private:
		string name;
		int smallCost;
		int mediumCost;
		int largeCost;
		int numIngredients;
		string* ingredients;
	public:
		Pizza (); //Default constructor
		Pizza (string, int, int, int, int); //Non-default constructor
		Pizza (const Pizza&); //Copy constructor
		~Pizza (); //Destructor
		const Pizza& operator= (const Pizza &); //Assignment operator overload
		//Accessors:
		string get_name () const;
		int get_small_cost () const;
		int get_medium_cost () const;
		int get_large_cost () const;	
		int get_num_ingredients () const;
		string* get_ingredients () const;
		//Mutators:
		void set_name (string);
		void set_small_cost (int);
		void set_medium_cost (int);
		void set_large_cost (int);
		void set_num_ingredients (int);
		void set_ingredients(string*);
		void pop_pizza(ifstream&);
};
