/****************************************************************************

Simulation header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Sim_simple.h
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
	int numTTI; // # of TTIs for simulation
	int numIteration; // # of iterations for different mobile station configurations
	enum SLS::Scenario scenario; // Simulation scenario
	enum SLS::LinkDirection linkDirection; // Link direction
	class Network *network; // Parameters related to network configuration
	class Scheduling *scheduling; // Parameters related to radio resource management
	class Performance *performance; // Parameters related to link performance
	class Channel *channel; // Parameters related to channel

	void Initialize(string fileName); // Initialization
	void ConcludeIteration();  // Conclude Iteration the simulation
	void Conclude(); // Concluding the simulation
};



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             GLOBAL VARIABLES                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

extern SystemSim Sim;


#endif