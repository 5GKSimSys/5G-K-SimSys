/****************************************************************************

Scheduling (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_simple.cpp
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

#include "Scheduling_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::Initialize(string fileName)
{
	// Read radio resource management parameters from the file
	ifstream inFile("../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamScheduling_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "trafficModel") trafficModel = Scheduling_TrafficModel(stoi(result[1]));
			else if (result[0] == "trafficLoad") trafficLoad = stoi(result[1]);
			else if (result[0] == "dataSize") dataSize = stoi(result[1]);
			else if (result[0] == "algorithm") algorithm = Scheduling_Algorithm(stoi(result[1]));
			else if (result[0] == "numRB") numRB = stoi(result[1]);
			else if (result[0] == "realisticFeedback") realisticFeedback = stoi(result[1]);
		}
	}
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::Feedback()
{
	for (int i = 0; i < Sim.network->numMS; i++)
	{
		//cout << i;
		MS[i]->scheduling->Feedback();
	}
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::Schedule()
{
	for (int i = 0; i < Sim.network->numBS; i++)
	{
		BS[i]->scheduling->Schedule();
	}
}


void Scheduling::ConcludeIteration()
{

}


void Scheduling::Conclude()
{

}