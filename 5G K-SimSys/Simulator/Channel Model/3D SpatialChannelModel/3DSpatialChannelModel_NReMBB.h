/****************************************************************************

3D Spatial Channel Model header (NR eMBB)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : 3DSpatialChannelModel_NReMBB.h
DATE         : 2017.7.16
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.7.16   Jaewon Lee      Created
2018.1.31   Minsig Han		Trimmed

===========================================================================*/

#ifndef SPATIALCHANNELMODEL_H
#define SPATIALCHANNELMODEL_H

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

enum channelCondition {
	LOS,
	NLOS
};

//Large Scale Parameter
typedef struct {
	double sigmaShadowing;
	double muRiceanK;
	double sigmaRiceanK;
	double muDelaySpread;
	double epsilonDelaySpread;
	double muASD;
	double epsilonASD;
	double muASA;
	double epsilonASA;
	double muZSD;
	double epsilonZSD;
	double muZSA;
	double epsilonZSA;

	double ASDvsDS;
	double ASAvsDS;
	double ASAvsSF;
	double ASDvsSF;
	double DSvsSF;
	double ASDvsASA;
	double ASDvsK;
	double ASAvsK;
	double DSvsK;
	double SFvsK;

	double ZSDvsSF;
	double ZSAvsSF;
	double ZSDvsK;
	double ZSAvsK;
	double ZSDvsDS;
	double ZSAvsDS;
	double ZSDvsASD;
	double ZSAvsASD;
	double ZSDvsASA;
	double ZSAvsASA;
	double ZSDvsZSA;

	double delayScalingParameter;
	double muXPR;
	double sigmaXPR;
	double numberOfClusters;
	double numberOfRaysPerClusters;
	double cluserDS;
	double cluserASD;
	double cluserASA;
	double cluserZSA;
	double perClusterShadowing;
} LargeScaleParmeter;

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

class SpatialChannel
{
public:
	int a;
	LargeScaleParmeter UrbanMicroCellLOS;
	LargeScaleParmeter UrbanMicroCellNLOS;
	LargeScaleParmeter UrbanMicroCellOtoI;

	LargeScaleParmeter UrbanMacroCellLOS;
	LargeScaleParmeter UrbanMacroCellNLOS;
	LargeScaleParmeter UrbanMacroCellOtoI;

	LargeScaleParmeter IndoorOfficeLOS;
	LargeScaleParmeter IndoorOfficeNLOS;

	LargeScaleParmeter RuralMacroCellLOS;
	LargeScaleParmeter RuralMacroCellNLOS;
	LargeScaleParmeter RuralMacroCellOtoI;

// Channel Level 2 functions
	void SmallScaleParameter(int msID, int bsID, int site, int sector);
	void GeneralParameters(int msID, int site);
	void CoefficientGeneration(int msID, int bs, int site, int sector);
	void RSRP(int msID, int bs, int site, int sector);
	void ChannelCoefficient(int msID);
	void ApplyPathLossAndShadowing(int msID);
	void DftParameterSetting(int msID);
	void DiscreteFourierTransform(int msID);
	 
// Channel Level 3 functions - actual channel implementations (36.873)
	void Pathloss(int src, int dst);
	void Delay(int src);
	void ClusterPower(int src, int dst);
	void ArrivalAndDepartureAngle(int src, int bs, int site, int sector);
	void ArrivalAndDepartureAntennaGain(int src, int bs, int site, int sector);
	double AntennaGain(arma::mat angleLCS);
	arma::mat ReceiverAntennaGain(int src, int zeta, arma::mat angleGCS);
	arma::cx_mat TransmitterAntennaGain(int src, double alpha, double beta, double gamma, double zeta, arma::mat angleGCS, int i, int numProcess);
	arma::cx_mat exp_F_urd(int src, arma::mat A, int numRxAntenna);
	arma::cx_mat exp_F_prd(int src, double alpha, double beta, double gamma, arma::mat angleGCS, int numTxHorizontalAntenna, int numTxVerticalAntenna, int numTxPort);

	// Channel Level 4 functions - basic functions	
	double Distance2D(double srcX, double srcY, double bsX, double bsY);
	double Distance3D(double srcX, double srcY, double srcZ, double bsX, double bsY, double bsZ);
	double AzimuthAngleOfGlobalCoordinateSystem(double srcX, double srcY, double dstX, double dstY);
	double ZenithAngleOfGlobalCoordinateSystem(double srcX, double srcY, double srcZ, double dstX, double dstY, double dstZ);
	arma::mat GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(double alpha, double beta, double gamma, arma::mat angleGCS);
	arma::mat LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(double alpha, double beta, double gamma, double theta, double pi, arma::mat antennaGain);
	arma::mat DistanceAngular(double a, double b, double c, double x, double y, double z);
	double Modulo(double a, double b);
	void Initialize(); // Initialization
};

#endif