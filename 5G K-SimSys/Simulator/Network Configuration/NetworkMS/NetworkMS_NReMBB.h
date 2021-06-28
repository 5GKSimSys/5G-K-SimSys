/****************************************************************************

Network Mobile Station header (NR eMBB)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : NetworkMS_NReMBB.h
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
2017.1.20  Minsig Han      Created

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
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Indoor Outdoor
enum MS_location {
	Outdoor,
	Indoor
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                          CLASS DECLARATION                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Network mobile station setting
class NetworkMS
{
public:
	// Network MS parameter
	int id; // MS ID
	int attachedBS; // Attached BS ID
	int associatedBS;
	double height; // Antenna height
	complex<double> pos; // (X,Y) Position
	arma::mat pos3D; // (X,Y,Z) Position
	arma::vec interArrivalTime;
	enum scenario;
	enum MS_location;
	int location;
	double indoorDistance2D;
	int arrivalTime;
	double msBuffer;
	arma::mat wraparoundposBS; // Wraparound BSs' (X,Y,Z) Position //19*3
	double direction; // antenna boresight for directional antenna
	double velocityVertical;
	double velocityHorizontal;
	int bufferTime;
	
	// Network MS functions
	void Initialize(int msID, int bs); // Initialization
	void WrapAround(); //Wraparound
	void Associate(int msID, arma::vec RSRP); // Association
	void PlaceRandomHexagonal(); // Place in a random pattern in hexagonal grid
	void PlaceRandomRectangular(); // Place in a random pattern in Rectangular
	void PlaceRandomCircular(); // Place in a random pattern in Circular
	arma::mat LargeScaleParameter(int ChannelModel, int ChannelCondition, int msID, int bsID);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif