#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Collection.hpp"
#include "NotMoveableCollection.hpp"
#include "Factory.hpp"
#include "Action.hpp"
#include <unistd.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "BloxBox");
    CollectionMoveables<10> collection = {}; //Items go here when the are created dynamically.
    shared_ptr<MoveableObject> active_object; //last selected object.
    auto defaultColor = sf::Color::Red; //Red would be the standard color of the selectors.

    //--------------------SHAPE SELECTOR-------------------------------------------------------
    sf::RectangleShape squareBox(sf::Vector2f{20,20});
    squareBox.setPosition(25,0);
    squareBox.setFillColor(defaultColor);
    sf::CircleShape circleBox(10);
    circleBox.setPosition(25,25);
    circleBox.setFillColor(defaultColor);
    //---------------------COLOR SELECTORS-----------------------------------------------------
    sf::RectangleShape redBox(sf::Vector2f(20,20));
    redBox.setFillColor(sf::Color::Red);

    sf::RectangleShape greenBox(sf::Vector2f(20,20));
    greenBox.setFillColor(sf::Color::Green);
    greenBox.setPosition(0,25);

    sf::RectangleShape blueBox(sf::Vector2f(20,20));
    blueBox.setFillColor(sf::Color::Blue);
    blueBox.setPosition(0,50);

    sf::RectangleShape yellowBox(sf::Vector2f(20,20));
    yellowBox.setFillColor(sf::Color::Yellow);
    yellowBox.setPosition(0,75);

    sf::RectangleShape whiteBox(sf::Vector2f(20,20));
    whiteBox.setFillColor(sf::Color::White);
    whiteBox.setPosition(0,100);

    sf::RectangleShape purpleBox(sf::Vector2f(20,20));
    purpleBox.setFillColor(sf::Color::Magenta);
    purpleBox.setPosition(0,125);

    sf::RectangleShape cyanBox(sf::Vector2f(20,20));
    cyanBox.setFillColor(sf::Color::Cyan);
    cyanBox.setPosition(0,150);

    std::vector<sf::RectangleShape> colors = {redBox,greenBox,blueBox,yellowBox,whiteBox,purpleBox,cyanBox};
    //----------------------MOVE TOOL---------------------------------------------
    sf::Image img;
    img.loadFromFile("..//move.png"); //Double for linux
    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite sprite(texture);
    sprite.setPosition(0,175);
    sprite.scale(sf::Vector2f(0.1,0.1));

    //----------------------------DELETE TOOL------------------------------------------------
    sf::Image img2;
    img2.loadFromFile("..//trash.jpg");
    sf::Texture texture2;
    texture2.loadFromImage(img2);
    sf::Sprite sprite2(texture2);
    sprite2.setPosition(25,175);
    sprite2.scale(sf::Vector2f(0.1,0.1));

    // ----------------------------------ACTIONS-----------------------------------------------
	Action actions[] = {Action(Keyboard::Left, [&]() { active_object->move(Vector2f(-2.0, 0.0)); std::cout << "Move Left \n"; }),
                      Action(Keyboard::Right, [&]() { active_object->move(Vector2f(+2.0, 0.0)); std::cout << "Move Right \n";}),
                      Action(Keyboard::Up, [&]() { active_object->move(Vector2f(0.0, -2.0)); std::cout << "Move Up \n"; }),
                      Action(Keyboard::Down, [&]() { active_object->move(Vector2f(0.0, +2.0)); std::cout << "Move Down \n"; })};

    //-----------------------------------------------------------------------------------------
    bool moveChosen = false;
    bool deleteChosen = false;
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                auto mPos = sf::Mouse::getPosition(window);
                active_object->jump(sf::Vector2f(mPos.x,mPos.y));
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto position = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                    {

                        sf::Vector2f minVal = {0,0};
                        sf::Vector2f maxVal = {20,170};

                        if( position.x >= minVal.x && position.x <= maxVal.x && position.y >= minVal.y && position.y <= maxVal.y)
                        {
                            for(auto x: colors)
                            {
                                auto globalBounds = x.getGlobalBounds();
                                if(globalBounds.contains(position.x,position.y))
                                {
                                    squareBox.setFillColor(x.getFillColor());
                                    circleBox.setFillColor(x.getFillColor());
                                }
                            }
                        } 

                        //Is the Circle Clicked?
                        else if(circleBox.getGlobalBounds().contains(position.x,position.y)){
                            collection.add(make_shared<Circle>(sf::Vector2f(50,25),20,circleBox.getFillColor()));
                            
                            //Select the newly created object as active.
                            sf::Mouse::setPosition(sf::Vector2i(60,35),window);
                            active_object = collection.getObject(sf::Mouse::getPosition(window));
                            }

                        //Is the Rectangle clicked?
                        else if(squareBox.getGlobalBounds().contains(position.x,position.y))
                        {
                            collection.add(make_shared<Rectangle>(sf::Vector2f(50,0),sf::Vector2f(50,50),squareBox.getFillColor())); //TO-DO fix coord.

                            //Select the newly created object as active.
                            sf::Mouse::setPosition(sf::Vector2i(60,35),window);
                            active_object = collection.getObject(sf::Mouse::getPosition(window));
                        }

                        //Is the move tool selected?
                        else if(sprite.getGlobalBounds().contains(position.x,position.y))
                        {
                            std::cout << "move tool is selected" << std::endl;
                            deleteChosen == false;
                            moveChosen = true;
                        }

                        //Is the delete tool selected?
                        else if(sprite2.getGlobalBounds().contains(position.x,position.y))
                        {
                            std::cout << "delete tool is selected" << std::endl;
                            moveChosen == false;
                            deleteChosen = true;
                        }

                        else //It's not the circle, it's not the rectangle and not the colors, so it's a random positon. 
                        {
                            active_object = collection.getObject(sf::Mouse::getPosition(window));
                            std::cout << "Active Object = " << active_object << std::endl;
                            if (deleteChosen == true && active_object != nullptr){
                                collection.remove(active_object);
                            }
                        }
                    }
            }

            //Do all the actions.
            for (auto& Action : actions) 
            {
                Action();
            }
        }

        //Clear the window of the old.
        window.clear();

        //Draw the color tiles.
        for(auto x : colors){
            window.draw(x);
        }

        //Draw the selector boxes
        window.draw(squareBox);
        window.draw(circleBox);

        //Draw all the items that were created during this run.
        collection.drawObjects(window);

        //Draw all the sprites 
        window.draw(sprite);
        window.draw(sprite2);

        //Display it all.
        window.display();
    }
    return 0;
}