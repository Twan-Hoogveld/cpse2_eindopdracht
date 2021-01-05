#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Shapes.hpp"
#include "istream"
#include <memory>

using std::istream;
using std::make_shared;
using std::shared_ptr;

// shared_ptr<MoveableObject> readMoveableObject(){
//     Vector2f position = {1,1};
//     std::string name = "Obj";
//     Color color;
//     if (name == "CIRCLE")
//     {
//         int diameter;
// 		return make_shared<Circle>(position, diameter, color);
//     } 
//     else if (name == "RECTANGLE") 
//     {
//         Vector2f position2 = {5,5};
//         return make_shared<Rectangle>(position, position2, color);
//     }
// }

#endif  // FACTORY_HPP