#ifndef NOTMOVEABLECOLLECTION_HPP
#define NOTMOVEABLECOLLECTION_HPP

#include "Shapes.hpp"
#include "Storage.hpp"
#include <memory>

using std::shared_ptr;
using std::make_shared;

template<unsigned int N>
class CollectionNotMoveables {
	private:
	Storage<shared_ptr<NotMoveableObject>, N> storage;

	public:
	CollectionNotMoveables(const Storage<shared_ptr<NotMoveableObject>, N>& store) : storage(store){}
	CollectionNotMoveables(){}

	void add(shared_ptr<NotMoveableObject> to_add){
		storage.add(to_add);
	}

	shared_ptr<NotMoveableObject> getObject(const Vector2i& mouse_pos){
		for(auto object : storage){
			FloatRect boundary = object->getBound();
			if(boundary.contains(Vector2f(mouse_pos))){
				return object;
			}
		}
		return make_shared<DummyNotMoveableObject>();
	}

	void drawObjects(RenderWindow& window){
		for(auto object : storage){
			object->draw(window);
		}
	}
};

#endif //NOTMOVEABLECOLLECTION_HPP