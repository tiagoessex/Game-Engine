
/**

		hard-coded configuration and data files locations and identifications

*/


#ifndef __GAMEFILES_h_
#define __GAMEFILES_h_


// c/c++ headers
#include <string>


struct ConfigFiles_t
{
	std::string OGRELOG;	// RenderManager.h
	std::string APPLOG;		// main.cpp
	std::string SETTINGS;	// RenderManager.h
	std::string RESOURCES;	// RenderManager.h
	std::string PLUGINS;	// RenderManager.h
	std::string PLUGINS_D;	// RenderManager.h
};

struct DataFiles_t
{
	std::string ENTITIES_TEMPLATES;		// GameObjectsFactory.h
	std::string PARAMETERS_TEMPLATES;	// GameObjectsParameters.h
	std::string GAME_SOUNDS;			// **************
	std::string ANIMATIONS;				// **************
};


struct LevelData_t
{
	int level;
	std::string file;
};

static ConfigFiles_t CONFIGFILES = { 
	"../logs/ogre_log.log",
	"../logs/debuglog.log",
	"../settings/settings.cfg",
	"../settings/resources.cfg",
	"../settings/plugins.cfg",
	"../settings/plugins_d.cfg"	
};


static DataFiles_t DATAFILES = { 
	"../data/gotemplates.xml",
	"../data/goparameters.xml",
	"../data/sounds.xml",
	"../data/animations.xml"
};

static LevelData_t LEVELDATA[] = { 
	{1, "../data/level1.xml"},
	{2, "../data/level2.xml"},
	{3, "../data/level3.xml"}
};


#endif
