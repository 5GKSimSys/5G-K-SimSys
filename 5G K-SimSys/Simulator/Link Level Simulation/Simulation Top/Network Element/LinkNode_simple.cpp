/****************************************************************************

Link Level Simulation Node part code (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : LinkNode_simple.cpp
DATE         : 2016.11.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.11.5	Minjoong Rim 	Created

===========================================================================*/


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "LinkNode_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void LinkNode::Transmit(LinkNode* rx)
{
#ifdef LINK_SIM_CONFIG_SIMPLE

	LinkProcessing::Transmit(p);
#else

    switch (Link.scenario.direction)
    {
    case Downlink: 	Downlink.Transmit(p); break;
    case Uplink:		Uplink.Transmit(p); break;
    case RandomAccess:	RandomAccess.Transmit(p); break;
    }

#endif
}


void LinkNode::Channel(LinkNode* tx, LinkChannel *channel)
{
    for (int i = 0; i < tx->length.frame; i++)
   {
        data.rxFrame[i] += channel->value * tx->data.rxFrame[i];
    }
}

void LinkNode::InitializeIteration()
{
}

void LinkNode::ConcludeIteration()
{
}


void LinkNode::Receive(LinkNode* tx, LinkChannel* channel)
{
#ifdef LINK_SIM_CONFIG_SIMPLE
	 LinkProcessing::Receive(p, tx, channel);
#else

    switch (Link.scenario.direction)
    {
    case Downlink: 	Downlink.Receive(p, tx, channel); break;
    case Uplink:		Uplink.Receive(p, tx, channel); break;
    case RandomAccess:	RandomAccess.Receive(p, tx, channel); break;
    }

#endif


}

void LinkNode::Noise()
{
}


LinkNode* TX[LLS_MAX_TX];
LinkNode* RX[LLS_MAX_RX];