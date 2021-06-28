/****************************************************************************

Performance for Base Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : PerformanceMS_simple.cpp
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

#include "PerformanceMS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void PerformanceMS::Initialize(int ms)
{
	id = ms; // MS ID
}



void PerformanceMS::Measure()
{
	MS[id]->channel->ShortTerm(id);
	MS[id]->channel->CalculateSINR(id);
	throughput = log2(1 + MS[id]->channel->sinr);
}



void PerformanceMS::ConcludeIteration() {

}



void PerformanceMS::Conclude() {

}