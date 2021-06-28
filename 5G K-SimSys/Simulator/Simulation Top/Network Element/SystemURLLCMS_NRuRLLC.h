/****************************************************************************

System uRLLC Mobile Station header (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemURLLCMS_NRuRLLC.h
DATE         : 2018.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2018.10.11  Jaewon Lee      Created

===========================================================================*/

#ifndef SYSTEMURLLCMS_H
#define SYSTEMURLLCMS_H

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
class SystemURLLCMS
{
public:
	class NetworkURLLCMS *network; // Network configuration info at MS
	class SchedulingURLLCMS *scheduling; // Scheduling info at MS
	class PerformanceURLLCMS *performance; // Link performance info at MS
	class ChannelURLLCMS *channel; // Channel

	SystemURLLCMS(int umsID, int bs); // Declare constructor
	~SystemURLLCMS(); // Declare destructor
};

extern SystemURLLCMS* UMS[SLS_MAX_UMS];

#endif