




#ifndef _FilesUtils_h_
#define _FilesUtils_h_

#include <vector>
#include <map>
#include <string>

namespace Venator { 
	namespace Utils {

/**
    file format ex:

            # section 1
            [persistent]
            ../resources/sounds/bip1.wav
            ../resources/sounds/bip2.wav
            ../resources/sounds/bip3.wav

*/
std::vector<std::string> getValuesList(const char* filename, const std::string& sec_name);


/**
    file format ex:

                # section 1
                [persistent]
                sound1=../resources/sounds/bip1.wav
                sound2=../resources/sounds/bip2.wav
                sound3=../resources/sounds/bip3.wav

*/
std::map<std::string, std::string> getValuesMap(const char* filename, const std::string& sec_name);

std::string _getKey(std::string const& original);
std::string _getValue(std::string const& original);

	}
}

#endif