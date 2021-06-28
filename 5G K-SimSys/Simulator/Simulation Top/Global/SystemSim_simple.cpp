/****************************************************************************

System Level Simulation (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSim_simple.cpp
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
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include "SystemSim_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                   SLS Simulator class Initialize                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

void SystemSim::Initialize(string fileName)
{
	// Open the file
	ifstream inFile("../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamTop_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if(result[0] == "numTTI") numTTI = stoi(result[1]);
			else if (result[0] == "numIteration") numIteration = stoi(result[1]);
			else if (result[0] == "scenario") scenario = SLS::Scenario(stoi(result[1]));
			else if (result[0] == "linkDirection") linkDirection = SLS::LinkDirection(stoi(result[1]));
			
		}
	}

	network = new Network();
	scheduling = new Scheduling();
	performance = new Performance();
	channel = new Channel();

	network->Initialize(fileName); // Parameter initialization for network configuration
	scheduling->Initialize(fileName); // Parameter initialization for radio resource management
	performance->Initialize(fileName); // Parameter initialization for link performance
	channel->Initialize(fileName); // Parameter initialization for channel

}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*               SLS Simulator class Conclude Iteration                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SystemSim::ConcludeIteration()
{
	channel->ConcludeIteration();
	performance->ConcludeIteration();
	scheduling->ConcludeIteration();
	network->ConcludeIteration();
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                   SLS Simulator class Conclude                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SystemSim::Conclude()
{
	channel->Conclude();
	performance->Conclude();
	scheduling->Conclude();
	network->Conclude();
}

SystemSim Sim;