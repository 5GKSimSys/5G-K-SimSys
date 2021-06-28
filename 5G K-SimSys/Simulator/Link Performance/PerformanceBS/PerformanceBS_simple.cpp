/****************************************************************************

Performance for Base Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : PerformanceBS_simple.cpp
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

#include "PerformanceBS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         METHOD                                           */
/*                                                                          */
/*-------------------------------------------------------------------------*/

void PerformanceBS::Initialize(int bs)
{
	id = bs; // BS ID
}



void PerformanceBS::Measure()
{
	MS[BS[id]->scheduling->scheduledMS]->performance->Measure();
	throughput = MS[BS[id]->scheduling->scheduledMS]->performance->throughput;
}



void PerformanceBS::ConcludeIteration() {

}



void PerformanceBS::Conclude() {

}