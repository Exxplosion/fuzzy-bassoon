#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
//#include <Time.hpp>

#define GROUND$ 515

#define SIZE_PICT$ 0.4

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

    short int health_points;

    Object(const std::string name_file,
           const float obj_size_x,
           const float obj_size_y,
           int pos_x, int pos_y);

    virtual void draw(sf::RenderWindow &window) = 0;
};


class Hero : public Object
{
public:
    enum Direction
    {
        LEFT = 1,
        JUMP_UP_LEFT,
        JUMP_DOWN_LEFT,
        GOT_HIT_LEFT,
        DIZZY_LEFT,
        INVINCIBLE_LEFT,
        STAY_LEFT,
        RIGHT,
        JUMP_UP_RIGHT,
        JUMP_DOWN_RIGHT,
        GOT_HIT_RIGHT,
        DIZZY_RIGHT,
        INVINCIBLE_RIGHT,
        STAY_RIGHT,
        GAME_OVER
    };

    short int previous_direction;
    short int previous_direction_2;
    short int current_direction;
    int NUMBER_SLIDE;
    double currentFrame;

    bool ON_GROUND;
    bool ON_INVINCIBLE;

    const sf::Time COOLDOWN_INVINCIBLE;
    sf::Time recent_click;
    sf::Time first_click;
    sf::Time current_summary_time;
    const sf::Time permissible_summary_time;
    sf::Clock clock;

    virtual void draw(sf::RenderWindow &window);

    void motion();

    Hero(const std::string name_file,
         const float obj_size_x,
         const float obj_size_y,
         int pos_x, int pos_y);

    Hero(const Hero &) = delete;

    void update(float time);
};