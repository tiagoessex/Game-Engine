

/**
		manages all tags of gos

		each time the world removes a go also removes a go from here

*/


#ifndef __TagsManager_h_
#define __TagsManager_h_

#include <vector>
#include <map>

#include "GameObjectCommon.h"
#include "GOListener.h"

namespace Venator {
	namespace GameObjectComponentSystem {
		class GameObject;
		class TagsManager;
	}
}

class Venator::GameObjectComponentSystem::TagsManager  : public GOListener {
	typedef std::vector<GameObject*> GOSVEC;
	typedef std::map< std::string,GOSVEC > TAGSDB;
	public:
		void initialise(void);
		void destroy(void);
		void reset(void);
		void clear(void);

		void receiveEvent(GOSEVENTS ev, void* info);

		static TagsManager* getInstance( void );
		static TagsManager& getSingleton(void);

		friend class World;
	private:
		TagsManager(void);
		~TagsManager(void);
		TagsManager( const TagsManager& ) { }
		TagsManager & operator = ( const TagsManager& );
		static TagsManager *mTagsManager;

		void setTag(GameObject* go, const std::string& tag);
		void removeTag(GameObject* go, const std::string& tag);
		void removeTag(GameObject* go);				// remove all tags of this go
		bool hasTag(GameObject* go,const std::string& tag);
		const std::string& getTag(GameObject* go);  // get only first
		std::vector<GameObject*>& getGameObjectsWithTag(const std::string& tag);

		TAGSDB tags;
		std::string empty;						// empty string => no tag
		std::vector<GameObject*> emptylist;		// empty collection => no gos

};	// class TagsManager




#endif
