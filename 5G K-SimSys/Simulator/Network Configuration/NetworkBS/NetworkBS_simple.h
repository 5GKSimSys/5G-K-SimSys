/****************************************************************************

		Network Base Station header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkBS_simple.h
DATE         : 2016.10.5
VERSION      : 0.0
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

#ifndef NETWORKBS_H
#define NETWORKBS_H

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

// Network base station setting
class NetworkBS
{
  public:
	int id; // BS ID
	int site; // Site ID
	int sector; // Sector number (0, 1, 2)
	enum SLS_BsType type; // BS Type
	int numAttachedMS; // # of attached MS 
	int attachedMS[SLS_MAX_MS_PER_BS]; // Attached MS ID
	double height; // Antenna height
	complex<double> pos; // (X,Y) Position
	double direction; // antenna boresight for directional antenna

	void Initialize(int bs, int site, int sector, SLS::BsType type); // Initialization
	void PlaceHexagonal();
	void PlaceRandom();
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif