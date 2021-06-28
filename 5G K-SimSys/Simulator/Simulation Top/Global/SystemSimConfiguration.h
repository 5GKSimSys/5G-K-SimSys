/****************************************************************************

System Level Simulation Configuration


PROJECT NAME : System Level Simulator
FILE NAME    : SystemSimConfiguration.h
DATE         : 2017.12.1
VERSION      : 0.4
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.5   Minjoong Rim    Created
2017.01.20  Minsig Han      Add Simulation Configuration for FDMIMO SLS
2017.05.13  Jaewon Lee      Add Simulation Configuration for NReMBB SLS
2017.12.1   Jaewon Lee      Add Simulation Configuration for NRLAA SLS
===========================================================================*/

#pragma once

#ifndef CONFIG_H
#define CONFIG_H


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         SIMULATION TYPE DECLARATION                     */
/*                                                                         */
/*-------------------------------------------------------------------------*/

//#define SYSTEM_SIM_CONFIG_LINK // Link level simulation
//#define SYSTEM_SIM_CONFIG_SIMPLE // Simple simulation
//#define SYSTEM_SIM_CONFIG_FDMIMO // FDMIMO simulation
//#define SYSTEM_SIM_CONFIG_NReMBB// NReMBB simulation
//#define SYSTEM_SIM_CONFIG_NRuRLLC// NRuRLLC simulation
#define SYSTEM_SIM_CONFIG_NRmMTC// NRmMTC simulation
//#define SYSTEM_SIM_CONFIG_NRLAA // NRLAA simulation


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#ifdef SYSTEM_SIM_CONFIG_SIMPLE

#include "../../Simulation Top/Global/SLS_simple.h"
#include "../../Simulation Top/Global/Global.h"
#include "../../Channel Model/Antenna/Antenna_simple.h"
#include "../../Channel Model/LargeScale Channel/LargeScaleChannel_simple.h"
#include "../../Channel Model/Channel/Channel_simple.h"
#include "../../Channel Model/ChannelMS/ChannelMS_simple.h"
#include "../../Channel Model/ChannelBS/ChannelBS_simple.h"
#include "../../Network Configuration/Network/Network_simple.h"
#include "../../Network Configuration/NetworkMS/NetworkMS_simple.h"
#include "../../Network Configuration/NetworkBS/NetworkBS_simple.h"
#include "../../Radio Resource Management/Scheduling/Scheduling_simple.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingMS_simple.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingBS_simple.h"

#ifdef SYSTEM_SIM_CONFIG_LINK
#ifdef SYSTEM_SIM_CONFIG_SIMPLE
#include "../../Link Performance/Performance/Performance_simpleLink.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_simpleLink.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_simpleLink.h"
#else
#include "../../Link Performance/Performance/Performance_link.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_link.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_link.h"
#endif
#else
#ifdef SYSTEM_SIM_CONFIG_SIMPLE
#include "../../Link Performance/Performance/Performance_simple.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_simple.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_simple.h"
#else
#include "../../Link Performance/Performance/Performance.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS.h"
#endif
#endif
#include "../../Simulation Top/Network Element/SystemMS_simple.h"
#include "../../Simulation Top/Network Element/SystemBS_simple.h"
#include "../../Simulation Top/Global/SystemSim_simple.h"


#endif

#ifdef SYSTEM_SIM_CONFIG_FDMIMO
#include "../../Simulation Top/Global/SLS_FDMIMO.h"
#include "../../Simulation Top/Global/Global.h"
#include "../../Simulation Top/Global/SystemSim_FDMIMO.h"
#include "../../Simulation Top/Network Element/SystemBS_FDMIMO.h"
#include "../../Simulation Top/Network Element/SystemMS_FDMIMO.h"
#include "../../Network Configuration/Network/Network_FDMIMO.h"
#include "../../Network Configuration/NetworkBS/NetworkBS_FDMIMO.h"
#include "../../Network Configuration/NetworkMS/NetworkMS_FDMIMO.h"
#include "../../Channel Model/Channel/Channel_FDMIMO.h"
#include "../../Channel Model/ChannelBS/ChannelBS_FDMIMO.h"
#include "../../Channel Model/ChannelMS/ChannelMS_FDMIMO.h"
#include "../../Link Performance/Performance/Performance_FDMIMO.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_FDMIMO.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_FDMIMO.h"
#include "../../Radio Resource Management/Scheduling/Scheduling_FDMIMO.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingBS_FDMIMO.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingMS_FDMIMO.h"

#endif

#ifdef SYSTEM_SIM_CONFIG_NReMBB
#include "../../Simulation Top/Global/SLS_NReMBB.h"
#include "../../Simulation Top/Global/Global.h"
#include "../../Simulation Top/Global/SystemSim_NReMBB.h"
#include "../../Simulation Top/Network Element/SystemBS_NReMBB.h"
#include "../../Simulation Top/Network Element/SystemMS_NReMBB.h"
#include "../../Network Configuration/Network/Network_NReMBB.h"
#include "../../Network Configuration/NetworkBS/NetworkBS_NReMBB.h"
#include "../../Network Configuration/NetworkMS/NetworkMS_NReMBB.h"
#include "../../Channel Model/Channel/Channel_NReMBB.h"
#include "../../Channel Model/ChannelBS/ChannelBS_NReMBB.h"
#include "../../Channel Model/ChannelMS/ChannelMS_NReMBB.h"
#include "../../Channel Model/3D SpatialChannelModel/3DSpatialChannelModel_NReMBB.h"
#include "../../Link Performance/Performance/Performance_NReMBB.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_NReMBB.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_NReMBB.h"
#include "../../Radio Resource Management/Scheduling/Scheduling_NReMBB.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingBS_NReMBB.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingMS_NReMBB.h"

