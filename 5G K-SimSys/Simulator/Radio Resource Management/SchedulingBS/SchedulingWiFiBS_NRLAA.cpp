/****************************************************************************

Scheduling (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_FD MIMO.cpp
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
2017.3.1	Minsig Han    	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "SchedulingBS_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/


void SchedulingWiFiBS::Initialize(int bs)
{
	id = bs; // BS ID
	state = 0;
	scheduledMS.zeros(Sim.scheduling->numMaxLayer);
	this->DynamicInitilize();

	DIFS=70;
	SIFS=10;
	CWmin=16;
	CWmax=1024;
	slottime=9;
	transtime=3000;
	acktime=300;
	
	CW = 16;

	error=0;
	error_sum=0;
	error_tot=0;
}

void SchedulingWiFiBS::DynamicInitilize()
{
	Sim.TTIValue = 1000;
	int MaxTTI = LBT_MCOT / Sim.TTIValue;
	int numSubband = Sim.scheduling->numSubband;
	int numBS = Sim.network->numBS;
	int numUE = Sim.network->numMS;


	/*-------------------------------------------------------------------------*/
	/*                                                                         */
	/*                         MEMORY ALLOCATION                               */
	/*                                                                         */
	/*-------------------------------------------------------------------------*/

	this->DIFS_on = new int[numSubband];
	this->ECCA_on = new int[numSubband];
	this->ECCA_count_CCA = new int[numSubband];
	this->ECCA_count_time = new int[numSubband];
	this->ECCA_criteria = new double[numSubband];
	this->Transmission_on = new int[numSubband];
	this->Transmit_total_time = new int[numSubband];
	this->Subband_LBT_Try = new int[numSubband];
	this->Subband_Take_Channel = new int[numSubband];
	this->Transmission_on_sum = new int[numSubband];

	this->reservation = new int[numSubband];
	this->jamming_start_time = new int[numSubband];
	this->jamming_end_time = new int[numSubband];
	this->fake_LTEU_transmit_block_size = new int[numSubband];
	this->Max_DL_Subframe_Num = new int[numSubband];
	this->Max_UL_Subframe_Num = new int[numSubband];
	this->DL_Subframe = new int[numSubband];
	this->UL_Subframe = new int[numSubband];
	this->real_tx_on = new int[numSubband];

	this->InterferenceTimeFromBsForCQI = new int[numBS];
	this->InterferenceTimeFromUeForCQI = new int[numUE];
	this->InterferenceTimeFromBsForFER = new int[numBS];
	this->InterferenceTimeFromUeForFER = new int[numUE];

	this->Transmit_start_time = new int *[numSubband];
	this->Transmit_end_time = new int *[numSubband];
	for (int i = 0; i < numSubband; i++)
	{
		this->Transmit_start_time[i] = new int[MaxTTI];
		this->Transmit_end_time[i] = new int[MaxTTI];
	}


	/*-------------------------------------------------------------------------*/
	/*                                                                         */
	/*                         INITIALIZATION                                  */
	/*                                                                         */
	/*-------------------------------------------------------------------------*/

	for (int i = 0; i < numSubband; i++)
	{
		this->DIFS_on[i] = 0;
		this->ECCA_on[i] = 0;
		this->ECCA_count_CCA[i] = 0;
		this->ECCA_count_time[i] = 0;
		this->ECCA_criteria[i] = 0.0;
		this->Transmission_on[i] = 0;
		this->Transmit_total_time[i] = 0;
		this->Subband_LBT_Try[i] = 0;
		this->Subband_Take_Channel[i] = 0;
		this->Transmission_on_sum[i] = 0;
		this->reservation[i] = 0;
		this->jamming_start_time[i] = 0;
		this->jamming_end_time[i] = 0;
		this->Max_DL_Subframe_Num[i] = 0;
		this->Max_UL_Subframe_Num[i] = 0;
		this->DL_Subframe[i] = 0;
		this->UL_Subframe[i] = 0;
		this->real_tx_on[i] = 0;

		for (int j = 0; j < MaxTTI; j++)
		{
			this->Transmit_start_time[i][j] = 0;
			this->Transmit_end_time[i][j] = 0;
		}
	}

	// new
	this->LBT_step = 0;
	this->res_Td = 0;
	this->tf = 16;
	this->res_mp = 0;
	this->ECCA_slot_size = 10;	// us
	this->CtDecre = 0;
	this->exp_bo_num = 1;
	this->ECCA_count_ava = 0;
	this->sensing_time = 9;
	this->LBT_thereshold = -62;	// dB

	// priority_class
	this->p_class=Sim.NewPClass;

	if (this->p_class == 1) {
		this->mp = 1;
		this->LBT_q = 4;
		this->exp_bo_num_max =2;
		this->LTEU_Transmit_block = 2;

	}
	else if (this->p_class == 2) {
		this->mp = 1;
		this->LBT_q = 8;
		this->exp_bo_num_max=2;
		this->LTEU_Transmit_block =3;

	}
	else if (this->p_class == 3) {
		this->mp = 3;
		this->LBT_q = 16;
		this->exp_bo_num_max=4;
		this->LTEU_Transmit_block = 8;

	}
	else if (this->p_class == 4) {
		this->mp = 7;
		this->LBT_q = 16;
		this->exp_bo_num_max=64;
		this->LTEU_Transmit_block = 8;

	}


	// error;
	this->error = 0;
	this->error_sum = 0;
	this->error_tot = 0;
	
	this->MAC_time = 0;


	for (int i = 0; i < numBS; i++)
	{
		this->InterferenceTimeFromBsForCQI[i] = 0;
		this->InterferenceTimeFromBsForFER[i] = 0;
	}
	for (int i = 0; i < numUE; i++)
	{
		this->InterferenceTimeFromUeForCQI[i] = 0;
		this->InterferenceTimeFromUeForFER[i] = 0;
	}

	this->Subband_LBT_Mode = 0;
	this->DL_Traffic_Existence = 1;
	this->UL_Traffic_Existence = 0;
	this->Transmit_current_fr = 0;
	this->p_cqi_report = 0;
}
//
//void SchedulingBS::FrameStructure(int bsID, SLS::TDDType tddtype)
//{
//	
//	BS[bsID]->scheduling->downlinkBuffer = 0;
//	BS[bsID]->scheduling->uplinkBuffer = 0;
//
//	for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
//	{
//		int msID = BS[bsID]->network->attachedMS[attachedMsID];
//		BS[bsID]->scheduling->downlinkBuffer = BS[bsID]->scheduling->downlinkBuffer + MS[msID]->scheduling->downlinkBuffer;
//		BS[bsID]->scheduling->uplinkBuffer = BS[bsID]->scheduling->uplinkBuffer + MS[msID]->scheduling->uplinkBuffer;
//	}
//	double trafficRatio = BS[bsID]->scheduling->downlinkBuffer / (BS[bsID]->scheduling->downlinkBuffer + BS[bsID]->scheduling->uplinkBuffer);
//	trafficRatio = 0.5;
//	arma::mat lteTDDframestructure;
//
//	switch (tddtype)
//	{
//	case SLS::StaticTDD: // Sim.numTTIperFrame==10인 경우에만 현재 동작
//		BS[bsID]->scheduling->framestructure.zeros(Sim.numTTIperFrame);
//		/*
//		lteTDDframestructure.zeros(7, 10);
//		lteTDDframestructure << 0 << 0 << 1 << 1 << 1 << 0 << 0 << 1 << 1 << 1 << 1 << arma::endr
//			<< 0 << 0 << 1 << 1 << 0 << 0 << 1 << 1 << 1 << 0 << arma::endr
//			<< 0 << 0 << 1 << 0 << 0 << 0 << 1 << 1 << 0 << 0 << arma::endr
//			<< 0 << 0 << 1 << 1 << 1 << 0 << 0 << 0 << 0 << 0 << arma::endr
//			<< 0 << 0 << 1 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr
//			<< 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << arma::endr
//			<< 0 << 0 << 1 << 1 << 1 << 0 << 1 << 1 << 1 << 0 << arma::endr;
//
////		BS[bsID]->scheduling->framestructure = abs(1.0 - (find(lteTDDframestructure == 1) / Sim.numTTIperFrame) - trafficRatio).index_min;
//		*/
//		break;
//	case SLS::DynamicTDD:
//		BS[bsID]->scheduling->framestructure.zeros(Sim.numTTIperFrame);
//		for (int link = 0; link < Sim.numTTIperFrame; link++)
//		{
//			if (arma::randu() > trafficRatio)
//				BS[bsID]->scheduling->framestructure(link) = 0;
//			else
//				BS[bsID]->scheduling->framestructure(link) = 1;
//		}
//		break;
//	case SLS::HybridTDD:
//		BS[bsID]->scheduling->framestructure = sort(arma::randu(Sim.numTTIperFrame > trafficRatio));
//		break;
//	}
//	
//}
//
//void SchedulingBS::Schedule(int bsID)
//{
//	
//	if (BS[bsID]->channel->NumAssociatedMS > 0)
//	{
//		arma::vec PFMetric(BS[bsID]->channel->NumAssociatedMS);
//		for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
//		{
//			int msID = BS[bsID]->network->attachedMS[attachedMsID];
//			//PFMetric(attachedMsID) = MS[msID]->scheduling->spectralEfficiency / MS[msID]->scheduling->averagedThroghput;
//		}
//		int ScheduledAttachedMsID = PFMetric.index_max();
//		BS[bsID]->scheduling->scheduledMS = BS[bsID]->network->attachedMS[ScheduledAttachedMsID];
////		BS[bsID]->scheduling->precodingMatrix = MS[ScheduledAttachedMsID]->scheduling->PrecodingMatrix;
//	}
//
//	else
//	{
//		BS[bsID]->scheduling->scheduledMS = -1;
//		BS[bsID]->scheduling->precodingMatrix.zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//	}
//	
//}
//
//void SchedulingBS::MuMimoSchedule(int bsID, int subband, arma::uvec scheduluedMS, int link)
//{
//	
//	// MU-MIMO Scheduling function - Greedy user selection
//	if (BS[bsID]->channel->NumAssociatedMS > 0)
//	{
//		BS[bsID]->scheduling->numScheduledMS = 0;
//		int numMaxLayer = std::min(Sim.scheduling->numMaxLayer, BS[bsID]->channel->NumAssociatedMS); // 계산 복잡도 줄이기 위해
//		if (numMaxLayer == 0);
//		else
//		{
//			arma::uvec attachedMs(BS[bsID]->channel->NumAssociatedMS);
//			for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
//				attachedMs(attachedMsID) = BS[bsID]->network->attachedMS[attachedMsID];
//
//			arma::uvec *groupMetric; 
//			groupMetric = new arma::uvec[numMaxLayer];
//			arma::vec groupMetricValue; groupMetricValue.zeros(numMaxLayer);
//			for (int numLayer = 0; numLayer < numMaxLayer; numLayer++)
//			{
//				groupMetric[numLayer].zeros(numLayer + 1);
//				printCombination(attachedMs, groupMetric[numLayer], groupMetricValue(numLayer), BS[bsID]->channel->NumAssociatedMS, numLayer + 1, link);
//			}
//			arma::uvec temp = groupMetric[groupMetricValue.index_max()];
//			int tempMS = 0;
//			for (int i = 0; i < arma::size(temp)(0); i++)
//			{
//				if (MS[BS[bsID]->network->attachedMS[temp(i)]]->network->msBuffer != 0) 
//				{
//					BS[bsID]->scheduling->scheduledMS(tempMS) = BS[bsID]->network->attachedMS[temp(i)];
//					BS[bsID]->scheduling->numScheduledMS++;
//				}					
//			}
//
//			/*arma::mat PFMetric; PFMetric.zeros(numMaxLayer, BS[bsID]->channel->NumAssociatedMS);
//			arma::mat PFMetricValue; PFMetricValue.zeros(numMaxLayer, BS[bsID]->channel->NumAssociatedMS);
//			arma::vec groupMetric, value, combinationSet;
//			groupMetric.zeros(numMaxLayer); value.zeros(numMaxLayer); combinationSet.zeros(numMaxLayer);
//			for (int numLayer = 0; numLayer < numMaxLayer; numLayer++)			{
//
//				Combination(attachedMs, groupMetric, value, combinationSet, 0, numMaxLayer, 0, numLayer, 0);
//				PFMetric.row(numLayer) = groupMetric.t();
//				PFMetricValue.row(numLayer) = value.t();
//			}
//			arma::vec temp = PFMetric.row(PFMetricValue.index_max()).t();
//			for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
//				BS[bsID]->scheduling->scheduledMS(attachedMsID) = BS[bsID]->network->attachedMS[int(temp(attachedMsID))];*/
//				
//			/*BS[bsID]->scheduling->scheduledMS.zeros(BS[bsID]->channel->NumAssociatedMS);
//			for (int attachedMsID = 0; attachedMsID < BS[bsID]->channel->NumAssociatedMS; attachedMsID++)
//				BS[bsID]->scheduling->scheduledMS(attachedMsID) = BS[bsID]->network->attachedMS[attachedMsID];*/
//			//		BS[bsID]->scheduling->precodingMatrix = MS[ScheduledAttachedMsID]->scheduling->PrecodingMatrix;
//		}
//		
//	}
//
//	else
//	{
//		BS[bsID]->scheduling->scheduledMS = -1;
//		BS[bsID]->scheduling->precodingMatrix.zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//	}
//	
//}
//
//void SchedulingBS::printCombination(arma::uvec arr, arma::uvec groupMetric, double value, int n, int r, int link)
//{
//	arma::uvec data;
//	data.zeros(r);
//	combinationUtil(arr, data, groupMetric, value, 0, n - 1, 0, r, link);
//}
//
//void SchedulingBS::combinationUtil(arma::uvec arr, arma::uvec data, arma::uvec groupMetric, double value, int start, int end, int index, int r, int link)
//{
//	if (index == r)
//	{
//		double temp = 0; double metricTemp = 0;
//		for (int j = 0; j < r; j++)
//		{
//			double spectralEfficiency, averagedThroghput;
//			if (link == 0)
//			{				
//				spectralEfficiency = MS[arr(j)]->scheduling->downlinkspectralEfficiency;
//				averagedThroghput = MS[arr(j)]->scheduling->downlinkaveragedThroghput;
//			}
//			else
//			{
//				spectralEfficiency = MS[arr(j)]->scheduling->uplinkspectralEfficiency;
//				averagedThroghput = MS[arr(j)]->scheduling->uplinkaveragedThroghput;
//			}
//
//			if (averagedThroghput == 0)
//				metricTemp = spectralEfficiency / double(r);
//			else
//				metricTemp = (spectralEfficiency / averagedThroghput) / double(r);
//
//			temp = temp + metricTemp;			
//		}
//		index = 0;
//		if (value < temp)
//		{
//			groupMetric = data;
//			value = temp;
//		}
//	}
//
//	for (int i = start; i <= end && (end - i + 1) >= (r - index); i++)
//	{
//		data(index) = arr(i);
//		combinationUtil(arr, data, groupMetric, value, i + 1, end, index + 1, r, link);
//	}
//}
//
//double SchedulingBS::GetSpectralEfficiency(double SINR, int &MCS) // uplink에도 같은 값 적용 가능?
//{
//	if (SINR < -7.595) { MCS = -1; return 0.0; }
//	else if (SINR >= -7.595&&SINR < -5.712) { MCS = 0; return  0.1523; }
//	else if (SINR >= -5.712&&SINR < -3.591) { MCS = 1; return 0.2344; }
//	else if (SINR >= -3.591&&SINR < -1.578) { MCS = 2; return 0.3770; }
//	else if (SINR >= -1.578&&SINR < 0.4483) { MCS = 3; return 0.6016; }
//	else if (SINR >= 0.4483&&SINR < 2.345) { MCS = 4; return 0.8770; }
//	else if (SINR >= 2.345&&SINR < 4.312) { MCS = 5; return 1.1758; }
//	else if (SINR >= 4.312&&SINR < 6.264) { MCS = 6; return 1.4766; }
//	else if (SINR >= 6.264&&SINR < 8.248) { MCS = 7; return 1.9141; }
//	else if (SINR >= 8.248&&SINR < 10.24) { MCS = 8; return 2.4063; }
//	else if (SINR >= 10.24&&SINR < 12.05) { MCS = 9; return 2.7305; }
//	else if (SINR >= 12.05&&SINR < 13.93) { MCS = 10; return 3.3223; }
//	else if (SINR >= 13.93&&SINR < 16.02) { MCS = 11; return 3.9023; }
//	else if (SINR >= 16.02&&SINR < 17.83) { MCS = 12; return 4.5234; }
//	else if (SINR >= 17.83&&SINR < 20.06) { MCS = 13; return 5.1152; }
//	else if (SINR >= 20.06) { MCS = 14; return 5.5547; }
//	return -1.0;
//}
//
//void SchedulingBS::FrequencyChannelInterferenceTimeFromBsForCQI(int msID)
//{
//	// 시간 고려
//	int sbs = MS[msID]->network->attachedBS;
//
//	// BS -> UE
//	for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
//	{
//		MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] = 0;
//		if (MS[msID]->scheduling->InterferenceTimeFromBsForCQI[ibs] > 0)
//		{
//			MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] = double(MS[msID]->scheduling->InterferenceTimeFromBsForCQI[ibs]) / double(Sim.TTIValue);
//		}
//
//		// 새 코드
//		for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//		{
//			MS[msID]->channel->FrequencyChannel(ibs, 0, RBindex) = MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] * MS[msID]->channel->FrequencyChannel(ibs, 0, RBindex);
//		}
//	}
//}
//
//void SchedulingBS::Feedback(int msID)
//{
//	int oi[57];
//
//	for (int i = 0; i < 57; i++) {
//		oi[i] = MS[msID]->channel->assIndex[i];
//	}
//
//	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth * 1e6 / 1000;
//	arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
//	arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;
//
//	tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//	tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//	tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
//
//	for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//	{
//		tempRHr = tempRHr + MS[msID]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
//		tempRH = tempRH + (MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
//	}
//
//	arma::svd(tempU, temps, tempV, tempRH, "std");
//	for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//	{
//		tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//		for (int si = 1; si < SLS_MAX_BS; si++)
//		{
//			tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
//		}
//		tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
//		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//		temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
//		signal = temph*temph.t();
//		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
//		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
//	}
//
//	MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(10.0 * log10(pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1), MS[msID]->scheduling->MCS);
//	//MS[msID]->scheduling->PrecodingMatrix = tempV.col(0);
//	
//	for (int RBindex = 0; RBindex < 50; RBindex++) {
//		MS[msID]->scheduling->PreSINR[0][0][RBindex] = FrequencySinr(RBindex);
//	}
//	MS[msID]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (50)) - 1;
//	MS[msID]->scheduling->downlinkESINRdB = 10.0 * log10(MS[msID]->scheduling->downlinkESINR);
//	MS[msID]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->downlinkESINRdB, MS[msID]->scheduling->MCS);
//}
//
//void SchedulingBS::MuMimoFeedback(int msID, int type)
//{
//	
//	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth * 1e6 / 1000;
//	arma::cx_mat tempRI, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
//	arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;
//	arma::cx_mat *analogCodebook, *digitalCodebook;
//	if (type == 0)
//	{
//		for (int RBindex = 0; RBindex < (50); RBindex++)
//		{
//			tempRI.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
//			for (int si = 1; si < SLS_MAX_BS; si++)
//			{
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t()*MS[msID]->channel->FrequencyChannel(si, 0, RBindex) / double(Sim.channel->NumberOfReceiveAntennaPort);
//			}
//			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
//			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort)).i();
//			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
//			signal = temph*temph.t();
//			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort))*tempIRC.t();
//			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
//		}
//	}
//	else
//	{
//		analogCodebook = new arma::cx_mat[16];
//		digitalCodebook = new arma::cx_mat[16];
//		analogCodebook = PrecodingMatrix(Analogbeamforming, analogCodebook);
//		digitalCodebook = PrecodingMatrix(Digitalbeamforming, digitalCodebook);
//		double temp = 0; double maxtemp = 0;
//		for (int analogbeam = 0; analogbeam < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2; analogbeam++)
//		{
//			for (int digitalbeam = 0; digitalbeam < Sim.channel->NumberOfTransmitAntennaPort * 2; digitalbeam++)
//			{
//				for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//				{
//					tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t() * analogCodebook[analogbeam] * digitalCodebook[digitalbeam];
//					tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//					temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
//					temp = temp + trace(real(temph*temph.t()));
//				}
//				if (maxtemp < temp) maxtemp = temp;
//				MS[msID]->scheduling->analogPrecodingMatrix = analogCodebook[analogbeam];
//				MS[msID]->scheduling->digitalPrecodingMatrix = digitalCodebook[digitalbeam];
//			}
//		}
//
//		for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//		{
//			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//			for (int si = 1; si < SLS_MAX_BS; si++)
//			{
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
//			}
//			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()*MS[msID]->scheduling->analogPrecodingMatrix*MS[msID]->scheduling->digitalPrecodingMatrix;
//			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
//			signal = temph*temph.t();
//			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
//			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
//		}
//	}
//	
//
//	MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(10.0 * log10(pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1), MS[msID]->scheduling->MCS);
//	
//}
//
//void SchedulingBS::ReceivedSINR(int msID, int link, int slotnumber)
//{
//
//	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth * 1e6 / 1000;
//	arma::cx_mat tempRI, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
//	arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;
//	double temp = 0; double maxtemp = 0;
//	for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//	{
//		tempM = MS[msID]->channel->FrequencyChannel(0, link, RBindex).t() * MS[msID]->scheduling->analogPrecodingMatrix * MS[msID]->scheduling->digitalPrecodingMatrix;
//		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//		temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, link, RBindex).t();
//		temp = temp + trace(real(temph*temph.t()));
//	}
//
//	for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//	{
//		tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//		for (int si = 1; si < SLS_MAX_BS; si++)
//		{
//			if (BS[si]->scheduling->framestructure(link) == link)
//			{
//				arma::cx_mat precodingMatrix; precodingMatrix.zeros(Sim.channel->NumberOfReceiveAntennaPort, BS[si]->scheduling->scheduledMS(0));
//				//precodingMatrix = MS[BS[si]->scheduling->scheduledMS(0)]->scheduling->analogPrecodingMatrix * MS[BS[si]->scheduling->scheduledMS(0)]->scheduling->digitalPrecodingMatrix;
//
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, link, RBindex)*precodingMatrix*precodingMatrix.t()*MS[msID]->channel->FrequencyChannel(si, link, RBindex).t();
//			}
//			else
//			{
//				arma::cx_mat precodingMatrix; precodingMatrix.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, BS[si]->scheduling->scheduledMS(0));
//				//precodingMatrix = MS[BS[si]->scheduling->scheduledMS(0)]->scheduling->analogPrecodingMatrix * MS[BS[si]->scheduling->scheduledMS(0)]->scheduling->digitalPrecodingMatrix;
//
//				tempRI = tempRI + MS[si]->channel->FrequencyChannel(si, link, RBindex)*precodingMatrix*precodingMatrix.t()*MS[si]->channel->FrequencyChannel(si, link, RBindex).t();
//			}
//
//		}
//		tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()*MS[msID]->scheduling->analogPrecodingMatrix*MS[msID]->scheduling->digitalPrecodingMatrix;
//		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//		temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
//		signal = temph*temph.t();
//		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
//		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
//	}
//
//	MS[msID]->scheduling->uplinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1;
//	MS[msID]->scheduling->uplinkESINRdB = 10.0 * log10(MS[msID]->scheduling->uplinkESINR);
//	MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->uplinkESINRdB, MS[msID]->scheduling->MCS);
//
//}
//
//
//arma::cx_mat* SchedulingBS::PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook)
//{
//	
//	codebook = new arma::cx_mat[Sim.channel->NumberOfReceiveAntennaPort * 2];
//	arma::cx_mat tempanalogCodebook;
//	tempanalogCodebook.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//	std::complex <double> phase;
//	int index_t1, index_t2;
//	std::complex <double> *phase_a = new std::complex <double>[2];
//
//	switch (precodingtype)
//	{
//	case Analogbeamforming:
//		for (int i = 0; i < Sim.channel->NumberOfReceiveAntennaPort; i++)
//		{
//			for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort / 2; j++)
//			{
//				phase.real(0.0);
//				phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfReceiveAntennaPort));
//				tempanalogCodebook(j, i) = exp(phase);
//			}
//		}
//		index_t1 = 0; index_t2 = Sim.channel->NumberOfReceiveAntennaPort;
//		phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
//		for (int i = 0; i < Sim.channel->NumberOfReceiveAntennaPort; i++)
//		{
//			for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort; j++)
//			{
//				if (i % 2 == 0)
//				{
//					codebook[index_t1].zeros(Sim.channel->NumberOfReceiveAntennaPort, 1);
//					codebook[index_t1].submat(0, 0, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
//					codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfReceiveAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
//					codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfReceiveAntennaPort);
//					index_t1 = index_t1 + 1;
//				}
//				else
//				{
//					codebook[index_t2].zeros(Sim.channel->NumberOfReceiveAntennaPort, 1);
//					codebook[index_t2].submat(0, 0, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
//					codebook[index_t2].submat(Sim.channel->NumberOfReceiveAntennaPort / 2, 0, Sim.channel->NumberOfReceiveAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfReceiveAntennaPort / 2 - 1, i);
//					codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfReceiveAntennaPort);
//					index_t2 = index_t2 + 1;
//				}
//			}
//		}
//		return codebook;
//		break;
//
//	case Digitalbeamforming:
//		codebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort * 2];
//		arma::cx_mat tempdigitalCodebook;
//		tempdigitalCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);
//		std::complex <double> phase;
//		for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
//		{
//			for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
//			{
//				phase.real(0.0);
//				phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
//				tempdigitalCodebook(j, i) = exp(phase);
//			}
//		}
//		index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;		
//		phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
//		for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
//		{
//			for (int j = 0; j < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; j++)
//			{
//				if (i % 2 == 0)
//				{
//					codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//					codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//					codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//					codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
//					index_t1 = index_t1 + 1;
//				}
//				else
//				{
//					codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//					codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//					codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//					codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
//					index_t2 = index_t2 + 1;
//				}
//			}
//		}
//		return codebook;
//		break;
//	}
//	
//}
//
//void SchedulingBS::CqiReportCondition(int bsID)
//{
//	for (int msID = 0; msID < Sim.network->numMS; msID++)
//	{
//		if (MS[msID]->network->system_type == 1 && MS[msID]->network->attachedBS == bsID)
//		{
//			int PacketNum = MS[msID]->network->CurrentPacketNumDL;
//
//			BS[bsID]->scheduling->p_cqi_report = 1;
//
//			if ((MS[msID]->network->ArrivalTimeDL > 0 && MS[msID]->network->ArrivalTimeDL < 21 * 1000) || MS[msID]->network->PacketQueueSizeDL[PacketNum] > 0)
//			{
//				if (BS[bsID]->scheduling->p_cqi_report == 0)
//				{
//					BS[bsID]->scheduling->p_cqi_report = 1;
//				}
//			}
//		}
//	}
//}
//
//void SchedulingBS::PreSinrCalculation(int bsID)
//{
//	//int TXon = 0;
//	//for (int i = 0; i < Sim.scheduling->numSubband; i++)
//	//{
//	//	if (BS[bsID]->scheduling->Transmission_on[i] == 1)
//	//	{
//	//		TXon = 1;
//	//		break;
//	//	}
//	//}
//
//	if (BS[bsID]->scheduling->p_cqi_report == 1) // CQI Report Condition이 ON된 상황이라면, (CRS 전송중)
//	{
//		for (int msID = 0; msID < Sim.network->numMS; msID++)
//		{
//			if (MS[msID]->network->attachedBS == bsID)
//			{
//				// CQI Mismatch: delayed CQI
//				if (IDEAL_CQI == 0)
//				{
//					for (int i = 0; i < Sim.scheduling->numSubband; i++)
//					{
//						for (int k = 0; k < RB_PER_SUBBAND; k++)
//						{
//							for (int m = 0; m < CQI_MISMATCH_DELAY - 1; m++)
//							{
//								MS[msID]->scheduling->PreSINR[i][CQI_MISMATCH_DELAY - 1 - m][k] = MS[msID]->scheduling->PreSINR[i][CQI_MISMATCH_DELAY - 2 - m][k];
//							}
//						}
//					}
//				}
//
//				// SINR Calculation For CQI Report
//				if (COT_CQI_ON == 0)
//				{
//						BS[bsID]->scheduling->FrequencyChannelInterferenceTimeFromBsForCQI(msID);
//						BS[bsID]->scheduling->Feedback(msID); // Feedback() 함수의 역할을 대신해야 함
//				}
//				else if (COT_CQI_ON == 1)
//				{
//
//				}
//			}
//		}
//	}
//}
//
//void SchedulingBS::WiderBwOperation(int bsID)
//{
//	// 현재는 딱히 구현 알고리즘이 없어서... 일단 모든 channel에 대해 각각 subband LBT를 수행하기로 함
//	int numSubband = Sim.scheduling->numSubband;
//
//	BS[bsID]->scheduling->Subband_LBT_Mode = 1;
//	for (int i = 0; i < numSubband; i++)
//	{
//		BS[bsID]->scheduling->Subband_LBT_Try[i] = 1;
//	}
//}
//
//void SchedulingBS::Transmission_Decision(int bsID) // Naming rule X
//{
//	int numSubband = Sim.scheduling->numSubband;
//
//
//	/*-------------------------------------------------------------------------*/
//	/*                                                                         */
//	/*              Timing Calculation according to LBT Category               */
//	/*                                                                         */
//	/*-------------------------------------------------------------------------*/
//
//	if (LBT_CATEGORY == 0 || LBT_CATEGORY == 1)
//	{
//		for (int i = 0; i < numSubband; i++)
//		{
//  			if (BS[bsID]->scheduling->Transmission_on[i] == 1 && BS[bsID]->scheduling->Transmit_total_time[i] == 0)
//			{
//				if (BS[bsID]->scheduling->DL_Traffic_Existence == 1)
//				{
// 					int TTIValue = Sim.TTIValue;
//					if ((Sim.usGlobalTime % TTIValue) != 0) // If Simulation time != TTI boundary,
//					{
//						// BS[bsID]->scheduling->TddConfiguration(bsID);
//
//						BS[bsID]->scheduling->reservation[i] = 1; // Initial signal ON 
//
//																	// Initial signal start & end time
//						BS[bsID]->scheduling->jamming_start_time[i] = Sim.usGlobalTime;
//						BS[bsID]->scheduling->jamming_end_time[i] = Sim.usGlobalTime - (Sim.usGlobalTime % TTIValue) + TTIValue - 1; // [참고] 일단은 partial subframe 개념(mini-slot) 사용 하지 않음
//
//																																	   // Data transmission start & end time per TTI
//						if ((BS[bsID]->scheduling->jamming_end_time[i] + 1) % TTIValue != 0) // Partial subframe boundary != subframe boundary
//						{
//
//						}
//						else // // Partial subframe boundary = subframe boundary
//						{
//							BS[bsID]->scheduling->fake_LTEU_transmit_block_size[i] = LTEU_Transmit_block - 1; // Actual Number of TTI
//							BS[bsID]->scheduling->Transmit_total_time[i] = BS[bsID]->scheduling->fake_LTEU_transmit_block_size[i] * TTIValue; // COT
//
//							if (BS[bsID]->scheduling->UL_Traffic_Existence == 0) // If only DL traffic exist,
//							{
//								BS[bsID]->scheduling->Max_DL_Subframe_Num[i] = BS[bsID]->scheduling->fake_LTEU_transmit_block_size[i];
//
//								for (int TTI = 0; TTI < BS[bsID]->scheduling->Max_DL_Subframe_Num[i]; TTI++)
//								{
//									if (TTI == 0) // For first TTI
//									{
//										BS[bsID]->scheduling->Transmit_start_time[i][0] = BS[bsID]->scheduling->jamming_end_time[i] + 1;
//										BS[bsID]->scheduling->Transmit_end_time[i][0] = BS[bsID]->scheduling->Transmit_start_time[i][0] + (TTIValue - 1);
//									}
//									else // For others TTI
//									{
//										BS[bsID]->scheduling->Transmit_start_time[i][TTI] = BS[bsID]->scheduling->Transmit_start_time[i][TTI - 1] + TTIValue;
//										BS[bsID]->scheduling->Transmit_end_time[i][TTI] = BS[bsID]->scheduling->Transmit_end_time[i][TTI - 1] + TTIValue;
//									}
//								}
//							}
//							// UL 관련 동작은 추후에 구현할 예정
//						}
//					}
//					else if ((Sim.usGlobalTime % TTIValue) == 0) // If Simulation time = TTI boundary,
//					{
//						BS[bsID]->scheduling->reservation[i] = 0;	// Initial signal off
//
//						if (BS[bsID]->scheduling->DL_Traffic_Existence == 1) // If DL traffic exist, 
//						{
//							BS[bsID]->scheduling->DL_Subframe[i] = 1; // Go DL data transmission period
//							BS[bsID]->scheduling->UL_Subframe[i] = 0;
//						}
//						else if (BS[bsID]->scheduling->DL_Traffic_Existence == 0 && BS[bsID]->scheduling->UL_Traffic_Existence == 1) // If only UL traffic exist,
//						{
//							BS[bsID]->scheduling->DL_Subframe[i] = 0;
//							BS[bsID]->scheduling->UL_Subframe[i] = 1; // Go UL data transmission period
//						}
//
//						if ((Sim.usGlobalTime % TTIValue) != 0) // Partial subframe boundary != subframe boundary
//						{
//
//						}
//						else // Partial subframe boundary = subframe boundary
//						{
//							BS[bsID]->scheduling->fake_LTEU_transmit_block_size[i] = BS[bsID]->scheduling->LTEU_Transmit_block;
//							BS[bsID]->scheduling->Transmit_total_time[i] = BS[bsID]->scheduling->fake_LTEU_transmit_block_size[i] * TTIValue;
//
//							for (int TTI = 0; TTI < BS[bsID]->scheduling->Max_DL_Subframe_Num[i]; TTI++)
//							{
//								if (TTI == 0) // For first TTI
//								{
//									BS[bsID]->scheduling->Transmit_start_time[i][0] = Sim.usGlobalTime;
//									BS[bsID]->scheduling->Transmit_end_time[i][0] = BS[bsID]->scheduling->Transmit_start_time[i][0] + (TTIValue - 1);
//								}
//								else // For others TTI
//								{
//									BS[bsID]->scheduling->Transmit_start_time[i][TTI] = BS[bsID]->scheduling->Transmit_start_time[i][TTI - 1] + TTIValue;
//									BS[bsID]->scheduling->Transmit_end_time[i][TTI] = BS[bsID]->scheduling->Transmit_end_time[i][TTI - 1] + TTIValue;
//								}
//							}
//
//							// UL 관련 부분은 추후에
//
//						}
//					}
//
//				}
//				// UL Traffic Exist 는 추후에...
//			}
//		}
//	}
//
//
//	/*-------------------------------------------------------------------------*/
//	/*                                                                         */
//	/*                         Transmission Decision                           */
//	/*                                                                         */
//	/*-------------------------------------------------------------------------*/
//
//	// DL & UL Subframe ON/OFF State Decision
//	for (int i = 0; i < numSubband; i++)
//	{
//		if (BS[bsID]->scheduling->jamming_end_time[i] > 0 && BS[bsID]->scheduling->jamming_end_time[i] + 1 == Sim.usGlobalTime) // If initial signal is end, 
//		{
//			BS[bsID]->scheduling->reservation[i] = 0;
//
//			if (BS[bsID]->scheduling->DL_Traffic_Existence == 1) // If DL traffic exist,
//			{
//				BS[bsID]->scheduling->DL_Subframe[i] = 1; // Go DL data transmission period
//				BS[bsID]->scheduling->UL_Subframe[i] = 0;
//			}
//			else if (BS[bsID]->scheduling->DL_Traffic_Existence == 0 && BS[bsID]->scheduling->UL_Traffic_Existence == 1) // If UL traffic only exist
//			{
//
//			}
//		}
//	}
//	// Real Data Transmission ON/OFF Decision
//	for (int i = 0; i < numSubband; i++)
//	{
// 		if (BS[bsID]->scheduling->DL_Subframe[i] == 1 && BS[bsID]->scheduling->Transmit_start_time[i][0] == Sim.usGlobalTime && Sim.usGlobalTime != 0) // If current time = DL data transmission start time
//		{
//			BS[bsID]->scheduling->real_tx_on[i] = 1;
//		}
//	}
//
//
//	/*-------------------------------------------------------------------------*/
//	/*                                                                         */
//	/*                         Performance Metric                              */
//	/*                                                                         */
//	/*-------------------------------------------------------------------------*/
//
//
//}
//
//void SchedulingBS::BsOperationStart(int bsID) // Subband 반영 안됨
//{
//	if (BS[bsID]->scheduling->DL_Subframe[0] == 1 && BS[bsID]->scheduling->UL_Subframe[0] == 0)
//	{
//		int CurrentTTI = BS[bsID]->scheduling->Transmit_current_fr;
//		if (BS[bsID]->scheduling->Transmit_start_time[0][CurrentTTI] == Sim.usGlobalTime)
//		{
//			//if (exp_bo_lteu == 1 || exp_bo_lteu == 2)
//			//{
//			//	pBS[ch_LTEU][ibs].error_on = 0;
//			//	pBS[ch_LTEU][ibs].linkcount = 0;
//			//}
//
//			ISITinitializationForFER(bsID);	// Inter-system Interference Time Initialization for FER
//			if (IDEAL_CQI == 0)
//			{
//				SchedulingDL(bsID);
//				McsAssignDL(bsID);
//			}
//		}
//	}
//}
//
//void SchedulingBS::ISITinitializationForFER(int bsID)
//{
//	for (int msID = 0; msID < Sim.network->numMS; msID++)
//	{
//		if (MS[msID]->network->system_type == 1 && MS[msID]->network->attachedBS == bsID)
//		{
//			// BS -> UE
//			for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
//			{
//				MS[msID]->scheduling->InterferenceTimeFromBsForFER[ibs] = 0;
//			}
//			// UE -> UE
//			for (int ims = 0; ims < Sim.network->numMS; ims++)
//			{
//				MS[msID]->scheduling->InterferenceTimeFromUeForFER[ims] = 0;
//			}
//			// AP -> UE
//
//			// STA -> UE
//		}
//	}
//}
//
//void SchedulingBS::SchedulingDL(int bsID)
//{
//	// Multi-band에 대한 PF 스케쥴링을 어떻게 해야할지 모르겠음.
//	// 자원은 Virtual하게 관리하면 됨 (80MHz를 점유하였으면, RB가 100개에서 400개로 늘어난 것처럼 -> 여기까지는 구현해놓으면 됨)
//	// UE에게 자원을 줄 때, 각 RB에 대한 CQI를 보고, 이에 따라 PF metric이 가장 높은 UE에게 RB를 주는 방식으로 구현하면 될까?
//	// 각 20MHz 밴드는 2048 FFT를 사용하고, 40MHz 밴드는 4096 FFT를 사용하고, 이런식으로 채널이 생성되는거 맞나?
//	// K-sim 코드에서 DFT후 각 subcarrier별로 채널이 어떻게 생성되는지를 알아야하며, subband 일 때, 그리고 Wideband 일 때 어떻게 다른지도 알아야 함
//	// 일단은 Single-channel (기존과 동일)에 대한 부분만 구현
//
//	// Initialization before Resource Allocation Procedures
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			for (int k = 0; k < RB_PER_SUBBAND; k++)
//			{
//				MS[i]->scheduling->AllocatedRB[k] = 0;
//			}
//			MS[i]->scheduling->TotalNumOfAllocatedRB = 0;
//		}
//	}
//
//	// Resource Allocation
//	if (SCHEDULING_MODE == 1) // RB-Level PF
//	{
//		int CurrentFrame = BS[bsID]->scheduling->Transmit_current_fr;
//
//		for (int k = 0; k < RB_PER_SUBBAND; k++) // RB 0번부터~Numpilot 까지
//		{
//			int MaxMetricUserIndex = 0;
//			double MaxMetricValue = 0.0;
//			int NumOfScheduledUser = 0;
//			for (int i = 0; i < Sim.network->numMS; i++) // User 순서대로
//			{
//				if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//				{
//					int PacketNum = MS[i]->network->CurrentPacketNumDL;
//					//int HarqProcessID = BS[bsID]->scheduling->HarqProcessID % 8;
//
//					if (HARQ_ONOFF == 1)
//					{
//						if (HARQ_MODE == 0)
//						{
//							if (MS[i]->network->PacketQueueSizeDL[PacketNum] > 0)
//							{
//								NumOfScheduledUser++;
//								if (IDEAL_CQI == 0) // Real CQI,
//								{
//									if (MaxMetricValue <= MS[i]->scheduling->PreSINR[0][CQI_MISMATCH_DELAY - 1][k] / MS[i]->scheduling->PfAverageR)
//									{
//										MaxMetricValue = MS[i]->scheduling->PreSINR[0][CQI_MISMATCH_DELAY - 1][k] / MS[i]->scheduling->PfAverageR;
//										MaxMetricUserIndex = i;
//									}
//								}
//								if (IDEAL_CQI == 1) // Ideal CQI,
//								{
//
//								}
//							}
//						}
//					}
//				}
//			}
//
//			if (NumOfScheduledUser != 0)
//			{
//				if (HARQ_ONOFF == 1)
//				{
//					MS[MaxMetricUserIndex]->scheduling->AllocatedRB[k] = 1;
//				}
//			}
//		}// RB Loop
//	}
//}
//
//void SchedulingBS::McsAssignDL(int bsID)
//{
//	// Initialization
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			for (int mod = 0; mod < 3; mod++)
//			{
//				MS[i]->scheduling->AvgSinrEESM[mod] = 0.0;
//			}
//			MS[i]->scheduling->EffectiveSINR = 0;
//		}
//	}
//
//	// Effective SINR Calculation
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			int PacketNum = MS[i]->network->CurrentPacketNumDL;
//			int HarqProcessID = MS[i]->scheduling->HarqProcessID % 8;
//
//			if (MS[i]->network->PacketQueueSizeDL[PacketNum] > 0)
//			{
//				if (HARQ_ONOFF == 1)
//				{
//					if (HARQ_MODE == 0)
//					{
//						for (int mod = 0; mod < 3; mod++)
//						{
//							double NumOfScheduledRB = 0.0;
//							for (int k = 0; k < RB_PER_SUBBAND; k++)
//							{
//								if (MS[i]->scheduling->AllocatedRB[k] == 1)
//								{
//									NumOfScheduledRB = NumOfScheduledRB + 1.0;
//
//									if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 0)   // 초기 전송 단말일 때만 -> 할당 받은 RB의 effective SINR 계산
//									{
//										if (IDEAL_CQI == 0)
//										{
//											MS[i]->scheduling->SinrOfRbEESM[mod][k] =
//												Sim.scheduling->EESM(MS[i]->scheduling->PreSINR[0][CQI_MISMATCH_DELAY - 1][k], 2 * (mod + 1));
//										}
//										else if (IDEAL_CQI == 1)
//										{
//										}
//
//										MS[i]->scheduling->AvgSinrEESM[mod] = MS[i]->scheduling->AvgSinrEESM[mod] + MS[i]->scheduling->SinrOfRbEESM[mod][k];
//									}
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
//	// MCS Decision
//	for (int i = 0; i < Sim.network->numMS; i++)
//	{
//		if (MS[i]->network->system_type == 1 && MS[i]->network->attachedBS == bsID)
//		{
//			int HarqProcessID = MS[i]->scheduling->HarqProcessID % 8;
//
//			if (HARQ_ONOFF == 1)
//			{
//				if (HARQ_MODE == 1) // Non-adaptive: 재전송 단말은 MCS 그대로 사용
//				{
//					if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] == 0)  // For Initial Transmission
//					{
//						if (MS[i]->scheduling->TotalNumOfAllocatedRB > 0)
//						{
//							double aQ = 10.0*log10(Sim.scheduling->EESMdemapping(MS[i]->scheduling->AvgSinrEESM[0], 2));
//							double bQ = 10.0*log10(Sim.scheduling->EESMdemapping(MS[i]->scheduling->AvgSinrEESM[1], 4));
//							double cQ = 10.0*log10(Sim.scheduling->EESMdemapping(MS[i]->scheduling->AvgSinrEESM[2], 6));
//							MS[i]->scheduling->TempSpectralEfficiency = Sim.scheduling->MCSdecision(aQ, bQ, cQ, MS[i]->scheduling->TempMCSindex, MS[i]->scheduling->EffectiveSINR);
//
//							MS[i]->scheduling->RealRxMode = 1;
//						}
//					}
//					else if (MS[i]->scheduling->HarqReTxNum[HarqProcessID] > 0) // For Retransmission
//					{
//						MS[i]->scheduling->RealRxMode = 1;
//					}
//				}
//			}
//		}
//	}
//}
//
//void SchedulingBS::ConcludeIteration()
//{
//
//}
//
//void SchedulingBS::Conclude()
//{
//
//}
