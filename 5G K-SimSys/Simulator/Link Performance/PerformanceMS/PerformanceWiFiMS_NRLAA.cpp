/****************************************************************************

Performance for Base Station(FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Performance_NReMBB.cpp
DATE         : 2017.3.1
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, Alln Rights Reserved

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

#include "PerformanceMS_NRLAA.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void PerformanceWiFiMS::Initialize(int ms)
{
	id = ms; // MS ID
	downlinkThroghput = 0;
	uplinkThroghput = 0;
}



//void PerformanceMS::Measure()
//{
//
//}
//
//void PerformanceMS::ISIPcalculationForFerCheck(int msID, int type)
//{
//	int sbs = MS[msID]->network->attachedBS;
//
//	// BS -> UE
//	for (int ibs = 0; ibs < Sim.network->numBS; ibs++)
//	{
//		MS[msID]->scheduling->AvgInterferenceFromBsForFER[ibs] = 0;
//		if (BS[sbs]->scheduling->InterferenceTimeFromBsForFER[ibs] > 0)
//		{
//			MS[msID]->scheduling->AvgInterferenceFromBsForFER[ibs] = double(BS[sbs]->scheduling->InterferenceTimeFromBsForFER[ibs]) / double(Sim.TTIValue);
//		}
//	}
//	// UE -> UE
//
//	// AP -> UE
//
//	// STA -> UE
//}
//
//void PerformanceMS::SINRCalculationForFerCheck(int msID, int type)
//{
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
//		MS[msID]->scheduling->FerSINR[RBindex] = FrequencySinr(RBindex);
//	}
//
//}
//
//arma::cx_mat* PerformanceMS::PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type)
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
//void PerformanceMS::ConcludeIteration() {
//
//}
//
//
//
//void PerformanceMS::Conclude() {
//
//}
