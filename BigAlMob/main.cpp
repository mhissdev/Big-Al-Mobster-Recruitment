// Mark Hiscock 13.03.2015
// A mobster recruitment simulation
// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "City.h"
#include <iostream>

using namespace std;

// Prototype functions
void splashScreen(void);

int _tmain(int argc, _TCHAR* argv[])
{
	// Output splashscreen
	splashScreen();

	// Initiate City
	City city;

	return 0;
}


// Output the splashscreen
void splashScreen(void)
{
	cout << "*******************************************************************************\n"
		 << "*                                                                             *\n"
		 << "*         WELCOME TO BIG AL'S MOB : A MOBSTER RECRUITMENT SIMULATION          *\n"
		 << "*                                                                             *\n"
		 << "*                        (Programmed by Mark Hiscock)                         *\n"
		 << "*                                                                             *\n"
		 << "*******************************************************************************\n\n"
		 << "Big Al has a choice of 3 citites.\n\n"
		 << "Which one will allow him to the recruit the most mobsters?\n\n";

	system("pause");
}
                                                                     


