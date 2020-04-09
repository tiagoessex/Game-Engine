
/**

	PARAMETERS:
		- [particles]	- script file

	DEPENDENCIES:
		- ComponentRender 

*/


#ifndef __ComponentParticles_H__
#define __ComponentParticles_H__

#include "Component.h"


namespace Ogre {
	class ParticleSystem;
}

namespace Venator {	
	namespace GameObjectComponentSystem {
		class ComponentParticles;
	}
}

class Venator::GameObjectComponentSystem::ComponentParticles : public Component {

	private:
		Ogre::ParticleSystem* particles;
		std::string scriptfile;

	public:
		ComponentParticles(void);
		~ComponentParticles(void);			

		void start();
		void end();

		void setParticles(Ogre::ParticleSystem* p) { particles = p; };
		Ogre::ParticleSystem* getParticles(void) const { return particles; };

		const std::string& getParticlesScriptFile(void) { return scriptfile; }
		void setParticlesScriptFile(const std::string& file) { scriptfile = file; }

		void setVisible(bool b);
		bool isVisible(void);

		static int ID;

		static Factory<Component,ComponentParticles> compFactory;

};



#endif