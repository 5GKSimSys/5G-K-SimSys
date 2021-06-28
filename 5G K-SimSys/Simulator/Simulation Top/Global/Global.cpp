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



/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include "Global.h"


/*-------------------------------------------------------------------------
String Split function
---------------------------------------------------------------------------*/
string* strSplit(string strOrigin, string strTok)
{
	int cutAt;
	int index = 0;
	string* strResult = new string[1000];

	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		if (cutAt > 0)
		{
			strResult[index++] = strOrigin.substr(0, cutAt);
		}
		strOrigin = strOrigin.substr(cutAt + 1);
	}

	if (strOrigin.length() > 0)
	{
		strResult[index++] = strOrigin.substr(0, cutAt);
	}

	return strResult;
}

void setcolor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}