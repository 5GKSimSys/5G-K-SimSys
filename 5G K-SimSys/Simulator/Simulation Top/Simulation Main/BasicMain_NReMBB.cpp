/****************************************************************************

Simulation main (NR eMBB)


PROJECT NAME : NReMBB System Level Simulation
FILE NAME    : BasicMain_NReMBB.cpp
DATE         : 2017.12.4
VERSION      : 0.9
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2017, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.06.15	Minsig Han  	Created
2017.10.13	Jaewon Lee  	Add variables for NR scenarios
2017.12.4	Jaewon Lee  	Editted for structure change
===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "BasicMain_NReMBB.h"

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         GLOBAL VARIABLE DECLARATION                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#define SYSTEM_SIM_CONFIG_NReMBB // System level simulation for NR enhanced mobile broadband

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         FUNCTION DECLARATION                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         MAIN                                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

int main()
{

	Sim.Initialize("NReMBB_UrbanMacroCell"); // NReMBB_UrbanMacroCell, NReMBB_DenseUrban, NReMBB_IndoorOffice, NReMBB_RuralMacroCell
	Sim.network->PlaceBS();	// BS placement

	for (int i = 0; i < Sim.numIteration; i++)
	{

		Sim.network->PlaceFullBufferMS();		// Full buffer MS placement 
		//Sim.network->PlaceNonFullBufferMS();	// Non Full buffer MS placement 
		Sim.network->PlaceWraparound();
		Sim.channel->LongTermChannel();

		for (Sim.TTI = 0; Sim.TTI < Sim.numTTI; Sim.TTI++)
		{

			Sim.channel->ShortTermChannel(); // DFT

			if (Sim.TTI % Sim.numTTIperFrame == 0) // Dynamic TDD scheduling
			{
				Sim.scheduling->FrameStructure(SLS::DynamicTDD);
			}
			if (Sim.TTI % Sim.feedbackPeriod == 0)
				Sim.scheduling->Feedback(); // Feeback
			Sim.scheduling->Schedule(); // Scheduling 
			Sim.scheduling->ReceivedSINRCalculation(); // Scheduling 
			Sim.performance->FERCheckup(); // FER Checkup	
			Sim.performance->HARQInformation(); // HARQ Information update
			Sim.performance->Measurement(); // Throughput measurement		

		}
	}

	Sim.Demonstration();
	Sim.Conclude();

	return 0;

}