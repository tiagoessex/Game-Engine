
/**

*/


#ifndef __PlayState_h_
#define __PlayState_h_


// Venator headers
#include "GameState.h"
#include "../gameobjects/GameObject.h"
#include "../events/Listener.h"


//#include "../events/EventsCommon.h"

#include "../Globals.h"
/*
namespace Ogre {
	class Camera;
	class SceneManager;
	class Entity;
	class SceneNode;
	class AnimationState;
	class NodeAnimationTrack;
	class TransformKeyFrame;
	class Animation;
	class StaticGeometry;
	class InstancedGeometry;
}
*/

#include "Ogre.h"

namespace Venator {
	namespace RenderEngine  {
		class Grid;
		class StaticText;
		struct NodeAnimation;
	}
	namespace GameStates {
		class PlayState;
	}	
	namespace SoundSystem {
		class SoundListener;
	}
	namespace Debug	{
		class DebugShits;
	}
}

class Venator::GameStates::PlayState : public GameState, public Venator::Events::Listener {
	/**
		GameState shits
	*/
	public:		
		PlayState(void);
		virtual ~PlayState(void);

		// state shits
		void onENTER();
		void onEXIT();
		void onPAUSE();
		void onRESUME();

		bool updateStart(const Scalar& dt);
		bool update(const Scalar& dt);
		bool updateEnd(const Scalar& dt);

		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);
		virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id); 
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);


		// events
		void receiveEvent(Venator::Events::EVENTS ev, Venator::Events::Event* info);


	private:
		Ogre::Camera* mCamera;
		Ogre::SceneManager* manager;

	/**
		specific shits for this state
	*/

	private:
		Venator::RenderEngine::Grid* grid;
		Ogre::SceneNode* node;
		Ogre::Entity* ent;
		// tests
		bool flag_start_test;
		// tests
		GameObjectComponentSystem::GameObject* g1;
		GameObjectComponentSystem::GameObject* g2;
		Ogre::AnimationState * mLightAnimationState;
		Ogre::NodeAnimationTrack* track;
		Ogre::StaticGeometry *sg;
		std::vector<Ogre::InstancedGeometry::InstancedObject*> instances;

#if _DEBUG_
		Debug::DebugShits* debug;
#endif

};	


#endif



