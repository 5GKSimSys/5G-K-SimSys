/****************************************************************************

Scheduling (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NRmMTC.cpp
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

#include "SchedulingMS_NRmMTC.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SchedulingMS::Initialize(int ms)
{
	id = ms; // MS ID
	//averagedThroghput = 0.0001;
	if (Sim.scheduling->trafficModel == RRM::NonFullBuffer)
	{
		double dataSize = Sim.scheduling->dataSize;
	}	
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void SchedulingMS::PreambleSelection()
{
	preambleNum = arma::randu() * Sim.scheduling->numPreamble; // uniformly distribution
}

double SchedulingMS::GetSpectralEfficiency(double SINR, int &MCS)
{   

	if (SINR < -7.595) { MCS = -1; return 0.0; }
	else if (SINR >= -7.595&&SINR < -5.712) { MCS = 0; return  0.1523; }
	else if (SINR >= -5.712&&SINR < -3.591) { MCS = 1; return 0.2344; }
	else if (SINR >= -3.591&&SINR < -1.578) { MCS = 2; return 0.3770; }
	else if (SINR >= -1.578&&SINR < 0.4483) { MCS = 3; return 0.6016; }
	else if (SINR >= 0.4483&&SINR < 2.345) { MCS = 4; return 0.8770; }
	else if (SINR >= 2.345&&SINR < 4.312) { MCS = 5; return 1.1758; }
	else if (SINR >= 4.312&&SINR < 6.264) { MCS = 6; return 1.4766; }
	else if (SINR >= 6.264&&SINR < 8.248) { MCS = 7; return 1.9141; }
	else if (SINR >= 8.248&&SINR < 10.24) { MCS = 8; return 2.4063; }
	else if (SINR >= 10.24&&SINR < 12.05) { MCS = 9; return 2.7305; }
	else if (SINR >= 12.05&&SINR < 13.93) { MCS = 10; return 3.3223; }
	else if (SINR >= 13.93&&SINR < 16.02) { MCS = 11; return 3.9023; }
	else if (SINR >= 16.02&&SINR < 17.83) { MCS = 12; return 4.5234; }
	else if (SINR >= 17.83&&SINR < 20.06) { MCS = 13; return 5.1152; }
	else if (SINR >= 20.06) { MCS = 14; return 5.5547; }
	return -1.0;

}

void SchedulingMS::Feedback()
{	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NRmMTC.bandwidth * 1e6 / 1000;
	arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NRmMTC.bandwidth / 10 * 50), temps;

	tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
	MS[id]->channel->ShortTermChannel(id);
	for (int RBindex = 0; RBindex <  (Sim.channel->NRmMTC.bandwidth / 10 * 50); RBindex++)
	{
		tempRHr = tempRHr + MS[id]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[id]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NRmMTC.bandwidth / 10 * 50);
		tempRH = tempRH + (MS[id]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[id]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NRmMTC.bandwidth / 10 * 50);
	}
	
	arma::svd(tempU, temps, tempV, tempRH, "std");
	for (int RBindex = 0; RBindex < (Sim.channel->NRmMTC.bandwidth / 10 * 50); RBindex++)
	{
		tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
		for (int si = 1; si < SLS_MAX_BS; si++)
		{
			tempRI = tempRI + MS[id]->channel->FrequencyChannel(si, 0, RBindex)*MS[id]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
		}
		tempM = MS[id]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
		temph = tempIRC*MS[id]->channel->FrequencyChannel(0, 0, RBindex); 
		signal = temph*temph.t();
		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
	}

	MS[id]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / 50) - 1 + MS[id]->scheduling->HARQeSINR;
	MS[id]->scheduling->downlinkESINRdB = 10.0 * log10(MS[id]->scheduling->downlinkESINR);
	MS[id]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[id]->scheduling->downlinkESINRdB, MS[id]->scheduling->MCS);
	
}

void SchedulingMS::ReceivedSINR()
{
	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NRmMTC.bandwidth * 1e6 / 1000;
	arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NRmMTC.bandwidth / 10 * 50), temps;

	tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
	tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
	MS[id]->channel->ShortTermChannel(id);
	for (int RBindex = 0; RBindex < (Sim.channel->NRmMTC.bandwidth / 10 * 50); RBindex++)
	{
		tempRHr = tempRHr + MS[id]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[id]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NRmMTC.bandwidth / 10 * 50);
		tempRH = tempRH + (MS[id]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[id]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NRmMTC.bandwidth / 10 * 50);
	}

	arma::svd(tempU, temps, tempV, tempRH, "std");
	for (int RBindex = 0; RBindex < (Sim.channel->NRmMTC.bandwidth / 10 * 50); RBindex++)
	{
		tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
		for (int si = 1; si < SLS_MAX_BS; si++)
		{
			tempRI = tempRI + MS[id]->channel->FrequencyChannel(si, 0, RBindex)*MS[id]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
		}
		tempM = MS[id]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
		tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
		temph = tempIRC*MS[id]->channel->FrequencyChannel(0, 0, RBindex);
		signal = temph*temph.t();
		interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
		FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
	}

	MS[id]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / 50) - 1 + MS[id]->scheduling->HARQeSINR;
	MS[id]->scheduling->downlinkESINRdB = 10.0 * log10(MS[id]->scheduling->downlinkESINR);
}

arma::cx_mat* SchedulingMS::PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type)
{
	codebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort * 2];
	arma::cx_mat tempanalogCodebook;
	//tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
	int index_t1, index_t2;
	std::complex <double> *phase_a = new std::complex <double>[2];
	std::complex <double> phase;
	if (type == 0);
	else
	{
		switch (precodingtype)
		{
		case Analogbeamforming:
			//codebook = new arma::cx_mat[Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2];
			tempanalogCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);

			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
				{
					phase.real(0.0);
					phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
					tempanalogCodebook(j, i) = exp(phase);
				}
			}
			index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;
			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort; j++)
				{
					if (i % 2 == 0)
					{
						codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t1 = index_t1 + 1;
					}
					else
					{
						codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t2 = index_t2 + 1;
					}
				}
			}
			//arma::cx_mat tempanalogCodebook;
			/*tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);

			for (int i = 0; i < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; i++)
			{
			for (int j = 0; j < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2; j++)
			{
			phase.real(0.0);
			phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna));
			tempanalogCodebook(j, i) = exp(phase);
			}
			}
			index_t1 = 0; index_t2 = Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna;
			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
			for (int i = 0; i < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna; i++)
			{
			for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort; j++)
			{
			if (i % 2 == 0)
			{
			codebook[index_t1].zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, 1);
			codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
			index_t1 = index_t1 + 1;
			}
			else
			{
			codebook[index_t2].zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna, 1);
			codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, 0) = tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t2].submat(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, 0, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna - 1, 0) = phase_a[j] * tempanalogCodebook.submat(0, i, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2 - 1, i);
			codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
			index_t2 = index_t2 + 1;
			}
			}
			}*/
			return codebook;
			break;

		case Digitalbeamforming:
			arma::cx_mat tempdigitalCodebook;
			tempdigitalCodebook.zeros(Sim.channel->NumberOfTransmitAntennaPort / 2, Sim.channel->NumberOfTransmitAntennaPort);

			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfTransmitAntennaPort / 2; j++)
				{
					phase.real(0.0);
					phase.imag(2 * PI*j*i / double(Sim.channel->NumberOfTransmitAntennaPort));
					tempdigitalCodebook(j, i) = exp(phase);
				}
			}
			index_t1 = 0; index_t2 = Sim.channel->NumberOfTransmitAntennaPort;
			phase_a[0].real(1.0); phase_a[0].imag(0.0); phase_a[1].real(-1.0); phase_a[1].imag(0.0);
			for (int i = 0; i < Sim.channel->NumberOfTransmitAntennaPort; i++)
			{
				for (int j = 0; j < Sim.channel->NumberOfReceiveAntennaPort; j++)
				{
					if (i % 2 == 0)
					{
						codebook[index_t1].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t1].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t1] = codebook[index_t1] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t1 = index_t1 + 1;
					}
					else
					{
						codebook[index_t2].zeros(Sim.channel->NumberOfTransmitAntennaPort, 1);
						codebook[index_t2].submat(0, 0, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, 0) = tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2].submat(Sim.channel->NumberOfTransmitAntennaPort / 2, 0, Sim.channel->NumberOfTransmitAntennaPort - 1, 0) = phase_a[j] * tempdigitalCodebook.submat(0, i, Sim.channel->NumberOfTransmitAntennaPort / 2 - 1, i);
						codebook[index_t2] = codebook[index_t2] / sqrt(Sim.channel->NumberOfTransmitAntennaPort);
						index_t2 = index_t2 + 1;
					}
				}
			}
			return codebook;
			break;
		}
	}	
	
}

void SchedulingMS::ConcludeIteration()
{

}

void SchedulingMS::Conclude()
{

}
