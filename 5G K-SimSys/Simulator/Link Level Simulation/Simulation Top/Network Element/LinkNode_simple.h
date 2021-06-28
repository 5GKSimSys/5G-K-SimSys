/****************************************************************************

Link Node header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : LinkNode_simple.h
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

#ifndef LINKNODE_H
#define LINKNODE_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/LinkSimConfiguration.h"

class LinkChannel;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

class LinkNode
{
public:
    int id; // ID
    LinkNode* p; // Pointer to self
    LLS_Scheme scheme; // Transmission and reception schemes
    LLS_Length length; // Data length
    LLS_NumError numError; // # of errors
    LLS_ErrorRate errorRate; // Error rates
    LLS_ResourceAllocation resourceAlloc; // Resource allocation
    LLS_FeedbackInfo feedback; // Feedback information
    LLS_Data data; // Link simulation data

	LinkNode() { }; // Create and initialize
	~LinkNode() { }; // Delete
    void Transmit(LinkNode* rx); // Transmission process with its own parameters
    void Receive(LinkNode* tx, LinkChannel* channel); // Reception process with transmitter parameters
    void Noise(); // Generate noise
    void Channel(LinkNode* tx, LinkChannel* channel); // Add TX data to received signal
    void InitializeIteration();
    void ConcludeIteration();
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL VARIABLES                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

extern LinkNode* TX[LLS_MAX_TX];
extern LinkNode* RX[LLS_MAX_RX];

#endif