/****************************************************************************

Channel Model for Mobile Station (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : ChannelURLLCMS_NRuRLLC.cpp
DATE         : 2017.01.02
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.01.31	Minsig Han		Created
2017.02.22	Minsig Han		RSRP
2017.02.26  Minsig Han		DFT
2017.03.01	Minsig Han		Short-term Channel
2017.03.07  Minsig Han		Apply PL and Shadowing

===========================================================================*/

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "ChannelURLLCMS_NRuRLLC.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         Level 1 Functions                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void ChannelURLLCMS::Initialize(int msID)
{
	int id = msID; // UMS ID
	antennaOrientation.zeros(3, 1);
	antennaOrientation(0, 0) = arma::randu() * 360 * PI / 180;
	antennaOrientation(1, 0) = 90.0*PI / 180;
	antennaOrientation(2, 0) = 0;
	//complex<double> vector;

	//for (int i = 0; i < Sim.network->numBS; i++) // Long term channel calculation
	//{
	//	for (int j = 0; j < Sim.network->numWraparound; j++)
	//	{
	//	
	//	}
	//}
}

void ChannelURLLCMS::LongTermChannel(int msID) {
	
//	spatialChannel = new SpatialChannel();
	//// BS-to-UMS channel
	//for (int bsID = 0, site = 0; site < Sim.network->numBS; site++)
	//{
	//	GeneralParameters(msID, site);
	//	for (int sector = 0; sector < Sim.network->numSector; sector++, bsID++)
	//	{
	//		SmallScaleParameter(msID, bsID, site, sector);
	//		CoefficientGeneration(msID, bsID, site, sector);
	//	}
	//}

	//// BS-to-BS channel
	//for (int bsID = 0, site = 0; site < Sim.network->numSite; site++)
	//{

	//}

	//// UMS-to-UMS channel
	//for (int bsID = 0, site = 0; site < Sim.network->numSite; site++)
	//{

	//}

	for (int bsID = 0, site = 0; site < Sim.network->numSite; site++) {
		GeneralParameters(msID, site);								
		for (int sector = 0; sector < Sim.network->numSector; sector++, bsID++){
			SmallScaleParameter(msID, bsID, site, sector);
			CoefficientGeneration(msID, bsID, site, sector);
		}
	}

	UMS[msID]->network->Associate(msID, UMS[msID]->channel->RSRPout); // Perform association
	ChannelCoefficient(msID);
	ApplyPathLossAndShadowing(msID);

}

void ChannelURLLCMS::ShortTermChannel(int msID) {
	
	DftParameterSetting(msID);
	DiscreteFourierTransform(msID);
	/*if (Sim.TTI == (UMS[msID]->network->bufferTime + UMS[msID]->network->interArrivalTime(UMS[msID]->network->arrivalTime)))
	{
		UMS[msID]->network->msBuffer = UMS[msID]->network->msBuffer + Sim.network->bufferSize;
		UMS[msID]->network->bufferTime = Sim.TTI;
		UMS[msID]->network->arrivalTime++;
	}*/
}

void ChannelURLLCMS::GeneralParameters(int msID, int site) {
	SpatialChannel spatialChannel;
	spatialChannel.Initialize();
	UMS[msID]->channel->distance2D = spatialChannel.Distance2D(UMS[msID]->network->pos3D(0, 0), UMS[msID]->network->pos3D(0, 1), UMS[msID]->network->wraparoundposBS(site, 0), UMS[msID]->network->wraparoundposBS(site, 1));
	UMS[msID]->channel->distance3D = spatialChannel.Distance3D(UMS[msID]->network->pos3D(0, 0), UMS[msID]->network->pos3D(0, 1), UMS[msID]->network->pos3D(0, 2), UMS[msID]->network->wraparoundposBS(site, 0), UMS[msID]->network->wraparoundposBS(site, 1), UMS[msID]->network->wraparoundposBS(site, 2));

	// cout << "Pathloss calculated" << endl;
	spatialChannel.Pathloss(msID, site, 1);
	UMS[msID]->channel->largeScaleParameter = UMS[msID]->network->LargeScaleParameter(Sim.channel->ChannelModel, UMS[msID]->channel->channelCondition, msID, site); // ShadowFading, RiceanK, DelaySpread, rmsASD, rmsASA, rmsZSD, rmsZSA
}

