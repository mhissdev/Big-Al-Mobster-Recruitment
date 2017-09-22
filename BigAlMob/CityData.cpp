// CityData Class Implementation: Gets users choice of city and loads/saves test data
// Mark Hiscock 07.04.2015
#include "StdAfx.h"
#include "CityData.h"


/****************************************************************************************
*** CityData Constructor 
****************************************************************************************/
CityData::CityData(void)
{
	this->m_fileLoaded = false;

	// Set City Names
	this->m_cityNames.push_back("New York");
	this->m_cityNames.push_back("Chicago");
	this->m_cityNames.push_back("Los Angeles");
}


/****************************************************************************************
*** CityData Destructor 
****************************************************************************************/
CityData::~CityData(void)
{
}


/****************************************************************************************
*** Function chooseCity : Get users choice of city (called by inherited City class)
****************************************************************************************/
void CityData::chooseCity(void)
{
	// Output header
	this->outputOptionHeader();

	// Get user option
	cout << "Please enter choice(1-" << this->NUM_CITIES << "): ";
	this->m_option = this->userIntInput(1, this->NUM_CITIES);

	// Decrement m_option as m_cityName array is zero based
	this->m_option--;

	// Load File
	this->loadData();

	// Validate data
	this->m_fileLoaded = this->validateData();

	if(this->m_fileLoaded)
	{
		// Data OK: Edit data if required
		this->editData();

		// Assign values to rates for recruitment, arrest and escape
		this->setRates();
	}
	else
	{
		// Invalid or Incomplete file
		cout << "ERROR: Incomplete data set\n\n";
	}
}


/****************************************************************************************
*** Function outputOptionHeader : Outputs the city options
****************************************************************************************/
void CityData::outputOptionHeader(void)
{
	system("cls");
	cout << "****************************************\n"
		 << " Please select a city (1-" << this->NUM_CITIES << ")\n"
		 << "****************************************\n\n";
	
	// List options
	for(int i=0; i<this->NUM_CITIES; i++)
	{
		cout << i + 1 << ". " << this->m_cityNames[i] << "\n";
	}

	cout << "\n";
}


/****************************************************************************************
*** Function parseInt : String to integer conversion
*** @Param string str : The string to be converted
*** @Param int& result : The resulting integer value
*** @Returns bool : true = success
****************************************************************************************/
bool CityData::parseInt(string str, int& result)
{
	if(stringstream(str) >> result)
	{
		// Successful conversion of str: assigned to result as it is passed by reference
		return true;
	}

	return false;
}


/****************************************************************************************
*** Function userIntInput : Gets the user input within the given range
*** @Param int min : Minimum valid input
*** @Param int max : Maximum valid input
*** @Returns int : A valid option within given range
****************************************************************************************/
int CityData::userIntInput(int min, int max)
{
	int value = 0;									// Integer value of user input
	bool valid = false;								// Input has not been validated

	// Loop until valid
	while(!valid)
	{
		// Get User Input
		string input;
		getline(cin, input);

		// Validate user input
		if(!this->parseInt(input, value) || value < min || value > max)
		{
			// Invalid input
			cout << "INVALID INPUT: Please enter a number (" << min << "-" << max << "): ";
		}
		else
		{
			// Valid input (break out of  loop)
			valid = true;
		}
	}

	// Return value
	return value;
}


/****************************************************************************************
*** Function loadData : Loads test data from an external text file and adds valid
*** values to m_data array
****************************************************************************************/
void CityData::loadData(void)
{
	ifstream file;										// The file stream object

	// Open the file
	file.open(this->FILENAME);

	if(file.is_open()){

		// Read each line of file
		string str;
		while(getline(file, str))
		{
			// get value
			int value;

			// Add to data array if numeric
			if(this->parseInt(str, value))
			{
				// Check value is within range
				if(value >= this->MIN_PERCENT && value <= this->MAX_PERCENT)
				{
					this->m_data.push_back(value);
				}
			}
		}

		// Close the file
		file.close();
	}
	else{
		cout << "ERROR: There was a problem locating the file '" << FILENAME << "'\n";
	}
}


/****************************************************************************************
*** Function validateData : Checks the expected number of valid values
*** @Returns bool : success = true
****************************************************************************************/
bool CityData::validateData(void)
{
	// There should be three items of data for each city (NUM_VALUES)
	if(this->m_data.size() == this->NUM_CITIES * this->NUM_VALUES)
	{
		// All data seems to be present
		return true;
	}

	// Invalid data length
	return false;
}


