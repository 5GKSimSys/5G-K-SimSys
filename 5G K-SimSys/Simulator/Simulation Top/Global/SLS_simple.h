/****************************************************************************

		System Level Simulator header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : SLS_simple.h
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
2016.10.5	Minjoong Rim	Created

===========================================================================*/

#ifndef SLS_H
#define SLS_H

/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include <cstdlib>
#include <string>
#include <complex>
#include <string>
#include "../../Library/Math/armadillo-7.400.4/include/armadillo"


//using namespace std;


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         CONSTANT                                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#define SLS_MAX_MACRO_SITE      19	// Max # of Macro sites
#define SLS_MAX_MICRO_PER_MACRO 9	// Max # of Micro sites per Macro BS
#define SLS_MAX_MS_PER_MACRO    100	// Max # of MSs per Macro BS
#define SLS_MAX_SECTOR_MACRO    3	// Max # of secctors per Macro site 
#define SLS_MAX_SECTOR_MICRO    3	// Max # of sectors per Micro site
#define SLS_MAX_MS_PER_BS		1	// Max # of Micro sites per BS
#define SLS_MAX_MACRO_BS		(SLS_MAX_MACRO_SITE * SLS_MAX_SECTOR_MACRO) 	// Max # of Macro BSs
#define SLS_MAX_MICRO_SITE		(SLS_MAX_MACRO_BS * SLS_MAX_MICRO_PER_MACRO)    // Max # of Micro sites
#define SLS_MAX_SITE			(SLS_MAX_MACRO_SITE + SLS_MAX_MICRO_SITE) 		// Max # of sites
#define SLS_MAX_MICRO_BS 		(SLS_MAX_MICRO_SITE * SLS_MAX_SECTOR_MACRO)		// Max # of Micro BSs
#define SLS_MAX_BS              (SLS_MAX_MACRO_BS + SLS_MAX_MICRO_BS) 			// Max # of BSs
#define SLS_MAX_MS              (SLS_MAX_MACRO_BS * SLS_MAX_MS_PER_MACRO) 		// Max # of MSs
#define SLS_NULL				-1	// Null index
#define SLS_INFINITY			1000000000
#define SLS_MINUS_INFINITY		-1000000000


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

namespace SLS {

	enum BsType {
		MacroBS,
		MicroBS
	}; // Base station type


	enum Scenario {
		SimpleScenario,
		BasicScenario,
		IndoorHotspot,
		DenseUrban,
		Rural,
		UrbanMacro,
		HighSpeedTrain,
		UrbanGridV2X,
		HighwayV2X,
		UrbanMassiveConnection,
		ExtremeLongRange
	}; // Simulation scenario


	enum LinkDirection {
		Downlink,
		Uplink,
		RandomAccess,
		FDD,
		TDD,
		FDD_TDD,
		FDD_Downlink
	}; // Simulation link direction

}

#endif