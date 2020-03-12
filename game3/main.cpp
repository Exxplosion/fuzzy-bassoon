#include <SFML/Graphics.hpp>

using namespace sf;
int main()

{
    RenderWindow window(VideoMode(128, 128), "Lesson 4. kychka-pc.ru");


    Texture herotexture;
    herotexture.loadFromFile("./hero.png");

    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 0, 21, 23)); //получили нужный нам прямоугольник с котом
    herosprite.setPosition(1, 1);

    bool right = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))
        {
            herosprite.move(-0.1, 0);
            herosprite.setTextureRect(IntRect(0, 0, 21, 23));
            herosprite.setScale(-1, 1);
            right = false;
        } //добавили управление на клавиши W,S,A,D
        if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))
        {
            herosprite.move(0.1, 0);
            herosprite.setTextureRect(IntRect(0, 0, 21, 23));
            herosprite.setScale(1, 1);
            right = true;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))))
        {
            herosprite.move(0, -0.1);
            herosprite.setTextureRect(IntRect(0, 28, 26, 27));

            if (right)
                herosprite.setScale(1, 1);
            else
                herosprite.setScale(-1, 1);
            
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))))
        {
            herosprite.move(0, 0.1);
            herosprite.setTextureRect(IntRect(28, 30, 16, 22));
            if (right)
                herosprite.setScale(1, 1);
            else
                herosprite.setScale(-1, 1);
        }
        window.clear();
        window.draw(herosprite);
        window.display();
    }

    return 0;
}

// 0 0 21 23
// 23, 0, 24, 21
// 49, 0, 16, 23
// 69, 0, 21, 21


//0, 28, 26, 27
//28, 30, 16, 22
//47, 28, 28, 21

//10, 60, 16, 29
//34, 59, 26, 29
