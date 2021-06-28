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

#include "SchedulingMS_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SchedulingWiFiMS::Initialize(int ms)
{
	id = ms; // MS ID
	state = 0;
	//averagedThroghput = 0.0001;
	if (Sim.scheduling->trafficModel == RRM::NonFullBuffer)
	{
		double dataSize = Sim.scheduling->dataSize;
	}
	this->DynamicInitilize();
}

void SchedulingWiFiMS::DynamicInitilize()
{
	int numBS = Sim.network->numBS;
	int numMS = Sim.network->numMS;
	int numSubband = Sim.scheduling->numSubband;


	/*-------------------------------------------------------------------------*/
	/*                                                                         */
	/*                         MEMORY ALLOCATION                               */
	/*                                                                         */
	/*-------------------------------------------------------------------------*/
	
	// Inter-system Interference
	this->InterferenceTimeFromBsForCQI = new int[numBS];
	this->InterferenceTimeFromBsForFER = new int[numBS];
	this->AvgInterferenceFromBsForFER = new double[numBS];
	this->InterferenceTimeFromUeForCQI = new int[numMS];
	this->InterferenceTimeFromUeForFER = new int[numMS];
	this->AvgInterferenceFromBsForCQI = new double[numBS];
	this->Transmission_on = new int[numSubband];

	// Resource Allocation & MCS Decision
	this->AllocatedRB = new int[RB_PER_SUBBAND];

	// SINR (Pre & Post)
	this->PreSINR = new double **[numSubband];
	
	for (int i = 0; i < numSubband; i++)
	{
		this->PreSINR[i] = new double *[CQI_MISMATCH_DELAY];
		for (int j = 0; j < CQI_MISMATCH_DELAY; j++)
		{
			this->PreSINR[i][j] = new double[RB_PER_SUBBAND];
		}
	}
	this->FerSINR = new double[numSubband];
	this->AvgSinrEESM = new double[3];
	this->SinrOfRbEESM = new double *[3];
	for (int i = 0; i < 3; i++)
	{
		this->SinrOfRbEESM[i] = new double[RB_PER_SUBBAND];
	}

	// HARQ
	this->HarqReTxNum = new int[HARQ_PROCESS_NUM];
	this->HarqMCSindex = new int[HARQ_PROCESS_NUM];
	this->HarqSpectralEfficiency = new double[HARQ_PROCESS_NUM];
	this->HarqEffectiveSINR = new double[HARQ_PROCESS_NUM];
	this->HarqSINR = new double *[HARQ_PROCESS_NUM];
	for (int i = 0; i < HARQ_PROCESS_NUM; i++)
	{
		this->HarqSINR[i] = new double[RB_PER_SUBBAND];
	}


	/*-------------------------------------------------------------------------*/
	/*                                                                         */
	/*                         INITIALIZATION                                  */
	/*                                                                         */
	/*-------------------------------------------------------------------------*/
	
	// Inter-system Interference
	for (int i = 0; i < numBS; i++)
	{
		this->InterferenceTimeFromBsForCQI[i] = 0;
		this->InterferenceTimeFromBsForFER[i] = 0;
		this->AvgInterferenceFromBsForFER[i] = 0;
	}
	for (int i = 0; i < numMS; i++)
	{
		this->InterferenceTimeFromUeForCQI[i] = 0;
		this->InterferenceTimeFromUeForFER[i] = 0;
	}
	
	// Resource Allocation & MCS Decision
	for (int i = 0; i < RB_PER_SUBBAND; i++)
	{
		this->AllocatedRB[i] = 0;
	}
	this->TotalNumOfAllocatedRB = 0;
	this->PfAverageR = 0.0;
	this->InstantR = 0.0;
	this->TempMCSindex = 0;
	this->TempSpectralEfficiency = 0.0;
	this->ModulationOrderDL = 0;

	// SINR (Pre, Post)
	for (int i = 0; i < numSubband; i++)
	{

		this->Transmission_on[i] = 0;

		for (int j = 0; j < CQI_MISMATCH_DELAY; j++)
		{
			for (int m = 0; m < RB_PER_SUBBAND; m++)
			{
				this->PreSINR[i][j][m] = 0.0;
			}
		}
	}/*
	for (int i = 0; i < RB_PER_SUBBAND; i++)
	{
		this->FerSINR[i] = 0.0;
	}*/
	for (int i = 0; i < 3; i++)
	{
		this->AvgSinrEESM[i] = 0.0;
		for (int j = 0; j < RB_PER_SUBBAND; j++)
		{
			this->SinrOfRbEESM[i][j] = 0.0;
		}
	}
	this->EffectiveSINR = 0.0;
	
	// HARQ
	this->HarqProcessID = 0;
	for (int i = 0; i < HARQ_PROCESS_NUM; i++)
	{
		this->HarqReTxNum[i] = 0;
		this->HarqMCSindex[i] = 0;
		this->HarqSpectralEfficiency[i] = 0.0;
		for (int j = 0; j < RB_PER_SUBBAND; j++)
		{
			this->HarqSINR[i][j] = 0.0;
		}
		this->HarqEffectiveSINR[i] = 0.0;
	}

	// 기타
	this->RealRxMode = 0;
	
}
//
///*-------------------------------------------------------------------------*/
///*                                                                         */
///*                         METHOD                                          */
///*                                                                         */
///*-------------------------------------------------------------------------*/
//
//double SchedulingMS::GetSpectralEfficiency(double SINR, int &MCS)
//{   
//
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
//
//}
//
//void SchedulingMS::Feedback(int msID, int type)
//{
//	// 시간 고려
//	int sbs = MS[msID]->network->attachedBS;
//
//	// BS -> UE
//	for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
//	{
//		MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] = 0;
//		if (BS[sbs]->scheduling->InterferenceTimeFromBsForCQI[ibs] > 0)
//		{
//			MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] = double(BS[sbs]->scheduling->InterferenceTimeFromBsForCQI[ibs]) / double(Sim.TTIValue);
//		}
//
//	}
//
//	int oi[57];
//
//	for (int i = 0; i < 57; i++) {
//		oi[i] = MS[msID]->channel->assIndex[i];
//	}
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
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex).t()*MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex) / double(Sim.channel->NumberOfReceiveAntennaPort);
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
//		analogCodebook = PrecodingMatrix(Analogbeamforming, analogCodebook, type);
//		digitalCodebook = PrecodingMatrix(Digitalbeamforming, digitalCodebook, type);
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
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex)*MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
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
//	for (int RBindex = 0; RBindex < 50; RBindex++) {
//		MS[msID]->scheduling->PreSINR[0][0][RBindex] = FrequencySinr(RBindex);		
//	}
//	MS[msID]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (50)) - 1;
//	MS[msID]->scheduling->downlinkESINRdB = 10.0 * log10(MS[msID]->scheduling->downlinkESINR);
//	MS[msID]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->downlinkESINRdB, MS[msID]->scheduling->MCS);
//}
//
//void SchedulingMS::MuMimoFeedback(int msID, int type)
//{
//	
//	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth;
//	arma::cx_mat tempRI, tempRH, tempRHr, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
//	arma::vec FrequencySinr(50), temps;
//	arma::cx_mat *analogCodebook, *digitalCodebook;
//	if (type == 0)
//	{
//		for (int RBindex = 0; RBindex < ( 50); RBindex++)
//		{
//			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//			tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//			tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
//
//			for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//			{
//				tempRHr = tempRHr + MS[msID]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
//				tempRH = tempRH + (MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
//			}
//
//			arma::svd(tempU, temps, tempV, tempRH, "std");
//			for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//			{
//				tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//				for (int si = 1; si < SLS_MAX_BS; si++)
//				{
//					tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
//				}
//				tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
//				tempIRC = tempM.t()*(tempM*tempM.t() + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//				temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
//				signal = temph*temph.t();
//				interferencePlusNoise = tempIRC*(noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
//				FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
//			}
//		}
//	}
//	else
//	{
//		analogCodebook = new arma::cx_mat[16];
//		digitalCodebook = new arma::cx_mat[16];
//		analogCodebook = PrecodingMatrix(Analogbeamforming, analogCodebook, type);
//		digitalCodebook = PrecodingMatrix(Digitalbeamforming, digitalCodebook, type);
//		double temp = 0; double maxtemp = 0;
//		for (int analogbeam = 0; analogbeam < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2; analogbeam++)
//		{
//			for (int digitalbeam = 0; digitalbeam < Sim.channel->NumberOfTransmitAntennaPort * 2; digitalbeam++)
//			{
//				for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
//				{
//					tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex) * analogCodebook[analogbeam] * digitalCodebook[digitalbeam];
//					tempIRC = tempM.t()*(tempM*tempM.t() + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//					temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
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
//			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*MS[msID]->scheduling->analogPrecodingMatrix*MS[msID]->scheduling->digitalPrecodingMatrix;
//			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
//			signal = temph*temph.t();
//			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
//			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
//		}
//	}
//	
//	if (BS[MS[msID]->channel->associatedBsIndex]->scheduling->framestructure(Sim.TTI % Sim.numTTIperFrame) == 0)
//	{
//		MS[msID]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (50)) - 1;
//		MS[msID]->scheduling->downlinkESINRdB = 10.0 * log10(MS[msID]->scheduling->downlinkESINR);
//		MS[msID]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->downlinkESINRdB, MS[msID]->scheduling->MCS);
//	} 
//	else
//	{
//		MS[msID]->scheduling->uplinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (50)) - 1;
//		MS[msID]->scheduling->uplinkESINRdB = 10.0 * log10(MS[msID]->scheduling->uplinkESINR);
//		MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->uplinkESINRdB, MS[msID]->scheduling->MCS);
//	}
//		
//}
//
//void SchedulingMS::ReceivedSINR(int msID, int slotnumber, int type)
//{
//	
//	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth;
//	arma::cx_mat tempRI, tempRH, tempRHr, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
//	arma::vec FrequencySinr(50), temps;
//	double temp = 0; double maxtemp = 0;
//	if (type == 0);
//	else
//	{
//		for (int RBindex = 0; RBindex < (50); RBindex++)
//		{
//			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex) * MS[msID]->scheduling->analogPrecodingMatrix * MS[msID]->scheduling->digitalPrecodingMatrix;
//			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
//			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
//			temp = temp + trace(real(temph*temph.t()));
//		}
//
//		for (int RBindex = 0; RBindex < (50); RBindex++)
//		{
//			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
//			for (int si = 1; si < SLS_MAX_BS; si++)
//			{
//				//			rma::cx_mat precodingMatrix; precodingMatrix.zeros(Sim.channel->NumberOfRxAntenna, BS[si]->scheduling->scheduledMS);
//				//			precodingMatrix = MS[BS[si]->scheduling->scheduledMS(slotnumber)]->scheduling->analogPrecodingMatrix * MS[BS[si]->scheduling->scheduledMS(slotnumber)]->scheduling->digitalPrecodingMatrix;
//
//				//			tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, link, RBindex)*precodingMatrix*precodingMatrix.t()*MS[msID]->channel->FrequencyChannel(si, link, RBindex).t();
//
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
//	if (BS[MS[msID]->channel->associatedBsIndex]->scheduling->framestructure(Sim.TTI % Sim.numTTIperFrame) == 0)
//	{
//		if (MS[msID]->scheduling->downlinkESINRdB < 0)
//		{
//			MS[msID]->scheduling->downlinkESINRdB = MS[msID]->scheduling->downlinkESINRdB + HARQvalue;
//			MS[msID]->scheduling->downlinkESINR = pow(10.0, MS[msID]->scheduling->downlinkESINRdB) / (10.0);
//			MS[msID]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->downlinkESINRdB, MS[msID]->scheduling->MCS);
//		}		
//	}
//	else
//	{
//		if (MS[msID]->scheduling->uplinkESINRdB < 0)
//		{
//			MS[msID]->scheduling->uplinkESINRdB = MS[msID]->scheduling->uplinkESINRdB + HARQvalue;
//			MS[msID]->scheduling->uplinkESINR = pow(10.0, MS[msID]->scheduling->uplinkESINRdB) / (10.0);
//			MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->uplinkESINRdB, MS[msID]->scheduling->MCS);
//		}
//	}
//}
//
//arma::cx_mat* SchedulingMS::PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type)
//{
//	codebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort * 2];
//	arma::cx_mat tempanalogCodebook;
//	//tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
//	int index_t1, index_t2;
//	std::complex <double> *phase_a = new std::complex <double>[2];
//	std::complex <double> phase;
//	if (type == 0);
//	else
//	{
//		switch (precodingtype)
//		{
//		case Analogbeamforming:
//			//codebook = new arma::cx_mat[Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2];
//			tempanalogCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);
//
//			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
//			{
//				for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
//				{
//					phase.real(0.0);
//					phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
//					tempanalogCodebook(j, i) = exp(phase);
//				}
//			}
//			index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;
//			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
//			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
//			{
//				for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort; j++)
//				{
//					if (i % 2 == 0)
//					{
//						codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//						codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
//						index_t1 = index_t1 + 1;
//					}
//					else
//					{
//						codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//						codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
//						index_t2 = index_t2 + 1;
//					}
//				}
//			}
//			//arma::cx_mat tempanalogCodebook;
//			/*tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
//
//			for (int i = 0; i < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; i++)
//			{
//			for (int j = 0; j < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2; j++)
//			{
//			phase.real(0.0);
//			phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna));
//			tempanalogCodebook(j, i) = exp(phase);
//			}
//			}
//			index_t1 = 0; index_t2 = Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna;
//			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
//			for (int i = 0; i < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; i++)
//			{
//			for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort; j++)
//			{
//			if (i % 2 == 0)
//			{
//			codebook[index_t1].zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, 1);
//			codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
//			codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
//			codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
//			index_t1 = index_t1 + 1;
//			}
//			else
//			{
//			codebook[index_t2].zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, 1);
//			codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
//			codebook[index_t2].submat(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
//			codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
//			index_t2 = index_t2 + 1;
//			}
//			}
//			}*/
//			return codebook;
//			break;
//
//		case Digitalbeamforming:
//			arma::cx_mat tempdigitalCodebook;
//			tempdigitalCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);
//
//			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
//			{
//				for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
//				{
//					phase.real(0.0);
//					phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
//					tempdigitalCodebook(j, i) = exp(phase);
//				}
//			}
//			index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;
//			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
//			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
//			{
//				for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort; j++)
//				{
//					if (i % 2 == 0)
//					{
//						codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//						codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
//						index_t1 = index_t1 + 1;
//					}
//					else
//					{
//						codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
//						codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
//						codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
//						index_t2 = index_t2 + 1;
//					}
//				}
//			}
//			return codebook;
//			break;
//		}
//	}	
//	
//}
//
//void SchedulingMS::SinrCalculationForCqiReport(int msID, int type)
//{
//	// 시간 고려
//	int sbs = MS[msID]->network->attachedBS;
//
//	// BS -> UE
//	for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
//	{
//		MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] = 0;
//		if (BS[sbs]->scheduling->InterferenceTimeFromBsForCQI[ibs] > 0)
//		{
//			MS[msID]->scheduling->AvgInterferenceFromBsForCQI[ibs] = double(BS[sbs]->scheduling->InterferenceTimeFromBsForCQI[ibs]) / double(Sim.TTIValue);
//		}
//
//	}
//
//	int oi[57];
//
//	for (int i = 0; i < 57; i++) {
//		oi[i] = MS[msID]->channel->assIndex[i];
//	}
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
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex).t()*MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex) / double(Sim.channel->NumberOfReceiveAntennaPort);
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
//		analogCodebook = PrecodingMatrix(Analogbeamforming, analogCodebook, type);
//		digitalCodebook = PrecodingMatrix(Digitalbeamforming, digitalCodebook, type);
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
//				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex)*MS[msID]->channel->FrequencyChannel(oi[si], 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
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
//	for (int RBindex = 0; RBindex < 50; RBindex++) {
//		MS[msID]->scheduling->PreSINR[0][0][RBindex] = FrequencySinr(RBindex);
//	}
//}
//
//void SchedulingMS::ConcludeIteration()
//{
//
//}
//
//void SchedulingMS::Conclude()
//{
//
//}
