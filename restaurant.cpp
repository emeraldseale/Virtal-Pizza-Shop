/********************************************************************************************************************************************************** Program: restaurant.cpp
** Author: Emerald Seale
** Date: 4/24/18
** Description: Holds all function bodies for the Restaurant class
** Input: String numbers to choose different functions
** Output: Prints to screen and .txt files
********************************************************************************************************************************************************/

#include "restaurant.h"
#include <iostream>
#include <fstream>

using namespace std;

/********************************************************************************************************************************************************** Function: Restaurant
** Description: Default constructor for the Restaurant class
** Parameters: None
** Pre-Conditions: An object of the Restaurant class is initialized 
** Post-Conditions: An object is created and all its member variables are initialized to default
********************************************************************************************************************************************************/
Restaurant::Restaurant () {

	Menu menu;
	employees = NULL;
	week = NULL;
	name = "Default";
	phone = "000-000-0000";
	address = "0000 Default";	
}

/********************************************************************************************************************************************************** Function: Restaurant
** Description: Non-default constructor for the Restaurant class
** Parameters: Integer numPizzas
** Pre-Conditions: An object of the Pizza class is initialized with inputs
** Post-Conditions: An object is created and all of its member variables are set to the input
********************************************************************************************************************************************************/
Restaurant::Restaurant (string n, string p, string a, int ne, int nd) {

	name = n;
	phone = p;
	address = a;
	employees = new employee[ne];
	week = new hours[nd];

}

/********************************************************************************************************************************************************** Function: Restaurant
** Description: Copy constructor for the Restaurant class
** Parameters: Constant parameter Restaurant copy by reference
** Pre-Conditions: A Menu object is passed or returned by value
** Post-Conditions: The object goes through a deep copy as opposed to a shallow one
********************************************************************************************************************************************************/
Restaurant::Restaurant (const Restaurant& copy) {

	name = copy.name;
	phone = copy.phone;
	address = copy.address;
	menu = copy.menu;
	employees = copy.employees;
	week = copy.week;
}

/********************************************************************************************************************************************************** Function: ~Restaurant
** Description: Destructor for the Restaurant class
** Parameters: None
** Pre-Conditions: A Restaurant object goes out of scope
** Post-Conditions: The object is destroyed and its memory is freed from the heap
********************************************************************************************************************************************************/Restaurant::~Restaurant () {
	
	delete [] employees;
	delete [] week;
}

/********************************************************************************************************************************************************** Function: operator=
** Description: Assignment operator overload 
** Parameters: Constant Restaurant copy by reference
** Pre-Conditions: A Restaurant object is assigned the value of another Pizza object
** Post-Conditions: The Restaurant object's member variables are equal to what it was assigned, a deep copy not shallow
********************************************************************************************************************************************************/
const Restaurant& Restaurant::operator= (const Restaurant& copy) {
	
	name = copy.name;
	phone = copy.phone;
	address = copy.address;
	menu = copy.menu;
	if (employees != NULL) {
		delete [] employees;	
	}
	employees = copy.employees;
	if (week != NULL) {
		delete [] week;
	}
	week = copy.week;
	return *this;
}

/********************************************************************************************************************************************************** Functions: All accessor functions (get_blank)
** Description: Gets a value from the private portion of the Restaurant class and returns it
** Parameters: None
** Pre-Conditions: The variable is in the private sphere and unaccessable
** Post-Conditions: The variable is returned and accessable
********************************************************************************************************************************************************/
Menu Restaurant::get_menu () { return menu; }
employee* Restaurant::get_employees () { return employees; }
hours* Restaurant::get_week () { return week; }
string Restaurant::get_name () { return name; }
string Restaurant::get_phone () { return phone; }
string Restaurant::get_address () { return address; }

/********************************************************************************************************************************************************** Functions: All mutator functions (set_blank)
** Description: Changes a value from the private portion of the Restaurant class
** Parameters: Integer np and array of Pizzas p
** Pre-Conditions: The variable in the private sphere is unaccessable and unchangeable, remains default
** Post-Conditions: The variable is mutated
********************************************************************************************************************************************************/void Restaurant::set_menu (Menu m) { menu = m; }
void Restaurant::set_employees (employee* e) { employees = e; }
void Restaurant::set_week (hours* w) { week = w; }
void Restaurant::set_name (string n) { name = n; }
void Restaurant::set_phone (string p) { phone = p; }
void Restaurant::set_address (string a) { address = a; }

