#include <SFML/Graphics.hpp>
#include <string>
//using namespace sf;

struct coordinates
{
    double x;
    double y;

    coordinates(double x_, double y_) :
        x(x_),
        y(y_)
    {};
};

class Object
{
public:
    const std::string file_load_name;
    const double size_x;
    const double size_y;
    sf::Texture texture;
    sf::Sprite obj_sprite;
    coordinates pos_obj;


    Object(const std::string name_file,
           const double obj_size_x,
           const double obj_size_y,
               sf::Texture texture_ = sf::Texture(),
           sf::Sprite sprite_ = sf::Sprite()) :

    file_load_name(name_file),
    size_x(obj_size_x),
    size_y(obj_size_y),
    texture(texture_),
    obj_sprite(sprite_),
    pos_obj(1.0, 1.0)
    {
        texture.loadFromFile(file_load_name);
        obj_sprite.setTexture(texture);
        obj_sprite.setTextureRect(sf::IntRect(0, 0, 21, 23));
        obj_sprite.setPosition(pos_obj.x, pos_obj.y);
    };

    virtual void draw(sf::RenderWindow &window) = 0;
    /*{
        sf::Clock clock;
        while(window.isOpen())
        {
            window.clear(sf::Color::White);
            window.draw(this->obj_sprite);
            //obj_sprite.setOrigin(size_x/2, size_y/2);
            
            if (clock.getElapsedTime() > sf::seconds(1))
            {
                this->obj_sprite.move(this->pos_obj.x, this->pos_obj.y);
                pos_obj.x = 0.1 * pos_obj.x + pos_obj.x;
                pos_obj.y = 0.1 * pos_obj.y + pos_obj.y;
                printf("HAHAA %f %f\n", pos_obj.x, pos_obj.y);
                clock.restart();
            }
            window.display();
        }
    } */
};


class Hero : public Object
{
public:
    sf::Clock clock;

    void draw(sf::RenderWindow &window)
    {
        while (window.isOpen())
        {
            window.clear(sf::Color::White);
            window.draw(obj_sprite);
            //obj_sprite.setOrigin(size_x/2, size_y/2);

            if (clock.getElapsedTime() > sf::seconds(1))
            {
                obj_sprite.move(this->pos_obj.x, this->pos_obj.y);
                pos_obj.x = 0.1 * pos_obj.x + pos_obj.x;
                pos_obj.y = 0.1 * pos_obj.y + pos_obj.y;
                printf("HAHAA %f %f\n", pos_obj.x, pos_obj.y);
                clock.restart();
            }
            window.display();
        }
    }

    Hero(const std::string name_file,
                const double obj_size_x,
                const double obj_size_y,
                sf::Texture texture_ = sf::Texture(),
                sf::Sprite sprite_ = sf::Sprite()):
        Object(name_file,
               obj_size_x,
               obj_size_y,
               texture_,
               sprite_),
        clock(sf::Clock())
    {};
};

int main()
{
    Hero hero("hero.png", 20, 20);
    sf::RenderWindow window(sf::VideoMode(2*128, 2*128), "GO");
   hero.draw(window);
    //hero.move_hero();

/*
    while (1)
    {
        window.clear(sf::Color::White);
        window.display();
    }
    //    window.draw(hero.obj_sprite);
*/

    return 0;
}