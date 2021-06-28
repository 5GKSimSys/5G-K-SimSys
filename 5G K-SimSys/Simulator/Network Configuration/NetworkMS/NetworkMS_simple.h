/****************************************************************************

		Network Mobile Station header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : NetworkMS_simple.h
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

#ifndef NETWORKMS_H
#define NETWORKMS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                          CLASS DECLARATION                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Network mobile station setting
class NetworkMS
{
  public:
	int id; // MS ID
	int attachedBS; // Attached BS ID
	double height; // Antenna height
	complex<double> pos; // (X,Y) Position
	double direction; // antenna boresight for directional antenna

	void Initialize(int ms, int bs); // Initialization
	void Associate(); // Association
	void PlaceRandom(); // Place in a random pattern
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif