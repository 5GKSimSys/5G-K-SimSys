/****************************************************************************

		Channel model header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Channel_simple.h
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
2016.10.5	Minjoong Rim	Created

===========================================================================*/

#ifndef CHANNEL_H
#define CHANNEL_H

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

// Channel model
enum Channel_Model {
	SimpleChannel,
	UrbanMacro3D,
	UrbanMicro3D,
	UrbanMacro5G,
	UrbanMicro5G
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                           TYPE DEFINITION                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel parameter
typedef struct {
	double carrierFrequency; // Carrier frequency (GHz)
	double bandwidth; // Bandwidth (MHz)
	double txPower; // TX power (dBm)
	double noiseFigure; // Noise figure (dB)
	double antennaGain; // Antenna gain (dBi)
	class Antenna antenna; // Antenna parameters
	enum Channel_Model model; // Channel model
} Channel_Parameter;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel
class Channel
{
  public:
	Channel_Parameter macroBS; // Macro BS parameter
	Channel_Parameter microBS; // Micro BS parameter
	Channel_Parameter macroMS; // MS parameter related to Macro BS
	Channel_Parameter microMS; // MS parameter realated to Micro BS

	void Initialize(string fileName); // Initialization
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};

#endif