/********************************************************************************************************************************************************** Function: countPizzas
** Description: Counts the number of lines in a given pizza file
** Parameters: ifstream object f by reference
** Pre-Conditions: Text file must not be empty
** Post-Conditions: Returns the number of lines
********************************************************************************************************************************************************/
int Restaurant::count_pizzas (ifstream& f) {
	
	int count = 0;
	f.open("menu.txt");
	while (!f.eof()) {
		f.ignore(256, '\n');
		count++;
	}
	f.clear();
	f.seekg(0, ios::beg);
	f.close();
	if (count != 0) {
		count = (count - 1);
	}
	return count;
}

/********************************************************************************************************************************************************** Function: countEmployees
** Description: Counts the number of lines in a given employee text file
** Parameters: ifstream object f by reference
** Pre-Conditions: All text files must be populated
** Post-Conditions: The number of lines is returned
********************************************************************************************************************************************************/
int Restaurant::count_employees (ifstream& f) {
	
	int count = 0;
	f.open("employee.txt");
	while (!f.eof()) {
		f.ignore(256, '\n');
		count++;
	}
	f.clear();
	f.seekg(0, ios::beg);
	if (count != 0) {
		count = (count - 1);
	}
	return count;
}

/********************************************************************************************************************************************************** Function: pop_week
** Description: Populates the week days and hours from the file
** Parameters: ifstream object f by reference, integer numDays
** Pre-Conditions: All text files must be named and formatted correctly
** Post-Conditions: The week array is populated
********************************************************************************************************************************************************/
void Restaurant::pop_week (ifstream& f, int numDays) {
	
	for (int i = 0; i < numDays; i++) {
		f >> week[i].day;
		f >> week[i].openHour;
		f >> week[i].closeHour;
	}
}

/********************************************************************************************************************************************************** Function: load_data
** Description: Populates all member variables with information read from text files
** Paramters: None
** Pre-Conditions: All text files must be named and formatted correctly
** Post-Conditions: All classes' member variables are no longer default
********************************************************************************************************************************************************/
void Restaurant::load_data () {

	ifstream f;
	int countPizzas = count_pizzas(f);
	menu.set_num_pizzas(countPizzas);
	menu.set_pizzas(countPizzas);
	int countEmployees = count_employees(f);
	employees = new employee[countEmployees];
	for (int i = 0; i < countEmployees; i++) {
		f >> employees[i].id;
		f >> employees[i].firstName;
		f >> employees[i].lastName;
		f >> employees[i].password;
	}
	f.close();
	f.open("restaurant_info.txt");
	getline(f, name);
	getline(f, phone);
	getline(f, address);
	int numDays = 0;
	f >> numDays;
	week = new hours[numDays];
	pop_week(f, numDays);
}

/********************************************************************************************************************************************************** Function: login
** Description: Checks to see if the inputted login information for employees is valid
** Parameters: string id, string password
** Pre-Conditions: A string id and password must be input
** Post-Conditions: It is determined whether or not the input is valid
********************************************************************************************************************************************************/bool Restaurant::login (string id, string password) {

	ifstream f;
	string tempID = " ";
	string tempPass = " ";
	f.open("employee.txt");
	while (!f.eof()) {
		f >> tempID;
		if (tempID == id) {
			f.ignore(32, ' ');
			f.ignore(32, ' ');
			f.ignore(32, ' ');
			f >> tempPass;
			if (tempPass == password) {
				return true;
			}
		}
	}
	f.close();
	cout << "I'm sorry, we don't recognize that ID and/or password. Please try again." << endl;
	return false;
}

/********************************************************************************************************************************************************** Function: intro
** Description: Introduction to the program
** Parameters: None
** Pre-Conditions: The program must be run via the executable
** Post-Conditions: The program is begun
********************************************************************************************************************************************************/char Restaurant::intro () {

	char choice = 0;
	cout << "\nWelcome to Bytes Pizza!" << endl;
	do {
		cout << "If you are a customer, enter c. If you are an employee, enter e. If you'd like to quit, enter q." << endl;
		cin >> choice;
	} while (choice != 'c' && choice != 'e' && choice != 'q');
	return choice;
}

/********************************************************************************************************************************************************** Function: enter_login
** Description: Prompts the user to enter their login information
** Parameters: None
** Pre-Conditions: The user must have entered an 'e' for their choice
** Post-Conditions: The login information is sent to the login to check for validity
********************************************************************************************************************************************************/
void Restaurant::enter_login () {

	string enterID = " ";
	string enterPass = " ";
	do {
		cout << "\nPlease enter your login information. Enter q for both to quit." << endl;
		cout << "Enter ID: ";
		cin >> enterID;
		cout << "Enter Password: ";
		cin >> enterPass;
		if (enterID == "q" && enterPass == "q") {
			break;
		}
	} while (!login(enterID,enterPass));
	if (enterID == "q" && enterPass == "q") {
		char choice = intro();	
		choice_select(choice);
	} else {
		cout << "Login successful. Welcome." << endl;
	}
}

