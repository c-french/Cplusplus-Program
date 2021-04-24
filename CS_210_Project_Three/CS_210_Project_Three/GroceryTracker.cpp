/*
* This class utilizes the given starter code (contained in CppToPython.cpp) to call functions written in
* PythonCode.py to read the file InputFile.txt, find the frequency of the items contained, write a file frequency.dat
* based on that, and pass it back to C++ to read the contained data
*/
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream> //read file
#include <conio.h> //for _getch()
#include <sstream>

using namespace std;

#include "GroceryTracker.h"
#include "CppToPython.h"

void GroceryTracker::PrintMenu() {
	/*this function will be the "starting screen", giving the user options of what to do in the program, then call the appropriate function
	requested by the user
	*/
	char ch;

	cout << setfill('#') << setw(50) << "#" << endl;
	cout << setfill(' ') << setw(40) << "What would you like to do?" << setw(10) << endl;
	cout << setfill('#') << setw(50) << "#" << endl;
	cout << "1: List items purchased with quantities" << endl;
	cout << "2: Number of times specific item was purchased" << endl;
	cout << "3: Create a histogram" << endl;
	cout << "4: Exit" << endl;
	cout << setfill('#') << setw(50) << "#" << endl;

	ch = _getch();
	if (ch == '1') {
		PrintQuantities();
		cout << endl;
		PrintMenu();
	}
	else if (ch == '2') {
		Frequency();
		cout << endl;
		PrintMenu();
	}
	else if (ch == '3') {
		MakeFile();
		Histogram();
		cout << endl;
		PrintMenu();
	}
	else if (ch == '4') {
		//quit program
		return;
	}
	else {
		//if user inputs anything else, tell them what went wrong and try again
		cout << "Invalid entry.  Please enter 1, 2, or 3" << endl;
		cout << endl;
		PrintMenu();
	}
}

void GroceryTracker::Frequency() {
	string item;
	int quantity;
	cout << "Enter item name: " << endl;
	cin >> item;
	for (int i = 0; i < item.length() + 1; ++i) {
		/*validating input for Python.  the dictionary Python creates has the first character capitalized in the key
		* rather than redefine the dict object to ignore the case of the key, just use our C++ to edit our input string
		* to match the case of the key in Python
		*/
		if (islower(item[i])) {
			if (i == 0) {
				//if this is the first char in the string, we want it to be uppercase
				item[i] = toupper(item[i]);
			}
			//if it's not the first char, we want it lowercase
		}
		else {
			if (i != 0) {
				//if this isn't the first char in the string, make it lowercase
				item[i] = tolower(item[i]);
			}
		}

	}

	quantity = CppToPython::callIntFunc("LookFor", item);
	if (quantity == 0) {
		//Python reads the file and makes a dictionary from what is on the list. if something is not on the list, the function returns 0
		//this lets the user know it wasn't found
		cout << "Item not found" << endl;
	}
	else {
		//returns item and quantity to user
		cout << item << " was found " << quantity << " times." << endl;
	}
}

void GroceryTracker::PrintQuantities(){
	//calls the PrintItems function from Python
	CppToPython::CallProcedure("PrintItems");
}

void GroceryTracker::MakeFile() {
	CppToPython::CallProcedure("MakeFile");
}

void GroceryTracker::Histogram() {
	/* this function will read from the 'frequency.dat' file created by Python and print to the console
	* a histogram using asterisks to visually represent the quantities of the item
	*/
	ifstream readFS;
	string line;

	//open file made in Python
	readFS.open("frequency.dat");
	//make sure we opened it
	if (!readFS.is_open()) {
		cout << "ERROR: Could not open frequency.dat" << endl;
		return;
	}
	// iterate over text file, adding whole line to string 'line'
	while (getline(readFS, line)) {
		string item;
		int amount;

		stringstream ss(line);
		//first item in the line, followed by the amount.  this will store each one to their own variables
		ss >> item;
		ss >> amount;
		//print item name and placeholder for histogram
		cout << item << " ";
		//for the given value in 'amount', print an asterisk to the line
		for (int i = 0; i < amount; ++i) {
			cout << "*";
		}
		//finish printing the line to prepare for the next one
		cout << endl;
	}
	//close the file
	readFS.close();
}