#ifndef SLIME_H
#define SLIME_H
#include "objects.h"
#include <SFML/Graphics.hpp>


//Этот враг максимально простой. Ходит влево/вправо, при соударении о стенку меняет направление.
class Slime : public Object
{
public:
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
    bool CheckWall();

    void motion();

    Slime(const std::string name_file,
         const float obj_size_x,
         const float obj_size_y,
         int pos_x, int pos_y);

    Slime(const Slime &) = delete;

    void update(float time);
};

#endif