/****************************************************************************

System uRLLC Mobile Station (NR uRLLC)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemURLLCMS_NRuRLLC.cpp
DATE         : 2018.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2018, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2018.10.11	Jaewon Lee  	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "SystemURLLCMS_NRuRLLC.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*             Mobile Station Class Constructor Definition                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemURLLCMS::SystemURLLCMS(int umsID, int bsID)
{
	network = new NetworkURLLCMS();
	channel = new ChannelURLLCMS();
	scheduling = new SchedulingURLLCMS();
	performance = new PerformanceURLLCMS();
	
	network->Initialize(umsID, bsID); // Initialize network configuration parameters
	channel->Initialize(umsID); // Initializer channel config parameters
	scheduling->Initialize(umsID); // Initialize RRM parameters
	performance->Initialize(umsID); // Initialize link performance parameter
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*              Mobile Station Class Destructor Definition                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemURLLCMS::~SystemURLLCMS()
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

SystemURLLCMS* UMS[SLS_MAX_UMS];