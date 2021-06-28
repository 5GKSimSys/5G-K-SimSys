/****************************************************************************

Network Base Station header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : NetworkBS_NReMBB.h
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
2017.1.20  Minsig Han      Created

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
/*                           TYPE DEFINITION                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                          CLASS DECLARATION                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Network base station setting
class NetworkBS
{
public:
	//
	int networkModel;

	// Network BS parameters
	int bsType; // BS Type
	int id; // BS ID
	int site; // Site ID
	int sector; // Sector number (0, 1, 2)
	int numAttachedMS; // # of attached MS 
	int attachedMS[SLS_MAX_MS]; // Attached MS ID  --> 
	double height; // BS height
	complex<double> pos; // (X,Y) Position
	arma::mat pos3D; // (X,Y,Z) Position
	double direction; // antenna boresight for directional antenna
	
	// Network BS functions
	void Initialize(int bs, int site, int sector, SLS::BsType type); // Initialization
	void PlaceHexagonal();
	void PlaceRectangular();
	void PlaceCircular();
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif