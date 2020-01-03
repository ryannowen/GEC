#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include "Vector2.h"
#include <vector>

class Entity;

enum class EAction
{
	eIdleRight,
	eIdleLeft,
	eMoveRight,
	eMoveLeft,
	eAttackRight,
	eAttackLeft
};

enum class ESide
{
	ePlayerCharacter,
	ePlayerBoss,
	eNeutral,
	eEnvironment
};

class Controller
{
protected:
	/// Keyboard Input - Up, Down, Right, Left, Jump, Action
	std::vector<int> keyboardInput;
	/// Controller Input - Y, X, Jump, Action
	std::vector<int> controllerInput;

	ESide controllerSide{ ESide::eNeutral };
	EAction controllerAction{ EAction::eIdleRight };

public:
	Controller(const std::vector<int>& argKeyboardInput = std::vector<int>(), const std::vector<int>& argControllerInput = std::vector<int>());

	virtual void Update(Entity& argEntity, const unsigned int argPlayerID);

	void UpdateAnimDir(const EAction argRightAction, const EAction argLeftAction);
	// Returns true if right, false if left
	bool GetFacingDirection() const;

	void SetKeyboardInput(const std::vector<int>& argKeyboardInput);
	void SetControllerInput(const std::vector<int>& argControllerInput);

	void SetSide(const ESide argSide) { controllerSide = argSide; };
	void SetAction(const EAction argAction) { controllerAction = argAction; };


	Vector2<float> GetMovementDirection(const unsigned int argPlayerID) const;
	bool isJumping(const unsigned int argPlayerID);

	ESide GetSide() const { return controllerSide; };
	EAction GetAction() const { return controllerAction; };
};

