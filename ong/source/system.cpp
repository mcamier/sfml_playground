#include "../header/system.hpp"

#include <TE/math/math.hpp>

//
//
void CollisionSystem::preUpdate(const Time& time) {
    this->p1 = getComponent<COngPlayer>(this->playerOneId);
    this->p2 = getComponent<COngPlayer>(this->playerTwoId);
}

void CollisionSystem::update(const Time& time, EntityId entityId) {
    auto* bp = getComponent<CPosition>(entityId);
    auto* bc = getComponent<COngBall>(entityId);

    if (bc->last_hit_by == players::p1 && ballCollideWithPaddle(bp, p2)) {
        // collision
        // compute collision response here ?
        /*vec2f norm = angleToVec(player.angle);
        vec2f incidence = ball.vector;
        float x = vec2f::dot(norm, incidence);

        vec2f reflect = incidence - (2 * (incidence - (x * norm)));
        collision_response = -reflect;*/
    } else if (bc->last_hit_by == players::p2 && ballCollideWithPaddle(bp, p1)) {
        // collision
    }
}

const string& CollisionSystem::getName() {
    return name;
}

bool CollisionSystem::collideWithArc(CPosition* ballPos, COngPlayer* player) {
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

bool CollisionSystem::ballCollideWithPaddle(CPosition* ballPos, COngPlayer* player) {
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

const string& KineticSystem::getName() {
    return name;
}