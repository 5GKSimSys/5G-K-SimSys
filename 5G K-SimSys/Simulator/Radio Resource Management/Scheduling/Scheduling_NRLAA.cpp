/****************************************************************************

Scheduling (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_FD MIMO.cpp
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

#include "Scheduling_NRLAA.h"

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

	DIFS = 10;
	SIFS = 1;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "algorithm") algorithm = RRM::Scheduling_Algorithm(stoi(result[1]));
			else if (result[0] == "numRB") numRB = stoi(result[1]);
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

void Scheduling::StartAction()
{
	Sim.scheduling->ISITcalculation();
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		int tmp_cuf = BS[bsID]->scheduling->Transmit_current_fr;
		if (BS[bsID]->scheduling->Transmit_start_time[0][tmp_cuf] == Sim.usGlobalTime && Sim.TTI != 0)
		{
			BS[bsID]->scheduling->ISITinitializationForFER(bsID);	// Inter-system Interference Time Initialization for FER
			Sim.scheduling->Schedule(); // Scheduz		
		}
	}
}

void Scheduling::FrameStructure(SLS::TDDType tddtype)
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->FrameStructure(bsID, tddtype);
	}
	cout << "[Scheduling]: Frame Sturcture for next frame" << endl;
}

void Scheduling::Feedback()
{
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->CqiReportCondition(bsID);	// CQI Report Condition Check
	}
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->PreSinrCalculation(bsID);	// SINR Calculation for CQI Report
	}
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

void Scheduling::ListenBeforeTalk()
{
	LbtCategory();	// LBT Operation based on LBT Category (Inter-BS)

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		BS[bsID]->scheduling->Transmission_Decision(bsID); // Transmission Decision for Current COT (intra-BS)
	}
}

void Scheduling::LbtCategory()
{
	if (LBT_CATEGORY == 0)
	{
		// LBT Procedures: Channel Selection & LBT Mode Decision (Intra-BS)
		for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
		{
			BS[bsID]->scheduling->WiderBwOperation(bsID);
		}

		// LBT Procedures: LBT Operation (Inter-BS)
		Sim.scheduling->DLLBT_simple();
	}
	else if (LBT_CATEGORY == 1)
	{
		for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
		{
			BS[bsID]->scheduling->WiderBwOperation(bsID);
		}

		// LBT Procedures: LBT Operation (Inter-BS)
		Sim.scheduling->DLLBT_new();
	}
}

void Scheduling::ISITcalculation() // Subband 작업 안해둠
{
	// ISIT Initialization for CQI (FER관련 ISIT 값 초기화는 다른 함수에서 수행)
	if (Sim.usGlobalTime % Sim.TTIValue == 0)
	{
		for (int msID = 0; msID < Sim.network->numMS; msID++)
		{
			if (MS[msID]->network->system_type == 1)
			{
				for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
				{
					MS[msID]->scheduling->InterferenceTimeFromBsForCQI[ibs] = 0;
				}
				for (int iue = 0; iue < Sim.network->numMS; iue++)
				{
					MS[msID]->scheduling->InterferenceTimeFromUeForCQI[iue] = 0;
				}
				// AP -> UE
				// STA -> UE 도 작업할 것
			}
		}
	}

	// ISIT Calculation for CQI & FER

		for (int msID = 0; msID < Sim.network->numMS; msID++)
		{
			if (MS[msID]->network->system_type == 1)
			{
				int sbs = MS[msID]->network->attachedBS;

				// BS -> UE
				for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
				{
					if (ibs != sbs)
					{
						if (BS[sbs]->scheduling->Transmission_on[0] == 1) // CQI Report Condition이 ON이라면,
						{
							MS[msID]->scheduling->InterferenceTimeFromBsForCQI[ibs]++;
						}
					}
				}
				// UE -> UE
				// AP -> UE
				// STA -> UE 구현할 것
			}
		}
}

void Scheduling::DLLBT_simple() // DL Category 4 LBT (Simple version) + Sub-band Operation // Sub-band Operation은 아직 구현 못했음... 어떻게 구현해야 할지 감이 안옴 (구현이슈라서) 
{
	// Initialize
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		for (int msID = 0; msID < Sim.network->numMS; msID++)
		{
			if (MS[msID]->network->system_type == 1 && MS[msID]->network->attachedBS == bsID)
			{
				int PacketNum = MS[msID]->network->CurrentPacketNumDL;
				if (MS[msID]->network->PacketQueueSizeDL[PacketNum] > 0)
				{
					for (int i = 0; i < Sim.scheduling->numSubband; i++)
					{
						if (BS[bsID]->scheduling->Transmission_on[i] == 0 && BS[bsID]->scheduling->ECCA_on[i] == 0 && BS[bsID]->scheduling->DIFS_on[i] == 0) // 보낼 트래픽 있음 + LBT 중 아님 = LBT 시작!
						{
							BS[bsID]->scheduling->DIFS_on[i] = 1;
							BS[bsID]->scheduling->ECCA_on[i] = 1;
							BS[bsID]->scheduling->ECCA_criteria[i] = 0.0;
							BS[bsID]->scheduling->ECCA_count_time[i] = LBT_DIFS_SIZE;

							BS[bsID]->scheduling->ECCA_count_CCA[i] = 16; // Back-off counter는 전송후 처리에서 결정됨 // 현재는 임시로 테스트를 위해서 값을 바로 대입
							break;
						}
					}
				}
			}
		}
		// DIFS & ECCA Energy Detection
		for (int i = 0; i < Sim.scheduling->numSubband; i++)
		{
			if (BS[bsID]->scheduling->DIFS_on[i] == 1) // DIFS 중
			{
				if (BS[bsID]->scheduling->ECCA_count_time[i] > 0)
				{
					// 간섭 누적하는 코드 필요 (채널 관련 파라미터를 현재 알지 못해서 비워둠)

					// BS -> BS

					BS[bsID]->scheduling->ECCA_count_time[i] = BS[bsID]->scheduling->ECCA_count_time[i] - 1;
				}
			}
			else if (BS[bsID]->scheduling->DIFS_on[i] == 0) // ECCA 중
			{
				if (BS[bsID]->scheduling->ECCA_count_time[i] > 0)
				{

					// 간섭 누적하는 코드 필요 (채널 관련 파라미터를 현재 알지 못해서 비워둠)

					// BS -> BS

					BS[bsID]->scheduling->ECCA_count_time[i] = BS[bsID]->scheduling->ECCA_count_time[i] - 1;
				}
			}
		}
	}
	// Busy & Idle Decision
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		for (int i = 0; i < Sim.scheduling->numSubband; i++)
		{
			if (BS[bsID]->scheduling->ECCA_on[i] == 1)
			{
				if (BS[bsID]->scheduling->ECCA_count_time[i] == 0)
				{
					if (BS[bsID]->scheduling->DIFS_on[i] == 1) // Decision in DIFS period
					{
						if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[i]) + 30.0 < LBT_THRESHOLD) // If Idle,
						{
							if (BS[bsID]->scheduling->ECCA_count_CCA[i] == 0) // If initial ECCA count is 0,
							{
								BS[bsID]->scheduling->DIFS_on[i] = 0;
								BS[bsID]->scheduling->ECCA_on[i] = 0;
								BS[bsID]->scheduling->ECCA_criteria[i] = 0.0;
								BS[bsID]->scheduling->ECCA_count_time[i] = 0;
								BS[bsID]->scheduling->Transmission_on[i] = 1; // Go Transmission (Initial signal)
							}
							else if (BS[bsID]->scheduling->ECCA_count_CCA[i] > 0) // If initial ECCA counter is not 0, 
							{
								BS[bsID]->scheduling->DIFS_on[i] = 0;
								BS[bsID]->scheduling->ECCA_on[i] = 1; // Go ECCA
								BS[bsID]->scheduling->ECCA_criteria[i] = 0.0;
								BS[bsID]->scheduling->ECCA_count_time[i] = LBT_SLOT_SIZE;
							}
						}
						else if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[i]) + 30.0 >= LBT_THRESHOLD) // If Busy,
						{
							BS[bsID]->scheduling->ECCA_criteria[i] = 0.0;
							BS[bsID]->scheduling->ECCA_count_time[i] = LBT_DIFS_SIZE; // Again DIFS
						}
					}
					else if (BS[bsID]->scheduling->DIFS_on[i] == 0) // Decision in ECCA period
					{
						if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[i]) + 30.0 < LBT_THRESHOLD) // If Idle,
						{
							BS[bsID]->scheduling->ECCA_count_CCA[i] = BS[bsID]->scheduling->ECCA_count_CCA[i] - 1; // ECCA counter - 1

							if (BS[bsID]->scheduling->ECCA_count_CCA[i] == 0) // If ECCA counter is 0,
							{
								BS[bsID]->scheduling->ECCA_on[i] = 0;
								BS[bsID]->scheduling->ECCA_criteria[i] = 0;
								BS[bsID]->scheduling->ECCA_count_time[i] = 0;
								BS[bsID]->scheduling->Transmission_on[i] = 1; // Go Transmission (Initial signal)
							}
							else if (BS[bsID]->scheduling->ECCA_count_CCA[i] > 0) // If ECCA counter is not 0,
							{
								BS[bsID]->scheduling->ECCA_on[i] = 1;
								BS[bsID]->scheduling->ECCA_criteria[i] = 0.0;
								BS[bsID]->scheduling->ECCA_count_time[i] = LBT_SLOT_SIZE; // Continue ECCA
							}
						}
						else if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[i]) + 30.0 >= LBT_THRESHOLD) // If Busy,
						{
							BS[bsID]->scheduling->DIFS_on[i] = 1; // Remaining ECCA counter + Go DIFS
							BS[bsID]->scheduling->ECCA_on[i] = 1;
							BS[bsID]->scheduling->ECCA_criteria[i] = 0.0;
							BS[bsID]->scheduling->ECCA_count_time[i] = LBT_DIFS_SIZE;
						}
					}
				}
			}
		}
	}
}

void Scheduling::DLLBT_new()
{
	// Initialize
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		for (int msID = 0; msID < Sim.network->numMS; msID++)
		{
			if (MS[msID]->network->attachedBS == bsID)
			{
				int PacketNum = MS[msID]->network->CurrentPacketNumDL;
				if (BS[bsID]->scheduling->ECCA_on[0] == 0 && BS[bsID]->scheduling->Transmission_on[0] == 0 && BS[bsID]->scheduling->LBT_step == 0)
				{
				BS[bsID]->scheduling->DIFS_on[0] = 1;
				BS[bsID]->scheduling->ECCA_on[0] = 1;
				BS[bsID]->scheduling->LBT_step = 5;
				BS[bsID]->scheduling->ECCA_criteria[0] = 0.0;
				BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->tf + BS[bsID]->scheduling->mp*BS[bsID]->scheduling->ECCA_slot_size;
				BS[bsID]->scheduling->res_mp = BS[bsID]->scheduling->mp;
				BS[bsID]->scheduling->CtDecre = 0;
				break;
				}
			}
		}
	}

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		if (BS[bsID]->scheduling->ECCA_on[0] == 1)
		{
			if (BS[bsID]->scheduling->LBT_step == 1)	// step 1
			{
				//generator?
				int tmp_count = ceil(rand() / (float)RAND_MAX * BS[bsID]->scheduling->exp_bo_num*BS[bsID]->scheduling->LBT_q);
				BS[bsID]->scheduling->ECCA_count_CCA[0] = tmp_count - 1;
				BS[bsID]->scheduling->ECCA_count_time[0] = BS[bsID]->scheduling->ECCA_slot_size;
				BS[bsID]->scheduling->ECCA_criteria[0] = 0;
				BS[bsID]->scheduling->CtDecre = 0;
				BS[bsID]->scheduling->ECCA_count_ava = 1;
				BS[bsID]->scheduling->LBT_step = 2;
			}

			if (BS[bsID]->scheduling->LBT_step == 2)	// step 2
			{
				if (BS[bsID]->scheduling->ECCA_count_CCA[0] > 0 && BS[bsID]->scheduling->CtDecre == 1)
				{
					BS[bsID]->scheduling->ECCA_count_CCA[0] = BS[bsID]->scheduling->ECCA_count_CCA[0] - 1;
				}
				BS[bsID]->scheduling->LBT_step = 3;
				BS[bsID]->scheduling->ECCA_count_time[0] = BS[bsID]->scheduling->ECCA_slot_size;
			}

			if (BS[bsID]->scheduling->LBT_step == 3)	// step 3 
			{
				if (BS[bsID]->scheduling->ECCA_count_CCA[0] > 0)
				{
					if (BS[bsID]->scheduling->ECCA_count_time[0] == BS[bsID]->scheduling->ECCA_slot_size)
					{
						BS[bsID]->scheduling->ECCA_criteria[0] = 0;
					}

					if (BS[bsID]->scheduling->ECCA_count_time[0] > 0 && BS[bsID]->scheduling->ECCA_count_time[0] > BS[bsID]->scheduling->ECCA_slot_size - BS[bsID]->scheduling->sensing_time)
					{
						// LTE U BS
						for (int ot = 0; ot < Sim.network->numBS; ot++)
						{
							if (bsID != ot &&BS[ot]->scheduling->Transmission_on[0] == 1)
							{
										BS[bsID]->scheduling->ECCA_criteria[0] = BS[bsID]->scheduling->ECCA_criteria[0] + MS[bsID]->scheduling->RSRP_fBS[ot][0] / BS[bsID]->scheduling->sensing_time;
							}
						}

						// WiFiBS
						for (int ot = 0; ot < Sim.network->numBS; ot++)
						{
							if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
							{
								BS[bsID]->scheduling->ECCA_criteria[0] = BS[bsID]->scheduling->ECCA_criteria[0] + MS[bsID]->scheduling->RSRP_fBS[ot][1] / BS[bsID]->scheduling->sensing_time;
							}
						}

						// WiFiMS
						for (int ot = 0; ot < Sim.network->numMS; ot++)
						{
							if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
							{
								BS[bsID]->scheduling->ECCA_criteria[0] = BS[bsID]->scheduling->ECCA_criteria[0] + MS[bsID]->scheduling->RSRP_fBS[ot][2] / BS[bsID]->scheduling->sensing_time;
							}
						}

						BS[bsID]->scheduling->ECCA_count_time[0] = BS[bsID]->scheduling->ECCA_count_time[0] - 1;
					}
					else if (BS[bsID]->scheduling->ECCA_count_time[0] > 1 && BS[bsID]->scheduling->ECCA_count_time[0] <= BS[bsID]->scheduling->ECCA_slot_size - BS[bsID]->scheduling->sensing_time)
					{
						BS[bsID]->scheduling->ECCA_count_time[0] = BS[bsID]->scheduling->ECCA_count_time[0] - 1;
					}
					else if (BS[bsID]->scheduling->ECCA_count_time[0] == 1)
					{
						if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[0]) + 30.0 < BS[bsID]->scheduling->LBT_thereshold)
						{
							BS[bsID]->scheduling->LBT_step = 4;
							BS[bsID]->scheduling->CtDecre = 1;
						}
						else if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[0]) + 30.0 >= BS[bsID]->scheduling->LBT_thereshold)
						{
							BS[bsID]->scheduling->LBT_step = 5;
							BS[bsID]->scheduling->ECCA_criteria[0] = 0;
							BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->tf + BS[bsID]->scheduling->mp*BS[bsID]->scheduling->ECCA_slot_size;
							BS[bsID]->scheduling->res_mp = BS[bsID]->scheduling->mp;
							BS[bsID]->scheduling->CtDecre = 0;
						}
					}
				}
				else if (BS[bsID]->scheduling->ECCA_count_CCA[0] == 0)
				{
					BS[bsID]->scheduling->LBT_step = 4;
				}
			}

			if (BS[bsID]->scheduling->LBT_step == 4)	// step 4
			{
				if (BS[bsID]->scheduling->ECCA_count_CCA[0] == 0)
				{
					BS[bsID]->scheduling->ECCA_on[0] = 0;
					BS[bsID]->scheduling->LBT_step = 0;
					BS[bsID]->scheduling->ECCA_count_CCA[0] = 0;
					BS[bsID]->scheduling->Transmission_on[0] = 1;
				}
				else if (BS[bsID]->scheduling->ECCA_count_CCA[0] > 0)
				{
					BS[bsID]->scheduling->LBT_step = 2;
				}
			}

			if (BS[bsID]->scheduling->LBT_step == 5)	// step 5
			{
				if (BS[bsID]->scheduling->res_Td > BS[bsID]->scheduling->mp*BS[bsID]->scheduling->ECCA_slot_size)
				{
 					BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->res_Td - 1;
				}
				else if (BS[bsID]->scheduling->res_Td <= BS[bsID]->scheduling->res_mp*BS[bsID]->scheduling->ECCA_slot_size && BS[bsID]->scheduling->res_Td > BS[bsID]->scheduling->res_mp*BS[bsID]->scheduling->ECCA_slot_size - BS[bsID]->scheduling->sensing_time)
				{
					// LTE U BS
					for (int ot = 0; ot < Sim.network->numBS; ot++)
					{
						if (bsID != ot &&BS[ot]->scheduling->Transmission_on[0] == 1)
						{
							BS[bsID]->scheduling->ECCA_criteria[0] = BS[bsID]->scheduling->ECCA_criteria[0] + MS[bsID]->scheduling->RSRP_fBS[ot][0] / BS[bsID]->scheduling->sensing_time;
						}
					}

					// WiFiBS
					for (int ot = 0; ot < Sim.network->numBS; ot++)
					{
						if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
						{
							BS[bsID]->scheduling->ECCA_criteria[0] = BS[bsID]->scheduling->ECCA_criteria[0] + MS[bsID]->scheduling->RSRP_fBS[ot][1] / BS[bsID]->scheduling->sensing_time;
						}
					}

					// WiFiMS
					for (int ot = 0; ot < Sim.network->numMS; ot++)
					{
						if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
						{
							BS[bsID]->scheduling->ECCA_criteria[0] = BS[bsID]->scheduling->ECCA_criteria[0] + MS[bsID]->scheduling->RSRP_fBS[ot][2] / BS[bsID]->scheduling->sensing_time;
						}
					}

					BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->res_Td - 1;
				}
				else if (BS[bsID]->scheduling->res_Td == (BS[bsID]->scheduling->res_mp - 1)*BS[bsID]->scheduling->ECCA_slot_size + 1)
				{
					if (10 * log10(BS[bsID]->scheduling->ECCA_criteria[0] )+ 30 < BS[bsID]->scheduling->LBT_thereshold - 10)
					{
						BS[bsID]->scheduling->CtDecre++;
					}
					BS[bsID]->scheduling->ECCA_criteria[0] = 0;
					BS[bsID]->scheduling->res_mp = BS[bsID]->scheduling->res_mp - 1;
					BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->res_Td - 1;
					if (BS[bsID]->scheduling->res_mp == 0)
					{
						BS[bsID]->scheduling->LBT_step = 6;
					}
				}
				else
				{
					BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->res_Td - 1;
				}
			}

			if (BS[bsID]->scheduling->LBT_step == 6)	// step 6
			{
				if (BS[bsID]->scheduling->CtDecre == BS[bsID]->scheduling->mp)
				{
					if (BS[bsID]->scheduling->ECCA_count_ava == 0)
					{
						BS[bsID]->scheduling->LBT_step = 1;
						BS[bsID]->scheduling->CtDecre = 0;
					}
					else if (BS[bsID]->scheduling->ECCA_count_ava == 1)
					{
						BS[bsID]->scheduling->LBT_step = 2;
						BS[bsID]->scheduling->CtDecre = 0;
					}
				}
				else
				{
					BS[bsID]->scheduling->LBT_step = 5;
					BS[bsID]->scheduling->ECCA_criteria[0] = 0;
					BS[bsID]->scheduling->res_Td = BS[bsID]->scheduling->tf + BS[bsID]->scheduling->mp*BS[bsID]->scheduling->ECCA_slot_size;
					BS[bsID]->scheduling->res_mp = BS[bsID]->scheduling->mp;
					BS[bsID]->scheduling->CtDecre = 0;
				}
			}
		}
	}
}

void Scheduling::DCFforWiFiBS() {
	// Initialize
	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
				if (WiFiBS[bsID]->scheduling->Transmission_on[0] == 0 && WiFiBS[bsID]->scheduling->state == 0)
				{
					WiFiBS[bsID]->scheduling->state = 1;
					WiFiBS[bsID]->scheduling->tDIFS = WiFiBS[bsID]->scheduling->DIFS;
					WiFiBS[bsID]->scheduling->tSIFS = WiFiBS[bsID]->scheduling->SIFS;
					WiFiBS[bsID]->scheduling->whilebackoff = 0;
					WiFiBS[bsID]->scheduling->error = 0;
					break;
				}
			}

	for (int bsID = 0; bsID < Sim.network->numBS; bsID++)
	{
		if (WiFiBS[bsID]->scheduling->state == 1) {	// DIFS
			WiFiBS[bsID]->scheduling->sensing = 0;
			WiFiBS[bsID]->scheduling->first = 0;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < Sim.network->numMS; j++) {
					WiFiBS[bsID]->scheduling->second[i][j] = 0;
				}
			}


			if (WiFiBS[bsID]->scheduling->tDIFS == 0) {
				if (WiFiBS[bsID]->scheduling->whilebackoff == 0) {
					WiFiBS[bsID]->scheduling->state = 2;
				}
				if (WiFiBS[bsID]->scheduling->whilebackoff == 1) {
					WiFiBS[bsID]->scheduling->state = 3;
					WiFiBS[bsID]->scheduling->whilebackoff == 0;
				}
			}


			// ED
			// LTE U BS
			for (int ot = 0; ot < Sim.network->numBS; ot++)
			{
				if (BS[ot]->scheduling->Transmission_on[0] == 1)
				{
					WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][0];
				}
			}

			// WiFiBS
			for (int ot = 0; ot < Sim.network->numBS; ot++)
			{
				if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
				{
					WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][1];
				}
			}

			// WiFiMS
			for (int ot = 0; ot < Sim.network->numMS; ot++)
			{
				if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
				{
					WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][2];
				}
			}

			if (10 * log10(WiFiBS[bsID]->scheduling->first) + 30 >BS[bsID]->scheduling->LBT_thereshold) {
				WiFiBS[bsID]->scheduling->sensing = 1;
			}


			// Preamble
			// WiFiBS
			for (int ot = 0; ot < Sim.network->numBS; ot++)
			{
				if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
				{
					if (10 * log10(WiFiBS[bsID]->scheduling->RSRP_fBS[ot][1]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
						WiFiBS[bsID]->scheduling->sensing = 1;
					}
				}
			}

			// WiFiMS
			for (int ot = 0; ot < Sim.network->numMS; ot++)
			{
				if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
				{
					if (10 * log10(WiFiBS[bsID]->scheduling->RSRP_fBS[ot][2]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
						WiFiBS[bsID]->scheduling->sensing = 1;
					}
				}
			}


			if (WiFiBS[bsID]->scheduling->sensing == 1) {
				WiFiBS[bsID]->scheduling->tDIFS = Sim.scheduling->DIFS;
			}
			else {
				WiFiBS[bsID]->scheduling->tDIFS = WiFiBS[bsID]->scheduling->tDIFS - 1;
			}

		
		}

		if (WiFiBS[bsID]->scheduling->state == 2) {	// Genearate back-off count
			WiFiBS[bsID]->scheduling->tslot = ceil(rand() / (float)RAND_MAX * WiFiBS[bsID]->scheduling->CW);
			WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->slottime;
			WiFiBS[bsID]->scheduling->state = 3;
		}

		if (WiFiBS[bsID]->scheduling->state == 3) {	// back-off count
			if (WiFiBS[bsID]->scheduling->ttime == 0 && WiFiBS[bsID]->scheduling->tslot == 0) {
				WiFiBS[bsID]->scheduling->state = 4;
				WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->transtime;

				// error check for Transmit start
				WiFiBS[bsID]->scheduling->sensing = 0;
				WiFiBS[bsID]->scheduling->first = 0;
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < Sim.network->numMS; j++) {
						WiFiBS[bsID]->scheduling->second[i][j] = 0;
					}
				}

				// ED
				// LTE U BS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (BS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][0];
					}
				}

				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][1];
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][2];
					}
				}

				if (10 * log10(WiFiBS[bsID]->scheduling->first) + 30 >BS[bsID]->scheduling->LBT_thereshold) {
					WiFiBS[bsID]->scheduling->error = 1;
				}


				// Preamble
				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						if (10 * log10(WiFiBS[bsID]->scheduling->RSRP_fBS[ot][1]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
							WiFiBS[bsID]->scheduling->error = 1;
						}
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						if (10 * log10(WiFiBS[bsID]->scheduling->RSRP_fBS[ot][2]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
							WiFiBS[bsID]->scheduling->error = 1;
						}
					}
				}

				WiFiBS[bsID]->scheduling->Transmission_on[0] = 1;

			}
			// error check for Transmit end


			if (WiFiBS[bsID]->scheduling->ttime == 0 && WiFiBS[bsID]->scheduling->tslot > 0) {	// 각 slot 끝에서
				WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->slottime;

				// ED
				if (10 * log10(WiFiBS[bsID]->scheduling->first) + 30 >BS[bsID]->scheduling->LBT_thereshold) {
					WiFiBS[bsID]->scheduling->sensing = 1;
				}

				// Preamble
				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						if (10 * log10(WiFiBS[bsID]->scheduling->second[ot][1]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
							WiFiBS[bsID]->scheduling->sensing = 1;
						}
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						if (10 * log10(WiFiBS[bsID]->scheduling->second[ot][2]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
							WiFiBS[bsID]->scheduling->sensing = 1;
						}
					}
				}

				if (WiFiBS[bsID]->scheduling->sensing == 1) {
					WiFiBS[bsID]->scheduling->whilebackoff = 1;
					WiFiBS[bsID]->scheduling->state = 1;
				}

				if (WiFiBS[bsID]->scheduling->sensing == 0) {
					WiFiBS[bsID]->scheduling->tslot = WiFiBS[bsID]->scheduling->tslot - 1;
				}

			}
			
			
			if (WiFiBS[bsID]->scheduling->ttime > 0) {
				if (WiFiBS[bsID]->scheduling->ttime == WiFiBS[bsID]->scheduling->slottime) {
					WiFiBS[bsID]->scheduling->sensing = 0;
					WiFiBS[bsID]->scheduling->first = 0;
					for (int i = 0; i < 2; i++) {
						for (int j = 0; j < Sim.network->numMS; j++) {
							WiFiBS[bsID]->scheduling->second[i][j] = 0;
						}
					}
				}

				// ED
				// LTE U BS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (BS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][0]/ WiFiBS[bsID]->scheduling->slottime;
					}
				}

				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][1] / WiFiBS[bsID]->scheduling->slottime;
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][2] / WiFiBS[bsID]->scheduling->slottime;
					}
				}


				// Preamble
				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->second[ot][1] = WiFiBS[bsID]->scheduling->second[ot][1] + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][1] / WiFiBS[bsID]->scheduling->slottime;
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->second[ot][2] = WiFiBS[bsID]->scheduling->second[ot][2] + WiFiBS[bsID]->scheduling->RSRP_fBS[ot][2] / WiFiBS[bsID]->scheduling->slottime;
					}
				}

				WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->ttime - 1;

			}


		}

		if (WiFiBS[bsID]->scheduling->state == 4) {	// transmit
			if (WiFiBS[bsID]->scheduling->ttime == 0) {
				WiFiBS[bsID]->scheduling->state = 5;
				WiFiBS[bsID]->scheduling->Transmission_on[0] = 0;
			}
			
			WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->ttime - 1;
		}

		if (WiFiBS[bsID]->scheduling->state == 5) {	// SIFS
			if (WiFiBS[bsID]->scheduling->tSIFS == 0) {
				WiFiBS[bsID]->scheduling->state = 6;
				WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->acktime;

				// error check for ACK start
				WiFiBS[bsID]->scheduling->sensing = 0;
				WiFiBS[bsID]->scheduling->first = 0;
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < Sim.network->numMS; j++) {
						WiFiBS[bsID]->scheduling->second[i][j] = 0;
					}
				}

				// ED
				// LTE U BS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (BS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiMS[bsID]->scheduling->RSRP_fBS[ot][0];
					}
				}

				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiMS[bsID]->scheduling->RSRP_fBS[ot][1];
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						WiFiBS[bsID]->scheduling->first = WiFiBS[bsID]->scheduling->first + WiFiMS[bsID]->scheduling->RSRP_fBS[ot][2];
					}
				}

				if (10 * log10(WiFiBS[bsID]->scheduling->first) + 30 >BS[bsID]->scheduling->LBT_thereshold) {
					WiFiBS[bsID]->scheduling->error = 1;
				}


				// Preamble
				// WiFiBS
				for (int ot = 0; ot < Sim.network->numBS; ot++)
				{
					if (WiFiBS[ot]->scheduling->Transmission_on[0] == 1)
					{
						if (10 * log10(WiFiMS[bsID]->scheduling->RSRP_fBS[ot][1]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
							WiFiBS[bsID]->scheduling->error = 1;
						}
					}
				}

				// WiFiMS
				for (int ot = 0; ot < Sim.network->numMS; ot++)
				{
					if (WiFiMS[ot]->scheduling->Transmission_on[0] == 1)
					{
						if (10 * log10(WiFiMS[bsID]->scheduling->RSRP_fBS[ot][2]) + 30 > BS[bsID]->scheduling->LBT_thereshold - 20) {
							WiFiBS[bsID]->scheduling->error = 1;
						}
					}
				}

				WiFiMS[bsID]->scheduling->Transmission_on[0] = 1;
			
			}				
			// error check for ACK end

			WiFiBS[bsID]->scheduling->tSIFS = WiFiBS[bsID]->scheduling->tSIFS - 1;
		}

		if (WiFiBS[bsID]->scheduling->state == 6) {	// ACK
			if (WiFiBS[bsID]->scheduling->ttime == 0) {
				WiFiBS[bsID]->scheduling->state = 7;
				WiFiMS[bsID]->scheduling->Transmission_on[0] = 0;
			}

			WiFiBS[bsID]->scheduling->ttime = WiFiBS[bsID]->scheduling->ttime - 1;
		}

		if (WiFiBS[bsID]->scheduling->state == 7) {	// END
			WiFiBS[bsID]->scheduling->error_sum = WiFiBS[bsID]->scheduling->error_sum + WiFiBS[bsID]->scheduling->error;
			WiFiBS[bsID]->scheduling->error_tot++;
			WiFiBS[bsID]->scheduling->state = 0;

			if (WiFiBS[bsID]->scheduling->error == 0) {
				WiFiBS[bsID]->scheduling->CW = WiFiBS[bsID]->scheduling->CWmin;
			}
			else {
				WiFiBS[bsID]->scheduling->CW = WiFiBS[bsID]->scheduling->CW * 2;
				if (WiFiBS[bsID]->scheduling->CW >= WiFiBS[bsID]->scheduling->CWmax) {
					WiFiBS[bsID]->scheduling->CW = WiFiBS[bsID]->scheduling->CWmax;
				}
			}
		}

	}

}

void Scheduling::DCFforWiFiMS() {

}

double Scheduling::EESM(double LinearValueSINR, int ModulationOrder)
{
	double RBIR_value = 0;

	double RBIR_QPSK[] = {
		0.0072, 0.0080, 0.0090, 0.0101, 0.0114, 0.0127, 0.0143, 0.0159, 0.0179,
		0.0200, 0.0225, 0.0251, 0.0282, 0.0315, 0.0352, 0.0394, 0.0442, 0.0493,
		0.0551, 0.0616, 0.0688, 0.0767, 0.0855, 0.0953, 0.1061, 0.1180, 0.1311,
		0.1456, 0.1615, 0.1788, 0.1978, 0.2184, 0.2407, 0.2650, 0.2910, 0.3190,
		0.3489, 0.3806, 0.4141, 0.4493, 0.4859, 0.5239, 0.5628, 0.6024, 0.6422,
		0.6817, 0.7207, 0.7584, 0.7944, 0.8281, 0.8592, 0.8872, 0.9119, 0.9331,
		0.9507, 0.9649, 0.9760, 0.9842, 0.9901, 0.9942, 0.9968, 0.9983, 0.9992,
		0.9997, 0.9999, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000 };

	double RBIR_16QAM[] = {
		0.0036, 0.0040, 0.0045, 0.0050, 0.0057, 0.0063, 0.0071, 0.0080, 0.0089,
		0.0100, 0.0112, 0.0126, 0.0141, 0.0158, 0.0176, 0.0197, 0.0221, 0.0247,
		0.0276, 0.0308, 0.0344, 0.0384, 0.0428, 0.0476, 0.0531, 0.0590, 0.0656,
		0.0728, 0.0808, 0.0895, 0.0990, 0.1094, 0.1206, 0.1329, 0.1461, 0.1603,
		0.1756, 0.1920, 0.2094, 0.2279, 0.2474, 0.2680, 0.2896, 0.3122, 0.3357,
		0.3600, 0.3852, 0.4112, 0.4379, 0.4653, 0.4933, 0.5219, 0.5509, 0.5804,
		0.6103, 0.6403, 0.6709, 0.7014, 0.7317, 0.7617, 0.7910, 0.8193, 0.8463,
		0.8716, 0.8949, 0.9158, 0.9343, 0.9501, 0.9633, 0.9739, 0.9821, 0.9883,
		0.9927, 0.9957, 0.9976, 0.9988, 0.9994, 0.9997, 0.9999, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000 };

	double RBIR_64QAM[] = {
		0.0024, 0.0027, 0.0030, 0.0034, 0.0038, 0.0043, 0.0047, 0.0054, 0.0060,
		0.0067, 0.0075, 0.0084, 0.0094, 0.0106, 0.0117, 0.0132, 0.0147, 0.0165,
		0.0184, 0.0207, 0.0229, 0.0257, 0.0285, 0.0319, 0.0354, 0.0396, 0.0437,
		0.0488, 0.0539, 0.0599, 0.0660, 0.0732, 0.0805, 0.0890, 0.0974, 0.1073,
		0.1172, 0.1285, 0.1398, 0.1525, 0.1653, 0.1795, 0.1937, 0.2092, 0.2247,
		0.2415, 0.2583, 0.2763, 0.2942, 0.3132, 0.3321, 0.3519, 0.3718, 0.3924,
		0.4131, 0.4345, 0.4558, 0.4778, 0.4997, 0.5223, 0.5448, 0.5677, 0.5907,
		0.6141, 0.6374, 0.6611, 0.6848, 0.7087, 0.7325, 0.7564, 0.7802, 0.8036,
		0.8269, 0.8489, 0.8708, 0.8904, 0.9100, 0.9262, 0.9425, 0.9547, 0.9668,
		0.9732, 0.9796, 0.9840, 0.9883, 0.9910, 0.9937, 0.9954, 0.9971, 0.9983,
		0.9995, 0.9998, 1.0000, 1.0000, 1.0000 };

	double SINR_dB = 10.0*log10(LinearValueSINR);

	switch (ModulationOrder)
	{
	case 2:
		if (SINR_dB >= 20.0)
		{
			RBIR_value = 1;
		}
		else if (SINR_dB < -20)
		{
			RBIR_value = 0;
		}
		else
		{
			int RBIR_Upper_Index = (int)((SINR_dB + 20.0) / 0.5 + 1.0);
			int RBIR_Lower_Index = (int)((SINR_dB + 20.0) / 0.5);
			RBIR_value = RBIR_QPSK[RBIR_Lower_Index] + (RBIR_QPSK[RBIR_Upper_Index] - RBIR_QPSK[RBIR_Lower_Index])*((SINR_dB - ((double)RBIR_Lower_Index * 0.5 - 20.0)) / 0.5);
		}
		break;
	case 4:
		if (SINR_dB >= 20.0)
		{
			RBIR_value = 1;
		}
		else if (SINR_dB < -20)
		{
			RBIR_value = 0;
		}
		else
		{
			int RBIR_Upper_Index = (int)((SINR_dB + 20.0) / 0.5 + 1.0);
			int RBIR_Lower_Index = (int)((SINR_dB + 20.0) / 0.5);
			RBIR_value = RBIR_16QAM[RBIR_Lower_Index] + (RBIR_16QAM[RBIR_Upper_Index] - RBIR_16QAM[RBIR_Lower_Index])*((SINR_dB - ((double)RBIR_Lower_Index * 0.5 - 20.0)) / 0.5);
		}
		break;
	case 6:
		if (SINR_dB >= 20.0)
		{
			RBIR_value = 1;
		}
		else if (SINR_dB < -20)
		{
			RBIR_value = 0;
		}
		else
		{
			int RBIR_Upper_Index = (int)((SINR_dB + 20.0) / 0.5 + 1.0);
			int RBIR_Lower_Index = (int)((SINR_dB + 20.0) / 0.5);
			RBIR_value = RBIR_64QAM[RBIR_Lower_Index] + (RBIR_64QAM[RBIR_Upper_Index] - RBIR_64QAM[RBIR_Lower_Index])*((SINR_dB - ((double)RBIR_Lower_Index * 0.5 - 20.0)) / 0.5);
		}
		break;
	}

	return RBIR_value;
}

double Scheduling::EESMdemapping(double AverageEESM, int ModulationOrder)
{
	int i, j;
	double RBIR_SINR[95];
	double ratio, ESINR;

	double RBIR_QPSK[] = {
		0.0072, 0.0080, 0.0090, 0.0101, 0.0114, 0.0127, 0.0143, 0.0159, 0.0179,
		0.0200, 0.0225, 0.0251, 0.0282, 0.0315, 0.0352, 0.0394, 0.0442, 0.0493,
		0.0551, 0.0616, 0.0688, 0.0767, 0.0855, 0.0953, 0.1061, 0.1180, 0.1311,
		0.1456, 0.1615, 0.1788, 0.1978, 0.2184, 0.2407, 0.2650, 0.2910, 0.3190,
		0.3489, 0.3806, 0.4141, 0.4493, 0.4859, 0.5239, 0.5628, 0.6024, 0.6422,
		0.6817, 0.7207, 0.7584, 0.7944, 0.8281, 0.8592, 0.8872, 0.9119, 0.9331,
		0.9507, 0.9649, 0.9760, 0.9842, 0.9901, 0.9942, 0.9968, 0.9983, 0.9992,
		0.9997, 0.9999, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000 };

	double RBIR_16QAM[] = {
		0.0036, 0.0040, 0.0045, 0.0050, 0.0057, 0.0063, 0.0071, 0.0080, 0.0089,
		0.0100, 0.0112, 0.0126, 0.0141, 0.0158, 0.0176, 0.0197, 0.0221, 0.0247,
		0.0276, 0.0308, 0.0344, 0.0384, 0.0428, 0.0476, 0.0531, 0.0590, 0.0656,
		0.0728, 0.0808, 0.0895, 0.0990, 0.1094, 0.1206, 0.1329, 0.1461, 0.1603,
		0.1756, 0.1920, 0.2094, 0.2279, 0.2474, 0.2680, 0.2896, 0.3122, 0.3357,
		0.3600, 0.3852, 0.4112, 0.4379, 0.4653, 0.4933, 0.5219, 0.5509, 0.5804,
		0.6103, 0.6403, 0.6709, 0.7014, 0.7317, 0.7617, 0.7910, 0.8193, 0.8463,
		0.8716, 0.8949, 0.9158, 0.9343, 0.9501, 0.9633, 0.9739, 0.9821, 0.9883,
		0.9927, 0.9957, 0.9976, 0.9988, 0.9994, 0.9997, 0.9999, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000, 1.0000,
		1.0000, 1.0000, 1.0000, 1.0000, 1.0000 };

	double RBIR_64QAM[] = {
		0.0024, 0.0027, 0.0030, 0.0034, 0.0038, 0.0043, 0.0047, 0.0054, 0.0060,
		0.0067, 0.0075, 0.0084, 0.0094, 0.0106, 0.0117, 0.0132, 0.0147, 0.0165,
		0.0184, 0.0207, 0.0229, 0.0257, 0.0285, 0.0319, 0.0354, 0.0396, 0.0437,
		0.0488, 0.0539, 0.0599, 0.0660, 0.0732, 0.0805, 0.0890, 0.0974, 0.1073,
		0.1172, 0.1285, 0.1398, 0.1525, 0.1653, 0.1795, 0.1937, 0.2092, 0.2247,
		0.2415, 0.2583, 0.2763, 0.2942, 0.3132, 0.3321, 0.3519, 0.3718, 0.3924,
		0.4131, 0.4345, 0.4558, 0.4778, 0.4997, 0.5223, 0.5448, 0.5677, 0.5907,
		0.6141, 0.6374, 0.6611, 0.6848, 0.7087, 0.7325, 0.7564, 0.7802, 0.8036,
		0.8269, 0.8489, 0.8708, 0.8904, 0.9100, 0.9262, 0.9425, 0.9547, 0.9668,
		0.9732, 0.9796, 0.9840, 0.9883, 0.9910, 0.9937, 0.9954, 0.9971, 0.9983,
		0.9995, 0.9998, 1.0000, 1.0000, 1.0000 };

	for (i = 0; i < 95; i++)
	{
		RBIR_SINR[i] = -20.0 + (double)i*0.5;
	}

	if (ModulationOrder == 2)
	{
		for (j = 0; j < 95; j++)
		{
			if (AverageEESM - 0.00001 < RBIR_QPSK[j])
			{
				if (j == 0)
				{
					ESINR = -20.0;
				}
				else
				{
					ratio = (RBIR_SINR[j] - RBIR_SINR[j - 1]) / (RBIR_QPSK[j] - RBIR_QPSK[j - 1]);
					ESINR = RBIR_SINR[j - 1] + ratio * (AverageEESM - RBIR_QPSK[j - 1]);
				}
				break;
			}
		}
	}
	else if (ModulationOrder == 4)
	{
		for (j = 0; j < 95; j++)
		{
			if (AverageEESM - 0.00001 < RBIR_16QAM[j])
			{
				if (j == 0)
				{
					ESINR = -20.0;
				}
				else
				{
					ratio = (RBIR_SINR[j] - RBIR_SINR[j - 1]) / (RBIR_16QAM[j] - RBIR_16QAM[j - 1]);
					ESINR = RBIR_SINR[j - 1] + ratio * (AverageEESM - RBIR_16QAM[j - 1]);
				}
				break;
			}
		}
	}
	else if (ModulationOrder == 6)
	{
		for (j = 0; j < 95; j++)
		{
			if (AverageEESM - 0.00001 < RBIR_64QAM[j])
			{
				if (j == 0)
				{
					ESINR = -20.0;
				}
				else
				{
					ratio = (RBIR_SINR[j] - RBIR_SINR[j - 1]) / (RBIR_64QAM[j] - RBIR_64QAM[j - 1]);
					ESINR = RBIR_SINR[j - 1] + ratio * (AverageEESM - RBIR_64QAM[j - 1]);
				}
				break;
			}
		}
	}

	ESINR = pow(10.0, ESINR / 10.0);
	return ESINR;
}

double Scheduling::MCSdecision(double SINRdB_QPSK, double SINRdB_16QAM, double SINRdB_64QAM, int &MCSindex, double &SINRfinal)
{

	// Initialization
	int AMCMode = -1;
	SINRfinal = SINRdB_QPSK;

	// MCS Decision: TargetBLER = 0.1 (Variable TB Size)
	if (SINRdB_64QAM >= 19.8962) {
		AMCMode = 14;
		SINRfinal = SINRdB_64QAM;
	}
	else if (SINRdB_64QAM >= 17.6419) {
		AMCMode = 13;
		SINRfinal = SINRdB_64QAM;
	}
	else if (SINRdB_64QAM >= 15.7625) {
		AMCMode = 12;
		SINRfinal = SINRdB_64QAM;
	}
	else if (SINRdB_64QAM >= 13.9351) {
		AMCMode = 11;
		SINRfinal = SINRdB_64QAM;
	}
	else if (SINRdB_64QAM >= 12.05) {
		AMCMode = 10;
		SINRfinal = SINRdB_64QAM;
	}
	else if (SINRdB_64QAM >= 10.24) {
		AMCMode = 9;
		SINRfinal = SINRdB_64QAM;
	}
	else if (SINRdB_16QAM >= 8.2618) {
		AMCMode = 8;
		SINRfinal = SINRdB_16QAM;
	}
	else if (SINRdB_16QAM >= 6.3627) {
		AMCMode = 7;
		SINRfinal = SINRdB_16QAM;
	}
	else if (SINRdB_16QAM >= 4.4311) {
		AMCMode = 6;
		SINRfinal = SINRdB_16QAM;
	}
	else if (SINRdB_QPSK >= 2.5004) {
		AMCMode = 5;
		SINRfinal = SINRdB_QPSK;
	}
	else if (SINRdB_QPSK >= 0.6426) {
		AMCMode = 4;
		SINRfinal = SINRdB_QPSK;
	}
	else if (SINRdB_QPSK >= -1.3346) {
		AMCMode = 3;
		SINRfinal = SINRdB_QPSK;
	}
	else if (SINRdB_QPSK >= -3.2022) {
		AMCMode = 2;
		SINRfinal = SINRdB_QPSK;
	}
	else if (SINRdB_QPSK >= -5.1903) {
		AMCMode = 1;
		SINRfinal = SINRdB_QPSK;
	}
	else if (SINRdB_QPSK >= -6.8852) {
		AMCMode = 0;
		SINRfinal = SINRdB_QPSK;
	}
	MCSindex = AMCMode;
	if (AMCMode == -1) MCSindex = 0;
	SINRfinal = pow(10.0, SINRfinal / 10); // Final SINR(linear) Value

										   // Spectral Efficiency
	double Bits;
	if (AMCMode == -1) Bits = 0;
	else if (AMCMode == 0) Bits = (double)0.1523;//(1.0/6.0);
	else if (AMCMode == 1) Bits = (double)0.2344;//(1.0/3.0);
	else if (AMCMode == 2) Bits = (double)0.3770;//(2.0/3.0);
	else if (AMCMode == 3) Bits = (double)0.6016;
	else if (AMCMode == 4) Bits = (double)0.8770;//(4.0/3.0);
	else if (AMCMode == 5) Bits = (double)1.1758;//(20.0/13.0);	
	else if (AMCMode == 6) Bits = (double)1.4766;
	else if (AMCMode == 7) Bits = (double)1.9141;//(8.0/3.0);	
	else if (AMCMode == 8) Bits = (double)2.4063;//(10.0/3.0);	
	else if (AMCMode == 9) Bits = (double)2.7305;
	else if (AMCMode == 10) Bits = (double)3.3223;
	else if (AMCMode == 11) Bits = (double)3.9023;
	else if (AMCMode == 12) Bits = (double)4.5234;
	else if (AMCMode == 13) Bits = (double)5.1152;
	else if (AMCMode == 14) Bits = (double)5.5547;

	return Bits;
}

void Scheduling::Conclude()
{

}



void Scheduling::ConcludeIteration()
{

}