#endif

#ifdef SYSTEM_SIM_CONFIG_NRuRLLC
#include "../../Simulation Top/Global/SLS_NRuRLLC.h"
#include "../../Simulation Top/Global/Global.h"
#include "../../Simulation Top/Global/SystemSim_NRuRLLC.h"
#include "../../Simulation Top/Network Element/SystemBS_NRuRLLC.h"
#include "../../Simulation Top/Network Element/SystemMS_NRuRLLC.h"
#include "../../Simulation Top/Network Element/SystemURLLCMS_NRuRLLC.h"
#include "../../Network Configuration/Network/Network_NRuRLLC.h"
#include "../../Network Configuration/NetworkBS/NetworkBS_NRuRLLC.h"
#include "../../Network Configuration/NetworkMS/NetworkMS_NRuRLLC.h"
#include "../../Network Configuration/NetworkURLLCMS/NetworkURLLCMS_NRuRLLC.h"
#include "../../Channel Model/Channel/Channel_NRuRLLC.h"
#include "../../Channel Model/ChannelBS/ChannelBS_NRuRLLC.h"
#include "../../Channel Model/ChannelMS/ChannelMS_NRuRLLC.h"
#include "../../Channel Model/ChannelURLLCMS/ChannelURLLCMS_NRuRLLC.h"
#include "../../Channel Model/3D SpatialChannelModel/3DSpatialChannelModel_NRuRLLC.h"
#include "../../Link Performance/Performance/Performance_NRuRLLC.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_NRuRLLC.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_NRuRLLC.h"
#include "../../Link Performance/PerformanceURLLCMS/PerformanceURLLCMS_NRuRLLC.h"
#include "../../Radio Resource Management/Scheduling/Scheduling_NRuRLLC.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingBS_NRuRLLC.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingMS_NRuRLLC.h"
#include "../../Radio Resource Management/SchedulingURLLCMS/SchedulingURLLCMS_NRuRLLC.h"

#endif

#ifdef SYSTEM_SIM_CONFIG_NRmMTC
#include "../../Simulation Top/Global/SLS_NRmMTC.h"
#include "../../Simulation Top/Global/Global.h"
#include "../../Simulation Top/Global/SystemSim_NRmMTC.h"
#include "../../Simulation Top/Network Element/SystemBS_NRmMTC.h"
#include "../../Simulation Top/Network Element/SystemMS_NRmMTC.h"
#include "../../Network Configuration/Network/Network_NRmMTC.h"
#include "../../Network Configuration/NetworkBS/NetworkBS_NRmMTC.h"
#include "../../Network Configuration/NetworkMS/NetworkMS_NRmMTC.h"
#include "../../Channel Model/Channel/Channel_NRmMTC.h"
#include "../../Channel Model/ChannelBS/ChannelBS_NRmMTC.h"
#include "../../Channel Model/ChannelMS/ChannelMS_NRmMTC.h"
#include "../../Channel Model/3D SpatialChannelModel/3DSpatialChannelModel_NRmMTC.h"
#include "../../Link Performance/Performance/Performance_NRmMTC.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_NRmMTC.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_NRmMTC.h"
#include "../../Radio Resource Management/Scheduling/Scheduling_NRmMTC.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingBS_NRmMTC.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingMS_NRmMTC.h"

#endif

#ifdef SYSTEM_SIM_CONFIG_NRLAA
#include "../../Simulation Top/Global/SLS_NRLAA.h"
#include "../../Simulation Top/Global/Global.h"
#include "../../Simulation Top/Global/SystemSim_NRLAA.h"
#include "../../Simulation Top/Network Element/SystemBS_NRLAA.h"
#include "../../Simulation Top/Network Element/SystemMS_NRLAA.h"
#include "../../Simulation Top/Network Element/SystemWifiBS_NRLAA.h"
#include "../../Simulation Top/Network Element/SystemWifiMS_NRLAA.h"
#include "../../Network Configuration/Network/Network_NRLAA.h"
#include "../../Network Configuration/NetworkBS/NetworkBS_NRLAA.h"
#include "../../Network Configuration/NetworkMS/NetworkMS_NRLAA.h"
#include "../../Network Configuration/NetworkBS/NetworkWifiBS_NRLAA.h"
#include "../../Network Configuration/NetworkMS/NetworkWifiMS_NRLAA.h"
#include "../../Channel Model/3D SpatialChannelModel/3DSpatialChannelModel_NReMBB.h"
#include "../../Channel Model/Channel/Channel_NRLAA.h"
#include "../../Channel Model/ChannelBS/ChannelBS_NRLAA.h"
#include "../../Channel Model/ChannelMS/ChannelMS_NRLAA.h"
#include "../../Channel Model/ChannelBS/ChannelWifiBS_NRLAA.h"
#include "../../Channel Model/ChannelMS/ChannelWifiMS_NRLAA.h"
#include "../../Link Performance/Performance/Performance_NRLAA.h"
#include "../../Link Performance/PerformanceBS/PerformanceBS_NRLAA.h"
#include "../../Link Performance/PerformanceMS/PerformanceMS_NRLAA.h"
#include "../../Link Performance/PerformanceBS/PerformanceWifiBS_NRLAA.h"
#include "../../Link Performance/PerformanceMS/PerformanceWifiMS_NRLAA.h"
#include "../../Radio Resource Management/Scheduling/Scheduling_NRLAA.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingBS_NRLAA.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingMS_NRLAA.h"
#include "../../Radio Resource Management/SchedulingBS/SchedulingWifiBS_NRLAA.h"
#include "../../Radio Resource Management/SchedulingMS/SchedulingWifiMS_NRLAA.h"

#endif



#endif