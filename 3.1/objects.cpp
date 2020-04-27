#include "objects.h"

Object::Object(const std::string name_file,
       const float obj_size_x,
       const float obj_size_y,
       int pos_x, int pos_y, sf::Texture texture_ = sf::Texture(),
           sf::Sprite sprite_ = sf::Sprite()) : 
        velocity_obj(0, 0),
        acceleration_obj(0, 0),
        file_load_name(name_file),
        size_obj(obj_size_x, obj_size_y),
        pos_obj(pos_x, pos_y),
        texture(texture_),
        obj_sprite(sprite_)
        {
            image.loadFromFile(file_load_name);
            image.createMaskFromColor(sf::Color::Black);
            texture.loadFromImage(image);
            obj_sprite.setTexture(texture);
            obj_sprite.setTextureRect(sf::IntRect(0, 0, obj_size_x, obj_size_y));
            obj_sprite.setPosition(pos_obj.x, pos_obj.y);
        }

Hero::Hero(const std::string name_file,
            const float obj_size_x,
            const float obj_size_y,
            int pos_x, int pos_y) :

        Object(name_file, obj_size_x, obj_size_y, pos_x, pos_y),
        currentFrame(0.0),
        previous_direction(RIGHT),
        ON_GROUND(true)
        {}

void Hero::motion()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->velocity_obj.x = -0.1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->velocity_obj.x = 0.1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (this->ON_GROUND)
        {
            this->velocity_obj.y = -0.35;
            this->ON_GROUND = false;
            //hero.current_direction = Hero::JUMP_UP;
        }
    }
}

void Hero::draw(sf::RenderWindow &window)
{

    if (this->current_direction == RIGHT)
    {
        this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 0, 551, 509));
    }
    if (this->current_direction == LEFT)
        this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 0, -551, 509));

    if (this->current_direction == JUMP_UP)
    {
        if (this->previous_direction == RIGHT)
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 509, 551, 530));
        else
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 509, -551, 530));
    }

    if (this->current_direction == JUMP_DOWN)
    {
        if (this->previous_direction == RIGHT)
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 509 + 530, 551, 502));
        else
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 509 + 530, -551, 502));
    }

    if (this->current_direction == STAY)
    {
        if (this->previous_direction == RIGHT)
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 509 + 530 + 502, 551, 509));
        else
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 509 + 530 + 502, -551, 509));
    }

    window.draw(this->obj_sprite);
}

void Hero::update(float time)
{

    this->pos_obj.x += this->velocity_obj.x * time;

    if (!this->ON_GROUND)
        this->velocity_obj.y = this->velocity_obj.y + 0.0005 * time;

    this->pos_obj.y += this->velocity_obj.y * time;
    this->ON_GROUND = false;

    if (this->pos_obj.y > GROUND$)
    {
        this->pos_obj.y = GROUND$;
        this->velocity_obj.y = 0;
        this->ON_GROUND = true;
    }

    currentFrame += 0.005 * time;

    if (currentFrame > 4)  //fix this + spritesheet @TODO 
        currentFrame -= 4;

    this->obj_sprite.setPosition(this->pos_obj.x, this->pos_obj.y);

    this->previous_direction_2 = this->current_direction;

    if (this->current_direction == LEFT || this->current_direction == RIGHT)
    {
        this->previous_direction = this->current_direction;
    }

    if (this->velocity_obj.y < 0)
    {
        this->current_direction = JUMP_UP;
    }
    else
    {
        if (this->velocity_obj.y > 0)
        {
            this->current_direction = JUMP_DOWN;
        }
        else
        {
            if (this->velocity_obj.x > 0)
            {
                this->current_direction = RIGHT;
            }
            else
            {
                if (this->velocity_obj.x < 0)
                {
                    this->current_direction = LEFT;
                }
                else
                {
                    this->current_direction = STAY;
                }
            }
        }
    }

    if (this->previous_direction_2 != this->current_direction)
    {
        currentFrame = 0;
    }

    this->velocity_obj.x = 0;
}
/*
Game::Game(sf::Texture texture_ = sf::Texture(),
    sf::Sprite sprite_ = sf::Sprite(), sf::Event event_ = sf::Event(),
    sf::Clock clock_ = sf::Clock()):
     window(sf::VideoMode(1280, 720), "GO"),
     time_game(0.0),
     Background(texture_),
     sprite_background(sprite_),
     event_game(event_),
     clock_game(clock_)
     {
         Background.loadFromFile("maxresdefault.jpg");
         sprite_background.setTexture(Background);
     }
*/

Game::Game() : 
    window(sf::VideoMode(1280, 720), "GO"),
    time_game(0.0),
    Background(sf::Texture()),
    sprite_background(sf::Sprite()),
    event_game(sf::Event()),
    clock_game(sf::Clock())
{
    Background.loadFromFile("maxresdefault.jpg");
    sprite_background.setTexture(Background);
}

void Game::run()
{
    Hero hero("Corgi_2.png", 551.0, 509.0, 0, GROUND$);

    while(window.isOpen())
    {
        this->time_game = clock_game.getElapsedTime().asMicroseconds();
        this->clock_game.restart();

        this->time_game = this->time_game / 1000;

        if (this->time_game > 20)
            this->time_game = 20;

        window.clear();
        window.pollEvent(event_game);

        if (event_game.type == sf::Event::Closed)
            window.close();
        // The escape key was pressed
        if ((event_game.type == sf::Event::KeyPressed) && (event_game.key.code == sf::Keyboard::Escape))
            window.close();

        hero.motion();

        hero.update(time_game);

        window.draw(sprite_background);
        hero.draw(window);
        window.display();
    }
}