/****************************************************************************

Network Element Mobile Station header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : MS_simple.h
DATE         : 2017.02.01
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.01.20  Minsig Han      Created

===========================================================================*/

#ifndef SYSTEMMS_H
#define SYSTEMMS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Mobile station
class SystemMS
{
public:
	class NetworkMS *network; // Network configuration info at MS
	class SchedulingMS *scheduling; // Scheduling info at MS
	class PerformanceMS *performance; // Link performance info at MS
	class ChannelMS *channel; // Channel

	SystemMS(int msID, int bs); // Declare constructor
	~SystemMS(); // Declare destructor
};

extern SystemMS* MS[SLS_MAX_MS];

#endif