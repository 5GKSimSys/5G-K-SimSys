/****************************************************************************

Channel Model for Base Station (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : ChannelBS_simple.cpp
DATE         : 2017.02.01
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.02.01	Minsig Han      Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "ChannelBS_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void ChannelBS::Initialize(int bs, int site, int sector)
{
	id = bs;
	site = site;
	sector = sector;
	NumAssociatedMS = 0;

}

void ChannelBS::LongTermChannel(int bsID) {

	//	spatialChannel = new SpatialChannel();
	//// BS-to-MS channel
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

	//// MS-to-MS channel
	//for (int bsID = 0, site = 0; site < Sim.network->numSite; site++)
	//{

	//}

	for (int bsID = 0, site = 0; site < Sim.network->numSite; site++) {
		//GeneralParameters(bsID, site);
		//for (int sector = 0; sector < Sim.network->numSector; sector++, bsID++) {
			//SmallScaleParameter(bsID, bsID, site, sector);
			//CoefficientGeneration(bsID, bsID, site, sector);
		//}
	}
	//ChannelCoefficient(bsID);
	//ApplyPathLossAndShadowing(bsID);

}

void ChannelBS::GeneralParameters(int bsID, int site) {
	SpatialChannel spatialChannel;
	spatialChannel.Initialize();
	if (Sim.network->NetworkModel == NETWORK::UrbanMacroCell || Sim.network->NetworkModel == NETWORK::DenseUrban || Sim.network->NetworkModel == NETWORK::RuralMacroCell) {
		BS[bsID]->channel->distance2D = spatialChannel.Distance2D(BS[bsID]->network->pos3D(0, 0), BS[bsID]->network->pos3D(0, 1), BS[bsID]->network->wraparoundposBS(site, 0), BS[bsID]->network->wraparoundposBS(site, 1));
		BS[bsID]->channel->distance3D = spatialChannel.Distance3D(BS[bsID]->network->pos3D(0, 0), BS[bsID]->network->pos3D(0, 1), BS[bsID]->network->pos3D(0, 2), BS[bsID]->network->wraparoundposBS(site, 0), BS[bsID]->network->wraparoundposBS(site, 1), BS[bsID]->network->wraparoundposBS(site, 2));
	}
	else if (Sim.network->NetworkModel == NETWORK::IndoorOffice) {
		BS[bsID]->channel->distance2D = spatialChannel.Distance2D(BS[bsID]->network->pos3D(0, 0), BS[bsID]->network->pos3D(0, 1), BS[site]->network->pos3D(0, 0), BS[site]->network->pos3D(0, 1));
		BS[bsID]->channel->distance3D = spatialChannel.Distance3D(BS[bsID]->network->pos3D(0, 0), BS[bsID]->network->pos3D(0, 1), BS[bsID]->network->pos3D(0, 2), BS[site]->network->pos3D(0, 0), BS[site]->network->pos3D(0, 1), BS[site]->network->pos3D(0, 2));
	}
	// cout << "Pathloss calculated" << endl;
	spatialChannel.Pathloss(bsID, site);
	BS[bsID]->channel->largeScaleParameter = BS[bsID]->network->LargeScaleParameter(Sim.channel->ChannelModel, BS[bsID]->channel->channelCondition, bsID, site); // ShadowFading, RiceanK, DelaySpread, rmsASD, rmsASA, rmsZSD, rmsZSA
}