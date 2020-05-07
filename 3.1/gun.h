#ifndef GUN_H
#define GUN_H
#include "objects.h"
#include <SFML/Graphics.hpp>
#include "bulet.h"
#include <list>

class Gun : public Object
{

private:
std::list<Bulet> bullets;

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

    void fire();

    void motion();

    Gun(const std::string name_file,
         const float obj_size_x,
         const float obj_size_y,
         int pos_x, int pos_y);

    Gun(const Gun&) = delete;


    void update(float time, sf::RenderWindow &window);
};

#endif