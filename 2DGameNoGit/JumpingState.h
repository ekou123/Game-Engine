#include "State.h"
#include "Player.h"
#include "StateMachine.h"
#include "GravityComponent.h"

class Player;

class JumpingState : public State {
public:
    JumpingState(Player* player, StateMachine* stateMachine)
        : State(player , stateMachine),
        jumpSpeed(std::sqrt(2.0f * player->getComponent<GravityComponent>()->getGravity() * desiredJumpHeight))
    {}

    void enter() override;

    void handleInput(const bool* ks, float) override;

    void update(float dt) override;

    void exit() override;

private:
    static constexpr float desiredJumpHeight = 100.0f; // pixels
    float jumpSpeed;   // computed from desiredJumpHeight
    float vy = 0.0f;
    bool isGrounded = true;
};