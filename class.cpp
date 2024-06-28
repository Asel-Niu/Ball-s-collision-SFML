#include "class.hpp"

fixed_ball::fixed_ball(){
    position = sf::Vector2f(0.f, 0.f);
    size = 0.f;
    color = sf::Color::Red;
};

fixed_ball::fixed_ball(sf::Vector2f position_, float size_, sf::Color color_){
    position = position_;
    size = size_;
    color = color_;
};

fixed_ball::~fixed_ball(){};

void fixed_ball::draw(sf::RenderWindow& window){
    sf::CircleShape shape(size);
    shape.setFillColor(color);
    shape.setPosition(sf::Vector2f(-size, -size) + position);
    window.draw(shape);
};

//////////////////////////////////////////////

ball::ball() : fixed_ball(){
    speed = sf::Vector2f(0.f, 0.f);
    mass = 1.f;
};

ball::ball(sf::Vector2f position_, float size_, sf::Color color_, sf::Vector2f speed_, float mass_) : fixed_ball(position_, size_, color_){
    speed = speed_;
    mass = mass_;
};

ball::~ball(){};

void ball::move(float dTime){
    position += dTime*speed;
};

//////////////////////////////////////////////


line::line(){
    point_A = sf::Vector2f(0.f, 0.f);
    point_B = sf::Vector2f(0.f, 0.f);
    color = sf::Color::Red;
};

line::line(sf::Vector2f point_A_, sf::Vector2f point_B_, sf::Color color_){
    point_A = point_A_;
    point_B = point_B_;
    color = color_;
};

line::~line(){};

void line::draw(sf::RenderWindow& window){
    sf::Vertex line_[] = {
        sf::Vertex(point_A, color),
        sf::Vertex(point_B, color)
    };
    window.draw(line_, 2, sf::Lines);
};

//////////////////////////////////////////////

box::box(){
    position = sf::Vector2f(0.f, 0.f);
    size = sf::Vector2f(0.f, 0.f);
};

box::box(sf::Vector2f position_, sf::Vector2f size_){
    position = position_;
    size = size_;
};

box::~box(){};

void box::draw(sf::RenderWindow& window){
    sf::RectangleShape rectangle(size);
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(position);
    window.draw(rectangle);
};

//////////////////////////////////////////////

polygon::polygon(unsigned number_, sf::Vector2f* vertex_, bool closed_, sf::Color color_){
    number = number_;
    closed = closed_;
    color = color_;

    angle = new fixed_ball[number];
    for(unsigned i = 0; i < number; i++){
        angle[i] = fixed_ball(vertex_[i], 0.5f, color);
    };

    if(closed){
        wall = new line[number];
    } else wall = new line[number -1];
    for(unsigned i = 1; i < number; i++)
        wall[i - 1] = line(vertex_[i - 1], vertex_[i], color);
    if(closed) wall[number - 1] = line(vertex_[number - 1], vertex_[0], color);
};

polygon::~polygon(){
    delete[] angle;
    delete[] wall;
};

void polygon::draw(sf::RenderWindow& window){
    for(unsigned i = 0; i < (number - 1); i++)
        wall[i].draw(window);
    if(closed) wall[number - 1].draw(window);  
};

//////////////////////////////////////////////

bool is_collision(fixed_ball A, ball& B){
    sf::Vector2f interval = B.position - A.position;
    if(abs(interval) <= (A.size + B.size)){
        float cos_alpha = (sf::Vector2f(0.f, 1.f)*interval)/abs(interval);
        float sin_alpha = (sf::Vector2f(1.f, 0.f)*interval)/abs(interval);
        float cos_beta = (B.speed*interval)/(abs(B.speed)*abs(interval));
        float sin_beta = (B.speed*sf::Vector2f(cos_alpha, -sin_alpha))/abs(B.speed);

        sf::Vector2f speed;
        speed.x = cos_alpha*sin_beta - sin_alpha*cos_beta;
        speed.y = -sin_alpha*sin_beta - cos_alpha*cos_beta;
        speed = speed*abs(B.speed);
        B.speed = speed;

        return true;
    }

    return false;
}

