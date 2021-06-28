/****************************************************************************

Channel Model (NR eMBB)


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

#include "Channel_NReMBB.h"


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
}

void Channel::ShortTermChannel()
{
	/*for (int msID = 0; msID < Sim.network->numMS; msID++)
	{
		MS[msID]->channel->ShortTermChannel(msID);
	}
		setcolor(11, 0);
		cout << "[Channel]: Short Term Channel of MS(DFT) calculated" << endl;*/
}

void Channel::TemporaryGlobalVariableInitialize(int msID) {
	// Initialize
	MS[msID]->channel->RSRPout.zeros(Sim.network->numBS, 1);
	MS[msID]->channel->VelocityLOS.zeros(Sim.network->numBS, 1);
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
	MS[msID]->channel->tau = arma::field<arma::mat>(Sim.network->numBS);
	MS[msID]->channel->tauLOS = arma::field<arma::mat>(Sim.network->numBS);
	MS[msID]->channel->DftParameter = arma::field<arma::cx_mat>(Sim.network->numBS, 50 / 10 * NReMBB.bandwidth);
	MS[msID]->channel->FrequencyChannel = arma::field<arma::cx_mat>(Sim.network->numMS, 2, 50 / 10 * NReMBB.bandwidth);
	MS[msID]->channel->CouplingLoss.zeros(Sim.network->numBS);
	arma::field<arma::mat> E(Sim.network->numBS, 1);
	MS[msID]->channel->DemoAOA = E;
	MS[msID]->channel->DemoAOD = E;
	MS[msID]->channel->DemoClusterPower = E;
}

void Channel::ConcludeIteration() {

};

void Channel::Conclude() {

};