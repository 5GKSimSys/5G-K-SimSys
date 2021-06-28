/****************************************************************************

Network Configuration (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Network_simple.cpp
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

#include "Network_simple.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Network::Initialize(string fileName)
{
	// Read network configuration parameters from the file
	ifstream inFile("../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamNetwork_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "numLayer") numLayer = stoi(result[1]);
			else if (result[0] == "macro.numSite") macro.numSite = stoi(result[1]);
			else if (result[0] == "macro.numSector") macro.numSector = stoi(result[1]);
			else if (result[0] == "macro.interSiteDistance") macro.interSiteDistance = stoi(result[1]);
			else if (result[0] == "macro.height") macro.height = stoi(result[1]);
			else if (result[0] == "numMsPerMacro") numMsPerMacro = stoi(result[1]);
			else if (result[0] == "minDistanceToBS") minDistanceToBS = stoi(result[1]);
		}
	}
	if (macro.numSite && macro.numSector) macro.numBS = macro.numSite * macro.numSector;
	numWraparound = NETWORK_NUM_WRAPAROUND;
	//posWraparound[0] = (2, 2);
	double A = sqrt(3) / 2;
	posWraparound << 0 << 5.0* A * 1i << 2*A*4*1i << -3*A+3.5*1i << -5*A-0.5*1i << -2*A-4.0*1i << 3*A-3.5*1i;
	posWraparound = Sim.network->macro.interSiteDistance * posWraparound;
	numMS = macro.numBS * numMsPerMacro;
}



void Network::PlaceMacroBS()
{
	for (int bs = 0, i = 0; i < macro.numSite; i++) // # of Macro Sites
	{
		for (int j = 0; j < macro.numSector; j++, bs++) // # of Sectors
		{
			BS[bs] = new SystemBS(bs, i, j, SLS::MacroBS);
		}
	}
}



void Network::PlaceMicroBS()
{
	for (int micro = macro.numSite, bs = macro.numBS, i = 0; i < macro.numBS; i++) // # of Macro Sites
	{
		for (int j = 0; j < numMicroPerMacro; j++, micro++) // # of Micro Sites
		{
			for (int k = 0; k < macro.numSector; k++, bs++) // # of Sectors of Micro BS
			{
				BS[bs] = new SystemBS(bs, micro, k, SLS::MicroBS); // Create new BS and perform initialization
			}
		}
	}
}



void Network::PlaceFullBufferMS()
{
	for (int ms = 0, i = 0; i < macro.numBS; i++) // # of Macro BS
	{
		for (int j = 0; j < numMsPerMacro; j++, ms++) // # of MSs of Macro BS
		{
			MS[ms] = new SystemMS(ms, i); // Create a new MS and perform initialization
			MS[ms]->network->Associate(); // Perform association
		}
	}
}



void Network::PlaceNonFullBufferMS()
{
	int ms;

	for (int i = 0; i < macro.numBS; i++) // # of Macro BS
	{
		if (rand() > txProbability)
		{
			ms = BS[i]->network->numAttachedMS++;
			MS[ms] = new SystemMS(ms, i); // Create a new MS and perform initialization
			
			MS[ms]->network->Associate(); // Perform association
		}
	}
}



void Network::MoveMS()
{
	for (int i = 0; i < numMS; i++)
	{
		// Position update
		// Recalculate long term channel
		// Handover if necessary
	}
}



void Network::ConcludeIteration()
{
	for (int i = 0; i < numMS; i++) // Delete MS
	{
		delete MS[i];
	}
	for (int i = macro.numBS; i < numBS; i++) // Delete Micro BS
	{
		delete BS[i];
	}
}



void Network::Conclude()
{
}
