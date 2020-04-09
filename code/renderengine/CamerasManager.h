

/**

	ATT: DO NOT UE THIS DIRECTLY - USE RenderManager TO CREATE/DESTROY CAMERAS

*/

#ifndef __CamerasManager_h_
#define __CamerasManager_h_


#include <map>
#include <string>


#include "OgreCamera.h"


namespace Ogre {
	class Camera;
	class SceneManager;
}

namespace Venator {
	namespace RenderEngine {
		class CamerasManager;
	}
}

class Venator::RenderEngine::CamerasManager {
	typedef std::map<std::string, Ogre::Camera*> CamerasMap;

	public:
		void initialise(void);
		void destroy(void);
		void reset(void);

		std::string _debugPrint(void);				


		static CamerasManager* getInstance(void);
		static CamerasManager& getSingleton(void);

		friend class RenderManager;

	private:
		CamerasManager(void);
		~CamerasManager(void);
		CamerasManager( const CamerasManager& ) { }
		CamerasManager & operator = ( const CamerasManager& );
		static CamerasManager *mCamerasManager;
	
		Ogre::Camera* _createCamera(const std::string& name, 
									Ogre::SceneManager* manager,
									const Ogre::ColourValue& bkcolor,									
									Ogre::Real clipnear,
									Ogre::Real clipfar,
									int zorder);

		void _removeCamera(const std::string& name);
		Ogre::Camera* _getCamera(const std::string& name);
		bool _hasCamera(const std::string& name);

		CamerasMap cameras;
};


#endif