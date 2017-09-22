// CityData Class Interface: Gets users choice of city and loads/saves test data
// Mark Hiscock 07.04.2015
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class CityData
{
public:
	CityData(void);
	~CityData(void);

protected:
	// Members
	bool m_fileLoaded;								// Flag - True if data file has loaded and validated OK
	vector<string> m_cityNames;						// Holds the city names
	int m_option;									// Users choice of city (0 = New York, 1 = Chicago, 2 = Los Angeles)
	int m_recruit;									// Recruitment rate
	int m_arrest;									// Arrest rate
	int m_escape;									// Escape rate

	// Methods
	void chooseCity(void);							// Get the users choice of city
	bool userBoolInput(void);						// Returns true if user enters 'yes' or 'y'

private:
	// Members
	static const int NUM_CITIES;					// The number of cities (3)
	static const int NUM_VALUES;					// Number of data values per city (3)
	static const string FILENAME;					// The filename for the test data ('cities.txt')
	static const int MIN_PERCENT;					// Minimum value for recruit, arrest and escape rate (0)
	static const int MAX_PERCENT;					// Maximum value for recruit, arrest and escape rate (100)
	vector<int> m_data;								// Holds the loaded data (keep this in case we need to save file)

	// Methods
	void outputOptionHeader(void);					// Outputs the city options
	bool parseInt(string str, int& result);			// Helper function to convert string to int (returns true if successful)
	int userIntInput(int min, int max);				// Returns the user input within the given range
	void loadData(void);							// Loads the city data from a text file
	bool validateData(void);						// Checks the expected number of values (NUM_CITIES * NUM_VALUES)
	void editData(void);							// Edit the test data for the chosen city
	void outputEditHeader(void);					// Outputs the edit menu header
	void saveData(void);							// Writes the city data to a text file
	void setRates(void);							// Copy test data from array
};

