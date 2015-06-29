#include "paddle.h"

paddle::paddle()
{
    AI = false;
    aiming = false;
    block = sf::RectangleShape(sf::Vector2f(20, 70));
    block.setFillColor(sf::Color::Cyan);
    block.setPosition(0, 200);
    velocity[0] = 0;
    velocity[1] = 0;
    aimcount = 0;
    accel[0] = 3;
    accel[1] = 3;
    ytop = 200;


}

paddle::paddle(bool mode){
  if(!mode){ paddle();}
  else{
      AI = true;
    block = sf::RectangleShape(sf::Vector2f(20, 70));
    block.setFillColor(sf::Color::Cyan);
    block.setPosition(980, 200);
    velocity[0] = 11;
    velocity[1] = 11;
    accel[0] =1.8;
    accel[1] = 1.8;
    ytop = 200;
    aiming = false;
    aimcount = 0;

  }

}

void paddle::aim(bool shift){
aiming = shift;
}

void paddle::move(int direction, int bally){
    if(!AI){
            if(aiming){
                direction = -1;
            }
    if(direction == 1 && ytop >  10){
         if(velocity[1] >= 0){
            velocity[1] = -3;
         }
        velocity[1] -= accel[1];
        if(velocity[1] < -22){
            velocity[1] = -22;
        }
        if(velocity[1] > 22){
            velocity[1] = 22;
        }
        block.move(0, velocity[1]);

    }
    if(direction == 0 && ytop < 490){
            if(velocity[1] <= 0){
                velocity[1] = 3;
            }
        velocity[1] += accel[1];
        if(velocity[1] < -22){
            velocity[1] = -22;
        }
        if(velocity[1] > 22){
            velocity[1] = 22;
        }
        block.move(0, velocity[1]);
    }

     if(aiming){

            block.setPosition(block.getPosition().x, bally - 35);
            if(aimcount >= 3){
                aimcount = 0;
                aiming = false;
            }
     }

    int check = (int) block.getPosition().y;
         ytop = check;
         if(check < 10){
            ytop = 10;
            block.setPosition(block.getPosition().x, 10);
         }
         if(check > 420){
            ytop = 420;
             block.setPosition(block.getPosition().x, 420);
         }



}
else{
    int midy = ytop + 35;
    if(midy <= bally + 25 && midy + 25 >= bally){}
    else if(midy > bally + 25){
        block.move(0, -velocity[1]);
    }
    else if(midy + 2 < bally){
        block.move(0, velocity[1]);
    }
    int check = (int) block.getPosition().y;
         ytop = check;
         if(check < 10){
            ytop = 10;
            block.setPosition(block.getPosition().x, 10);
         }
         if(check > 490){
            ytop = 490;
             block.setPosition(block.getPosition().x, 490);
         }

}
}

void paddle::setX(){
block.move(980, 0);}


paddle::~paddle()
{}

