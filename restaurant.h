/*********************************************************************************************************************************************************** Program: restaurant.h
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds the restaurant class and all its member variables and function definitions
** Input: None
** Output: None
*********************************************************************************************************************************************************/

#include "menu.h"
#include "hours.h"
#include "employee.h"
#include "orders.h"
#include <string>

using namespace std;

class Restaurant {

	private:
		Menu menu;
		employee* employees;
		hours* week;
		//add in orders array
		string name;
		string phone;
		string address;
	public:
		Restaurant (); //Default constructor
		Restaurant (string, string, string, int, int); //Non-default constructor
		Restaurant (const Restaurant&); //Copy constructor
		~Restaurant (); //Destructor
		const Restaurant& operator= (const Restaurant&); //Assignment operator overload
		//Accessors:
		Menu get_menu ();
		employee* get_employees ();
		hours* get_week ();
		orders* get_arr_orders ();
		string get_name ();
		string get_phone ();
		string get_address ();
		//Mutators:
		void set_menu (Menu);
		void set_employees (employee*);
		void set_week (hours*);
		void set_arr_orders (orders*);
		void set_name (string);
		void set_phone (string);
		void set_address (string);
		//Other functions:
		char intro ();
		void choice_select(char);
		void load_data ();
		void enter_login ();
		bool login (string, string);
		void employee_functionality();
		void customer_functionality();
		void display_employee_options();
		void display_customer_options();
		void view_menu ();
		void view_hours ();
		void view_address ();
		void view_phone ();
		void search_menu_by_price ();
		void search_by_ingredients ();
		void inclusion_search(ofstream&);
		void inclusion_search_reduce(string);
		void exclusion_search(ofstream&);
		void exclusion_search_reduce(string);
		void place_order ();
		void order_default_menu ();
		void change_hours ();
		void add_to_menu ();
		void remove_from_menu ();
		void view_orders ();
		void remove_orders ();
		int count_pizzas (ifstream&);
		int count_employees (ifstream&);
		void pop_week (ifstream&, int);
		void replace_hours(string, string, string);
		void get_new_pizza(string&, int&, int&, int&, int&);
		void print_new_menu ();
		void create_reduced_menu_price(ofstream&, int, string);
		void print_reduced_search();
		void take_order (string, string, string, string, string, string, string, string);
		void load_temp_menu (ofstream&, bool&, string&);
		void print_new_hours ();
};
