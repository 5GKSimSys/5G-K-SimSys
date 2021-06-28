/****************************************************************************

Channel Model (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : SpatialChannel_NReMBB.cpp
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

#include "3DSpatialChannelModel_NReMBB.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         LOCAL VARIABLE DECLARATION                      */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void SpatialChannel::Initialize()
{
#ifdef NReMBB_UrbanMacroCell
	UrbanMacroCellLOS.sigmaShadowing = 4;
	UrbanMacroCellLOS.muRiceanK = 9;
	UrbanMacroCellLOS.sigmaRiceanK = 3.5;
	UrbanMacroCellLOS.muDelaySpread = -6.955 - 0.0963 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellLOS.epsilonDelaySpread = 0.66;
	UrbanMacroCellLOS.muASD = 1.06 + 0.1114 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellLOS.epsilonASD = 0.28;
	UrbanMacroCellLOS.muASA = 1.81;
	UrbanMacroCellLOS.epsilonASA = 0.20;
	UrbanMacroCellLOS.muZSD = 0;
	UrbanMacroCellLOS.epsilonZSD = 0.4;
	UrbanMacroCellLOS.muZSA = 0.95;
	UrbanMacroCellLOS.epsilonZSA = 0.16;
	UrbanMacroCellLOS.ASDvsDS = 0.4;
	UrbanMacroCellLOS.ASAvsDS = 0.8;
	UrbanMacroCellLOS.ASAvsSF = -0.5;
	UrbanMacroCellLOS.ASDvsSF = -0.5;
	UrbanMacroCellLOS.DSvsSF = -0.4;
	UrbanMacroCellLOS.ASDvsASA = 0;
	UrbanMacroCellLOS.ASDvsK = 0;
	UrbanMacroCellLOS.ASAvsK = -0.2;
	UrbanMacroCellLOS.DSvsK = -0.4;
	UrbanMacroCellLOS.SFvsK = 0;
	UrbanMacroCellLOS.ZSDvsSF = 0;
	UrbanMacroCellLOS.ZSAvsSF = -0.8;
	UrbanMacroCellLOS.ZSDvsK = 0;
	UrbanMacroCellLOS.ZSAvsK = 0;
	UrbanMacroCellLOS.ZSDvsDS = -0.2;
	UrbanMacroCellLOS.ZSAvsDS = 0;
	UrbanMacroCellLOS.ZSDvsASD = 0.5;
	UrbanMacroCellLOS.ZSAvsASD = 0;
	UrbanMacroCellLOS.ZSDvsASA = -0.3;
	UrbanMacroCellLOS.ZSAvsASA = 0.4;
	UrbanMacroCellLOS.ZSDvsZSA = 0;
	UrbanMacroCellLOS.delayScalingParameter = 2.5;
	UrbanMacroCellLOS.muXPR = 8;
	UrbanMacroCellLOS.sigmaXPR = 4;
	UrbanMacroCellLOS.numberOfClusters = 12;
	UrbanMacroCellLOS.numberOfRaysPerClusters = 20;
	UrbanMacroCellLOS.cluserDS = max(0.25, 6.5622 - 3.4084 * log10(Sim.channel->NReMBB.carrierFrequency));
	UrbanMacroCellLOS.cluserASD = 5;
	UrbanMacroCellLOS.cluserASA = 11;
	UrbanMacroCellLOS.cluserZSA = 7;
	UrbanMacroCellLOS.perClusterShadowing = 3;
	UrbanMacroCellNLOS.sigmaShadowing = 6;
	UrbanMacroCellNLOS.muRiceanK = 0;
	UrbanMacroCellNLOS.sigmaRiceanK = 0;
	UrbanMacroCellNLOS.muDelaySpread = -6.28 - 0.204 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellNLOS.epsilonDelaySpread = 0.39;
	UrbanMacroCellNLOS.muASD = 1.5 - 0.1144 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellNLOS.epsilonASD = 0.28;
	UrbanMacroCellNLOS.muASA = 2.08 - 0.27 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellNLOS.epsilonASA = 0.11;
	UrbanMacroCellNLOS.muZSD = 0;
	UrbanMacroCellNLOS.epsilonZSD = 0.49;
	UrbanMacroCellNLOS.muZSA = -0.3236 * log10(Sim.channel->NReMBB.carrierFrequency) + 1.512;
	UrbanMacroCellNLOS.epsilonZSA = 0.16;
	UrbanMacroCellNLOS.ASDvsDS = 0.4;
	UrbanMacroCellNLOS.ASAvsDS = 0.6;
	UrbanMacroCellNLOS.ASAvsSF = 0;
	UrbanMacroCellNLOS.ASDvsSF = -0.6;
	UrbanMacroCellNLOS.DSvsSF = -0.4;
	UrbanMacroCellNLOS.ASDvsASA = 0.4;
	UrbanMacroCellNLOS.ASDvsK = 0;
	UrbanMacroCellNLOS.ASAvsK = 0;
	UrbanMacroCellNLOS.DSvsK = 0;
	UrbanMacroCellNLOS.SFvsK = 0;
	UrbanMacroCellNLOS.ZSDvsSF = 0;
	UrbanMacroCellNLOS.ZSAvsSF = -0.4;
	UrbanMacroCellNLOS.ZSDvsK = 0;
	UrbanMacroCellNLOS.ZSAvsK = 0;
	UrbanMacroCellNLOS.ZSDvsDS = -0.5;
	UrbanMacroCellNLOS.ZSAvsDS = 0;
	UrbanMacroCellNLOS.ZSDvsASD = 0.5;
	UrbanMacroCellNLOS.ZSAvsASD = -0.1;
	UrbanMacroCellNLOS.ZSDvsASA = 0;
	UrbanMacroCellNLOS.ZSAvsASA = 0;
	UrbanMacroCellNLOS.ZSDvsZSA = 0;
	UrbanMacroCellNLOS.delayScalingParameter = 2.3;
	UrbanMacroCellNLOS.muXPR = 7;
	UrbanMacroCellNLOS.sigmaXPR = 3;
	UrbanMacroCellNLOS.numberOfClusters = 20;
	UrbanMacroCellNLOS.numberOfRaysPerClusters = 20;
	UrbanMacroCellNLOS.cluserDS = max(0.25, 6.5622 - 3.4084 * log10(Sim.channel->NReMBB.carrierFrequency));
	UrbanMacroCellNLOS.cluserASD = 2;
	UrbanMacroCellNLOS.cluserASA = 15;
	UrbanMacroCellNLOS.cluserZSA = 7;
	UrbanMacroCellNLOS.perClusterShadowing = 3;
	UrbanMacroCellOtoI.sigmaShadowing = 7;
	UrbanMacroCellOtoI.muRiceanK = 0;
	UrbanMacroCellOtoI.sigmaRiceanK = 0;
	UrbanMacroCellOtoI.muDelaySpread = -6.62;
	UrbanMacroCellOtoI.epsilonDelaySpread = 0.32;
	UrbanMacroCellOtoI.muASD = 1.25;
	UrbanMacroCellOtoI.epsilonASD = 0.42;
	UrbanMacroCellOtoI.muASA = 1.76;
	UrbanMacroCellOtoI.epsilonASA = 0.16;
	UrbanMacroCellOtoI.muZSD = 0;
	UrbanMacroCellOtoI.epsilonZSD = 0;
	UrbanMacroCellOtoI.muZSA = 1.01;
	UrbanMacroCellOtoI.epsilonZSA = 0.43;
	UrbanMacroCellOtoI.ASDvsDS = 0.4;
	UrbanMacroCellOtoI.ASAvsDS = 0.4;
	UrbanMacroCellOtoI.ASAvsSF = 0;
	UrbanMacroCellOtoI.ASDvsSF = 0.2;
	UrbanMacroCellOtoI.DSvsSF = -0.5;
	UrbanMacroCellOtoI.ASDvsASA = 0;
	UrbanMacroCellOtoI.ASDvsK = 0;
	UrbanMacroCellOtoI.ASAvsK = 0;
	UrbanMacroCellOtoI.DSvsK = 0;
	UrbanMacroCellOtoI.SFvsK = 0;
	UrbanMacroCellOtoI.ZSDvsSF = 0;
	UrbanMacroCellOtoI.ZSAvsSF = 0;
	UrbanMacroCellOtoI.ZSDvsK = 0;
	UrbanMacroCellOtoI.ZSAvsK = 0;
	UrbanMacroCellOtoI.ZSDvsDS = -0.6;
	UrbanMacroCellOtoI.ZSAvsDS = -0.2;
	UrbanMacroCellOtoI.ZSDvsASD = -0.2;
	UrbanMacroCellOtoI.ZSAvsASD = 0;
	UrbanMacroCellOtoI.ZSDvsASA = 0;
	UrbanMacroCellOtoI.ZSAvsASA = 0.5;
	UrbanMacroCellOtoI.ZSDvsZSA = 0.5;
	UrbanMacroCellOtoI.delayScalingParameter = 2.2;
	UrbanMacroCellOtoI.muXPR = 9;
	UrbanMacroCellOtoI.sigmaXPR = 5;
	UrbanMacroCellOtoI.numberOfClusters = 12;
	UrbanMacroCellOtoI.numberOfRaysPerClusters = 20;
	UrbanMacroCellOtoI.cluserASD = 11;
	UrbanMacroCellOtoI.cluserASD = 5;
	UrbanMacroCellOtoI.cluserASA = 8;
	UrbanMacroCellOtoI.cluserZSA = 3;
	UrbanMacroCellOtoI.perClusterShadowing = 4;
#endif

#ifdef NReMBB_DenseUrban
	UrbanMacroCellLOS.sigmaShadowing = 4;
	UrbanMacroCellLOS.muRiceanK = 9;
	UrbanMacroCellLOS.sigmaRiceanK = 3.5;
	UrbanMacroCellLOS.muDelaySpread = -6.955 - 0.0963 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellLOS.epsilonDelaySpread = 0.66;
	UrbanMacroCellLOS.muASD = 1.06 + 0.1114 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellLOS.epsilonASD = 0.28;
	UrbanMacroCellLOS.muASA = 1.81;
	UrbanMacroCellLOS.epsilonASA = 0.20;
	UrbanMacroCellLOS.muZSD = 0;
	UrbanMacroCellLOS.epsilonZSD = 0.4;
	UrbanMacroCellLOS.muZSA = 0.95;
	UrbanMacroCellLOS.epsilonZSA = 0.16;
	UrbanMacroCellLOS.ASDvsDS = 0.4;
	UrbanMacroCellLOS.ASAvsDS = 0.8;
	UrbanMacroCellLOS.ASAvsSF = -0.5;
	UrbanMacroCellLOS.ASDvsSF = -0.5;
	UrbanMacroCellLOS.DSvsSF = -0.4;
	UrbanMacroCellLOS.ASDvsASA = 0;
	UrbanMacroCellLOS.ASDvsK = 0;
	UrbanMacroCellLOS.ASAvsK = -0.2;
	UrbanMacroCellLOS.DSvsK = -0.4;
	UrbanMacroCellLOS.SFvsK = 0;
	UrbanMacroCellLOS.ZSDvsSF = 0;
	UrbanMacroCellLOS.ZSAvsSF = -0.8;
	UrbanMacroCellLOS.ZSDvsK = 0;
	UrbanMacroCellLOS.ZSAvsK = 0;
	UrbanMacroCellLOS.ZSDvsDS = -0.2;
	UrbanMacroCellLOS.ZSAvsDS = 0;
	UrbanMacroCellLOS.ZSDvsASD = 0.5;
	UrbanMacroCellLOS.ZSAvsASD = 0;
	UrbanMacroCellLOS.ZSDvsASA = -0.3;
	UrbanMacroCellLOS.ZSAvsASA = 0.4;
	UrbanMacroCellLOS.ZSDvsZSA = 0;
	UrbanMacroCellLOS.delayScalingParameter = 2.5;
	UrbanMacroCellLOS.muXPR = 8;
	UrbanMacroCellLOS.sigmaXPR = 4;
	UrbanMacroCellLOS.numberOfClusters = 12;
	UrbanMacroCellLOS.numberOfRaysPerClusters = 20;
	UrbanMacroCellLOS.cluserDS = max(0.25, 6.5622 - 3.4084 * log10(Sim.channel->NReMBB.carrierFrequency));
	UrbanMacroCellLOS.cluserASD = 5;
	UrbanMacroCellLOS.cluserASA = 11;
	UrbanMacroCellLOS.cluserZSA = 7;
	UrbanMacroCellLOS.perClusterShadowing = 3;
	UrbanMacroCellNLOS.sigmaShadowing = 6;
	UrbanMacroCellNLOS.muRiceanK = 0;
	UrbanMacroCellNLOS.sigmaRiceanK = 0;
	UrbanMacroCellNLOS.muDelaySpread = -6.28 - 0.204 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellNLOS.epsilonDelaySpread = 0.39;
	UrbanMacroCellNLOS.muASD = 1.5 - 0.1144 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellNLOS.epsilonASD = 0.28;
	UrbanMacroCellNLOS.muASA = 2.08 - 0.27 * log10(Sim.channel->NReMBB.carrierFrequency);
	UrbanMacroCellNLOS.epsilonASA = 0.11;
	UrbanMacroCellNLOS.muZSD = 0;
	UrbanMacroCellNLOS.epsilonZSD = 0.49;
	UrbanMacroCellNLOS.muZSA = -0.3236 * log10(Sim.channel->NReMBB.carrierFrequency) + 1.512;
	UrbanMacroCellNLOS.epsilonZSA = 0.16;
	UrbanMacroCellNLOS.ASDvsDS = 0.4;
	UrbanMacroCellNLOS.ASAvsDS = 0.6;
	UrbanMacroCellNLOS.ASAvsSF = 0;
	UrbanMacroCellNLOS.ASDvsSF = -0.6;
	UrbanMacroCellNLOS.DSvsSF = -0.4;
	UrbanMacroCellNLOS.ASDvsASA = 0.4;
	UrbanMacroCellNLOS.ASDvsK = 0;
	UrbanMacroCellNLOS.ASAvsK = 0;
	UrbanMacroCellNLOS.DSvsK = 0;
	UrbanMacroCellNLOS.SFvsK = 0;
	UrbanMacroCellNLOS.ZSDvsSF = 0;
	UrbanMacroCellNLOS.ZSAvsSF = -0.4;
	UrbanMacroCellNLOS.ZSDvsK = 0;
	UrbanMacroCellNLOS.ZSAvsK = 0;
	UrbanMacroCellNLOS.ZSDvsDS = -0.5;
	UrbanMacroCellNLOS.ZSAvsDS = 0;
	UrbanMacroCellNLOS.ZSDvsASD = 0.5;
	UrbanMacroCellNLOS.ZSAvsASD = -0.1;
	UrbanMacroCellNLOS.ZSDvsASA = 0;
	UrbanMacroCellNLOS.ZSAvsASA = 0;
	UrbanMacroCellNLOS.ZSDvsZSA = 0;
	UrbanMacroCellNLOS.delayScalingParameter = 2.3;
	UrbanMacroCellNLOS.muXPR = 7;
	UrbanMacroCellNLOS.sigmaXPR = 3;
	UrbanMacroCellNLOS.numberOfClusters = 20;
	UrbanMacroCellNLOS.numberOfRaysPerClusters = 20;
	UrbanMacroCellNLOS.cluserDS = max(0.25, 6.5622 - 3.4084 * log10(Sim.channel->NReMBB.carrierFrequency));
	UrbanMacroCellNLOS.cluserASD = 2;
	UrbanMacroCellNLOS.cluserASA = 15;
	UrbanMacroCellNLOS.cluserZSA = 7;
	UrbanMacroCellNLOS.perClusterShadowing = 3;
	UrbanMacroCellOtoI.sigmaShadowing = 7;
	UrbanMacroCellOtoI.muRiceanK = 0;
	UrbanMacroCellOtoI.sigmaRiceanK = 0;
	UrbanMacroCellOtoI.muDelaySpread = -6.62;
	UrbanMacroCellOtoI.epsilonDelaySpread = 0.32;
	UrbanMacroCellOtoI.muASD = 1.25;
	UrbanMacroCellOtoI.epsilonASD = 0.42;
	UrbanMacroCellOtoI.muASA = 1.76;
	UrbanMacroCellOtoI.epsilonASA = 0.16;
	UrbanMacroCellOtoI.muZSD = 0;
	UrbanMacroCellOtoI.epsilonZSD = 0;
	UrbanMacroCellOtoI.muZSA = 1.01;
	UrbanMacroCellOtoI.epsilonZSA = 0.43;
	UrbanMacroCellOtoI.ASDvsDS = 0.4;
	UrbanMacroCellOtoI.ASAvsDS = 0.4;
	UrbanMacroCellOtoI.ASAvsSF = 0;
	UrbanMacroCellOtoI.ASDvsSF = 0.2;
	UrbanMacroCellOtoI.DSvsSF = -0.5;
	UrbanMacroCellOtoI.ASDvsASA = 0;
	UrbanMacroCellOtoI.ASDvsK = 0;
	UrbanMacroCellOtoI.ASAvsK = 0;
	UrbanMacroCellOtoI.DSvsK = 0;
	UrbanMacroCellOtoI.SFvsK = 0;
	UrbanMacroCellOtoI.ZSDvsSF = 0;
	UrbanMacroCellOtoI.ZSAvsSF = 0;
	UrbanMacroCellOtoI.ZSDvsK = 0;
	UrbanMacroCellOtoI.ZSAvsK = 0;
	UrbanMacroCellOtoI.ZSDvsDS = -0.6;
	UrbanMacroCellOtoI.ZSAvsDS = -0.2;
	UrbanMacroCellOtoI.ZSDvsASD = -0.2;
	UrbanMacroCellOtoI.ZSAvsASD = 0;
	UrbanMacroCellOtoI.ZSDvsASA = 0;
	UrbanMacroCellOtoI.ZSAvsASA = 0.5;
	UrbanMacroCellOtoI.ZSDvsZSA = 0.5;
	UrbanMacroCellOtoI.delayScalingParameter = 2.2;
	UrbanMacroCellOtoI.muXPR = 9;
	UrbanMacroCellOtoI.sigmaXPR = 5;
	UrbanMacroCellOtoI.numberOfClusters = 12;
	UrbanMacroCellOtoI.numberOfRaysPerClusters = 20;
	UrbanMacroCellOtoI.cluserASD = 11;
	UrbanMacroCellOtoI.cluserASD = 5;
	UrbanMacroCellOtoI.cluserASA = 8;
	UrbanMacroCellOtoI.cluserZSA = 3;
	UrbanMacroCellOtoI.perClusterShadowing = 4;

	UrbanMicroCellLOS.sigmaShadowing = 4;
	UrbanMicroCellLOS.muRiceanK = 9;
	UrbanMicroCellLOS.sigmaRiceanK = 5;
	UrbanMicroCellLOS.muDelaySpread = -0.24 * log10(1 + Sim.channel->NReMBB.carrierFrequency) - 7.14;
	UrbanMicroCellLOS.epsilonDelaySpread = 0.38;
	UrbanMicroCellLOS.muASD = -0.05 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.21;
	UrbanMicroCellLOS.epsilonASD = 0.41;
	UrbanMicroCellLOS.muASA = -0.08 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.73;
	UrbanMicroCellLOS.epsilonASA = 0.014 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.28;
	UrbanMicroCellLOS.muZSD = 0;
	UrbanMicroCellLOS.epsilonZSD = 0.35;
	UrbanMicroCellLOS.muZSA = -0.1 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.73;
	UrbanMicroCellLOS.epsilonZSA = -0.04 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.34;
	UrbanMicroCellLOS.ASDvsDS = 0.5;
	UrbanMicroCellLOS.ASAvsDS = 0.8;
	UrbanMicroCellLOS.ASAvsSF = -0.4;
	UrbanMicroCellLOS.ASDvsSF = -0.5;
	UrbanMicroCellLOS.DSvsSF = -0.4;
	UrbanMicroCellLOS.ASDvsASA = 0.4;
	UrbanMicroCellLOS.ASDvsK = -0.2;
	UrbanMicroCellLOS.ASAvsK = -0.3;
	UrbanMicroCellLOS.DSvsK = -0.7;
	UrbanMicroCellLOS.SFvsK = 0.5;
	UrbanMicroCellLOS.ZSDvsSF = 0;
	UrbanMicroCellLOS.ZSAvsSF = 0;
	UrbanMicroCellLOS.ZSDvsK = 0;
	UrbanMicroCellLOS.ZSAvsK = 0;
	UrbanMicroCellLOS.ZSDvsDS = 0;
	UrbanMicroCellLOS.ZSAvsDS = 0.2;
	UrbanMicroCellLOS.ZSDvsASD = 0.5;
	UrbanMicroCellLOS.ZSAvsASD = 0.3;
	UrbanMicroCellLOS.ZSDvsASA = 0;
	UrbanMicroCellLOS.ZSAvsASA = 0;
	UrbanMicroCellLOS.ZSDvsZSA = 0;
	UrbanMicroCellLOS.delayScalingParameter = 3;
	UrbanMicroCellLOS.muXPR = 9;
	UrbanMicroCellLOS.sigmaXPR = 3;
	UrbanMicroCellLOS.numberOfClusters = 12;
	UrbanMicroCellLOS.numberOfRaysPerClusters = 20;
	UrbanMicroCellLOS.cluserDS = 5;
	UrbanMicroCellLOS.cluserASD = 3;
	UrbanMicroCellLOS.cluserASA = 17;
	UrbanMicroCellLOS.cluserZSA = 7;
	UrbanMicroCellLOS.perClusterShadowing = 3;
	UrbanMicroCellNLOS.sigmaShadowing = 7.82;
	UrbanMicroCellNLOS.muRiceanK = 0;
	UrbanMicroCellNLOS.sigmaRiceanK = 0;
	UrbanMicroCellNLOS.muDelaySpread = -0.24 * log10(1 + Sim.channel->NReMBB.carrierFrequency) - 6.83;
	UrbanMicroCellNLOS.epsilonDelaySpread = 0.16 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.28;
	UrbanMicroCellNLOS.muASD = -0.23 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.53;
	UrbanMicroCellNLOS.epsilonASD = 0.11 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.33;
	UrbanMicroCellNLOS.muASA = -0.08 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.81;
	UrbanMicroCellNLOS.epsilonASA = 0.05 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.3;
	UrbanMicroCellNLOS.muZSD = 0;
	UrbanMicroCellNLOS.epsilonZSD = 0.35;
	UrbanMicroCellNLOS.muZSA = -0.04 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.92;
	UrbanMicroCellNLOS.epsilonZSA = -0.07 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.41;
	UrbanMicroCellNLOS.ASDvsDS = 0;
	UrbanMicroCellNLOS.ASAvsDS = 0.4;
	UrbanMicroCellNLOS.ASAvsSF = -0.4;
	UrbanMicroCellNLOS.ASDvsSF = 0;
	UrbanMicroCellNLOS.DSvsSF = -0.7;
	UrbanMicroCellNLOS.ASDvsASA = 0;
	UrbanMicroCellNLOS.ASDvsK = 0;
	UrbanMicroCellNLOS.ASAvsK = 0;
	UrbanMicroCellNLOS.DSvsK = 0;
	UrbanMicroCellNLOS.SFvsK = 0;
	UrbanMicroCellNLOS.ZSDvsSF = 0;
	UrbanMicroCellNLOS.ZSAvsSF = 0;
	UrbanMicroCellNLOS.ZSDvsK = 0;
	UrbanMicroCellNLOS.ZSAvsK = 0;
	UrbanMicroCellNLOS.ZSDvsDS = -0.5;
	UrbanMicroCellNLOS.ZSAvsDS = 0;
	UrbanMicroCellNLOS.ZSDvsASD = 0.5;
	UrbanMicroCellNLOS.ZSAvsASD = 0.5;
	UrbanMicroCellNLOS.ZSDvsASA = 0;
	UrbanMicroCellNLOS.ZSAvsASA = 0.2;
	UrbanMicroCellNLOS.ZSDvsZSA = 0;
	UrbanMicroCellNLOS.delayScalingParameter = 2.1;
	UrbanMicroCellNLOS.muXPR = 8.0;
	UrbanMicroCellNLOS.sigmaXPR = 3;
	UrbanMicroCellNLOS.numberOfClusters = 19;
	UrbanMicroCellNLOS.numberOfRaysPerClusters = 20;
	UrbanMicroCellNLOS.cluserDS = 11;
	UrbanMicroCellNLOS.cluserASD = 10;
	UrbanMicroCellNLOS.cluserASA = 22;
	UrbanMicroCellNLOS.cluserZSA = 7;
	UrbanMicroCellNLOS.perClusterShadowing = 3;
	UrbanMicroCellOtoI.sigmaShadowing = 7;
	UrbanMicroCellOtoI.muRiceanK = 0;
	UrbanMicroCellOtoI.sigmaRiceanK = 0;
	UrbanMicroCellOtoI.muDelaySpread = -6.62;
	UrbanMicroCellOtoI.epsilonDelaySpread = 0.32;
	UrbanMicroCellOtoI.muASD = 1.25;
	UrbanMicroCellOtoI.epsilonASD = 0.42;
	UrbanMicroCellOtoI.muASA = 1.76;
	UrbanMicroCellOtoI.epsilonASA = 0.16;
	UrbanMicroCellOtoI.muZSD = 0;
	UrbanMicroCellOtoI.epsilonZSD = 0;
	UrbanMicroCellOtoI.muZSA = 1.01;
	UrbanMicroCellOtoI.epsilonZSA = 0.43;
	UrbanMicroCellOtoI.ASDvsDS = 0.4;
	UrbanMicroCellOtoI.ASAvsDS = 0.4;
	UrbanMicroCellOtoI.ASAvsSF = 0;
	UrbanMicroCellOtoI.ASDvsSF = 0.2;
	UrbanMicroCellOtoI.DSvsSF = -0.5;
	UrbanMicroCellOtoI.ASDvsASA = 0;
	UrbanMicroCellOtoI.ASDvsK = 0;
	UrbanMicroCellOtoI.ASAvsK = 0;
	UrbanMicroCellOtoI.DSvsK = 0;
	UrbanMicroCellOtoI.SFvsK = 0;
	UrbanMicroCellOtoI.ZSDvsSF = 0;
	UrbanMicroCellOtoI.ZSAvsSF = 0;
	UrbanMicroCellOtoI.ZSDvsK = 0;
	UrbanMicroCellOtoI.ZSAvsK = 0;
	UrbanMicroCellOtoI.ZSDvsDS = -0.6;
	UrbanMicroCellOtoI.ZSAvsDS = -0.2;
	UrbanMicroCellOtoI.ZSDvsASD = -0.2;
	UrbanMicroCellOtoI.ZSAvsASD = 0;
	UrbanMicroCellOtoI.ZSDvsASA = 0;
	UrbanMicroCellOtoI.ZSAvsASA = 0.5;
	UrbanMicroCellOtoI.ZSDvsZSA = 0.5;
	UrbanMicroCellOtoI.delayScalingParameter = 2.2;
	UrbanMicroCellOtoI.muXPR = 9;
	UrbanMicroCellOtoI.sigmaXPR = 5;
	UrbanMicroCellOtoI.numberOfClusters = 12;
	UrbanMicroCellOtoI.numberOfRaysPerClusters = 20;
	UrbanMicroCellOtoI.cluserDS = 11;
	UrbanMicroCellOtoI.cluserASD = 5;
	UrbanMicroCellOtoI.cluserASA = 8;
	UrbanMicroCellOtoI.cluserZSA = 3;
	UrbanMicroCellOtoI.perClusterShadowing = 4;
#endif

#ifdef NReMBB_IndoorOffice
	IndoorOfficeLOS.sigmaShadowing = 3;
	IndoorOfficeLOS.muRiceanK = 7;
	IndoorOfficeLOS.sigmaRiceanK = 4;
	IndoorOfficeLOS.muDelaySpread = -0.01 * log10(1 + Sim.channel->NReMBB.carrierFrequency) - 7.692;
	IndoorOfficeLOS.epsilonDelaySpread = 0.18;
	IndoorOfficeLOS.muASD = 1.60;
	IndoorOfficeLOS.epsilonASD = 0.18;
	IndoorOfficeLOS.muASA = -0.19 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.781;
	IndoorOfficeLOS.epsilonASA = 0.12 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.119;
	IndoorOfficeLOS.muZSD = -1.43 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 2.228;
	IndoorOfficeLOS.epsilonZSD = 0.13 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.30;
	IndoorOfficeLOS.muZSA = -0.26 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.44;
	IndoorOfficeLOS.epsilonZSA = -0.04 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.264;
	IndoorOfficeLOS.ASDvsDS = 0.6;
	IndoorOfficeLOS.ASAvsDS = 0.8;
	IndoorOfficeLOS.ASAvsSF = -0.5;
	IndoorOfficeLOS.ASDvsSF = -0.4;
	IndoorOfficeLOS.DSvsSF = -0.8;
	IndoorOfficeLOS.ASDvsASA = 0.4;
	IndoorOfficeLOS.ASDvsK = 0;
	IndoorOfficeLOS.ASAvsK = 0;
	IndoorOfficeLOS.DSvsK = -0.5;
	IndoorOfficeLOS.SFvsK = 0.5;
	IndoorOfficeLOS.ZSDvsSF = 0.2;
	IndoorOfficeLOS.ZSAvsSF = 0.3;
	IndoorOfficeLOS.ZSDvsK = 0;
	IndoorOfficeLOS.ZSAvsK = 0.1;
	IndoorOfficeLOS.ZSDvsDS = 0.1;
	IndoorOfficeLOS.ZSAvsDS = 0.2;
	IndoorOfficeLOS.ZSDvsASD = 0.5;
	IndoorOfficeLOS.ZSAvsASD = 0;
	IndoorOfficeLOS.ZSDvsASA = 0;
	IndoorOfficeLOS.ZSAvsASA = 0.5;
	IndoorOfficeLOS.ZSDvsZSA = 0;
	IndoorOfficeLOS.delayScalingParameter = 3.6;
	IndoorOfficeLOS.muXPR = 11;
	IndoorOfficeLOS.sigmaXPR = 4;
	IndoorOfficeLOS.numberOfClusters = 12;
	IndoorOfficeLOS.numberOfRaysPerClusters = 20;
	IndoorOfficeLOS.cluserDS = 0;
	IndoorOfficeLOS.cluserASD = 5;
	IndoorOfficeLOS.cluserASA = 8;
	IndoorOfficeLOS.cluserZSA = 9;
	IndoorOfficeLOS.perClusterShadowing = 6;
	IndoorOfficeNLOS.sigmaShadowing = 8.03;
	IndoorOfficeNLOS.muRiceanK = 0;
	IndoorOfficeNLOS.sigmaRiceanK = 0;
	IndoorOfficeNLOS.muDelaySpread = -0.28 * log10(1 + Sim.channel->NReMBB.carrierFrequency) - 7.173;
	IndoorOfficeNLOS.epsilonDelaySpread = 0.10 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.055;
	IndoorOfficeNLOS.muASD = 1.62;
	IndoorOfficeNLOS.epsilonASD = 0.25;
	IndoorOfficeNLOS.muASA = -0.11 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.863;
	IndoorOfficeNLOS.epsilonASA = 0.12 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.059;
	IndoorOfficeNLOS.muZSD = 1.08;
	IndoorOfficeNLOS.epsilonZSD = 0.36;
	IndoorOfficeNLOS.muZSA = -0.15 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 1.387;
	IndoorOfficeNLOS.epsilonZSA = -0.09 * log10(1 + Sim.channel->NReMBB.carrierFrequency) + 0.746;
	IndoorOfficeNLOS.ASDvsDS = 0.4;
	IndoorOfficeNLOS.ASAvsDS = 0;
	IndoorOfficeNLOS.ASAvsSF = -0.4;
	IndoorOfficeNLOS.ASDvsSF = 0;
	IndoorOfficeNLOS.DSvsSF = -0.5;
	IndoorOfficeNLOS.ASDvsASA = 0;
	IndoorOfficeNLOS.ASDvsK = 0;
	IndoorOfficeNLOS.ASAvsK = 0;
	IndoorOfficeNLOS.DSvsK = 0;
	IndoorOfficeNLOS.SFvsK = 0;
	IndoorOfficeNLOS.ZSDvsSF = 0;
	IndoorOfficeNLOS.ZSAvsSF = 0;
	IndoorOfficeNLOS.ZSDvsK = 0;
	IndoorOfficeNLOS.ZSAvsK = 0;
	IndoorOfficeNLOS.ZSDvsDS = -0.27;
	IndoorOfficeNLOS.ZSAvsDS = -0.06;
	IndoorOfficeNLOS.ZSDvsASD = 0.35;
	IndoorOfficeNLOS.ZSAvsASD = 0.23;
	IndoorOfficeNLOS.ZSDvsASA = -0.08;
	IndoorOfficeNLOS.ZSAvsASA = 0.43;
	IndoorOfficeNLOS.ZSDvsZSA = 0.42;
	IndoorOfficeNLOS.delayScalingParameter = 3;
	IndoorOfficeNLOS.muXPR = 10;
	IndoorOfficeNLOS.sigmaXPR = 4;
	IndoorOfficeNLOS.numberOfClusters = 19;
	IndoorOfficeNLOS.numberOfRaysPerClusters = 20;
	IndoorOfficeNLOS.cluserDS = 0;
	IndoorOfficeNLOS.cluserASD = 5;
	IndoorOfficeNLOS.cluserASA = 11;
	IndoorOfficeNLOS.cluserZSA = 9;
	IndoorOfficeNLOS.perClusterShadowing = 3;
#endif

#ifdef NReMBB_RuralMacroCell
	RuralMacroCellLOS.sigmaShadowing = 4;
	RuralMacroCellLOS.muRiceanK = 7;
	RuralMacroCellLOS.sigmaRiceanK = 4;
	RuralMacroCellLOS.muDelaySpread = -7.49;
	RuralMacroCellLOS.epsilonDelaySpread = 0.55;
	RuralMacroCellLOS.muASD = 0.90;
	RuralMacroCellLOS.epsilonASD = 0.38;
	RuralMacroCellLOS.muASA = 1.52;
	RuralMacroCellLOS.epsilonASA = 0.24;
	RuralMacroCellLOS.muZSD = 0;
	RuralMacroCellLOS.epsilonZSD = 0.34;
	RuralMacroCellLOS.muZSA = 0.47;
	RuralMacroCellLOS.epsilonZSA = 0.40;
	RuralMacroCellLOS.ASDvsDS = 0;
	RuralMacroCellLOS.ASAvsDS = 0;
	RuralMacroCellLOS.ASAvsSF = 0;
	RuralMacroCellLOS.ASDvsSF = 0;
	RuralMacroCellLOS.DSvsSF = -0.5;
	RuralMacroCellLOS.ASDvsASA = 0;
	RuralMacroCellLOS.ASDvsK = 0;
	RuralMacroCellLOS.ASAvsK = 0;
	RuralMacroCellLOS.DSvsK = 0;
	RuralMacroCellLOS.SFvsK = 0;
	RuralMacroCellLOS.ZSDvsSF = 0.01;
	RuralMacroCellLOS.ZSAvsSF = -0.17;
	RuralMacroCellLOS.ZSDvsK = 0;
	RuralMacroCellLOS.ZSAvsK = -0.02;
	RuralMacroCellLOS.ZSDvsDS = -0.05;
	RuralMacroCellLOS.ZSAvsDS = 0.27;
	RuralMacroCellLOS.ZSDvsASD = 0.73;
	RuralMacroCellLOS.ZSAvsASD = -0.14;
	RuralMacroCellLOS.ZSDvsASA = -0.20;
	RuralMacroCellLOS.ZSAvsASA = 0.24;
	RuralMacroCellLOS.ZSDvsZSA = -0.07;
	RuralMacroCellLOS.delayScalingParameter = 3.8;
	RuralMacroCellLOS.muXPR = 12;
	RuralMacroCellLOS.sigmaXPR = 4;
	RuralMacroCellLOS.numberOfClusters = 11;
	RuralMacroCellLOS.numberOfRaysPerClusters = 20;
	RuralMacroCellLOS.cluserDS = 0;
	RuralMacroCellLOS.cluserASD = 2;
	RuralMacroCellLOS.cluserASA = 3;
	RuralMacroCellLOS.cluserZSA = 3;
	RuralMacroCellLOS.perClusterShadowing = 3;
	RuralMacroCellNLOS.sigmaShadowing = 8;
	RuralMacroCellNLOS.muRiceanK = 0;
	RuralMacroCellNLOS.sigmaRiceanK = 0;
	RuralMacroCellNLOS.muDelaySpread = -7.43;
	RuralMacroCellNLOS.epsilonDelaySpread = 0.48;
	RuralMacroCellNLOS.muASD = 0.95;
	RuralMacroCellNLOS.epsilonASD = 0.45;
	RuralMacroCellNLOS.muASA = 1.52;
	RuralMacroCellNLOS.epsilonASA = 0.13;
	RuralMacroCellNLOS.muZSD = 0;
	RuralMacroCellNLOS.epsilonZSD = 0.30;
	RuralMacroCellNLOS.muZSA = 0.58;
	RuralMacroCellNLOS.epsilonZSA = 0.37;
	RuralMacroCellNLOS.ASDvsDS = -0.4;
	RuralMacroCellNLOS.ASAvsDS = 0;
	RuralMacroCellNLOS.ASAvsSF = 0;
	RuralMacroCellNLOS.ASDvsSF = 0.6;
	RuralMacroCellNLOS.DSvsSF = -0.5;
	RuralMacroCellNLOS.ASDvsASA = 0;
	RuralMacroCellNLOS.ASDvsK = 0;
	RuralMacroCellNLOS.ASAvsK = 0;
	RuralMacroCellNLOS.DSvsK = 0;
	RuralMacroCellNLOS.SFvsK = 0;
	RuralMacroCellNLOS.ZSDvsSF = -0.04;
	RuralMacroCellNLOS.ZSAvsSF = -0.25;
	RuralMacroCellNLOS.ZSDvsK = 0;
	RuralMacroCellNLOS.ZSAvsK = 0;
	RuralMacroCellNLOS.ZSDvsDS = -0.10;
	RuralMacroCellNLOS.ZSAvsDS = -0.40;
	RuralMacroCellNLOS.ZSDvsASD = 0.42;
	RuralMacroCellNLOS.ZSAvsASD = -0.27;
	RuralMacroCellNLOS.ZSDvsASA = -0.18;
	RuralMacroCellNLOS.ZSAvsASA = 0.26;
	RuralMacroCellNLOS.ZSDvsZSA = -0.27;
	RuralMacroCellNLOS.delayScalingParameter = 1.7;
	RuralMacroCellNLOS.muXPR = 7;
	RuralMacroCellNLOS.sigmaXPR = 3;
	RuralMacroCellNLOS.numberOfClusters = 10;
	RuralMacroCellNLOS.numberOfRaysPerClusters = 20;
	RuralMacroCellNLOS.cluserDS = 0;
	RuralMacroCellNLOS.cluserASD = 2;
	RuralMacroCellNLOS.cluserASA = 3;
	RuralMacroCellNLOS.cluserZSA = 3;
	RuralMacroCellNLOS.perClusterShadowing = 3;
	RuralMacroCellOtoI.sigmaShadowing = 8;
	RuralMacroCellOtoI.muRiceanK = 0;
	RuralMacroCellOtoI.sigmaRiceanK = 0;
	RuralMacroCellOtoI.muDelaySpread = -7.47;
	RuralMacroCellOtoI.epsilonDelaySpread = 0.24;
	RuralMacroCellOtoI.muASD = 0.67;
	RuralMacroCellOtoI.epsilonASD = 0.18;
	RuralMacroCellOtoI.muASA = 1.66;
	RuralMacroCellOtoI.epsilonASA = 0.21;
	RuralMacroCellOtoI.muZSD = 0;
	RuralMacroCellOtoI.epsilonZSD = 0.30;
	RuralMacroCellOtoI.muZSA = 0.93;
	RuralMacroCellOtoI.epsilonZSA = 0.22;
	RuralMacroCellOtoI.ASDvsDS = 0;
	RuralMacroCellOtoI.ASAvsDS = 0;
	RuralMacroCellOtoI.ASAvsSF = 0;
	RuralMacroCellOtoI.ASDvsSF = 0;
	RuralMacroCellOtoI.DSvsSF = 0;
	RuralMacroCellOtoI.ASDvsASA = -0.7;
	RuralMacroCellOtoI.ASDvsK = 0;
	RuralMacroCellOtoI.ASAvsK = 0;
	RuralMacroCellOtoI.DSvsK = 0;
	RuralMacroCellOtoI.SFvsK = 0;
	RuralMacroCellOtoI.ZSDvsSF = 0;
	RuralMacroCellOtoI.ZSAvsSF = 0;
	RuralMacroCellOtoI.ZSDvsK = 0;
	RuralMacroCellOtoI.ZSAvsK = 0;
	RuralMacroCellOtoI.ZSDvsDS = 0;
	RuralMacroCellOtoI.ZSAvsDS = 0;
	RuralMacroCellOtoI.ZSDvsASD = 0.66;
	RuralMacroCellOtoI.ZSAvsASD = 0.47;
	RuralMacroCellOtoI.ZSDvsASA = -0.55;
	RuralMacroCellOtoI.ZSAvsASA = -0.22;
	RuralMacroCellOtoI.ZSDvsZSA = 0;
	RuralMacroCellOtoI.delayScalingParameter = 1.7;
	RuralMacroCellOtoI.muXPR = 7;
	RuralMacroCellOtoI.sigmaXPR = 3;
	RuralMacroCellOtoI.numberOfClusters = 10;
	RuralMacroCellOtoI.numberOfRaysPerClusters = 20;
	RuralMacroCellOtoI.cluserDS = 0;
	RuralMacroCellOtoI.cluserASD = 2;
	RuralMacroCellOtoI.cluserASA = 3;
	RuralMacroCellOtoI.cluserZSA = 3;
	RuralMacroCellOtoI.perClusterShadowing = 3;
#endif
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         Level 3 Functions                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SpatialChannel::Pathloss(int src, int dst) {
	int channelModel = Sim.channel->ChannelModel;
	double distance2D = MS[src]->channel->distance2D;
	double distance3D = MS[src]->channel->distance3D;

	double indoorDistance2D, outdoorDistance2D, pathlossLOS, pathlossNLOS, gdistance2D, cdistance2D, losProbability;
	double srcZ = MS[src]->network->pos3D(0,2), dstZ = BS[dst]->network->pos3D(0, 2);
	double breakPointDistance2D = 4.0 * (dstZ - 1.0) * (srcZ - 1.0) * (Sim.channel->NReMBB.carrierFrequency*1e9) / 3e8;

	// Indoor distance & Outdoor distance
	indoorDistance2D = MS[src]->network->indoorDistance2D; // indoor ue case 0~25, outdoor 0
	if (indoorDistance2D > distance2D) {
		outdoorDistance2D = 0;
		indoorDistance2D = distance2D;
	}
	else if (indoorDistance2D <= distance2D) {
		outdoorDistance2D = distance2D - indoorDistance2D;
	}

	// Pathloss model based on TR 38.901
	switch (channelModel)
	{
	case SLS::DenseUrban:
		if (srcZ == 10) // small cell (UMi)
		{
			if (distance2D >= 10 && distance2D <= breakPointDistance2D) {
				pathlossLOS = 32.4 + 21.0 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency);
			}
			else if (breakPointDistance2D < distance2D && distance2D < 5000.0) {
				pathlossLOS = 32.4 + 40.0 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency) - 9.5 * log10(pow(breakPointDistance2D, 2.0) + pow((srcZ - dstZ), 2.0));
			}
			pathlossNLOS = 35.3 * log10(distance3D) + 22.4 + 21.3 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.3 * (dstZ - 1.5);

			if (outdoorDistance2D <= 18)
				losProbability = 1;
			else
				losProbability = 18.0 / outdoorDistance2D + exp(-outdoorDistance2D / 36.0) * (1 - (18.0 / outdoorDistance2D));
		}
		else
		{
			if (distance2D >= 10 && distance2D <= breakPointDistance2D) {
				pathlossLOS = 28.0 + 22.0 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency);
			}
			else if (breakPointDistance2D < distance2D && distance2D < 5000.0) {
				pathlossLOS = 40.0 * log10(distance3D) + 28.0 + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency) - 9.0 * log10(pow(breakPointDistance2D, 2.0) + pow((srcZ - dstZ), 2.0));
			}
			pathlossNLOS = 13.54 + 39.08 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.6 * (dstZ - 1.5);

			// LOS probability cacluation
			if (outdoorDistance2D <= 18)
				losProbability = 1;
			else
			{
				double C;
				if (dstZ <= 13)
					C = 0;
				else
					C = pow((dstZ - 13) / 10, 1.5);
				losProbability = 18.0 / outdoorDistance2D + exp(-outdoorDistance2D / 63.0) * (1 - (18.0 / outdoorDistance2D)) * (1 + C * 5 / 4 * pow(outdoorDistance2D / 100, 3) * exp(-outdoorDistance2D / 150));
			}
		}

		break;

	case SLS::UrbanMacroCell:

		breakPointDistance2D = 4.0 * (dstZ - 1.0) * (srcZ - 1.0) * (Sim.channel->NReMBB.carrierFrequency*1e9) / 3e8;

		if (distance2D >= 10 && distance2D <= breakPointDistance2D) {
			pathlossLOS = 28.0 + 22.0 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency);
		}
		else if (breakPointDistance2D < distance2D && distance2D < 5000.0) {
			pathlossLOS = 40.0 * log10(distance3D) + 28.0 + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency) - 9.0 * log10(pow(breakPointDistance2D, 2.0) + pow((srcZ - dstZ), 2.0));
		}
		pathlossNLOS = 13.54 + 39.08 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.6 * (dstZ - 1.5);

		// LOS probability cacluation
		if (outdoorDistance2D <= 18)
			losProbability = 1;
		else
		{
			double C;
			if (dstZ <= 13)
				C = 0;
			else
				C = pow((dstZ - 13) / 10, 1.5);
			losProbability = 18.0 / outdoorDistance2D + exp(-outdoorDistance2D / 63.0) * (1 - (18.0 / outdoorDistance2D)) * (1 + C * 5 / 4 * pow(outdoorDistance2D / 100, 3) * exp(-outdoorDistance2D / 150));
		}

		break;

	case SLS::IndoorOffice:

		pathlossLOS = 32.4 + 17.3 * log10(distance3D) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency);
		pathlossNLOS = 38.3 * log10(distance3D) + 17.3 + 24.9 * log10(Sim.channel->NReMBB.carrierFrequency);

		// LOS probability cacluation
		if (indoorDistance2D <= 1.2)
			losProbability = 1;
		else if (indoorDistance2D > 1.2 && indoorDistance2D <= 6.5)
			losProbability = exp(-(indoorDistance2D - 1.2) / 4.7);
		else
			losProbability = exp(-(indoorDistance2D - 6.5) / 32.6) * 0.32;

		break;

	case SLS::RuralMacroCell:

		breakPointDistance2D = 2 * PI * dstZ * srcZ * (Sim.channel->NReMBB.carrierFrequency*1e9) / 3e8;

		if (distance2D >= 10 && distance2D <= breakPointDistance2D) {
			pathlossLOS = 20.0 * log10(40 * PI * distance3D * Sim.channel->NReMBB.carrierFrequency / 3.0) + min(0.03 * pow(5.0, 1.72), 10.0) * log10(distance3D) - min(0.044 * pow(5.0, 1.72), 14.77) + 0.002 * log10(5.0) * distance3D;
		}
		else if (breakPointDistance2D < distance2D && distance2D < 5000.0) {
			pathlossLOS = 20.0 * log10(40 * PI * distance3D * Sim.channel->NReMBB.carrierFrequency / 3.0) + min(0.03 * pow(5.0, 1.72), 10.0) * log10(distance3D) - min(0.044 * pow(5.0, 1.72), 14.77) + 0.002 * log10(5.0) * distance3D + 40.0 * log10(distance3D / breakPointDistance2D);
		}
		pathlossNLOS = 161.04 - 7.1 * log10(20.0) + 7.5 * log10(5.0) - (24.37 - 3.7 * pow(5.0 / srcZ, 2.0)) * log10(srcZ) + (43.42 - 3.1 * log10(srcZ)) * (log10(distance3D) - 3.0) + 20.0 * log10(Sim.channel->NReMBB.carrierFrequency) - (3.2 * pow(log10(11.75 * dstZ), 2.0) - 4.97);

		// LOS probability cacluation
		if (outdoorDistance2D <= 10)
			losProbability = 1;
		else
			losProbability = exp(-(indoorDistance2D - 10) / 1000);

		break;

	}
	// Pathloss 값 ue location에 따라 대입
	if (arma::randu() < losProbability) { // outdoor LOS
		MS[src]->channel->pathloss = pathlossLOS;
		MS[src]->channel->channelCondition = LOS;
	}
	else {								  // outdoor NLOS
		MS[src]->channel->pathloss = max(pathlossLOS, pathlossNLOS);
		MS[src]->channel->channelCondition = NLOS;
	}
}