/********************************************************************************************************************************************************** Function: display_employee_options
** Description: Prints the options for employees to the screen
** Parameters: None
** Pre-Conditions: There is nothing printed to the screen
** Post-Conditions: There are options printed to the screen
********************************************************************************************************************************************************/
void Restaurant::display_employee_options () {

	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1. Change hours" << endl;
	cout << "2. View orders" << endl;
	cout << "3. Remove order" << endl;
	cout << "4. Add item to menu" << endl;
	cout << "5. Remove item from menu" << endl;
	cout << "6. View menu" << endl;
	cout << "7. View hours" << endl;
	cout << "8. View address" << endl;
	cout << "9. View phone" << endl;
	cout << "10. Log out" << endl;
	cout << "\nPlease enter your selection: " << endl;
}

/********************************************************************************************************************************************************** Function: replace_hours
** Description: Replaces a given line with the new information
** Parameters: Character day, int start, int end
** Pre-Conditions: The hours are all whatever was read from the original file
** Post-Conditions: The hours are replaced with user input
********************************************************************************************************************************************************/
void Restaurant::replace_hours (string dayWeek, string start, string end) {

	for (int i = 0; i < 7; i++) {
		if (week[i].day == dayWeek) {
			week[i].openHour = start;
			week[i].closeHour = end;
		}
	}
}

/********************************************************************************************************************************************************** Function: print_new_hours
** Description: Prints the new hours to the screen after they've been changed
** Parameters: None
** Pre-Conditions: The hours have been changed somehow
** Post-Conditions: The new hours are printed to the screen
********************************************************************************************************************************************************/
void Restaurant::print_new_hours () {

	cout << "\nHere are the new hours:" << endl;
	for (int i = 0; i < 7; i++) {
		cout << week[i].day << " ";
		cout << week[i].openHour << " ";
		cout << week[i].closeHour << endl;
	}
}

/********************************************************************************************************************************************************** Function: change_hours
** Description: Allows the user to change the hours of the store
** Parameters: None
** Pre-Conditions: The hours are whatever's in the file originally
** Post-Conditions: The hours have been changed and rewritten back to the original file
********************************************************************************************************************************************************/
void Restaurant::change_hours () {

	ofstream w;
	w.open("temp.txt");
	string day = " ", start = " ", end = " ";
	cout << "Enter which day you'd like to change the hours for: ";
	getline(cin, day);
	cout << "What should the opening time be?";
	getline(cin, start);
	cout << "What should the closing time be?";
	getline(cin, end);
	replace_hours(day, start, end);
	w << name << endl << phone << endl << address << endl << "7" << endl;
	for (int i = 0; i < 7; i++) {
		w << week[i].day << " ";
		w << week[i].openHour << " ";
		w << week[i].closeHour << endl;
	}
	w.close();
	remove("restaurant_info.txt");
	rename("temp.txt", "restaurant_info.txt");
	print_new_hours();
}

/********************************************************************************************************************************************************** Function: get_new_pizza
** Description: Gets all pizza info from the user to add a new pizza to the menu
** Parameters: name, smallCost, mediumCost, largeCost, and numIngredients by reference
** Pre-Conditions: These are initialized to garbage values
** Post-Conditions: These are set to whatever the user input
********************************************************************************************************************************************************/
void Restaurant::get_new_pizza(string& name, int& smallCost, int& mediumCost, int& largeCost, int& numIngredients) {

	cout << "\nEnter the name of your pizza: ";
	getline(cin, name);
	cout << "Enter the small cost: ";
	cin >> smallCost;
	cout << "Enter the medium cost: ";
	cin >> mediumCost;
	cout << "Enter the large cost: ";
	cin >> largeCost;
	cout << "Enter the number of ingredients: ";
	cin >> numIngredients;
}

/********************************************************************************************************************************************************** Function: print_new_menu
** Description: Prints the new menu to the screen after changes have been made to it
** Parameters: None
** Pre-Conditions: The menu has been altered in some way
** Post-Conditions: The menu is now printed to the screen
********************************************************************************************************************************************************/
void Restaurant::print_new_menu () {

	ifstream f;
	string line;
	f.open("menu.txt");
	cout << "\nHere is the new menu:" << endl;
	while (!f.eof()) {
		getline(f, line);
		cout << line << endl;
	}
	f.close();
}

