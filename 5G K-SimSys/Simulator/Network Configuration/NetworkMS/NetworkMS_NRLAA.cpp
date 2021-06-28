/****************************************************************************

Network Configuration for Mobile Station (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkMS_FD MIMO.cpp
DATE         : 2016.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.15	Minsig Han	 	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "NetworkMS_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void NetworkMS::Initialize(int msID, int bsID)
{

	this->id = msID; // MS ID
	this->attachedBS = bsID; // Temporary association	
	this->pos3D;
	this->location;
	this->interArrivalTime.zeros(Sim.numTTI);

	// MS Placement
	if (Sim.network->NetworkModel == NETWORK::IndoorOffice) {
		this->PlaceRandomRectangular();
	}

	if (Sim.network->bufferModel == RRM::FullBuffer) {
		// Buffer Size
	}
	else if (Sim.network->bufferModel == RRM::NonFullBuffer) {
		for (int tti = 0; tti < Sim.numTTI; tti++) {
			this->interArrivalTime(tti) = ceil(-(1 / Sim.network->meanArrivalTime)*log(1 - arma::randu()) * 10 / 5);
		}
		this->bufferTime = 0;
		this->msBuffer = 0;
		this->arrivalTime = 0;
	}

}

void NetworkMS::PlaceRandomRectangular()
{
	// Uniform, random MS placement in a rectangular grid
	arma::cx_double p;
	this->pos = 120 * arma::randu() + 50 * arma::randu() * 1i;
	this->height = Sim.network->IndoorOffice.height;
	this->pos3D << pos.real() << pos.imag() << height;
}

void NetworkMS::PlaceRandomCircular()
{
	// Uniform, random MS placement in a circular grid
	arma::cx_double p;
	this->pos = 120 * arma::randu() + 50 * arma::randu() * 1i;
	this->height = Sim.network->IndoorOffice.height;
	this->pos3D << pos.real() << pos.imag() << height;
}

void NetworkMS::WrapAround()
{
	//int id = ms; // MS ID
	complex<double> vector;
	arma::cx_mat temp(1, Sim.network->numWraparound);
	arma::cx_mat wraparound(1, Sim.network->numSite);
	this->wraparoundposBS.zeros(Sim.network->numSite, 3);
	arma::mat x, y, z;
	z.ones(Sim.network->numSite, 1);
	z = z*Sim.network->UrbanMacroCell.height;
	for (int i = 0; i < Sim.network->numSite; i++) // Long term channel calculation
	{
		for (int j = 0; j < Sim.network->numWraparound; j++)
		{
			vector = abs(MS[id]->network->pos - (Sim.network->posWraparound[j] + BS[Sim.network->numSector * i]->network->pos));
			temp(j) = vector;
		}
		arma::uword index = temp.index_min();
		wraparound(i) = Sim.network->posWraparound[index] + BS[Sim.network->numSector * i]->network->pos;
	}
	x = arma::real(arma::trans(wraparound));
	y = -arma::imag(arma::trans(wraparound));
	this->wraparoundposBS.submat(arma::span(0, Sim.network->numSite - 1), arma::span(0, 0)) = x;
	this->wraparoundposBS.submat(arma::span(0, Sim.network->numSite - 1), arma::span(1, 1)) = y;
	this->wraparoundposBS.submat(arma::span(0, Sim.network->numSite - 1), arma::span(2, 2)) = z;
}

arma::mat NetworkMS::LargeScaleParameter(int channelModel, int channelCondition, int msID, int bsID) {
	arma::mat LargeScaleParameter;
	LargeScaleParameter.zeros(7, 1);
	arma::mat correlationMatrix;
	correlationMatrix.zeros(7, 7);
	arma::mat largeScaleParameter(7, 1);
	largeScaleParameter.zeros(7, 1);
	arma::mat correlationMatrixCholeskyDecomposed(7, 7);
	correlationMatrixCholeskyDecomposed.zeros(7, 7);
	SpatialChannel spatialChannel;
	spatialChannel.Initialize();
	// 
	MS[msID]->network->location = 1;

	if ((MS[msID]->channel->channelCondition == LOS)) {
		correlationMatrix << 1 << spatialChannel.IndoorOfficeLOS.SFvsK << spatialChannel.IndoorOfficeLOS.DSvsSF << spatialChannel.IndoorOfficeLOS.ASDvsSF << spatialChannel.IndoorOfficeLOS.ASAvsSF << spatialChannel.IndoorOfficeLOS.ZSDvsSF << spatialChannel.IndoorOfficeLOS.ZSAvsSF << arma::endr
			<< spatialChannel.IndoorOfficeLOS.SFvsK << 1 << spatialChannel.IndoorOfficeLOS.DSvsK << spatialChannel.IndoorOfficeLOS.ASDvsK << spatialChannel.IndoorOfficeLOS.ASAvsK << spatialChannel.IndoorOfficeLOS.ZSDvsK << spatialChannel.IndoorOfficeLOS.ZSAvsK << arma::endr
			<< spatialChannel.IndoorOfficeLOS.DSvsSF << spatialChannel.IndoorOfficeLOS.DSvsK << 1 << spatialChannel.IndoorOfficeLOS.ASDvsDS << spatialChannel.IndoorOfficeLOS.ASAvsDS << spatialChannel.IndoorOfficeLOS.ZSDvsDS << spatialChannel.IndoorOfficeLOS.ZSAvsDS << arma::endr
			<< spatialChannel.IndoorOfficeLOS.ASDvsSF << spatialChannel.IndoorOfficeLOS.ASDvsK << spatialChannel.IndoorOfficeLOS.ASDvsDS << 1 << spatialChannel.IndoorOfficeLOS.ASDvsASA << spatialChannel.IndoorOfficeLOS.ZSDvsASD << spatialChannel.IndoorOfficeLOS.ZSAvsASD << arma::endr
			<< spatialChannel.IndoorOfficeLOS.ASAvsSF << spatialChannel.IndoorOfficeLOS.ASAvsK << spatialChannel.IndoorOfficeLOS.ASAvsDS << spatialChannel.IndoorOfficeLOS.ASDvsASA << 1 << spatialChannel.IndoorOfficeLOS.ZSDvsASA << spatialChannel.IndoorOfficeLOS.ZSDvsASA << arma::endr
			<< spatialChannel.IndoorOfficeLOS.ZSDvsSF << spatialChannel.IndoorOfficeLOS.ZSDvsK << spatialChannel.IndoorOfficeLOS.ZSDvsDS << spatialChannel.IndoorOfficeLOS.ZSDvsASD << spatialChannel.IndoorOfficeLOS.ZSDvsASA << 1 << spatialChannel.IndoorOfficeLOS.ZSDvsZSA << arma::endr
			<< spatialChannel.IndoorOfficeLOS.ZSAvsSF << spatialChannel.IndoorOfficeLOS.ZSAvsK << spatialChannel.IndoorOfficeLOS.ZSAvsDS << spatialChannel.IndoorOfficeLOS.ZSAvsASD << spatialChannel.IndoorOfficeLOS.ZSAvsASA << spatialChannel.IndoorOfficeLOS.ZSDvsZSA << 1 << arma::endr;
	}

	else if ((MS[msID]->channel->channelCondition == NLOS)) {
		correlationMatrix << 1 << spatialChannel.IndoorOfficeNLOS.SFvsK << spatialChannel.IndoorOfficeNLOS.DSvsSF << spatialChannel.IndoorOfficeNLOS.ASDvsSF << spatialChannel.IndoorOfficeNLOS.ASAvsSF << spatialChannel.IndoorOfficeNLOS.ZSDvsSF << spatialChannel.IndoorOfficeNLOS.ZSAvsSF << arma::endr
			<< spatialChannel.IndoorOfficeNLOS.SFvsK << 1 << spatialChannel.IndoorOfficeNLOS.DSvsK << spatialChannel.IndoorOfficeNLOS.ASDvsK << spatialChannel.IndoorOfficeNLOS.ASAvsK << spatialChannel.IndoorOfficeNLOS.ZSDvsK << spatialChannel.IndoorOfficeNLOS.ZSAvsK << arma::endr
			<< spatialChannel.IndoorOfficeNLOS.DSvsSF << spatialChannel.IndoorOfficeNLOS.DSvsK << 1 << spatialChannel.IndoorOfficeNLOS.ASDvsDS << spatialChannel.IndoorOfficeNLOS.ASAvsDS << spatialChannel.IndoorOfficeNLOS.ZSDvsDS << spatialChannel.IndoorOfficeNLOS.ZSAvsDS << arma::endr
			<< spatialChannel.IndoorOfficeNLOS.ASDvsSF << spatialChannel.IndoorOfficeNLOS.ASDvsK << spatialChannel.IndoorOfficeNLOS.ASDvsDS << 1 << spatialChannel.IndoorOfficeNLOS.ASDvsASA << spatialChannel.IndoorOfficeNLOS.ZSDvsASD << spatialChannel.IndoorOfficeNLOS.ZSAvsASD << arma::endr
			<< spatialChannel.IndoorOfficeNLOS.ASAvsSF << spatialChannel.IndoorOfficeNLOS.ASAvsK << spatialChannel.IndoorOfficeNLOS.ASAvsDS << spatialChannel.IndoorOfficeNLOS.ASDvsASA << 1 << spatialChannel.IndoorOfficeNLOS.ZSDvsASA << spatialChannel.IndoorOfficeNLOS.ZSDvsASA << arma::endr
			<< spatialChannel.IndoorOfficeNLOS.ZSDvsSF << spatialChannel.IndoorOfficeNLOS.ZSDvsK << spatialChannel.IndoorOfficeNLOS.ZSDvsDS << spatialChannel.IndoorOfficeNLOS.ZSDvsASD << spatialChannel.IndoorOfficeNLOS.ZSDvsASA << 1 << spatialChannel.IndoorOfficeNLOS.ZSDvsZSA << arma::endr
			<< spatialChannel.IndoorOfficeNLOS.ZSAvsSF << spatialChannel.IndoorOfficeNLOS.ZSAvsK << spatialChannel.IndoorOfficeNLOS.ZSAvsDS << spatialChannel.IndoorOfficeNLOS.ZSAvsASD << spatialChannel.IndoorOfficeNLOS.ZSAvsASA << spatialChannel.IndoorOfficeNLOS.ZSDvsZSA << 1 << arma::endr;
	}
	correlationMatrixCholeskyDecomposed = arma::chol(correlationMatrix, "lower");
	LargeScaleParameter = correlationMatrixCholeskyDecomposed*arma::randn(7, 1);

	largeScaleParameter[0] = spatialChannel.IndoorOfficeLOS.sigmaShadowing*LargeScaleParameter(0);
	largeScaleParameter[1] = spatialChannel.IndoorOfficeLOS.sigmaRiceanK*LargeScaleParameter(1) + spatialChannel.IndoorOfficeLOS.muRiceanK;
	largeScaleParameter[2] = pow(10.0, spatialChannel.IndoorOfficeLOS.epsilonDelaySpread*LargeScaleParameter(2) + spatialChannel.IndoorOfficeLOS.muDelaySpread);
	largeScaleParameter[3] = min(pow(10.0, spatialChannel.IndoorOfficeLOS.epsilonASD*LargeScaleParameter(3) + spatialChannel.IndoorOfficeLOS.muASD), 104.0);
	largeScaleParameter[4] = min(pow(10.0, spatialChannel.IndoorOfficeLOS.epsilonASA*LargeScaleParameter(4) + spatialChannel.IndoorOfficeLOS.muASA), 104.0);
	largeScaleParameter[5] = min(pow(10.0, spatialChannel.IndoorOfficeLOS.epsilonZSD*LargeScaleParameter(5) + spatialChannel.IndoorOfficeLOS.muZSD), 52.0);
	largeScaleParameter[6] = min(pow(10.0, spatialChannel.IndoorOfficeLOS.epsilonZSA*LargeScaleParameter(6) + spatialChannel.IndoorOfficeLOS.muZSA), 52.0);

	return largeScaleParameter;
}

void NetworkMS::Associate(int msID, arma::vec RSRP)
{
	arma::uvec interferenceIndex(SLS_MAX_BS); interferenceIndex.zeros(SLS_MAX_BS);
	arma::uvec indices; indices.zeros(SLS_MAX_BS);
	indices = arma::sort_index(RSRP, "descend");
	for (int l = 0; l < Sim.network->numBS; l++)
		interferenceIndex(l) = indices(l);

	MS[msID]->channel->associatedBsIndex = indices(0);
	BS[indices(0)]->network->attachedMS[BS[indices(0)]->channel->NumAssociatedMS] = msID;
	BS[indices(0)]->channel->NumAssociatedMS = BS[indices(0)]->channel->NumAssociatedMS + 1;
	MS[msID]->channel->BSindex = interferenceIndex;
}

void NetworkMS::ConcludeIteration()
{

}

void NetworkMS::Conclude() {

}