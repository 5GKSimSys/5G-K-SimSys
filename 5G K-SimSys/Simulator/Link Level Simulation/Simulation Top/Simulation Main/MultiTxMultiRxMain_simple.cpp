/****************************************************************************

Multi Tx Multi Rx Simulation Main code (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : MultiTxMultiRxMain_simple.cpp
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

#include "MultiTxMultiRxMain_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         MAIN                                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

int main()
{

    Link.Initialize(); // Initialize simulation parameters
    Link.InitializeNode(); // Initialize transmitters, receivers, and channels
    for (int snr = Link.snr.min; snr <= Link.snr.max; snr += Link.snr.step)
    {
        Link.InitializeIteration(snr); // Initialize simulation parameters for an iteration
        for (int i = 0; i < Link.numIteration; i++)
        {
			for (int j = 0; j < Link.scenario.numRX; j++)
			{
				RX[j]->Noise(); // Noise generation
			}
            for (int j = 0; j < Link.scenario.numTX; j++) 
            {
                TX[j]->Transmit(RX[j]); // Transmission
				for (int k = 0; k < Link.scenario.numRX; k++)
				{
					RX[k]->Channel(TX[j], CH[j][k]); // Channel
				}
             }
			for (int j = 0; j < Link.scenario.numRX; j++)
			{
				RX[j]->Receive(TX[j], CH[j][j]); // Reception process
			}
        }
        Link.ConcludeIteration(); // Calculate BER and FER
    }
    Link.Conclude(); // Conclude simulation

    return 0;
}