/********************************************************************************************************************************************************** Function: add_to_menu
** Description: Allows an employee to add an item to the menu
** Parameters: None
** Pre-Conditions: User must be signed in as an employee
** Post-Conditions: A pizza object is added to the menu
********************************************************************************************************************************************************/
void Restaurant::add_to_menu () {

	ofstream w;
	string name, ingredients;
	int smallCost, mediumCost, largeCost, numIngredients;
	int newNumPizzas = (menu.get_num_pizzas() + 1);
	delete [] menu.get_pizzas();
	menu.set_num_pizzas(newNumPizzas);
	w.open("menu.txt", ofstream::app);
	get_new_pizza(name, smallCost, mediumCost, largeCost, numIngredients);
	w << name << " " << smallCost << " " << mediumCost << " " << largeCost << " " << numIngredients << " ";
	for (int i = 0; i < numIngredients; i++) {
		ingredients = " ";
		cout << "Enter ingredient " << (i + 1) << ": ";
		cin >> ingredients;
		w << ingredients;
		if (i != (numIngredients - 1)) {
			w << " ";
		}
	}
	w.close();
	menu.set_pizzas(newNumPizzas);	
	print_new_menu();
}
 
/********************************************************************************************************************************************************** Function: remove_from_menu
** Description: Allows an employee to remove a pizza from the menu
** Parameters: None
** Pre-Conditions: User must be signed in as an employee
** Post-Conditions: A pizza object is removed from the menu
********************************************************************************************************************************************************/
void Restaurant::remove_from_menu () {

	ofstream w;
	string nameDel = " ";
	int newNumPizzas = (menu.get_num_pizzas() - 1);
	w.open("temp.txt");
	cout << "Enter the name of the pizza you'd like to take off the menu: ";
	getline(cin, nameDel);
	for (int i = 0; i < (newNumPizzas + 1); i++) {
		if (menu.get_pizzas()[i].get_name() != nameDel) {
			w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
			w << menu.get_pizzas()[i].get_medium_cost() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
			w << menu.get_pizzas()[i].get_num_ingredients() << " ";
			for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
				w << menu.get_pizzas()[i].get_ingredients()[j] << " ";	
			}
			w << endl;
		}
	}
	delete [] menu.get_pizzas();
	menu.set_num_pizzas(newNumPizzas);
	menu.set_pizzas(newNumPizzas);
	w.close();
	remove("menu.txt");
	rename("temp.txt", "menu.txt");
	print_new_menu();
}

/********************************************************************************************************************************************************** Function: remove_orders
** Description: Allows an employee to remove a specified order
** Parameters: None
** Pre-Conditions: Employee must select "3"
** Post-Conditions: The chosen order has been deleted from the file
********************************************************************************************************************************************************/
void Restaurant::remove_orders () {

	ifstream f;
	ofstream w;
	char removeOrder;
	string line, orderNum;
	cout << "Please enter the number of the order you'd like to remove: ";
	cin >> removeOrder;
	f.open("orders.txt");
	w.open("temp.txt");
	while (!f.eof()) {
		line = " ";
		getline(f, line);
		if (line[0] != removeOrder) {
			w << line << endl;
		}
	}
	f.close();
	w.close();
	remove("orders.txt");
	rename("temp.txt", "orders.txt");
	cout << "\nThe order has been removed. Here are the remaining orders:" << endl;
	f.open("orders.txt");
	while (!f.eof()) {
		getline(f, line);
		cout << line << endl;
	}
	f.close();

}	

/********************************************************************************************************************************************************** Function: view_orders
** Description: Prints all orders from the .txt file to the screen
** Parameters: None
** Pre-Conditions: The orders are not visible on the screen, but are in the .txt file
** Post-Conditions: The orders are printed to the screen
********************************************************************************************************************************************************/
void Restaurant::view_orders () {

	ifstream f;
	f.open("orders.txt");
	string line;
	cout << "\nHere are the orders:" << endl;
	while (!f.eof()) {
		getline(f, line);
		cout << line << endl;
	}
}

/********************************************************************************************************************************************************** Function: view_menu
** Description: Prints the menu to the screen
** Parameters: None
** Pre-Conditions: The menu is held within the .txt file
** Post-Conditions: The menu is printed to the screen
********************************************************************************************************************************************************/
void Restaurant::view_menu () {

	cout << "\nHere is the menu:" << endl;
	for (int i = 0; i < menu.get_num_pizzas(); i++) {
		cout << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
		cout << menu.get_pizzas()[i].get_medium_cost() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
		cout << menu.get_pizzas()[i].get_num_ingredients() << " ";
		for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
			cout << menu.get_pizzas()[i].get_ingredients()[j] << " ";
		}
		cout << endl;
	}
}

