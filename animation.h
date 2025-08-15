#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Animation {
public:
    float Frame, speed;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;

    Animation();
    Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);
    void update();
    bool isEnd();
};
