/****************************************************************************

Link Sim header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : LinkSim_simple.h
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

#ifndef LINKSIM_H
#define LINKSIM_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/LinkSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             TYPE DECLARATION                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

typedef struct {
    int min; // Minimum of SNR
    int max; // Maximum of SNR
    int step; // Step size
    int dB; // SNR in dB scale
    double linear; // SNR in linear scale
} LinkSim_SnrParam;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

class LinkSim
{
public:
    LLS_Scenario scenario; // Simulation scenario
    LLS_Synchronization synchronization; // Synchronization algorithm on
    LLS_Scheme scheme; // Transmission and reception schemes
    LLS_Length length; // Data length
    LLS_NumError numError; // # of errors
    LLS_ErrorRate errorRate; // Error rates
    int numIteration;  // # of simulation iterations
	LinkSim_SnrParam snr;  // SNR-related parameters

    void Initialize(); // Initialize simulation parameters
    void InitializeNode(); // Initialize transmitter(s) and receiver(s)
    void InitializeIteration(int snrdb); // Initialize simulation parameters for an iteration
    void ConcludeIteration(); // Calculate BER, FER
    void Conclude(); // Conclude simulation
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL VARIABLES                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

extern LinkSim Link;

#endif