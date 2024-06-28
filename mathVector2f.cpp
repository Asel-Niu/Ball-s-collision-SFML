#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "mathVector2f.hpp"

float operator *(const sf::Vector2f& left, const sf::Vector2f& right){
    return (left.x*right.x + left.y*right.y);
}

float abs(sf::Vector2f A){
    return sqrt(A*A);
}

float cos(sf::Vector2f A, sf::Vector2f B){
    return (A*B)/(abs(A)*abs(B));
}