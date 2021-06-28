/****************************************************************************

Performance (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Performance_simple.cpp
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

#include "Performance_simple.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Performance::Initialize(string fileName)
{
	// Read link performance parameters from the file
	ifstream inFile("../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamPerformance_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "realisticChannelEstimation") realisticChannelEstimation = stoi(result[1]);
		}
	}

	throughput = 0;
}



void Performance::Measure()
{
	for (int i = 0; i < Sim.network->numBS; i++)
	{
		BS[i]->performance->Measure();
		throughput += BS[i]->performance->throughput;
	}
	/*for (int j = 0; j < Sim.network->numMS; j++)
	{
		MS[j]->performance->Measure();
		//cout << j << ": " << MS[j]->performance->throughput << endl;
	}*/
}



void Performance::Conclude()
{
	throughput /= (Sim.numIteration * Sim.numTTI);
	cout << "CONCLUDE :: " << throughput << endl;
}



void Performance::ConcludeIteration()
{
	
}