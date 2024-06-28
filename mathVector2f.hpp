#ifndef MATHVECTOR2F_HPP_
#define MATHVECTOR2F_HPP_

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

float operator *(const sf::Vector2f& left, const sf::Vector2f& right);

float abs(sf::Vector2f A);

float cos(sf::Vector2f A, sf::Vector2f B);

#endif 