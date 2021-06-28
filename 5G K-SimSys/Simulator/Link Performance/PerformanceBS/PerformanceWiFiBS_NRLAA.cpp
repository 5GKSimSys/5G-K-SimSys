/****************************************************************************

Performance for Base Station(FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : PerformanceBS_NReMBB.cpp
DATE         : 2017.3.1
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han     	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "PerformanceBS_NRLAA.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void PerformanceWiFiBS::Initialize(int bs)
{
	id = bs; // BS ID
}

//double PerformanceBS::FER(double SINR, int MCS)
//{
//	double Frame_Error_Rate = 1;
//	double ESINR_L = SINR; //둘다 리니어 값
//	switch (MCS)
//	{
//	case -1: //2015.11.24
//		Frame_Error_Rate = 0.0;
//		break;
//
//	case 0:
//		if (ESINR_L < pow(10.0, -7.737 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(69.109 - 410.4 * ESINR_L);
//		break;
//	case 1:
//		if (ESINR_L < pow(10.0, -5.852 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(70.072 - 269.63 * ESINR_L);
//
//		break;
//
//	case 2:
//		if (ESINR_L < pow(10.0, -3.737 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(69.19 - 163.42 * ESINR_L);
//
//		break;
//
//	case 3:
//		if (ESINR_L < pow(10.0, -1.718 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(70.491 - 104.69 * ESINR_L);
//
//		break;
//
//	case 4:
//		if (ESINR_L < pow(10.0, 0.3206 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(77.142 - 71.651* ESINR_L);
//
//		break;
//
//	case 5:
//		if (ESINR_L < pow(10.0, 2.14 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(47.496 - 29.018 * ESINR_L);
//
//		break;
//
//	case 6:
//		if (ESINR_L < pow(10.0, 4.096 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(45.163 - 17.585 * ESINR_L);
//
//		break;
//
//	case 7:
//		if (ESINR_L < pow(10.0, 6.052 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(45.936 - 11.402 * ESINR_L);
//
//		break;
//
//	case 8:
//		if (ESINR_L < pow(10.0, 8.03 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(44.625 - 7.0239 * ESINR_L);
//
//		break;
//
//	case 9:
//		if (ESINR_L < pow(10.0, 10.03 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(46.766 - 4.6398 * ESINR_L);
//
//		break;
//
//	case 10:
//		if (ESINR_L < pow(10.0, 11.82 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(41.834 - 2.7525 * ESINR_L);
//
//		break;
//	case 11:
//		if (ESINR_L < pow(10.0, 13.65 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(33.542 - 1.4485 * ESINR_L);
//
//		break;
//	case 12:
//		if (ESINR_L < pow(10.0, 15.69 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(29.392 - 0.79247 * ESINR_L);
//
//		break;
//	case 13:
//		if (ESINR_L < pow(10.0, 17.5 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(29.525 - 0.52504 * ESINR_L);
//
//		break;
//	case 14:
//		if (ESINR_L < pow(10.0, 18.98 / 10.0))
//			Frame_Error_Rate = 1.0;
//		else
//			Frame_Error_Rate = exp(8.154 - 0.10315 * ESINR_L);
//
//		break;
//	}
//	return Frame_Error_Rate;
//}
//
//void PerformanceBS::Measure(int bsID, int link)
//{
//	arma::cx_mat tempM, tempRI, tempIRC, temph, signal, interferencePlusNoise;
//
//	double FERvalue, randomFERvalue;
//	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth * 1e6 / 1000;
//	int siIndex;
//	arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;
//	BS[bsID]->channel->AnalogBeamPhase.zeros(arma::size(BS[bsID]->scheduling->scheduledMS)(0));
//	BS[bsID]->channel->DigitalBeamPhase.zeros(arma::size(BS[bsID]->scheduling->scheduledMS)(0));
//	BS[bsID]->channel->BeamAmplitude.zeros(arma::size(BS[bsID]->scheduling->scheduledMS)(0));
//
//	if (BS[bsID]->channel->NumAssociatedMS > 0)
//	{
//		BS[bsID]->performance->MUMIMOGroup = arma::size(BS[bsID]->scheduling->scheduledMS)(0);
//		for (int i = 0; i < arma::size(BS[bsID]->scheduling->scheduledMS)(0); i++)
//		{
//			int msID = BS[bsID]->scheduling->scheduledMS(i);
//
//			randomFERvalue = arma::randu();
//			if (link == 0)
//				FERvalue = FER(MS[msID]->scheduling->downlinkESINR, MS[msID]->scheduling->MCS);
//			else
//				FERvalue = FER(MS[msID]->scheduling->uplinkESINR, MS[msID]->scheduling->MCS);
//
//			if (link == 0)
//			{                              
//				MS[msID]->performance->downlinkThroghput = MS[msID]->scheduling->downlinkspectralEfficiency * Sim.channel->NReMBB.bandwidth / 10 * 50 * (12 * 11 - 12 - 16) * 1000;
// 				MS[msID]->channel->AnalogBeamPhase(0);
//				MS[msID]->channel->DigitalBeamPhase(0);
//				MS[msID]->channel->BeamAmplitude(0) = 1.0 / arma::size(BS[bsID]->scheduling->scheduledMS)(0);
//
//			}
//			else
//			{
//				MS[msID]->performance->uplinkThroghput = MS[msID]->scheduling->uplinkspectralEfficiency * Sim.channel->NReMBB.bandwidth / 10 * 50 * (12 * 11 - 12 - 16) * 1000;
//				MS[msID]->channel->AnalogBeamPhase(1);
//				MS[msID]->channel->DigitalBeamPhase(1);
//				MS[msID]->channel->BeamAmplitude(1) = 1.0 / arma::size(BS[bsID]->scheduling->scheduledMS)(0);
//				BS[bsID]->channel->AnalogBeamPhase(i) = MS[msID]->channel->AnalogBeamPhase(1);
//				BS[bsID]->channel->DigitalBeamPhase(i) = MS[msID]->channel->DigitalBeamPhase(1);
//				BS[bsID]->channel->BeamAmplitude(i) = MS[msID]->channel->BeamAmplitude(1);
//			}
//
//			MS[msID]->performance->instantThroughput = MS[msID]->scheduling->downlinkspectralEfficiency * Sim.channel->NReMBB.bandwidth / 10 * 50 * (12 * 11 - 12 - 16) * 1000;
//			MS[msID]->network->msBuffer = MS[msID]->network->msBuffer - MS[msID]->performance->instantThroughput;
//			if (MS[msID]->network->msBuffer < 0)
//				MS[msID]->network->msBuffer = 0;
//		}	
//		
//	}
//	else
//	{
//		BS[bsID]->performance->throughput = 0;
//	}
//	
//}
//
//void PerformanceBS::MuMimoMeasure(int bsID)
//{
//	
//
//
//}
//
//void PerformanceBS::BsOperationEnd(int bsID) // Subband 반영 안됨
//{
//	int CurrentTTI = BS[bsID]->scheduling->Transmit_current_fr;
//	if (BS[bsID]->scheduling->Transmit_start_time[0][CurrentTTI] == Sim.TTIValue && BS[bsID]->scheduling->DL_Subframe[0] == 1 && BS[bsID]->scheduling->UL_Subframe[0] == 0)
//	{
//		PostSinrCalculation(bsID);
//		if (IDEAL_CQI == 1)
//		{
//			BS[bsID]->scheduling->SchedulingDL(bsID);
//			BS[bsID]->scheduling->McsAssignDL(bsID);
//		}
//		FerCheckDL(bsID);
//	}
//}
//
//void PerformanceBS::PostSinrCalculation(int bsID) // Subband 반영 안됨
//{
//	for (int msID = 0; msID < Sim.network->numMS; msID++)
//	{
//		int PacketNum = MS[msID]->network->CurrentPacketNumDL;
//		if (MS[msID]->network->attachedBS == bsID && MS[msID]->network->PacketQueueSizeDL[PacketNum] > 0)
//		{
//			MS[msID]->performance->ISIPcalculationForFerCheck(msID, 0);
//			MS[msID]->channel->ShortTermChannel(msID); // 추후에는 ShorTermChannel 함수안의 DftParameterSetting, DiscreteFourierTransform 함수에 From UE, From AP, From STA 채널 생성도 추가해야 함
//			MS[msID]->performance->SINRCalculationForFerCheck(msID, 0);	// Feedback 함수 이용해서 SINR 계산
//		}
//	}
//}
//
//void PerformanceBS::FerCheckDL(int bsID) // Subband 반영 안됨
//{
//	// Initialization
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID && MS[i]->scheduling->RealRxMode == 1)
//		{
//			if (MS[i]->scheduling->TempMCSindex >= 9 && MS[i]->scheduling->TempMCSindex <= 14) {
//				MS[i]->scheduling->ModulationOrderDL = 6;
//			}
//			else if (MS[i]->scheduling->TempMCSindex >= 6 && MS[i]->scheduling->TempMCSindex <= 8) {
//				MS[i]->scheduling->ModulationOrderDL = 4;
//			}
//			else if (MS[i]->scheduling->TempMCSindex >= 0 && MS[i]->scheduling->TempMCSindex <= 5) {
//				MS[i]->scheduling->ModulationOrderDL = 2;
//			}
//
//			int mod = (MS[i]->scheduling->ModulationOrderDL / 2) - 1;
//			MS[i]->scheduling->InstantR = 0.0;
//			MS[i]->scheduling->TotalNumOfAllocatedRB = 0;
//			MS[i]->scheduling->AvgSinrEESM[mod] = 0.0;
//			MS[i]->scheduling->EffectiveSINR = 0;
//		}
//	}
//
//	// Received SINR Calculation (할당받은 RB에 대해)
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID && MS[i]->scheduling->RealRxMode == 1)
//		{
//			int PacketIndex = MS[i]->network->CurrentPacketNumDL;
//			if (MS[i]->network->PacketQueueSizeDL[PacketIndex] > 0)
//			{
//				int mod = (MS[i]->scheduling->ModulationOrderDL / 2) - 1;
//				int HaqrProcessID = MS[i]->scheduling->HarqProcessID % 8;
//				//int BS_Process_ID = pBS[ch_LTEU][ibs].frame_for_HARQ % 8;
//
//				if (HARQ_ONOFF == 1)
//				{
//					if (HARQ_MODE == 1)
//					{
//						double NumOfScheduledRB = 0.0;
//						if (MS[i]->scheduling->HarqReTxNum[HaqrProcessID] == 0) // For Initial Transmission
//						{
//							for (int k = 0; k < RB_PER_SUBBAND; k++)
//							{
//								if (MS[i]->scheduling->AllocatedRB[k] == 1)
//								{
//									NumOfScheduledRB = NumOfScheduledRB + 1.0;
//									MS[i]->scheduling->SinrOfRbEESM[mod][k] =
//										Sim.scheduling->EESM(MS[i]->scheduling->FerSINR[k], 2 * (mod + 1));
//									MS[i]->scheduling->AvgSinrEESM[mod] = MS[i]->scheduling->AvgSinrEESM[mod] + MS[i]->scheduling->SinrOfRbEESM[mod][k];
//								}
//							}
//							MS[i]->scheduling->TotalNumOfAllocatedRB = NumOfScheduledRB;
//							MS[i]->scheduling->AvgSinrEESM[mod] = MS[i]->scheduling->AvgSinrEESM[mod] / NumOfScheduledRB;
//						}
//						else if (MS[i]->scheduling->HarqReTxNum[HaqrProcessID] > 0) // For Retransmission
//						{
//							for (int k = 0; k < RB_PER_SUBBAND; k++)
//							{
//								if (MS[i]->scheduling->AllocatedRB[k] == 1)
//								{
//									NumOfScheduledRB = NumOfScheduledRB + 1.0;
//									MS[i]->scheduling->SinrOfRbEESM[mod][k] =
//										Sim.scheduling->EESM(MS[i]->scheduling->FerSINR[k] + MS[i]->scheduling->HarqSINR[HaqrProcessID][k], 2 * (mod + 1)); // SINR Combining (CC)
//									MS[i]->scheduling->AvgSinrEESM[mod] = MS[i]->scheduling->AvgSinrEESM[mod] + MS[i]->scheduling->SinrOfRbEESM[mod][k];
//								}
//							}
//							MS[i]->scheduling->TotalNumOfAllocatedRB = NumOfScheduledRB;
//							MS[i]->scheduling->AvgSinrEESM[mod] = MS[i]->scheduling->AvgSinrEESM[mod] / NumOfScheduledRB;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// Effective SINR Calculation (EESM demapping을 통해 Final SINR 계산)
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID && MS[i]->scheduling->RealRxMode == 1)
//		{
//			int MCSindex = MS[i]->scheduling->ModulationOrderDL;
//			int mod = (MS[i]->scheduling->ModulationOrderDL / 2) - 1;
//			int HarqProcessID = MS[i]->scheduling->HarqProcessID % 8;
//			//int BS_Process_ID = pBS[ch_LTEU][ibs].frame_for_HARQ % 8;
//
//			if (MS[i]->scheduling->TotalNumOfAllocatedRB != 0)
//			{
//				if (HARQ_ONOFF == 1)
//				{
//					if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 0) {	// Initial Transmission
//						MS[i]->scheduling->EffectiveSINR = Sim.scheduling->EESMdemapping(MS[i]->scheduling->AvgSinrEESM[mod], MCSindex);
//					}
//					else if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] > 0) { // Retransmission
//						MS[i]->scheduling->HarqEffectiveSINR[HarqProcessID] = Sim.scheduling->EESMdemapping(MS[i]->scheduling->AvgSinrEESM[mod], MCSindex);
//					}
//				}
//			}
//		}
//	}
//
//	// FER Check-up & HARQ Update
//	for (int i = 0; i < Sim.network->numMS; i++) // 
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			if (MS[i]->scheduling->TotalNumOfAllocatedRB == 0) // 할당을 못받은 경우.(재전송 자원 포함!)
//			{
//				MS[i]->scheduling->InstantR = 0.0; // 이번 TTI에 처리한 수율 = 0
//			}
//			else
//			{
//				MS[i]->scheduling->RealRxMode = 0;
//				int HarqProcessID = MS[i]->scheduling->HarqProcessID % 8;
//
//				// FER Calculation & Check-up
//				double dFER = 0.0;
//				if (HARQ_ONOFF == 1)
//				{
//					if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 0) // For Initial Transmission, 현재 MCS, SINR 사용
//					{
//						double TempSINR = 10 * log10(MS[i]->scheduling->EffectiveSINR);
//						dFER = FER(10 * log10(MS[i]->scheduling->EffectiveSINR), MS[i]->scheduling->TempMCSindex);
//						dFER = FER(10 * log10(MS[i]->scheduling->EffectiveSINR), MS[i]->scheduling->TempMCSindex);
//					}
//					else if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] > 0) // For Retransmission, 재전송 MCS, SINR 사용
//					{
//						//재전송 받았을 때 디코딩을 위한 SINR 계산
//						if (HARQ_MODE == 1) // non-adaptive HARQ (MCS 그대로)
//						{
//							double TempSINR = 10 * log10(MS[i]->scheduling->HarqEffectiveSINR[HarqProcessID]);
//							dFER = FER(10 * log10(MS[i]->scheduling->HarqEffectiveSINR[HarqProcessID]), MS[i]->scheduling->HarqMCSindex[HarqProcessID]);
//						}
//					}
//				}
//
//				double dRandomValue = arma::randu();
//
//				// Transmission Fail
//				if (dFER >= dRandomValue)
//				{
//					MS[i]->scheduling->InstantR = 0.0; // 이번 TTI에 처리한 수율 = 0
//														 // LBT Update: Exponential Backoff // 구현 추후에
//
//														 // HARQ Update: # of Retransmission, MCS Index, Spectral Efficiency, SINR // Packet Loss // Throughput Measure
//					if (HARQ_ONOFF == 1)
//					{
//						// # of Retransmission Update
//						MS[i]->scheduling->HarqReTxNum[HarqProcessID]++;
//
//						// MCS Index, Spectral Efficiency, SINR Update
//						if (HARQ_MODE == 1)
//						{
//							if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 1) // When Initial Transmission,
//							{
//								MS[i]->scheduling->HarqMCSindex[HarqProcessID] = MS[i]->scheduling->TempMCSindex;
//								MS[i]->scheduling->HarqSpectralEfficiency[HarqProcessID] = MS[i]->scheduling->TempSpectralEfficiency;
//								for (int k = 0; k < RB_PER_SUBBAND; k++) {
//									MS[i]->scheduling->HarqSINR[HarqProcessID][k] = MS[i]->scheduling->FerSINR[k];
//								}
//							}
//							else if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] > 1) // When Retransmission
//							{
//								for (int k = 0; k < RB_PER_SUBBAND; k++) {
//									MS[i]->scheduling->HarqSINR[HarqProcessID][k] = MS[i]->scheduling->HarqSINR[HarqProcessID][k] + MS[i]->scheduling->FerSINR[k];
//								}
//							}
//						}
//
//						//  Packet Loss: 변수 초기화
//						if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 4)
//						{
//							for (int k = 0; k < RB_PER_SUBBAND; k++) {
//								MS[i]->scheduling->HarqSINR[HarqProcessID][k] = 0;
//							}
//							MS[i]->scheduling->HarqEffectiveSINR[HarqProcessID] = 0.0;
//							MS[i]->scheduling->HarqReTxNum[HarqProcessID] = 0;
//							//MS[i]->scheduling->Packet_Loss_2[ibs] = pMS[ch_LTEU][i].Packet_Loss_2[ibs] + 1;
//						}
//
//						MS[i]->scheduling->HarqProcessID++;
//					}
//				}
//				// Transmission Success
//				else
//				{
//					// Throughput Update
//					int CurrentTTI = BS[bsID]->scheduling->Transmit_current_fr;
//					double TxLength = double(BS[bsID]->scheduling->Transmit_end_time[CurrentTTI] - BS[bsID]->scheduling->Transmit_start_time[CurrentTTI] + 1) / Sim.TTIValue;
//					if (HARQ_ONOFF == 1)
//					{
//						if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 0) // For Initial Transmission
//						{
//							MS[i]->scheduling->InstantR
//								= TxLength * MS[i]->scheduling->TempSpectralEfficiency * MS[i]->scheduling->TotalNumOfAllocatedRB * 12.0 * 14.0 * ((100.0 - LAA_CONTROL_OVERHEAD_DL) / 100.0) * 1000; // BPS	
//						}
//						else if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] > 0) // For Retransmission
//						{
//							MS[i]->scheduling->InstantR
//								= TxLength * MS[i]->scheduling->HarqSpectralEfficiency[HarqProcessID] * MS[i]->scheduling->TotalNumOfAllocatedRB * 12.0 * 14.0 * ((100.0 - LAA_CONTROL_OVERHEAD_DL) / 100.0) * 1000; // BPS
//						}
//					}
//
//					// DL Buffer Size Update
//					double BufferSize = MS[i]->network->BufferSizeDL - (MS[i]->scheduling->InstantR / 1000.0); // UE의 버퍼에 남은 bit 숫자 계산
//					if (BufferSize < 0) {
//						MS[i]->network->BufferSizeDL = 0.0;
//					}
//					else {
//						MS[i]->network->BufferSizeDL = MS[i]->network->BufferSizeDL - (MS[i]->scheduling->InstantR / 1000.0);
//					}
//
//					// DL Packet Size Update
//					if (FTP_TRAFFIC_MODEL == 3)
//					{
//						int PacketNum = MS[i]->network->CurrentPacketNumDL;
//						if (MS[i]->network->PacketQueueSizeDL[PacketNum] > 0)
//						{
//							double RemainedPacketSize = MS[i]->network->PacketQueueSizeDL[PacketNum] - (MS[i]->scheduling->InstantR / 1000.0);
//							if (RemainedPacketSize <= 0) {
//								MS[i]->network->PacketQueueSizeDL[PacketNum] = 0.0;
//							}
//							else {
//								MS[i]->network->PacketQueueSizeDL[PacketNum] = MS[i]->network->PacketQueueSizeDL[PacketNum] - (MS[i]->scheduling->InstantR / 1000.0);
//							}
//						}
//					}
//
//					// HARQ 초기화
//					if (HARQ_ONOFF == 1)
//					{
//						for (int k = 0; k < RB_PER_SUBBAND; k++) {
//							MS[i]->scheduling->HarqSINR[HarqProcessID][k] = 0;
//						}
//						MS[i]->scheduling->HarqEffectiveSINR[HarqProcessID] = 0.0;
//						MS[i]->scheduling->HarqReTxNum[HarqProcessID] = 0;
//
//						MS[i]->scheduling->HarqProcessID++;
//					}
//				}
//			}
//		}
//	}
//
//	// PF Metric Update
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			int PacketNum = MS[i]->network->CurrentPacketNumDL;
//			if (MS[i]->network->PacketQueueSizeDL[PacketNum] > 0 || MS[i]->scheduling->InstantR > 0) {
//				MS[i]->scheduling->PfAverageR = (1.0 - 0.02) * MS[i]->scheduling->PfAverageR + (0.02) * MS[i]->scheduling->InstantR; // Tc = 1/50
//			}
//		}
//	}
//
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		// Performance Measure: LAA UPT & Delay
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			if (FTP_TRAFFIC_MODEL == 3)
//			{
//				int PacketNum = MS[i]->network->CurrentPacketNumDL;
//				if (MS[i]->network->PacketQueueSizeDL[PacketNum] == 0 && MS[i]->network->PacketQueueDelayDL[PacketNum] > 0)
//				{
//					if (ceil(Sim.usGlobalTime / 1000) >= RECORDING_START)
//					{
//						/*ofstream output0;
//						output0.open((string)tmp_filename, ios::app);
//						output0 << CBR / (1000000.0*pMS[ch_LTEU][i].packet_queue_time[tmp_pkt_index]) << endl;*/
//					}
//
//					if (ceil(Sim.usGlobalTime / 1000) >= RECORDING_START)
//					{
//						//ofstream output1;
//						//output1.open((string)tmp_filename_28, ios::app);
//						//output1 << 1000.0*pMS[ch_LTEU][i].packet_queue_time[tmp_pkt_index] << endl;
//					}
//
//					MS[i]->network->CurrentPacketNumDL++;
//				}
//			}
//		}
//
//		// Performance Measure: LAA Rho
//		if (MS[i]->scheduling->InstantR != 0 && ceil(Sim.usGlobalTime / 1000) >= RECORDING_START)
//		{
//			Sim.performance->ServedCellThroughputLaaDL = Sim.performance->ServedCellThroughputLaaDL + (MS[i]->scheduling->InstantR / 1000.0);
//		}
//	}
//}
//
//void PerformanceBS::BsEndAction(int bsID) // Subband 반영 안됨
//{
//	int CurrentTTI = BS[bsID]->scheduling->Transmit_current_fr;
//	if (BS[bsID]->scheduling->DL_Subframe[0] == 1 && BS[bsID]->scheduling->UL_Subframe[0] == 0)
//	{
//		BS[bsID]->scheduling->Transmit_current_fr++;
//		BS[bsID]->scheduling->ECCA_count_ava = 0;
//
//		// Buffer Size Check
//		double BufferSize = 0.0;
//		for (int msID = 0; msID < Sim.network->numMS; msID++)
//		{
//			if (MS[msID]->network->system_type == 1 && MS[msID]->network->attachedBS == bsID)
//			{
//				int PacketNum = MS[msID]->network->CurrentPacketNumDL;
//				if (MS[msID]->network->PacketQueueSizeDL[PacketNum] > 0)
//				{
//					BufferSize = BufferSize + MS[msID]->network->PacketQueueSizeDL[PacketNum];
//				}
//			}
//		}
//
//		BufferSize = 1.0;
//
//		if (BufferSize == 0)	// If there is no DL Traffic in Buffer -> Go UL Transmission or Release the Channel
//		{
//			if (LBT_CATEGORY == 0 || LBT_CATEGORY == 1)
//			{
//				//BS[bsID]->scheduling->Not_alloc_count = BS[bsID]->scheduling->Max_DL_Subframe_Num[0] - BS[bsID]->scheduling->Transmit_current_fr; 
//				BS[bsID]->scheduling->Transmit_current_fr = BS[bsID]->scheduling->Max_DL_Subframe_Num[0];
//			}
//		}
//
//		// End Action according to LBT Category
//		if (LBT_CATEGORY == 0 || LBT_CATEGORY == 1)
//		{
//			if (BS[bsID]->scheduling->Transmit_current_fr == BS[bsID]->scheduling->Max_DL_Subframe_Num[0]) // If DL is end,
//			{
//				if (BS[bsID]->scheduling->UL_Traffic_Existence == 0) // If there is no UL Traffic, then Release the Channel
//				{
//					//exp back off size 결정
//					/*if (exp_bo_lteu == 1 || exp_bo_lteu == 2 || exp_bo_lteu == 3)
//					{
//					if (pBS[ch_LTEU][ibs].error_on == 0)
//					{
//					pBS[ch_LTEU][ibs].exp_bo_num = 1;
//					}
//					else if (pBS[ch_LTEU][ibs].error_on > 0) // NACK이 하나만 있어도 2배 증가
//					{
//					pBS[ch_LTEU][ibs].exp_bo_num = min(max_exp_size, pBS[ch_LTEU][ibs].exp_bo_num*2.0);
//					}
//					}
//					if (exp_bo_lteu == 3)
//					{
//					pBS[ch_LTEU][ibs].error_on = 0;
//					}
//					if (exp_bo_lteu == 6) // Rel. 13 Standard
//					{
//					double tmp_ratio = double(pBS[ch_LTEU][ibs].error_on) / double(pBS[ch_LTEU][ibs].linkcount);
//
//					if (tmp_ratio > 0.8) // NACK이 80% 넘으면 2배 증가
//					{
//					pBS[ch_LTEU][ibs].exp_bo_num = min(max_exp_size, pBS[ch_LTEU][ibs].exp_bo_num*2.0);
//					}
//					else // NACK이 80% 안넘으면 초기화
//					{
//					pBS[ch_LTEU][ibs].exp_bo_num = 1;
//					}
//
//					if (pBS[ch_LTEU][ibs].exp_bo_num == max_exp_size)
//					{
//					pBS[ch_LTEU][ibs].max_exp_count++;
//					}
//					else
//					{
//					pBS[ch_LTEU][ibs].max_exp_count = 0;
//					}
//
//					if (pBS[ch_LTEU][ibs].max_exp_count == max_exp_count_th)
//					{
//					pBS[ch_LTEU][ibs].exp_bo_num = 1;
//					pBS[ch_LTEU][ibs].max_exp_count = 0;
//					}
//					}*/
//
//					BS[bsID]->scheduling->Transmit_current_fr = 0;
//					for (int fr = 0; fr < BS[bsID]->scheduling->fake_LTEU_transmit_block_size[0]; fr++)
//					{
//						BS[bsID]->scheduling->Transmit_start_time[0][fr] = 0;
//						BS[bsID]->scheduling->Transmit_end_time[0][fr] = 0;
//					}
//					BS[bsID]->scheduling->p_cqi_report = 0;
//					BS[bsID]->scheduling->real_tx_on[0] = 0;
//					BS[bsID]->scheduling->Transmission_on[0] = 0;
//					//pWLAN->lteubs_act[ch_LTEU][ibs] = pBS[ch_LTEU][ibs].Transmission_on;
//					BS[bsID]->scheduling->Transmit_total_time[0] = 0;
//
//					BS[bsID]->scheduling->ECCA_on[0] = 0;
//					BS[bsID]->scheduling->ECCA_count_CCA[0] = 0;
//
//					BS[bsID]->scheduling->DL_Subframe[0] = 0;
//					BS[bsID]->scheduling->UL_Subframe[0] = 0;
//
//					//BS[bsID]->scheduling->DL_Traffic_Existence = 0; // UL_LAA
//				}
//				// UL 있는 상황은 나중에 구현할 예정
//			}
//		}
//	}
//}
//
//void PerformanceBS::ConcludeIteration() {
//
//}
//
//void PerformanceBS::Conclude() {
//
//}
