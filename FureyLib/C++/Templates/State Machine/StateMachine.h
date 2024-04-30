
// Template State Machine Script
// by Kyle Furey

#pragma once

// Include this heading to use the class
#include "StateMachine.h"

// INCLUDE YOUR STATE HEADERS AT THE BOTTOM OF THIS SCRIPT!

// Forward declaration of state machine
class state_machine;

// The base class for each state. All states should inherit from this class.
class state_base
{
protected:

	// The inherited state machine from the owner
	state_machine* my_state_machine = nullptr;

public:

	// Called when this state is set as the state machine's current state
	virtual void on_state_enter()
	{
		// Note: Logic applies to all inherited states
	}

	// Called when this state machine's current state is no longer this state
	virtual void on_state_exit()
	{
		// Note: Logic applies to all inherited states
	}

	// Called every frame while this state is the state machine's current state
	virtual void state_update()
	{
		// Note: Logic applies to all inherited states
	}
};

// Base for building an state machine.
class state_machine
{
public:

	// The current state of this state machine
	state_base* current_state = nullptr;

	// Starting state constructor
	state_machine(state_base* new_state = nullptr)
	{
		start(new_state);
	}

	// Deconstructor
	~state_machine()
	{
		delete current_state;
		current_state = nullptr;
	}

	// Properly switches the state machine's current state
	void switch_state(state_base* new_state)
	{
		// Exit the current state
		if (current_state != nullptr)
		{
			current_state->on_state_exit();
		}

		// Deallocate state memory
		delete current_state;

		// Switch the current state to the new state
		current_state = new_state;

		// Enter the new state
		if (current_state != nullptr)
		{
			current_state->on_state_enter();
		}
	}

	// Updates the current state (should be called each tick)
	void tick()
	{
		update();
	}

private:

	// Instantiates the starting state
	void start(state_base* new_state)
	{
		// Sets the current state as the starting state (should be changed from template state)
		switch_state(new_state);
	}

	// Calls the update function based on the current state
	void update()
	{
		// Call the current state's update function
		if (current_state != nullptr)
		{
			current_state->state_update();
		}
	}
};

// Include your state headers here!
#include "State.h"
