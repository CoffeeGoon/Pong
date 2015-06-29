#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "stage.h"

using namespace std;
stage::stage()
{
    ball = sf::CircleShape(30);
    ball.setFillColor(sf::Color::Blue);
    upper = sf::RectangleShape(sf::Vector2f(1000, 10));
    upper.setFillColor(sf::Color::Magenta);
    lower = sf::RectangleShape(sf::Vector2f(1000, 10));
    lower.setFillColor(sf::Color::Magenta);
    powercoord[0] = (rand() % 500) + 300;
    powercoord[1] = (rand() % 300) + 100;
    upper.setPosition(0,0);
    lower.setPosition(0, 490);
    ptype = 0;
    prep = false;
    aimcount = 0;
    kenisis = false;
    serve = true;
    gameover = false;
    collide = false;
    velocity[0] = 0;
    velocity[1] = 0;
    p1score = 0;
    p2score = 0;
     for(int i = 0; i < 5; i++){
       bar[i] = sf::RectangleShape(sf::Vector2f(10, 70));
       bar[i].setPosition(200, 55 + (i * 80) + 8);
       bar[i].setFillColor(sf::Color::Green);
       transparent[i] = false;
      }

}

void stage::reset(){
p1score = 0;
p2score = 0;
aimcount = 0;
gameover = false;
ptype = 0;
prep = false;
powerup = false;
 kenisis = false;
    serve = true;
    gameover = false;
    collide = false;
    velocity[0] = 0;
    velocity[1] = 0;
    for(int i = 0; i < 5; i++){
        transparent[i] = false;
    }
}

stage::~stage()
{
    //dtor
}

bool stage::genPowerup(){
if(!powerup && ptype == 0 && !serve){
    srand(time(0));
     cout << "chance " << chance << endl;
    if(chance < rand() % 100){
        powerup = true;
        chance = 99;
        powercoord[0] = (rand() % 500) + 300;
        powercoord[1] = (rand() % 300) + 100;
        return true;

    }
}
return false;

}

void stage::genBar(int play){
    ptype = 0;
    powerup = false;
    chance = 99;
for(int i = 0; i < 5; i++){
    transparent[i] = true;
    if(play == 2){
       bar[i].setPosition(790, bar[i].getPosition().y);
}
else{
     bar[i].setPosition(200, bar[i].getPosition().y);
}
}
}

void stage::bshift(int n){
    kenisis = false;
    ptype = 0;
    powerup = false;
    chance = 99;
  if(n == 1){
    velocity[1] -= 14;
  }
  else{
    velocity[1] += 14;
  }
}

int stage::play1score(){
   return p1score;
}
int stage::play2score(){
   return p2score;
}
int stage::ballx(){
   sf::Vector2f temp = ball.getPosition();
   int tempx = (int)(temp.x);
   return tempx;
}
int stage::bally(){
 sf::Vector2f temp = ball.getPosition();
   int tempy = (int)(temp.y);
   return tempy;
}

void stage::setBall(int dx, int dy){
      ball.setPosition(dx, dy);
}
void stage::update(int paddley){
   if(!gameover){
    if(serve){
        sf::Vector2f temp = ball.getPosition();
        if(!turn2){
        ball.setPosition(20, paddley);}
        else if(turn2){
            ball.setPosition(920, paddley);
        }
    }
    else{
        if(!collide){
                sf::Vector2f temp = ball.getPosition();
                sf::Vector2f tempup = upper.getPosition();
                sf::Vector2f tempdown = lower.getPosition();
                 if(temp.y < tempup.y){
                    collide = true;
                    velocity[1] = -velocity[1];
                    velocity[0] = velocity[0] + velocity[0]/10;
                    if(velocity[0] > 40){
                        velocity[0] = 40;
                    }
                    if(velocity[0] < -40){
                        velocity[0] = -40;
                    }
                 }
            else if(temp.y + 60 > tempdown.y){
                    collide = true;
                velocity[1] = -(velocity[1] + velocity[1]/15);
                velocity[0] = velocity[0] + velocity[0]/10;
                 if(velocity[0] > 40){
                        velocity[0] = 40;
                    }
                    if(velocity[0] < -40){
                        velocity[0] = -40;
                    }
            }
            if(temp.x < -60){
                p2score++;
                chance -= 20;
                serve = true;
                collide = false;
            }
            if(temp.x > 1060){
                p1score++;
                chance -= 20;
                serve = true;
                turn2 = true;
                collide = false;
            }
            if(!serve && !collide){
                ball.move(velocity[0], velocity[1]);
            }
        }
        else{
             ball.move(velocity[0], velocity[1]);
            sf::Vector2f temp = ball.getPosition();
                if(temp.x < -30){
                        chance -= 20;
                p2score++;
                serve = true;
            }
            if(temp.x > 1030){
                p1score++;
                chance -= 20;
                serve = true;
            }
            collide = false;
        }


    }
if(p1score > 10 || p2score > 10){
            gameover = true;

        }
   }
}

