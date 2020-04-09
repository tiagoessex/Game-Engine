

#include "Log.h"

#include <cassert>

using namespace Venator;

Log *Log::mLog = 0;

Log::Log()
{}

Log::~Log()
{}

void Log::setFile(const char* filename) {
  out.open (filename);
  logInfo("log file created\n\n");
}

void Log::destroy(void) {
  	if (out.is_open()) {
	    logInfo("\n\nlog file is closed");
	    out.close();
	}
	if (getInstance()) delete mLog;
}

void Log::logInfo(const char* info) {
	if (out.is_open())
		out<<info<<std::endl;
}


Log& Log::getSingleton(void) {  
    assert(mLog);
    return *mLog;
}


Log* Log::getInstance( void ) {
	if( !mLog ) {
		mLog = new Log();
    }

    return mLog;
}


