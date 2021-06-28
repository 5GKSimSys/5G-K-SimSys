/****************************************************************************

Network Element Base Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : BS_simple.cpp
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

#include "SystemBS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL                                      */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemBS* BS[SLS_MAX_BS];


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                                  METHOD                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 Base Station Class Constructor Definition 
---------------------------------------------------------------------------*/

SystemBS::SystemBS(int bs, int site, int sector, SLS::BsType type)
{
	network = new NetworkBS();
	scheduling = new SchedulingBS();
	performance = new PerformanceBS();
	channel = new ChannelBS();

	network->Initialize(bs, site, sector, type); // Initialize network configuration parameters
	scheduling->Initialize(bs); // Initialize RRM parameters
	performance->Initialize(bs); // Initialize link performance parameters
	channel->Initialize(bs, site, sector); // Initialize channel parameters

	Sim.network->numBS++;
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*              Base Station Class Destructor Definition                   */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemBS::~SystemBS() {
	delete this->network;
	delete this->scheduling;
	delete this->performance;
	delete this->channel;
}


