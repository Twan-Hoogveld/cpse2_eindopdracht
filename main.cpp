#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Collection.hpp"
#include "Factory.hpp"
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
    //----------------------MOVE TOOL---------------------------------------------
    sf::Image img;
    img.loadFromFile("..//img//move.png"); //Double for linux
    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite sprite(texture);
    sprite.setPosition(0,175);
    sprite.scale(sf::Vector2f(0.1,0.1));
    //----------------------------DELETE TOOL------------------------------------------------
    sf::Image img2;
    img2.loadFromFile("..//img//trash.jpg");
    sf::Texture texture2;
    texture2.loadFromImage(img2);
    sf::Sprite sprite2(texture2);
    sprite2.setPosition(25,175);
    sprite2.scale(sf::Vector2f(0.1,0.1));
    //============================PLUS=========================================================
    sf::Image img3;
    img3.loadFromFile("..//img//plus.png");
    sf::Texture texture3;
    texture3.loadFromImage(img3);
    sf::Sprite sprite3(texture3);
    sprite3.setPosition(25,210);
    sprite3.scale(sf::Vector2f(0.03,0.03));
    //=============================MINUS=======================================================
    sf::Image img4;
    img4.loadFromFile("..//img//minus.png");
    sf::Texture texture4;
    texture4.loadFromImage(img4);
    sf::Sprite sprite4(texture4);
    sprite4.setPosition(0,210);
    sprite4.scale(sf::Vector2f(0.03,0.03));
    //=================OUTLINE TOGGLE==========================================================
    sf::Image img5;
    img5.loadFromFile("..//img//outline.png");
    sf::Texture texture5;
    texture5.loadFromImage(img5);
    sf::Sprite sprite5(texture5);
    sprite5.setPosition(0,250);
    sprite5.scale(sf::Vector2f(0.1,0.1));
    //============================BACKGROUND FORGROUND TEXT====================================
    sf::Text fg;
    fg.setString("Foreground");
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    fg.setFont(font);
    fg.setCharacterSize(18);
    fg.setFillColor(sf::Color::White);
    fg.setPosition(0,280);

    sf::Text bg;
    bg.setString("Background");
    bg.setFont(font);
    bg.setCharacterSize(18);
    bg.setFillColor(sf::Color::White);
    bg.setPosition(0,300);

    //===================================VECTORS FOR EASY DRAWING AND SELCTING=================
    std::vector<sf::RectangleShape> colors = {redBox,greenBox,blueBox,yellowBox,whiteBox,purpleBox,cyanBox};
    std::vector<sf::Sprite> sprites = {sprite,sprite2,sprite3,sprite4,sprite5};
    std::vector<sf::Text> tx = {fg,bg};
    //=========================================================================================
    bool moveChosen = false;
    bool deleteChosen = false;
    bool colorChosen = false;
    bool plusChosen = false;
    bool minusChosen = false;
    bool outlineChosen = false;
    bool fgChosen = false;
    bool bgChosen = false;
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
            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left) && moveChosen == true && active_object != nullptr)
            {
                auto mPos = sf::Mouse::getPosition(window);
                active_object->jump(sf::Vector2f(mPos.x,mPos.y)); 
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) //are any of the colors clicked?
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
                        collection.add(make_shared<Rectangle>(sf::Vector2f(50,0),sf::Vector2f(70,20),currentColor));
                    }

                //Is the move tool selected? Then the other tools will be not selected.
                if(sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        deleteChosen = false;
                        colorChosen = false;
                        plusChosen = false;
                        minusChosen = false;
                        moveChosen = true;
                        outlineChosen = false;
                        fgChosen = false;
                        bgChosen = false;
                    }

                //Is the delete tool selected?
                if(sprite2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        plusChosen = false;
                        minusChosen = false;
                        deleteChosen = true;                        
                        outlineChosen = false;
                        fgChosen = false;
                        bgChosen = false;
                    }

                //Is the plus tool selected?
                if(sprite3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        deleteChosen = false;
                        plusChosen = true;
                        minusChosen = false;
                        outlineChosen = false;
                        fgChosen = false;
                        bgChosen = false;
                    }

                //Is the minus tool selected?
                if(sprite4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        deleteChosen = false;
                        minusChosen = true;
                        plusChosen = false;
                        outlineChosen = false;
                        fgChosen = false;
                        bgChosen = false;
                    }

                //Is the outline toggle tool selected?
                if(sprite5.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        deleteChosen = false;
                        minusChosen = false;
                        plusChosen = false;
                        outlineChosen = true;
                        fgChosen = false;
                        bgChosen = false;

                    }

                //Is the fg tool selected?
                if(fg.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        deleteChosen = false;
                        minusChosen = false;
                        plusChosen = false;
                        outlineChosen = false;
                        fgChosen = true;
                        bgChosen = false;

                    }                
                //Is the bg toggle tool selected?
                if(bg.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
                    {
                        moveChosen = false;
                        colorChosen = false;
                        deleteChosen = false;
                        minusChosen = false;
                        plusChosen = false;
                        outlineChosen = false;
                        fgChosen = false;
                        bgChosen = true;
                    }

                //Delete the object you clicked on if you are in delete mode.
                if(deleteChosen) 
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

                //If you are in color choose mode, you can change any objects color.
                else if (colorChosen)
                    {
                        active_object = collection.getObject(sf::Mouse::getPosition(window));
                        active_object->setFillColor(currentColor); 
                    }
                
                else if (outlineChosen)
                    {
                        active_object = collection.getObject(sf::Mouse::getPosition(window));
                        active_object->setOutlineColor(currentColor); 
                    }

                else if (minusChosen)
                    {
                    active_object = collection.getObject(sf::Mouse::getPosition(window));
                    auto scale = active_object->getScale();
                    active_object->setScale(scale.x - 0.1 ,scale.y - 0.1);
                    }
                else if (plusChosen)
                {
                    active_object = collection.getObject(sf::Mouse::getPosition(window));
                    auto scale = active_object->getScale();
                    active_object->setScale(scale.x + 0.1 ,scale.y + 0.1);                
                }

                else if (bgChosen)
                {
                    active_object = collection.getObject(sf::Mouse::getPosition(window));
                    collection.moveToBackground(active_object);
                }
                else if(fgChosen)
                {
                    active_object = collection.getObject(sf::Mouse::getPosition(window));
                    //collection.moveToForeground(active_object);
                }
                else
                    {
                    active_object = collection.getObject(sf::Mouse::getPosition(window));
                    }
            }
        }

        //Clear the window of the old.
        window.clear();

        //Draw the color tiles.
        for(auto x : colors)
        {
            window.draw(x);
        }

        //Draw the selector boxes
        window.draw(squareBox);
        window.draw(circleBox);

        //Draw all the items that were created during this run.
        collection.drawObjects(window);

        //Draw all the sprites
        for(auto x : sprites)
        {
            window.draw(x);
        }

        for (auto x : tx)
        {
            window.draw(x);
        }

        //Display it all.
        window.display();
    }
    return 0;
}