void stage::checkPaddle(float paddle1, float v1, float paddle2, float v2){
     sf::Vector2f pos = ball.getPosition();
      int tempx = (int)pos.x;
      int tempy = (int)(pos.y + 30);
      if(tempx < 20 && tempy > paddle1 && tempy < paddle1 + 100 ){
        collide = true;
        chance -= 5;
        if(powerup && ptype == 1 && prep){
            aimcount++;
            if(aimcount > 5){
                powerup = false;
                prep = false;
                ptype = 0;
                aimcount = 0;
            }
        }

        double middle = paddle1 + 35;
        double vshift = 0;
        if(tempy > middle + 10){
            vshift = 5;
        }
        if(tempy < middle - 10){
                vshift = -5;

        }

        velocity[0] = - (velocity[0] + velocity[0]/7);
        velocity[1] =  velocity[1] + (- velocity[1]/10) + v1/5 + vshift;

      }
      else if(tempx > 920 && tempy > paddle2 && tempy < paddle2 + 100){
            collide = true;
             chance -= 5;
            if(prep && powerup && ptype == 1){
            aimcount++;
            if(aimcount > 5){
            ptype = 0;
            aimcount = 0;
            prep = false;
            powerup = false;

            }
        }

             double middle = paddle2 + 35;
        double vshift = 0;
        if(tempy > middle + 10){
            vshift = 5;
        }
        if(tempy < middle - 10){
                vshift = -5;

        }
        velocity[0] = - (velocity[0] + velocity[0]/7);
        velocity[1] =  velocity[1] + (- velocity[1]/10) + v2/5 + vshift;
      }
      else{
        for(int i = 0; i < 5; i++){
            if(transparent[i]){
                if(velocity[0] < 0 && bar[i].getPosition().x < 500){
                    if(tempx < bar[i].getPosition().x + 10 && tempy > bar[i].getPosition().y && tempy < bar[i].getPosition().y +  70){
                        transparent[i] = false;
        collide = true;
        double middle = bar[i].getPosition().y + 40;
        double vshift = 0;
        if(tempy > middle + 10){
            vshift = 5;
        }
        if(tempy < middle - 10){
                vshift = -5;

        }

        velocity[0] = - (velocity[0] + velocity[0]/7);
        velocity[1] =  velocity[1] + (- velocity[1]/10) + v1/5 + vshift;
                          break;
                    }
                }
                else if(velocity[0] > 0 && bar[i].getPosition().x > 500){
                    if(tempx + 60 > bar[i].getPosition().x  && tempy > bar[i].getPosition().y && tempy < bar[i].getPosition().y +  70){
                        transparent[i] = false;
        collide = true;
        double middle = bar[i].getPosition().y + 40;
        double vshift = 0;
        if(tempy > middle + 10){
            vshift = 5;
        }
        if(tempy < middle - 10){
                vshift = -5;

        }

        velocity[0] = - (velocity[0] + velocity[0]/7);
        velocity[1] =  velocity[1] + (- velocity[1]/10) + v1/5 + vshift;
                          break;
                    }
                }

            }
        }


      }


}


void stage::smack(float v){
    velocity[0] = 8;
    if(turn2){
        velocity[0] = -8;
        turn2 = false;
    }
    velocity[1] = v/8;
    serve = false;
}

void stage::changeBV(int vx, int vy){
velocity[0] = (double) vx;
velocity[1] = (double) vy;

}

