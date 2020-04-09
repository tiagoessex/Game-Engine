
/**

	resoruces manager

	tasks:
		- set / load / unload / ....



	dependencies:
		- soundmanager



*/

#ifndef __ResourcesManager_h_
#define __ResourcesManager_h_



namespace Venator {	
	namespace Resources {
		class ResourcesManager;
	}
}

class Venator::Resources::ResourcesManager {

	public:		
		bool initialise(void);
		void destroy(void);
		void reset(void);

		// for the singleton pattern
		static ResourcesManager* getInstance(void);
		static ResourcesManager& getSingleton(void);

	private:
		ResourcesManager(void);
		virtual ~ResourcesManager(void);
		ResourcesManager( const ResourcesManager& ) { }
		ResourcesManager & operator = ( const ResourcesManager& );

		void _loadSounds();

		static ResourcesManager *mResourcesManager;


};		// class


#endif
