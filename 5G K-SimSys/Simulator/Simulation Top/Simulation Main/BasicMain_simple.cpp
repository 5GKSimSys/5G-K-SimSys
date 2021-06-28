/****************************************************************************

		Simulation main (simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Sim_simple.cpp
DATE         : 2016.10.11
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.11	Minjoong Rim 	Created

===========================================================================*/


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "BasicMain_simple.h"

#define SYSTEM_SIM_CONFIG_LINK // Link level simulation
#define SYSTEM_SIM_CONFIG_SIMPLE // Simple simulation


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         GLOBAL VARIABLE DECLARATION                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/



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
	Sim.Initialize("simple"); // Simulation initialization
	Sim.network->PlaceMacroBS(); // Macro BS placement
	cout << "Placed Macro BS" << endl;
	//Sim.network->PlaceMicroBS(); // Micro BS placement
	//cout << "Placed Micro BS" << endl;
	for (int i = 0; i < Sim.numIteration; i++)
	{
		Sim.network->PlaceFullBufferMS(); // Full buffer MS placement
		cout << "Placed Full Buffer MS" << endl;
		for (int j = 0; j < Sim.numTTI; j++)
		{
			Sim.network->MoveMS(); // for mobility
			//cout << "MS Moved" << endl;
			Sim.network->PlaceNonFullBufferMS(); // Non-full buffer MS placement
			//cout << "placed Non Full Buffer MS" << endl;
			Sim.scheduling->Feedback(); // MS feedback
			cout << "Feedback Success" << endl;
			//cout << BS[0]->network->id;
			Sim.scheduling->Schedule(); // Scheduling
			cout << "Scheduling Success" << endl;
			Sim.performance->Measure(); // Throughput measurement
			cout << "Measure Success" << endl;
		}
		//Sim.ConcludeIteration(); // Iteration conclusion
	}
	Sim.Conclude(); // Simulation conclusion
	return 0;
}