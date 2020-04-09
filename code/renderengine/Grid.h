
/*


	to do:
		- speficfy: origin and orientation

*/

#ifndef _GRID__h__
#define _GRID__h__


// ogre headers
#include "OgreManualObject.h"

// venator headers
#include "../Prerequisites.h"		// Scalar


namespace Ogre {
	class SceneManager;
	class SceneNode;
}

namespace Venator {
	namespace RenderEngine {
		class Grid;
	}
}


class Venator::RenderEngine::Grid : public Ogre::ManualObject {
	public:
		Grid(const std::string& name, Ogre::SceneManager* scenemgr, Scalar divisions, Scalar unit);
		~Grid(void);

		void create(void);
		void destroy(void);

	private:
		Scalar divisions;
		Scalar unit;
		Ogre::SceneManager* scenemgr;
		Ogre::SceneNode* myManualObjectNode;

};




#endif