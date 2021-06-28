/****************************************************************************

		System Level Simulator header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Global.h
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

#ifndef GLOBAL_H
#define GLOBAL_H
using namespace std;
/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------
String Split function
---------------------------------------------------------------------------*/

string* strSplit(string strOrigin, string strTok);

/*-------------------------------------------------------------------------
Set Color for the Console Window Output
---------------------------------------------------------------------------*/

void setcolor(int color, int bgcolor);


#endif