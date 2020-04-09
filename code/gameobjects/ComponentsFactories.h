


#ifndef _COMPONENTSFACTORIES_H
#define _COMPONENTSFACTORIES_H

namespace Venator {
	namespace GameObjectComponentSystem {
		template <class BT>	class ComponentsBaseFactory;
		template <class BT,class ST> class Factory;
	}
}

template <class BT>
class Venator::GameObjectComponentSystem::ComponentsBaseFactory  {
   public:
      ComponentsBaseFactory() {}
      virtual ~ComponentsBaseFactory() {}
      virtual BT *createInstance() = 0;
 };

template <class BT,class ST>
class Venator::GameObjectComponentSystem::Factory : public ComponentsBaseFactory<BT> {
   public:
      Factory() {}
      virtual ~Factory() {}
      virtual BT *createInstance() {return new ST;}
};




#endif
