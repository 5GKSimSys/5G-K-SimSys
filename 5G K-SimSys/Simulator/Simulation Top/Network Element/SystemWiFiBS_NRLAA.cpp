/****************************************************************************

Network Element Base Station (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemBS_NReMBB.cpp
DATE         : 2016.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.20   Minsig Han      Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "SystemWiFiBS_NRLAA.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                                  METHOD                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
Base Station Class Constructor Definition
---------------------------------------------------------------------------*/

SystemWiFiBS::SystemWiFiBS(int bs, int site, int sector, SLS::BsType type)
{
	network = new NetworkWiFiBS();
	channel = new ChannelWiFiBS();
	scheduling = new SchedulingWiFiBS();
	performance = new PerformanceWiFiBS();
	

	network->Initialize(bs, site, sector, type);// Initialize network configuration parameters
	channel->Initialize(bs, site, sector);		// Initialize channel parameters
	scheduling->Initialize(bs);					// Initialize RRM parameters
	performance->Initialize(bs);				// Initialize link performance parameters

	//Sim.network->numBS++;
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*              Base Station Class Destructor Definition                   */
/*                                                                         */
/*-------------------------------------------------------------------------*/

SystemWiFiBS::~SystemWiFiBS() 
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

SystemWiFiBS* WiFiBS[SLS_MAX_BS];

