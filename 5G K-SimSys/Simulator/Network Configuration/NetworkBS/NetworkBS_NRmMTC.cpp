/****************************************************************************

Network Configuration for Base Station (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkBS_NRmMTC.cpp
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

#include "NetworkBS_NRmMTC.h"


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
	if (Sim.network->NetworkModel == NETWORK::UrbanMacroCell)
	{
		PlaceHexagonal();
	}
}

void NetworkBS::PlaceHexagonal()
{

	double A = sqrt(3) / 2;

	arma::mat x, y, z;
	arma::cx_mat hexagonal = arma::zeros<arma::cx_mat>(1, SLS_MAX_MAINSITE);
	x << 0 << A << 0 << -A << -A << 0 << A << 2 * A << 2 * A << A << 0 << -A << -2 * A << -2 * A << -2 * A << -A << 0 << A << 2 * A;
	y << 0 << 0.5 << 1 << 0.5 << -0.5 << -1 << -0.5 << 0 << 1 << 1.5 << 2 << 1.5 << 1 << 0 << -1 << -1.5 << -2 << -1.5 << -1;

	if (Sim.network->NetworkModel == NETWORK::UrbanMacroCell)
	{
		x = Sim.network->UrbanMacroCell.interSiteDistance * x;
		y = Sim.network->UrbanMacroCell.interSiteDistance * y;
		z << Sim.network->UrbanMacroCell.height;
	}
	

	hexagonal.set_real(x);
	hexagonal.set_imag(y);
	this->pos = hexagonal(ceil(id / (Sim.network->numSector * (1 + Sim.network->numMicroBS * Sim.network->numSector))));
	this->pos3D << x(ceil(id / (Sim.network->numSector * (1 + Sim.network->numMicroBS * Sim.network->numSector)))) << y(ceil(id / (Sim.network->numSector * (1 + Sim.network->numMicroBS * Sim.network->numSector)))) << z(0);

}

void NetworkBS::PlaceRectangular()
{

	double A = sqrt(3) / 2;

	arma::mat x, y, z;
	arma::cx_mat rectangular = arma::zeros<arma::cx_mat>(1, 12);
	x << 10 << 30 << 50 << 70 << 90 << 110 << 10 << 30 << 50 << 70 << 90 << 110;
	y << 15 << 15 << 15 << 15 << 15 << 15 << 35 << 35 << 35 << 35 << 35 << 35;

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
	
}

void NetworkBS::ConcludeIteration()
{

}

void NetworkBS::Conclude()
{

}