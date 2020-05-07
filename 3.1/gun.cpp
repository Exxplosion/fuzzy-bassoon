#include "gun.h"
#include "objects.h"

Gun::Gun(const std::string name_file,
            const float obj_size_x,
            const float obj_size_y,
            int pos_x, int pos_y) :

        Object(name_file, obj_size_x, obj_size_y, pos_x, pos_y),
        currentFrame(0.0),
        previous_direction(RIGHT),
        ON_GROUND(true)
        {
            current_direction = RIGHT;
            acceleration_obj = {0, 0.0005};
            //velocity_obj = {0.3, -0.3};
            //velocity_obj.x = 0;
            //velocity_obj.y = 0;
        }


void Gun::draw(sf::RenderWindow &window)
{
    this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * 551 * int(currentFrame), 0, SIZE_PICT$ * 551, SIZE_PICT$ * 509));

    window.draw(this->obj_sprite);
}


void Gun::fire(){
    if (bullets.size() == 0){

        Bulet my_bulet("Corgi.png", SIZE_PICT$ * 551.0, SIZE_PICT$ * 509.0, 0, GROUND$);

        my_bulet.current_direction = this->current_direction;
        my_bulet.velocity_obj.x = 0.3;
        my_bulet.velocity_obj.y = 0;
        bullets.push_back(my_bulet); //Пулю надо убрать в проверке касания со стенами?
        
    }

    if(bullets.size() != 0){
        
        if(!bullets.front().life){
            bullets.pop_front();
        } 
    }
}

void Gun::update(float time, sf::RenderWindow &window){
    draw(window);
    fire();
    if(bullets.size() != 0){
        bullets.front().update(time, window);
    }

      
}