void ChannelURLLCMS::SmallScaleParameter(int msID, int bsID, int site, int sector) {
	SpatialChannel spatialChannel;
	spatialChannel.Initialize();

	spatialChannel.Delay(msID, 1);
	// cout << "Delay genereated" << endl;

	spatialChannel.ClusterPower(msID, bsID, 1);
	// cout << "Cluster Power Generated" << endl;

	spatialChannel.ArrivalAndDepartureAngle(msID, bsID, site, sector, 1);
	// cout << "Generate Arrival And Departure Angles"<< endl;

	spatialChannel.ArrivalAndDepartureAntennaGain(msID, bsID, site, sector, 1);
	// cout << "Generate Arrival And Departure AntennaGains" << endl;

}

void ChannelURLLCMS::CoefficientGeneration(int msID, int bsID, int site, int sector) {
	RSRP(msID, bsID, site, sector);
}

void ChannelURLLCMS::RSRP(int src, int dst, int site, int sector) {
	double muXPR, sigmaXPR;
	SpatialChannel spatialChannel;
	spatialChannel.Initialize();

	if ((UMS[src]->network->location == Outdoor) && (UMS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
		muXPR = spatialChannel.UrbanMacroCellLOS.muXPR;
		sigmaXPR = spatialChannel.UrbanMacroCellLOS.sigmaXPR;
	}
	else if ((UMS[src]->network->location == Outdoor) && (UMS[src]->channel->channelCondition == NLOS)) {
		muXPR = spatialChannel.UrbanMacroCellNLOS.muXPR;
		sigmaXPR = spatialChannel.UrbanMacroCellNLOS.sigmaXPR;
	}
	else if ((UMS[src]->network->location == Indoor) && (UMS[src]->channel->channelCondition == LOS)) {
		muXPR = spatialChannel.UrbanMacroCellOtoI.muXPR;
		sigmaXPR = spatialChannel.UrbanMacroCellOtoI.sigmaXPR;
	}
	else {
		muXPR = spatialChannel.UrbanMacroCellOtoI.muXPR;
		sigmaXPR = spatialChannel.UrbanMacroCellOtoI.sigmaXPR;
	}
	
	int numRealCluster = UMS[src]->channel->numRealCluster;
	int numRay = 20;
	int numProcess = Sim.channel->NumberOfChannelProcess;
	int numRxAntenna = Sim.channel->NumberOfReceiveAntennaPort;
	double kR = pow(10.0, UMS[src]->channel->largeScaleParameter[1] / 10.0);
	double K_R1;
	double XPR = pow(10.0, (muXPR + sigmaXPR*arma::randn()) / 10.0);

	std::complex<double> Big_pi_NLOS_thetatheta(0, (360 * arma::randu() - 180.0)*PI / 180.0);
	std::complex<double> Big_pi_NLOS_thetapi(0, (360 * arma::randu() - 180.0)*PI / 180.0);
	std::complex<double> Big_pi_NLOS_pitheta(0, (360 * arma::randu() - 180.0)*PI / 180.0);
	std::complex<double> Big_pi_NLOS_pipi(0, (360 * arma::randu() - 180.0)*PI / 180.0);
	arma::field<arma::cx_mat> alpha_nmup_temp(numProcess);
	alpha_nmup_temp(0).zeros(numRealCluster, numRay);
	arma::field<arma::cx_mat> alpha_nmup_temp_x(numProcess);
	alpha_nmup_temp_x(0).zeros(numRealCluster, numRay);
	arma::field<arma::cx_mat> alpha_nmup_temp1(numProcess);
	alpha_nmup_temp1(0).zeros(numRealCluster, numRay);
	arma::field<arma::cx_mat> alpha_nmup_temp_x1(numProcess);
	alpha_nmup_temp_x1(0).zeros(numRealCluster, numRay);

	arma::vec RSRP_cal;
	RSRP_cal.zeros(57);
	arma::mat RSRP;
	RSRP.zeros(numProcess, 1);

	arma::mat cluster_P_1;
	arma::mat F_rx_smallUH;
	arma::mat F_rx_smallUV;
	arma::mat F_rx_smallXH;
	arma::mat F_rx_smallXV;

	arma::cx_mat F_tx_smallUH;
	arma::cx_mat F_tx_smallUV;
	arma::cx_mat F_tx_smallXH;
	arma::cx_mat F_tx_smallXV;

	arma::mat F_rx_UH;
	arma::mat F_rx_UV;
	arma::mat F_rx_XH;
	arma::mat F_rx_XV;

	arma::cx_mat F_tx_UH;
	arma::cx_mat F_tx_UV;
	arma::cx_mat F_tx_XH;
	arma::cx_mat F_tx_XV;
	arma::cx_mat f_urd_LOS = UMS[src]->channel->F_urd_LOS(dst, 0);
	arma::field<arma::mat> Alpha_nmup(Sim.channel->NumberOfReceiveAntennaPort, numProcess);
	arma::mat velocity(MAX_CLUSTER + 4, numRay);


	double AngleAODLOS = UMS[src]->channel->GCSAOD;
	double AngleZODLOS = UMS[src]->channel->GCSZOD;
	double AngleAOALOS = UMS[src]->channel->GCSAOA;
	double AngleZOALOS = UMS[src]->channel->GCSZOA;
	double GCSAOA = UMS[src]->channel->GCSAOA;
	double GCSAOD = UMS[src]->channel->GCSAOD;
	double GCSZOA = UMS[src]->channel->GCSZOA;
	double GCSZOD = UMS[src]->channel->GCSZOD;

	double velocityLOS = 2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(PI - AngleZODLOS)*cos(AngleAOALOS)*5.0 / 6.0*sin(UMS[src]->network->velocityVertical)*cos(UMS[src]->network->velocityHorizontal) + sin(PI - GCSZOD)*sin(GCSAOA)*5.0 / 6.0*sin(UMS[src]->network->velocityVertical)*sin(UMS[src]->network->velocityHorizontal) + cos(PI - GCSZOD)*5.0 / 6.0*cos(UMS[src]->network->velocityVertical));
	UMS[src]->channel->VelocityLOS(dst, 0) = velocityLOS;

	arma::field<arma::mat> alpha_sum(numProcess, 1);

	double rayAOA, rayAOD, rayZOA, rayZOD;

	cluster_P_1 = UMS[src]->channel->realClusterPowersForLOS;
	if ((UMS[src]->network->location == Outdoor) && (UMS[src]->channel->channelCondition == LOS)) K_R1 = kR;
	else K_R1 = 0.0;
	int abb = 0;


	arma::cx_mat alpha_zero_temp(numProcess, 1);
	arma::cx_mat alpha_zero_temp_x(numProcess, 1);
	arma::cx_mat alpha_zero_temp1(numProcess, 1);
	arma::cx_mat alpha_zero_temp_x1(numProcess, 1);
	arma::cx_mat Alpha_zero(numRxAntenna, numProcess);

	F_rx_UH = UMS[src]->channel->ReceiverAntennaGainLOSUH;
	F_rx_UV = UMS[src]->channel->ReceiverAntennaGainLOSUV;
	F_rx_XH = UMS[src]->channel->ReceiverAntennaGainLOSXH;
	F_rx_XV = UMS[src]->channel->ReceiverAntennaGainLOSXV;

	F_tx_UH = UMS[src]->channel->TransmitterAntennaGainLOSUH;
	F_tx_UV = UMS[src]->channel->TransmitterAntennaGainLOSUV;
	F_tx_XH = UMS[src]->channel->TransmitterAntennaGainLOSXH;
	F_tx_XV = UMS[src]->channel->TransmitterAntennaGainLOSXV;

	std::complex<double> Big_PI_LOS(0.0, (360 * arma::randu() - 180.0)*PI / 180.0);

	int processIndex = UMS[src]->channel->processIndex;

	if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray))
		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0));
	else if ((Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray)) {
		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
		alpha_zero_temp_x[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_XV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_XH(0, 0));
	}
	else if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization)) {
		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
		alpha_zero_temp_x[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_XV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_XH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
	}
	else {
		alpha_zero_temp[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0));
		alpha_zero_temp1[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_UV(0, 0) * exp(Big_PI_LOS) * F_tx_XV(0, 0) - F_rx_UH(0, 0) * exp(Big_PI_LOS) * F_tx_XH(0, 0)); // tx x
		alpha_zero_temp_x[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_XV(0, 0) * exp(Big_PI_LOS) * F_tx_XV(0, 0) - F_rx_XH(0, 0) * exp(Big_PI_LOS) * F_tx_XH(0, 0));
		alpha_zero_temp_x1[processIndex] = sqrt(K_R1 / (K_R1 + 1.0f)) * (F_rx_XV(0, 0) * exp(Big_PI_LOS) * F_tx_UV(0, 0) - F_rx_XH(0, 0) * exp(Big_PI_LOS) * F_tx_UH(0, 0)); // rx x
	}

	for (int u = 0; u < Sim.channel->NumberOfReceiveAntennaPort; u++) {
		Alpha_zero(u, processIndex) = alpha_zero_temp[processIndex] * exp(f_urd_LOS[u]);
		Alpha_nmup(u, processIndex) = 0.0;
	}



	for (int n = 0; n < numRealCluster; n++) {
		for (int m = 0; m < numRay; m++) {
			F_rx_smallUH = UMS[src]->channel->SmallScaleReceiverAntennaGainUH(n, m);
			F_rx_smallUV = UMS[src]->channel->SmallScaleReceiverAntennaGainUV(n, m);
			F_rx_smallXH = UMS[src]->channel->SmallScaleReceiverAntennaGainXH(n, m);
			F_rx_smallXV = UMS[src]->channel->SmallScaleReceiverAntennaGainXV(n, m);

			F_tx_smallUH = UMS[src]->channel->SmallScaleTransmitterAntennaGainUH(n, m);
			F_tx_smallUV = UMS[src]->channel->SmallScaleTransmitterAntennaGainUV(n, m);
			F_tx_smallXH = UMS[src]->channel->SmallScaleTransmitterAntennaGainXH(n, m);
			F_tx_smallXV = UMS[src]->channel->SmallScaleTransmitterAntennaGainXV(n, m);

			rayAOA = UMS[src]->channel->SmallScaleAOA(n, m);
			rayAOD = UMS[src]->channel->SmallScaleAOD(n, m);
			rayZOA = UMS[src]->channel->SmallScaleZOA(n, m);
			rayZOD = UMS[src]->channel->SmallScaleZOD(n, m);

			for (int processIndex = 0; processIndex < numProcess; processIndex++) {
				for (int u = 0; u < numRxAntenna; u++) {
					if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray))
						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*(F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) * F_tx_smallUV(0, 0));
					else if ((Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) && (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray)) {
						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
						alpha_nmup_temp_x(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallXV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallXH(0, 0));
					}
					else if ((Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) && (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization)) {
						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
						alpha_nmup_temp_x(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0)))*((F_rx_smallXV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallXH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallXV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallXH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
					}
					else {
						alpha_nmup_temp(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0));
						alpha_nmup_temp1(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallUV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallUH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallXV(0, 0) + (F_rx_smallUV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallUH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallXH(0, 0)); // tx x
						alpha_nmup_temp_x(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallXV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallXH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallXV(0, 0) + (F_rx_smallXV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallXH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallXH(0, 0));
						alpha_nmup_temp_x1(processIndex)(n, m) = sqrt(cluster_P_1[n] / (20.0f * (K_R1 + 1.0f)))*((F_rx_smallXV(0, 0) * exp(Big_pi_NLOS_thetatheta) + F_rx_smallXH(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_pitheta)) * F_tx_smallUV(0, 0) + (F_rx_smallXV(0, 0) * sqrt(1.0f / XPR) * exp(Big_pi_NLOS_thetapi) + F_rx_smallXH(0, 0) * exp(Big_pi_NLOS_pipi)) * F_tx_smallUH(0, 0)); // rx x
					}

					Alpha_nmup(u, processIndex) = Alpha_nmup(u, processIndex) + pow(abs(alpha_nmup_temp(processIndex)(n, m) * exp(UMS[src]->channel->F_urd(n, m)(u, 0))), 2.0);
				}

				if (n == 0 || n == 1) {
					velocity(abb, m) = 2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(rayZOA*PI / 180.0)*cos(rayAOA*PI / 180.0)*5.0 / 6.0*sin(UMS[src]->network->velocityVertical)*cos(UMS[src]->network->velocityHorizontal) + sin(rayZOA*PI / 180.0)*sin(rayAOA*PI / 180.0)*5.0 / 6.0*sin(UMS[src]->network->velocityVertical)*sin(UMS[src]->network->velocityHorizontal) + cos(rayZOA*PI / 180.0)*5.0 / 6.0*cos(UMS[src]->network->velocityVertical));
					velocity(abb + 1, m) = velocity(abb, m);
					velocity(abb + 2, m) = velocity(abb, m);
					if ((m == 19) && (processIndex == numProcess - 1))
						abb = abb + 3;
				}
				else {
					velocity[abb, m] = 2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(rayZOA*PI / 180.0)*cos(rayAOA*PI / 180.0)*5.0 / 6.0*sin(UMS[src]->network->velocityVertical)*cos(UMS[src]->network->velocityHorizontal) + sin(rayZOA*PI / 180.0)*sin(rayAOA*PI / 180.0)*5.0 / 6.0*sin(UMS[src]->network->velocityVertical)*sin(UMS[src]->network->velocityHorizontal) + cos(rayZOA*PI / 180.0)*5.0 / 6.0*cos(UMS[src]->network->velocityVertical));
					if ((m == 19) && (processIndex == numProcess - 1))
						abb++;
				}

			}
			//			UMS[src]->channel->Velocity = velocity;
			UMS[src]->channel->VelocityBS(dst) = velocity;
		}
	}

	double couplingLoss = pow(10.0, -UMS[src]->channel->pathloss / 10.0) * pow(10.0, -UMS[src]->channel->largeScaleParameter(0, 0) / 10.0)* pow(10, (Sim.channel->NRuRLLC.txPower / 10.0));
	UMS[src]->channel->CouplingLoss(dst) = couplingLoss;

	for (int processIndex = 0; processIndex < numProcess; processIndex++) {
		alpha_sum[processIndex] = 0.0;
		for (int u = 0; u < numRxAntenna; u++) {
			alpha_sum[processIndex] = alpha_sum[processIndex] + pow(abs(Alpha_zero(u, processIndex)), 2.0) + Alpha_nmup(u, processIndex);
		}
		RSRP[processIndex] = couplingLoss * alpha_sum[processIndex](0, 0) / numRxAntenna / numProcess;
	}

	RSRP_cal(3 * site + sector) = RSRP[0];

	UMS[src]->channel->Alpha_zero_temp(dst) = alpha_zero_temp;
	UMS[src]->channel->Alpha_zero_temp_x(dst, 0) = alpha_zero_temp_x;
	UMS[src]->channel->Alpha_zero_temp1(dst, 0) = alpha_zero_temp1;
	UMS[src]->channel->Alpha_zero_temp_x1(dst, 0) = alpha_zero_temp_x1;

	UMS[src]->channel->Alpha_nmup_temp(dst, 0) = alpha_nmup_temp(0);
	UMS[src]->channel->Alpha_nmup_temp_x(dst, 0) = alpha_nmup_temp_x(0);
	UMS[src]->channel->Alpha_nmup_temp1(dst, 0) = alpha_nmup_temp1(0);
	UMS[src]->channel->Alpha_nmup_temp_x1(dst, 0) = alpha_nmup_temp_x1(0);

	UMS[src]->channel->RSRPout(3 * site + sector, 0) = RSRP_cal(3 * site + sector, 0);
}

