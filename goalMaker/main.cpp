#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>
#include "stage.h";
#include "paddle.h";

using namespace std;

int main(){
  sf::RenderWindow window(sf::VideoMode(1000, 500), "Table Tennis");
  bool startscreen = true;
  sf::Texture powcon[3];
  if(!powcon[0].loadFromFile("src/p1.png")){ cout << "youch" << endl;}
   if(!powcon[1].loadFromFile("src/p2.png")){cout<< "youch" <<endl;}
    if(!powcon[2].loadFromFile("src/p3.png")){cout << "youch" << endl; }
    sf::Sprite icons[3];
    for(int k = 0; k < 3; k++){
        icons[k].setTexture(powcon[k]);
        icons[k].setPosition(250, 500);
    }

  string titl = "Table Tennis Tri";
  string pl1 = "One Player \n \n  (powerups are triggered with the A S D keys)";
  string pl2 = "Two Player";
  sf::Font font;
  if(!font.loadFromFile("Gabriola.ttf")){
    cout << "Font not loaded" << endl;
    exit(-1);
  }
  sf::Text title;
  sf::Text opt1;
  sf::Text opt2;
  title.setFont(font);
  title.setString(titl);
  title.setCharacterSize(35);
  title.setColor(sf::Color::White);
  title.setPosition(430, 100);
  opt1.setFont(font);
  opt1.setString(pl1);
  opt2.setString(pl2);
  opt1.setCharacterSize(25);
  opt1.setColor(sf::Color::Green);
   opt1.setPosition(340, 150);
  opt2.setFont(font);
  opt2.setCharacterSize(25);
  opt2.setColor(sf::Color::Green);
  opt2.setPosition(610, 150);
   stage daGame = stage();
   paddle player1;
   paddle player2;
   int tessel = 0;
    int whichP = 0;
    int whosP = -1;
   while(window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            window.close();
        }
        if(startscreen){


           if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
             sf::Vector2i locpos = sf::Mouse::getPosition(window);
             int xee = (int)(locpos.x);
             int yee = (int)(locpos.y);
             if(xee < 429 && xee > 339 && yee > 149 && yee < 180  ){
                startscreen = false;
                player1 = paddle();
                player2 = paddle(true);
                daGame.setBall(18, player1.getY());

             }
             else if(xee > 609 && xee < 709 && yee > 149 && yee < 180){
                    startscreen = false;
                player1 = paddle();
                player2 = paddle();
                player2.setX();
                daGame.setBall(18, player1.getY());
                opt2.setColor(sf::Color::Yellow);
             }

           }
        }

       }
       if(!startscreen){
            bool press = false;
             int direction = 0;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            press = true;
            direction = 1;
            if(daGame.getKen() && whosP == 0){
                daGame.bshift(1);

            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            press = true;
            if(daGame.getKen() && whosP == 0){
                daGame.bshift(0);

            }
          }
          if(press){ player1.move(direction, daGame.bally() + 30);}
           if(!player2.getBot()){
          bool press2 = false;
          direction = 0;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
            press2 = true;
            direction = 1;
            if(daGame.getKen() && whosP == 1){
                daGame.bshift(1);

            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            press2 = true;
            if(daGame.getKen() && whosP == 1){
                daGame.bshift(0);

            }
          }
          if(press2){
             player2.move(direction, daGame.bally());
          }
           }
          if(player2.getBot()){
          player2.move(direction, daGame.bally());
          }

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && daGame.getS()){
            daGame.smack(player1.getV());
          }
          if(!player2.getBot() && daGame.P2turn()){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && daGame.getS()){
            daGame.smack(player2.getV());
          }
          }
          if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) || player1.getA() ){
                bool defaul = false;
          if(daGame.getPtype() == 1 && whosP == 0){
            defaul = true;
            daGame.setPrep(true);


          }
            player1.aim(defaul);
            if(daGame.getPtype() == 1 && whosP == 0){
                    player1.setAimCount(daGame.getCount());
            player1.move(-1, daGame.bally() + 30);
            }
          }

          if( sf::Keyboard::isKeyPressed(sf::Keyboard::J) || player2.getA() ){
                bool defaul = false;
          if(daGame.getPtype() == 1 && whosP == 1){
            defaul = true;
            daGame.setPrep(true);

          }
            player2.aim(defaul);
            if(daGame.getPtype() == 1 && whosP == 1){
                    player2.setAimCount(daGame.getCount());
            player2.move(-1, daGame.bally() + 30);
            }
          }

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            bool defaul = false;
            if(daGame.getPtype() == 2 && whosP == 0){
                daGame.genBar(1);
            }
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !player2.getBot()){
            bool defaul = false;
            if(daGame.getPtype() == 2 && whosP == 1){
                daGame.genBar(2);
            }
          }

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            bool defaul = false;
            if(daGame.getPtype() == 3 && whosP == 0){
                daGame.useKenisis();
            }
          }

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !player2.getBot()){
            bool defaul = false;
            if(daGame.getPtype() == 3 && whosP == 1){
                daGame.useKenisis();
            }
          }
          if(player2.getBot()){
            if( whosP == 1 && daGame.getKen() && daGame.getVX() < 0 && daGame.ballx() < 150){
                daGame.bshift(1);
            }
          }


          bool create  = daGame.genPowerup();
           if(create && whichP == 0 && ! daGame.getS()){
            whichP = (tessel % 3) + 1;
            cout << "Which P? " << whichP << endl;
            int* loc = daGame.getCor();
            icons[whichP - 1].setPosition(loc[0], loc[1]);
              cout << loc[0] << " " << loc[1] << endl;
          }


          daGame.checkPaddle(player1.getY(), player1.getV(), player2.getY(), player2.getV());
          if(player2.getBot() || ! daGame.P2turn() ){
          daGame.update(player1.getY());
          }
          else if(!player2.getBot() && daGame.P2turn()){
            daGame.update(player2.getY());
          }

          if(whichP != 0){
            int bx = daGame.ballx() + 30;
            int by = daGame.bally() + 30;
            if(bx - 10 > icons[whichP - 1].getPosition().x  && bx < icons[whichP - 1].getPosition().x + 60
               && by > icons[whichP - 1].getPosition().y - 10 && by < icons[whichP - 1].getPosition().y + 80){
                daGame.setPtype(whichP);

                if(daGame.getVX() > 0){
                    whosP = 0;
                }

                 else if(player2.getBot()){
                    daGame.setPtype(whichP);
                    if(whichP == 2){
                    daGame.genBar(2);}
                    if(whichP == 1){
                        player2.aim(true);
                    }
                    else if(whichP == 3){
                     daGame.useKenisis();
                    }
                }
                else{
                    whosP = 1;
                }
                 whichP = 0;
               }

          }
           if(daGame.play1score() > 10 || daGame.play2score() > 10){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                 daGame.reset();
                 startscreen = true;
               }
        }
          }


       window.clear();
       if(startscreen){
       window.draw(title);
           window.draw(opt1);
           window.draw(opt2);
       }
       else{

        stringstream ss;
        sf::Text unscore;
         sf::Text toscore;
         unscore.setFont(font);
         unscore.setColor(sf::Color::White);
         toscore.setColor(sf::Color::White);
         toscore.setFont(font);
         ss << (daGame.play1score()) << "          " << (daGame.play2score());
         string temp = ss.str();
           string fin = "Player 1 wins!";
         if(daGame.play2score() > 10){
            fin = "Player 2 wins!";
        }
        if(daGame.play1score() > 10 || daGame.play2score() > 10){
            temp += " \n       " + fin;
        }
         unscore.setString(temp);
         unscore.setCharacterSize(30);
         toscore.setCharacterSize(30);
         unscore.setPosition(450, 80);
         toscore.setPosition(560, 80);

         window.draw(unscore);
         bool* tr = daGame.getTr();
         sf::RectangleShape* barrier = daGame.getBar();
         for(int i = 0; i < 5; i++){
            if(tr[i]){
                window.draw(barrier[i]);
            }
         }
           if(whichP != 0){
              icons[whichP - 1].setOrigin(25, 35);
              icons[whichP -1].rotate(15);
            window.draw(icons[whichP - 1]);
           }
         tessel++;
        if(daGame.getKen()){

            sf::CircleShape temp = daGame.getBall();
            temp.setFillColor(sf::Color(79,9,93));
              double scalar = .88;
              double diameter = 60;
             int dx = daGame.getVX();
             int dy = daGame.getVY();
             double ossel = (tessel % 11)/2;
             double angle = 3.14159265358979/4;
             srand(time(0));
             if( ossel != 5){
            for(int i = 0; i < 4; i++){
                   temp.scale(.84f, .84f);
                    //temp.setRadius(30 * (scalar * (i + 1)));
                    double rad = 30 * (scalar);
                    scalar *= scalar;
                   double ajust = (30 - rad)/(i + 2);
                   double yshift = (.6 * rad) * sin(angle * (i + ossel)) - 2;
                   double xshift = (.3 * rad) * cos(angle * (i + ossel));
                temp.move( -(dx * 2)  + xshift  , -(dy) + ajust + yshift  );
                window.draw(temp);

            }
        }
        }
          if(! daGame.getKen() || tessel % 11 != 5){
         window.draw(daGame.getBall());
       }

        window.draw(daGame.down());
        window.draw(daGame.up());
        window.draw(player1.getPad());
        window.draw(player2.getPad());
        sf::sleep(sf::milliseconds(30));
       }
        window.display();
   }
   return 0;
}
