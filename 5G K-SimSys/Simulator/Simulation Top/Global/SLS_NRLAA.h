/****************************************************************************

System Level Simulator header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : SLS_NReMBB.h
DATE         : 2017.10.3
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.5	Minjoong Rim	Created
2017.05.20	Minsig Han		Editted for NReMBB SLS
2017.10.3   Jaewon Lee      Editted for dynamic TDD
===========================================================================*/

#pragma once

#ifndef SLSNR_H
#define SLSNR_H // !1

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE						   */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include <math.h>
#include <cstdlib>
#include <string>
#include <complex>
#include <string>
#include <windows.h>
#include "../../../Simulator/Library/Math/armadillo-7.700.0/include/armadillo"

using namespace std;

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         GLOBAL VARIABLE DECLARATION                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#define NRLAA_IndoorOffice

#ifdef NRLAA_IndoorOffice
#define SLS_MAX_MAINSITE 12
#define SLS_MAX_MAINSECTOR_MAINSITE 3
#define SLS_MAX_SUBSITE_MAINSECTOR 0
#define SLS_MAX_MS_PER_MAINSECTOR 10
#define SLS_MAX_BS SLS_MAX_MAINSITE * SLS_MAX_MAINSECTOR_MAINSITE * (SLS_MAX_SUBSITE_MAINSECTOR + 1)
#define SLS_MAX_MS SLS_MAX_MS_PER_MAINSECTOR * SLS_MAX_MAINSITE * SLS_MAX_MAINSECTOR_MAINSITE
#define MAX_CLUSTER 20
#define MAX_RAY 20
#endif

/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         CONSTANT                                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#define SLS_NULL					-1	// Null index
#define PI							3.14159265359
#define SLS_INFINITY				1000000000
#define SLS_MINUS_INFINITY			-1000000000
#define SpeedOfElectomageneticWave	3e8
#define HARQvalue arma::randu() * 50;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

namespace SLS {

	enum BsType {
		MacroBS,
		MicroBS,
		IndoorBS
	}; // Base station type

	enum Scenario {
		UrbanMacroCell,
		DenseUrban,
		IndoorOffice,
		RuralMacroCell
	}; // Simulation scenario of 3GPP TR 38.802

	enum LinkDirection {
		Downlink,
		Uplink,
		Dynamiclink
	}; // Simulation link direction

	enum TDDType {
		StaticTDD,
		DynamicTDD,
		HybridTDD
	}; // Simulation link direction
}

#endif 