/********************************************************************************************************************************************************** Function: view_hours
** Description: Prints the hours to the screen
** Parameters: None
** Pre-Conditions: Information is in a .txt file
** Post-Conditions: Information is printed to the screen
********************************************************************************************************************************************************/
void Restaurant::view_hours () {

	cout << "\nHere are the hours:" << endl;
	for (int i = 0; i < 7; i++) {
		cout << week[i].day << " ";
		cout << week[i].openHour << " ";
		cout << week[i].closeHour << endl;
	}
}

/********************************************************************************************************************************************************** Function: view_address
** Description: Prints the address to the screen
** Parameters: None
** Pre-Conditons: The information is in a .txt file
** Post-Conditions: The information is printed to the screen
********************************************************************************************************************************************************/
void Restaurant::view_address () {

	cout << "\nHere is the address: " << address << endl;
}

/********************************************************************************************************************************************************** Function: view_phone
** Description: Prints the phone number to the screen
** Parameters: None
** Pre-Conditions: The information is in a .txt file
** Post-Conditons: The information is printed to the screen
********************************************************************************************************************************************************/
void Restaurant::view_phone () {
	
	cout << "\nHere is the phone number: " << phone << endl;
}

/********************************************************************************************************************************************************** Function: employee_functionality
** Description: Presents all employee functionality and options
** Parameters: None
** Pre-Conditions: Employee must log in successfully
** Post-Conditions: Employee may choose whichever functionality they please
********************************************************************************************************************************************************/
void Restaurant::employee_functionality () {
	
	string selection = " ";	
	do {
		display_employee_options();
		getline(cin, selection);
		if (selection == "1") {
			change_hours();
		} else if (selection == "2") {
			view_orders();
		} else if (selection == "3") {
			remove_orders();
		} else if (selection == "4") {
			add_to_menu();
		} else if (selection == "5") {
			remove_from_menu();
		} else if (selection == "6") {
			view_menu();
		} else if (selection == "7") {
			view_hours();
		} else if (selection == "8") {
			view_address();
		} else if (selection == "9") {
			view_phone();
		} else if (selection == "10"){
			char choice = intro();
			choice_select(choice);

		}
	} while (selection != "10");
}

/********************************************************************************************************************************************************** Function: display_customer_options
** Description: Displays all options for a customer user
** Parameters: None
** Pre-Conditions: User must be a customer
** Post-Conditions: All options are printed to the screen
********************************************************************************************************************************************************/
void Restaurant::display_customer_options () {

	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1. View menu" << endl;
	cout << "2. Search by cost" << endl;
	cout << "3. Search by ingredients" << endl;
	cout << "4. Place order" << endl;
	cout << "5. View hours" << endl;
	cout << "6. View address" << endl;
	cout << "7. View phone" << endl;
	cout << "8. Log out" << endl;
	cout << "\nPlease enter your selection: ";
}

/********************************************************************************************************************************************************** Function: create_reduced_menu_price
** Description: Prints the desired pizzas to the temporary menu
** Parameters: ofstream object w, int upperPrice, string size
** Pre-Conditions: The user must enter a number that is above some pizza
** Post-Conditions: The user is given a special reduced menu to order from
********************************************************************************************************************************************************/
void Restaurant::create_reduced_menu_price (ofstream& w, int upperPrice, string size) {
	
	for (int i = 0; i < menu.get_num_pizzas(); i++) {
		if (size == "s") {
			if (menu.get_pizzas()[i].get_small_cost() < upperPrice) {
				w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
				w << menu.get_pizzas()[i].get_num_ingredients() << " ";
			for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
				w << menu.get_pizzas()[i].get_ingredients()[j] << " ";	
			}
			w << endl;
			}
		} else if (size == "m") {
			if (menu.get_pizzas()[i].get_medium_cost() < upperPrice) {
				w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_medium_cost() << " ";
				w << menu.get_pizzas()[i].get_num_ingredients() << " ";
			for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
				w << menu.get_pizzas()[i].get_ingredients()[j] << " ";	
			}
			w << endl;
			} 
		} else {
			if (menu.get_pizzas()[i].get_large_cost() < upperPrice) {
				w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
				w << menu.get_pizzas()[i].get_num_ingredients() << " ";
			for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
				w << menu.get_pizzas()[i].get_ingredients()[j] << " ";	
			}
			w << endl;
			}
		}
	}
}

