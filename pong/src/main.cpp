#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "pong.hpp"
#include "mat3.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "math.hpp"
#include "vec2.hpp"

#define FONT_NOT_LOADED_ERR -1

void drawPlayer(sf::RenderWindow& window, vec2& pos);
void drawBall(sf::RenderWindow& window, vec2& pos);
void drawMiddleLine(sf::RenderWindow& window);
bool isMoveAllowed(vec2& paddle_pos);
bool isInside(vec2& position, vec2& area);
bool ballCollideWithPlayer(Ball& ball, Player& player);
void resetBallAndPlayersPosition(Ball& ball, Player& player1, Player& player2);

const int paddle_p1_x_axis = 50;
const int paddle_p2_x_axis = 750;

const int game_width = 800;
const int game_height = 600;

using namespace std;

int main()
{
    bool round_active = false;
    int collisionCount = 0;
    Player p1(paddle_p1_x_axis, game_height/2);
    Player p2(paddle_p2_x_axis, game_height/2);
    Ball ball(game_width/2, game_height/2);

    // Set window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Foobar");
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("comic.ttf")) {
        return FONT_NOT_LOADED_ERR;
    }

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
            }
        }

        // Start the round is not already started when the player push the space bar
        if (!round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            round_active = true;
            ball.vector = angleToVec(160);
        }
        else if (round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            ball.pos = vec2(game_width/2, game_height/2);
            ball.pos_dest = ball.pos;
            ball.vector = angleToVec(160);
        }

        if (round_active) {

            // player 1 move handling
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                p1.pos_dest.y -= elapsed.asSeconds()*Player::speed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                p1.pos_dest.y += elapsed.asSeconds()*Player::speed;
            }

            // Move the ball if round active
            if (round_active) {
                float ballSpeed = Ball::speed * (1 + (0.2 * collisionCount));
                ball.pos_dest.x = ball.pos.x+(ball.vector.x*elapsed.asSeconds() * ballSpeed);
                ball.pos_dest.y = ball.pos.y+(ball.vector.y*elapsed.asSeconds() * ballSpeed);
            }

            if (isMoveAllowed(p1.pos_dest)) {
                p1.setDestAsNewPos();
            }
            else {
                p1.resetDest();
            }


            // player 2 AI
            bool isBallComingToP2 = (ball.vector.x>0);
            if (!isBallComingToP2) {
                //go back to the center of the screen, then idle
                if (p2.pos.y<(game_height/2)) {
                    p2.pos_dest.y += elapsed.asSeconds()*Player::speed;
                }
                else if (p2.pos.y>(game_height/2)) {
                    p2.pos_dest.y -= elapsed.asSeconds()*Player::speed;
                }
            }
            else {
                // dummy follow the ball
                if (ball.pos.y>p2.pos.y && ball.vector.y>=0) {
                    p2.pos_dest.y += elapsed.asSeconds()*Player::speed;
                }
                else if (ball.pos.y<p2.pos.y && ball.vector.y<=0) {
                    p2.pos_dest.y -= elapsed.asSeconds()*Player::speed;
                }
            }
            if (isMoveAllowed(p2.pos_dest)) {
                p2.setDestAsNewPos();
            }
            else {
                p2.resetDest();
            }

            // handle ball collision
            bool collideWithTop = ball.pos_dest.y<0;
            bool collideWithBottom = ball.pos_dest.y+Ball::height>game_height;
            bool collideWithLeftGoal = ball.pos_dest.x<0;
            bool collideWithRightGoal = ball.pos_dest.x+Ball::width>game_width;
            // collide with players
            if (ballCollideWithPlayer(ball, p1) || ballCollideWithPlayer(ball, p2)) {
                // should compute the exact place where the ball meet the paddle
                // otherwise bad thing could happens if time elapsed between 2 frames is too big
                ball.resetDest();
                ball.vector.x = -ball.vector.x;
                collisionCount++;
            }
            // collide with top and bottom  border
            if (collideWithTop || collideWithBottom) {
                ball.resetDest();
                ball.vector.y = -ball.vector.y;
            }
            else {
                ball.setDestAsNewPos();
            }
            // collide with goals
            if (collideWithLeftGoal) {
                resetBallAndPlayersPosition(ball, p1, p2);
                p2.score++;
                collisionCount = 0;
                round_active = false;
            }
            else if (collideWithRightGoal) {
                resetBallAndPlayersPosition(ball, p1, p2);
                p1.score++;
                collisionCount = 0;
                round_active = false;
            }
        }

        // draw
        // clear the window with black color
        window.clear(sf::Color::Black);
        drawPlayer(window, p1.pos);
        drawPlayer(window, p2.pos);
        drawBall(window, ball.pos);
        drawMiddleLine(window);

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        if (!round_active) {
            text.setString("Press Space button to begin !");
            window.draw(text);
        }

        text.setString(std::to_string(p1.score));
        text.setPosition((game_width/2)-30, 20);
        window.draw(text);

        text.setString(std::to_string(p2.score));
        text.setPosition((game_width/2)+30, 20);
        window.draw(text);

        window.display();
    }
    return 0;
}

void resetBallAndPlayersPosition(Ball& ball, Player& player1, Player& player2)
{
    player1.pos = vec2(paddle_p1_x_axis, game_height/2);
    player1.pos_dest = player1.pos;
    player2.pos = vec2(paddle_p2_x_axis, game_height/2);
    player2.pos_dest = player2.pos;
    ball = Ball(game_width/2, game_height/2);
}

bool ballCollideWithPlayer(Ball& ball, Player& player)
{
    if (((ball.pos_dest.x>player.pos_dest.x) && (ball.pos_dest.x<(player.pos_dest.x+Player::width))) ||
            (((ball.pos_dest.x+Ball::width)>player.pos_dest.x)
                    && ((ball.pos_dest.x+Ball::width)<(player.pos_dest.x+Player::width)))) {
        return !(ball.pos_dest.y+Ball::height<player.pos_dest.y ||
                ball.pos_dest.y>(player.pos_dest.y+Player::height));
    }
    return false;
}

bool isMoveAllowed(vec2& paddle_pos)
{
    vec2 area(game_width, game_height);
    vec2 paddle_right_corner(paddle_pos.x+Player::width, paddle_pos.y+Player::height);

    return isInside(paddle_pos, area) &&
            isInside(paddle_right_corner, area);
}

bool isInside(vec2& pos, vec2& area)
{
    return !(pos.x<0 ||
            pos.y<0 ||
            pos.x>area.x ||
            pos.y>area.y);
}

void drawPlayer(sf::RenderWindow& window, vec2& pos)
{
    sf::RectangleShape shape(sf::Vector2f(Player::width, Player::height));
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(sf::Color::White);

    window.draw(shape);
}

void drawMiddleLine(sf::RenderWindow& window) {
    sf::RectangleShape shape(sf::Vector2f(2, game_height));
    shape.setPosition(game_width/2, 0);
    shape.setFillColor(sf::Color::White);

    window.draw(shape);
}

void drawBall(sf::RenderWindow& window, vec2& pos)
{
    sf::RectangleShape shape(sf::Vector2f(Ball::width, Ball::height));
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(sf::Color::White);

    window.draw(shape);
}