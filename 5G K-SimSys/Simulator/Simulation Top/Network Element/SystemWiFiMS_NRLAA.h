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

#ifndef SYSTEMWIFIMS_H
#define SYSTEMWIFIMS_H

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
class SystemWiFiMS
{
public:
	class NetworkWiFiMS *network; // Network configuration info at MS
	class SchedulingWiFiMS *scheduling; // Scheduling info at MS
	class PerformanceWiFiMS *performance; // Link performance info at MS
	class ChannelWiFiMS *channel; // Channel

	SystemWiFiMS(int msID, int bs); // Declare constructor
	~SystemWiFiMS(); // Declare destructor
};

extern SystemWiFiMS* WiFiMS[SLS_MAX_MS];

#endif