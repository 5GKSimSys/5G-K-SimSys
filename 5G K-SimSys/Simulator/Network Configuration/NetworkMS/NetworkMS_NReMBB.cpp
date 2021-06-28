/****************************************************************************

Network Configuration for Mobile Station (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkMS_NReMBB.cpp
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

#include "NetworkMS_NReMBB.h"
#include "../Network/Network_NReMBB.h"

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
	if (Sim.network->NetworkModel == NETWORK::UrbanMacroCell){
		this->PlaceRandomHexagonal(); 
	}
	else if (Sim.network->NetworkModel == NETWORK::DenseUrban) {
		if (bsID % (Sim.network->numSector*Sim.network->numMicroBS + 1))
			this->PlaceRandomHexagonal(); 
		else
			this->PlaceRandomCircular();
	}
	else if (Sim.network->NetworkModel == NETWORK::IndoorOffice) {
		this->PlaceRandomRectangular(); 
	}
	else if (Sim.network->NetworkModel == NETWORK::RuralMacroCell) {
		this->PlaceRandomHexagonal(); 
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

void NetworkMS::PlaceRandomHexagonal()
{
	// Uniform, random MS placement in a hexagonal grid

	arma::cx_double p;
	double A = sqrt(3) / 2;
	double interSiteDistance;
	double height;
	double minDistanceToBS;

	if (Sim.network->NetworkModel == NETWORK::UrbanMacroCell) {
		int minDistanceCheck = 0;
		minDistanceToBS = Sim.network->UrbanMacroCell.minDistanceToBS;

		while (minDistanceCheck == 0)
		{
			p = arma::randu() / 2 + 1i * arma::randu() / sqrt(3);
			if (p.imag() > ((1 - p.real()) / sqrt(3)))
				p = (p - 1i * 1.0 / sqrt(3)) * exp(1i * 2.0 * PI * 1.0 / 3.0);
			p = exp(1i * 2.0 * PI * (1 / 2 + floor(arma::randu() * 3) / 3)) * p;
			p = 1.0 / 2.0 + 1i / (2.0 * sqrt(3)) + p;
			p = exp(1i * 2.0 * PI * (double)(attachedBS - 1 % 3) / 3.0) * p;
			pos = BS[this->attachedBS]->network->pos + p * 2.0 / 3.0 * A * Sim.network->UrbanMacroCell.interSiteDistance;
			if (abs(this->pos) > minDistanceToBS)	minDistanceCheck = 1;
		}

		if (Sim.network->UrbanMacroCell.indoorMsFraction / 100 > arma::randu()) // indoor == 1, outdoor == 0
		{
			this->location = Indoor;
			this->indoorDistance2D = arma::randu() * 25;

			height = 3 * (rand() % ((rand() % 5) + 4)) + 1.5;
		}
		else
		{
			this->location = Outdoor;
			this->indoorDistance2D = 0;

			height = 1.5;
		}
		this->pos3D << pos.real() << pos.imag() << height;
	}

	else if (Sim.network->NetworkModel == NETWORK::DenseUrban) {
		int minDistanceCheck = 0;
		minDistanceToBS = Sim.network->UrbanMacroCell.minDistanceToBS;
		
		while (minDistanceCheck == 0)
		{
			p = arma::randu() / 2 + 1i * arma::randu() / sqrt(3);
			if (p.imag() > ((1 - p.real()) / sqrt(3)))
				p = (p - 1i * 1.0 / sqrt(3)) * exp(1i * 2.0 * PI * 1.0 / 3.0);
			p = exp(1i * 2.0 * PI * (1 / 2 + floor(arma::randu() * 3) / 3)) * p;
			p = 1.0 / 2.0 + 1i / (2.0 * sqrt(3)) + p;
			p = exp(1i * 2.0 * PI * (double)(attachedBS - 1 % 3) / 3.0) * p;
			pos = BS[this->attachedBS]->network->pos + p * 2.0 / 3.0 * A * Sim.network->UrbanMacroCell.interSiteDistance;
			if (abs(this->pos) > minDistanceToBS)	minDistanceCheck = 1;
		}
			
		if (Sim.network->UrbanMacroCell.indoorMsFraction / 100 > arma::randu()) // indoor == 1, outdoor == 0
		{
			this->location = Indoor;
			this->indoorDistance2D = arma::randu() * 25;

			height = 3 * (rand() % ((rand() % 5) + 4)) + 1.5;
		}
		else
		{
			this->location = Outdoor;
			this->indoorDistance2D = 0;
		
			height = 1.5;
		}
		this->pos3D << pos.real() << pos.imag() << height;
	}

	else if (Sim.network->NetworkModel == NETWORK::RuralMacroCell) {
		int minDistanceCheck = 0;
		minDistanceToBS = Sim.network->RuralMacroCell.minDistanceToBS;

		while (minDistanceCheck == 0)
		{
			p = arma::randu() / 2 + 1i * arma::randu() / sqrt(3);
			if (p.imag() > ((1 - p.real()) / sqrt(3)))
				p = (p - 1i * 1.0 / sqrt(3)) * exp(1i * 2.0 * PI * 1.0 / 3.0);
			p = exp(1i * 2.0 * PI * (1 / 2 + floor(arma::randu() * 3) / 3)) * p;
			p = 1.0 / 2.0 + 1i / (2.0 * sqrt(3)) + p;
			p = exp(1i * 2.0 * PI * (double)(attachedBS - 1 % 3) / 3.0) * p;
			pos = BS[this->attachedBS]->network->pos + p * 2.0 / 3.0 * A * Sim.network->RuralMacroCell.interSiteDistance;
			if (abs(this->pos) > minDistanceToBS)	minDistanceCheck = 1;
		}

		if (Sim.network->RuralMacroCell.indoorMsFraction / 100 > arma::randu()) // indoor == 1, outdoor == 0
		{
			this->location = Indoor;
			this->indoorDistance2D = arma::randu() * 25;

			height = 3 * (rand() % ((rand() % 5) + 4)) + 1.5;
		}
		else
		{
			this->location = Outdoor;
			this->indoorDistance2D = 0;

			height = 1.5;
		}
		this->pos3D << pos.real() << pos.imag() << height;
	}

}

void NetworkMS::PlaceRandomRectangular()
{
	// Uniform, random MS placement in a rectangular grid
	arma::cx_double p;
	this->pos= 120 * arma::randu() + 50 * arma::randu() * 1i;
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
	arma::mat largeScaleParameter(7,1);
	largeScaleParameter.zeros(7, 1);
	arma::mat correlationMatrixCholeskyDecomposed(7,7);
	correlationMatrixCholeskyDecomposed.zeros(7, 7);
	SpatialChannel spatialChannel;
	spatialChannel.Initialize();

	switch (channelModel) {
	case SLS::DenseUrban:
		if ((MS[msID]->network->location == Outdoor) && (MS[msID]->channel->channelCondition == LOS)) {
			correlationMatrix << 1 << spatialChannel.UrbanMacroCellLOS.SFvsK << spatialChannel.UrbanMacroCellLOS.DSvsSF << spatialChannel.UrbanMacroCellLOS.ASDvsSF << spatialChannel.UrbanMacroCellLOS.ASAvsSF << spatialChannel.UrbanMacroCellLOS.ZSDvsSF << spatialChannel.UrbanMacroCellLOS.ZSAvsSF << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.SFvsK << 1 << spatialChannel.UrbanMacroCellLOS.DSvsK << spatialChannel.UrbanMacroCellLOS.ASDvsK << spatialChannel.UrbanMacroCellLOS.ASAvsK << spatialChannel.UrbanMacroCellLOS.ZSDvsK << spatialChannel.UrbanMacroCellLOS.ZSAvsK << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.DSvsSF << spatialChannel.UrbanMacroCellLOS.DSvsK << 1 << spatialChannel.UrbanMacroCellLOS.ASDvsDS << spatialChannel.UrbanMacroCellLOS.ASAvsDS << spatialChannel.UrbanMacroCellLOS.ZSDvsDS << spatialChannel.UrbanMacroCellLOS.ZSAvsDS << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ASDvsSF << spatialChannel.UrbanMacroCellLOS.ASDvsK << spatialChannel.UrbanMacroCellLOS.ASDvsDS << 1 << spatialChannel.UrbanMacroCellLOS.ASDvsASA << spatialChannel.UrbanMacroCellLOS.ZSDvsASD << spatialChannel.UrbanMacroCellLOS.ZSAvsASD << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ASAvsSF << spatialChannel.UrbanMacroCellLOS.ASAvsK << spatialChannel.UrbanMacroCellLOS.ASAvsDS << spatialChannel.UrbanMacroCellLOS.ASDvsASA << 1 << spatialChannel.UrbanMacroCellLOS.ZSDvsASA << spatialChannel.UrbanMacroCellLOS.ZSDvsASA << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ZSDvsSF << spatialChannel.UrbanMacroCellLOS.ZSDvsK << spatialChannel.UrbanMacroCellLOS.ZSDvsDS << spatialChannel.UrbanMacroCellLOS.ZSDvsASD << spatialChannel.UrbanMacroCellLOS.ZSDvsASA << 1 << spatialChannel.UrbanMacroCellLOS.ZSDvsZSA << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ZSAvsSF << spatialChannel.UrbanMacroCellLOS.ZSAvsK << spatialChannel.UrbanMacroCellLOS.ZSAvsDS << spatialChannel.UrbanMacroCellLOS.ZSAvsASD << spatialChannel.UrbanMacroCellLOS.ZSAvsASA << spatialChannel.UrbanMacroCellLOS.ZSDvsZSA << 1 << arma::endr;
		}

		else if ((MS[msID]->network->location == Outdoor) && (MS[msID]->channel->channelCondition == NLOS)) {
			correlationMatrix << 1 << spatialChannel.UrbanMacroCellNLOS.SFvsK << spatialChannel.UrbanMacroCellNLOS.DSvsSF << spatialChannel.UrbanMacroCellNLOS.ASDvsSF << spatialChannel.UrbanMacroCellNLOS.ASAvsSF << spatialChannel.UrbanMacroCellNLOS.ZSDvsSF << spatialChannel.UrbanMacroCellNLOS.ZSAvsSF << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.SFvsK << 1 << spatialChannel.UrbanMacroCellNLOS.DSvsK << spatialChannel.UrbanMacroCellNLOS.ASDvsK << spatialChannel.UrbanMacroCellNLOS.ASAvsK << spatialChannel.UrbanMacroCellNLOS.ZSDvsK << spatialChannel.UrbanMacroCellNLOS.ZSAvsK << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.DSvsSF << spatialChannel.UrbanMacroCellNLOS.DSvsK << 1 << spatialChannel.UrbanMacroCellNLOS.ASDvsDS << spatialChannel.UrbanMacroCellNLOS.ASAvsDS << spatialChannel.UrbanMacroCellNLOS.ZSDvsDS << spatialChannel.UrbanMacroCellNLOS.ZSAvsDS << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ASDvsSF << spatialChannel.UrbanMacroCellNLOS.ASDvsK << spatialChannel.UrbanMacroCellNLOS.ASDvsDS << 1 << spatialChannel.UrbanMacroCellNLOS.ASDvsASA << spatialChannel.UrbanMacroCellNLOS.ZSDvsASD << spatialChannel.UrbanMacroCellNLOS.ZSAvsASD << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ASAvsSF << spatialChannel.UrbanMacroCellNLOS.ASAvsK << spatialChannel.UrbanMacroCellNLOS.ASAvsDS << spatialChannel.UrbanMacroCellNLOS.ASDvsASA << 1 << spatialChannel.UrbanMacroCellNLOS.ZSDvsASA << spatialChannel.UrbanMacroCellNLOS.ZSDvsASA << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ZSDvsSF << spatialChannel.UrbanMacroCellNLOS.ZSDvsK << spatialChannel.UrbanMacroCellNLOS.ZSDvsDS << spatialChannel.UrbanMacroCellNLOS.ZSDvsASD << spatialChannel.UrbanMacroCellNLOS.ZSDvsASA << 1 << spatialChannel.UrbanMacroCellNLOS.ZSDvsZSA << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ZSAvsSF << spatialChannel.UrbanMacroCellNLOS.ZSAvsK << spatialChannel.UrbanMacroCellNLOS.ZSAvsDS << spatialChannel.UrbanMacroCellNLOS.ZSAvsASD << spatialChannel.UrbanMacroCellNLOS.ZSAvsASA << spatialChannel.UrbanMacroCellNLOS.ZSDvsZSA << 1 << arma::endr;
		}

		else if ((MS[msID]->network->location == Indoor)) {
			correlationMatrix << 1 << spatialChannel.UrbanMacroCellOtoI.SFvsK << spatialChannel.UrbanMacroCellOtoI.DSvsSF << spatialChannel.UrbanMacroCellOtoI.ASDvsSF << spatialChannel.UrbanMacroCellOtoI.ASAvsSF << spatialChannel.UrbanMacroCellOtoI.ZSDvsSF << spatialChannel.UrbanMacroCellOtoI.ZSAvsSF << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.SFvsK << 1 << spatialChannel.UrbanMacroCellOtoI.DSvsK << spatialChannel.UrbanMacroCellOtoI.ASDvsK << spatialChannel.UrbanMacroCellOtoI.ASAvsK << spatialChannel.UrbanMacroCellOtoI.ZSDvsK << spatialChannel.UrbanMacroCellOtoI.ZSAvsK << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.DSvsSF << spatialChannel.UrbanMacroCellOtoI.DSvsK << 1 << spatialChannel.UrbanMacroCellOtoI.ASDvsDS << spatialChannel.UrbanMacroCellOtoI.ASAvsDS << spatialChannel.UrbanMacroCellOtoI.ZSDvsDS << spatialChannel.UrbanMacroCellOtoI.ZSAvsDS << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ASDvsSF << spatialChannel.UrbanMacroCellOtoI.ASDvsK << spatialChannel.UrbanMacroCellOtoI.ASDvsDS << 1 << spatialChannel.UrbanMacroCellOtoI.ASDvsASA << spatialChannel.UrbanMacroCellOtoI.ZSDvsASD << spatialChannel.UrbanMacroCellOtoI.ZSAvsASD << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ASAvsSF << spatialChannel.UrbanMacroCellOtoI.ASAvsK << spatialChannel.UrbanMacroCellOtoI.ASAvsDS << spatialChannel.UrbanMacroCellOtoI.ASDvsASA << 1 << spatialChannel.UrbanMacroCellOtoI.ZSDvsASA << spatialChannel.UrbanMacroCellOtoI.ZSDvsASA << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ZSDvsSF << spatialChannel.UrbanMacroCellOtoI.ZSDvsK << spatialChannel.UrbanMacroCellOtoI.ZSDvsDS << spatialChannel.UrbanMacroCellOtoI.ZSDvsASD << spatialChannel.UrbanMacroCellOtoI.ZSDvsASA << 1 << spatialChannel.UrbanMacroCellOtoI.ZSDvsZSA << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ZSAvsSF << spatialChannel.UrbanMacroCellOtoI.ZSAvsK << spatialChannel.UrbanMacroCellOtoI.ZSAvsDS << spatialChannel.UrbanMacroCellOtoI.ZSAvsASD << spatialChannel.UrbanMacroCellOtoI.ZSAvsASA << spatialChannel.UrbanMacroCellOtoI.ZSDvsZSA << 1 << arma::endr;
		}


		correlationMatrixCholeskyDecomposed = arma::chol(correlationMatrix, "lower");
		LargeScaleParameter = correlationMatrixCholeskyDecomposed*arma::randn(7, 1);

		largeScaleParameter[0] = spatialChannel.UrbanMacroCellLOS.sigmaShadowing*LargeScaleParameter(0);
		largeScaleParameter[1] = spatialChannel.UrbanMacroCellLOS.sigmaRiceanK*LargeScaleParameter(1) + spatialChannel.UrbanMacroCellLOS.muRiceanK;
		largeScaleParameter[2] = pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonDelaySpread*LargeScaleParameter(2) + spatialChannel.UrbanMacroCellLOS.muDelaySpread);
		largeScaleParameter[3] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonASD*LargeScaleParameter(3) + spatialChannel.UrbanMacroCellLOS.muASD), 104.0);
		largeScaleParameter[4] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonASA*LargeScaleParameter(4) + spatialChannel.UrbanMacroCellLOS.muASA), 104.0);
		largeScaleParameter[5] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonZSD*LargeScaleParameter(5) + spatialChannel.UrbanMacroCellLOS.muZSD), 52.0);
		largeScaleParameter[6] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonZSA*LargeScaleParameter(6) + spatialChannel.UrbanMacroCellLOS.muZSA), 52.0);

		break;


	case SLS::UrbanMacroCell:
		if ((MS[msID]->network->location == Outdoor) && (MS[msID]->channel->channelCondition == LOS)) {
			correlationMatrix << 1 << spatialChannel.UrbanMacroCellLOS.SFvsK << spatialChannel.UrbanMacroCellLOS.DSvsSF << spatialChannel.UrbanMacroCellLOS.ASDvsSF << spatialChannel.UrbanMacroCellLOS.ASAvsSF << spatialChannel.UrbanMacroCellLOS.ZSDvsSF << spatialChannel.UrbanMacroCellLOS.ZSAvsSF << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.SFvsK << 1 << spatialChannel.UrbanMacroCellLOS.DSvsK << spatialChannel.UrbanMacroCellLOS.ASDvsK << spatialChannel.UrbanMacroCellLOS.ASAvsK << spatialChannel.UrbanMacroCellLOS.ZSDvsK << spatialChannel.UrbanMacroCellLOS.ZSAvsK << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.DSvsSF << spatialChannel.UrbanMacroCellLOS.DSvsK << 1 << spatialChannel.UrbanMacroCellLOS.ASDvsDS << spatialChannel.UrbanMacroCellLOS.ASAvsDS << spatialChannel.UrbanMacroCellLOS.ZSDvsDS << spatialChannel.UrbanMacroCellLOS.ZSAvsDS << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ASDvsSF << spatialChannel.UrbanMacroCellLOS.ASDvsK << spatialChannel.UrbanMacroCellLOS.ASDvsDS << 1 << spatialChannel.UrbanMacroCellLOS.ASDvsASA << spatialChannel.UrbanMacroCellLOS.ZSDvsASD << spatialChannel.UrbanMacroCellLOS.ZSAvsASD << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ASAvsSF << spatialChannel.UrbanMacroCellLOS.ASAvsK << spatialChannel.UrbanMacroCellLOS.ASAvsDS << spatialChannel.UrbanMacroCellLOS.ASDvsASA << 1 << spatialChannel.UrbanMacroCellLOS.ZSDvsASA << spatialChannel.UrbanMacroCellLOS.ZSDvsASA << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ZSDvsSF << spatialChannel.UrbanMacroCellLOS.ZSDvsK << spatialChannel.UrbanMacroCellLOS.ZSDvsDS << spatialChannel.UrbanMacroCellLOS.ZSDvsASD << spatialChannel.UrbanMacroCellLOS.ZSDvsASA << 1 << spatialChannel.UrbanMacroCellLOS.ZSDvsZSA << arma::endr
				<< spatialChannel.UrbanMacroCellLOS.ZSAvsSF << spatialChannel.UrbanMacroCellLOS.ZSAvsK << spatialChannel.UrbanMacroCellLOS.ZSAvsDS << spatialChannel.UrbanMacroCellLOS.ZSAvsASD << spatialChannel.UrbanMacroCellLOS.ZSAvsASA << spatialChannel.UrbanMacroCellLOS.ZSDvsZSA << 1 << arma::endr;
		}

		else if ((MS[msID]->network->location == Outdoor) && (MS[msID]->channel->channelCondition == NLOS)) {
			correlationMatrix << 1 << spatialChannel.UrbanMacroCellNLOS.SFvsK << spatialChannel.UrbanMacroCellNLOS.DSvsSF << spatialChannel.UrbanMacroCellNLOS.ASDvsSF << spatialChannel.UrbanMacroCellNLOS.ASAvsSF << spatialChannel.UrbanMacroCellNLOS.ZSDvsSF << spatialChannel.UrbanMacroCellNLOS.ZSAvsSF << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.SFvsK << 1 << spatialChannel.UrbanMacroCellNLOS.DSvsK << spatialChannel.UrbanMacroCellNLOS.ASDvsK << spatialChannel.UrbanMacroCellNLOS.ASAvsK << spatialChannel.UrbanMacroCellNLOS.ZSDvsK << spatialChannel.UrbanMacroCellNLOS.ZSAvsK << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.DSvsSF << spatialChannel.UrbanMacroCellNLOS.DSvsK << 1 << spatialChannel.UrbanMacroCellNLOS.ASDvsDS << spatialChannel.UrbanMacroCellNLOS.ASAvsDS << spatialChannel.UrbanMacroCellNLOS.ZSDvsDS << spatialChannel.UrbanMacroCellNLOS.ZSAvsDS << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ASDvsSF << spatialChannel.UrbanMacroCellNLOS.ASDvsK << spatialChannel.UrbanMacroCellNLOS.ASDvsDS << 1 << spatialChannel.UrbanMacroCellNLOS.ASDvsASA << spatialChannel.UrbanMacroCellNLOS.ZSDvsASD << spatialChannel.UrbanMacroCellNLOS.ZSAvsASD << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ASAvsSF << spatialChannel.UrbanMacroCellNLOS.ASAvsK << spatialChannel.UrbanMacroCellNLOS.ASAvsDS << spatialChannel.UrbanMacroCellNLOS.ASDvsASA << 1 << spatialChannel.UrbanMacroCellNLOS.ZSDvsASA << spatialChannel.UrbanMacroCellNLOS.ZSDvsASA << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ZSDvsSF << spatialChannel.UrbanMacroCellNLOS.ZSDvsK << spatialChannel.UrbanMacroCellNLOS.ZSDvsDS << spatialChannel.UrbanMacroCellNLOS.ZSDvsASD << spatialChannel.UrbanMacroCellNLOS.ZSDvsASA << 1 << spatialChannel.UrbanMacroCellNLOS.ZSDvsZSA << arma::endr
				<< spatialChannel.UrbanMacroCellNLOS.ZSAvsSF << spatialChannel.UrbanMacroCellNLOS.ZSAvsK << spatialChannel.UrbanMacroCellNLOS.ZSAvsDS << spatialChannel.UrbanMacroCellNLOS.ZSAvsASD << spatialChannel.UrbanMacroCellNLOS.ZSAvsASA << spatialChannel.UrbanMacroCellNLOS.ZSDvsZSA << 1 << arma::endr;
		}

		else if ((MS[msID]->network->location == Indoor)) {
			correlationMatrix << 1 << spatialChannel.UrbanMacroCellOtoI.SFvsK << spatialChannel.UrbanMacroCellOtoI.DSvsSF << spatialChannel.UrbanMacroCellOtoI.ASDvsSF << spatialChannel.UrbanMacroCellOtoI.ASAvsSF << spatialChannel.UrbanMacroCellOtoI.ZSDvsSF << spatialChannel.UrbanMacroCellOtoI.ZSAvsSF << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.SFvsK << 1 << spatialChannel.UrbanMacroCellOtoI.DSvsK << spatialChannel.UrbanMacroCellOtoI.ASDvsK << spatialChannel.UrbanMacroCellOtoI.ASAvsK << spatialChannel.UrbanMacroCellOtoI.ZSDvsK << spatialChannel.UrbanMacroCellOtoI.ZSAvsK << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.DSvsSF << spatialChannel.UrbanMacroCellOtoI.DSvsK << 1 << spatialChannel.UrbanMacroCellOtoI.ASDvsDS << spatialChannel.UrbanMacroCellOtoI.ASAvsDS << spatialChannel.UrbanMacroCellOtoI.ZSDvsDS << spatialChannel.UrbanMacroCellOtoI.ZSAvsDS << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ASDvsSF << spatialChannel.UrbanMacroCellOtoI.ASDvsK << spatialChannel.UrbanMacroCellOtoI.ASDvsDS << 1 << spatialChannel.UrbanMacroCellOtoI.ASDvsASA << spatialChannel.UrbanMacroCellOtoI.ZSDvsASD << spatialChannel.UrbanMacroCellOtoI.ZSAvsASD << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ASAvsSF << spatialChannel.UrbanMacroCellOtoI.ASAvsK << spatialChannel.UrbanMacroCellOtoI.ASAvsDS << spatialChannel.UrbanMacroCellOtoI.ASDvsASA << 1 << spatialChannel.UrbanMacroCellOtoI.ZSDvsASA << spatialChannel.UrbanMacroCellOtoI.ZSDvsASA << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ZSDvsSF << spatialChannel.UrbanMacroCellOtoI.ZSDvsK << spatialChannel.UrbanMacroCellOtoI.ZSDvsDS << spatialChannel.UrbanMacroCellOtoI.ZSDvsASD << spatialChannel.UrbanMacroCellOtoI.ZSDvsASA << 1 << spatialChannel.UrbanMacroCellOtoI.ZSDvsZSA << arma::endr
				<< spatialChannel.UrbanMacroCellOtoI.ZSAvsSF << spatialChannel.UrbanMacroCellOtoI.ZSAvsK << spatialChannel.UrbanMacroCellOtoI.ZSAvsDS << spatialChannel.UrbanMacroCellOtoI.ZSAvsASD << spatialChannel.UrbanMacroCellOtoI.ZSAvsASA << spatialChannel.UrbanMacroCellOtoI.ZSDvsZSA << 1 << arma::endr;
		}


		correlationMatrixCholeskyDecomposed = arma::chol(correlationMatrix, "lower");
		LargeScaleParameter = correlationMatrixCholeskyDecomposed*arma::randn(7, 1);

		largeScaleParameter[0] = spatialChannel.UrbanMacroCellLOS.sigmaShadowing*LargeScaleParameter(0);
		largeScaleParameter[1] = spatialChannel.UrbanMacroCellLOS.sigmaRiceanK*LargeScaleParameter(1) + spatialChannel.UrbanMacroCellLOS.muRiceanK;
		largeScaleParameter[2] = pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonDelaySpread*LargeScaleParameter(2) + spatialChannel.UrbanMacroCellLOS.muDelaySpread);
		largeScaleParameter[3] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonASD*LargeScaleParameter(3) + spatialChannel.UrbanMacroCellLOS.muASD), 104.0);
		largeScaleParameter[4] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonASA*LargeScaleParameter(4) + spatialChannel.UrbanMacroCellLOS.muASA), 104.0);
		largeScaleParameter[5] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonZSD*LargeScaleParameter(5) + spatialChannel.UrbanMacroCellLOS.muZSD), 52.0);
		largeScaleParameter[6] = min(pow(10.0, spatialChannel.UrbanMacroCellLOS.epsilonZSA*LargeScaleParameter(6) + spatialChannel.UrbanMacroCellLOS.muZSA), 52.0);

		break;

	case SLS::IndoorOffice:
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

		break;

	case SLS::RuralMacroCell:
		if ((MS[msID]->network->location == Outdoor) && (MS[msID]->channel->channelCondition == LOS)) {
			correlationMatrix << 1 << spatialChannel.RuralMacroCellLOS.SFvsK << spatialChannel.RuralMacroCellLOS.DSvsSF << spatialChannel.RuralMacroCellLOS.ASDvsSF << spatialChannel.RuralMacroCellLOS.ASAvsSF << spatialChannel.RuralMacroCellLOS.ZSDvsSF << spatialChannel.RuralMacroCellLOS.ZSAvsSF << arma::endr
				<< spatialChannel.RuralMacroCellLOS.SFvsK << 1 << spatialChannel.RuralMacroCellLOS.DSvsK << spatialChannel.RuralMacroCellLOS.ASDvsK << spatialChannel.RuralMacroCellLOS.ASAvsK << spatialChannel.RuralMacroCellLOS.ZSDvsK << spatialChannel.RuralMacroCellLOS.ZSAvsK << arma::endr
				<< spatialChannel.RuralMacroCellLOS.DSvsSF << spatialChannel.RuralMacroCellLOS.DSvsK << 1 << spatialChannel.RuralMacroCellLOS.ASDvsDS << spatialChannel.RuralMacroCellLOS.ASAvsDS << spatialChannel.RuralMacroCellLOS.ZSDvsDS << spatialChannel.RuralMacroCellLOS.ZSAvsDS << arma::endr
				<< spatialChannel.RuralMacroCellLOS.ASDvsSF << spatialChannel.RuralMacroCellLOS.ASDvsK << spatialChannel.RuralMacroCellLOS.ASDvsDS << 1 << spatialChannel.RuralMacroCellLOS.ASDvsASA << spatialChannel.RuralMacroCellLOS.ZSDvsASD << spatialChannel.RuralMacroCellLOS.ZSAvsASD << arma::endr
				<< spatialChannel.RuralMacroCellLOS.ASAvsSF << spatialChannel.RuralMacroCellLOS.ASAvsK << spatialChannel.RuralMacroCellLOS.ASAvsDS << spatialChannel.RuralMacroCellLOS.ASDvsASA << 1 << spatialChannel.RuralMacroCellLOS.ZSDvsASA << spatialChannel.RuralMacroCellLOS.ZSDvsASA << arma::endr
				<< spatialChannel.RuralMacroCellLOS.ZSDvsSF << spatialChannel.RuralMacroCellLOS.ZSDvsK << spatialChannel.RuralMacroCellLOS.ZSDvsDS << spatialChannel.RuralMacroCellLOS.ZSDvsASD << spatialChannel.RuralMacroCellLOS.ZSDvsASA << 1 << spatialChannel.RuralMacroCellLOS.ZSDvsZSA << arma::endr
				<< spatialChannel.RuralMacroCellLOS.ZSAvsSF << spatialChannel.RuralMacroCellLOS.ZSAvsK << spatialChannel.RuralMacroCellLOS.ZSAvsDS << spatialChannel.RuralMacroCellLOS.ZSAvsASD << spatialChannel.RuralMacroCellLOS.ZSAvsASA << spatialChannel.RuralMacroCellLOS.ZSDvsZSA << 1 << arma::endr;
		}

		else if ((MS[msID]->network->location == Outdoor) && (MS[msID]->channel->channelCondition == NLOS)) {
			correlationMatrix << 1 << spatialChannel.RuralMacroCellNLOS.SFvsK << spatialChannel.RuralMacroCellNLOS.DSvsSF << spatialChannel.RuralMacroCellNLOS.ASDvsSF << spatialChannel.RuralMacroCellNLOS.ASAvsSF << spatialChannel.RuralMacroCellNLOS.ZSDvsSF << spatialChannel.RuralMacroCellNLOS.ZSAvsSF << arma::endr
				<< spatialChannel.RuralMacroCellNLOS.SFvsK << 1 << spatialChannel.RuralMacroCellNLOS.DSvsK << spatialChannel.RuralMacroCellNLOS.ASDvsK << spatialChannel.RuralMacroCellNLOS.ASAvsK << spatialChannel.RuralMacroCellNLOS.ZSDvsK << spatialChannel.RuralMacroCellNLOS.ZSAvsK << arma::endr
				<< spatialChannel.RuralMacroCellNLOS.DSvsSF << spatialChannel.RuralMacroCellNLOS.DSvsK << 1 << spatialChannel.RuralMacroCellNLOS.ASDvsDS << spatialChannel.RuralMacroCellNLOS.ASAvsDS << spatialChannel.RuralMacroCellNLOS.ZSDvsDS << spatialChannel.RuralMacroCellNLOS.ZSAvsDS << arma::endr
				<< spatialChannel.RuralMacroCellNLOS.ASDvsSF << spatialChannel.RuralMacroCellNLOS.ASDvsK << spatialChannel.RuralMacroCellNLOS.ASDvsDS << 1 << spatialChannel.RuralMacroCellNLOS.ASDvsASA << spatialChannel.RuralMacroCellNLOS.ZSDvsASD << spatialChannel.RuralMacroCellNLOS.ZSAvsASD << arma::endr
				<< spatialChannel.RuralMacroCellNLOS.ASAvsSF << spatialChannel.RuralMacroCellNLOS.ASAvsK << spatialChannel.RuralMacroCellNLOS.ASAvsDS << spatialChannel.RuralMacroCellNLOS.ASDvsASA << 1 << spatialChannel.RuralMacroCellNLOS.ZSDvsASA << spatialChannel.RuralMacroCellNLOS.ZSDvsASA << arma::endr
				<< spatialChannel.RuralMacroCellNLOS.ZSDvsSF << spatialChannel.RuralMacroCellNLOS.ZSDvsK << spatialChannel.RuralMacroCellNLOS.ZSDvsDS << spatialChannel.RuralMacroCellNLOS.ZSDvsASD << spatialChannel.RuralMacroCellNLOS.ZSDvsASA << 1 << spatialChannel.RuralMacroCellNLOS.ZSDvsZSA << arma::endr
				<< spatialChannel.RuralMacroCellNLOS.ZSAvsSF << spatialChannel.RuralMacroCellNLOS.ZSAvsK << spatialChannel.RuralMacroCellNLOS.ZSAvsDS << spatialChannel.RuralMacroCellNLOS.ZSAvsASD << spatialChannel.RuralMacroCellNLOS.ZSAvsASA << spatialChannel.RuralMacroCellNLOS.ZSDvsZSA << 1 << arma::endr;
		}

		else if ((MS[msID]->network->location == Indoor)) {
			correlationMatrix << 1 << spatialChannel.RuralMacroCellOtoI.SFvsK << spatialChannel.RuralMacroCellOtoI.DSvsSF << spatialChannel.RuralMacroCellOtoI.ASDvsSF << spatialChannel.RuralMacroCellOtoI.ASAvsSF << spatialChannel.RuralMacroCellOtoI.ZSDvsSF << spatialChannel.RuralMacroCellOtoI.ZSAvsSF << arma::endr
				<< spatialChannel.RuralMacroCellOtoI.SFvsK << 1 << spatialChannel.RuralMacroCellOtoI.DSvsK << spatialChannel.RuralMacroCellOtoI.ASDvsK << spatialChannel.RuralMacroCellOtoI.ASAvsK << spatialChannel.RuralMacroCellOtoI.ZSDvsK << spatialChannel.RuralMacroCellOtoI.ZSAvsK << arma::endr
				<< spatialChannel.RuralMacroCellOtoI.DSvsSF << spatialChannel.RuralMacroCellOtoI.DSvsK << 1 << spatialChannel.RuralMacroCellOtoI.ASDvsDS << spatialChannel.RuralMacroCellOtoI.ASAvsDS << spatialChannel.RuralMacroCellOtoI.ZSDvsDS << spatialChannel.RuralMacroCellOtoI.ZSAvsDS << arma::endr
				<< spatialChannel.RuralMacroCellOtoI.ASDvsSF << spatialChannel.RuralMacroCellOtoI.ASDvsK << spatialChannel.RuralMacroCellOtoI.ASDvsDS << 1 << spatialChannel.RuralMacroCellOtoI.ASDvsASA << spatialChannel.RuralMacroCellOtoI.ZSDvsASD << spatialChannel.RuralMacroCellOtoI.ZSAvsASD << arma::endr
				<< spatialChannel.RuralMacroCellOtoI.ASAvsSF << spatialChannel.RuralMacroCellOtoI.ASAvsK << spatialChannel.RuralMacroCellOtoI.ASAvsDS << spatialChannel.RuralMacroCellOtoI.ASDvsASA << 1 << spatialChannel.RuralMacroCellOtoI.ZSDvsASA << spatialChannel.RuralMacroCellOtoI.ZSDvsASA << arma::endr
				<< spatialChannel.RuralMacroCellOtoI.ZSDvsSF << spatialChannel.RuralMacroCellOtoI.ZSDvsK << spatialChannel.RuralMacroCellOtoI.ZSDvsDS << spatialChannel.RuralMacroCellOtoI.ZSDvsASD << spatialChannel.RuralMacroCellOtoI.ZSDvsASA << 1 << spatialChannel.RuralMacroCellOtoI.ZSDvsZSA << arma::endr
				<< spatialChannel.RuralMacroCellOtoI.ZSAvsSF << spatialChannel.RuralMacroCellOtoI.ZSAvsK << spatialChannel.RuralMacroCellOtoI.ZSAvsDS << spatialChannel.RuralMacroCellOtoI.ZSAvsASD << spatialChannel.RuralMacroCellOtoI.ZSAvsASA << spatialChannel.RuralMacroCellOtoI.ZSDvsZSA << 1 << arma::endr;
		}


		correlationMatrixCholeskyDecomposed = arma::chol(correlationMatrix, "lower");
		LargeScaleParameter = correlationMatrixCholeskyDecomposed*arma::randn(7, 1);

		largeScaleParameter[0] = spatialChannel.RuralMacroCellLOS.sigmaShadowing*LargeScaleParameter(0);
		largeScaleParameter[1] = spatialChannel.RuralMacroCellLOS.sigmaRiceanK*LargeScaleParameter(1) + spatialChannel.RuralMacroCellLOS.muRiceanK;
		largeScaleParameter[2] = pow(10.0, spatialChannel.RuralMacroCellLOS.epsilonDelaySpread*LargeScaleParameter(2) + spatialChannel.RuralMacroCellLOS.muDelaySpread);
		largeScaleParameter[3] = min(pow(10.0, spatialChannel.RuralMacroCellLOS.epsilonASD*LargeScaleParameter(3) + spatialChannel.RuralMacroCellLOS.muASD), 104.0);
		largeScaleParameter[4] = min(pow(10.0, spatialChannel.RuralMacroCellLOS.epsilonASA*LargeScaleParameter(4) + spatialChannel.RuralMacroCellLOS.muASA), 104.0);
		largeScaleParameter[5] = min(pow(10.0, spatialChannel.RuralMacroCellLOS.epsilonZSD*LargeScaleParameter(5) + spatialChannel.RuralMacroCellLOS.muZSD), 52.0);
		largeScaleParameter[6] = min(pow(10.0, spatialChannel.RuralMacroCellLOS.epsilonZSA*LargeScaleParameter(6) + spatialChannel.RuralMacroCellLOS.muZSA), 52.0);

		break;
	}


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