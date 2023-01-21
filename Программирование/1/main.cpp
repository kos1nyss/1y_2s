#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <ctime>

class AnimatedText {
private:
    std::string text;
    int duration;

public:
    AnimatedText(const std::string& _text, const int& _duration) {
        text = _text;
        duration = _duration;
    }

    std::string get_text(int timestamp) {
        int seconds = timestamp % (duration + 1);
        std::string cropped_text = text.substr(0, text.size() * seconds / duration);
        return cropped_text;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(170, 40), "AnimatedText");

    int duraton = 13;
    std::string printed_text = "Hello, world";
    AnimatedText animated_text = AnimatedText(printed_text, duraton);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(sf::Color::White);

    float timestamp;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        timestamp = std::clock();

        text.setPosition(0, 0);
        text.setString(animated_text.get_text(timestamp / 1000 + 1));

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}