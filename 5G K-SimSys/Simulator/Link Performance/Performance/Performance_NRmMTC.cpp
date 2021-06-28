/****************************************************************************

Performance (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : Performance_NRmMTC.cpp
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

#include "Performance_NRmMTC.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Performance::Initialize(string fileName)
{
	// Read link performance parameters from the file
	ifstream inFile("../../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamPerformance_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "realisticChannelEstimation") realisticChannelEstimation = stoi(result[1]);
			else if (result[0] == "checkPerformanceParameter") checkPerformanceParameter = stoi(result[1]);
			else if (result[0] == "targetConnectionDensity") targetConnectionDensity = stoi(result[1]);
		}
	}

	throughput = 0;
	connectionDensity = 0;
}

void Performance::Conclude()
{
	
}

void Performance::Measure()
{

	for (int i = 0; i < Sim.network->numMS; i++)
		MS[i]->performance->instantThroughput = 0;


	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->performance->Measure();
		connectionDensity = connectionDensity + BS[bsID]->performance->connectionDensity / Sim.network->numBS;
	}
	

	double averagedPfWindowSize = 50.0;
	setcolor(15, 0);
	cout << "************ TTI: " << Sim.TTI << " ************" << endl;
	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->scheduling->downlinkaveragedThroghput = MS[msID]->scheduling->downlinkaveragedThroghput*(Sim.TTI) / (Sim.TTI + 1) + MS[msID]->performance->downlinkThroghput / (Sim.TTI + 1);
	}

	cout << "******** Average Throughput Calculated ********" << endl;
	//for (int msID = 0; msID < Sim.network->numMS; msID++)
	//{
	//	Sim.RateTTI(msID, Sim.TTI) = MS[msID]->performance->instantThroughput;
	//}


}

void Performance::ConcludeIteration()
{

}
