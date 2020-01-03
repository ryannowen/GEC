#include "Controller_Slime.h"

#include "Slime.h"
#include "World.h"

void Controller_Slime::Update(Entity& argEntity, const unsigned int argPlayerID)
{
	Slime* slime = static_cast<Slime*>(&argEntity);

	const std::shared_ptr<Entity> player{ WORLD.GetPlayer() };

	Vector2<float> dir{ player->currentPosition - slime->currentPosition };


	if (dir.Dot() > 32 && !slime->isCharging && !slime->isAttacking)
	{
		UpdateAnimDir(EAction::eMoveRight, EAction::eMoveLeft);
	}
	else if (slime->canAttack && !slime->isAttacking)
	{
		slime->isAttacking = true;
		slime->canAttack = false;
		slime->SetDamage(1);
		UpdateAnimDir(EAction::eAttackRight, EAction::eAttackLeft);
	}
	else if (!slime->isAttacking)
	{
		UpdateAnimDir(EAction::eIdleRight, EAction::eIdleLeft);
	}
	
}
