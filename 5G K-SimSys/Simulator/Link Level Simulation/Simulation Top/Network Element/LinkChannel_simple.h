/****************************************************************************

Link Channel header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : LinkChannel_simple.h
DATE         : 2016.11.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.11.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef LINKCHANNEL_H
#define LINKCHANNEL_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/LinkSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

class LinkChannel
{
public:
    int txId; // Transmitter ID
    int rxId; // Receiver ID
    LLS::ChannelType channelType; // Channel type
	complex<double> value;

   void Generate(); // Channel generation
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL VARIABLES                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

extern LinkChannel* CH[LLS_MAX_TX][LLS_MAX_RX]; // Channel

#endif