#include "LinkNode_simple.h"

void LinkNode::Transmit(LinkNode* rx)
{
#ifdef LINK_SIM_CONFIGURATION_SIMPLE

    LinkProcessing.Transmit(p);

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


void LinkNode::Receive(LinkNode* tx, LinkChannel* channel)
{
#ifdef LINK_SIM_CONFIGURATION_SIMPLE

    LinkProcessing.Receive(p, tx, channel);

#else

    switch (Link.scenario.direction)
    {
    case Downlink: 	Downlink.Receive(p, tx, channel); break;
    case Uplink:		Uplink.Receive(p, tx, channel); break;
    case RandomAccess:	RandomAccess.Receive(p, tx, channel); break;
    }

#endif
}

