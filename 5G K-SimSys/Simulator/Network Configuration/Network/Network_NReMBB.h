/****************************************************************************

Network header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : Network_NReMBB.h
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

#ifdef NReMBB_UrbanMacroCell
#define NETWORK_NUM_WRAPAROUND	7
#endif
#ifdef NReMBB_DenseUrban
#define NETWORK_NUM_WRAPAROUND	7
#endif
#ifdef NReMBB_IndoorOffice
#define NETWORK_NUM_WRAPAROUND	1
#endif
#ifdef NReMBB_RuralMacroCell
#define NETWORK_NUM_WRAPAROUND	7
#endif


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                           TYPE DEFINITION                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

namespace NETWORK {
	enum Network_Model {
		UrbanMacroCell,
		DenseUrban,
		IndoorOffice,
		RuralMacroCell
	};
}

typedef struct {
	double interSiteDistance; // (Minimum) inter site distance (m)
	double interSiteDistanceToMicro; // (Minimum)inter site distance(m) - only Dense Urban scenario
	double height; // Antenna height (m)
	double minDistanceToBS;
	double indoorMsFraction;
} Network_Parameter;

typedef struct {
	double alpha0;
	double alpha1;
	double alpha2;
}Sector_Degree;

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                          CLASS DECLARATION                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Network Setting
class Network
{
public:
	//Simulator Paramter
	enum NETWORK::Network_Model NetworkModel; // 0: Urban Macro Cell, 1: Dence Urban, 2: Indoor Office, 3: Rural Macro Cell 
	int numWraparound; // # of wrap-around positions considered 
	arma::cx_mat posWraparound; // Positions of wrap-around
	int numLayer; // # of layers (1: Single layer, 2: Two layers)
	int numSite; // # of Sites (macro.numSite + micro.numSite)
	int numMacroBS; // # of Macro BSs 
	int numMicroBS; // # of Macro BSs 
	int numBS; // # of BSs 
	int numSector; // # of sector(BS)s per Site
	int numMsPerSector;
	int numFullBufferMsPerSector;
	int numNonFullBufferMsPerSector;
	int numFullBufferMsPerMicro;
	int numNonFullBufferMsPerMicro;
	int bufferModel;
	double meanArrivalTime;
	double bufferSize;
	double msMobility; // MS mobility (movement in horizontal plane)

					   // BS degree
	Sector_Degree sectorDegree; // Alpha { 30, 150, -90 }
	double beta;
	double gamma;

	Network_Parameter UrbanMicroCell; // UMi scenario parameters
	Network_Parameter UrbanMacroCell; // UMa sceanrio parameters
	Network_Parameter IndoorOffice; // 3D UMa High rise parameters
	Network_Parameter RuralMacroCell; // 3D UMa High rise parameters

	int numMsPerMacro; // # of MSs per macro BS for initial placement
	int numMS; // # of MSs = numMsPerMacro * macro.numBS
	double minDistanceToBS; // Minimum distance to BS (m)
	double txProbability; // Transmission probability for non-full-buffer MS (0 ~ 1)

	void Initialize(string fileName); // Initialization
	void PlaceBS(); // BS placement
	void PlaceFullBufferMS(); // Full buffer MS placement -- random
	void PlaceNonFullBufferMS(); // Full buffer MS placement -- random
	void MsBuffer();
	void PlaceWraparound();
	void Conclude(); // Simulation conclusion


	void ConcludeIteration(); // Iteration conclusion
							  //	void Conclude(); // Simulation conclusion 
};


#endif