void SpatialChannel::Delay(int src) {
	double riceanKdB = MS[src]->channel->largeScaleParameter(1, 0);
	double riceanKfactorDependentScalingConstantdB = 0.7705 - 0.0433 *riceanKdB + 0.0002 * pow(riceanKdB, 2.0) + 0.000017 * pow(riceanKdB, 3.0);
	double temp;
	double rTau, numCluster;
	arma::mat tauPrime;
	arma::mat tau;
	temp = SLS_INFINITY;

	switch (Sim.channel->ChannelModel)
	{
	case SLS::DenseUrban:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
			rTau = UrbanMacroCellLOS.delayScalingParameter;
			numCluster = UrbanMacroCellLOS.numberOfClusters;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
			rTau = UrbanMacroCellNLOS.delayScalingParameter;
			numCluster = UrbanMacroCellNLOS.numberOfClusters;
		}
		else {
			rTau = UrbanMacroCellOtoI.delayScalingParameter;
			numCluster = UrbanMacroCellOtoI.numberOfClusters;
		}
		break;

	case SLS::UrbanMacroCell:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
			rTau = UrbanMacroCellLOS.delayScalingParameter;
			numCluster = UrbanMacroCellLOS.numberOfClusters;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
			rTau = UrbanMacroCellNLOS.delayScalingParameter;
			numCluster = UrbanMacroCellNLOS.numberOfClusters;
		}
		else {
			rTau = UrbanMacroCellOtoI.delayScalingParameter;
			numCluster = UrbanMacroCellOtoI.numberOfClusters;
		}

		break;

	case SLS::IndoorOffice:

		if (MS[src]->channel->channelCondition == LOS)
		{
			rTau = IndoorOfficeLOS.delayScalingParameter;
			numCluster = IndoorOfficeLOS.numberOfClusters;
		}
		else if (MS[src]->channel->channelCondition == NLOS)
		{
			rTau = IndoorOfficeNLOS.delayScalingParameter;
			numCluster = IndoorOfficeNLOS.numberOfClusters;
		}

		break;

	case SLS::RuralMacroCell:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
			rTau = RuralMacroCellLOS.delayScalingParameter;
			numCluster = RuralMacroCellLOS.numberOfClusters;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
			rTau = RuralMacroCellNLOS.delayScalingParameter;
			numCluster = RuralMacroCellNLOS.numberOfClusters;
		}
		else {
			rTau = RuralMacroCellOtoI.delayScalingParameter;
			numCluster = RuralMacroCellOtoI.numberOfClusters;
		}

		break;
	}

	tauPrime.zeros(numCluster, 1);
	tau.zeros(numCluster, 1);
	for (int n = 0; n < numCluster; n++) {
		double a = MS[src]->channel->largeScaleParameter(2, 0);
		tauPrime(n, 0) = -rTau * a * log(arma::randu<double>());

		double test = log(10);
		if (temp > tauPrime(n, 0))
			temp = tauPrime(n, 0);
	}

	for (int n = 0; n < numCluster; n++) {
		tau(n, 0) = tauPrime(n, 0) - temp;
	}

	arma::mat delay = arma::sort(tau, "ascend");

	MS[src]->channel->numCluster = numCluster;
	MS[src]->channel->delay = delay;
}

void SpatialChannel::ClusterPower(int src, int dst) {
	int numRealCluster = 0;
	double numCluster,rTau, perClusterShadowingStd; // model specific parameter
	double riceanKdB = MS[src]->channel->largeScaleParameter(1, 0);
	double riceanKfactorDependentScalingConstantdB = 0.7705 - 0.0433 *riceanKdB + 0.0002 * pow(riceanKdB, 2.0) + 0.000017 * pow(riceanKdB, 3.0);
	double sumPowerPrime = 0.0;
	double maxClusterPower = 0.0;
	double kR = pow(10.0, MS[src]->channel->largeScaleParameter[1] / 10.0);
	// Load Channel model parameter
	switch (Sim.channel->ChannelModel)
	{
	case SLS::DenseUrban:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {			// Outdoor LOS
			rTau = UrbanMacroCellLOS.delayScalingParameter;
			numCluster = UrbanMacroCellLOS.numberOfClusters;
			perClusterShadowingStd = UrbanMacroCellLOS.perClusterShadowing;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {	// Outdoor NLOS
			rTau = UrbanMacroCellNLOS.delayScalingParameter;
			numCluster = UrbanMacroCellNLOS.numberOfClusters;
			perClusterShadowingStd = UrbanMacroCellNLOS.perClusterShadowing;
		}
		else {																								// Indoor
			rTau = UrbanMacroCellOtoI.delayScalingParameter;
			numCluster = UrbanMacroCellOtoI.numberOfClusters;
			perClusterShadowingStd = UrbanMacroCellOtoI.perClusterShadowing;
		}
		break;

	case SLS::UrbanMacroCell:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {			// Outdoor LOS
			rTau = UrbanMacroCellLOS.delayScalingParameter;
			numCluster = UrbanMacroCellLOS.numberOfClusters;
			perClusterShadowingStd = UrbanMacroCellLOS.perClusterShadowing;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {	// Outdoor NLOS
			rTau = UrbanMacroCellNLOS.delayScalingParameter;
			numCluster = UrbanMacroCellNLOS.numberOfClusters;
			perClusterShadowingStd = UrbanMacroCellNLOS.perClusterShadowing;
		}
		else {																								// Indoor
			rTau = UrbanMacroCellOtoI.delayScalingParameter;
			numCluster = UrbanMacroCellOtoI.numberOfClusters;
			perClusterShadowingStd = UrbanMacroCellOtoI.perClusterShadowing;
		}

		break;
	case SLS::IndoorOffice:

		if ((MS[src]->channel->channelCondition == LOS)) {
			rTau = IndoorOfficeLOS.delayScalingParameter;
			numCluster = IndoorOfficeLOS.numberOfClusters;
			perClusterShadowingStd = IndoorOfficeLOS.perClusterShadowing;
		}
		else if ((MS[src]->channel->channelCondition == NLOS)) {	
			rTau = IndoorOfficeNLOS.delayScalingParameter;
			numCluster = IndoorOfficeNLOS.numberOfClusters;
			perClusterShadowingStd = IndoorOfficeNLOS.perClusterShadowing;
		}

		break;
	case SLS::RuralMacroCell:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {			// Outdoor LOS
			rTau = RuralMacroCellLOS.delayScalingParameter;
			numCluster = RuralMacroCellLOS.numberOfClusters;
			perClusterShadowingStd = RuralMacroCellLOS.perClusterShadowing;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {	// Outdoor NLOS
			rTau = RuralMacroCellNLOS.delayScalingParameter;
			numCluster = RuralMacroCellNLOS.numberOfClusters;
			perClusterShadowingStd = RuralMacroCellNLOS.perClusterShadowing;
		}
		else {																								// Indoor
			rTau = RuralMacroCellOtoI.delayScalingParameter;
			numCluster = RuralMacroCellOtoI.numberOfClusters;
			perClusterShadowingStd = RuralMacroCellOtoI.perClusterShadowing;
		}

		break;
	}
	arma::mat powerPrime(numCluster, 1);
	arma::mat delaysLOS(numCluster, 1);
	arma::mat clusterPower(numCluster, 1);
	arma::mat clusterPower1(numCluster, 1);
	arma::mat delayReduced(numCluster, 1);
	arma::mat delayLOSReduced(numCluster, 1);
	arma::mat clusterPowerReduced(numCluster, 1);  //Cluster power for equations in (7.3-9) and (7.3-14)
	arma::mat realClusterPowersForLOS(numCluster, 1); //Cluster power for equations in (7.3-22)
	arma::mat delay = MS[src]->channel->delay;

	
	for (int n = 0; n < numCluster; n++) {
		powerPrime[n] = exp(-delay(n,0) * (rTau - 1.0) / (rTau * MS[src]->channel->largeScaleParameter(2, 0))) * pow(10.0, -(perClusterShadowingStd * arma::randn()) / 10.0);
		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) // outdoor LOS인 경우
			delaysLOS[n] = delay[n] / riceanKfactorDependentScalingConstantdB;
		sumPowerPrime = sumPowerPrime + powerPrime[n];
	}
	
		
	

	for (int n = 0; n < numCluster; n++) {
		clusterPower1[n] = powerPrime[n] / sumPowerPrime;
		
		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS))
			clusterPower[n] = 1.0 / (kR + 1.0) * clusterPower1[n] + (n == 0) * kR / (kR + 1.0);
		else
			clusterPower[n] = clusterPower1[n];


		if (maxClusterPower < clusterPower[n])
			maxClusterPower = clusterPower[n];
	}
	
	for (int n = 0; n < numCluster; n++) {
		if (10.0*log10(clusterPower[n]) - 10.0*log10(maxClusterPower) < -25.0)
			clusterPower[n] = -100.0;

		if (clusterPower[n] != -100.0) {
			clusterPowerReduced[numRealCluster] = clusterPower[n];	//KR 적용한거
			realClusterPowersForLOS[numRealCluster] = clusterPower1[n]; //KR 적용안한거(뒤에서 쓸꺼)
			delayReduced[numRealCluster] = delay[n];
			delayLOSReduced[numRealCluster] = delaysLOS[n];
			numRealCluster++;
		}
	}
	MS[src]->channel->tau(dst) = delayReduced;
	MS[src]->channel->tauLOS(dst) = delayLOSReduced;


	// => 이런애들은 Sim.channel->sturcture-> 공통 // 각자 maxcluster에 structure를 만들어서 저장
	MS[src]->channel->maxClusterPower = maxClusterPower;
	MS[src]->channel->numRealCluster = numRealCluster;
	MS[src]->channel->NumRealCluseter(dst, 0) = numRealCluster;
	MS[src]->channel->delayReduced = delayReduced;
	MS[src]->channel->clusterPowerReduced = clusterPowerReduced;
	MS[src]->channel->realClusterPowersForLOS = realClusterPowersForLOS;
}

