/****************************************************************************

Network Configuration for Mobile Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkMS_simple.cpp
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

#include "NetworkMS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void NetworkMS::Initialize(int ms, int bs)
{
	id = ms; // MS ID
	attachedBS = bs; // Temporary association
	PlaceRandom(); // Place in a random pattern
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void NetworkMS::PlaceRandom()
{
	// Place in a random pattern
	arma::cx_double p = arma::randu() / 2 + 1i * arma::randu() / sqrt(3);

	double A = sqrt(3) / 2;
	if (p.imag() > (1 - p.real()) / sqrt(3))
		p = (p - 1i * 1.0 / sqrt(3)) * exp(1i * 2.0 * 3.1416 * 1.0 / 3.0);

		p = exp(1i * 2.0 * 3.1416 * (1 / 2 + floor(arma::randu() * 3) / 3)) * p;
	p = 1.0 / 2.0 + 1i / (2.0 * sqrt(3)) + p;
	p = exp(1i * 2.0 * 3.1416 * (double)(id - 1 % 3) / 3.0) * p;
	pos = BS[attachedBS]->network->pos + p * 2.0 / 3.0 * A * Sim.network->macro.interSiteDistance;
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void NetworkMS::Associate()
{

	MS[id]->channel->Initialize(id); // Initialize channel parameters
	double largest = SLS_MINUS_INFINITY;
	for (int i = 0; i < Sim.network->numBS; i++)
	{
		if (MS[id]->channel->longTerm[i] > largest)
		{
			attachedBS = i;
			largest = MS[id]->channel->longTerm[i];
		}
	}
}



void NetworkMS::ConcludeIteration() 
{

}



void NetworkMS::Conclude() {

}