bool is_collision(ball& A, ball& B){
    sf::Vector2f interval = B.position - A.position;
    if(abs(interval) <= (A.size + B.size)){
        sf::Vector2f speed_V = A.speed - B.speed;
        float cos_alpha = (sf::Vector2f(0.f, 1.f)*interval)/abs(interval);
        float sin_alpha = (sf::Vector2f(1.f, 0.f)*interval)/abs(interval);
        float cos_beta = (speed_V*interval)/(abs(speed_V)*abs(interval));
        float sin_beta = (speed_V*sf::Vector2f(cos_alpha, -sin_alpha))/abs(speed_V);

        sf::Vector2f speed_V1;
        speed_V1.x = cos_alpha*sin_beta + ((A.mass - B.mass)/(A.mass + B.mass))*sin_alpha*cos_beta;
        speed_V1.y = -sin_alpha*sin_beta + ((A.mass - B.mass)/(A.mass + B.mass))*cos_alpha*cos_beta;
        speed_V1 = speed_V1*abs(speed_V) + B.speed;

        sf::Vector2f speed_V2;
        speed_V2 = ((2*A.mass/(A.mass + B.mass))*cos_beta*abs(speed_V))*sf::Vector2f(sin_alpha, cos_alpha) + B.speed;
        
        A.speed = speed_V1;
        B.speed = speed_V2;

        return true;
    }    

    return false;
};

bool is_collision(line A, ball& B){
    sf::Vector2f AO = B.position - A.point_A;
    sf::Vector2f OB = A.point_B - B.position;
    sf::Vector2f AB = A.point_B - A.point_A;
            
    if((AO*AB > 0)&&(OB*AB > 0)){
        if((AO*AO - (AO*AB)*(AO*AB)/(AB*AB)) <= B.size*B.size){
            
            sf::Vector2f n;
            n.x = (A.point_B.y - A.point_A.y)/sqrt((A.point_B.x - A.point_A.x)*(A.point_B.x - A.point_A.x) + (A.point_B.y - A.point_A.y)*(A.point_B.y - A.point_A.y));
            n.y = -(A.point_B.x - A.point_A.x)/sqrt((A.point_B.x - A.point_A.x)*(A.point_B.x - A.point_A.x) + (A.point_B.y - A.point_A.y)*(A.point_B.y - A.point_A.y));
            
            sf::Vector2f l = AB/abs(AB);

            sf::Vector2f speed_x = (B.speed*l)*l;
            sf::Vector2f speed_y = (B.speed*n)*n;
            speed_y = -speed_y;
            B.speed = speed_x + speed_y;

            return true;
        }
    }

    return false;
};

bool is_collision(box A, ball& B){
    bool res = false;
    if((A.position.x + B.size) >= B.position.x){
        B.speed.x *= -1.f;
        res = true;
    }
    if((A.position.x + A.size.x - B.size) <= B.position.x){
        B.speed.x *= -1.f;
        res = true;
    }

    if((A.position.y + B.size) >= B.position.y){
        B.speed.y *= -1.f;
        res = true;
    }
    if((A.position.y + A.size.y - B.size) <= B.position.y){
        B.speed.y *= -1.f;
        res = true;
    }

    return res;
};

bool is_collision(polygon& A, ball& B){
    bool res = false;
    for(unsigned i = 0; i < (A.number - 1); i++){
        if(is_collision(A.wall[i], B)) res = true;
    }
    if(A.closed){
        if(is_collision(A.wall[A.number - 1], B)) res = true;
    }
    if(!res){
        for(unsigned i = 0; i < A.number; i++){
            if(is_collision(A.angle[i], B)) res = true;
        }
    }
    return res;
};

//////////////////////////////////////////////
