/****************************************************************************

		Network Element Base Station header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : BS_simple.h
DATE         : 2016.10.5
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef SYSTEMBS_H
#define SYSTEMBS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                             CLASS DECLARATION                            */
/*                                                                          */
/*-------------------------------------------------------------------------*/

// Base station
class SystemBS
{
  public:
	class NetworkBS *network; // Network configuration info at BS
	class SchedulingBS *scheduling; // Scheduling info at BS
	class PerformanceBS *performance; // Performance info at BS
	class ChannelBS *channel; // Large scale channel correlation according to Site

	SystemBS(int bs, int site, int sector, SLS::BsType type); // Declare constructor
	~SystemBS(); // Declare destructor
};


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                             GLOBAL VARIABLES                             */
/*                                                                          */
/*-------------------------------------------------------------------------*/

extern SystemBS* BS[SLS_MAX_BS];


#endif