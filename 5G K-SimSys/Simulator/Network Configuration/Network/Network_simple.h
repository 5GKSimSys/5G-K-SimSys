/****************************************************************************

		Network header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Network_simple.h
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

#ifndef NETWORK_H
#define NETWORK_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         CONSTANT                                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#define NETWORK_NUM_WRAPAROUND	7


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                           TYPE DEFINITION                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Base Station Parameter
typedef struct {
	int numSite; // # of Sites
	int numSector; // # of sector(BS)s per Site
	int numBS; // # of BSs = numSector * numSite
	double interSiteDistance; // (Minimum) inter site distance (m)
	double height; // Antenna height (m)
} Network_BsParameter;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                          CLASS DECLARATION                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Network Setting
class Network
{
  public:
	int numWraparound; // # of wrap-around positions considered 
	arma::cx_mat posWraparound; // Positions of wrap-around
	int numLayer; // # of layers (1: Single layer, 2: Two layers)
	int numSite; // # of Sites (macro.numSite + micro.numSite)
	int numBS; // # of BSs (macro.numBS + micro.numBS)
	int numMicroPerMacro; // # of micro sites per macro BS
	Network_BsParameter macro; // Macro BS parameters
	Network_BsParameter micro; // Micro BS Parameters
	int numMS; // # of MSs = numMsPerMacro * macro.numBS
	int numMsPerMacro; // # of MSs per macro BS for initial placement
	double minDistanceToBS; // Minimum distance to BS (m)
	double txProbability; // Transmission probability for non-full-buffer MS (0 ~ 1)

	void Initialize(string fileName); // Initialization
	void PlaceMacroBS(); // Macro BS placement
	void PlaceMicroBS(); // Micro BS placement
	void PlaceFullBufferMS(); // Full buffer MS placement
	void PlaceNonFullBufferMS(); // Non-full buffer MS placement
	void MoveMS(); // MS movement
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif