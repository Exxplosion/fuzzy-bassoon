#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define GROUND$ 211

class Game
{
public:
    sf::RenderWindow window;
    sf::Texture Background;
    sf::Sprite sprite_background;
    sf::Event event_game;
    sf::Clock clock_game;
    float time_game;
/*
    Game(sf::Texture texture_,
         sf::Sprite sprite_, sf::Event event_,
         sf::Clock clock_);*/
         
    Game();

    void run();

    Game(const Game &) = delete;
};



class Object
{
public:
    const std::string file_load_name;

    const sf::Vector2f size_obj;

    sf::Image image;
    sf::Texture texture; //stdmap ; texture manager use??
    sf::Sprite obj_sprite;

    sf::Vector2f pos_obj;
    sf::Vector2f velocity_obj;
    sf::Vector2f acceleration_obj;

    Object(const std::string name_file,
           const float obj_size_x,
           const float obj_size_y,
           int pos_x, int pos_y, 
           sf::Texture texture_,
           sf::Sprite sprite_);

    virtual void draw(sf::RenderWindow &window) = 0;
};


class Hero : public Object
{
public:
    enum Direction
    {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT,
        JUMP_UP,
        JUMP_DOWN,
        STAY
    };

    short int previous_direction;
    short int previous_direction_2;
    short int current_direction;
    int NUMBER_SLIDE;
    double currentFrame;
    bool ON_GROUND;

    virtual void draw(sf::RenderWindow &window);

    void motion();

    Hero(const std::string name_file,
         const float obj_size_x,
         const float obj_size_y,
         int pos_x, int pos_y);

    Hero(const Hero &) = delete;

    void update(float time);
};