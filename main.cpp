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
    sf::Color currentColor = sf::Color::Red; //Red would be the standard color of the selectors.

    //--------------------SHAPE SELECTOR-------------------------------------------------------
    sf::RectangleShape squareBox(sf::Vector2f{20,20});
    squareBox.setPosition(25,0);
    squareBox.setFillColor(currentColor);
    sf::CircleShape circleBox(10);
    circleBox.setPosition(25,25);
    circleBox.setFillColor(currentColor);
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
    //=========================================================================================
    bool moveChosen = false;
    bool deleteChosen = false;
    bool colorChosen = false;
    //==========================================================================================

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            //Move the last selected Object
            std::cout << moveChosen << "===== " << active_object << std::endl;
            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left) && moveChosen == true && active_object != nullptr)
            {
                auto mPos = sf::Mouse::getPosition(window);
                active_object->jump(sf::Vector2f(mPos.x,mPos.y)); 
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //is any of the colors clicked?
                    {
                    for(auto x: colors)
                        {
                            auto globalBounds = x.getGlobalBounds();
                            if(globalBounds.contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                            {
                                currentColor = x.getFillColor();
                                squareBox.setFillColor(currentColor);
                                circleBox.setFillColor(currentColor);
                                colorChosen = true;
                                break;
                            }
                        }
                    } 

                //Is the Circle Clicked? Make a new circle, the user can now, if in move mode, move the object.
                if(circleBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        collection.add(make_shared<Circle>(sf::Vector2f(50,25),20,currentColor));

                    }

                //Is the Rectangle clicked? Make a new rect, the user can now, if in move mode, move the object.
                if (squareBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        collection.add(make_shared<Rectangle>(sf::Vector2f(50,0),sf::Vector2f(50,50),currentColor)); //TO-DO fix coord.
                    }

                //Is the move tool selected? Then the other tools will be not selected.
                if(sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        deleteChosen = false;
                        colorChosen = false;
                        moveChosen = true;
                        std::cout << "move is chosen." << std::endl;
                    }

                //Is the delete tool selected?
                if(sprite2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        deleteChosen = true;

                    }

                if(deleteChosen == true) 
                    {
                        active_object = collection.getObject(sf::Mouse::getPosition(window));
                        if (active_object != nullptr)
                        {
                            if (deleteChosen == true)
                            {
                                collection.remove(active_object);
                                active_object = nullptr;
                            }
                        }
                    }

                    //It's not a button of any kind, so it's a random position.
                if (colorChosen)
                    {
                        active_object = collection.getObject(sf::Mouse::getPosition(window));
                        active_object.get()->setFillColor(sf::Color::Cyan); 
                        colorChosen = false;
                    }
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