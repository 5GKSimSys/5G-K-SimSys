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

#include "BasicMain_NRLAA.h"

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

	Sim.Initialize("NRLAA_IndoorOffice");
	Sim.network->PlaceBS();	// BS placement
	Sim.network->PlaceWiFiBS();

	for (int i = 0; i < Sim.numIteration; i++)
	{

		Sim.network->PlaceFullBufferMS();		// Full buffer MS placement
		Sim.network->PlaceFullBufferWiFiMS();
		//Sim.network->PlaceNonFullBufferMS();	// Non Full buffer MS placement 
		Sim.network->PlaceWraparound();
		Sim.channel->LongTermChannel();

	//	for (Sim.TTI = 0; Sim.TTI < Sim.numTTI; Sim.TTI++)
	//	{

	//		Sim.channel->ShortTermChannel(); // DFT

	//		if (Sim.TTI % Sim.numTTIperFrame == 0) // Dynamic TDD scheduling
	//		{
	//			Sim.scheduling->FrameStructure(SLS::DynamicTDD);

	//			for (Sim.usLoop = 0; Sim.usLoop < Sim.TTIValue; Sim.usLoop++)
	//			{
	//				Sim.usGlobalTime = Sim.usLoop + Sim.TTI * Sim.TTIValue;
	//				Sim.scheduling->ListenBeforeTalk();	// LBT Procedures

	//				Sim.scheduling->DCFforWiFiBS();	// DCF
	//				Sim.scheduling->DCFforWiFiMS();	// DCF

	//				//Sim.scheduling->StartAction();
	//				//Sim.performance->EndAction();		// End Action
	//			}
	//		}
	//		if (Sim.TTI % Sim.feedbackPeriod == 0)
	//			Sim.scheduling->Feedback(); // Feeback
	//		Sim.scheduling->Schedule(); // Scheduling 
	//		Sim.scheduling->ReceivedSINRCalculation(); // Scheduling 
	//		Sim.performance->Measure(); // Throughput measurement		

	//	}
	}

	//Sim.Demonstration();
	//Sim.Conclude();

	return 0;

}

//int main()
//{
//	for (int k = 0; k < 1; k++) {
//
//		Sim.Initialize("NRLAA_UrbanMacroCell"); // NRLAAUrbanMacroCell, NRLAADenseUrban, NRLAAIndoorOffice, NRLAARuralMacroCell, NewCell
//		Sim.network->PlaceMacroBS();	// Macro BS placement
//		//Sim.network->PlaceMicroBS();	// Micro BS placement
//
//		Sim.network->PlaceMacroWiFiBS();
//
//		for (int i = 0; i < Sim.numIteration; i++)
//		{
//
//			Sim.network->PlaceFullBufferMS();		// Full buffer MS placement 
//			//Sim.network->PlaceNonFullBufferMS();	// Non Full buffer MS placement 
//
//			Sim.network->PlaceFullBufferWiFiMS();		// Full buffer MS placement 
//			
//			//Sim.network->PlaceWraparound();
//			//Sim.channel->LongTermChannel();
//
//			Sim.channel->PathlossforMS();
//			Sim.channel->PathlossforWiFiBS();
//			Sim.channel->PathlossforWiFiMS();
//
//			//Sim.network->AssociationforWiFi();
//
//			for (Sim.TTI = 0; Sim.TTI < Sim.numTTI; Sim.TTI++)
//			{
//
//				//Sim.channel->ShortTermChannel(); // DFT
//
//				if (Sim.TTI % Sim.numTTIperFrame == 0) // Dynamic TDD scheduling
//				{
//					Sim.scheduling->FrameStructure(SLS::StaticTDD);
//				}
//
//				for (Sim.usLoop = 0; Sim.usLoop < Sim.TTIValue; Sim.usLoop++)
//				{
//					Sim.usGlobalTime = Sim.usLoop + Sim.TTI * Sim.TTIValue;
//					Sim.scheduling->ListenBeforeTalk();	// LBT Procedures
//
//					Sim.scheduling->DCFforWiFiBS();	// DCF
//					Sim.scheduling->DCFforWiFiMS();	// DCF
//
//					Sim.scheduling->StartAction();
//					Sim.performance->EndAction();		// End Action
//				}
//
//				//Sim.scheduling->Feedback(); // Feeback
//			}
//		}
//
//		for (int bsID = 0; bsID < Sim.network->numBS; bsID++) {
//			BS[bsID]->scheduling->MAC_time = (BS[bsID]->scheduling->error_tot - BS[bsID]->scheduling->error_sum)*Sim.TTIValue*BS[bsID]->scheduling->LTEU_Transmit_block;
//		}
//
//		for (int bsID = 0; bsID < Sim.network->numBS; bsID++) {
//			WiFiBS[bsID]->scheduling->MAC_time = (WiFiBS[bsID]->scheduling->error_tot - WiFiBS[bsID]->scheduling->error_sum)*WiFiBS[bsID]->scheduling->transtime;
//		}
//
//		Sim.Demonstration();
//	}
//}