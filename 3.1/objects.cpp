#include "objects.h"

Object::Object(const std::string name_file,
       const float obj_size_x,
       const float obj_size_y,
       int pos_x, int pos_y) :
        velocity_obj(0, 0),
        acceleration_obj(0, 0),
        file_load_name(name_file),
        size_obj(obj_size_x, obj_size_y),
        pos_obj(pos_x, pos_y),
        health_points(0),
        texture(sf::Texture()),
        obj_sprite(sf::Sprite())
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
        ON_GROUND(true),
        COOLDOWN_INVINCIBLE(sf::seconds(3.0))
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        this->ON_INVINCIBLE = true;
        if (this->previous_direction_2 > 7)
        {
            this->current_direction = INVINCIBLE_RIGHT;
            this->velocity_obj.x = 1.0;
        }
        else 
        {
            this->current_direction = INVINCIBLE_LEFT;
            this->velocity_obj.x = -1.0;
        }
    }
}

void Hero::draw(sf::RenderWindow &window)
{
    //this->current_direction = INVINCIBLE_LEFT;
    switch (this->current_direction)
    {
    case JUMP_DOWN_LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), SIZE_PICT$ * (509 + 530), -SIZE_PICT$ * 551, SIZE_PICT$ * 502));
        break;
    case LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), 0, -SIZE_PICT$ * 551, SIZE_PICT$ * 509));
        break;
    case JUMP_UP_LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), SIZE_PICT$ * 509, -SIZE_PICT$ * 551, SIZE_PICT$ * 530));
        break;
    case STAY_LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), SIZE_PICT$ * (509 + 530 + 502), -SIZE_PICT$ * 551, SIZE_PICT$ * 509));
        break;
    case GOT_HIT_LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (615 * int(currentFrame) + 615), SIZE_PICT$ * 3397, -SIZE_PICT$ * 615, SIZE_PICT$ * 481));
        break;
    case DIZZY_LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), SIZE_PICT$ * 2902, -SIZE_PICT$ * 551, SIZE_PICT$ * 492));
        break;
    case INVINCIBLE_LEFT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (1460 * int(currentFrame) + 1460), SIZE_PICT$ * 2053, -SIZE_PICT$ * 1460, SIZE_PICT$ * 2053));
        break;
    case JUMP_DOWN_RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * 551 * int(currentFrame), SIZE_PICT$ *(509 + 530), SIZE_PICT$ * 551, SIZE_PICT$ * 502));
        break;
    case RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * 551 * int(currentFrame), 0, SIZE_PICT$ * 551, SIZE_PICT$ * 509));
        break;
    case JUMP_UP_RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame)), SIZE_PICT$ * 509, SIZE_PICT$ * 551, SIZE_PICT$ * 530));
        break;
    case STAY_RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * 551 * int(currentFrame), SIZE_PICT$ *(509 + 530 + 502), SIZE_PICT$ * 551, SIZE_PICT$ * 509));
        break;
    case GOT_HIT_RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (615 * int(currentFrame) + 615), SIZE_PICT$ * 3397, SIZE_PICT$ * 615, SIZE_PICT$ * 481));
        break;
    case DIZZY_RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), SIZE_PICT$ * 2902, SIZE_PICT$ * 551, SIZE_PICT$ * 492));
        break;
    case INVINCIBLE_RIGHT:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (1460 * int(currentFrame)), SIZE_PICT$ * 2053, SIZE_PICT$ * 1460, SIZE_PICT$ * 2053));
        //this->obj_sprite.setOrigin();
        break;
    case GAME_OVER:
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), 0, -SIZE_PICT$ * 551, SIZE_PICT$ * 509));
        break;
    default:
        break;
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

    if (currentFrame > 8) //TODO: fix this + spritesheet
        currentFrame -= 8;

    this->obj_sprite.setPosition(this->pos_obj.x, this->pos_obj.y);

    this->previous_direction_2 = this->current_direction;

    if (this->current_direction == LEFT || this->current_direction == RIGHT)
    {
        this->previous_direction = this->current_direction;
    }

    if (this->ON_INVINCIBLE)
    {
        this->velocity_obj.x = 0;
        this->ON_INVINCIBLE = false;
        return;
    }

    if (this->velocity_obj.x > 0 && this->velocity_obj.y > 0)
    {
        this->current_direction = JUMP_UP_RIGHT;
    }
    else if (this->velocity_obj.x > 0 && this->velocity_obj.y < 0)
    {
        this->current_direction = JUMP_DOWN_RIGHT;
    }
    else if (this->velocity_obj.x < 0 && this->velocity_obj.y > 0)
    {
        this->current_direction = JUMP_UP_LEFT;
    }
    else if (this->velocity_obj.x < 0 && this->velocity_obj.y < 0)
    {
        this->current_direction = JUMP_DOWN_LEFT;
    }
    else if (this->velocity_obj.x > 0 && this->velocity_obj.y == 0)
    {
        this->current_direction = RIGHT;
    }
    else if (this->velocity_obj.x < 0 && this->velocity_obj.y == 0)
    {
        this->current_direction = LEFT;
    }
    else if (this->velocity_obj.x == 0 && this->velocity_obj.y < 0)
    {
        if (this->previous_direction_2 < 8)
        {
            this->current_direction = JUMP_DOWN_LEFT;
        }
        else
        {
            this->current_direction = JUMP_DOWN_RIGHT;
        }
    }
    else if (this->velocity_obj.x == 0 && this->velocity_obj.y > 0)
    {
        if (this->previous_direction_2 < 8)
        {
            this->current_direction = JUMP_UP_LEFT;
        }
        else
        {
            this->current_direction = JUMP_UP_RIGHT;
        }
    }
    else
    {
        if (this->previous_direction_2 < 8)
        {
            this->current_direction = STAY_LEFT;
        }
        else
        {
            this->current_direction = STAY_RIGHT;
        }
    }

        this->velocity_obj.x = 0;
}

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
    Hero hero("Corgi_2.png", SIZE_PICT$ * 551.0, SIZE_PICT$ * 509.0, 0, GROUND$);

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