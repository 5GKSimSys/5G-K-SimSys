/****************************************************************************

Scheduling for Mobile Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : SchedulingMS_simple.cpp
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

#include "SchedulingMS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SchedulingMS::Initialize(int ms)
{
	id = ms; // MS ID
	if (Sim.scheduling->trafficModel == NonFullBuffer)
	{
		int dataSize = Sim.scheduling->dataSize;
	}
}



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void SchedulingMS::Feedback()
{

}



void SchedulingMS::ConcludeIteration()
{

}



void SchedulingMS::Conclude()
{

}