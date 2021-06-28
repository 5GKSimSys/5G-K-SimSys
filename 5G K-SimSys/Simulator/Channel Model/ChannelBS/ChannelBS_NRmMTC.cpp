/****************************************************************************

Channel Model for Base Station (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : ChannelBS_NRmMTC.cpp
DATE         : 2017.02.01
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.02.01	Minsig Han      Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "ChannelBS_NRmMTC.h"


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
	NumAssociatedMS = 0;

}

