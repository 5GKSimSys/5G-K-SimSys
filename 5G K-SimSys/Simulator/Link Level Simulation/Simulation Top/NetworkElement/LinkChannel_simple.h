#ifndef LINKCHANNEL_H
#define LINKCHANNEL_H

#include "../../../Simulation Top/Global/SystemSimConfiguration.h"



class LinkChannel
{
    int txId; // Transmitter ID
    int rxId; // Receiver ID
    LLS_ChannelType channelType; // Channel type
	complex<double> value;

    Generate(); // Channel generation
};

extern LinkChannel* CH[LLS_MAX_TX][LLS_MAX_RX]; // Channel

#endif