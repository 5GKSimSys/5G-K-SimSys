/****************************************************************************

Network Configuration for Base Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkBS_simple.cpp
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
2016.10.11	Minjoong Rim 	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "NetworkBS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void NetworkBS::Initialize(int bs, int site, int sector, SLS::BsType type)
{
	id = bs; // BS ID
	site = site; // Site ID
	sector = sector; // Sector number (0, 1, 2)
	type = type; // BS type 
	switch (type) {
	case SLS::MacroBS: PlaceHexagonal(); break;
	case SLS::MicroBS: PlaceRandom(); break;
	}
}



void NetworkBS::PlaceHexagonal()
{
	double A = sqrt(3) / 2;

	arma::cx_mat hexagonal;
	hexagonal << 0 << A + 0.5i << 1i << -A + 0.5i << -A - 0.5i << -1i << A - 0.5i << 
		2 * A << 2 * A + 1i << A + 1.5 * 1i << 2.0 * 1i << -A + 1.5 * 1i << -2 * A + 1i << 
		-2 * A << -2 * A - 1i << -A - 1.5 * 1i << -2.0 * 1i << A - 1.5 * 1i << 2 * A - 1i;
	hexagonal = Sim.network->macro.interSiteDistance * hexagonal;
	pos = hexagonal(ceil(id / 3));
	// Place in a hexagonal pattern
}


void NetworkBS::PlaceRandom()
{
	// Place in a random pattern
}



void NetworkBS::ConcludeIteration() 
{

}



void NetworkBS::Conclude()
{

}