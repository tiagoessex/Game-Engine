

#include "ComponentParticles.h"
#include "../../Globals.h"
#include "../GameObject.h"
#include "ComponentRender.h"
#include "../../utils/VenatorUtils.h"

#include "OgreParticleSystem.h"
#include "OgreSceneManager.h"


using namespace Venator;
using namespace Venator::GameObjectComponentSystem;

Factory<Component,ComponentParticles> ComponentParticles::compFactory;


int ComponentParticles::ID = 0;

ComponentParticles::ComponentParticles(void) :  
							Component("particles"),
							particles(0)
					
{}


ComponentParticles::~ComponentParticles(void) 
{}

void ComponentParticles::start() 
{
	PARAMETERSMAP::iterator it1 = owner->parameters.find("particles");
	if (it1 == owner->parameters.end()) { return; }
	scriptfile = (*it1).second;
	
	ComponentRender* c = static_cast<ComponentRender*>(owner->getComponent(RENDER));
	if (!c) { return; }
	
	if (c->getSceneManager() && c->getSceneNode()) {
		try	{
			particles = c->getSceneManager()->createParticleSystem("ComponentParticles_" + Utils::Number2String(ID),scriptfile);
			c->getSceneNode()->attachObject(particles);
		} catch(Ogre::Exception& e) {
			LOGERROR(("ERROR! -- ComponentParticles::onStart() -- - unable to create particles system " + e.getFullDescription()).c_str());
			particles = 0;
			c = 0;
			return;	
		}
	}
}

void ComponentParticles::end() 
{
	if (!particles) {
		return;
	}

	if (particles->isAttached()) {
		particles->getParentSceneNode()->detachObject(particles);
	}

	particles->_getManager()->destroyParticleSystem(particles);
}



void ComponentParticles::setVisible(bool b) 
{
	if (particles) {
		particles->setVisible(b);
	}
}

bool ComponentParticles::isVisible(void) 
{
	if (particles) {
		return particles->isVisible();
	}
	return false;
}

