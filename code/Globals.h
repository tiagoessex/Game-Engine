
/**

	all defines of the game are set here so to facilitate their tracking

*/


#ifndef __Globals_h_
#define __Globals_h_

#define RUNTIMELOG		1			// normal logs
#define ERRORLOG		1			// error logs
									// !!!!!!!this should alwauys be active!!!!!!!
#define CTORDTORLOG		1			// log dtors and ctors
#define _DEBUG_			1			// debug code active


#if RUNTIMELOG || ERRORLOG || CTORDTORLOG
#include "Log.h"
#endif

#define LOGINFO(str)	if (RUNTIMELOG)		Log::getSingleton().logInfo(str) 
#define LOGERROR(str)	if (ERRORLOG)		Log::getSingleton().logInfo(str) 
#define LOGTORS(str)	if (CTORDTORLOG)	Log::getSingleton().logInfo(str) 


// foward declaration
/*namespace Venator
{
	struct t_GameWorld;
}
*/
// SHUT DOWN ALL - THIS IS USED TO FLAG A FATAL ERROR IN SOME PART OF THE PROGRAM OR SOMETHING OF THAT KIND
extern bool shutDown;

#endif