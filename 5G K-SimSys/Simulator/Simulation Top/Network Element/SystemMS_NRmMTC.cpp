/****************************************************************************

Network Element Mobile Station (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemMS_NRmMTC.cpp
DATE         : 2017.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.20	Minsig Han  	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "SystemMS_NRmMTC.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*             Mobile Station Class Constructor Definition                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemMS::SystemMS(int msID, int bsID)
{
	network = new NetworkMS();
	channel = new ChannelMS();
	scheduling = new SchedulingMS();
	performance = new PerformanceMS();
	
	network->Initialize(msID, bsID); // Initialize network configuration parameters
	channel->Initialize(msID); // Initializer channel config parameters
	scheduling->Initialize(msID); // Initialize RRM parameters
	performance->Initialize(msID); // Initialize link performance parameter
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*              Mobile Station Class Destructor Definition                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemMS::~SystemMS() 
{
	delete this->network;
	delete this->channel;
	delete this->scheduling;
	delete this->performance;
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL                                      */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemMS* MS[SLS_MAX_MS];