/********************************************************************************************************************************************************** Function: take_order
** Description: Copies the order to the orders.txt file
** Parameters: strings choice, firstName, lastName, ccNum, address, phone, pizzaName, size, and quantity
** Pre-Conditions: There are no orders
** Post-Conditions: There is an order
********************************************************************************************************************************************************/
void Restaurant::take_order (string fN, string lN, string ccNum, string address, string phone, string pN, string size, string quantity) {

	ifstream f;
	ofstream w;
	f.open("orders.txt");
	w.open("orders.txt", fstream::app);
	int orderNum = 0;
	while (!f.eof()) {
		f.ignore(256, '\n');
		orderNum++;
	}
	f.close();
	w << orderNum << " " << fN << " " << lN << " " << ccNum << " " << address << " " << phone << " " << pN << " " << size << " " << quantity << endl;
	w.close();
	cout << "\nYour order has been placed and should arrive shortly." << endl;
}

/********************************************************************************************************************************************************** Function: place_order
** Description: Allows the customer to place an order off the menu
** Parameters: None
** Pre-Conditions: The orders.txt file is empty
** Post-Conditions: The orders.txt file is populated with an order
********************************************************************************************************************************************************/
void Restaurant::place_order () {

	string choice, firstName, lastName, ccNum, address, phone, pizzaName, size, quantity;
	do {
		cout << "Would you like to place an order off your reduced search? Enter (1) for yes and (2) for no: ";
		getline(cin, choice);
	} while (choice != "1" && choice != "2");
	if (choice == "1") {
		cout << "Please enter your first name: ";
		getline(cin, firstName);
		cout << "Last name: ";
		getline(cin, lastName);
		cout << "Credit card number: ";
		getline(cin, ccNum);
		cout << "Address: ";
		getline(cin, address);
		cout << "Phone: ";
		getline(cin, phone);
		cout << "Name of the pizza you're ordering: ";
		getline(cin, pizzaName);
		cout << "What size would you like: ";
		getline(cin, size);
		cout << "How many: ";
		getline(cin, quantity);
		take_order(firstName, lastName, ccNum, address, phone, pizzaName, size, quantity);
	}
}

/********************************************************************************************************************************************************** Function: search_menu_by_price
** Description: Allows the customer to reduce their menu by price
** Parameters: None
** Pre-Conditions: User must be a customer and enter "2"
** Post-Conditions: The user is given a choice to order off their reduced menu
********************************************************************************************************************************************************/
void Restaurant::search_menu_by_price () {

	ifstream f;
	ofstream w;
	w.open("temp_menu.txt");
	int upperPrice = 0;
	string size = " ";
	cout << "Enter your upper limit for price: ";
	cin >> upperPrice;
	do {
		cout << "Enter the pizza size you'd like, 's' for small, 'm' for medium, or 'l' for large: ";
		cin >> size;
	} while (size != "s" && size != "m" && size != "l");
	create_reduced_menu_price(w, upperPrice, size);
	w.close();
	f.open("temp_menu.txt");
	cout << "\nHere are the pizzas in that size below your price range:" << endl;
	while (!f.eof()) {
		getline(f, size);
		cout << size << endl;
	}
	remove("temp_menu.txt");
	place_order();
}

/********************************************************************************************************************************************************** Function: print_reduced_search
** Description: Prints the reduced search to the screen after an inclusion or exclusion search
** Parameters: None
** Pre-Conditions: The customer must have searched by ingredients
** Post-Conditions: The reduced search is printed to the screen
********************************************************************************************************************************************************/
void Restaurant::print_reduced_search() {

	ifstream f;
	string line;
	f.open("temp_menu.txt");
	cout << "\nHere are the pizzas that matched your search:" << endl;
	while(!f.eof()) {
		getline(f, line);
		cout << line << endl;
	}
	f.close();
}

/********************************************************************************************************************************************************** Function: inclusion_search_reduce
** Description: Reduces search further by excluding an ingredient after an inclusion search
** Parameters: String ingredient
** Pre-Conditions: Customer must do an inclusion search and then select "1"
** Post-Conditions: Customer is given a reduced search and is given the option to order
********************************************************************************************************************************************************/
void Restaurant::inclusion_search_reduce (string ingredientInclude) {

	ofstream w;
	bool flag = 0;
	w.open("temp_menu.txt");
	string ingredient;
	cout << "\nWhat ingredient would you like to exclude? ";
	getline(cin, ingredient);
	for (int i = 0; i < menu.get_num_pizzas(); i++) {
		flag = false;
		for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
			if (menu.get_pizzas()[i].get_ingredients()[j] == ingredient) {
				flag = true;
			}		
		}
		if (flag == false) {
			for (int k = 0; k < menu.get_pizzas()[i].get_num_ingredients(); k++) {
				if (menu.get_pizzas()[i].get_ingredients()[k] == ingredientInclude) {
					w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
					w << menu.get_pizzas()[i].get_medium_cost() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
					w << menu.get_pizzas()[i].get_num_ingredients() << " ";
					for (int k = 0; k < menu.get_pizzas()[i].get_num_ingredients(); k++) {
						w << menu.get_pizzas()[i].get_ingredients()[k] << " ";
					}
					w << endl;
				}
			}
		}
	}
	print_reduced_search();
	remove("temp_menu.txt");
	place_order();
}

