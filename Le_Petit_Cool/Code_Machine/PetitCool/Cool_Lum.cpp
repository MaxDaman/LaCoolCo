/*	LACOOL_CO's GENERAL LIBRARY
	TYPE : SENSOR	-	MODEL : Grove Luminosity Sensor
	ROLE : 	Le Petit Cool Luminosity Sensor
			Le Cool Stick Luminosity Sensor
	@author Maximilien Daman	15/11/2015
	Mail : max@lacool.co	Web : www.lacool.co
 */

//Inclusion des librairies
	#include "Arduino.h"
	#include "PetitCool.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////CONSTRUCTEURS///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////	
Cool_Lum::Cool_Lum()
{}

void Cool_Lum::begin(uint8_t ConnectPin)
{
	LumPin = ConnectPin + 54;
	setError(0);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ERRORLEVEL///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uint8_t Cool_Lum::errorlevel()
{	//MOYENNE MOBILE A STABILISER//
//Initialisation:
	int NbTry = 2;
	int Temp[NbTry];
	int M[2*NbTry];
	int Test = 0;
//Test de fonctionnement:
	for(int i=0; i<NbTry; i++)
	{
		M[2*i] = analogRead(LumPin);
		delay(1);
		M[2*i+1] = analogRead(LumPin);
		delay(1);
		Temp[i] = (M[2*i]>M[2*i+1])?(M[2*i]-M[2*i+1]):(M[2*i+1]-M[2*i]);
		Temp[i] = (Temp[i]>1)?0:1;
	}
	for(int i=0; i<NbTry-1; i++)
	{
		Test += (Temp[2*i]==Temp[2*i+1]);
	}
//Niveau d erreur:
	ErrorLevel = (!Test)?1:0;
	return ErrorLevel;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////