void SpatialChannel::ArrivalAndDepartureAngle(int src, int dst, int site, int sector) {
	MS[src]->network->velocityHorizontal = (360 * arma::randu()*PI) / 180;
	MS[src]->network->velocityVertical = (90 * PI) / 180;

	arma::mat departureAngleGCS(2, 1);
	arma::mat arrivalAngleGCS(2, 1);
	double srcZ = MS[src]->network->pos3D(0, 2), dstZ = BS[dst]->network->pos3D(0, 2);
	double cAOAAOD, cZOAZOD;
	double clusterASA, clusterASD, clusterZSA, muZSD, muOffsetZOD, muXPR, sigmaXPR;
	double distance2D = MS[src]->channel->distance2D;
	arma::mat subCluster0(1, 10);
	subCluster0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 19 << 20 << arma::endr;
	arma::mat subCluster1(1, 6);
	subCluster1 << 9 << 10 << 11 << 12 << 17 << 18 << arma::endr;
	arma::mat subCluster2(1, 4);
	subCluster2 << 13 << 14 << 15 << 16 << arma::endr;
	arma::mat wholeCluster(1, 20);
	wholeCluster << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << arma::endr;
	arma::mat offsetAngle(1, 20);
	offsetAngle << 0.0447 << -0.0447 << 0.1413 << -0.1413 << 0.2492 << -0.2492 << 0.3715 << -0.3715 << 0.5129 << -0.5129 << 0.6797 << -0.6797 << 0.8844 << -0.8844 << 1.1481 << -1.1481 << 1.5195 << -1.5195 << 2.1551 << -2.1551 << arma::endr;

	// Table 7.3-2 Scaling factors for AOA, AOD generation 
	arma::mat scalingFactorForAOAandAOD(2, 11);
	scalingFactorForAOAandAOD << 4 << 5 << 8 << 10 << 11 << 12 << 14 << 15 << 16 << 19 << 20 << arma::endr
		<< 0.779 << 0.860 << 1.018 << 1.090 << 1.123 << 1.146 << 1.190 << 1.211 << 1.226 << 1.273 << 1.289 << arma::endr;
	// Table 7.3-3 Scaling factors for ZOA, ZOD generation 
	arma::mat scalingFactorForZOAandZOD(2, 3);
	scalingFactorForZOAandZOD << 12 << 19 << 20 << arma::endr
		<< 1.104 << 1.184 << 1.178 << arma::endr;
	// Sector offset angle
	arma::mat alpha(3, 1);
	alpha << (PI / 180) * 30 << (PI / 180) * 150 << (PI / 180) *(-90) << arma::endr;

	// muOFFSEZZOD CLUSTERASA CLUSTERASD ZSA muZSD
	switch (Sim.channel->ChannelModel)
	{
	case SLS::DenseUrban:
		if (srcZ == 10) // small cell (UMi)
		{
			if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
				clusterASA = UrbanMicroCellLOS.cluserASA;
				clusterASD = UrbanMicroCellLOS.cluserASD;
				clusterZSA = UrbanMicroCellLOS.cluserZSA;
				muZSD = max(-0.21, -14.8 * (distance2D / 1000) + 0.01 * abs(dstZ - srcZ) + 0.83);
				muOffsetZOD = 0.0;
				muXPR = UrbanMicroCellLOS.muXPR;
				sigmaXPR = UrbanMicroCellLOS.sigmaXPR;
			}
			else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
				clusterASA = UrbanMicroCellNLOS.cluserASA;
				clusterASD = UrbanMicroCellNLOS.cluserASD;
				clusterZSA = UrbanMicroCellNLOS.cluserZSA;
				muZSD = max(-0.5, -3.1 * (distance2D / 1000) + 0.01 * max(dstZ - srcZ, 0.0) + 0.2);
				muXPR = UrbanMicroCellNLOS.muXPR;
				sigmaXPR = UrbanMicroCellNLOS.sigmaXPR;

				muOffsetZOD = -pow(10.0, -1.5 * log10(max(10.0, distance2D)) + 3.3);
			}
			else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS)) {
				clusterASA = UrbanMicroCellOtoI.cluserASA;
				clusterASD = UrbanMicroCellOtoI.cluserASD;
				clusterZSA = UrbanMicroCellOtoI.cluserZSA;
				muZSD = max(-0.21, -14.8 * (distance2D / 1000) + 0.01 * abs(dstZ - srcZ) + 0.83);
				muOffsetZOD = 0.0;
				muXPR = UrbanMicroCellOtoI.muXPR;
				sigmaXPR = UrbanMicroCellOtoI.sigmaXPR;
			}
			else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == NLOS)) {
				clusterASA = UrbanMicroCellOtoI.cluserASA;
				clusterASD = UrbanMicroCellOtoI.cluserASD;
				clusterZSA = UrbanMicroCellOtoI.cluserZSA;
				muZSD = max(-0.5, -3.1 * (distance2D / 1000) + 0.01 * max(dstZ - srcZ, 0.0) + 0.2);
				muOffsetZOD = -pow(10.0, -1.5 * log10(max(10.0, distance2D)) + 3.3);
				muXPR = UrbanMicroCellOtoI.muXPR;
				sigmaXPR = UrbanMicroCellOtoI.sigmaXPR;
			}
		}
		else
		{
			if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
				clusterASA = UrbanMacroCellLOS.cluserASA;
				clusterASD = UrbanMacroCellLOS.cluserASD;
				clusterZSA = UrbanMacroCellLOS.cluserZSA;
				muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.75);
				muOffsetZOD = 0.0;
				muXPR = UrbanMacroCellLOS.muXPR;
				sigmaXPR = UrbanMacroCellLOS.sigmaXPR;
			}
			else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
				clusterASA = UrbanMacroCellNLOS.cluserASA;
				clusterASD = UrbanMacroCellNLOS.cluserASD;
				clusterZSA = UrbanMacroCellNLOS.cluserZSA;
				muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.9);
				muXPR = UrbanMacroCellNLOS.muXPR;
				sigmaXPR = UrbanMacroCellNLOS.sigmaXPR;

				muOffsetZOD = 7.66 * log10(Sim.channel->NReMBB.carrierFrequency) - 5.96 - pow(10.0, 0.208 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.782 * log10(max(25.0, distance2D)) + (-0.13 * log10(Sim.channel->NReMBB.carrierFrequency) + 2.03) - 0.07 * (dstZ - 1.5));
			}
			else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS)) {
				clusterASA = UrbanMacroCellOtoI.cluserASA;
				clusterASD = UrbanMacroCellOtoI.cluserASD;
				clusterZSA = UrbanMacroCellOtoI.cluserZSA;
				muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.75);
				muOffsetZOD = 0.0;
				muXPR = UrbanMacroCellOtoI.muXPR;
				sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
			}
			else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == NLOS)) {
				clusterASA = UrbanMacroCellOtoI.cluserASA;
				clusterASD = UrbanMacroCellOtoI.cluserASD;
				clusterZSA = UrbanMacroCellOtoI.cluserZSA;
				muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.9);
				muOffsetZOD = 7.66 * log10(Sim.channel->NReMBB.carrierFrequency) - 5.96 - pow(10.0, 0.208 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.782 * log10(max(25.0, distance2D)) + (-0.13 * log10(Sim.channel->NReMBB.carrierFrequency) + 2.03) - 0.07 * (dstZ - 1.5));
				muXPR = UrbanMacroCellOtoI.muXPR;
				sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
			}
		}
		
		break;

	case SLS::UrbanMacroCell:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
			clusterASA = UrbanMacroCellLOS.cluserASA;
			clusterASD = UrbanMacroCellLOS.cluserASD;
			clusterZSA = UrbanMacroCellLOS.cluserZSA;
			muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.75);
			muOffsetZOD = 0.0;
			muXPR = UrbanMacroCellLOS.muXPR;
			sigmaXPR = UrbanMacroCellLOS.sigmaXPR;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
			clusterASA = UrbanMacroCellNLOS.cluserASA;
			clusterASD = UrbanMacroCellNLOS.cluserASD;
			clusterZSA = UrbanMacroCellNLOS.cluserZSA;
			muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.9);
			muXPR = UrbanMacroCellNLOS.muXPR;
			sigmaXPR = UrbanMacroCellNLOS.sigmaXPR;

			muOffsetZOD = 7.66 * log10(Sim.channel->NReMBB.carrierFrequency) - 5.96 - pow(10.0, 0.208 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.782 * log10(max(25.0, distance2D)) + (-0.13 * log10(Sim.channel->NReMBB.carrierFrequency) + 2.03) - 0.07 * (dstZ - 1.5));
		}
		else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS)) {
			clusterASA = UrbanMacroCellOtoI.cluserASA;
			clusterASD = UrbanMacroCellOtoI.cluserASD;
			clusterZSA = UrbanMacroCellOtoI.cluserZSA;
			muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.75);
			muOffsetZOD = 0.0;
			muXPR = UrbanMacroCellOtoI.muXPR;
			sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
		}
		else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == NLOS)) {
			clusterASA = UrbanMacroCellOtoI.cluserASA;
			clusterASD = UrbanMacroCellOtoI.cluserASD;
			clusterZSA = UrbanMacroCellOtoI.cluserZSA;
			muZSD = max(-0.5, -2.1 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.9);
			muOffsetZOD = 7.66 * log10(Sim.channel->NReMBB.carrierFrequency) - 5.96 - pow(10.0, 0.208 * log10(Sim.channel->NReMBB.carrierFrequency) - 0.782 * log10(max(25.0, distance2D)) + (-0.13 * log10(Sim.channel->NReMBB.carrierFrequency) + 2.03) - 0.07 * (dstZ - 1.5));
			muXPR = UrbanMacroCellOtoI.muXPR;
			sigmaXPR = UrbanMacroCellOtoI.sigmaXPR;
		}

		break;

	case SLS::IndoorOffice:

		if ((MS[src]->channel->channelCondition == LOS)) {
			clusterASA = IndoorOfficeLOS.cluserASA;
			clusterASD = IndoorOfficeLOS.cluserASD;
			clusterZSA = IndoorOfficeLOS.cluserZSA;
			muZSD = IndoorOfficeLOS.muZSD;
			muOffsetZOD = 0.0;
			muXPR = IndoorOfficeLOS.muXPR;
			sigmaXPR = IndoorOfficeLOS.sigmaXPR;
		}
		else if ((MS[src]->channel->channelCondition == NLOS)) {
			clusterASA = IndoorOfficeNLOS.cluserASA;
			clusterASD = IndoorOfficeNLOS.cluserASD;
			clusterZSA = IndoorOfficeNLOS.cluserZSA;
			muZSD = IndoorOfficeNLOS.muZSD;
			muOffsetZOD = -pow(10.0, (-0.62*log10(max(10.0, distance2D)) + 1.93 - 0.07*(abs(MS[src]->network->pos3D(0, 2)) - 1.5)));
			muXPR = IndoorOfficeNLOS.muXPR;
			sigmaXPR = IndoorOfficeNLOS.sigmaXPR;
		}

		break;

	case SLS::RuralMacroCell:

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) { // Outdoor LOS
			clusterASA = RuralMacroCellLOS.cluserASA;
			clusterASD = RuralMacroCellLOS.cluserASD;
			clusterZSA = RuralMacroCellLOS.cluserZSA;
			muZSD = max(-1.0, -0.17 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.22);
			muOffsetZOD = 0.0;
			muXPR = RuralMacroCellLOS.muXPR;
			sigmaXPR = RuralMacroCellLOS.sigmaXPR;
		}
		else if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == NLOS)) {
			clusterASA = RuralMacroCellNLOS.cluserASA;
			clusterASD = RuralMacroCellNLOS.cluserASD;
			clusterZSA = RuralMacroCellNLOS.cluserZSA;
			muZSD = max(-1.0, -0.19 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.28);
			muOffsetZOD = atan2(35 - 3.5, distance2D) - atan2(35 - 1.5, distance2D);
			muXPR = RuralMacroCellNLOS.muXPR;
			sigmaXPR = RuralMacroCellNLOS.sigmaXPR;
		}
		else if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS)) {
			clusterASA = RuralMacroCellOtoI.cluserASA;
			clusterASD = RuralMacroCellOtoI.cluserASD;
			clusterZSA = RuralMacroCellOtoI.cluserZSA;
			muZSD = max(-1.0, -0.19 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.28);
			muOffsetZOD = atan2(35 - 3.5, distance2D) - atan2(35 - 1.5, distance2D);
			muXPR = RuralMacroCellOtoI.muXPR;
			sigmaXPR = RuralMacroCellOtoI.sigmaXPR;
		}
		else {
			clusterASA = RuralMacroCellOtoI.cluserASA;
			clusterASD = RuralMacroCellOtoI.cluserASD;
			clusterZSA = RuralMacroCellOtoI.cluserZSA;
			muZSD = max(-1.0, -0.19 * (distance2D / 1000) - 0.01 * (dstZ - 1.5) + 0.28);
			muOffsetZOD = atan2(35 - 3.5, distance2D) - atan2(35 - 1.5, distance2D);
			muXPR = RuralMacroCellOtoI.muXPR;
			sigmaXPR = RuralMacroCellOtoI.sigmaXPR;
		}

		break;
	}

	if ( (Sim.network->NetworkModel == NETWORK::UrbanMacroCell) || (Sim.network->NetworkModel == NETWORK::DenseUrban) || (Sim.network->NetworkModel == NETWORK::RuralMacroCell)) {
		departureAngleGCS(0, 0) = AzimuthAngleOfGlobalCoordinateSystem(MS[src]->network->wraparoundposBS(site, 0), MS[src]->network->wraparoundposBS(site, 1), MS[src]->network->pos3D(0, 0), MS[src]->network->pos3D(0, 1));
		departureAngleGCS(1, 0) = ZenithAngleOfGlobalCoordinateSystem(MS[src]->network->wraparoundposBS(site, 0), MS[src]->network->wraparoundposBS(site, 1), MS[src]->network->wraparoundposBS(site, 2), MS[src]->network->pos3D(0, 0), MS[src]->network->pos3D(0, 1), MS[src]->network->pos3D(0, 2));

		arrivalAngleGCS(0, 0) = AzimuthAngleOfGlobalCoordinateSystem(MS[src]->network->pos3D(0, 0), MS[src]->network->pos3D(1), MS[src]->network->wraparoundposBS(site, 0), MS[src]->network->wraparoundposBS(site, 1));
		arrivalAngleGCS(1, 0) = ZenithAngleOfGlobalCoordinateSystem(MS[src]->network->pos3D(0), MS[src]->network->pos3D(1), MS[src]->network->pos3D(2), MS[src]->network->wraparoundposBS(site, 0), MS[src]->network->wraparoundposBS(site, 1), MS[src]->network->wraparoundposBS(site, 2));
	}
	else if (Sim.network->NetworkModel == NETWORK::IndoorOffice) {
		departureAngleGCS(0, 0) = AzimuthAngleOfGlobalCoordinateSystem(BS[dst]->network->pos3D(0, 0), BS[dst]->network->pos3D(0, 1), MS[src]->network->pos3D(0, 0), MS[src]->network->pos3D(0, 1));
		departureAngleGCS(1, 0) = ZenithAngleOfGlobalCoordinateSystem(BS[dst]->network->pos3D(0, 0), BS[dst]->network->pos3D(0, 1), BS[dst]->network->pos3D(0, 2), MS[src]->network->pos3D(0, 0), MS[src]->network->pos3D(0, 1), MS[src]->network->pos3D(0, 2));

		arrivalAngleGCS(0, 0) = AzimuthAngleOfGlobalCoordinateSystem(MS[src]->network->pos3D(0, 0), MS[src]->network->pos3D(1), BS[dst]->network->pos3D(0, 0), BS[dst]->network->pos3D(0, 1));
		arrivalAngleGCS(1, 0) = ZenithAngleOfGlobalCoordinateSystem(MS[src]->network->pos3D(0), MS[src]->network->pos3D(1), MS[src]->network->pos3D(2), BS[dst]->network->pos3D(0, 0), BS[dst]->network->pos3D(0, 1), BS[dst]->network->pos3D(0, 2));
	}

	MS[src]->channel->GCSAOA = arrivalAngleGCS(0, 0);
	MS[src]->channel->GCSAOD = departureAngleGCS(0, 0);
	MS[src]->channel->GCSZOA = arrivalAngleGCS(1, 0);
	MS[src]->channel->GCSZOD = departureAngleGCS(1, 0);
	MS[src]->channel->AnalogBeamPhase.zeros(2);
	MS[src]->channel->DigitalBeamPhase.zeros(2);
	MS[src]->channel->BeamAmplitude.zeros(2);
	
	MS[src]->channel->AnalogBeamPhase(1) = MS[src]->channel->GCSZOD;
	MS[src]->channel->AnalogBeamPhase(0) = MS[src]->channel->GCSZOA;
	MS[src]->channel->DigitalBeamPhase(1) = MS[src]->channel->GCSAOD;
	MS[src]->channel->DigitalBeamPhase(0) = MS[src]->channel->GCSAOD;

	if (sector == 0) {
		arma::mat departureAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha0, Sim.network->beta, Sim.network->gamma, departureAngleGCS);
		arma::mat arrivalAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha0, Sim.network->beta, Sim.network->gamma, arrivalAngleGCS);
	}
	else if (sector == 1) {
		arma::mat departureAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha1, Sim.network->beta, Sim.network->gamma, departureAngleGCS);
		arma::mat arrivalAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha1, Sim.network->beta, Sim.network->gamma, arrivalAngleGCS);
	}
	else if (sector == 2) {
		arma::mat departureAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha2, Sim.network->beta, Sim.network->gamma, departureAngleGCS);
		arma::mat arrivalAngleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(Sim.network->sectorDegree.alpha2, Sim.network->beta, Sim.network->gamma, arrivalAngleGCS);
	}

	int numCluster = MS[src]->channel->numCluster;


	for (int m = 0; m < 11; m++) {
		if (numCluster == scalingFactorForAOAandAOD(0, m)) {
			cAOAAOD = scalingFactorForAOAandAOD(1, m);
		}
	}

	for (int m = 0; m < 3; m++) {
		if (numCluster == scalingFactorForZOAandZOD(0, m)) {
			cZOAZOD = scalingFactorForZOAandZOD(1, m);
		}
	}

	double K = MS[src]->channel->largeScaleParameter(1, 0);
	if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {
		cAOAAOD = cAOAAOD * (1.1035 - 0.028 *K - 0.002 * pow(K, 2.0) + 0.0001 * pow(K, 3.0));
		cZOAZOD = cZOAZOD * (1.3086 + 0.0339 *K - 0.0077 * pow(K, 2.0) + 0.0002 * pow(K, 3.0));
	}

	int numRealCluster = MS[src]->channel->numRealCluster;
	double sigmaASA = MS[src]->channel->largeScaleParameter(4, 0);
	double sigmaASD = MS[src]->channel->largeScaleParameter(3, 0);
	double sigmaZSA = MS[src]->channel->largeScaleParameter(6, 0);
	double sigmaZSD = MS[src]->channel->largeScaleParameter(5, 0);
	double maxClusterPower = MS[src]->channel->maxClusterPower;
	double clusterZOA, clusterZOD, clusterAOA, clusterAOD;

	int abb = 0;
	arma::mat piAOAPrime(numRealCluster, 1);
	arma::mat piAODPrime(numRealCluster, 1);
	arma::mat thetaZOAPrime(numRealCluster, 1);
	arma::mat thetaZODPrime(numRealCluster, 1);

	arma::mat thetaRxRay(1, 20);
	arma::mat piRxRay(1, 20);
	arma::mat thetaTxRay(1, 20);
	arma::mat piTxRay(1, 20);

	arma::mat RayAOAtemp(1, 20);
	arma::mat RayAODtemp(1, 20);
	arma::mat RayZOAtemp(1, 20);
	arma::mat RayZODtemp(1, 20);
	
	arma::mat RayAOA(20, 1);
	arma::mat RayAOD(20, 1);
	arma::mat RayZOA(20, 1);
	arma::mat RayZOD(20, 1);

	arma::mat xAOA(20, 1);
	arma::mat xAOD(20, 1);
	arma::mat xZOA(20, 1);
	arma::mat xZOD(20, 1);
	arma::mat yAOA(20, 1);
	arma::mat yAOD(20, 1);
	arma::mat yZOA(20, 1);
	arma::mat yZOD(20, 1);

	arma::mat clusterPowerReduced = MS[src]->channel->clusterPowerReduced;

	MS[src]->channel->SmallScaleAOA.zeros(numRealCluster,20); // n,m
	MS[src]->channel->SmallScaleAOD.zeros(numRealCluster, 20); // n,m
	MS[src]->channel->SmallScaleZOA.zeros(numRealCluster, 20); // n,m
	MS[src]->channel->SmallScaleZOD.zeros(numRealCluster, 20); // n,m
	MS[src]->channel->DemoAOA(dst, 0).zeros(MAX_CLUSTER,1);
	MS[src]->channel->DemoAOD(dst, 0).zeros(MAX_CLUSTER,1);
	MS[src]->channel->DemoClusterPower(dst, 0).zeros(MAX_CLUSTER,1);

	for (int n = 0; n < numRealCluster; n++) {
		piAOAPrime(n, 0) = (2.0 * (sigmaASA / 1.4) * sqrt(-log(clusterPowerReduced(n, 0) / maxClusterPower))) / cAOAAOD;
		piAODPrime(n, 0) = (2.0 * (sigmaASD / 1.4) * sqrt(-log(clusterPowerReduced(n, 0) / maxClusterPower))) / cAOAAOD;
		thetaZOAPrime(n, 0) = (-sigmaZSA * log(clusterPowerReduced(n, 0) / maxClusterPower)) / cZOAZOD;
		thetaZODPrime(n, 0) = (-sigmaZSD * log(clusterPowerReduced(n, 0) / maxClusterPower)) / cZOAZOD;
		
		// Random Coupling
		if (n == 0 || n == 1) {
			arma::mat thetaRayRxTemp0 = subCluster0;
			thetaRayRxTemp0 = shuffle(thetaRayRxTemp0, 1);
			arma::mat thetaRayRxTemp1 = subCluster1;
			thetaRayRxTemp1 = shuffle(thetaRayRxTemp1, 1);
			arma::mat thetaRayRxTemp2 = subCluster2;
			thetaRayRxTemp2 = shuffle(thetaRayRxTemp2, 1);

			arma::mat thetaRayTxTemp0 = subCluster0;
			thetaRayTxTemp0 = shuffle(thetaRayTxTemp0, 1);
			arma::mat thetaRayTxTemp1 = subCluster1;
			thetaRayTxTemp1 = shuffle(thetaRayTxTemp1, 1);
			arma::mat thetaRayTxTemp2 = subCluster2;
			thetaRayTxTemp2 = shuffle(thetaRayTxTemp2, 1);

			arma::mat piRayRxTemp0 = subCluster0;
			piRayRxTemp0 = shuffle(piRayRxTemp0, 1);
			arma::mat piRayRxTemp1 = subCluster1;
			piRayRxTemp1 = shuffle(piRayRxTemp1, 1);
			arma::mat piRayRxTemp2 = subCluster2;
			piRayRxTemp2 = shuffle(piRayRxTemp2, 1);

			arma::mat piRayTxTemp0 = subCluster0;
			piRayTxTemp0 = shuffle(piRayTxTemp0, 1);
			arma::mat piRayTxTemp1 = subCluster1;
			piRayTxTemp1 = shuffle(piRayTxTemp1, 1);
			arma::mat piRayTxTemp2 = subCluster2;
			piRayTxTemp2 = shuffle(piRayTxTemp2, 1);


			for (int numRay = 0; numRay < 20; numRay++) {
				if (numRay < 10) {
					thetaRxRay[numRay] = thetaRayRxTemp0[numRay] - 1;
					thetaTxRay[numRay] = thetaRayTxTemp0[numRay] - 1;
					piRxRay[numRay] = piRayRxTemp0[numRay] - 1;
					piTxRay[numRay] = piRayTxTemp0[numRay] - 1;

				}
				else if (numRay >= 10 && numRay < 16) {
					thetaRxRay[numRay] = thetaRayRxTemp1[numRay - 10] - 1;
					thetaTxRay[numRay] = thetaRayTxTemp1[numRay - 10] - 1;
					piRxRay[numRay] = piRayRxTemp1[numRay - 10] - 1;
					piTxRay[numRay] = piRayTxTemp1[numRay - 10] - 1;
				}
				else {
					thetaRxRay[numRay] = thetaRayRxTemp2[numRay - 16] - 1;
					thetaTxRay[numRay] = thetaRayTxTemp2[numRay - 16] - 1;
					piRxRay[numRay] = piRayRxTemp2[numRay - 16] - 1;
					piTxRay[numRay] = piRayTxTemp2[numRay - 16] - 1;
				}
			}
		}


		else { // n >=2
			arma::mat thetaRayRxTemp3 = wholeCluster;
			thetaRayRxTemp3 = shuffle(thetaRayRxTemp3, 1);
			arma::mat thetaRayTxTemp3 = wholeCluster;
			thetaRayTxTemp3 = shuffle(thetaRayTxTemp3, 1);
			arma::mat piRayRxTemp3 = wholeCluster;
			piRayRxTemp3 = shuffle(piRayRxTemp3, 1);
			arma::mat piRayTxTemp3 = wholeCluster;
			piRayTxTemp3 = shuffle(piRayTxTemp3, 1);


			for (int numRay = 0; numRay < 20; numRay++) {
				thetaRxRay[numRay] = thetaRayRxTemp3[numRay] - 1;
				thetaTxRay[numRay] = thetaRayTxTemp3[numRay] - 1;
				piRxRay[numRay] = piRayRxTemp3[numRay] - 1;
				piTxRay[numRay] = piRayTxTemp3[numRay] - 1;

			}
		}

		xAOA[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		xAOD[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		xZOA[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		xZOD[n] = (arma::randu() < 0.5) * 2.0 - 1.0;
		yAOA[n] = arma::randn() * (MS[src]->channel->largeScaleParameter(4, 0) / 7.0);
		yAOD[n] = arma::randn() * (MS[src]->channel->largeScaleParameter(3, 0) / 7.0);
		yZOA[n] = arma::randn() * (MS[src]->channel->largeScaleParameter(6, 0) / 7.0);
		yZOD[n] = arma::randn() * (MS[src]->channel->largeScaleParameter(5, 0) / 7.0);


		// muOFFSEZZOD CLUSTERASA CLUSTERASD ZSA muZSD

		if ((MS[src]->network->location == Outdoor) && (MS[src]->channel->channelCondition == LOS)) {
			clusterAOA = (xAOA[n] * piAOAPrime[n] + yAOA[n]) - (xAOA[0] * piAOAPrime[0] + yAOA[0] - (arrivalAngleGCS(0, 0)*180.0 / PI));
			clusterAOD = (xAOD[n] * piAODPrime[n] + yAOD[n]) - (xAOD[0] * piAODPrime[0] + yAOD[0] - (departureAngleGCS(0, 0)*180.0 / PI));
			clusterZOA = (xZOA[n] * thetaZOAPrime[n] + yZOA[n]) - (xZOA[0] * thetaZOAPrime[0] + yZOA[0] - ((PI - arrivalAngleGCS(1, 0))*180.0 / PI));
			clusterZOD = (xZOD[n] * thetaZODPrime[n] + yZOD[n]) - (xZOD[0] * thetaZODPrime[0] + yZOD[0] - (departureAngleGCS(1, 0)*180.0 / PI));
		}
		else  {
			clusterAOA = xAOA[n] * piAOAPrime[n] + yAOA[n] + (arrivalAngleGCS(0, 0)*180.0 / PI);
			clusterAOD = xAOD[n] * piAODPrime[n] + yAOD[n] + (departureAngleGCS(0, 0)*180.0 / PI);
			clusterZOA = xZOA[n] * thetaZOAPrime[n] + yZOA[n] + ((PI - arrivalAngleGCS(1, 0))*180.0 / PI);
			clusterZOD = xZOD[n] * thetaZODPrime[n] + yZOD[n] + (departureAngleGCS(1, 0)*180.0 / PI) + muOffsetZOD;
		}
		if ((MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == LOS) || (MS[src]->network->location == Indoor) && (MS[src]->channel->channelCondition == NLOS))
			clusterZOA = xZOA[n] * thetaZOAPrime[n] + yZOA[n] + 90.0;

		MS[src]->channel->DemoAOA(dst, 0)(n, 0) = clusterAOA;
		MS[src]->channel->DemoAOD(dst, 0)(n, 0) = clusterAOD;
		MS[src]->channel->DemoClusterPower(dst, 0)(n, 0) = clusterPowerReduced(n, 0);


		for (int m = 0; m < 20; m++) {
			RayAOD(m) = Modulo((clusterAOD + clusterASD * offsetAngle[m]), 360.0);
			RayZOD(m) = Modulo((clusterZOD + (3.0 / 8.0) * pow(10.0, muZSD) * offsetAngle[m]), 360.0);

			RayAOA(m) = Modulo((clusterAOA + clusterASA * offsetAngle[m]), 360.0);
			RayZOA(m) = Modulo((clusterZOA + clusterZSA * offsetAngle[m]), 360.0);

			if (RayAOA(m) >= 180.0 && RayAOA(m) <= 360.0)
				RayAOA(m) = -360.0 + RayAOA(m);
			if (RayAOD(m) >= 180.0 && RayAOD(m) <= 360.0)
				RayAOD(m) = -360.0 + RayAOD(m);
			if (RayZOA(m) >= 180.0 && RayZOA(m) <= 360.0)
				RayZOA(m) = 360.0 - RayZOA(m);
			if (RayZOD(m) >= 180.0 && RayZOD(m) <= 360.0)
				RayZOD(m) = 360.0 - RayZOD(m);
		}


		for (int m = 0; m < 20; m++) {
			RayAOAtemp(m) = RayAOA[piRxRay[m]];
			RayAODtemp[m] = RayAOD[piTxRay[m]];
			RayZOAtemp[m] = RayZOA[thetaRxRay[m]];
			RayZODtemp[m] = RayZOD[thetaTxRay[m]];
		}

		for (int m = 0; m < 20; m++) {
			RayAOA(m) = RayAOAtemp[m];
			RayAOD(m) = RayAODtemp[m];
			RayZOA(m) = RayZOAtemp[m];
			RayZOD(m) = RayZODtemp[m];
		}



		MS[src]->channel->SmallScaleAOA.row(n) = RayAOAtemp;
		MS[src]->channel->SmallScaleAOD.row(n) = RayAODtemp;
		MS[src]->channel->SmallScaleZOA.row(n) = RayZOAtemp;
		MS[src]->channel->SmallScaleZOD.row(n) = RayZODtemp;

	}
}
 
void SpatialChannel::ArrivalAndDepartureAntennaGain(int src, int dst, int site, int sector) {
	int numRealCluster=MS[src]->channel->numRealCluster;
	int numProcess = Sim.channel->NumberOfChannelProcess;
	int numRxAntenna = Sim.channel->NumberOfReceiveAntennaPort;
	int	numTxHorizontalAntenna= Sim.channel->NumberOfTxHorizontalAntenna;
	int numTxVerticalAntenna= Sim.channel->numberOfTxVerticalAntenna;
	int numTxPort= Sim.channel->NumberOfTransmitAntennaPort;
	double zetaRx1, zetaRx2, zetaTx1, zetaTx2;
	
	MS[src]->channel->SmallScaleReceiverAntennaGainUH.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleReceiverAntennaGainUV.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleReceiverAntennaGainXH.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleReceiverAntennaGainXV.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleTransmitterAntennaGainUH.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleTransmitterAntennaGainUV.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleTransmitterAntennaGainXH.zeros(numRealCluster, 20);
	MS[src]->channel->SmallScaleTransmitterAntennaGainXV.zeros(numRealCluster, 20);
	
	arma::mat alpha(3, 1);
	alpha << (PI / 180) * 30 << (PI / 180) * 150 << (PI / 180) *(-90) << arma::endr;
	double  beta = 0.0;
	double gamma = 0.0;

	// Antenna configuration zeta1, zeta2
	if (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray) {
		zetaRx1 = 0.0;
		zetaRx2 = 0.0;
	}
	else if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) {
		zetaRx1 = 0.0;
		zetaRx2 = PI / 2;
	}
	if (Sim.channel->BsAntennaModel == CHANNEL::UniformLinearArray) {
		zetaTx1 = 0.0;
		zetaTx2 = 0.0;
	}
	else if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) {
		zetaTx1 = -PI / 4;
		zetaTx2 = PI / 4;
	}

	arma::mat receiveAngle(2, 1);
	arma::mat transmitAngle(2, 1);

	arma::mat transmitAngleLOS(2, 1);
	arma::mat receiverAngleLOS(2, 1);
	transmitAngleLOS(0, 0) = MS[src]->channel->GCSAOD;
	transmitAngleLOS(1, 0) = MS[src]->channel->GCSZOD;
	receiverAngleLOS(0, 0) = MS[src]->channel->GCSAOA;
	receiverAngleLOS(1, 0) = MS[src]->channel->GCSZOA;

	arma::mat ReceiverAntennaGainXLOS;
	arma::mat ReceiverAntennaGainULOS = ReceiverAntennaGain(src,zetaRx1, receiverAngleLOS);
	if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) ReceiverAntennaGainXLOS = ReceiverAntennaGain(src, zetaRx2, receiverAngleLOS);;
	arma::cx_mat f_prd_LOS = exp_F_prd(src, alpha[sector], beta, gamma, transmitAngleLOS * 180 / PI, numTxHorizontalAntenna, numTxVerticalAntenna, numTxPort);
	arma::cx_mat f_urd_LOS = exp_F_urd(src, receiverAngleLOS * 180 / PI, numRxAntenna);

	MS[src]->channel->F_prd_LOS(dst, 0) = f_prd_LOS;
	MS[src]->channel->F_urd_LOS(dst, 0) = f_urd_LOS;
	
	arma::cx_mat TransmitterAntennaGainXLOS;
	arma::cx_mat TransmitterAntennaGainULOS;
	for (int processIndex = 0; processIndex < numProcess; processIndex++) {
		TransmitterAntennaGainULOS = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx1, transmitAngleLOS, dst, numProcess);
		if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) TransmitterAntennaGainXLOS = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx2, transmitAngleLOS, dst, numProcess);
	}

