#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "BloxBox");

    sf::RectangleShape redBox(sf::Vector2f(20,20));
    redBox.setFillColor(sf::Color::Red);

    sf::RectangleShape greenBox(sf::Vector2f(20,20));
    greenBox.setFillColor(sf::Color::Green);
    greenBox.setPosition(0,25);

    sf::RectangleShape blueBox(sf::Vector2f(20,20));
    blueBox.setFillColor(sf::Color::Blue);
    blueBox.setPosition(0,50);

    std::vector<sf::RectangleShape> shapes = {redBox,greenBox,blueBox};

    sf::Text text;
    text.setString("Hello World");
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition(50,10);


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
                        for(auto x: shapes)
                        {
                            auto globalBounds = x.getGlobalBounds();
                            if(globalBounds.contains(mousePositionX,mousePositionY))
                            {
                                text.setFillColor(x.getFillColor());
                            }
                        }
                    }
                }
        }
        window.clear();
        window.draw(redBox);
        window.draw(greenBox);
        window.draw(blueBox);
        window.draw(text);
        window.display();
    }

    return 0;
}

//for use in wsl use this before running:
//export DISPLAY=$(ip route|awk '/^default/{print $3}'):0.0