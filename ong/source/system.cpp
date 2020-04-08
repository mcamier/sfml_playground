#include "../header/system.hpp"

#include <TE/math/math.hpp>

//
//
void OngCollisionSystem::preUpdate(const Time& time) {
    this->p1 = getComponent<COngPlayer>(this->playerOneId);
    this->p2 = getComponent<COngPlayer>(this->playerTwoId);
}

void OngCollisionSystem::update(const Time& time, EntityId entityId) {
    auto* bp = getComponent<CPosition>(entityId);
    auto* bc = getComponent<COngBall>(entityId);

    if (bc->last_hit_by == players::p1 && ballCollideWithPaddle(bp, p2)) {
        ECSMessage collisionMsg(MSG_BALL_HIT);
        sendMessage(entityId, collisionMsg);
    } else if (bc->last_hit_by == players::p2 && ballCollideWithPaddle(bp, p1)) {
        ECSMessage collisionMsg(MSG_BALL_HIT);
        sendMessage(entityId, collisionMsg);
    }
}

void OngCollisionSystem::handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) {

}

const string& OngCollisionSystem::getName() {
    return name;
}

bool OngCollisionSystem::collideWithArc(CPosition* ballPos, COngPlayer* player) {
    ballPos->position.normalize();
    int ball_degrees = vectorToDegrees(ballPos->position);
    int player_degrees = player->angle;

    if (player_degrees <= player->paddle_half_arc) {
        float max = player_degrees + player->paddle_half_arc;
        float sub_360 = 360 - (player_degrees - player->paddle_half_arc);
        return ball_degrees <= max &&
               (ball_degrees >= 0 || ball_degrees >= sub_360);
    } else if (player_degrees >= (360 - player->paddle_half_arc)) {
        float min = player_degrees - player->paddle_half_arc;
        float up_0 = 360 - player_degrees;
        return ball_degrees >= min &&
               (ball_degrees <= 360 || ball_degrees <= up_0);
    } else {
        float min = player_degrees - player->paddle_half_arc;
        float max = player_degrees + player->paddle_half_arc;
        return ball_degrees >= min && ball_degrees <= max;
    }
}

bool OngCollisionSystem::ballCollideWithPaddle(CPosition* ballPos, COngPlayer* player) {
    if (isOutsideCircle(ballPos->position.x, ballPos->position.y, arena_radius - default_ball_radius) &&
        isInsideCircle(ballPos->position.x, ballPos->position.y, arena_radius)) {

        return collideWithArc(ballPos, player);
    }
    return false;
}


//
//
void KineticSystem::update(const Time& time, EntityId entityId) {
    auto* p = getComponent<CPosition>(entityId);
    auto* k = getComponent<CKinetic>(entityId);

    if (k->speed != 0) {
        p->position.x = p->position.x + (k->direction.x * time.asSeconds() * k->speed);
        p->position.y = p->position.y + (k->direction.y * time.asSeconds() * k->speed);
    }
}

void KineticSystem::handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) {

}

const string& KineticSystem::getName() {
    return name;
}


//
//
void OngPlayerSystem::update(const Time& time, EntityId entityId) {

}

void OngPlayerSystem::handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) {
    if(msg.type == MSG_PLAYER_MOVE_LEFT) {
        auto* player = getComponent<COngPlayer>(target);
        player->angle -= time.asSeconds() * default_player_speed;
        player->clampAngle();
        auto* pos = getComponent<CPosition>(target);
        pos->position = getPointOnArc(player->angle, arena_radius);
    }
    else if(msg.type == MSG_PLAYER_MOVE_RIGHT) {
        auto* player = getComponent<COngPlayer>(target);
        player->angle += time.asSeconds() * default_player_speed;
        player->clampAngle();
        auto* pos = getComponent<CPosition>(target);
        pos->position = getPointOnArc(player->angle, arena_radius);
    }
}

const string& OngPlayerSystem::getName() {
    return name;
}