// Save
	MS[src]->channel->ReceiverAntennaGainLOSUH = ReceiverAntennaGainULOS(0, 0);
	MS[src]->channel->ReceiverAntennaGainLOSUV = ReceiverAntennaGainULOS(1, 0);

	if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) 
	{
		MS[src]->channel->ReceiverAntennaGainLOSXH = ReceiverAntennaGainXLOS(0, 0);
		MS[src]->channel->ReceiverAntennaGainLOSXV = ReceiverAntennaGainXLOS(1, 0);
	}

	MS[src]->channel->TransmitterAntennaGainLOSUH = TransmitterAntennaGainULOS(0, 0);
	MS[src]->channel->TransmitterAntennaGainLOSUV = TransmitterAntennaGainULOS(1, 0);

	if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) 
	{
		MS[src]->channel->TransmitterAntennaGainLOSXH = TransmitterAntennaGainXLOS(0, 0);
		MS[src]->channel->TransmitterAntennaGainLOSXV = TransmitterAntennaGainXLOS(1, 0);
	}




	for (int n = 0; n < numRealCluster; n++) {
		for (int m = 0; m < 20; m++) {

			receiveAngle(0, 0) = MS[src]->channel->SmallScaleAOA(n, m);
			receiveAngle(1, 0) = MS[src]->channel->SmallScaleZOA(n, m);
			receiveAngle = receiveAngle*PI / 180.0;

			transmitAngle(0, 0) = MS[src]->channel->SmallScaleAOD(n, m);
			transmitAngle(1, 0) = MS[src]->channel->SmallScaleZOD(n, m);
			//transmitAngle = transmitAngle*PI / 180.0;

			arma::mat antennaGainRxSmallX;
			arma::mat antennaGainRxSmallU = ReceiverAntennaGain(src, zetaRx1, receiveAngle);
			if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) antennaGainRxSmallX = ReceiverAntennaGain(src, zetaRx2, receiveAngle);

			MS[src]->channel->SmallScaleReceiverAntennaGainUH(n, m) = antennaGainRxSmallU(0, 0);
			MS[src]->channel->SmallScaleReceiverAntennaGainUV(n, m) = antennaGainRxSmallU(1, 0);

			if (Sim.channel->MsAntennaModel == CHANNEL::CrossPolarization) {
				MS[src]->channel->SmallScaleReceiverAntennaGainXH(n, m) = antennaGainRxSmallX(0, 0);
				MS[src]->channel->SmallScaleReceiverAntennaGainXV(n, m) = antennaGainRxSmallX(1, 0);
			}

			MS[src]->channel->F_urd(n, m) = exp_F_urd(src, receiveAngle*(180 / PI), numRxAntenna);
			MS[src]->channel->F_urd_BS(dst, n, m) = MS[src]->channel->F_urd(n, m);
			MS[src]->channel->F_prd(n, m) = exp_F_prd(src, alpha[sector], 0.0, 0.0, transmitAngle *PI / 180.0, numTxHorizontalAntenna, numTxVerticalAntenna, numTxPort);
			MS[src]->channel->F_prd_BS(dst, n, m) = MS[src]->channel->F_prd(n, m);
			arma::cx_mat antennaGainTxSmallX;
			for (int indexProcess = 0; indexProcess < numProcess; indexProcess++) {
				arma::cx_mat antennaGainTxSmallU = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx1, transmitAngle *PI / 180.0, dst, numProcess);
				if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) antennaGainTxSmallX = TransmitterAntennaGain(src, alpha[sector], beta, gamma, zetaTx1, transmitAngle *PI / 180.0, dst, numProcess);
			
			MS[src]->channel->SmallScaleTransmitterAntennaGainUH(n, m) = antennaGainTxSmallU(0, 0);
			MS[src]->channel->SmallScaleTransmitterAntennaGainUV(n, m) = antennaGainTxSmallU(1, 0);

			if (Sim.channel->BsAntennaModel == CHANNEL::CrossPolarization) {
				MS[src]->channel->SmallScaleTransmitterAntennaGainXH(n, m) = antennaGainTxSmallX(0, 0);
				MS[src]->channel->SmallScaleTransmitterAntennaGainXV(n, m) = antennaGainTxSmallX(1, 0);
			}
			
			}
		}
	}

}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         Level 4 Functions                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

