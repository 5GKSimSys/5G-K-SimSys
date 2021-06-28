/****************************************************************************

Link Level Simulator Performance (simpleLink)


PROJECT NAME : System Level Simulator
FILE NAME    : Performance_simpleLink.cpp
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

#include "Performance_simpleLink.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Performance::Initialize(string fileName) 
{
    // Read link performance parameters from the file
	Link->InitializeIteration(); // Read link simulation parameters from the file
}


void Performance::Measure()
{
    int ms1, ms2;
    LinkNode *tx; // Transmitter
    LinkNode *rx; // Receiver
    LinkChannel channel;

    switch (Sim.linkDirection)
    {
	case LLS::Downlink:
        for (int i = 0; i < Sim.network->numBS; i++) // Transmission processing
       {
            ms1 = BS[i]->scheduling->scheduledMS; // Receiving MS ID
            rx = MS[ms1]->performance->link; // Receiving MS
            BS[i]->performance->link->Transmit(rx); // Transmit
        }
        for (int i = 0; i < Sim.network->numBS; i++) // Reception processing
       {
            ms1 = BS[i]->scheduling->scheduledMS; // Receiving MS ID
            rx = MS[ms1]->performance->link; // Receiving MS
            rx->Noise(); // Generate noise
            for (int j = 0; j < Sim.network->numBS; j++) // Interference as well as signal
            {
                channel.value = MS[ms1]->channel->value[j];
                rx->Channel(BS[j]->performance->link, &channel); // Channel
            }
            channel.value = MS[ms1]->channel->value[i];
            rx->Receive(BS[i]->performance->link, &channel);// Receive
        }
        break;
	case LLS::Uplink:
        for (int i = 0; i < Sim.network->numBS; i++) // Transmission processing
       {
             ms1 = BS[i]->scheduling->scheduledMS; // Transmitting MS ID
             rx = BS[i]->performance->link; // Receiving BS
             MS[ms1]->performance->link->Transmit(rx); // Transmit
        }
        for (int i = 0; i < Sim.network->numBS; i++) // Reception processing
       {
            ms1 = BS[i]->scheduling->scheduledMS; // Transmitting MS ID
            rx = BS[i]->performance->link; // Receiving BS
            rx->Noise(); // Generate noise
            for (int j = 0; j < Sim.network->numBS; j++) // Interference as well as signal
            {
                ms2 = BS[j]->scheduling->scheduledMS; // Interfering MS ID
                channel.value = MS[ms2]->channel->value[i];
                rx->Channel(MS[ms2]->performance->link, &channel); // Channel
            }
            channel.value = MS[ms1]->channel->value[i];
            rx->Receive(MS[ms1]->performance->link, &channel); // Receive
        }
        break;
    }
}


void Performance::InitializeIteration()
{
    Link->numError.uncodedBit = 0; // Initialize error count
    Link->numError.codedBit = 0;
    Link->numError.frame = 0;
    for (int i = 0; i < Sim.network->numBS; i++) 
    {
        BS[i]->performance->InitializeIteration();
    }
    for (int i = 0; i < Sim.network->numMS; i++)
    {
        MS[i]->performance->InitializeIteration();
    }
}


void Performance::ConcludeIteration()
{
	int totalTX;
	if (Sim.linkDirection == LLS::Downlink)
	{
		totalTX = Sim.numIteration * Sim.network->numMS;
		for (int i = 0; i < Sim.network->numMS; i++)
		{
			Link->numError.uncodedBit += MS[i]->performance->link->numError.uncodedBit;
			Link->numError.codedBit += MS[i]->performance->link->numError.codedBit;
			Link->numError.frame += MS[i]->performance->link->numError.frame;
		}
	}
	else if(Sim.linkDirection == LLS::Uplink)
	{
		totalTX = Sim.numIteration * Sim.network->numBS;
		for (int i = 0; i < Sim.network->numBS; i++)
		{
			Link->numError.uncodedBit += BS[i]->performance->link->numError.uncodedBit;
			Link->numError.codedBit += BS[i]->performance->link->numError.codedBit;
			Link->numError.frame += BS[i]->performance->link->numError.frame;
		}
	}
	//Link->errorRate.uncodedBit = Link->numError.uncodedBit / (double)(totalTX * Link->length.coded);
	//Link->errorRate.codedBit = Link->numError.codedBit / (double)(totalTX * Link->length.source);
	//	Link->errorRate.frame = Link->numError.frame / (double)(totalTX);
}

void Performance::Conclude()
{
}
