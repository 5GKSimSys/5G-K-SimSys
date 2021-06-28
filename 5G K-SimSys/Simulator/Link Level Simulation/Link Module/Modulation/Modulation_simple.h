/****************************************************************************

Modulation header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Modulation_simple.h
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

#ifndef MODULATION_H
#define MODULATION_H

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

class Modulation
{
public:
    static void ModulateBPSK(LinkNode* tx);
	static void ModulateQPSK(LinkNode* tx);
	static void Modulate16QAM(LinkNode* tx);
	static void Modulate64QAM(LinkNode* tx);
	static void Modulate256QAM(LinkNode* tx);

	static void DemodulateBPSK(LinkNode* tx, LinkNode* rx); // Use TX parameters
	static void DemodulateQPSK(LinkNode* tx, LinkNode* rx);
	static void Demodulate16QAM(LinkNode* tx, LinkNode* rx);
	static void Demodulate64QAM(LinkNode* tx, LinkNode* rx);
	static void Demodulate256QAM(LinkNode* tx, LinkNode* rx);
};
#endif