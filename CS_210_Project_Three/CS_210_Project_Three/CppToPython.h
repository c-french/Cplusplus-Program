/*
* This is a header file for the given starter code to interact between C++ and Python
* I included it in it's own class to clean up the code used in both
* Source.cpp and GroceryTracker.cpp
*/
#ifndef CPPTOPYTHON_H
#define CPPTOPYTHON_H
#include <string>

using namespace std;

class CppToPython {
	public:
		static void CallProcedure(string pName);
		static int callIntFunc(string proc, string param);
		static int callIntFunc(string proc, int param);
};
#endif
