#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "Shapes.hpp"
#include "Storage.hpp"
#include <memory>

using std::shared_ptr;
using std::make_shared;

template<unsigned int N>
class CollectionMoveables {
	private:
	Storage<shared_ptr<MoveableObject>, N> storage;

	public:
	CollectionMoveables(const Storage<shared_ptr<MoveableObject>, N>& store) : storage(store){}
	CollectionMoveables(){}

	void add(shared_ptr<MoveableObject> to_add){
		storage.add(to_add);
	}

	void remove(shared_ptr<MoveableObject> to_remove){
		storage.remove(to_remove);
	}

	void showStack(){
		storage.fillGaps();
	}

	shared_ptr<MoveableObject> getObject(const Vector2i& mouse_pos){
		for(auto object : storage)
		{
			if (object != nullptr)
			{
				FloatRect boundary = object->getBound();
				if(boundary.contains(Vector2f(mouse_pos)))
				{
				return object;
				}
			}
		}
		return make_shared<DummyMoveableObject>(); //if none is clicked..
	}

	void drawObjects(RenderWindow& window){
		for(auto object : storage){
			if(object != nullptr){
				object->draw(window);
			}
		}
	}
};

#endif //COLLECTION_HPP