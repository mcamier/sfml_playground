#ifndef FOOBAR_GAMESCREEN_HPP
#define FOOBAR_GAMESCREEN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "player.hpp"
#include "../utils/screen/screen.hpp"
#include "ball.hpp"
#include "../pong/game_screen.hpp"

class GameScreen : public Screen {

private:
    // all screen
    bool isLoaded = false;

    // pong game screen
    sf::Font font;

    const int game_width = 200;
    const int game_height = 200;
    const int arena_radius = 75;
    bool round_active = true;

    Player p1, p2;
    Ball ball;

public:
    GameScreen() {
        this->transitionDurationSec = 0.0f;
        p1 = Player(180);
        p2 = Player(0);
    }

    bool load()
    {
        if (!font.loadFromFile("PressStart2P.ttf")) {
            this->isLoaded = false;
            return false;
        }

        ball = Ball(game_width/2 - Ball::radius, game_height/2 - Ball::radius);
        this->isLoaded = true;

        return this->isLoaded;
    }

    void update(const sf::Time& time) override
    {
        float elapsedSec = time.asSeconds();

        // Start the round is not already started when the player push the space bar
        /*if (!round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            round_active = true;
            ball.vector = angleToVec(180);
        }*/

        if (round_active) {
            // player 1 move handling
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                p1.angle -= elapsedSec * Player::speed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                p1.angle += elapsedSec * Player::speed;
            }

            float decimal = p1.angle - (int)p1.angle;
            if(p1.angle >= 360) {
                p1.angle = (int)p1.angle % 360;
                p1.angle += decimal;
            }
        }
    }

    bool handleEvent(const sf::Event& event) override
    {
        return false;
    }

    void render(sf::RenderTexture& target) override
    {
        sf::RectangleShape vline(sf::Vector2f(1.f, game_height));
        vline.setPosition(game_width / 2, 0);
        vline.setFillColor(sf::Color::Magenta);
        sf::RectangleShape hline(sf::Vector2f(game_width, 1.f));
        hline.setPosition(0, game_height / 2);
        hline.setFillColor(sf::Color::Magenta);
        target.draw(vline);
        target.draw(hline);

        drawBall(target, ball.pos);
        drawPlayer(target, p1);


        sf::Rect<float> bounding_box = getPlayerBoundingBox(p1);
        sf::Vector2f vector_2_f(bounding_box.width, bounding_box.height);
        sf::Vector2f pos(bounding_box.left, bounding_box.top);
        sf::RectangleShape rectangle_shape = sf::RectangleShape(vector_2_f);
        rectangle_shape.setPosition(pos);
        rectangle_shape.setFillColor(sf::Color::Transparent);
        rectangle_shape.setOutlineThickness(1);
        rectangle_shape.setOutlineColor(sf::Color::Red);
        target.draw(rectangle_shape);
    }

private:
    sf::Rect<float> getPlayerBoundingBox(Player& player) {
        vec2 p_1 = getPointOnArc(player.angle - Player::arc_paddle_angle_half * 2, arena_radius - 2);
        vec2 p_2 = getPointOnArc(player.angle - Player::arc_paddle_angle_half * 2, arena_radius + 2);
        vec2 p_3 = getPointOnArc(player.angle + Player::arc_paddle_angle_half * 2, arena_radius - 2);
        vec2 p_4 = getPointOnArc(player.angle + Player::arc_paddle_angle_half * 2, arena_radius + 2);

        vec2 p_upperLeftPoint = upperLeftPoint(p_1, p_2, p_3, p_4);
        vec2 p_lowerRightPoint = lowerRightPoint(p_1, p_2, p_3, p_4);

        sf::Rect<float> rect(p_upperLeftPoint.x,
                p_upperLeftPoint.y,
                p_lowerRightPoint.x - p_upperLeftPoint.x,
                p_lowerRightPoint.y - p_upperLeftPoint.y);
        return rect;
    }

    vec2 upperLeftPoint(vec2 p_1, vec2 p_2, vec2 p_3, vec2 p_4) {
        vec2 result = p_1;

        if(p_2.x <= result.x && p_2.y <= result.y) {
            result = p_2;
        }
        if(p_3.x <= result.x && p_3.y <= result.y) {
            result = p_3;
        }
        if(p_4.x <= result.x && p_4.y <= result.y) {
            result = p_4;
        }
        return result;
    }

    vec2 lowerRightPoint(vec2 p_1, vec2 p_2, vec2 p_3, vec2 p_4) {
        vec2 result = p_1;

        if(p_2.x >= result.x && p_2.y >= result.y) {
            result = p_2;
        }
        if(p_3.x >= result.x && p_3.y >= result.y) {
            result = p_3;
        }
        if(p_4.x >= result.x && p_4.y >= result.y) {
            result = p_4;
        }
        return result;
    }

    void drawPlayer(sf::RenderTexture& tex, Player& player) {
        vec2 p = getPointOnArc(player.angle - Player::arc_paddle_angle_half * 2, arena_radius);
        vec2 p1 = getPointOnArc(player.angle - Player::arc_paddle_angle_half, arena_radius);
        vec2 p2 = getPointOnArc(player.angle, arena_radius);
        vec2 p3 = getPointOnArc(player.angle + Player::arc_paddle_angle_half, arena_radius);
        vec2 p4 = getPointOnArc(player.angle + Player::arc_paddle_angle_half * 2, arena_radius);


        sf::CircleShape shape(3);
        shape.setFillColor(sf::Color::White);

        shape.setPosition(p.x, p.y);
        tex.draw(shape);
        shape.setPosition(p1.x, p1.y);
        tex.draw(shape);
        shape.setPosition(p2.x, p2.y);
        tex.draw(shape);
        shape.setPosition(p3.x, p3.y);
        tex.draw(shape);
        shape.setPosition(p4.x, p4.y);
        tex.draw(shape);
    }

    vec2 getPointOnArc(float angle, float radius) {
        vec2 v = angleToVec(angle);
        v.y = -v.y;
        v.scale(radius);

        //relative to the center of the arena
        v.x += game_width/2;
        v.y += game_height/2;
        return v;
    }

    void drawBall(sf::RenderTexture& tex, vec2& pos)
    {
        sf::CircleShape shape(Ball::radius);
        shape.setPosition(pos.x , pos.y);
        shape.setFillColor(sf::Color::White);
        tex.draw(shape);
    }
};

#endif
