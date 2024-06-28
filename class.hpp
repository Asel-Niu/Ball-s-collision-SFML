#ifndef CLASS_HPP_
#define CLASS_HPP_

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "mathVector2f.hpp"

class fixed_ball{
public:
    sf::Vector2f position;
    float size;
    sf::Color color;
public:
    fixed_ball();
    fixed_ball(sf::Vector2f position_, float size_, sf::Color color_);
    ~fixed_ball();
    void draw(sf::RenderWindow& window);
};

//////////////////////////////////////////////

class ball : public fixed_ball{
public:
    sf::Vector2f speed;
    float mass;
public:
    ball();
    ball(sf::Vector2f position_, float size_, sf::Color color_, sf::Vector2f speed_ = sf::Vector2f(0.f, 0.f), float mass_ = 1.f);
    ~ball();
    void move(float dTime);
};

//////////////////////////////////////////////

class line{
public:
    sf::Vector2f point_A, point_B;
    sf::Color color;
public:
    line();
    line(sf::Vector2f point_A_, sf::Vector2f point_B_, sf::Color color_);
    ~line();
    void draw(sf::RenderWindow& window);
};

//////////////////////////////////////////////

class box{
public:
    sf::Vector2f position;
    sf::Vector2f size;
public:
    box();
    box(sf::Vector2f position_, sf::Vector2f size_);
    ~box();
    void draw(sf::RenderWindow& window);
    void collision(ball& B);
};

//////////////////////////////////////////////

class polygon{
public:
    unsigned number;
    bool closed;
    line* wall;
    fixed_ball* angle;
    sf::Color color;
public:
    polygon(unsigned number_, sf::Vector2f* vertex_, bool closed_, sf::Color color_);
    ~polygon();
    void draw(sf::RenderWindow& window);
};

//////////////////////////////////////////////

bool is_collision(fixed_ball A, ball& B);
bool is_collision(ball& A, ball& B);
bool is_collision(line A, ball& B);
bool is_collision(box A, ball& B);
bool is_collision(polygon& A, ball& B);

template <typename T>
void collision(T& A, ball& B){
    if(is_collision(A, B)){};
};

#endif
