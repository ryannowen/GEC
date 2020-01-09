#pragma once

// Include the HAPI header to get access to all of HAPIs interfaces
// HAPI itself is wrapped in the HAPISPACE namespace
#include <HAPI_lib.h>
using namespace HAPISPACE;

#include "Vector2.h"
#include <vector>

class Entity;

// Type of action the controller is currently doing
enum class EAction
{
	eIdleRight,
	eIdleLeft,
	eMoveRight,
	eMoveLeft,
	eAttackRight,
	eAttackLeft
};

// Side of controller
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

	// Overridable update for each controller
	virtual void Update(Entity& argEntity, const unsigned int argPlayerID);

	void UpdateAnimDir(const EAction argRightAction, const EAction argLeftAction);
	// Returns true if right, false if left
	bool GetFacingDirection() const;

	// Swaps keyboard and controller input with other controller
	void SwapInput(Controller& argController);

	// Changes keyboard input to given input
	void SetKeyboardInput(const std::vector<int>& argKeyboardInput);
	// Changes controller input to given input
	void SetControllerInput(const std::vector<int>& argControllerInput);

	// Sets side of controller
	void SetSide(const ESide argSide) { controllerSide = argSide; };
	// Sets current action of controller
	void SetAction(const EAction argAction) { controllerAction = argAction; };

	// Gets the current movement direction of controller using player input
	Vector2<float> GetMovementDirection(const unsigned int argPlayerID) const;
	// Gets if player is jumping
	bool GetIsJumping(const unsigned int argPlayerID);

	// Returns side of controller
	ESide GetSide() const { return controllerSide; };
	// Returns action of controller
	EAction GetAction() const { return controllerAction; };
};

