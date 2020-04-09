

#include "FilesUtils.h"

#include <fstream>

std::vector<std::string> Venator::Utils::getValuesList(const char* filename, const std::string& sec_name)
{
    std::ifstream infile;
    std::string str;
    std::string temp;
    std::vector<std::string> list;

    temp.clear();
    infile.open (filename, std::ifstream::in);


    while (getline(infile, str))
    {
        if (str[0] == '#') continue;
        if (str[0] == '\n') continue;
        if (!str.length()) continue;

        if (str[0] == '[')
        {
            std::string temp_sec = str.substr(1, str.find_last_of( "]" )-1);
            if (temp_sec != sec_name) continue;

             while (getline(infile, str))
            {
                if (str[0] == '#') continue;
                if (str[0] == '\n') continue;
                if (!str.length()) continue;
                if (str[0] == '[') break;
                list.push_back(str);
            }
        }
    }

    infile.close();
    return list;
}




std::string Venator::Utils::_getKey(std::string const& original)
{
    return original.substr(0, original.find( "=" ));
}

std::string Venator::Utils::_getValue(std::string const& original)
{
    return original.substr(original.find( "=" )+1);
}



/**
    file format ex:

                # section 1
                [persistent]
                sound1=../resources/sounds/bip1.wav
                sound2=../resources/sounds/bip2.wav
                sound3=../resources/sounds/bip3.wav

*/
std::map<std::string, std::string> Venator::Utils::getValuesMap(const char* filename, const std::string& sec_name)
{
    std::ifstream infile;
    std::string str;
    std::string temp;
    std::map<std::string, std::string> mapp;

    temp.clear();
    infile.open (filename, std::ifstream::in);


    while (getline(infile, str))
    {
        if (str[0] == '#') continue;
        if (str[0] == '\n') continue;
        if (!str.length()) continue;

        if (str[0] == '[')
        {
            std::string temp_sec = str.substr(1, str.find_last_of( "]" )-1);
            if (temp_sec != sec_name) continue;

             while (getline(infile, str))
             {
                if (str[0] == '#') continue;
                if (str[0] == '\n') continue;
                if (!str.length()) continue;
                if (str[0] == '[') break;
                mapp[_getKey(str)] = _getValue(str);
            }
        }
    }

    infile.close();
    return mapp;
}

