/****************************************************************************

Channel Model for Mobile Station header (NR eMBB)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : ChannelMS_NReMBB.h
DATE         : 2016.10.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.20   Minsig Han      Created

===========================================================================*/

#ifndef CHANNELMS_H
#define CHANNELMS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel mobile station parameter
class ChannelMS//: public SpatialChannel
{
public:
// Spatial Channel Library
//	class SpatialChannel *spatialChannel;

// Channel functions(Level 1) - Related to simulation main
	void Initialize(int msID);		 // Initialization
	void LongTermChannel(int msID);
	void ShortTermChannel(int msID);
	void ConcludeIteration();		 // Iteration conclusion
	void Conclude();	
	

	// Channel Level 2 functions
	void SmallScaleParameter(int msID, int bsID, int site, int sector);
	void GeneralParameters(int msID, int site);
	void CoefficientGeneration(int msID, int bs, int site, int sector);
	void RSRP(int msID, int bs, int site, int sector);
	void ChannelCoefficient(int msID);
	void ApplyPathLossAndShadowing(int msID);
	void DftParameterSetting(int msID);
	void DiscreteFourierTransform(int msID);

// MS specific channel variable
	enum MS_channelCondition condition;
	int channelCondition;				// 0=LOS 1=NLOS
	int associatedBsIndex;
	int numCluster;
	int processIndex;
	int numRealCluster;
	int numRay;
	double distance2D;
	double distance3D;
	double GCSAOA;
	double GCSAOD;
	double GCSZOA;
	double GCSZOD;
	arma::mat antennaOrientation;
	arma::vec AnalogBeamPhase;
	arma::vec DigitalBeamPhase;
	arma::vec BeamAmplitude;

// MS specific Channel coefficient
	double pathloss;
	double maxClusterPower;
	arma::mat largeScaleParameter;
	arma::mat delay;
	arma::mat delayReduced;
	arma::mat clusterPowerReduced;  // KR O
	arma::mat realClusterPowersForLOS; // KR X back
	arma::mat departureAngle;
	arma::mat arrivalAngle;
	arma::mat Site;
	arma::mat Sector;
	arma::mat SmallScaleAOA; // n,m
	arma::mat SmallScaleAOD; // n,m
	arma::mat SmallScaleZOA; // n,m
	arma::mat SmallScaleZOD; // n,m
	arma::mat SmallScaleReceiverAntennaGainUH;
	arma::mat SmallScaleReceiverAntennaGainUV;
	arma::mat SmallScaleReceiverAntennaGainXH;
	arma::mat SmallScaleReceiverAntennaGainXV;
	arma::mat RSRPout;
	arma::mat interferenceChannel;
	arma::mat ReceiverAntennaGainLOSUH;
	arma::mat ReceiverAntennaGainLOSUV;
	arma::mat ReceiverAntennaGainLOSXH;
	arma::mat ReceiverAntennaGainLOSXV;
	arma::mat VelocityLOS;
	arma::Mat<int> NumRealCluseter;
	arma::uvec BSindex;	// Strong BS index
	arma::cx_mat CouplingLoss;
	arma::cx_mat TransmitterAntennaGainLOSUH;
	arma::cx_mat TransmitterAntennaGainLOSUV;
	arma::cx_mat TransmitterAntennaGainLOSXH;
	arma::cx_mat TransmitterAntennaGainLOSXV;
	arma::cx_mat SmallScaleTransmitterAntennaGainUH;
	arma::cx_mat SmallScaleTransmitterAntennaGainUV;
	arma::cx_mat SmallScaleTransmitterAntennaGainXH;
	arma::cx_mat SmallScaleTransmitterAntennaGainXV;
	arma::field<arma::mat> Velocity;
	arma::field<arma::mat> VelocityBS;
	arma::field<arma::mat> tau;
	arma::field<arma::mat> tauLOS;
	arma::field<arma::cx_mat> DftParameter;
	arma::field<arma::cx_mat> FrequencyChannel;
	arma::field<arma::cx_mat> F_urd_LOS;
	arma::field<arma::cx_mat> F_prd_LOS;
	arma::field<arma::cx_mat> Alpha_zero_temp;
	arma::field<arma::cx_mat> Alpha_zero_temp_x;
	arma::field<arma::cx_mat> Alpha_zero_temp1;
	arma::field<arma::cx_mat> Alpha_zero_temp_x1;
	arma::field<arma::cx_mat> Alpha_nmup_temp;
	arma::field<arma::cx_mat> Alpha_nmup_temp_x;
	arma::field<arma::cx_mat> Alpha_nmup_temp1;
	arma::field<arma::cx_mat> Alpha_nmup_temp_x1;
	arma::field<arma::cx_mat> F_urd;
	arma::field<arma::cx_mat> F_urd_BS;
	arma::field<arma::cx_mat> F_prd;
	arma::field<arma::cx_mat> F_prd_BS;
	arma::field<arma::cx_mat> AlphaRayU0;
	arma::field<arma::cx_mat> AlphaRayX0;
	arma::field<arma::cx_mat> AlphaRayU1;
	arma::field<arma::cx_mat> AlphaRayX1;
	arma::field<arma::cx_mat> HtLOS;
	arma::field<arma::cx_mat> Ht;


// Channel Demo
	arma::field<arma::mat> DemoAOA;
	arma::field<arma::mat> DemoAOD;
	arma::field<arma::mat> DemoClusterPower;

};


#endif