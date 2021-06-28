/****************************************************************************

Performance for Base Station(NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : PerformanceBS_NRmMTC.cpp
DATE         : 2017.3.1
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han     	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "PerformanceBS_NRmMTC.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void PerformanceBS::Initialize(int bs)
{
	id = bs; // BS ID
	throughput = 0;
	packetOutageRate = 0;
	connectionDensity = 0;
}

void PerformanceBS::Measure()
{

	if (BS[id]->channel->NumAssociatedMS !=0)
	{
		MS[BS[id]->scheduling->scheduledMS]->performance->Measure();
	}
	if (failNum != 0)
		packetOutageRate = 1 - failNum / Sim.scheduling->numPreamble;		
	else
		packetOutageRate = 1;
	double temp = 0.01;
	connectionDensity = (1-failNum) / pow(Sim.network->UrbanMacroCell.interSiteDistance, 2.0) * sqrt(3) / 6.0;
	//throughput = throughput + MS[BS[id]->scheduling->scheduledMS]->performance->downlinkThroghput;
	

}

void PerformanceBS::MuMimoMeasure(int bsID)
{
	


}

void PerformanceBS::ConcludeIteration() {

}

void PerformanceBS::Conclude() {

}
