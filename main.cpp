#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Collection.hpp"
#include "Factory.hpp"
#include "Action.hpp"
#include "Shapes/Circle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "BloxBox");
    CollectionMoveables<10> collection = {};
    shared_ptr<MoveableObject> active_object;

    auto defaultColor = sf::Color::Red;

    sf::RectangleShape placeBox(sf::Vector2f(20,20));
    placeBox.setFillColor(defaultColor);
    placeBox.setPosition(25,0);

    //sf::CircleShape placeCircle(10);
    //placeCircle.setFillColor(defaultColor);
    //placeCircle.setPosition(25,25);

    sf::Vector2f a = {25,25};
    collection.add(make_shared<Circle>(a, 10, defaultColor));

    // std::vector<sf::Drawable> &placeObjects = {placeCircle,placeBox};

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

    sf::Text text;
    text.setString("Hello World");
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition(50,10);

	Action actions[] = {Action(Keyboard::Left, [&]() { active_object->move(Vector2f(-2.0, 0.0)); }),
                      Action(Keyboard::Right, [&]() { active_object->move(Vector2f(+2.0, 0.0)); }),
                      Action(Keyboard::Up, [&]() { active_object->move(Vector2f(0.0, -2.0)); }),
                      Action(Keyboard::Down, [&]() { active_object->move(Vector2f(0.0, +2.0)); })};


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                int mousePositionX = event.mouseButton.x;
                int mousePositionY = event.mouseButton.y;

                if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        active_object = collection.getObject(sf::Mouse::getPosition(window));
                    }

                    //     for(auto x: colors)
                    //     {
                    //         auto globalBounds = x.getGlobalBounds();
                    //         if(globalBounds.contains(mousePositionX,mousePositionY))
                    //         {
                    //             //Later on this will set the color of the square and circle that we can place.
                    //             text.setFillColor(x.getFillColor());
                    //         }
                    //     }
                    // }
                }
        }
        window.clear();

        for(auto x : colors){
            window.draw(x);
        }

        collection.drawObjects(window);
        window.draw(placeBox);
        window.draw(text);
        window.display();

    }
    return 0;
}

//for use in wsl use this before running:
//export DISPLAY=$(ip route|awk '/^default/{print $3}'):0.0