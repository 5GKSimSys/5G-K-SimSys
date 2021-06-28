/****************************************************************************

System Level Simulation (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSim_NReMBB.cpp
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

#include "SystemSim_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                   SLS Simulator class Initialize                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

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
			if (result[0] == "NewDistance") NewDistnace = stoi(result[1]);
			else if (result[0] == "NewPClass") NewPClass = stoi(result[1]);
			else if (result[0] == "numTTI") numTTI = stoi(result[1]);
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
	
	ofstream Pbs, Pms, Trs, Err, MAC, Errw, MACw, rsrp0, rsrp1, rsrp2;

	Pbs.open("../../Simulator/Data/Output Data/Demonstration/Pbs.txt", ios::app);
	Pms.open("../../Simulator/Data/Output Data/Demonstration/Pms.txt", ios::app);
	Err.open("../../Simulator/Data/Output Data/Demonstration/Err.txt", ios::app);
	MAC.open("../../Simulator/Data/Output Data/Demonstration/MAC.txt", ios::app);
	Errw.open("../../Simulator/Data/Output Data/Demonstration/Errw.txt", ios::app);
	MACw.open("../../Simulator/Data/Output Data/Demonstration/MACw.txt", ios::app);

	rsrp0.open("../../Simulator/Data/Output Data/Demonstration/rsrp0.txt", ios::app);
	rsrp1.open("../../Simulator/Data/Output Data/Demonstration/rsrp1.txt", ios::app);
	rsrp2.open("../../Simulator/Data/Output Data/Demonstration/rsrp2.txt", ios::app);

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		Pbs << BS[bsID]->network->pos.real() << "	" << BS[bsID]->network->pos.imag() << endl;
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		Pms << WiFiMS[msID]->network->pos.real() << "	" << WiFiMS[msID]->network->pos.imag() << "	" << WiFiMS[msID]->network->attachedBS << endl;
	}

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
			Err << BS[bsID]->scheduling->error_sum << "	" << BS[bsID]->scheduling->error_tot << endl;
	}

	int sim_tot_time = Sim.TTIValue*Sim.numTTI;

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		MAC << BS[bsID]->scheduling ->MAC_time << "	" << sim_tot_time << endl;
	}

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		Errw << WiFiBS[bsID]->scheduling->error_sum << "	" << WiFiBS[bsID]->scheduling->error_tot << endl;
	}

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		MACw << WiFiBS[bsID]->scheduling->MAC_time << "	" << sim_tot_time << endl;
	}

	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 3; b++) {
			rsrp0 << MS[a]->scheduling->RSRP_fBS[0][b] << "	" << MS[a]->scheduling->RSRP_fBS[1][b] << "	" << MS[a]->scheduling->RSRP_fBS[2][b] << "	" << MS[a]->scheduling->RSRP_fBS[3][b] << endl;
		}
		rsrp0 << endl;
	}
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 3; b++) {
			rsrp1 << WiFiBS[a]->scheduling->RSRP_fBS[0][b] << "	" << WiFiBS[a]->scheduling->RSRP_fBS[1][b] << "	" << WiFiBS[a]->scheduling->RSRP_fBS[2][b] << "	" << WiFiBS[a]->scheduling->RSRP_fBS[3][b] << endl;
		}
		rsrp1 << endl;
	}
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 3; b++) {
			rsrp2 << WiFiMS[a]->scheduling->RSRP_fBS[0][b] << "	" << WiFiMS[a]->scheduling->RSRP_fBS[1][b] << "	" << WiFiMS[a]->scheduling->RSRP_fBS[2][b] << "	" << WiFiMS[a]->scheduling->RSRP_fBS[3][b] << endl;
		}
		rsrp2 << endl;
	}

	Pbs << "	" << endl;
	Pms << "	" << endl;
	Err << "	" << endl;
	MAC << "	" << endl;
	Errw << "	" << endl;
	MACw << "	" << endl;

	rsrp0 << "	" << endl;
	rsrp1 << "	" << endl;
	rsrp2 << "	" << endl;

	Pbs.close();
	Pms.close();
	Err.close();
	MAC.close();
	Errw.close();
	MACw.close();

	rsrp0.close();
	rsrp1.close();
	rsrp2.close();

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
	////			clusterAngleAndPower << MS[msID]->channel->DemoAOD(servingCell, 0)(n, 0) << "	" << MS[msID]->channel->DemoAOA(servingCell, 0)(n, 0) << "	" << MS[msID]->channel->DemoClusterPower(servingCell, 0)(n, 0) << endl;
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