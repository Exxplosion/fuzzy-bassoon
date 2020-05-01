#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define NO_EVENT 228

static float currentFrame = 0;

#define GROUND$ 211 

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
        image.createMaskFromColor(sf::Color::Black);
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
        RIGHT,
        JUMP_UP,
        JUMP_DOWN,
        STAY
    };

    short int previous_direction;
    short int previous_direction_2;
    short int current_direction;
    int NUMBER_SLIDE;
    double CURRENT_FLAME;
    bool ON_GROUND;

    sf::Clock clock;

    bool reflection;



        /**/
    void draw(sf::RenderWindow &window)
    {
        //printf("HAHA\n");

        if (this->current_direction == RIGHT)
        {
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 0, 551, 509));
            //printf("HAHA/n");
        }
        if (this->current_direction == LEFT)
            this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 0, -551, 509));

        if (this->current_direction == JUMP_UP)
        {
            if (this->previous_direction == RIGHT)
                this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 509, 551, 530));
            else
                this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 509, -551, 530));
            printf("%d \n", 505 * int(currentFrame));
        }

        if (this->current_direction == JUMP_DOWN)
        {
            if (this->previous_direction == RIGHT)
                this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 509 + 530, 551, 502));
            else
                this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 509 + 530, -551, 502));

            printf("%d \n", 505 * int(currentFrame));
        }

        if (this->current_direction == STAY)
        {
            if (this->previous_direction == RIGHT)
                this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame), 509 + 530 + 502, 551, 509));
            else
                this->obj_sprite.setTextureRect(sf::IntRect(551 * int(currentFrame) + 551, 509 + 530 + 502, -551, 509));
            printf("%d \n", 505 * int(currentFrame));
        }

        window.draw(this->obj_sprite);
    }

        
    void control_Hero(int event_no)
    {
        this->ON_GROUND = (this->pos_obj.y > 495);  //kosyak
        if (!this->ON_GROUND)
        {
            this->acceleration_obj.y = 1.5f;
        }
        else
        {
            this->acceleration_obj.y = 0;
            this->velocity_obj.y = 0;
        }
        this->velocity_obj += this->acceleration_obj;
        this->velocity_obj.x = 0;
        this->pos_obj += this->velocity_obj;
        this->current_direction = STAY;
    }


    void control_Hero(sf::Event &event)
    {
        this->ON_GROUND = (this->pos_obj.y > 495);
        switch (event.key.code)
        {
            case (sf::Keyboard::Right) :
                this->current_direction = RIGHT;
                if (this->pos_obj.x < 900)
                {
                    if (abs(this->acceleration_obj.x) < 1.5f)
                    {
                        this->acceleration_obj.x += 0.1f;
                    }
                    else
                    {
                        this->acceleration_obj.x = 0;   //кажется что собака прыгает вперёд, (исправить?)
                    }
                    this->velocity_obj.x += 1.0f;
                    this->velocity_obj += this->acceleration_obj;
                    this->pos_obj += this->velocity_obj;
                }
                else
                {
                    this->acceleration_obj.x = 0;
                    this->velocity_obj.x = 0.f;
                    this->control_Hero(NO_EVENT);
                }
                reflection = true; //dont work
                break;
            case (sf::Keyboard::Left):
                this->current_direction = LEFT;
                if (this->pos_obj.x > 10)
                {
                    if (abs(this->acceleration_obj.x) < 1.5f)
                    {
                        this->acceleration_obj.x += -0.1f;
                    }
                    else
                    {
                        this->acceleration_obj.x = 0; //кажется что собака прыгает вперёд, (исправить?)
                    }
                    this->velocity_obj.x += -1.0f;
                    this->velocity_obj += this->acceleration_obj;
                    this->pos_obj += this->velocity_obj;
                }
                else
                {
                    this->acceleration_obj.x = 0;
                    this->velocity_obj.x = 0.f;
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
            case (sf::Keyboard::Space):
                if (this->ON_GROUND)
                {
                    printf("JUUUMP %f, %f, %d\n", this->pos_obj.x, this->pos_obj.y, this->ON_GROUND);
                    //this->acceleration_obj.y += -5.0f;
                    this->velocity_obj.y += -40.0f;
                    this->velocity_obj += this->acceleration_obj;
                    this->pos_obj += this->velocity_obj;
                    this->current_direction = UP;
                }
                break;
            default :
                printf("WTFFF %f, %f, %d\n", this->pos_obj.x, this->pos_obj.y, this->ON_GROUND);
                break;
            if (!this->ON_GROUND)
            {
                this->acceleration_obj.y = 1.5f;
                this->velocity_obj += this->acceleration_obj;
                this->pos_obj += this->velocity_obj;
            }
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
        clock(sf::Clock()),
        CURRENT_FLAME(0.0),
        previous_direction(RIGHT){};

    Hero(const Hero&) = delete;

    void update(float time)
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

    if (currentFrame > 4)
        currentFrame -= 4;

    this->obj_sprite.setPosition(this->pos_obj.x - 0, this->pos_obj.y - 0);

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
};

int main()
{

    Hero hero("Corgi_2.png", 551.0, 509.0, 0, GROUND$);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "GO");


    sf::Texture Bkg;
    if (!Bkg.loadFromFile("maxresdefault.jpg"))
    {
        return -1;
    }

    sf::Sprite Sprite;
    Sprite.setTexture(Bkg);

    sf::Clock clock;
    sf::Event event;
    hero.ON_GROUND = true;
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 1000;

       // if (time > 20)
        //    time = 20;

        window.clear(sf::Color::White);
        window.pollEvent(event);

        if (event.type == sf::Event::Closed)
            window.close();
        // The escape key was pressed
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            hero.velocity_obj.x = -0.1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            hero.velocity_obj.x = 0.1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (hero.ON_GROUND)
            {
                hero.velocity_obj.y = -0.35;
                hero.ON_GROUND = false;
                //hero.current_direction = Hero::JUMP_UP;
            }
        }

        hero.update(time);

        window.draw(Sprite);
        hero.draw(window);
        window.display();
    }
}