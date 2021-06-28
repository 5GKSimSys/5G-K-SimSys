/****************************************************************************

		Antenna header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Antenna_simple.h
DATE         : 2016.10.5
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
2016.10.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef CHANNELANTENNA_H
#define CHANNELANTENNA_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Antenna
class Antenna
{
  public:
	int num; // # of antennas

	void Initialize(); // Initialization
};


#endif