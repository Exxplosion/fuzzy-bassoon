#include "slime.h"
#include "objects.h"

Slime::Slime(const std::string name_file,
            const float obj_size_x,
            const float obj_size_y,
            int pos_x, int pos_y) :

        Object(name_file, obj_size_x, obj_size_y, pos_x, pos_y),
        currentFrame(0.0),
        previous_direction(RIGHT),
        ON_GROUND(true)
        {
            current_direction = RIGHT;
            velocity_obj.x = 0.1;
        }



void Slime::draw(sf::RenderWindow &window)
{
    if (this->current_direction == RIGHT)
    {
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * 551 * int(currentFrame), 0, SIZE_PICT$ * 551, SIZE_PICT$ * 509));
    }
    if (this->current_direction == LEFT)
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * (551 * int(currentFrame) + 551), 0, -SIZE_PICT$ * 551, SIZE_PICT$ * 509));

    window.draw(this->obj_sprite);
}


void Slime::motion()
{   int a;
    //int a = CheckWallX();
    switch (a)
    {
    case LEFT:
        current_direction = LEFT;
        velocity_obj.x = -0.1;
        break;

    case RIGHT:
        current_direction = RIGHT;
        velocity_obj.x = 0.1;
        break;
    
    }

}

void Slime::update(float time){
    this->pos_obj.x += this->velocity_obj.x * time;

    currentFrame += 0.005 * time;

    if (currentFrame > 4)  //fix this + spritesheet @TODO 
        currentFrame -= 4;

    this->obj_sprite.setPosition(this->pos_obj.x, this->pos_obj.y);

    //this->velocity_obj.x = 0;
}
