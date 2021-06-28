/****************************************************************************

Channel Model (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Antenna_simple.cpp
DATE         : 2016.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.11	Minjoong Rim 	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "Channel_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Channel::Initialize(string fileName)
{
	// Read channel model parameters from the file
	ifstream inFile("../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamChannel_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "macroBS.carrierFrequency") macroBS.carrierFrequency = stoi(result[1]);
			else if (result[0] == "macroBS.bandwidth") macroBS.bandwidth = stoi(result[1]);
			else if (result[0] == "macroBS.txPower") macroBS.txPower = stoi(result[1]);
			else if (result[0] == "macroBS.noiseFigure") macroBS.noiseFigure = stoi(result[1]);
			else if (result[0] == "macroBS.antennaGain") macroBS.antennaGain = stoi(result[1]);
			else if (result[0] == "macroBS.antenna.num") macroBS.antenna.num = stoi(result[1]);
			else if (result[0] == "macroBS.model") macroBS.model = Channel_Model(stoi(result[1]));
			else if (result[0] == "microBS.carrierFrequency") microBS.carrierFrequency = stoi(result[1]);
			else if (result[0] == "microBS.bandwidth") microBS.bandwidth = stoi(result[1]);
			else if (result[0] == "microBS.txPower") microBS.txPower = stoi(result[1]);
			else if (result[0] == "microBS.noiseFigure") microBS.noiseFigure = stoi(result[1]);
			else if (result[0] == "microBS.antennaGain") microBS.antennaGain = stoi(result[1]);
			else if (result[0] == "microBS.antenna.num") microBS.antenna.num = stoi(result[1]);
			else if (result[0] == "microBS.model") microBS.model = Channel_Model(stoi(result[1]));
			else if (result[0] == "macroMS.txPower") macroMS.txPower = stoi(result[1]);
			else if (result[0] == "macroMS.noiseFigure") macroMS.noiseFigure = stoi(result[1]);
			else if (result[0] == "macroMS.antennaGain") macroMS.antennaGain = stoi(result[1]);
			else if (result[0] == "macroMS.antenna.num") macroMS.antenna.num = stoi(result[1]);
			else if (result[0] == "microMS.txPower") microMS.txPower = stoi(result[1]);
			else if (result[0] == "microMS.noiseFigure") microMS.noiseFigure = stoi(result[1]);
			else if (result[0] == "microMS.antennaGain") microMS.antennaGain = stoi(result[1]);
			else if (result[0] == "microMS.antenna.num") microMS.antenna.num = stoi(result[1]);
		}
	}
};



void Channel::ConcludeIteration() {

};



void Channel::Conclude() {

};