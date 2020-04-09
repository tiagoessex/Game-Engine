
/**

	[init]
	OgreDebugDrawer* debugdrawer = new OgreDebugDrawer(scenemanager);
	debugdrawer->setDebugMode(	btIDebugDraw::DBG_DrawWireframe |
								btIDebugDraw::DBG_DrawContactPoints);
	dynamicsWorld->setDebugDrawer(debugdrawer, 2.0f);

	[in framestarted]
	dynamicsWorld->debugDrawWorld();

	[end]
	delete debugdrawer;

*/

//******************* TO DO: CLEAN UPS

#ifndef __BulletDebugDrawer_h__
#define __BulletDebugDrawer_h__
 

// venator headers
#include "../Prerequisites.h"
#include "BulletPhysicsPrerequisites.h"

// ogre headers
//#include <OgreFrameListener.h>

// bullet headers
#include <btBulletDynamicsCommon.h>


namespace Ogre
{
	class ManualObject;
	class SceneManager;
}

namespace Venator
{
	namespace PhysicsSystem
	{

		class OgreDebugDrawer: public btIDebugDraw		//, public Ogre::FrameListener
		{
			public:
				OgreDebugDrawer( Ogre::SceneManager *scm, btScalar contact_point_distance );
				~OgreDebugDrawer ();
				virtual void drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color);
				virtual void drawTriangle (const btVector3 &v0, const btVector3 &v1, const btVector3 &v2, const btVector3 &color, btScalar);
				virtual void drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);
				virtual void reportErrorWarning (const char *warningString);
				//********** to do
				virtual void draw3dText (const btVector3 &location, const char *textString) {};
				//**********
				virtual void setDebugMode (int debugMode);
				virtual int getDebugMode () const;
				void updateStart(void);
				void updateEnd(void);

			private:
				DebugDrawModes mDebugModes;
				static const char * matName;
				Ogre::SceneManager *scm;
				Ogre::ManualObject* lines;
				Ogre::ManualObject* triangles;
				btScalar contact_point_distance;
				Ogre::SceneNode* myManualObjectNode2;
				Ogre::SceneNode* myManualObjectNode;
		};

	}		// namespace PhysicsSystem
 
}			// namespace venator

#endif