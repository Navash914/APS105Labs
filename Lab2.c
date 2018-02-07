#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Declare Functions:
char * getFullName(char);
int getBandValue(char);
double getBandMultiplier(char);
double getBandTolerance(char);
double getResistance(double, double, double);
char * getUnit(double);
double trimResistance(double);
bool checkErrorName(char*, char*, char*, char*);
bool checkErrorValue(int,int,double,double);


int main(int argc, char **argv)
{
	// Declare Variables:
	char band1, band2, band3, band4, *unit;
	char *band1Full, *band2Full, *band3Full, *band4Full;
	int band1Value, band2Value; double band3Value, band4Value;
	double resistance, tolerance;
	bool valueError, nameError;
	
	// Prompt User Input:
	printf("Please enter the 1st band\n");
	scanf(" %c", &band1); // First Band
	
	printf("Please enter the 2nd band\n");
	scanf(" %c", &band2); // Second Band
	
	printf("Please enter the multiplier band\n");
	scanf(" %c", &band3); // Third (Multiplier) Band
	
	printf("Please enter the tolerance band\n");
	scanf(" %c", &band4); // Fourth (Tolerance) Band
	
	// Get Band Colour Names and Values:
	band1Full = getFullName(band1); band1Value = getBandValue(band1);
	band2Full = getFullName(band2); band2Value = getBandValue(band2);
	band3Full = getFullName(band3); band3Value = getBandMultiplier(band3);
	band4Full = getFullName(band4); band4Value = getBandTolerance(band4);
	
	// Check for Error:
	nameError = checkErrorName(band1Full, band2Full, band3Full, band4Full);
	valueError = checkErrorValue(band1Value, band2Value, band3Value, band4Value);
	
	if (nameError || valueError) { // Terminate if error
		printf("Error In Input");
		return 0;
	}
	
	resistance = getResistance(band1Value, band2Value, band3Value); // Get Resistance Value
	unit = getUnit(resistance); // Get Resistance Unit
	resistance = trimResistance(resistance); // Divide Resistance by Unit
	tolerance = band4Value; // Resistance Tolerance
	
	printf("Resistance bands: %s %s %s %s\n", band1Full, band2Full, band3Full, band4Full); // Print Out Band Names
	printf("Resistance: %0.2lf %s +/- %0.2lf%%", resistance, unit, tolerance); // Print Out Resistance Values
	
	return 0; // End of Program
}

char * getFullName(char band) {
	// Get full colour name of band based on user character input:
	if (band == 'k' || band == 'K') return "Black";
	else if (band == 'b' || band == 'B') return "Brown";
	else if (band == 'r' || band == 'R') return "Red";
	else if (band == 'o' || band == 'O') return "Orange";
	else if (band == 'e' || band == 'E') return "Yellow";
	else if (band == 'g' || band == 'G') return "Green";
	else if (band == 'u' || band == 'U') return "Blue";
	else if (band == 'v' || band == 'V') return "Violet";
	else if (band == 'y' || band == 'Y') return "Grey";
	else if (band == 'w' || band == 'W') return "White";
	else if (band == 'l' || band == 'L') return "Gold";
	else if (band == 's' || band == 'S') return "Silver";
	else return "error"; // Invalid input
}

int getBandValue(char band) {
	// Get band value (bands 1 and 2) based on user character input:
	if (band == 'k' || band == 'K') return 0;
	else if (band == 'b' || band == 'B') return 1;
	else if (band == 'r' || band == 'R') return 2;
	else if (band == 'o' || band == 'O') return 3;
	else if (band == 'e' || band == 'E') return 4;
	else if (band == 'g' || band == 'G') return 5;
	else if (band == 'u' || band == 'U') return 6;
	else if (band == 'v' || band == 'V') return 7;
	else if (band == 'y' || band == 'Y') return 8;
	else if (band == 'w' || band == 'W') return 9;
	else { // Invalid input
		printf("Invalid Band Number Input\n");
		return -1; // Return negative number to check for error
	}
}

double getBandMultiplier(char band) {
	// Get band multiplier value (band 3) based on user character input:
	if (band == 'k' || band == 'K') return 1;
	else if (band == 'b' || band == 'B') return 10;
	else if (band == 'r' || band == 'R') return 100;
	else if (band == 'o' || band == 'O') return 1000;
	else if (band == 'e' || band == 'E') return 10000;
	else if (band == 'g' || band == 'G') return 100000;
	else if (band == 'u' || band == 'U') return 1000000;
	else if (band == 'v' || band == 'V') return 10000000;
	else if (band == 'l' || band == 'L') return 0.1;
	else if (band == 's' || band == 'S') return 0.01;
	else { // Invalid input
		printf("Invalid Band Multiplier Input\n");
		return -1; // Return negative number to check for error
	}
}

double getBandTolerance(char band) {
	// Get band tolerance value (band 4) based on user character input:
	if (band == 'b' || band == 'B') return 1;
	else if (band == 'r' || band == 'R') return 2;
	else if (band == 'g' || band == 'G') return 0.5;
	else if (band == 'u' || band == 'U') return 0.25;
	else if (band == 'v' || band == 'V') return 0.1;
	else if (band == 'y' || band == 'Y') return 0.05;
	else if (band == 'l' || band == 'L') return 5;
	else if (band == 's' || band == 'S') return 10;
	else { // Invalid input
		printf("Invalid Band Tolerance Input\n");
		return -1; // Return negative number to check for error
	}
}

double getResistance(double band1, double band2, double band3) {
	double resistance;
	resistance = 10*band1 + band2; // Make two digit number from bands 1 and 2
	resistance *= band3; // Multiply by multiplier band value
	return resistance; // Return resistance value
}

char * getUnit(double resistance) {
	if (resistance < 1000) return "Ohms"; // Ohms if less than 1000
	else if (resistance < 1000000) return "KOhms"; // KOhms if greater than 1000 but less than 1 million
	else return "MOhms"; // MOhms if greater than 1 million
}

double trimResistance(double resistance) {
	if (resistance >= 1000000) resistance /= 1000000; // Divide by 1 million for MOhms
	else if (resistance >= 1000) resistance /= 1000; // Divide by 1000 for KOhms
	return resistance; // Return resistance value after adjustment for unit
}

bool checkErrorValue(int band1, int band2, double band3, double band4) {
	if (band1 < 0 || band2 < 0 || band3 < 0 || band4 < 0) return true; // Error present if any band has negative value
	return false; // OK otherwise
}

bool checkErrorName(char *band1, char *band2, char *band3, char *band4) {
	if (band1 == "error" || band2 == "error" || band3 == "error" || band4 == "error") return true; // Error present if any band has "error"
	return false; // OK otherwise
}
