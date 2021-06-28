/****************************************************************************

Link Level Simulation Configuration header for settings


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : LinkSimConfiguration.h
DATE         : 2016.11.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.11.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef LINKSIMCONF_H
#define LINKSIMCONF_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         SIMULATION TYPE DECLARATION                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#define LINK_SIM_CONFIG_SIMPLE // Simple simulation


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifdef LINK_SIM_CONFIG_SIMPLE
#include "LLS_simple.h"
#include "../Network Element/LinkChannel_simple.h"
#include "../Network Element/LinkNode_simple.h"

#include "LinkSim_simple.h"
#include "../../Link Module/Modulation/Modulation_simple.h"
#include "../../Link Processing/Common/LinkProcessing_simple.h"

#include "../../Link Module/ChannelCoding/Convolutional_simple.h"


#else
#include 'LLS.h"
#include "LinkSim.h"
#include "../NetworkElement/LinkNode.h"
#include "../NetworkElement/LinkChannel.h"
#include "../../LinkProcessing/Downlink/Downlink.h"
#include "../../LinkProcessing/Uplink/Uplink.h"
#include "../../LinkProcessing/RandomAccess/RandomAccess.h"
#include "../../LinkModule/Modulation/Modulation.h"
#endif

#endif