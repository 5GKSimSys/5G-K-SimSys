/****************************************************************************

Convolutional header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Convolutional_simple.h
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

#ifndef CONVOLUTIONAL_H
#define CONVOLUTIONAL_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/LinkSimConfiguration.h"

class LinkNode;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

class Convolutional
{
public:
    static void Encode(LinkNode* tx);
    static void Decode(LinkNode* tx, LinkNode *rx); // Use TX parameters
};

#endif