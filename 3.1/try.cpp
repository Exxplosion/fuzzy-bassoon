#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define NO_EVENT 228

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
           sf::Texture texture_ = sf::Texture(),
           sf::Sprite sprite_ = sf::Sprite()) :

    file_load_name(name_file),
    size_obj(obj_size_x, obj_size_y),
    texture(texture_),
    obj_sprite(sprite_),
    pos_obj(pos_x, pos_y),
    velocity_obj(0, 0),
    acceleration_obj(0, 0)
    {
        image.loadFromFile(file_load_name);
        image.createMaskFromColor(sf::Color::White);
        texture.loadFromImage(image);
        obj_sprite.setTexture(texture);
        obj_sprite.setTextureRect(sf::IntRect(0, 0, obj_size_x, obj_size_y));
        obj_sprite.setPosition(pos_obj.x, pos_obj.y);
    };

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
        RIGHT,   //+DIAG 
        STAY
    };

    short int previous_direction;
    short int current_direction;
    int NUMBER_SLIDE;
    bool ON_GROUND;

    sf::Clock clock;

    bool reflection;



    void draw(sf::RenderWindow &window)
    { 
        switch (current_direction)
        {
        case UP:
            break;
        case RIGHT:
            if (this->clock.getElapsedTime() > sf::seconds(0.09f))
            {
                this->obj_sprite.setTextureRect(sf::IntRect(300 * (NUMBER_SLIDE % 3), 203 * ((NUMBER_SLIDE / 3) % 3), 300, 203));
                this->clock.restart();
                if (NUMBER_SLIDE % 27 == 0)
                    NUMBER_SLIDE = NUMBER_SLIDE / 3;
                NUMBER_SLIDE++;
            }
            break;
        case LEFT:
            if (this->clock.getElapsedTime() > sf::seconds(0.09f))
            {
                this->obj_sprite.setTextureRect(sf::IntRect(300 * (NUMBER_SLIDE % 3), 203 * ((NUMBER_SLIDE / 3) % 3), 300, 203));
                this->clock.restart();
                if (NUMBER_SLIDE % 27 == 0)
                    NUMBER_SLIDE = NUMBER_SLIDE / 3;
                NUMBER_SLIDE++;
            }
            break;
        case DOWN:
            break;
        case STAY:
            this->obj_sprite.setTextureRect(sf::IntRect(300 * (NUMBER_SLIDE % 3), 203 * ((NUMBER_SLIDE / 3) % 3), 300, 203));
            break;
        default:
            break;
        } 
        window.draw(obj_sprite);
    }

    void control_Hero(int event_no)
    {
        this->velocity_obj.x -= 0.85 * this->velocity_obj.x;
        this->current_direction = STAY;
    }

    void control_Hero(sf::Event &event)
    {
        switch (event.key.code)
        {
            case (sf::Keyboard::Right) :
                this->current_direction = RIGHT;
                if (this->pos_obj.x < 900)
                {
                    this->velocity_obj.x += 1.0f;
                    this->velocity_obj += this->acceleration_obj;
                    this->pos_obj += this->velocity_obj;
                }
                else
                {
                    this->control_Hero(NO_EVENT);
                }
                reflection = true; //dont work
                break;
            case (sf::Keyboard::Left):
                this->current_direction = LEFT;
                if (this->pos_obj.x > 10)
                {
                    this->velocity_obj.x -= 1.0f;
                    this->velocity_obj += this->acceleration_obj;
                    this->pos_obj += this->velocity_obj;
                }
                else
                {
                    this->control_Hero(NO_EVENT);
                }
                reflection = false;
                break;
            case (sf::Keyboard::Down):
                //this->pos_obj.y += 1.1f;
                //this->obj_sprite.move(0, 1.1f);
                this->current_direction = DOWN;
                break;
            case (sf::Keyboard::Up):
                //this->pos_obj.y += -1.1f;
                //this->obj_sprite.move(0, -1.1f);
                this->current_direction = UP;
                break;
            default :
                break;
        }
        if (-100 < this->pos_obj.x && this->pos_obj.x < 1000)
        {
            this->velocity_obj += this->acceleration_obj;
            this->pos_obj += this->velocity_obj;
        }
        else
        {

            this->velocity_obj += this->acceleration_obj;
            this->pos_obj += this->velocity_obj;
            this->control_Hero(NO_EVENT);
        }
        

        this->obj_sprite.setPosition(this->pos_obj);
    }

    Hero(const std::string name_file,
           const float obj_size_x,
           const float obj_size_y,
           int pos_x, int pos_y,
           sf::Texture texture_ = sf::Texture(),
           sf::Sprite sprite_ = sf::Sprite()):
        Object(name_file,
               obj_size_x,
               obj_size_y,
               pos_x,
               pos_y,
               texture_,
               sprite_),
        clock(sf::Clock()){};

    Hero(const Hero&) = delete;
};

int main()
{
    Hero hero("dog.png", 300.0, 203.0, 0, 500);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "GO");

    sf::Event event;

    sf::Texture Bkg;
    if (!Bkg.loadFromFile("maxresdefault.jpg"))
    {
        return -1;
    }

    sf::Sprite Sprite;
    Sprite.setTexture(Bkg);

    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        while (window.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();
            // The escape key was pressed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed)
                hero.control_Hero(event);
            else
                hero.control_Hero(NO_EVENT);
        }

        window.draw(Sprite);
        hero.draw(window);
        window.display();
    }
}