void ChannelURLLCMS::ChannelCoefficient(int src) {
	int numProcess = Sim.channel->NumberOfChannelProcess;
	int numPort = Sim.channel->NumberOfTransmitAntennaPort;
	int numRxAntenna = Sim.channel->NumberOfReceiveAntennaPort;

	arma::mat RSRP = UMS[src]->channel->RSRPout;
	arma::field<arma::cx_mat> alpha_zero_temp = UMS[src]->channel->Alpha_zero_temp;
	arma::field<arma::cx_mat> alpha_zero_temp_x = UMS[src]->channel->Alpha_zero_temp_x;
	arma::field<arma::cx_mat> alpha_zero_temp1 = UMS[src]->channel->Alpha_zero_temp1;
	arma::field<arma::cx_mat> alpha_zero_temp_x1 = UMS[src]->channel->Alpha_zero_temp_x1;

	arma::field<arma::cx_mat> F_urd_LOS = UMS[src]->channel->F_urd_LOS;
	arma::field<arma::cx_mat> F_prd_LOS = UMS[src]->channel->F_prd_LOS;
	arma::field<arma::cx_mat> F_urd_BS = UMS[src]->channel->F_urd_BS;
	arma::field<arma::cx_mat> F_prd_BS = UMS[src]->channel->F_prd_BS;


	arma::field<arma::cx_mat> SI_H_t_los(SLS_MAX_BS, 1); //이거랑
	arma::field<arma::cx_mat> SI_H_t(SLS_MAX_BS, numProcess, MAX_CLUSTER); //이거 process 지우기
	UMS[src]->channel->HtLOS = arma::field<arma::cx_mat>(Sim.network->numBS, 1);
	UMS[src]->channel->Ht = arma::field<arma::cx_mat>(Sim.network->numBS, 1, MAX_CLUSTER);


	for (int bsIndex = 0; bsIndex < SLS_MAX_BS; bsIndex++) {
		SI_H_t_los(bsIndex, 0).zeros(numRxAntenna*numPort, 1);
		UMS[src]->channel->HtLOS(bsIndex, 0).zeros(numRxAntenna*numPort, 1);
	}

	for (int siIndex = 0; siIndex < Sim.network->numBS; siIndex++) {
		for (int processIndex = 0; processIndex < numProcess; processIndex++) {
			for (int n = 0; n < MAX_CLUSTER; n++) {
				SI_H_t(siIndex, processIndex, n).zeros(numRxAntenna*numPort, MAX_RAY);
				UMS[src]->channel->Ht(siIndex, processIndex, n).zeros(numRxAntenna*numPort, MAX_RAY);
			}
		}
	}

	// Strong Interference
	UMS[src]->channel->numRay = 20;
	arma::uvec BSindex = UMS[src]->channel->BSindex;
	for (int siIndex = 0; siIndex < Sim.network->numBS; siIndex++) {
		int dst = BSindex(siIndex);
		for (int u = 0; u < numRxAntenna; u++) {
			for (int p = 0; p < numPort; p++) {
				for (int processIndex = 0; processIndex < numProcess; processIndex++) {
					if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 0))
						SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex, 0) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
					else if ((Sim.channel->BsAntennaModel == 1) && (Sim.channel->MsAntennaModel == 0)) {
						if (p < numProcess / 2)
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
						else
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
					}
					else if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 1)) {
						if (u % 2 == 0)
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
						else
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
					}
					else {
						if ((u % 2 == 0) && (p < numProcess / 2))
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp(dst)(processIndex) *exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
						else if ((u % 2 == 0) && (p >= numProcess / 2))
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp1(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
						else if ((u % 2 == 1) && (p >= numProcess / 2))
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
						else
							SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0) = alpha_zero_temp_x1(dst)(processIndex) * exp(F_urd_LOS(dst)(u)) * exp(F_prd_LOS(dst)(p));
					}

					UMS[src]->channel->HtLOS(siIndex, processIndex)(u*numProcess + p, 0) = SI_H_t_los(siIndex, processIndex)(u*numProcess + p, 0);
				}
			}
		}

		//SI_H_t_los(0, 0).print();
		//alpha_zero_temp(siIndex).print();

		arma::field<arma::cx_mat> Alpha_nmup_temp = UMS[src]->channel->Alpha_nmup_temp;
		arma::field<arma::cx_mat> Alpha_nmup_temp1 = UMS[src]->channel->Alpha_nmup_temp1;
		arma::field<arma::cx_mat> Alpha_nmup_temp_x = UMS[src]->channel->Alpha_nmup_temp_x;
		arma::field<arma::cx_mat> Alpha_nmup_temp_x1 = UMS[src]->channel->Alpha_nmup_temp_x1;
		arma::Mat<int> NumRealCluseter = UMS[src]->channel->NumRealCluseter;

		for (int processIndex = 0; processIndex < numProcess; processIndex++) {
			int clst = 0;
			for (int n = 0; n < NumRealCluseter(dst); n++) {
				for (int m = 0; m < 20; m++) {
					for (int u = 0; u < numRxAntenna; u++) {
						for (int p = 0; p < numPort; p++) {
							if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 0)) {
								if (n == 0 || n == 1) {
									if (m < 10) {
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
									else if (m < 16) {
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
									else {
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								else { //n>=2
									SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
									if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
										clst++;
									}
								}
							}
							else if ((Sim.channel->BsAntennaModel == 1) && (Sim.channel->MsAntennaModel == 0)) {
								if (p < numPort / 2) {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								else {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
							}
							else if ((Sim.channel->BsAntennaModel == 0) && (Sim.channel->MsAntennaModel == 1)) {
								if (u % 2 == 0) {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								else {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
							}
							else {
								if ((u % 2 == 0) && (p < numPort / 2)) {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								else if ((u % 2 == 0) && (p >= numPort / 2)) {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								else if ((u % 2 == 1) && (p >= numPort / 2)) {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								else {
									if (n == 0 || n == 1) {
										if (m < 10) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 9) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else if (m < 16) {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 15) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
										else {
											SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
											if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
												clst++;
											}
										}
									}
									else { //n>=2
										SI_H_t(siIndex, processIndex, clst)(u*numPort + p, m) = Alpha_nmup_temp_x1(dst, processIndex)(n, m) * exp(F_urd_BS(dst, n, m)(u)) * exp(F_prd_BS(dst, n, m)(p));
										if ((m == 19) && (u == numRxAntenna - 1) && (p == numPort - 1)) {
											clst++;
										}
									}
								}
								//
							}

						}
					}
				}
			}
		}
	}
	UMS[src]->channel->Ht = SI_H_t;

}

void ChannelURLLCMS::ApplyPathLossAndShadowing(int src) {
	arma::cx_mat x(57, 1);
	arma::cx_mat y(1, 1);
	for (int si = 0; si < Sim.network->numBS; si++) {
		int dst = UMS[src]->channel->BSindex(si);
		//UMS[src]->channel->BSindex.print();
		//UMS[src]->channel->Ht(si, 0).print();
		y.zeros(1, 1);
		for (int n = 0; n < UMS[src]->channel->NumRealCluseter(dst); n++)
		{
			UMS[src]->channel->Ht(si, 0, n) = (UMS[src]->channel->CouplingLoss(dst)) * UMS[src]->channel->Ht(si, 0, n);
			//y = y + UMS[src]->channel->Ht(si, 0, n)*UMS[src]->channel->Ht(si, 0, n).t();
			//y = UMS[src]->channel->Ht(si, 0, n)*UMS[src]->channel->Ht(si, 0, n).t();
			//y.print();
		}

		//UMS[src]->channel->HtLOS(si,0) = (UMS[src]->channel->CouplingLoss(dst)) * UMS[src]->channel->HtLOS(si,0);
		//cout << UMS[src]->channel->channelCondition << endl;
		//UMS[src]->channel->HtLOS(si, 0).print();
		//y = y+ UMS[src]->channel->HtLOS(si, 0)*UMS[src]->channel->HtLOS(si, 0).t();
		x(si, 0) = y(0, 0);
	}
	//y = x(0, 0) /(sum(x)- x(0, 0));
	//y.print();

}

void ChannelURLLCMS::DftParameterSetting(int src)
{

	for (int si = 0; si < SLS_MAX_BS; si++)
	{
		int siIndex = UMS[src]->channel->BSindex(si);

		for (int c = 0; c < 50; c++)
		{
			UMS[src]->channel->DftParameter(si, c).zeros(1, MAX_CLUSTER + 4);
			int f = 213 + c * 12 + 6;
			int abb1 = 0;
			for (int n = 0; n < UMS[src]->channel->NumRealCluseter(siIndex); n++) {
				if (n == 0 || n == 1) {
					std::complex<double> dft, dft1, dft2;
					if ((UMS[src]->network->location == Outdoor) && (UMS[src]->channel->channelCondition == LOS)) {
						dft.real(0.0);
						dft.imag(-2.0 * PI*double(f)*UMS[src]->channel->tauLOS(siIndex)(n) * 15360000.0 / 1024.0);
						dft1.real(0.0);
						dft1.imag(-2.0 * PI*double(f)*(UMS[src]->channel->tauLOS(siIndex)(n) + 5e-9) * 15360000.0 / 1024.0);
						dft2.real(0.0);
						dft2.imag(-2.0 * PI*double(f)*(UMS[src]->channel->tauLOS(siIndex)(n) + 10e-9) * 15360000.0 / 1024.0);
					}
					else {
						dft.real(0.0);
						dft.imag(-2.0 * PI*double(f)*UMS[src]->channel->tau(siIndex)(n) * 15360000.0 / 1024.0);
						dft1.real(0.0);
						dft1.imag(-2.0 * PI*double(f)*(UMS[src]->channel->tau(siIndex)(n) + 5e-9) * 15360000.0 / 1024.0);
						dft2.real(0.0);
						dft2.imag(-2.0 * PI*double(f)*(UMS[src]->channel->tau(siIndex)(n) + 10e-9) * 15360000.0 / 1024.0);
					}
					UMS[src]->channel->DftParameter(si, c)(0, abb1) = exp(dft);
					UMS[src]->channel->DftParameter(si, c)(0, abb1 + 1) = exp(dft1);
					UMS[src]->channel->DftParameter(si, c)(0, abb1 + 2) = exp(dft2);
					abb1 = abb1 + 3;
				}
				else {
					std::complex<double> dft;
					if ((UMS[src]->network->location == Outdoor) && (UMS[src]->channel->channelCondition == LOS)) {
						dft.real(0.0);
						dft.imag(-2.0 * PI*double(f)*UMS[src]->channel->tauLOS(siIndex)(n) * 15360000.0 / 1024.0);
					}
					else {
						dft.real(0.0);
						dft.imag(-2.0 * PI*double(f)*UMS[src]->channel->tau(siIndex)(n) * 15360000.0 / 1024.0);
					}
					UMS[src]->channel->DftParameter(si, c)(0, abb1) = exp(dft);
					abb1 = abb1 + 1;
				}
			}
		}
	}

}

void ChannelURLLCMS::DiscreteFourierTransform(int src)
{
	arma::cx_mat x(57, 1);
	arma::cx_mat y;
	arma::field<arma::cx_mat> exp_vt(MAX_CLUSTER + 4); // dft 용
	arma::cx_mat h_k;
	arma::cx_mat h_k1;
	arma::cx_mat tmpp;
	tmpp.zeros(Sim.channel->NumberOfReceiveAntennaPort*Sim.channel->NumberOfTransmitAntennaPort, 1);
	std::complex<double> vt(0.0, 0.0);
	for (int si = 0; si < SLS_MAX_BS; si++) {
		y.zeros(1, 1);
		h_k.zeros(Sim.channel->NumberOfReceiveAntennaPort*Sim.channel->NumberOfTransmitAntennaPort, MAX_CLUSTER + 4);
		h_k1.zeros(Sim.channel->NumberOfReceiveAntennaPort*Sim.channel->NumberOfTransmitAntennaPort, MAX_CLUSTER + 4);
		//int l_ = wrap(i, si/3);
		int siIndex = UMS[src]->channel->BSindex(si);
		for (int pr = 0; pr < Sim.channel->NumberOfChannelProcess; pr++) {
			for (int n = 0; n < UMS[src]->channel->NumRealCluseter(siIndex); n++) {
				exp_vt(n).zeros(20, 1);
				for (int m = 0; m < 20; m++) {
					vt.real(0.0);
					vt.imag(2.0 * PI*UMS[src]->channel->VelocityBS(siIndex)(n, m) * double(Sim.TTI) / 1000.0); //[si] 빼고
					exp_vt(n)(m, 0) = exp(vt);
				}
				//h_k.col(n) = UMS[src]->channel->Ht[si, pr, n] * exp_vt[n];
				//UMS[src]->channel->Ht(si, pr, n).print();
				h_k.col(n) = UMS[src]->channel->Ht(si, pr, n) * exp_vt(n);
				//y = y+ UMS[src]->channel->Ht(si, pr, n)* UMS[src]->channel->Ht(si, pr, n).t();
				if (n == 0) //라이시안 부분 
				{
					vt.real(0.0);
					vt.imag(2.0 * PI*UMS[src]->channel->VelocityLOS[siIndex] * double(Sim.TTI) / 1000.0);
					h_k.col(n) = h_k.col(n) + UMS[src]->channel->HtLOS[si, pr] * exp(vt);
					//h_k.col(n) = h_k.col(n) + UMS[src]->channel->HtLOS(si, pr);
				}
			}
			for (int c = 0; c < 50; c++) {
				tmpp = UMS[src]->channel->DftParameter(si, c) * strans(h_k);
				UMS[src]->channel->FrequencyChannel(si, pr, c).zeros(Sim.channel->NumberOfReceiveAntennaPort, Sim.channel->NumberOfTransmitAntennaPort);

				for (int rx_ant = 0; rx_ant < Sim.channel->NumberOfReceiveAntennaPort; rx_ant++)
				{
					UMS[src]->channel->FrequencyChannel(si, pr, c).row(rx_ant) = tmpp.submat(0, rx_ant*Sim.channel->NumberOfTransmitAntennaPort, 0, rx_ant*Sim.channel->NumberOfTransmitAntennaPort + Sim.channel->NumberOfTransmitAntennaPort - 1);
				}
			}
		}
	}

}

void ChannelURLLCMS::ConcludeIteration() {
}

void ChannelURLLCMS::Conclude() {
}
