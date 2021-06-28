/****************************************************************************

Performance (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Performance_NReMBB.cpp
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

#include "Performance_NRLAA.h"



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
		}
	}

	throughput = 0;
	
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
			BS[bsID]->performance->Measure(bsID, BS[bsID]->scheduling->framestructure(Sim.TTI % Sim.numTTIperFrame));
	}


	double averagedPfWindowSize = 50.0;
	setcolor(15, 0);
	cout << "************ TTI: " << Sim.TTI << " ************" << endl;
	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->scheduling->downlinkaveragedThroghput = MS[msID]->scheduling->downlinkaveragedThroghput*(Sim.TTI) / (Sim.TTI + 1) + MS[msID]->performance->downlinkThroghput / (Sim.TTI + 1);
		//cout << "[Performance]: Downlink Throughput msID " << msID << " - " << MS[msID]->scheduling->downlinkaveragedThroghput << endl;
		//MS[msID]->scheduling->uplinkaveragedThroghput = MS[msID]->scheduling->uplinkaveragedThroghput*(Sim.TTI) / (Sim.TTI + 1) + MS[msID]->performance->uplinkThroghput / (Sim.TTI + 1);
		//cout << "[Performance]: Uplink Throughput msID " << msID << " - " << MS[msID]->scheduling->uplinkaveragedThroghput << endl;			
	}
	cout << "******** Average Throughput Calculated ********" << endl;
	//for (int msID = 0; msID < Sim.network->numMS; msID++)
	//{
	//	Sim.RateTTI(msID, Sim.TTI) = MS[msID]->performance->instantThroughput;
	//}


}

void Performance::EndAction()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		// RS 마지막에서 확인
		if (BS[bsID]->scheduling->jamming_end_time[0] == Sim.usGlobalTime&& Sim.usGlobalTime != 0)
		{
			BS[bsID]->scheduling->error = 0;
			BS[bsID]->scheduling->error_tot++;
			double sum = 0;

				for (int ot = 0; ot < Sim.network->numBS; ot++) {
					if (bsID != ot) {
						if (BS[ot]->scheduling->Transmission_on[0] == 1) {
							sum = sum + MS[bsID]->scheduling->RSRP_fBS[ot][0];
						}
					}
				}

				for (int ot = 0; ot < Sim.network->numBS; ot++) {
						if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1) {
							sum = sum + MS[bsID]->scheduling->RSRP_fBS[ot][1];
						}
				}

				for (int ot = 0; ot < Sim.network->numMS; ot++) {
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1) {
						sum = sum + MS[bsID]->scheduling->RSRP_fBS[ot][2];
					}
				}

				if (10 * log10(sum) + 30 >= BS[bsID]->scheduling->LBT_thereshold) {
					BS[bsID]->scheduling->error = 1;
				}

			BS[bsID]->scheduling->error_sum= BS[bsID]->scheduling->error_sum+ BS[bsID]->scheduling->error;
		}

		// 마지막 7번째 frame 끝에서 exp_bo 재설정
		int LastTTI = BS[bsID]->scheduling->LTEU_Transmit_block-2;
		if (BS[bsID]->scheduling->Transmit_end_time[0][LastTTI] == Sim.usGlobalTime && Sim.TTI != 0) {
			if (BS[bsID]->scheduling->error == 0) {
				BS[bsID]->scheduling->exp_bo_num = 1;
			}
			else {
				BS[bsID]->scheduling->exp_bo_num = BS[bsID]->scheduling->exp_bo_num * 2;
				if (BS[bsID]->scheduling->exp_bo_num >= BS[bsID]->scheduling->exp_bo_num_max) {
					BS[bsID]->scheduling->exp_bo_num = BS[bsID]->scheduling->exp_bo_num_max;
				}
			}
		}


		int CurrentTTI = BS[bsID]->scheduling->Transmit_current_fr;
		if (BS[bsID]->scheduling->Transmit_end_time[0][CurrentTTI] == Sim.usGlobalTime&& Sim.TTI != 0) {
			//Sim.performance->Measure();
			BS[bsID]->performance->BsEndAction(bsID);			// BS End Action (Parameters Initialization for Next Channel Occupancy) // DL
		}
	}
}

void Performance::ResultOut()
{
	// UPT

	// Delay (Latency)

}

void Performance::ConcludeIteration()
{

}