double SpatialChannel::Distance2D(double srcX, double srcY, double dstX, double dstY) {
	double distance2D;

	distance2D = sqrt(pow((dstX - srcX), 2) + pow((dstY - srcY), 2));

	return distance2D;
}

double SpatialChannel::Distance3D(double srcX, double srcY, double srcZ, double dstX, double dstY, double dstZ) {
	double distance3D;

	distance3D = sqrt(pow((dstX - srcX), 2) + pow((dstY - srcY), 2) + pow((dstZ - srcZ), 2));

	return distance3D;
}

double SpatialChannel::AzimuthAngleOfGlobalCoordinateSystem(double srcX, double srcY, double dstX, double dstY) {
	double azimuthAngle;

	azimuthAngle = atan2(dstY-srcY,dstX-srcX);

	return azimuthAngle;
}

double SpatialChannel::ZenithAngleOfGlobalCoordinateSystem(double srcX, double srcY, double srcZ, double dstX, double dstY, double dstZ){
	double zenithAngle;

	zenithAngle = atan2(Distance2D(srcX, srcY, dstX, dstY), dstZ - srcZ);

	return zenithAngle;
}

arma::mat SpatialChannel::GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(double alpha, double beta, double gamma, arma::mat angleGCS){ //GCS to LCS angle A Z / H V / pi theta
	arma::mat angleLCS(2,1);
	
	double pi = angleGCS(0, 0);		// ahpi
	double theta = angleGCS(1, 0);	// zvth
	angleLCS(1,0) = acosl(cos(beta) * cos(gamma) * cos(theta) + (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*sin(theta));
	angleLCS(0,0) = atan2l((cos(beta)*sin(gamma)*cos(theta) + (sin(beta)*sin(gamma)*cos(pi - alpha) + cos(gamma)*sin(pi - alpha))*sin(theta)), (cos(beta)*sin(theta)*cos(pi - alpha) - sin(beta)*cos(theta)));

	return angleLCS;
}

arma::mat SpatialChannel::LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(double alpha, double beta, double gamma, double theta, double pi, arma::mat antennaGain) { // LCS to GCS antenna gain
	arma::mat antennaGainGCS(2, 1);
	arma::mat psi(2,1);

	psi(0,0) = (cos(beta)*cos(gamma)*sin(theta) - (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*cos(theta)) / sqrt(1.0 - pow(cos(beta)*cos(gamma)*cos(theta) + (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*sin(theta), 2)); // cos psi
	psi(1,0) = (sin(beta)*cos(gamma)*sin(pi - alpha) + sin(gamma)*cos(pi - alpha)) / sqrt(1.0 - pow(cos(beta)*cos(gamma)*cos(theta) + (sin(beta)*cos(gamma)*cos(pi - alpha) - sin(gamma)*sin(pi - alpha))*sin(theta), 2));												  // sin psi

	antennaGainGCS(1, 0) = psi(0, 0) * antennaGain(1, 0) - psi(1, 0) *antennaGain(0, 0);
	antennaGainGCS(0, 0) = psi(1, 0) * antennaGain(1, 0) + psi(0, 0) * antennaGain(0, 0);

	return antennaGainGCS;
}

double SpatialChannel::AntennaGain(arma::mat angleLCS) // 0 H 1 V
{
//	double antennaGainVertical;
//	double antennaGainHorizontal;angleLCS(0,0)angleLCS(1,0)
//	double antennaGainCombined;

//	antennaGainVertical = -min( 12 * pow( ( ((angleLCS(1, 0)*180.0 / PI) - 90.0) / 65.0), 2)  ,              30.0);
//	antennaGainHorizontal = -min(12 * pow( ( (angleLCS(0, 0)*180.0 / PI) / 65.0)        , 2)  ,              30.0);
//	antennaGainCombined = (8 - min(-(antennaGainVertical + antennaGainHorizontal), 30.0));
//	return antennaGainCombined;
	double antennaGainVertical = -min(12 * pow(((angleLCS(1,0)*180.0 / PI - 90.0) / 65.0), 2), 30.0);
	double antennaGainHorizontal = -min(12 * pow(((angleLCS(0,0)*180.0 / PI) / 65.0), 2), 30.0);
	double antennaGainCombined = (8 - min(-(antennaGainVertical + antennaGainHorizontal), 30.0));
	return antennaGainCombined;
	
}

double SpatialChannel::Modulo(double a, double b) {
	if (b == 0)
	{
		return 0;
	}
	else
	{
		double n = floor(a / b);
		return a - n*b;
	}
}

arma::mat SpatialChannel::ReceiverAntennaGain(int src, int zeta, arma::mat angleGCS) { // 
	arma::mat angleLCS;

	MS[src]->channel->antennaOrientation.zeros(3, 1);
	MS[src]->channel->antennaOrientation(0, 0) = arma::randu() * 360 * PI / 180;
	MS[src]->channel->antennaOrientation(1, 0) = 90.0*PI / 180;
	MS[src]->channel->antennaOrientation(2, 0) = 0;
	
	angleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(MS[src]->channel->antennaOrientation(0, 0), 0, MS[src]->channel->antennaOrientation(2, 0), angleGCS);

	arma::mat antennaGainLCS2(2, 1); // 0 H 1 V
	arma::mat antennaGainLCS(2, 1); // 0 H 1 V
	arma::mat antennaGainGCS(2, 1); // 0 H 1 V


	antennaGainLCS2(0, 0) = 0;
	antennaGainLCS2(1, 0) = 1.0;

	if (Sim.channel->PolarizedAntennaModel == 0) {
		antennaGainLCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(0.0, 0.0, zeta, angleLCS(1,0), angleLCS(0,0), antennaGainLCS2);
		antennaGainGCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(MS[src]->channel->antennaOrientation(0, 0), 0.0, 0.0, angleGCS(1, 0), angleGCS(0, 0), antennaGainLCS);
	}
	else {
		antennaGainLCS = antennaGainLCS2;
		antennaGainGCS(1,0) = antennaGainLCS(1,0) * cos(zeta);
		antennaGainGCS(0,0) = antennaGainLCS(0,0) * sin(zeta);
	}


	return antennaGainGCS;
}

arma::cx_mat SpatialChannel::TransmitterAntennaGain(int src, double alpha, double beta, double gamma, double zeta, arma::mat angleGCS, int i, int numProcess) // i = BS index
{
	arma::mat angleLCS;
	arma::mat angleLCS2;
	
	arma::mat antennaGainLCS2;
	arma::mat antennaGainLCS;
	arma::mat antennaGainGCS;
	arma::cx_mat F_tx(2, 1);
	arma::vec tiltm(8);
	tiltm << 102 << 40 << 60 << 80 << 100 << 120 << 140 << 160 << arma::endr;

	
	BS[i]->channel->numVerticalAntenna = 8;
	antennaGainLCS2.zeros(2, 1);
	antennaGainLCS.zeros(2, 1);


	int K_MEANS = 0; // 나중에 뭔지 확인하고 처리
	//angle prime = GCStoLCS_angle(alpha, beta, gamma, A_V, A_H);
	angleLCS = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(alpha, beta, gamma, angleGCS);
	angleLCS2 = GlobalCoordinateSystemAngleToLocalCoordinateSystemAngle(0, 0, zeta, angleLCS);
		
	antennaGainLCS2(1, 0) = sqrt(pow(10.0, AntennaGain(angleLCS2) / 10.0));
	antennaGainLCS2(0, 0) = 0.0;
	Sim.channel->PolarizedAntennaModel = 0;
	if (Sim.channel->PolarizedAntennaModel == 0) {
		antennaGainLCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(0, 0, zeta, angleLCS(1,0), angleLCS(0,0), antennaGainLCS2);
		antennaGainGCS = LocalCoordinateSystemAntennaGainToGlobalCoordinateSystemAntennaGain(alpha, beta, gamma, angleGCS(1, 0), angleGCS(0, 0), antennaGainLCS);
	}
	else {
		antennaGainLCS = antennaGainLCS2;
		antennaGainGCS(1, 0) = antennaGainLCS(1, 0) * cos(zeta);
		antennaGainGCS(0, 0) = antennaGainLCS(0, 0) * sin(zeta);
	}


	Sim.channel->AntennaTilting = 1;
	if (Sim.channel->AntennaTilting == 1) { // tilt
		double F_tempReal = 0.0;
		double F_tempImag = 0.0;
		double F_temp1Real = 0.0;
		double F_temp1Imag = 0.0; // H real H image endr V real V image endr
		//F_temp(0, 0) = 0;  F_temp1(0, 0) = 0; // real image real image
		for (int p = 0; p < BS[i]->channel->numVerticalAntenna; p++) {
			arma::cx_mat wei(1, 1);
					
			wei(0, 0) = 1i*(-(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave)*p*(Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * 1.6)*cos(tiltm(numProcess) * PI / 180.0));
		
			arma::mat Rd = DistanceAngular(alpha, beta, gamma, 0.0, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * 1.6 * p);
			arma::cx_mat ant_co(1, 1);
			ant_co(0, 0) = 1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
			
			F_tempReal = F_tempReal + (antennaGainGCS(1, 0)* (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * real(exp(wei(0, 0)) * exp(ant_co(0, 0))));
			F_tempImag = F_tempImag + (antennaGainGCS(1, 0)* (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * imag(exp(wei(0, 0)) * exp(ant_co(0, 0))));

			F_temp1Real = F_temp1Real + antennaGainGCS(0, 0)* (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * real(exp(wei(0, 0)) * exp(ant_co(0, 0)));
			F_temp1Imag = F_temp1Imag + antennaGainGCS(0, 0) * (1.0 / sqrt(BS[i]->channel->numVerticalAntenna)) * imag(exp(wei(0, 0)) * exp(ant_co(0, 0)));
		}
		F_tx(1, 0) = F_tempReal + 1i* F_tempImag;
		F_tx(0, 0) = F_temp1Real + 1i* F_temp1Imag;
	}
	else {
		F_tx(1, 0) = antennaGainGCS(1, 0); 
		F_tx(0, 0) = antennaGainGCS(0, 0); 
	}

	arma::cx_mat txAntennaGainGCS = F_tx;
	return txAntennaGainGCS;
}

arma::mat SpatialChannel::DistanceAngular(double a, double b, double c, double x, double y, double z) {
	arma::mat Rd(3,1);
	
	Rd(0, 0) = cos(a)*cos(b) * x + cos(a)*sin(b)*sin(c) - sin(a)*cos(c) * y + cos(a)*sin(b)*cos(c) + sin(a)*sin(c) * z;
	Rd(1, 0) = sin(a)*cos(b) * x + sin(a)*sin(b)*sin(c) + cos(a)*cos(c) * y + sin(a)*sin(b)*cos(c) - cos(a)*sin(c) * z;
	Rd(2, 0) = -sin(b)		 * x + cos(b)*sin(c)					   * y + cos(b)*cos(c)						* z;

	return Rd;
}

arma::cx_mat SpatialChannel::exp_F_urd(int src, arma::mat A, int numRxAntenna)
{
	arma::mat Rd(3,1);
	arma::cx_mat Furd;
	Furd.zeros(numRxAntenna, 1);
	for (int u = 0; u < numRxAntenna; u++) {
		if (Sim.channel->MsAntennaModel == CHANNEL::UniformLinearArray) {
			Rd = DistanceAngular(MS[src]->channel->antennaOrientation(0, 0) , MS[src]->channel->antennaOrientation(1, 0), MS[src]->channel->antennaOrientation(2, 0), 0.0, Sim.channel->WaveLengthOfElectomageneticWave * 0.5 * u, 0.0); 
			Furd(u, 0) = 0.0+ 1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(A(1, 0))*cos(A(0, 0))*Rd(0, 0) + sin(A(1, 0))*sin(A(0, 0))*Rd(1, 0) + cos(A(1, 0))*Rd(2, 0)));
		}
		else {
			Furd(u, 0) = (0.0)+1i*(0.0);
		}
	}
	return Furd;
}

arma::cx_mat SpatialChannel::exp_F_prd(int src, double alpha, double beta, double gamma, arma::mat angleGCS, int numTxHorizontalAntenna, int numTxVerticalAntenna,int numTxPort)
{
	int tx_port = 0;
	double mul_V = 1.6;
	arma::mat Rd(3,1);
	arma::cx_mat F_prd;
	F_prd.zeros(numTxHorizontalAntenna, 1);
	if (Sim.channel->BsAntennaModel== CHANNEL::UniformLinearArray) {
		for (int u = 0; u < numTxHorizontalAntenna; u++) {
			if (numTxPort - numTxHorizontalAntenna != 0) {
				for (int p = 0; p < numTxVerticalAntenna; p++) {
					Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * mul_V* p);
					F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
					tx_port++;
				}
			}
			else {
				Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, 0.0);
				F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
				tx_port++;
			}
		}
	}
	else {
		for (int u = 0; u<numTxHorizontalAntenna / 2; u++) {
			if (numTxPort - numTxHorizontalAntenna != 0) {
				for (int p = 0; p<numTxVerticalAntenna; p++) {
					Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * mul_V* p);
					F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0))*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0)));
					F_prd[tx_port + numTxHorizontalAntenna / 2] = F_prd[tx_port];
					tx_port++;
				}
			}
			else {
				Rd = DistanceAngular(alpha, beta, gamma, 0.0, Sim.channel->WaveLengthOfElectomageneticWave / 2.0 * u, 0.0);
				F_prd[tx_port]=(0.0)+1i*(2.0*PI / Sim.channel->WaveLengthOfElectomageneticWave*(sin(angleGCS(1, 0))*cos(angleGCS(0, 0))*Rd(0, 0) + sin(angleGCS(1, 0))*sin(angleGCS(0, 0)*Rd(1, 0) + cos(angleGCS(1, 0))*Rd(2, 0))));
				F_prd[tx_port + numTxHorizontalAntenna / 2] = F_prd[tx_port];
				tx_port++;
			}
		}
	}

	return F_prd;
}