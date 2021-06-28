/****************************************************************************

System Level Simulation (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSim_NRmMTC.cpp
DATE         : 2017.12.1
VERSION      : 0.5
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.5.20	Minsig Han    	Created
2017.7.10	Minsig Han    	Add variables for non-full buffer scenario
2017.11.14	Jaewon Lee    	Add variables for 
2017.12.1	Jaewon Lee    	Add variables for
===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include "SystemSim_NRmMTC.h"


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                   SLS Simulator class Initialize                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/
int main()
{
	Sim.Initialize("NRmMTC_UrbanMacroCell"); // Simulation initialization
	Sim.network->PlaceMacroBS(); // Macro BS placement
	cout << "*******************Simulation Start*******************" << endl;
	
	while(Sim.performance->connectionDensity < Sim.performance->targetConnectionDensity)
	{
		Sim.network->PlaceMS(); // mMTC MS placement
		Sim.network->PlaceWraparound();
		Sim.channel->LongTermChannel();
		Sim.scheduling->PreambleSelection(); // MS Preamble selection
		Sim.scheduling->Feedback(); // SINR calculation
		Sim.scheduling->Schedule(); // Scheduling
		Sim.performance->Measure(); // POR, connection density, and performance calculation
		Sim.network->numMsPerSector++;
		Sim.network->numMS = Sim.network->numMacroBS * Sim.network->numSector * Sim.network->numMsPerSector;
	}
		
	Sim.ConcludeIteration(); // Iteration conclusion
	Sim.Conclude(); // Simulation conclusion
	return 0;
}


void SystemSim::Initialize(string fileName)
{
	// Random seed
	arma::arma_rng::set_seed_random();

	// Open the file
	ifstream inFile("../../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamTop_" + fileName + ".txt",ios::out);
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) 
		{

			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "numTTI") numTTI = stoi(result[1]);
			else if (result[0] == "numerologyParameter") numerologyParameter = stoi(result[1]);
			else if (result[0] == "numSymbolperTTI") numSymbolperTTI = stoi(result[1]);
			else if (result[0] == "numIteration") numIteration = stoi(result[1]);
			else if (result[0] == "feedbackPeriod") feedbackPeriod = stoi(result[1]);
			else if (result[0] == "scenario") scenario = SLS::Scenario(stoi(result[1]));
			else if (result[0] == "linkDirection") linkDirection = SLS::LinkDirection(stoi(result[1]));
			
		}
	}
	numTTIperFrame = pow(2.0, numerologyParameter) * 10;
	subcarrierSpacing = pow(2.0, numerologyParameter) * 15;

	network = new Network();
	scheduling = new Scheduling();
	performance = new Performance();
	channel = new Channel();


	network->Initialize(fileName); // Parameter initialization for network configuration
	channel->Initialize(fileName); // Parameter initialization for channel
	scheduling->Initialize(fileName); // Parameter initialization for radio resource management
	performance->Initialize(fileName); // Parameter initialization for link performance	

	Sim.RateTTI.zeros(Sim.network->numMS,Sim.numTTI);
	Sim.LatencyTTI.zeros(Sim.network->numMS, Sim.numTTI);
	Sim.BufferTTI.zeros(Sim.network->numMS, Sim.numTTI);

}


void SystemSim::Demonstration() {
	
	/*ofstream Pbs, Pms;

	Pbs.open("../../Simulator/Data/Output Data/Demonstration/Pbs.txt");
	Pms.open("../../Simulator/Data/Output Data/Demonstration/Pms.txt");

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		Pbs << BS[bsID]->network->pos3D(0, 0) << "	" << BS[bsID]->network->pos3D(0, 1) << "	" << BS[bsID]->network->pos3D(0, 2) << endl;
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		Pms << MS[msID]->network->pos3D(0, 0) << "	" << MS[msID]->network->pos3D(0, 1) << "	" << MS[msID]->network->pos3D(0, 2) << endl;
	}

	Pbs.close();
	Pms.close();*/
		
	//ofstream MS_Position, clusterAngleAndPower, MS_AOA, MS_AOD, MS_SINR, Buffer, Mainchart_Rate, Mainchart_Latency;
	//arma::vec rate;
	//rate.zeros(Sim.network->numMS);
	//
	//MS_Position.open("../../Simulator/Data/Output Data/Demonstration/MS_Position.txt");
	//Mainchart_Rate.open("../../Simulator/Data/Output Data/Demonstration/Mainchart_Rate.txt");
	//Mainchart_Latency.open("../../Simulator/Data/Output Data/Demonstration/Mainchart_Latency.txt");
	//
	//clusterAngleAndPower.open("../../Simulator/Data/Output Data/Demonstration/MS_ClusterInformation.txt");
	//MS_AOD.open("../../Simulator/Data/Output Data/Demonstration/MS_AOD.txt");
	//MS_AOA.open("../../Simulator/Data/Output Data/Demonstration/MS_AOA.txt");
	//Buffer.open("../../Simulator/Data/Output Data/Demonstration/Buffer.txt");
	//
	//	for (int msID = 0; msID < Sim.network->numMS; msID++) {
	//		// Ms 별 결과
	//		MS_Position << MS[msID]->network->pos3D(0, 0) << "	" << MS[msID]->network->pos3D(0, 1) << endl;
	//		
	//
	//		Buffer << MS[msID]->network->msBuffer << endl;
	//		for (int n = 0; n < MAX_CLUSTER; n++) { // MAX_Cluseter = 20
	//			// Cluster 별 결과
	//			int servingCell = MS[msID]->channel->associatedBsIndex;
//	//			clusterAngleAndPower << MS[msID]->channel->DemoAOD(servingCell, 0)(n, 0) << "	" << MS[msID]->channel->DemoAOA(servingCell, 0)(n, 0) << "	" << MS[msID]->channel->DemoClusterPower(servingCell, 0)(n, 0) << endl;
	//		}
	//	}
	//
	//	for (int tti = 0; tti < Sim.numTTI; tti++) {
	//		// TTI 별 결과
	//		Mainchart_Rate << Sim.RateTTI.submat(0,tti,Sim.network->numMS-1,tti).max() / 1000000 << "	" << Sim.RateTTI.submat(0, tti, Sim.network->numMS - 1, tti).min() / 1000000 << "	" << arma::mean(Sim.RateTTI.submat(0, tti, Sim.network->numMS - 1, tti)) / 1000000 << endl;
	//		Mainchart_Latency << MS[0]->network->interArrivalTime(tti) << endl;
	//	}
	//	
	//
	//Mainchart_Rate.close();
	//MS_Position.close();
	//clusterAngleAndPower.close();
	//Buffer.close();
	//Mainchart_Latency.close();
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
	Sim.network->Conclude();
	Sim.channel->Conclude();
	Sim.performance->Conclude();
	Sim.scheduling->Conclude();

}


SystemSim Sim;