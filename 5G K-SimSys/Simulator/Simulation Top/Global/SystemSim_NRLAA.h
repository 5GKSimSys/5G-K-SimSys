/****************************************************************************

Simulation header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSim_NRLAA.h
DATE         : 2017.09.12
VERSION      : 0.2
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.05.20  Jaewon Lee      Created
2017.09.12  Minsig Han      Add variables for non-full buffer scenario
===========================================================================*/

#ifndef SYSTEMSIM_H
#define SYSTEMSIM_H

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

// Simulation
class SystemSim
{
public:
	int NewDistnace;
	int NewPClass;

	int numerologyParameter; // μ in TS 38.211
	int numTTI; // # of TTIs for simulation
	int TTI;
	int numSymbolperTTI;
	int numTTIperFrame;
	int feedbackPeriod;
	int numIteration; // # of iterations for different mobile station configurations
	int subcarrierSpacing;
	enum SLS::Scenario scenario; // Simulation scenario
	enum SLS::LinkDirection linkDirection; // Link direction
	class Network *network; // Parameters related to network configuration
	class Scheduling *scheduling; // Parameters related to radio resource management
	class Performance *performance; // Parameters related to link performance
	class Channel *channel; // Parameters related to channel
	
	void Initialize(string fileName); // Initialization
	void Demonstration(); // Demo
	void ConcludeIteration();  // Conclude Iteration the simulation
	void Conclude(); // Concluding the simulation
	
	// Demo variables
	arma::mat RateTTI;
	arma::mat LatencyTTI;
	arma::mat BufferTTI;

	// LAA...
	int TTIValue;		// us 단위 // TTI가 몇 us인지
	int usLoop;			// us 단위 
	int usGlobalTime;	// us 단위 // Global simulation time
};



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL VARIABLES                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

extern SystemSim Sim;


#endif