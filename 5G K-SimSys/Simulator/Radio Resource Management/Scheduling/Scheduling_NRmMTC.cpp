/****************************************************************************

Scheduling (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NRmMTC.cpp
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
2017.1.31	WISELAB      	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "Scheduling_NRmMTC.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::Initialize(string fileName)
{
	// Read radio resource management parameters from the file
	ifstream inFile("../../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamScheduling_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "algorithm") algorithm = RRM::Scheduling_Algorithm(stoi(result[1]));
			else if (result[0] == "dataSize") dataSize = stoi(result[1]);
			else if (result[0] == "numRB") numRB = stoi(result[1]);
			else if (result[0] == "numCB") numCB = stoi(result[1]);
			else if (result[0] == "numCBG") numCBG = stoi(result[1]);
			else if (result[0] == "numPreamble") numPreamble = stoi(result[1]);
			else if (result[0] == "realisticFeedback") realisticFeedback = stoi(result[1]);
			else if (result[0] == "realisticChannelEstimation") realisticChannelEstimation = stoi(result[1]);
		}
	}
	numMaxLayer = 1;
}

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Scheduling::FrameStructure(SLS::TDDType tddtype)
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->FrameStructure(bsID, tddtype);
	}
	cout << "[Scheduling]: Frame Sturcture for next frame" << endl;
}

void Scheduling::PreambleSelection()
{
	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->scheduling->PreambleSelection(); // 
	}
}

void Scheduling::Feedback()
{
	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->scheduling->Feedback(); // Feedback(msID)
	}

	setcolor(13, 0);
	cout << "[Scheduling]: Mobile Station CSI feedback" << endl;
}

void Scheduling::Schedule()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->Schedule(bsID);
	}
	setcolor(13, 0);
	cout << "[Scheduling]: Base Station scheduling " << endl;
}

void Scheduling::ReceivedSINRCalculation()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		MS[BS[bsID]->scheduling->scheduledMS]->scheduling->ReceivedSINR();
			
	}
	
	cout << "[Scheduling]: Received SINR calculation " << endl;
}

void Scheduling::Conclude()
{

}



void Scheduling::ConcludeIteration()
{

}