/****************************************************************************************
*** Function editData : Enable user to edit the test data for the chosen city
****************************************************************************************/
void CityData::editData(void)
{
	// Output header
	this->outputEditHeader();

	// Ask user if they would like to edit test data
	cout << "Would you like to change the test data for "
		 << this->m_cityNames[this->m_option] << "(Y/N)? ";

	bool userResponse = this->userBoolInput();

	if(userResponse)
	{
		// User wishes to edit data
		int index = this->m_option * this->NUM_VALUES;						// Start index in m_cityData array

		// Set recruit rate value
		cout << "\nPlease enter new value for recruitment rate("
			 << this->MIN_PERCENT << "-" << this->MAX_PERCENT << "): ";

		this->m_data[index] = this->userIntInput(this->MIN_PERCENT, this->MAX_PERCENT);

		// Set arrest rate value
		cout << "Please enter new value for arrest rate("
			 << this->MIN_PERCENT << "-" << this->MAX_PERCENT << "): ";

		this->m_data[index + 1] = this->userIntInput(this->MIN_PERCENT, this->MAX_PERCENT);

		// Set escape rate value
		cout << "Please enter new value for escape rate("
			 << this->MIN_PERCENT << "-" << this->MAX_PERCENT << "): ";

		this->m_data[index + 2] = this->userIntInput(this->MIN_PERCENT, this->MAX_PERCENT);

		// Save data to file
		this->saveData();
	}
}


/****************************************************************************************
*** Function outputEditHeader : Outputs the edit menu header
****************************************************************************************/
void CityData::outputEditHeader(void)
{
	// The start index for the chosen city in the  m_cityData array
	int index = this->m_option * this->NUM_VALUES;

	// Output city name and test data for recruit/arrest/escape rates
	system("cls");
	cout << "****************************************\n"
		 << "City: " << this->m_cityNames[this->m_option] << "\n"
		 << "****************************************\n\n"
		 << "Recruit rate = " << this->m_data[index]  << "%\n"
		 << "Arrest rate = " << this->m_data[index + 1] << "%\n"
		 << "Esacpe rate = " << this->m_data[index + 2] << "%\n\n";
}


/****************************************************************************************
*** Function userBoolInput : Gets user response to yes/no question
*** @Returns bool : yes = true
****************************************************************************************/
bool CityData::userBoolInput()
{
	bool value;										// Boolean value to be returned
	bool valid = false;								// Input has not been validated

	// Loop until valid
	while(!valid)
	{
		// Get user input
		string input;
		getline(cin, input);

		// Convert input to lowercase
		transform(input.begin(), input.end(), input.begin(), ::tolower);

		// Check input
		if(input == "y" || input == "yes")
		{
			// User entered yes
			value =  true;
			valid = true;
		}
		else if(input == "n" || input == "no")
		{
			// User entered no
			value = false;
			valid = true;
		}
		else
		{
			// Invalid input
			cout << "INVALID INPUT: Please enter 'Y' for yes or 'N' for no: ";
		}
	}

	// Return value
	return value;
}


/****************************************************************************************
*** Function saveData : Writes all city test data to a text file
****************************************************************************************/
void CityData::saveData(void)
{
	this->outputEditHeader();
	cout << "Would you like to save the data(Y/N)? ";

	bool userResponse = this->userBoolInput();

	if(userResponse)
	{
		ofstream file;										// The file stream object

		// Open the file
		file.open(this->FILENAME);

		if(file.is_open())
		{
			// Write m_data array to file
			int len = this->m_data.size();

			for(int i=0; i<len; i++)
			{
				file << this->m_data[i] << "\n";
			}

			// Close the file
			file.close();
		}
		else
		{
			cout << "ERROR: Unable to save file. Please ensure write permissions are enabled!\n";
			system("pause");
		}
	}
}


/****************************************************************************************
*** Function setRates : Copies recruit/arrest/escape rates from m_data array to
*** member variables
****************************************************************************************/
void CityData::setRates(void)
{
	// The start index for the chosen city in the  m_cityData array
	int index = this->m_option * this->NUM_VALUES;

	// Set values of rates
	this->m_recruit = this->m_data[index];
	this->m_arrest = this->m_data[index + 1];
	this->m_escape = this->m_data[index + 2];

	// Clean up as we no longer need m_data
	this->m_data.clear();
}


/****************************************************************************************
*** Constants
****************************************************************************************/
const int CityData::NUM_CITIES = 3;
const string CityData::FILENAME = "cities.txt";
const int CityData::NUM_VALUES = 3;
const int CityData::MIN_PERCENT = 0;
const int CityData::MAX_PERCENT = 100;