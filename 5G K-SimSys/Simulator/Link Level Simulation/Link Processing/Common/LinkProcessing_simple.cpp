/****************************************************************************

Link Level Simulation Processing code (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : LinkProcessing_simple.cpp
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

#include "LinkProcessing_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void LinkProcessing::Transmit(LinkNode* tx)
{
    GenerateSourceData(tx);
    switch (tx->scheme.coding) { // Channel coding
	case LLS::ConvolutionalCoding: Convolutional::Encode(tx); break;
    //case TurboCoding:		Turbo.Encode(tx); break;
    //case LDPCCoding:		LDPC.Encode(tx); break;
    //case Polar:		Polar.Encode(tx); break;
	case LLS::NoCoding:
        for (int i = 0; i < tx->length.source; i++)
        {
            tx->data.coded[i] = tx->data.source[i];
        }
        break;
    }
    switch (tx->scheme.modulation) { // Modulation
	case LLS_BPSK:	Modulation::ModulateBPSK(tx); break;
    case LLS_QPSK:	Modulation::ModulateQPSK(tx); break;
    case LLS_16QAM:	Modulation::Modulate16QAM(tx); break;
    case LLS_64QAM:	Modulation::Modulate64QAM(tx); break;
    case LLS_256QAM:	Modulation::Modulate256QAM(tx); break;
    }
}


void LinkProcessing::Receive(LinkNode *tx, LinkNode* rx, LinkChannel *channel)
{
    ChannelCompensate(rx, tx, channel); // Channel compensation
    switch (tx->scheme.modulation) { // Channel coding
    case LLS_BPSK:	Modulation::DemodulateBPSK(tx, rx); break;
    case LLS_QPSK:	Modulation::DemodulateQPSK(tx, rx); break;
    case LLS_16QAM:	Modulation::Demodulate16QAM(tx, rx); break;
    case LLS_64QAM:	Modulation::Demodulate64QAM(tx, rx); break;
    case LLS_256QAM:	Modulation::Demodulate256QAM(tx, rx); break;
    }
    switch (tx->scheme.coding) { // Channel decoding
	case LLS::ConvolutionalCoding:	Convolutional::Decode(tx, rx); break;
    //case TurboCoding:		Turbo.Decode(tx, rx); break;
    //case LDPCCoding:		LDPC.Decode(tx, rx); break;
    //case Polar:		Polar.Decode(tx, rx); break;
	case LLS::NoCoding:
        for (int i = 0; i < rx->length.source; i++)
        {
            rx->data.decoded[i] = rx->data.hardDecision[i];
        }
        break;
    }
    CountError(rx, tx); // Count errors
}


void LinkProcessing::GenerateSourceData(LinkNode* tx)
{
    for (int i = 0; i < tx->length.source; i++)
    {
        tx->data.source[i] = rand() % 2;
     }
}


void LinkProcessing::ChannelCompensate(LinkNode*tx, LinkNode *rx, LinkChannel *channel)
{
     for (int i = 0; i < tx->length.frame; i++)
    {
        rx->data.compensated[i] += tx->data.rxFrame[i] / channel->value;
     }
}


void LinkProcessing::CountError(LinkNode* tx, LinkNode* rx)
{
    int uncodedBitError = 0;
    int codedBitError = 0;
    int frameError = 0;
    for (int i = 0; i < tx->length.coded; i++) // Uncoded bit error counting
    {
        if (rx->data.hardDecision != tx->data.coded)
        {
            uncodedBitError++;
        }
    }
    for (int i = 0; i < tx->length.source; i++) // Coded bit error counting
    {
        if (rx->data.decoded[i] != tx->data.source[i])
        {
            codedBitError++;
            frameError = 1;
        }
    }
    rx->numError.uncodedBit += uncodedBitError;
    rx->numError.codedBit += codedBitError;
    rx->numError.frame += frameError;
}