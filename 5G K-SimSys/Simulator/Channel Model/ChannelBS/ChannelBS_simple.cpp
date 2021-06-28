/****************************************************************************

Channel Model for Base Station (simple)


PROJECT NAME : System Level Simulator
FILE NAME    : ChannelBS_simple.cpp
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

#include "ChannelBS_simple.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void ChannelBS::Initialize(int bs, int site, int sector)
{
	id = bs;
	site = site;
	sector = sector;
	if (sector == 0)
	{
		correlation = new LargeScaleChannel();
	}
	else
	{
		correlation = BS[id - sector]->channel->correlation;
	}
}



void ChannelBS::ConcludeIteration() {

}



void ChannelBS::Conclude() {

}