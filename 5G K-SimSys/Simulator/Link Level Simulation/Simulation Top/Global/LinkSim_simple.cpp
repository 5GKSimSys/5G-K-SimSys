/****************************************************************************

Link Level Simulation Simulation class code (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : LinkSim_simple.cpp
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

#include "LinkSim_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*               Link Simulator Initialize                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void LinkSim::Initialize()
{
    // Initialize link level simulator parameters from the parameter file
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*               Link Simulator Node Initialize                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void LinkSim::InitializeNode()
{
    for (int i = 0; i < scenario.numTX; i++) // Initialize transmitters
    {
        TX[i] = new LinkNode();
    }
    for (int i = 0; i < scenario.numRX; i++) // Initialize receivers
    {
        RX[i] = new LinkNode();
    }
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*               Link Simulator Iteration Initialize                       */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void LinkSim::InitializeIteration(int snrdb)
{
    snr.dB = snrdb; // Initialize SNR variables
    //snr.linear = pow(10.0 snrdb/10.0);
    numError.uncodedBit = 0; // Initialize error count
    numError.codedBit = 0;
    numError.frame = 0;
    for (int i = 0; i < scenario.numRX; i++) // Initialize receivers
    {
        RX[i]->InitializeIteration();
    }
}



void LinkSim::ConcludeIteration()
{
     int totalTX = numIteration * scenario.numTX;
     for (int i = 0; i < scenario.numRX; i++) 
    {
        RX[i]->ConcludeIteration();
        numError.uncodedBit += RX[i]->numError.uncodedBit;
        numError.codedBit += RX[i]->numError.codedBit;
        numError.frame += RX[i]->numError.frame;

		cout << numError.frame;
    }
    //errorRate.uncodedBit = numError.uncodedBit / (double) (totalTX * length.uncodedBit);
    //errorRate.codedBit = numError.codedBit / (double) (totalTX * length.codedBit);
    errorRate.frame = numError.frame / (double) (totalTX);
}



void LinkSim::Conclude()
{
    // Close the files
}



LinkSim Link;