/********************************************************************************************************************************************************** Function: inclusion_search
** Description: Reduces the menu by including an ingredient
** Parameters: ofstream object w
** Pre-Conditions: Customer must select "1"
** Post-Conditions: Customer can choose to reduce by exclusion 
********************************************************************************************************************************************************/
void Restaurant::inclusion_search (ofstream& w) {

	string ingredient, reduceMore;
	cout << "What ingredient would you like to include? ";
	getline(cin, ingredient);
	for (int i = 0; i < menu.get_num_pizzas(); i++) {
		for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
			if (menu.get_pizzas()[i].get_ingredients()[j] == ingredient) {
				w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
				w << menu.get_pizzas()[i].get_medium_cost() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
				w << menu.get_pizzas()[i].get_num_ingredients() << " ";
				for (int k = 0; k < menu.get_pizzas()[i].get_num_ingredients(); k++) {
					w << menu.get_pizzas()[i].get_ingredients()[k] << " ";
				}
			}
		}
		w << endl;
	}
	print_reduced_search();
	remove("temp_menu.txt");
	do {
		cout << "Would you like to further reduce search results by excluding an ingredient? Enter (1) for yes and (2) for no: ";
		getline(cin, reduceMore);
	} while (reduceMore != "1" && reduceMore != "2");
	if (reduceMore == "1") {
		inclusion_search_reduce(ingredient);
	} else {
		place_order();
	}
}

/********************************************************************************************************************************************************** Function: exclusion_search_reduce
** Description: Further reduces the search after excluding by including an ingredient
** Parameters: String ingredientExclude
** Pre-Conditions: Customer must select "2"
** Post-Conditions: The customer is given a choice to place an order off the menu
********************************************************************************************************************************************************/
void Restaurant::exclusion_search_reduce (string ingredientExclude) {

	ofstream w;
	bool flag = 0;
	w.open("temp_menu.txt");
	string ingredient;
	cout << "\nWhat ingredient would you like to include? ";
	getline(cin, ingredient);
	for (int i = 0; i < menu.get_num_pizzas(); i++) {
		flag = false;
		for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
			if (menu.get_pizzas()[i].get_ingredients()[j] == ingredientExclude) {
				flag = true;
			}		
		}
		if (flag == false) {
			for (int k = 0; k < menu.get_pizzas()[i].get_num_ingredients(); k++) {
				if (menu.get_pizzas()[i].get_ingredients()[k] == ingredient) {
					w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
					w << menu.get_pizzas()[i].get_medium_cost() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
					w << menu.get_pizzas()[i].get_num_ingredients() << " ";
					for (int k = 0; k < menu.get_pizzas()[i].get_num_ingredients(); k++) {
						w << menu.get_pizzas()[i].get_ingredients()[k] << " ";
					}
					w << endl;
				}
			}
		}
	}
	print_reduced_search();
	remove("temp_menu.txt");
	place_order();
}

/********************************************************************************************************************************************************** Function: load_temp_menu
** Description: Populates the temporary menu for exclusion search
** Parameters: ofstream object w
** Pre-Conditions: The temp_menu.txt file is empty
** Post-Conditions: It's populated with information 
********************************************************************************************************************************************************/
void Restaurant::load_temp_menu (ofstream& w, bool& flag, string& ingredient) {

	for (int i = 0; i < menu.get_num_pizzas(); i++) {
		flag = false;
		for (int j = 0; j < menu.get_pizzas()[i].get_num_ingredients(); j++) {
			if (menu.get_pizzas()[i].get_ingredients()[j] == ingredient) {
				flag = true;
			}		
		}
		if (flag == false) {
			w << menu.get_pizzas()[i].get_name() << " " << menu.get_pizzas()[i].get_small_cost() << " ";
			w << menu.get_pizzas()[i].get_medium_cost() << " " << menu.get_pizzas()[i].get_large_cost() << " ";
			w << menu.get_pizzas()[i].get_num_ingredients() << " ";
			for (int k = 0; k < menu.get_pizzas()[i].get_num_ingredients(); k++) {
				w << menu.get_pizzas()[i].get_ingredients()[k] << " ";
			}
			w << endl;
		}
	}
}
	
