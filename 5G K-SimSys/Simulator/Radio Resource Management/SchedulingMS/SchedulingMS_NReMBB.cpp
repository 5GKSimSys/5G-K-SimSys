/****************************************************************************

Scheduling (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NReMBB.cpp
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

#include "SchedulingMS_NReMBB.h"


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
		dataSize = Sim.scheduling->dataSize;
		interArrivalTime = ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5); // first traffic generation TTI for non-full-buffer MS
		msBuffer = 0; // buffer initialization
	}
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void SchedulingMS::BufferUpdate()
{
	if ((Sim.TTI == interArrivalTime))
	{
		msBuffer = msBuffer + dataSize;
		interArrivalTime = Sim.TTI + ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5);
	}
}


double SchedulingMS::GetSpectralEfficiency(double SINR, int &MCS)
{   

	if (SINR < -7.8474) { MCS = -1; return 0.0; }
	else if (SINR >= -7.8474&&SINR < -6.2369) { MCS = 0; return  0.1523; }
	else if (SINR >= -6.2369&&SINR < -4.3591) { MCS = 1; return 0.2344; }
	else if (SINR >= -4.3591&&SINR < -1.9319) { MCS = 2; return 0.3770; }
	else if (SINR >= -1.9319&&SINR < 0.1509) { MCS = 3; return 0.6016; }
	else if (SINR >= 0.1509&&SINR < 1.9976) { MCS = 4; return 0.8770; }
	else if (SINR >= 1.9976&&SINR < 4.7278) { MCS = 5; return 1.1758; }
	else if (SINR >= 4.7278&&SINR < 6.2231) { MCS = 6; return 1.4766; }
	else if (SINR >= 6.2231&&SINR < 8.0591) { MCS = 7; return 1.9141; }
	else if (SINR >= 8.0591&&SINR < 9.8585) { MCS = 8; return 2.4063; }
	else if (SINR >= 9.8585&&SINR < 11.8432) { MCS = 9; return 2.7305; }
	else if (SINR >= 11.8432&&SINR < 13.4893) { MCS = 10; return 3.3223; }
	else if (SINR >= 13.4893&&SINR < 15.3598) { MCS = 11; return 3.9023; }
	else if (SINR >= 15.3598&&SINR < 17.4435) { MCS = 12; return 4.5234; }
	else if (SINR >= 17.4435&&SINR < 19.2155) { MCS = 13; return 5.1152; }
	else if (SINR >= 19.2155) { MCS = 14; return 5.5547; }
	return -1.0;

}

void SchedulingMS::Feedback(int msID)
{
	
	//double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth * 1e6 / 1000;
	//arma::cx_mat tempRI, tempRHr, tempRH, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	//arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;

	//tempRI.zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna);
	//tempRHr.zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna);
	//tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);

	//for (int RBindex = 0; RBindex <  (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
	//{
	//	tempRHr = tempRHr + MS[msID]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
	//	tempRH = tempRH + (MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
	//}
	//
	//arma::svd(tempU, temps, tempV, tempRH, "std");
	//for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
	//{
	//	tempRI.zeros(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna);
	//	for (int si = 1; si < SLS_MAX_BS; si++)
	//	{
	//		tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
	//	}
	//	tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
	//	tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna)).i();
	//	temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex); 
	//	signal = temph*temph.t();
	//	interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfRxAntenna, Sim.channel->NumberOfRxAntenna))*tempIRC.t();
	//	FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
	//}

	//MS[msID]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / 50) - 1;
	//MS[msID]->scheduling->downlinkESINRdB = 10.0 * log10(MS[msID]->scheduling->downlinkESINR);
	//MS[msID]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->downlinkESINRdB, MS[msID]->scheduling->MCS);
	////MS[msID]->scheduling->PrecodingMatrix = tempV.col(0);
	
}

void SchedulingMS::MuMimoFeedback(int msID, int type)
{
	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth;
	arma::cx_mat tempRI, tempRH, tempRHr, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;
	arma::cx_mat *analogCodebook, *digitalCodebook;
	if (type == 0)
	{
		for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
		{
			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
			MS[id]->channel->ShortTermChannel(id);
			for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
			{
				tempRHr = tempRHr + MS[msID]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
				tempRH = tempRH + (MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
			}

			arma::svd(tempU, temps, tempV, tempRH, "std");
			MS[msID]->scheduling->digitalPrecodingMatrix = tempV.col(0);
			for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
			{
				tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
				for (int si = 1; si < Sim.network->numBS; si++)
				{
					tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
				}
				tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
				tempIRC = tempM.t()*(tempM*tempM.t() + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort) + arma::randu()*0.1).i();
				temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
				signal = temph*temph.t();
				interferencePlusNoise = tempIRC*(noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
				FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
			}
		}
	}
	else
	{
		analogCodebook = new arma::cx_mat[Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2, Sim.channel->NumberOfTransmitAntennaPort];
		digitalCodebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort, 1];

		analogCodebook = Beamforming(Analogbeamforming, analogCodebook, 0);
		digitalCodebook = Beamforming(Digitalbeamforming, digitalCodebook, 0);
		MS[id]->channel->ShortTermChannel(id);
		double temp = 0; double maxtemp = 0;
		for (int analogbeam = 0; analogbeam < Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna * 2; analogbeam++)
		{
			for (int digitalbeam = 0; digitalbeam < Sim.channel->NumberOfTransmitAntennaPort * 2; digitalbeam++)
			{
				for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
				{
					tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex) * analogCodebook[analogbeam] * digitalCodebook[digitalbeam];
					tempIRC = tempM.t()*(tempM*tempM.t() + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
					temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
					temp = temp + trace(real(temph*temph.t()));
				}
				if (maxtemp < temp) maxtemp = temp;
				MS[msID]->scheduling->analogPrecodingMatrix = analogCodebook[analogbeam];
				MS[msID]->scheduling->digitalPrecodingMatrix = digitalCodebook[digitalbeam];
			}
		}

		for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
		{
			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			for (int si = 1; si < Sim.network->numBS; si++)
			{
				tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t() / double(Sim.channel->NumberOfTransmitAntennaPort);
			}
			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*MS[msID]->scheduling->analogPrecodingMatrix*MS[msID]->scheduling->digitalPrecodingMatrix;
			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort) + arma::randu()*0.1).i();
			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex);
			signal = temph*temph.t();
			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
		}
	}
	
	if (BS[MS[msID]->channel->associatedBsIndex]->scheduling->framestructure(Sim.TTI % Sim.numTTIperFrame) == 0)
	{
		MS[msID]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1 + MS[id]->scheduling->downlinkHARQeSINR;
		MS[msID]->scheduling->downlinkESINRdB = 10.0 * log10(MS[msID]->scheduling->downlinkESINR);
		MS[msID]->scheduling->downlinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->downlinkESINRdB, MS[msID]->scheduling->MCS);
	} 
	else
	{
		MS[msID]->scheduling->uplinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1 + MS[id]->scheduling->uplinkHARQeSINR;
		MS[msID]->scheduling->uplinkESINRdB = 10.0 * log10(MS[msID]->scheduling->uplinkESINR);
		MS[msID]->scheduling->uplinkspectralEfficiency = GetSpectralEfficiency(MS[msID]->scheduling->uplinkESINRdB, MS[msID]->scheduling->MCS);
	}
		
}

void SchedulingMS::ReceivedSINR(int msID, int slotnumber, int type)
{
	
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth;
	arma::cx_mat tempRI, tempRH, tempRHr, tempU, tempV, tempM, temph, tempIRC, signal, interferencePlusNoise;
	arma::vec FrequencySinr(50), temps;
	double temp = 0; double maxtemp = 0;
	if (type == 0)
	{
		for (int RBindex = 0; RBindex < (50); RBindex++)
		{
			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			tempRHr.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			tempRH.zeros(Sim.channel->NumberOfTransmitAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);
			MS[id]->channel->ShortTermChannel(id);
			for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
			{
				tempRHr = tempRHr + MS[msID]->channel->FrequencyChannel(0, 0, RBindex)	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
				tempRH = tempRH + (MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t())	*	(MS[msID]->channel->FrequencyChannel(0, 0, RBindex)) / (Sim.channel->NReMBB.bandwidth / 10 * 50);
			}

			arma::svd(tempU, temps, tempV, tempRH, "std");
			for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
			{
				tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
				tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
				for (int si = 0; si < SLS_MAX_BS; si++)
				{
					arma::cx_mat precodingMatrix; //precodingMatrix.zeros(Sim.channel->NumberOfReceiveAntennaPort, BS[si]->scheduling->scheduledMS);
					if (BS[si]->scheduling->numScheduledMS != 0 && si != MS[msID]->network->attachedBS)
					{
						for (int inteferenceUE = 0; inteferenceUE<BS[si]->scheduling->numScheduledMS; inteferenceUE++)
						precodingMatrix = MS[BS[si]->scheduling->scheduledMS(inteferenceUE)]->scheduling->digitalPrecodingMatrix;
						tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*precodingMatrix*precodingMatrix.t()*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t();
					}

				}
				tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex)*tempV.col(0);
				tempIRC = tempM.t()*(tempM*tempM.t() + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort));
				temph = tempIRC*tempM;
				signal = temph*temph.t();
				interferencePlusNoise = tempIRC*(noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
				FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
			}
		}
	}
	else
	{
		MS[id]->channel->ShortTermChannel(id);
		for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
		{
			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex) * MS[msID]->scheduling->analogPrecodingMatrix * MS[msID]->scheduling->digitalPrecodingMatrix;
			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
			temp = temp + trace(real(temph*temph.t()));
		}

		for (int RBindex = 0; RBindex < (Sim.channel->NReMBB.bandwidth / 10 * 50); RBindex++)
		{
			tempRI.zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort);
			for (int si = 1; si < Sim.network->numBS; si++)
			{
					arma::cx_mat precodingMatrix; precodingMatrix.zeros(Sim.channel->NumberOfReceiveAntennaPort, BS[si]->scheduling->numScheduledMS);
					precodingMatrix = MS[BS[si]->scheduling->scheduledMS(slotnumber)]->scheduling->analogPrecodingMatrix * MS[BS[si]->scheduling->scheduledMS(slotnumber)]->scheduling->digitalPrecodingMatrix;

					tempRI = tempRI + MS[msID]->channel->FrequencyChannel(si, 0, RBindex)*precodingMatrix*precodingMatrix.t()*MS[msID]->channel->FrequencyChannel(si, 0, RBindex).t();

			}
			tempM = MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t()*MS[msID]->scheduling->analogPrecodingMatrix*MS[msID]->scheduling->digitalPrecodingMatrix;
			tempIRC = tempM.t()*(tempM*tempM.t() + tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort)).i();
			temph = tempIRC*MS[msID]->channel->FrequencyChannel(0, 0, RBindex).t();
			signal = temph*temph.t();
			interferencePlusNoise = tempIRC*(tempRI + noise*arma::eye(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfReceiveAntennaPort))*tempIRC.t();
			FrequencySinr(RBindex) = real(signal(0, 0)) / real(interferencePlusNoise(0, 0));
		}
	}

	if (BS[MS[msID]->channel->associatedBsIndex]->scheduling->framestructure(Sim.TTI % Sim.numTTIperFrame) == 0)
	{
		MS[msID]->scheduling->downlinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1 + MS[id]->scheduling->downlinkHARQeSINR;
		MS[msID]->scheduling->downlinkESINRdB = 10.0 * log10(MS[msID]->scheduling->downlinkESINR);
	}
	else
	{
		MS[msID]->scheduling->uplinkESINR = pow(2, sum(log2(1.0 + FrequencySinr)) / (Sim.channel->NReMBB.bandwidth / 10 * 50)) - 1 + MS[id]->scheduling->uplinkHARQeSINR;
		MS[msID]->scheduling->uplinkESINRdB = 10.0 * log10(MS[msID]->scheduling->uplinkESINR);
	}
}

arma::cx_mat* SchedulingMS::Beamforming(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type)
{
	codebook = new arma::cx_mat[Sim.channel->NumberOfTransmitAntennaPort * 2];
	arma::cx_mat tempanalogCodebook;
	//tempanalogCodebook.zeros(Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna / 2, Sim.channel->NumberOfTxHorizontalAntenna * Sim.channel->numberOfTxVerticalAntenna);
	int index_t1, index_t2;
	std::complex <double> *phase_a = new std::complex <double>[4];
	std::complex <double> *phase_b = new std::complex <double>[4];
	std::complex <double> phase;
	if (type == 0) // Type I Single Panel
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
			phase_a[2].real(0.0); phase_a[0].imag(1.0); phase_a[1].real(0.0); phase_a[1].imag(-1.0);
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

	else if (type == 1) // Type I Multi Panel
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
			phase_a[2].real(0.0); phase_a[0].imag(1.0); phase_a[1].real(0.0); phase_a[1].imag(-1.0);
			phase_b[0].real(1.0); phase_b[0].imag(0.0); phase_b[1].real(-1.0); phase_b[1].imag(0.0);
			phase_b[2].real(0.0); phase_b[0].imag(1.0); phase_b[1].real(0.0); phase_b[1].imag(-1.0);

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
	else if (type == 2) // Type II 
	{

	}
	else // Type II Port selection
	{

	}
}

void SchedulingMS::ConcludeIteration()
{

}

void SchedulingMS::Conclude()
{

}
