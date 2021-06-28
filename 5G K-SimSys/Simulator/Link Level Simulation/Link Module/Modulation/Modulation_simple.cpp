/****************************************************************************

Modulation code (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Modulation_simple.cpp
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

#include "Modulation_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void Modulation::ModulateBPSK(LinkNode *tx)
{
	for (int i = 0; i < tx->length.frame; i++)
	{
        //tx->data.txFrame[i] = (1 - 2 * (double) tx->data.coded[i], 0);
    }
}


void Modulation::ModulateQPSK(LinkNode *tx)
{
    for (int i = 0; i < tx->length.frame; i++)
    {
        //tx->data.txFrame[i] = (sqrt(0.5) * (1 - 2 * tx->data.coded[i*2]), sqrt(0.5) * (1 - 2 * tx->data.coded[i*2+1]));
    }
}


void Modulation::Modulate16QAM(LinkNode * tx)
{
}


void Modulation::Modulate64QAM(LinkNode * tx)
{
}


void Modulation::Modulate256QAM(LinkNode * tx)
{
}


void Modulation::DemodulateBPSK(LinkNode *tx, LinkNode *rx)
{
    for (int i = 0; i < tx->length.frame; i++)
    {
        //rx->data.softDecision[i] = real(rx->data.compensated[i]) < 0;
    }
}


void Modulation::DemodulateQPSK(LinkNode *tx, LinkNode *rx)
{
    for (int i = 0; i < tx->length.frame; i++)
    {
        //rx->data.softDecision[i*2] = real(rx->data.compensated[i]) < 0; 
        //rx->data.softDecision[i*2+1] = imag(rx->data.compensated[i]) < 0;
     }
}


void Modulation::Demodulate16QAM(LinkNode * tx, LinkNode * rx)
{
}


void Modulation::Demodulate64QAM(LinkNode * tx, LinkNode * rx)
{
}


void Modulation::Demodulate256QAM(LinkNode * tx, LinkNode * rx)
{
}

