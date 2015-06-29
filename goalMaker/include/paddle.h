#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>

class paddle
{
    public:
        paddle();
        paddle(bool mode);
        void move(int direction, int bally);
        float getY(){ return ytop; }
        float getV(){ return velocity[1]; }
        void aim(bool alter);
        bool getBot(){ return AI;}
        bool getA(){ return aiming;}
        void setX();
        void setAimCount(int n){ aimcount = n;}
        sf::RectangleShape getPad(){
            if(aiming){
                block.setFillColor(sf::Color(75,0,0));
            }
            else{ block.setFillColor(sf::Color::Cyan);}
             return block;}
        virtual ~paddle();
    protected:
    private:
        bool AI;
        bool aiming;
        int aimcount;
        sf::RectangleShape block;
        double accel[2];
        double velocity[2];
        float ytop;

};

#endif // PADDLE_H
