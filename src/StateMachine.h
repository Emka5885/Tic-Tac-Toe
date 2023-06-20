#pragma once
#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> stateReference;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void AddState(stateReference newState, bool isReplacing = true);
	void RemoveState();

	void ProcessStateChanges();

	stateReference& GetActiveState();

private:
	std::stack<stateReference> states;
	stateReference newState;

	bool isRemoving = false;
	bool isAdding = false;
	bool isReplacing = false;
};