/****************************************************************************

Scheduling (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NReMBB.cpp
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

#include "Scheduling_NReMBB.h"


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
			else if (result[0] == "realisticFeedback") realisticFeedback = stoi(result[1]);
			else if (result[0] == "realisticChannelEstimation") realisticChannelEstimation = stoi(result[1]);
		}
	}
	numMaxLayer = 8;
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

void Scheduling::BufferUpdate()
{
	for (int i = 0; i < Sim.network->numMS; i++)
	{
		MS[i]->scheduling->BufferUpdate();
	}
}

void Scheduling::Feedback()
{
	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->scheduling->MuMimoFeedback(msID, 0); //MU-MIMO Feedback(msID)
	}
	//for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	//{
	//	BS[bsID]->scheduling->MuMimoFeedback(bsID);
	//}
	setcolor(13, 0);
	cout << "[Scheduling]: Mobile Station CSI feedback" << endl;
}

void Scheduling::Schedule()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->MuMimoSchedule(bsID, 0, BS[bsID]->scheduling->scheduledMS, BS[bsID]->scheduling->framestructure(Sim.TTI % Sim.numTTIperFrame));
	}
	setcolor(13, 0);
	cout << "[Scheduling]: Base Station scheduling " << endl;
}

void Scheduling::ReceivedSINRCalculation()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
			
			/*if (BS[bsID]->scheduling->framestructure(time) == 0)
			{
				for (int i = 0; i < arma::size(BS[bsID]->scheduling->scheduledMS)(0); i++)
				{
					for (int msID = 0; msID < BS[bsID]->scheduling->scheduledMS(i); msID++)
						MS[msID]->scheduling->ReceivedSINR(msID, BS[bsID]->scheduling->framestructure(time), time, 0);
				}				
			}
			else
			{
				for (int i = 0; i < arma::size(BS[bsID]->scheduling->scheduledMS)(0); i++)
				{
					for (int msID = 0; msID < BS[bsID]->scheduling->scheduledMS(i); msID++)
						BS[msID]->scheduling->ReceivedSINR(msID, BS[bsID]->scheduling->framestructure(time), time);
				}
			}*/
		for (int i = 0; i < BS[bsID]->scheduling->numScheduledMS; i++)
		{
			for (int msID = 0; msID < BS[bsID]->scheduling->scheduledMS(i); msID++)
				MS[msID]->scheduling->ReceivedSINR(msID, Sim.TTI % Sim.numTTIperFrame, 0);
		}
	}
	
	cout << "[Scheduling]: Received SINR calculation " << endl;
}

void Scheduling::Conclude()
{

}



void Scheduling::ConcludeIteration()
{

}
