#ifndef BULET_H
#define BULET_H
#include "objects.h"
#include <SFML/Graphics.hpp>


//Для правильности работы этого объекта противник, который его использует должен задать начальные скорости и направление.
class Bulet : public Object
{

public:

bool life;

    enum Direction
    {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT,
        STAY,
    };

    short int previous_direction;
    short int previous_direction_2;
    short int current_direction;
    int NUMBER_SLIDE;
    double currentFrame;
    bool ON_GROUND;

    virtual void draw(sf::RenderWindow &window);

    bool IsWall();

    void motion();

    Bulet(const std::string name_file,
         const float obj_size_x,
         const float obj_size_y,
         int pos_x, int pos_y);


    void update(float time, sf::RenderWindow &window);
};

#endif