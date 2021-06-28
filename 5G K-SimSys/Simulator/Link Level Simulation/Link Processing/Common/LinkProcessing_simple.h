/****************************************************************************

Link Processing header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : LinkProcessing_simple.h
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

#ifndef LINKPROCESSING_H
#define LINKPROCESSING_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/LinkSimConfiguration.h"

class LinkNode;
class LinkChannel;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

class LinkProcessing
{
public:
    static void Transmit(LinkNode *tx);
    static void Receive(LinkNode *tx, LinkNode *rx, LinkChannel *channel);
    static void GenerateSourceData(LinkNode *tx);
    static void ChannelCompensate(LinkNode *tx, LinkNode *rx, LinkChannel *channel);
    static void CountError(LinkNode *tx, LinkNode *rx);
};

#endif