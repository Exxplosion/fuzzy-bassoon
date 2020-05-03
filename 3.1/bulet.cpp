#include "bulet.h"
#include "objects.h"

 
Bulet::Bulet(const std::string name_file,
            const float obj_size_x,
            const float obj_size_y,
            int pos_x, int pos_y) :

        Object(name_file, obj_size_x, obj_size_y, pos_x, pos_y),
        currentFrame(0.0),
        previous_direction(RIGHT),
        ON_GROUND(true)
        {
            life = true;
            current_direction = STAY;
            acceleration_obj = {0, 0.0005};
            //velocity_obj = {0.3, -0.3};
            //velocity_obj.x = 0;
            //velocity_obj.y = 0;
        }


void Bulet::draw(sf::RenderWindow &window)
{
    if(life){
        this->obj_sprite.setTextureRect(sf::IntRect(SIZE_PICT$ * 551 * int(currentFrame), 0, SIZE_PICT$ * 551, SIZE_PICT$ * 509));
        window.draw(this->obj_sprite);
    }
    
}


void Bulet::motion()
{   
    

}

void Bulet::update(float time, sf::RenderWindow &window){
    this->pos_obj.x += this->velocity_obj.x * time;

    if (!this->ON_GROUND)
        this->velocity_obj.y = this->velocity_obj.y + acceleration_obj.y * time;

    this->pos_obj.y += this->velocity_obj.y * time;
    this->ON_GROUND = false;

    /* if (this->pos_obj.y > GROUND$)
    {
        this->pos_obj.y = GROUND$;
        this->velocity_obj.y = 0;
        this->ON_GROUND = true;
    } */
    IsWall();
    currentFrame += 0.005 * time;

    if (currentFrame > 4)  //fix this + spritesheet @TODO 
        currentFrame -= 4;

    this->obj_sprite.setPosition(this->pos_obj.x, this->pos_obj.y);

    draw(window);
    

    //this->velocity_obj.x = 0;
}


bool Bulet::IsWall(){
    if (pos_obj.y > GROUND$){
        velocity_obj = {0, 0};
        pos_obj.y = GROUND$;
        this->ON_GROUND = true;
        return 1;
    }
    return 0;
}
