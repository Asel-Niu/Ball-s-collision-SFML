#include <SFML/Graphics.hpp>
#include <ctime>
#include "class.hpp"

int main()
{
    const unsigned SCREEN_WEIGHT = 550;
    const unsigned SCREEN_HIGHT = 350;
    const char *SCREEN_TITLE = "Ball`s collision";

    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE, sf::Style::Default, settings);

    sf::Event event;

    srand(time(0));
    ball point[20];
    for(unsigned i = 0; i < 10; i++){
        point[i] = ball(sf::Vector2f(30.f*i + 50.f, 40.f),
                   6.f,
                   sf::Color(rand()%256, 0, 0),
                   sf::Vector2f(1.f*(rand()%11 - 5), 1.f*(rand()%11 - 5)),
                   1.f);
    }
    for(unsigned i = 10; i < 20; i++){
        point[i] = ball(sf::Vector2f(30.f*i + 50.f, 60.f),
                   6.f,
                   sf::Color(rand()%256, 0, 0),
                   sf::Vector2f(1.f*(rand()%11 - 5), 1.f*(rand()%11 - 5)),
                   1.f);
    }

    ball point_(sf::Vector2f(50.f, 50.f),
               10.f,
               sf::Color::Blue,
               sf::Vector2f(-1.f, 1.f),
               1.f);

    sf::Vector2f vertex[] = {
        sf::Vector2f(70.f, 70.f),
        sf::Vector2f(200.f, 70.f),
        sf::Vector2f(200.f, 340.f)
    };

    sf::Vector2f vertex_[] = {
        sf::Vector2f(400.f, 70.f),
        sf::Vector2f(300.f, 70.f),
        sf::Vector2f(300.f, 200.f),
        sf::Vector2f(400.f, 200.f)
    };

    sf::Vector2f vertex__[] = {
        sf::Vector2f(450.f, 340.f),
        sf::Vector2f(540.f, 270.f),
    };

    polygon pol(3, vertex, false, sf::Color::Black);
    polygon pol_(4, vertex_, true, sf::Color::Black);
    polygon pol__(2, vertex__, false, sf::Color::Black);

    fixed_ball fix_point(sf::Vector2f(100.f, 200.f), 30.f, sf::Color::Black);
    
    box area(sf::Vector2f(10.f, 10.f), sf::Vector2f(530.f, 330.f));

    while (window.isOpen()){

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        

        for(unsigned i = 0; i < 20; i++){
            for(unsigned k = i + 1; k < 20; k++){
                collision(point[i], point[k]);
            }
            collision(fix_point, point[i]);
            collision(pol, point[i]);
            collision(pol_, point[i]);
            collision(pol__, point[i]);
            collision(area, point[i]);
            point[i].move(0.005f);
        }

        window.clear();
        point_.draw(window);
        area.draw(window);
        fix_point.draw(window);
        pol.draw(window);
        pol_.draw(window);
        pol__.draw(window);
        for(unsigned i = 0; i < 20; i++)
            point[i].draw(window);
        window.display();
    }

    return 0;
}
