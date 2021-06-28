/****************************************************************************

		Channel Model for Mobile Station header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : ChannelMS_simple.h
DATE         : 2016.10.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef CHANNELMS_H
#define CHANNELMS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel mobile station parameter
class ChannelMS
{
  public:
	double longTerm[SLS_MAX_BS]; // Long term channel
	double shortTerm[SLS_MAX_BS]; // Short term channel
	complex<double> value[SLS_MAX_BS]; // Complex value with long term + short terms
	double sinr; // Signal to Interference plus Noise Ratio

	void Initialize(int ms); // Initialization
	void ShortTerm(int ms); // Short term channel
	void CalculateSINR(int ms); // Calculate SINR
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};

#endif