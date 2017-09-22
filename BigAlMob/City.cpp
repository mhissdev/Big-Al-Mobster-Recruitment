// City Class Implementation: Computes and outputs values for the time slice simulation
// Mark Hiscock 07.04.2015
#include "StdAfx.h"
#include "City.h"

/****************************************************************************************
*** City Constructor 
****************************************************************************************/
City::City(void)
{
	bool isRunning = true;							// Application is running

	while(isRunning)
	{
		this->m_numMobsters = 0;
		this->m_numJail = 0;

		// Get users choice of city and load/save test data
		this->chooseCity();

		if(this->m_fileLoaded)
		{
			// Test Data has been loaded OK so run the simulation
			this->run();

			// Output summary
			cout << "\n\nAfter " << ++this->m_numWeeks << " weeks Big Al managed to recruit "
				 << this->m_numMobsters << " mobsters!\n\n";

			// Ask the user if they would like to run application again
			cout << "Would you like to run the simulation again(Y/N)?";
			isRunning = this->userBoolInput();
		}
		else
		{
			// Hopefully we will never get here!
			cout << "Sorry, unable to run simulation!\n";
			isRunning = false;
		}
	}

}


/****************************************************************************************
*** City Destructor 
****************************************************************************************/
City::~City(void)
{
}


/****************************************************************************************
*** Function run : Runs the time slice simulation 
****************************************************************************************/
void City::run(void)
{
	// Output table header
	this->outputTableHeader();

	// Loop for maximum weeks unless idelal total is reached
	for(int i=0; i<this->MAX_WEEKS; i++)
	{
		// Set week number
		this->m_numWeeks = i;

		// Calculate weekly values
		this->tick();

		// Check if ideal total has been reached
		if(this->m_numMobsters >= this->IDEAL_MOB_SIZE)
		{
			// Break out of loop
			i = this->MAX_WEEKS;
		}
	}
}


/****************************************************************************************
*** Function tick : One iteration of the simulation (1 week)
****************************************************************************************/
void City::tick(void)
{
	// Calculate the difference between number of mobsters and ideal size
	int difference = this->IDEAL_MOB_SIZE - this->m_numMobsters;

	// Calculate number of mobsters recruited
	this->m_numRecruit = this->round(difference * this->m_recruit * 0.01f);

	// Calculate number of mobsters arrested
	this->m_numArrest = this->round(this->m_numMobsters * this->m_arrest * 0.01f);

	// Calculate number of mobsters escaped
	this->m_numEsacpe = this->round(this->m_numJail * this->m_escape * 0.01f);

	// Output row
	this->outputTableRow();

	// Update totals
	this->m_numMobsters += this->m_numRecruit + this->m_numEsacpe - this->m_numArrest;
	this->m_numJail += this->m_numArrest - this->m_numEsacpe;
}


/****************************************************************************************
*** Function outputTableHeader : Outputs the results table header
****************************************************************************************/
void City::outputTableHeader(void)
{
	// Clear screen
	system("cls");
	// Output city name, rates and table headings
	cout << "****************************************************\n"
		 << " City Overview: " << this->m_cityNames[this->m_option] << "\n"
		 << "****************************************************\n\n"
		 << "Rates: Recruit=" << this->m_recruit  << "%" 
		 << " Arrest=" << this->m_arrest  << "%" 
		 << " Escape=" << this->m_escape << "%\n\n"
		 << "#Week\t#Mobs\t#Jail\t#Recr\t#Arrest\t#Escape\n"
		 << "____________________________________________________\n";
}


/****************************************************************************************
*** Function outputTableRow: Outputs a row of the table
****************************************************************************************/
void City::outputTableRow(void)
{
	// Output weeky totals
	cout << this->m_numWeeks
		 << "\t" << this->m_numMobsters
		 << "\t" << this->m_numJail
		 << "\t" << this->m_numRecruit 
		 << "\t" << this->m_numArrest
		 << "\t" << this->m_numEsacpe << "\n";
}


/****************************************************************************************
*** Function round : Rounds a number to nearest Integer (.5 is rounded up)
*** @Param float value : The value to be rounded
*** @Returns int : The result of the rounded number
****************************************************************************************/
int City::round(float value)
{
	// Round floating point number
	float result = floor(value + 0.5f);

	// Cast result to return value as integer
	return static_cast<int>(result);
}


/****************************************************************************************
*** Constants
****************************************************************************************/
const int City::MAX_WEEKS = 10;
const int City::IDEAL_MOB_SIZE = 50;
