/****************************************************************************

Network Element Mobile Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : MS_simple.cpp
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

#include "SystemMS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*             Mobile Station Class Constructor Definition                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemMS::SystemMS(int ms, int bs)
{
	network = new NetworkMS();
	scheduling = new SchedulingMS();
	performance = new PerformanceMS();
	channel = new ChannelMS();

	network->Initialize(ms, bs); // Initialize network configuration parameters
	scheduling->Initialize(ms); // Initialize RRM parameters
	performance->Initialize(ms); // Initialize link performance parameter
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*              Mobile Station Class Destructor Definition                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemMS::~SystemMS() {
	delete this->network;
	delete this->scheduling;
	delete this->performance;
	delete this->channel;
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL                                      */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemMS* MS[SLS_MAX_MS];