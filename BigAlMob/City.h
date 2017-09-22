// City Class Interface: Computes and outputs values for the time slice simulation
// Mark Hiscock 07.04.2015
#pragma once

#include "citydata.h"
#include <cmath>

class City : public CityData
{
public:
	City(void);
	~City(void);

private:
	// Members
	static const int MAX_WEEKS;					// The maximum amount of weeks
	static const int IDEAL_MOB_SIZE;			// The ideal mob size
	int m_numMobsters;							// Total number of mobsters
	int m_numJail;								// Total number of mobsters in jail
	int m_numRecruit;							// The number of mobsters recruited in a week
	int m_numArrest;							// The number of mobsters arrested in a week
	int m_numEsacpe;							// The number of mobsters escaped in a week
	int m_numWeeks;								// The number of weeks that have passed

	// Methods
	void run(void);								// Starts the simulation
	void tick(void);							// One iteration of the simulation (1 week)
	void outputTableHeader(void);				// Outputs the table header
	void outputTableRow(void);					// Outputs a row of the table
	int round(float value);						// Rounds a floating point number to an integer
};

