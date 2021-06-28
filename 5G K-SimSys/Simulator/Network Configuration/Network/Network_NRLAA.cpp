/****************************************************************************

Network Configuration (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Network_FDMIMO.cpp
DATE         : 2017.1.31
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.31	Minsig Han     	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "Network_NRLAA.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Network::Initialize(string fileName)
{
	// Read network configuration parameters from the file
	ifstream inFile("../../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamNetwork_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "model") NetworkModel = NETWORK::Network_Model(stoi(result[1]));

			if (Sim.network->NetworkModel == NETWORK::IndoorOffice)
			{
				if (result[0] == "numLayer") numLayer = stoi(result[1]); // # of layers (1: Single layer, 2: Two layers)
				else if (result[0] == "numMacroBS") numMacroBS = stoi(result[1]); // # of Macro BSs 
				else if (result[0] == "numWifiBS") numWifiBS = stoi(result[1]); // # of Wifi BSs 
				else if (result[0] == "numSector") numSector = stoi(result[1]); // # of sectors per BS
				else if (result[0] == "numMsPerSector") numMsPerSector = stoi(result[1]); // # of MS per sector			
				else if (result[0] == "bufferModel") bufferModel = stoi(result[1]); // 
				else if (result[0] == "meanArrivalTime") meanArrivalTime = stoi(result[1]); // if bufferModel==1
				else if (result[0] == "bufferSize") bufferSize = stoi(result[1]); // 
				else if (result[0] == "IndoorOffice.interSiteDistance") IndoorOffice.interSiteDistance = stoi(result[1]);
				else if (result[0] == "IndoorOffice.height") IndoorOffice.height = stoi(result[1]);
				else if (result[0] == "IndoorOffice.minDistanceToBS") IndoorOffice.minDistanceToBS = stoi(result[1]);
				else if (result[0] == "IndoorOffice.indoorMsFraction") IndoorOffice.indoorMsFraction = stoi(result[1]); // MS's indoor probability (0 ~ 100)
				numMicroBS = 0;
			}
		}
	}

	numWraparound = NETWORK_NUM_WRAPAROUND;
	double A = sqrt(3) / 2;
	posWraparound << 0 << 5 * A + 0.5i << 3 * A + 4i << -3 * A + 3.5i << -5 * A - 0.5i << -3 * A - 4i << 3 * A - 3.5i;
	posWraparound = Sim.network->UrbanMacroCell.interSiteDistance * posWraparound;

	sectorDegree.alpha0 = (PI / 180) * 30;
	sectorDegree.alpha1 = (PI / 180) * 150;
	sectorDegree.alpha2 = (PI / 180) *(-90);
	beta = 0.0;
	gamma = 0.0;

}

void Network::PlaceBS()
{
	numBS = 0;
	int bsID = 0;
	for (int i = 0; i < numMacroBS; i++) // # of Indoor Sites
	{
		for (int j = 0; j < numSector; j++) // # of Indoor Sectors
		{
			BS[bsID] = new SystemBS(bsID, i, j, SLS::IndoorBS);
			bsID++;
		}
	}
	
	numBS = bsID;
	numSite = numBS / numSector;
	setcolor(10, 0);
	cout << "[Network  30%]: Base Stations placement" << endl;
}

void Network::PlaceWiFiBS()
{
	numBS = 0;
	int bsID = 0;
	for (int i = 0; i < numWifiBS; i++) // # of Indoor Sites
	{
		for (int j = 0; j < numSector; j++) // # of Indoor Sectors
		{
			BS[bsID] = new SystemBS(bsID, i, j, SLS::IndoorBS);
			bsID++;
		}
	}

	numBS = bsID;
	numSite = numBS / numSector;
	setcolor(10, 0);
	cout << "[Network  30%]: Base Stations placement" << endl;
}

void Network::PlaceFullBufferMS()
{
	for (int msID = 0, i = 0; i < numBS; i++) // # of Macro BS
	{
		BS[i]->network->numAttachedMS = 0;
		for (int j = 0; j < numMsPerSector; j++, msID++) // # of MSs of Macro BS
		{
			BS[i]->network->numAttachedMS++;
			MS[msID] = new SystemMS(msID, i); // Create a new MS and perform initialization
		}
	}
	cout << "[Network  70%]: Full Buffer Mobile Station placement" << endl;
}

void Network::PlaceNonFullBufferMS()
{
	for (int msID = 0, i = 0; i < numBS; i++) // # of Macro BS
	{
		BS[i]->network->numAttachedMS = 0;
		for (int j = 0; j < numMsPerSector; j++, msID++) // # of MSs of Macro BS
		{
			BS[i]->network->numAttachedMS++;
			MS[msID] = new SystemMS(msID, i); // Create a new MS and perform initialization
		}
	}
	cout << "[Network  70%]: Non-full Buffer Mobile Station placement" << endl;
}

void Network::PlaceWraparound()
{
	for (int ms = 0, i = 0; i < numBS; i++) // # of Macro BS
	{
		for (int j = 0; j < numMsPerSector; j++, ms++) // # of MSs of Macro BS
		{
			MS[ms]->network->WrapAround(); // Perform association
		}
	}
	cout << "[Network 100%]: Wraparound BS setting" << endl;
}

void Network::Conclude()
{
}

void Network::ConcludeIteration()
{
}