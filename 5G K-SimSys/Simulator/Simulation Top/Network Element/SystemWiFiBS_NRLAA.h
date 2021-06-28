/****************************************************************************

Network Element Base Station header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemBS_FDMIOM.h
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

#ifndef SYSTEMWiFiBS_H
#define SYSTEMWiFiBS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                           TYPE DEFINITION                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                             CLASS DECLARATION                            */
/*                                                                          */
/*-------------------------------------------------------------------------*/

// Base station
class SystemWiFiBS
{
public:
	class NetworkWiFiBS *network; // Network configuration info at BS
	class ChannelWiFiBS *channel; // Large scale channel correlation according to Site
	class SchedulingWiFiBS *scheduling; // Scheduling info at BS
	class PerformanceWiFiBS *performance; // Performance info at BS

	SystemWiFiBS(int bs, int site, int sector, SLS::BsType type); // Declare constructor
	~SystemWiFiBS(); // Declare destructor
};

extern SystemWiFiBS* WiFiBS[SLS_MAX_BS];

#endif