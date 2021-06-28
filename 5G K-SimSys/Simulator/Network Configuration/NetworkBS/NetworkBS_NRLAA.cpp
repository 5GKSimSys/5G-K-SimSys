/****************************************************************************

Network Configuration for Base Station (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkBS_FD MIMO.cpp
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
2017.1.15	Minsig Han  	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "NetworkBS_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void NetworkBS::Initialize(int bs, int site, int sector, SLS::BsType bsType)
{

	this->networkModel = Sim.network->NetworkModel; // Network model information 
	this->bsType = SLS::BsType(bsType);				// BS type 
	this->id = bs;									// BS ID
	this->site = site;								// Site ID
	this->sector = sector;							// Sector number (0, 1, 2)
	this->pos3D;
	this->numAttachedMS = 0;

	// BS position
	if (Sim.network->NetworkModel == NETWORK::IndoorOffice)
	{
		PlaceRectangular();
	}

}

void NetworkBS::PlaceHexagonal()
{

	double A = sqrt(3) / 2;

	arma::mat x, y, z;
	arma::cx_mat hexagonal = arma::zeros<arma::cx_mat>(1, SLS_MAX_MAINSITE);
	x << 0 << A << 0 << -A << -A << 0 << A << 2 * A << 2 * A << A << 0 << -A << -2 * A << -2 * A << -2 * A << -A << 0 << A << 2 * A;
	y << 0 << 0.5 << 1 << 0.5 << -0.5 << -1 << -0.5 << 0 << 1 << 1.5 << 2 << 1.5 << 1 << 0 << -1 << -1.5 << -2 << -1.5 << -1;

	/*if (Sim.network->NetworkModel == NETWORK::UrbanMacroCell)
	{
		x = Sim.network->UrbanMacroCell.interSiteDistance * x;
		y = Sim.network->UrbanMacroCell.interSiteDistance * y;
		z << Sim.network->UrbanMacroCell.height;
	}
	else if (Sim.network->NetworkModel == NETWORK::DenseUrban)
	{
		x = Sim.network->UrbanMacroCell.interSiteDistance * x;
		y = Sim.network->UrbanMacroCell.interSiteDistance * y;
		z << Sim.network->UrbanMacroCell.height;
	}
	else if (Sim.network->NetworkModel == NETWORK::RuralMacroCell)
	{
		x = Sim.network->RuralMacroCell.interSiteDistance * x;
		y = Sim.network->RuralMacroCell.interSiteDistance * y;
		z << Sim.network->RuralMacroCell.height;
	}*/

	hexagonal.set_real(x);
	hexagonal.set_imag(y);
	this->pos = hexagonal(ceil(id / (Sim.network->numSector * (1 + Sim.network->numMicroBS * Sim.network->numSector))));
	this->pos3D << x(ceil(id / (Sim.network->numSector * (1 + Sim.network->numMicroBS * Sim.network->numSector)))) << y(ceil(id / (Sim.network->numSector * (1 + Sim.network->numMicroBS * Sim.network->numSector)))) << z(0);

}

void NetworkBS::PlaceRectangular()
{
	int interSiteDistance = 50;
	arma::mat x, y, z;
	arma::cx_mat rectangular = arma::zeros<arma::cx_mat>(1, 4);
	x << 0 << interSiteDistance << 0 << interSiteDistance;
	y << 0 << 0 << interSiteDistance << interSiteDistance;

	if (Sim.network->NetworkModel == NETWORK::IndoorOffice) {
		z << Sim.network->IndoorOffice.height;
	}

	rectangular.set_real(x);
	rectangular.set_imag(y);
	this->pos = rectangular(ceil(id / 3));
	this->pos3D << x(ceil(id / 3)) << y(ceil(id / 3)) << z(0);

}

void NetworkBS::PlaceCircular()
{

	// Place in a random pattern
	arma::cx_double p;
	double A = sqrt(3) / 2;
	int macroTomicroCheck = 0; // 1 true, 0 false
	double normalizedMacroToMacro = Sim.network->UrbanMacroCell.interSiteDistance / sqrt(3);

	//while (macroTomicroCheck == 0)
	//{
	p = arma::randu() / 2 + 1i * arma::randu() / sqrt(3);
	if (p.imag() > (1 - p.real()) / sqrt(3))
		p = (p - 1i * 1.0 / sqrt(3)) * exp(1i * 2.0 * PI * 1.0 / 3.0);

	p = exp(1i * 2.0 * 3.1416 * (1 / 2 + floor(arma::randu() * 3) / 3)) * p;
	p = 1.0 / 2.0 + 1i / (2.0 * sqrt(3)) + p;

	p = (normalizedMacroToMacro - Sim.network->UrbanMicroCell.interSiteDistance) / normalizedMacroToMacro * p;	//normalize
	p = (Sim.network->UrbanMicroCell.interSiteDistance / 2) / normalizedMacroToMacro + 1i*((Sim.network->UrbanMicroCell.interSiteDistance / 2) / normalizedMacroToMacro) / sqrt(3) + p;	//center point
	if (abs(p) > (Sim.network->UrbanMacroCell.interSiteDistanceToMicro / 2) / normalizedMacroToMacro)
		macroTomicroCheck = 1;
	//}

	// Rotation
	//p = exp(1i * 2.0 * 3.1416 * (double)(id - 1 % 3) / 3.0) * p;
	p = exp(1i * 2.0 * 3.1416 * (double)((id / 3) % 3) / 3.0) * p;
	int val = id - (id % (Sim.network->numMicroBS * Sim.network->numSector + 1));
	pos = BS[val]->network->pos + p * 2.0 / 3.0 * A * Sim.network->UrbanMacroCell.interSiteDistance;
	this->pos3D << real(pos) << imag(pos) << Sim.network->UrbanMicroCell.height;

}

void NetworkBS::ConcludeIteration()
{

}

void NetworkBS::Conclude()
{

}