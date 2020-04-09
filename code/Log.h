
/*

	LOG FILES CREATOR	v1.0

	tiago c. santos			

	190620122035


    Log::getInstance()->setFile("qwe.txt");
    Log::getInstance()->logInfo("joder1");
    Log::getInstance()->logInfo("joder2");
    Log::getInstance()->logInfo("joder3");

    Log::getInstance()->destroy();
*/


#ifndef __Log_h_
#define __Log_h_

// c/c++ headers
#include <fstream>

namespace Venator {
	class Log;
}

class Venator::Log {
	public:
		void setFile(const char*  filename);
		void logInfo(const char* str);
		static Log* getInstance( void );		// for singleton pattern
		static Log& getSingleton(void);

		void destroy(void);							// call this one or the destructor

		Log(Log const&);
		void operator=(Log const&);

	private:
		Log();                      // private ctor						
		~Log();
		std::ofstream out;
		static Log *mLog;			// for singleton pattern
};

#endif