/********************************************************************************************************************************************************** Function: exclusion_search
** Description: Reduces the menu by excluding an ingredient
** Parameters: ofstream object w
** Pre-Conditions: Customer must select "2"
** Post-Conditions: Customer can choose to reduce by exclusion
********************************************************************************************************************************************************/
void Restaurant::exclusion_search (ofstream& w) {

	bool flag = false;
	string ingredient, reduceMore;
	cout << "What ingredient would you like to exclude? ";
	getline(cin, ingredient);
	load_temp_menu(w, flag, ingredient);
	print_reduced_search();
	remove("temp_menu.txt");
	do {
		cout << "Would you like to further reduce search results by excluding an ingredient? Enter (1) for yes and (2) for no: ";
		getline(cin, reduceMore);
	} while (reduceMore != "1" && reduceMore != "2");
	if (reduceMore == "1") {
		exclusion_search_reduce(ingredient);
	} else {
		place_order();
	}
}

/********************************************************************************************************************************************************** Function: search_menu_by_ingredients
** Description: Allows a customer to reduce a menu down by including or excluding ingredients
** Parameters: None
** Pre-Conditions: Customer must select "3"
** Post-Conditions: Customer can order off of a reduced temporary menu
********************************************************************************************************************************************************/
void Restaurant::search_by_ingredients () {

	ifstream f;
	ofstream w;
	w.open("temp_menu.txt");
	string choice = " ";
	do {
		cout << "\nWould you like to search by (1) inclusion or (2) exclusion?" << endl << "Enter your choice: ";
		getline(cin, choice);
	} while (choice != "1" && choice != "2");
	if (choice == "1") {
		inclusion_search(w);
	} else {
		exclusion_search(w);
	}
}

/********************************************************************************************************************************************************** Function: order_default_menu
** Description: Allows the customer to order off of the entire menu
** Parameters: None
** Pre-Conditions: The customer must select "4"
** Post-Conditions: An order is placed and saved to the file
********************************************************************************************************************************************************/
void Restaurant::order_default_menu () {

	string choice, firstName, lastName, ccNum, address, phone, pizzaName, size, quantity;
	do {
		cout << "Would you like to place an order off the entire menu? Enter (1) for yes and (2) for no: ";
		getline(cin, choice);
	} while (choice != "1" && choice != "2");
	if (choice == "1") {
		cout << "Please enter your first name: ";
		getline(cin, firstName);
		cout << "Last name: ";
		getline(cin, lastName);
		cout << "Credit card number: ";
		getline(cin, ccNum);
		cout << "Address: ";
		getline(cin, address);
		cout << "Phone: ";
		getline(cin, phone);
		cout << "Name of the pizza you're ordering: ";
		getline(cin, pizzaName);
		cout << "What size would you like: ";
		getline(cin, size);
		cout << "How many: ";
		getline(cin, quantity);
		take_order(firstName, lastName, ccNum, address, phone, pizzaName, size, quantity);
	}
}

/********************************************************************************************************************************************************** Function: customer_functionality
** Description: Presents all customer functionality and options
** Parameters: None
** Pre-Conditions: User must choose 'c' to use the program as a customer
** Post-Conditions: Customer may choose whichever functionality they please
********************************************************************************************************************************************************/
void Restaurant::customer_functionality () {

	string selection = " ";
	do {
		display_customer_options();
		getline(cin, selection);
		if (selection == "1") {
			view_menu();
		} else if (selection == "2") {
			search_menu_by_price();
		} else if (selection == "3") {
			search_by_ingredients();
		} else if (selection == "4") {
			order_default_menu();
		} else if (selection == "5") {
			view_hours();
		} else if (selection == "6") {
			view_address();
		} else if (selection == "7") {
			view_phone();
		} else if (selection == "8") {
			char choice = intro();
			choice_select(choice);	
		}
	} while (selection != "8"); 
}

/********************************************************************************************************************************************************** Function: choice_select
** Description: Directs the user down a specific path depending on if they're a customer, employee, or quitting
** Parameters: Character choice
** Pre-Conditions: The user must input a valid character choice
** Post-Conditions: The user is allowed certain functionality based on their choice
********************************************************************************************************************************************************/void Restaurant::choice_select (char choice) {

	if (choice == 'c') {
		customer_functionality();
	} else if (choice == 'e') {
		enter_login();
		employee_functionality();
	} else {
		cout << "\nPlease come again!" << endl;
	}
}
