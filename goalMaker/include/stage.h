#ifndef STAGE_H
#define STAGE_H
#include <SFML/Graphics.hpp>
#include <cmath>

class stage
{
    public:
        stage();
         int play1score();
         int play2score();
         int ballx();
         int bally();
         void genBar(int play);
         void smack(float vy);
         void setBall(int dx, int  dy);
         void update(int paddley);
         bool* getTr(){ return transparent;}
         sf::RectangleShape* getBar(){return bar;}
         void checkPaddle(float paddle1,float v1, float paddle2, float v2);
         void changeBV(int vx, int vy);
         bool getS(){ return serve; }
         void setPrep(bool k){ prep = k;}
         bool getPrep(){ return prep; }
         int getVX(){ return velocity[0]; }
         int getVY(){return velocity[1];}
         int getCount(){ return (aimcount/2);}
         void setPow(bool h){ powerup = h;}
         int* getCor(){ return powercoord;}
         void reset();
         bool P2turn(){ return turn2;}
         void useKenisis(){kenisis = true;}
         bool getKen(){return kenisis;}
         bool genPowerup();
         void setPtype(int n){ ptype = n;}
         int getPtype(){ return ptype;}
         void bshift(int dir);
         sf::CircleShape getBall(){
               if(kenisis){ ball.setFillColor(sf::Color(138, 00, 51));
               ball.setOutlineThickness(5);
               ball.setOutlineColor(sf::Color(79,9,93));}
               else{ ball.setFillColor(sf::Color::Blue);}
              return ball;
              }
         sf::RectangleShape up(){ return upper;}
         sf::RectangleShape down(){return lower;}
        virtual ~stage();
    protected:
    private:
        double velocity[2];
        int aimcount;
        int powercoord[2];
        sf::RectangleShape upper;
        sf::RectangleShape lower;
        sf::RectangleShape bar[5];
        bool transparent[5];
        bool kenisis;
        sf::CircleShape  ball;
        bool serve;
        bool prep;
        bool turn2 = false;
        bool gameover;
        int chance = 99;
        bool powerup = false;
        int ptype;
        sf::CircleShape pw;
        bool collide;
        int p1score;
        int p2score;

};

#endif // STAGE_H
