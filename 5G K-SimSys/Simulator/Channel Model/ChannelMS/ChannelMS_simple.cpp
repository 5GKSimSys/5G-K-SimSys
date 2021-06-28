/****************************************************************************

Channel Model for Mobile Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : ChannelMS_simple.cpp
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

#include "ChannelMS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void ChannelMS::Initialize(int ms)
{
	int id = ms; // MS ID
	double temp;
	complex<double> vector;
	for (int i = 0; i < Sim.network->numBS; i++) // Long term channel calculation
	{
		longTerm[i] = SLS_MINUS_INFINITY;
		for (int j = 0; j < Sim.network->numWraparound; j++)
		{
			vector = MS[ms]->network->pos - (Sim.network->posWraparound[j] + BS[i]->network->pos);
			double pathLoss = 128.1 + 37.6 * log10(abs(vector) / 1000);
			temp = BS[i]->channel->param.txPower + BS[i]->channel->param.antennaGain - pathLoss + BS[i]->channel->param.noiseFigure;

			if (temp > longTerm[i]) longTerm[i] = temp;
		}
	}
}



void ChannelMS::ShortTerm(int ms)
{
	for (int i = 0; i < Sim.network->numBS; i++) // Short term channel calculation
	{
		shortTerm[i] = 10 * log10(abs(pow(sqrt(1.0 / 2.0) * (arma::randu() + 1 * i * arma::randu()), 2)));
	}
}



void ChannelMS::CalculateSINR(int ms)
{
	int bs = MS[ms]->network->attachedBS;
	double signal = longTerm[bs] + shortTerm[bs];
	double interference = 0;
	for (int i = 0; i < Sim.network->numBS; i++)
	{
		if (i != bs) interference += longTerm[i] + shortTerm[i];
	}
	sinr = signal / interference;
}



void ChannelMS::ConcludeIteration() {

}



void ChannelMS::Conclude() {

}