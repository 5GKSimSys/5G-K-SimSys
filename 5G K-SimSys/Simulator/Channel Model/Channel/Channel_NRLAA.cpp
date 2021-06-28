/****************************************************************************

Channel Model (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Channel_NReMBB.cpp
DATE         : 2017.1.27
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.01.27	Minsig Han      	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "Channel_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Channel::Initialize(string fileName)
{
	// Read channel model parameters from the file
	ifstream inFile("../../Simulator/Data/Input Data/SimulationParameter/SystemSimParameter/SimParamChannel_" + fileName + ".txt");
	char inputString[100];
	string* result;

	if (inFile.is_open())
	{
		while (!inFile.eof()) {
			inFile.getline(inputString, 100);
			result = strSplit(inputString, "	");
			if (result[0] == "carrierFrequency") NReMBB.carrierFrequency = stod(result[1]);
			else if (result[0] == "bandwidth") NReMBB.bandwidth = stod(result[1]);
			else if (result[0] == "txPower") NReMBB.txPower = stod(result[1]);
			else if (result[0] == "rxPower") NReMBB.rxPower = stod(result[1]);
			else if (result[0] == "noiseFigure") NReMBB.noiseFigure = stod(result[1]);
			else if (result[0] == "channelModel") ChannelModel = SLS::Scenario(stoi(result[1]));
			else if (result[0] == "numberOfChannelProcess") NumberOfChannelProcess = (stoi(result[1])); // for beamformed CSI-RS

			else if (result[0] == "numberOfTxVerticalAntenna") numberOfTxVerticalAntenna = (stoi(result[1])); // M
			else if (result[0] == "numberOfTxHorizontalAntenna") NumberOfTxHorizontalAntenna = (stoi(result[1])); // N
			else if (result[0] == "bsAntennModel") BsAntennaModel = CHANNEL::Antenna_Model(stoi(result[1])); // P
			else if (result[0] == "numberOfTxVerticalPanel") numberOfTxVerticalPanel = (stoi(result[1])); // M_g
			else if (result[0] == "numberOfTxHorizontalPanel") NumberOfTxHorizontalPanel = (stoi(result[1])); // N_g
			else if (result[0] == "numberOfTransmitAntennaPort") NumberOfTransmitAntennaPort = (stoi(result[1]));
			else if (result[0] == "TxVerticalAntennaDistance") TxVerticalAntennaDistance = (stoi(result[1]));
			else if (result[0] == "TxHorizontalAntennaDistance") TxHorizontalAntennaDistance = (stoi(result[1]));
			else if (result[0] == "TxVerticalPanelDistance") TxVerticalPanelDistance = (stoi(result[1]));
			else if (result[0] == "TxHorizontalPanelDistance") TxHorizontalPanelDistance = (stoi(result[1]));

			else if (result[0] == "numberOfRxVerticalAntenna") numberOfRxVerticalAntenna = (stoi(result[1])); // M
			else if (result[0] == "numberOfRxHorizontalAntenna") NumberOfRxHorizontalAntenna = (stoi(result[1])); // N
			else if (result[0] == "msAntennModel") MsAntennaModel = CHANNEL::Antenna_Model(stoi(result[1])); // P
			else if (result[0] == "numberOfRxVerticalPanel") numberOfRxVerticalPanel = (stoi(result[1])); // M_g
			else if (result[0] == "numberOfRxHorizontalPanel") NumberOfRxHorizontalPanel = (stoi(result[1])); // N_g
			else if (result[0] == "numberOfReceiveAntennaPort") NumberOfReceiveAntennaPort = (stoi(result[1]));
			else if (result[0] == "RxVerticalAntennaDistance") RxVerticalAntennaDistance = (stoi(result[1]));
			else if (result[0] == "RxHorizontalAntennaDistance") RxHorizontalAntennaDistance = (stoi(result[1]));
			else if (result[0] == "RxVerticalPanelDistance") RxVerticalPanelDistance = (stoi(result[1]));
			else if (result[0] == "RxHorizontalPanelDistance") RxHorizontalPanelDistance = (stoi(result[1]));
					
			if (Sim.channel->ChannelModel == 1) {
				if (result[0] == "carrierFrequencyOfSmallCell") NReMBB.carrierFrequencyOfSmallCell = stod(result[1]);
				else if (result[0] == "bandwidthOfSmallCell") NReMBB.bandwidthOfSmallCell = stod(result[1]);
				else if (result[0] == "txPowerOfSmallCell") NReMBB.txPowerOfSmallCell = stod(result[1]);
				else if (result[0] == "rxPowerOfSmallCell") NReMBB.rxPowerOfSmallCell = stod(result[1]);
				else if (result[0] == "noiseFigureOfSmallCell") NReMBB.noiseFigureOfSmallCell = stod(result[1]);
				else if (result[0] == "numberOfChannelProcessOfSmallCell") NumberOfChannelProcessOfSmallCell = (stoi(result[1])); // for beamformed CSI-RS

				else if (result[0] == "numberOfTxVerticalAntennaOfSmallCell") numberOfTxVerticalAntennaOfSmallCell = (stoi(result[1])); // M
				else if (result[0] == "numberOfTxHorizontalAntennaOfSmallCell") NumberOfTxHorizontalAntennaOfSmallCell = (stoi(result[1])); // N
				else if (result[0] == "bsAntennModelOfSmallCell") BsAntennaModel = CHANNEL::Antenna_Model(stoi(result[1])); // P
				else if (result[0] == "numberOfTxVerticalPanelOfSmallCell") numberOfTxVerticalPanelOfSmallCell = (stoi(result[1])); // M_g
				else if (result[0] == "numberOfTxHorizontalPanelOfSmallCell") NumberOfTxHorizontalPanelOfSmallCell = (stoi(result[1])); // N_g
				else if (result[0] == "numberOfTransmitAntennaPortOfSmallCell") NumberOfTransmitAntennaPortOfSmallCell = (stoi(result[1]));
				else if (result[0] == "TxVerticalAntennaDistanceOfSmallCell") TxVerticalAntennaDistanceOfSmallCell = (stoi(result[1]));
				else if (result[0] == "TxHorizontalAntennaDistanceOfSmallCell") TxHorizontalAntennaDistanceOfSmallCell = (stoi(result[1]));
				else if (result[0] == "TxVerticalPanelDistanceOfSmallCell") TxVerticalPanelDistanceOfSmallCell = (stoi(result[1]));
				else if (result[0] == "TxHorizontalPanelDistanceOfSmallCell") TxHorizontalPanelDistanceOfSmallCell = (stoi(result[1]));
			}
		}
		WaveLengthOfElectomageneticWave = SpeedOfElectomageneticWave / (NReMBB.carrierFrequency*1e9);	

	}

};

void Channel::LongTermChannel()
{
	
	for (int msID=0; msID<Sim.network->numMS; msID++)
	{
		TemporaryGlobalVariableInitialize(msID);
		MS[msID]->channel->LongTermChannel(msID);

		setcolor(11, 0);
		double longTermChannelProcess;
		longTermChannelProcess = 95 * msID / (Sim.network->numMS);
		cout << "[Channel " << longTermChannelProcess << "%]: Long Term Channel of MS ID " << msID << " Calculated" << endl;
	}	

	for (int bsID = 0; bsID<Sim.network->numBS; bsID++)
	{
		TemporaryGlobalVariableInitializeForBS(bsID);
		BS[bsID]->channel->LongTermChannel(bsID);

		setcolor(11, 0);
		double longTermChannelProcess;
		longTermChannelProcess = 95 * bsID / (Sim.network->numBS);
		cout << "[Channel " << longTermChannelProcess << "%]: Long Term Channel of BS ID " << bsID << " Calculated" << endl;
	}

}

void Channel::ShortTermChannel()
{
	for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->channel->ShortTermChannel(msID);
	}
		setcolor(11, 0);
		cout << "[Channel]: Short Term Channel of MS(DFT) calculated" << endl;
}

void Channel::TemporaryGlobalVariableInitialize(int msID) {
	// Initialize
	MS[msID]->channel->RSRPout.zeros(57, 1);
	MS[msID]->channel->VelocityLOS.zeros(57, 1);
	MS[msID]->channel->Alpha_zero_temp = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	MS[msID]->channel->Alpha_zero_temp_x = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	MS[msID]->channel->Alpha_zero_temp1 = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	MS[msID]->channel->Alpha_zero_temp_x1 = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	MS[msID]->channel->NumRealCluseter.zeros(Sim.network->numBS, 1);
	arma::field<arma::cx_mat> A(Sim.network->numBS, 1);
	MS[msID]->channel->F_urd_LOS = A;
	MS[msID]->channel->F_prd_LOS = A;
	arma::field<arma::cx_mat> B(MAX_CLUSTER, 20);
	MS[msID]->channel->F_urd = B;
	MS[msID]->channel->F_prd = B;
	arma::field<arma::cx_mat> C(Sim.network->numBS, MAX_CLUSTER, 20);
	MS[msID]->channel->F_urd_BS = C;
	MS[msID]->channel->F_prd_BS = C;
	arma::field<arma::cx_mat> D(Sim.network->numBS, Sim.channel->NumberOfChannelProcess);
	MS[msID]->channel->Alpha_nmup_temp = D;
	MS[msID]->channel->Alpha_nmup_temp_x = D;
	MS[msID]->channel->Alpha_nmup_temp1 = D;
	MS[msID]->channel->Alpha_nmup_temp_x1 = D;
	MS[msID]->channel->VelocityBS = arma::field<arma::mat>(Sim.network->numBS, MAX_CLUSTER + 4, 20);
	MS[msID]->channel->tau = arma::field<arma::mat>(57);
	MS[msID]->channel->tauLOS = arma::field<arma::mat>(57);
	MS[msID]->channel->DftParameter = arma::field<arma::cx_mat>(Sim.network->numBS, 50);
	MS[msID]->channel->FrequencyChannel = arma::field<arma::cx_mat>(Sim.network->numMS, 2, 50);
	MS[msID]->channel->CouplingLoss.zeros(57);
	arma::field<arma::mat> E(Sim.network->numBS, 1);
	MS[msID]->channel->DemoAOA = E;
	MS[msID]->channel->DemoAOD = E;
	MS[msID]->channel->DemoClusterPower = E;
}

void Channel::TemporaryGlobalVariableInitializeForBS(int bsID) {
	// Initialize
	BS[bsID]->channel->RSRPout.zeros(57, 1);
	BS[bsID]->channel->VelocityLOS.zeros(57, 1);
	BS[bsID]->channel->Alpha_zero_temp = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	BS[bsID]->channel->Alpha_zero_temp_x = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	BS[bsID]->channel->Alpha_zero_temp1 = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	BS[bsID]->channel->Alpha_zero_temp_x1 = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	BS[bsID]->channel->NumRealCluseter.zeros(Sim.network->numBS, 1);
	arma::field<arma::cx_mat> A(Sim.network->numBS, 1);
	BS[bsID]->channel->F_urd_LOS = A;
	BS[bsID]->channel->F_prd_LOS = A;
	arma::field<arma::cx_mat> B(MAX_CLUSTER, 20);
	BS[bsID]->channel->F_urd = B;
	BS[bsID]->channel->F_prd = B;
	arma::field<arma::cx_mat> C(Sim.network->numBS, MAX_CLUSTER, 20);
	BS[bsID]->channel->F_urd_BS = C;
	BS[bsID]->channel->F_prd_BS = C;
	arma::field<arma::cx_mat> D(Sim.network->numBS, Sim.channel->NumberOfChannelProcess);
	BS[bsID]->channel->Alpha_nmup_temp = D;
	BS[bsID]->channel->Alpha_nmup_temp_x = D;
	BS[bsID]->channel->Alpha_nmup_temp1 = D;
	BS[bsID]->channel->Alpha_nmup_temp_x1 = D;
	BS[bsID]->channel->VelocityBS = arma::field<arma::mat>(Sim.network->numBS, MAX_CLUSTER + 4, 20);
	BS[bsID]->channel->tau = arma::field<arma::mat>(57);
	BS[bsID]->channel->tauLOS = arma::field<arma::mat>(57);
	BS[bsID]->channel->DftParameter = arma::field<arma::cx_mat>(Sim.network->numBS, 50);
	BS[bsID]->channel->FrequencyChannel = arma::field<arma::cx_mat>(Sim.network->numBS, 2, 50);
	BS[bsID]->channel->CouplingLoss.zeros(57);
	arma::field<arma::mat> E(Sim.network->numBS, 1);
	BS[bsID]->channel->DemoAOA = E;
	BS[bsID]->channel->DemoAOD = E;
	BS[bsID]->channel->DemoClusterPower = E;
}

void Channel::PathlossforMS() {
	int aaa = Sim.network->numMS;
	int aab = Sim.network->numMS;
	int aac = Sim.network->numMS;
		
	this->distancefrom = new double **[aaa];
	for (int a = 0; a < Sim.network->numMS; a++) {
		this->distancefrom[a] = new double *[aab];
		for (int b = 0; b < Sim.network->numMS; b++) {
			this->distancefrom[a][b] = new double[aac];
		}
	}

	this->LOS = new double **[aaa];
	for (int a = 0; a < Sim.network->numMS; a++) {
		this->LOS[a] = new double *[aab];
		for (int b = 0; b < Sim.network->numMS; b++) {
			this->LOS[a][b] = new double[aac];
		}
	}

	this->PLoS = new double **[aaa];
	for (int a = 0; a < Sim.network->numMS; a++) {
		this->PLoS[a] = new double *[aab];
		for (int b = 0; b < Sim.network->numMS; b++) {
			this->PLoS[a][b] = new double[aac];
		}
	}

	this->pathlosss = new double **[aaa];
	for (int a = 0; a < Sim.network->numMS; a++) {
		this->pathlosss[a] = new double *[aab];
		for (int b = 0; b < Sim.network->numMS; b++) {
			this->pathlosss[a][b] = new double[aac];
		}
	}
	// 0; to BS, 1; to WiFiBS, 2: to WiFiMS

	// 거리 계산
	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numBS; ot++) {
			distancefrom[msID][ot][0] = sqrt(pow(MS[msID]->network->pos.real() - BS[ot]->network->pos.real(), 2) + pow(MS[msID]->network->pos.imag() - BS[ot]->network->pos.imag(), 2));
		}
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numBS; ot++) {
			distancefrom[msID][ot][1] = sqrt(pow(MS[msID]->network->pos.real() - WiFiBS[ot]->network->pos.real(), 2) + pow(MS[msID]->network->pos.imag() - WiFiBS[ot]->network->pos.imag(), 2));
		}
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numMS; ot++) {
			distancefrom[msID][ot][2] = sqrt(pow(MS[msID]->network->pos.real() - WiFiMS[ot]->network->pos.real(), 2) + pow(MS[msID]->network->pos.imag() - WiFiMS[ot]->network->pos.imag(), 2));
		}
	}


	// LOS 판단
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {

				if (distancefrom[msID][ot][i] <= 18.0)
				{
					PLoS[msID][ot][i] = 1.0;
				}
				else if (distancefrom[msID][ot][i] > 18.0 && distancefrom[msID][ot][i] < 37.0)
				{
					PLoS[msID][ot][i] = exp(-(distancefrom[msID][ot][i] - 18.0) / 27.0);
				}
				else if (distancefrom[msID][ot][i] >= 37)
				{
					PLoS[msID][ot][i] = 0.5;
				}

				if (PLoS[msID][ot][i] >= (rand() / (float)RAND_MAX))
				{
					LOS[msID][ot][i] = 0;// LOS
				}
				else
				{
					LOS[msID][ot][i] = 1;// NLOS
				}
			}
		}
	}


	// Pathloos 계산 & RSRP에 대입
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {

				if (LOS[msID][ot][i] == 0)
				{
					pathlosss[msID][ot][i] = 16.9*log10(distancefrom[msID][ot][i]) + 32.8 + 20.0*log10(5);
				}
				else if (LOS[msID][ot][i] == 1)
				{
					pathlosss[msID][ot][i] = 43.3*log10(distancefrom[msID][ot][i]) + 11.5 + 20.0*log10(5);
				}

				MS[msID]->scheduling->RSRP_fBS[ot][i] = 18 - pathlosss[msID][ot][i];

			}
		}
	}

	// RSRP; dBm->Watt
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {
				MS[msID]->scheduling->RSRP_fBS[ot][i] = pow(10, (MS[msID]->scheduling->RSRP_fBS[ot][i] - 30) / 10);
			}
		}
	}
}

void Channel::PathlossforWiFiBS() {
	// 0; to BS, 1; to WiFiBS, 2: to WiFiMS
	
	// 거리 계산
	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numBS; ot++) {
			distancefrom[msID][ot][0] = sqrt(pow(WiFiBS[msID]->network->pos.real() - BS[ot]->network->pos.real(), 2) + pow(WiFiBS[msID]->network->pos.imag() - BS[ot]->network->pos.imag(), 2));
		}
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numBS; ot++) {
			distancefrom[msID][ot][1] = sqrt(pow(WiFiBS[msID]->network->pos.real() - WiFiBS[ot]->network->pos.real(), 2) + pow(WiFiBS[msID]->network->pos.imag() - WiFiBS[ot]->network->pos.imag(), 2));
		}
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numMS; ot++) {
			distancefrom[msID][ot][2] = sqrt(pow(WiFiBS[msID]->network->pos.real() - WiFiMS[ot]->network->pos.real(), 2) + pow(WiFiBS[msID]->network->pos.imag() - WiFiMS[ot]->network->pos.imag(), 2));
		}
	}


	// LOS 판단
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {

				if (distancefrom[msID][ot][i] <= 18.0)
				{
					PLoS[msID][ot][i] = 1.0;
				}
				else if (distancefrom[msID][ot][i] > 18.0 && distancefrom[msID][ot][i] < 37.0)
				{
					PLoS[msID][ot][i] = exp(-(distancefrom[msID][ot][i] - 18.0) / 27.0);
				}
				else if (distancefrom[msID][ot][i] >= 37)
				{
					PLoS[msID][ot][i] = 0.5;
				}

				if (PLoS[msID][ot][i] >= (rand() / (float)RAND_MAX))
				{
					LOS[msID][ot][i] = 0;// LOS
				}
				else
				{
					LOS[msID][ot][i] = 1;// NLOS
				}
			}
		}
	}


	// Pathloos 계산 & RSRP에 대입
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {

				if (LOS[msID][ot][i] == 0)
				{
					pathlosss[msID][ot][i] = 16.9*log10(distancefrom[msID][ot][i]) + 32.8 + 20.0*log10(5);
				}
				else if (LOS[msID][ot][i] == 1)
				{
					pathlosss[msID][ot][i] = 43.3*log10(distancefrom[msID][ot][i]) + 11.5 + 20.0*log10(5);
				}

				WiFiBS[msID]->scheduling->RSRP_fBS[ot][i] = 18 - pathlosss[msID][ot][i];

			}
		}
	}

	// RSRP; dBm->Watt
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {
				WiFiBS[msID]->scheduling->RSRP_fBS[ot][i] = pow(10, (WiFiBS[msID]->scheduling->RSRP_fBS[ot][i] - 30) / 10);
			}
		}
	}
}

void Channel::PathlossforWiFiMS() {
	// 0; to BS, 1; to WiFiBS, 2: to WiFiMS
	
	// 거리 계산
	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numBS; ot++) {
			distancefrom[msID][ot][0] = sqrt(pow(WiFiBS[msID]->network->pos.real() - BS[ot]->network->pos.real(), 2) + pow(WiFiMS[msID]->network->pos.imag() - BS[ot]->network->pos.imag(), 2));
		}
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numBS; ot++) {
			distancefrom[msID][ot][1] = sqrt(pow(WiFiMS[msID]->network->pos.real() - WiFiBS[ot]->network->pos.real(), 2) + pow(WiFiMS[msID]->network->pos.imag() - WiFiBS[ot]->network->pos.imag(), 2));
		}
	}

	for (int msID = 0; msID < Sim.network->numMS; msID++) {
		for (int ot = 0; ot < Sim.network->numMS; ot++) {
			distancefrom[msID][ot][2] = sqrt(pow(WiFiMS[msID]->network->pos.real() - WiFiMS[ot]->network->pos.real(), 2) + pow(WiFiMS[msID]->network->pos.imag() - WiFiMS[ot]->network->pos.imag(), 2));
		}
	}


	// LOS 판단
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {

				if (distancefrom[msID][ot][i] <= 18.0)
				{
					PLoS[msID][ot][i] = 1.0;
				}
				else if (distancefrom[msID][ot][i] > 18.0 && distancefrom[msID][ot][i] < 37.0)
				{
					PLoS[msID][ot][i] = exp(-(distancefrom[msID][ot][i] - 18.0) / 27.0);
				}
				else if (distancefrom[msID][ot][i] >= 37)
				{
					PLoS[msID][ot][i] = 0.5;
				}

				if (PLoS[msID][ot][i] >= (rand() / (float)RAND_MAX))
				{
					LOS[msID][ot][i] = 0;// LOS
				}
				else
				{
					LOS[msID][ot][i] = 1;// NLOS
				}
			}
		}
	}


	// Pathloos 계산 & RSRP에 대입
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {

				if (LOS[msID][ot][i] == 0)
				{
					pathlosss[msID][ot][i] = 16.9*log10(distancefrom[msID][ot][i]) + 32.8 + 20.0*log10(5);
				}
				else if (LOS[msID][ot][i] == 1)
				{
					pathlosss[msID][ot][i] = 43.3*log10(distancefrom[msID][ot][i]) + 11.5 + 20.0*log10(5);
				}

				WiFiMS[msID]->scheduling->RSRP_fBS[ot][i] = 18 - pathlosss[msID][ot][i];

			}
		}
	}

	// RSRP; dBm->Watt
	for (int i = 0; i < 3; i++) {
		for (int msID = 0; msID < Sim.network->numMS; msID++) {
			for (int ot = 0; ot < Sim.network->numBS; ot++) {
				WiFiMS[msID]->scheduling->RSRP_fBS[ot][i] = pow(10, (WiFiMS[msID]->scheduling->RSRP_fBS[ot][i] - 30) / 10);
			}
		}
	}
}

void Channel::ConcludeIteration() {

};

void Channel::Conclude() {

};