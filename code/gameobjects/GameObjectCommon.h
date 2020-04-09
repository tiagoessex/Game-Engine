
/**
		vars and defines to be used only by the GameObjectComponentSystem

*/

#ifndef __GameObjectCommon_H__
#define __GameObjectCommon_H__

#define MAXCOMPONENTS 64		// max number of allowed components


#include <boost/dynamic_bitset.hpp>


#include <string>
#include <map>

namespace Venator {
	namespace GameObjectComponentSystem	{


		typedef unsigned long long LLG;		// used primaraly for IDs
		typedef int CPOS;					// this will be used to indicate the first set bit
											// given by BITSET.find_first()

		typedef boost::dynamic_bitset<> BITSET;	
		typedef std::map<std::string, std::string> PARAMETERSMAP;

		// internal notification events for go and components management
		enum GOSEVENTS {ADDGO, DELGO, ADDCOMP, DELCOMP, REMOVEGO, REINSERTEDGO};

		// to be set by data or script file
		enum COMPONENTS {
			POSITION = 1,
			SCALE,
			ORIENTATION,
			RENDER,
			SPEED,
			FORWARD,
			LIFESPAN,
			ENTITY,
			PARTICLES,
			PLAYERCONTROL,
			PLAYERSHOOTLIFETIME,
			ENEMYLIFETIME,
			COLLIDER,
			RIGIDBODY,
			COLLISIONS,
			EXPLOSION,
			SOUND2D,
			SOUND3D,
			SOUNDLISTENER,
			SCENENODEANIMATION,
			MESHANIMATION
		};

	}
	
}

#endif
