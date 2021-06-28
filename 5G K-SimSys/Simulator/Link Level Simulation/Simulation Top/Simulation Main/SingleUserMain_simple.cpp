/****************************************************************************

Simulation main (simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Sim_simple.cpp
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

#include "SingleUserMain_simple.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         GLOBAL VARIABLE DECLARATION                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         FUNCTION DECLARATION                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         MAIN                                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

int main()
{
	LinkSim Link;
    Link.Initialize(); // Initialize simulation parameters
    Link.InitializeNode(); // Initialize transmitter, receiver, and channel
    for (int snr = Link.snr.min; snr <= Link.snr.max; snr += Link.snr.step)
    {
        Link.InitializeIteration(snr); // Initialize simulation parameters for an iteration
        for (int i = 0; i < Link.numIteration; i++)
        {
            TX[0]->Transmit(RX[0]); // Transmission
            RX[0]->Noise(); // Noise
            RX[0]->Channel(TX[0], CH[0][0]); // Channel
            RX[0]->Receive(TX[0], CH[0][0]); // Reception
        }
        Link.ConcludeIteration(); // Calculate BER and FER
    }
    Link.Conclude(); // Conclude simulation
    return 0;
}

