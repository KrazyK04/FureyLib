
// Delegate and Event Data Types Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <initializer_list>

// Include this heading to use the class
#include "Delegate.h"

// Define the method data type
#define _METHOD(variable) void (*variable) (ParameterTypes...)

// Define the function data type
#define _FUNCTION(variable) ReturnType (*variable) (ParameterTypes...)


// Forward declaration of event
template <typename ... ParameterTypes> class event;

// Forward declaration of delegate
template  <typename ReturnType, typename ... ParameterTypes> class delegate;

// Wrapper class for a collection of functions.
// All stored functions must return void.
// All stored functions must share the same parameters.
template <typename ... ParameterTypes> class event
{
private:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<event<ParameterTypes...>*> all_delegates;

	// Global cancellation token
	static bool cancelled_all;

	// Index of current invoked delegate
	static int invoke_index;


	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<_METHOD()> functions = std::vector<_METHOD()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Index of current delegate
	int index = 0;


public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	event()
	{
		functions = std::vector<_METHOD()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Function constructor
	event(_METHOD(function))
	{
		this->functions = std::vector<_METHOD()>();

		this->functions.push_back(function);

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Array constructor
	event(_METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<_METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Parameter constructor
	event(int number_of_functions,
		_METHOD(function1) = nullptr, _METHOD(function2) = nullptr, _METHOD(function3) = nullptr, _METHOD(function4) = nullptr,
		_METHOD(function5) = nullptr, _METHOD(function6) = nullptr, _METHOD(function7) = nullptr, _METHOD(function8) = nullptr,
		_METHOD(function9) = nullptr, _METHOD(function10) = nullptr, _METHOD(function11) = nullptr, _METHOD(function12) = nullptr,
		_METHOD(function13) = nullptr, _METHOD(function14) = nullptr, _METHOD(function15) = nullptr, _METHOD(function16) = nullptr)
	{
		this->functions = std::vector<_METHOD()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	event(std::vector<_METHOD()> functions)
	{
		functions = functions;

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// List constructor
	event(const std::initializer_list<_METHOD()> functions)
	{
		this->functions = std::vector<_METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Delegate constructor
	event(event<ParameterTypes...>& functions)
	{
		this->functions = std::vector<_METHOD()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Deconstructor
	~event()
	{
		for (int i = index + 1; i < all_delegates.size(); i++)
		{
			all_delegates[i]->index--;
		}

		all_delegates.erase(std::find(all_delegates.begin(), all_delegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool invoke(ParameterTypes... parameters)
	{
		cancel_invoke = false;

		cancelled_all = false;

		invoke_index = index;

		invoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancel_invoke || cancelled_all)
			{
				invoking = false;

				return false;
			}
		}

		invoking = false;

		return true;
	}

	// Invokes every delegate
	static bool invoke_all(ParameterTypes... parameters)
	{
		for (int i = 0; i < all_delegates.size(); i++)
		{
			if (!all_delegates[i]->invoke(parameters...))
			{
				return false;
			}
		}

		return true;
	}

	// Reinvokes the current delegate
	static bool invoke_current(ParameterTypes... parameters)
	{
		return all_delegates[invoke_index]->invoke(parameters...);
	}

	// Cancel an invoke
	void cancel()
	{
		cancel_invoke = true;
	}

	// Cancel all invokes
	static void cancel_all()
	{
		cancelled_all = true;
	}

	// Cancel the current invoke
	static void cancel_current()
	{
		all_delegates[invoke_index]->cancel_invoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool is_invoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	event<ParameterTypes...>& set(int index, _METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	event<ParameterTypes...>& add(_METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	event<ParameterTypes...>& add(int number_of_functions, _METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	event<ParameterTypes...>& add(std::vector<_METHOD()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	event<ParameterTypes...>& add(event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	event<ParameterTypes...>& remove(_METHOD(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	event<ParameterTypes...>& remove(event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	event<ParameterTypes...>& remove_at(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	event<ParameterTypes...>& clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool contains(_METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int find(_METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto to_new_array()
	{
		auto functions = new void[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto to_vector()
	{
		return functions;
	}


	// COLLECTION OPERATORS

	// Adding a function
	event<ParameterTypes...>& operator+(_METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	event<ParameterTypes...>& operator+=(_METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	event<ParameterTypes...>& operator-(_METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	event<ParameterTypes...>& operator-=(_METHOD(function))
	{
		return remove(function);
	}
};

// Static variable initialization
template <typename ... ParameterTypes> std::vector<event<ParameterTypes...>*> event<ParameterTypes...>::all_delegates = std::vector<event<ParameterTypes...>*>();
template <typename ... ParameterTypes> bool event<ParameterTypes...>::cancelled_all = false;
template <typename ... ParameterTypes> int event<ParameterTypes...>::invoke_index = 0;

// Wrapper class for a collection of functions.
// All stored functions must share the same return type.
// All stored functions must share the same parameters.
template <typename ReturnType, typename ... ParameterTypes> class delegate
{
private:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<delegate<ReturnType, ParameterTypes...>*> all_delegates;

	// Global cancellation token
	static bool cancelled_all;

	// Index of current invoked delegate
	static int invoke_index;


	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<_FUNCTION()> functions = std::vector<_FUNCTION()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Index of current delegate
	int index = 0;

public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	delegate()
	{
		functions = std::vector<_FUNCTION()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Function constructor
	delegate(_FUNCTION(function))
	{
		this->functions = std::vector<_FUNCTION()>();

		this->functions.push_back(function);

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Array constructor
	delegate(_FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<_FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Parameter constructor
	delegate(int number_of_functions,
		_FUNCTION(function1) = nullptr, _FUNCTION(function2) = nullptr, _FUNCTION(function3) = nullptr, _FUNCTION(function4) = nullptr,
		_FUNCTION(function5) = nullptr, _FUNCTION(function6) = nullptr, _FUNCTION(function7) = nullptr, _FUNCTION(function8) = nullptr,
		_FUNCTION(function9) = nullptr, _FUNCTION(function10) = nullptr, _FUNCTION(function11) = nullptr, _FUNCTION(function12) = nullptr,
		_FUNCTION(function13) = nullptr, _FUNCTION(function14) = nullptr, _FUNCTION(function15) = nullptr, _FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<_FUNCTION()>();

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	delegate(std::vector<_FUNCTION()> functions)
	{
		functions = functions;

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// List constructor
	delegate(const std::initializer_list<_FUNCTION()> functions)
	{
		this->functions = std::vector<_FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Delegate constructor
	delegate(delegate<ReturnType, ParameterTypes...>& functions)
	{
		this->functions = std::vector<_FUNCTION()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		all_delegates.push_back(this);

		index = all_delegates.size() - 1;
	}

	// Deconstructor
	~delegate()
	{
		for (int i = index + 1; i < all_delegates.size(); i++)
		{
			all_delegates[i]->index--;
		}

		all_delegates.erase(std::find(all_delegates.begin(), all_delegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Returns a dictionary with each key representing the function and the value being the returned data
	std::map<_FUNCTION(), ReturnType> invoke(ParameterTypes... parameters)
	{
		cancel_invoke = false;

		cancelled_all = false;

		invoke_index = index;

		invoking = true;

		std::map<_FUNCTION(), ReturnType> returns = std::map<_FUNCTION(), ReturnType>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancel_invoke || cancelled_all)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = ReturnType();
				}

				break;
			}
		}

		invoking = false;

		return returns;
	}

	// Invokes every delegate
	static auto invoke_all(ParameterTypes... parameters)
	{
		auto returns = std::map<delegate<ReturnType, ParameterTypes...>*, std::map<_FUNCTION(), ReturnType>>();

		for (int i = 0; i < all_delegates.size(); i++)
		{
			returns[all_delegates[i]] = all_delegates[i]->invoke(parameters...);

			if (all_delegates[i]->cancel_invoke || cancelled_all)
			{
				break;
			}
		}

		return returns;
	}

	// Reinvokes the current delegate
	static std::map<_FUNCTION(), ReturnType> invoke_current(ParameterTypes... parameters)
	{
		return all_delegates[invoke_index]->invoke(parameters...);
	}

	// Cancel an invoke
	void cancel()
	{
		cancel_invoke = true;
	}

	// Cancel all invokes
	static void cancel_all()
	{
		cancelled_all = true;
	}

	// Cancel the current invoke
	static void cancel_current()
	{
		all_delegates[invoke_index]->cancel_invoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool is_invoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	delegate<ReturnType, ParameterTypes...>& set(int index, _FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	delegate<ReturnType, ParameterTypes...>& add(_FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	delegate<ReturnType, ParameterTypes...>& add(int number_of_functions, _FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	delegate<ReturnType, ParameterTypes...>& add(std::vector<_FUNCTION()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	delegate<ReturnType, ParameterTypes...>& add(delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	delegate<ReturnType, ParameterTypes...>& remove(_FUNCTION(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	delegate<ReturnType, ParameterTypes...>& remove(delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	delegate<ReturnType, ParameterTypes...>& remove_at(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	delegate<ReturnType, ParameterTypes...>& clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool contains(_FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int find(_FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto to_new_array()
	{
		auto functions = new ReturnType[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto to_vector()
	{
		return functions;
	}


	// COLLECTION OPERATORS

	// Adding a function
	delegate<ReturnType, ParameterTypes...>& operator+(_FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	delegate<ReturnType, ParameterTypes...>& operator+=(_FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	delegate<ReturnType, ParameterTypes...>& operator-(_FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	delegate<ReturnType, ParameterTypes...>& operator-=(_FUNCTION(function))
	{
		return remove(function);
	}
};

// Static variable initialization
template <typename ReturnType, typename ... ParameterTypes> std::vector<delegate<ReturnType, ParameterTypes...>*> delegate<ReturnType, ParameterTypes...>::all_delegates = std::vector<delegate<ReturnType, ParameterTypes...>*>();
template <typename ReturnType, typename ... ParameterTypes> bool delegate<ReturnType, ParameterTypes...>::cancelled_all = false;
template <typename ReturnType, typename ... ParameterTypes> int delegate<ReturnType, ParameterTypes...>::invoke_index = 0;

// Forward declaration of event
template <typename ... ParameterTypes> class Event;

// Forward declaration of delegate
template  <typename ReturnType, typename ... ParameterTypes> class Delegate;

// Wrapper class for a collection of functions.
// All stored functions must return void.
// All stored functions must share the same parameters.
template <typename ... ParameterTypes> class Event
{
private:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<Event<ParameterTypes...>*> allDelegates;

	// Global cancellation token
	static bool cancelledAll;

	// Index of current invoked delegate
	static int invokeIndex;


	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<_METHOD()> functions = std::vector<_METHOD()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Index of current delegate
	int index = 0;


public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Event()
	{
		functions = std::vector<_METHOD()>();

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Function constructor
	Event(_METHOD(function))
	{
		this->functions = std::vector<_METHOD()>();

		this->functions.push_back(function);

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Array constructor
	Event(_METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<_METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Parameter constructor
	Event(int number_of_functions,
		_METHOD(function1) = nullptr, _METHOD(function2) = nullptr, _METHOD(function3) = nullptr, _METHOD(function4) = nullptr,
		_METHOD(function5) = nullptr, _METHOD(function6) = nullptr, _METHOD(function7) = nullptr, _METHOD(function8) = nullptr,
		_METHOD(function9) = nullptr, _METHOD(function10) = nullptr, _METHOD(function11) = nullptr, _METHOD(function12) = nullptr,
		_METHOD(function13) = nullptr, _METHOD(function14) = nullptr, _METHOD(function15) = nullptr, _METHOD(function16) = nullptr)
	{
		this->functions = std::vector<_METHOD()>();

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	Event(std::vector<_METHOD()> functions)
	{
		functions = functions;

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// List constructor
	Event(const std::initializer_list<_METHOD()> functions)
	{
		this->functions = std::vector<_METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Delegate constructor
	Event(Event<ParameterTypes...>& functions)
	{
		this->functions = std::vector<_METHOD()>();

		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Deconstructor
	~Event()
	{
		for (int i = index + 1; i < allDelegates.size(); i++)
		{
			allDelegates[i]->index--;
		}

		allDelegates.erase(std::find(allDelegates.begin(), allDelegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool Invoke(ParameterTypes... parameters)
	{
		cancelInvoke = false;

		cancelledAll = false;

		invokeIndex = index;

		invoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancelInvoke || cancelledAll)
			{
				invoking = false;

				return false;
			}
		}

		invoking = false;

		return true;
	}

	// Invokes every delegate
	static bool InvokeAll(ParameterTypes... parameters)
	{
		for (int i = 0; i < allDelegates.size(); i++)
		{
			if (!allDelegates[i]->Invoke(parameters...))
			{
				return false;
			}
		}

		return true;
	}

	// Reinvokes the current delegate
	static bool InvokeCurrent(ParameterTypes... parameters)
	{
		return allDelegates[invokeIndex]->invoke(parameters...);
	}

	// Cancel an invoke
	void Cancel()
	{
		cancelInvoke = true;
	}

	// Cancel all invokes
	static void CancelAll()
	{
		cancelledAll = true;
	}

	// Cancel the current invoke
	static void CancelCurrent()
	{
		allDelegates[invokeIndex]->cancelInvoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool IsInvoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto Get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	Event<ParameterTypes...>& Set(int index, _METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	Event<ParameterTypes...>& Add(_METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	Event<ParameterTypes...>& Add(int number_of_functions, _METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	Event<ParameterTypes...>& Add(std::vector<_METHOD()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	Event<ParameterTypes...>& Add(Event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	Event<ParameterTypes...>& Remove(_METHOD(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	Event<ParameterTypes...>& Remove(Event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	Event<ParameterTypes...>& RemoveAt(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	Event<ParameterTypes...>& Clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int Count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool Contains(_METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int Find(_METHOD(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto ToNewArray()
	{
		auto functions = new void[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto ToVector()
	{
		return functions;
	}


	// COLLECTION OPERATORS

	// Adding a function
	Event<ParameterTypes...>& operator+(_METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	Event<ParameterTypes...>& operator+=(_METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	Event<ParameterTypes...>& operator-(_METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	Event<ParameterTypes...>& operator-=(_METHOD(function))
	{
		return remove(function);
	}
};

// Static variable initialization
template <typename ... ParameterTypes> std::vector<Event<ParameterTypes...>*> Event<ParameterTypes...>::allDelegates = std::vector<Event<ParameterTypes...>*>();
template <typename ... ParameterTypes> bool Event<ParameterTypes...>::cancelledAll = false;
template <typename ... ParameterTypes> int Event<ParameterTypes...>::invokeIndex = 0;

// Wrapper class for a collection of functions.
// All stored functions must share the same return type.
// All stored functions must share the same parameters.
template <typename ReturnType, typename ... ParameterTypes> class Delegate
{
private:

	// STATIC DELEGATE DATA

	// Global list of all delegates
	static std::vector<Delegate<ReturnType, ParameterTypes...>*> allDelegates;

	// Global cancellation token
	static bool cancelledAll;

	// Index of current invoked delegate
	static int invokeIndex;


	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<_FUNCTION()> functions = std::vector<_FUNCTION()>();

	// Whether the delegate is currently invoking functions
	bool invoking = false;

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Index of current delegate
	int index = 0;

public:

	// DELEGATE CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	Delegate()
	{
		functions = std::vector<_FUNCTION()>();

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Function constructor
	Delegate(_FUNCTION(function))
	{
		this->functions = std::vector<_FUNCTION()>();

		this->functions.push_back(function);

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Array constructor
	Delegate(_FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<_FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Parameter constructor
	Delegate(int number_of_functions,
		_FUNCTION(function1) = nullptr, _FUNCTION(function2) = nullptr, _FUNCTION(function3) = nullptr, _FUNCTION(function4) = nullptr,
		_FUNCTION(function5) = nullptr, _FUNCTION(function6) = nullptr, _FUNCTION(function7) = nullptr, _FUNCTION(function8) = nullptr,
		_FUNCTION(function9) = nullptr, _FUNCTION(function10) = nullptr, _FUNCTION(function11) = nullptr, _FUNCTION(function12) = nullptr,
		_FUNCTION(function13) = nullptr, _FUNCTION(function14) = nullptr, _FUNCTION(function15) = nullptr, _FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<_FUNCTION()>();

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;

		if (number_of_functions >= 1) {
			this->functions.push_back(function1);
		}
		else {
			return;
		}

		if (number_of_functions >= 2) {
			this->functions.push_back(function2);
		}
		else {
			return;
		}

		if (number_of_functions >= 3) {
			this->functions.push_back(function3);
		}
		else {
			return;
		}

		if (number_of_functions >= 4) {
			this->functions.push_back(function4);
		}
		else {
			return;
		}

		if (number_of_functions >= 5) {
			this->functions.push_back(function5);
		}
		else {
			return;
		}

		if (number_of_functions >= 6) {
			this->functions.push_back(function6);
		}
		else {
			return;
		}

		if (number_of_functions >= 7) {
			this->functions.push_back(function7);
		}
		else {
			return;
		}

		if (number_of_functions >= 8) {
			this->functions.push_back(function8);
		}
		else {
			return;
		}

		if (number_of_functions >= 9) {
			this->functions.push_back(function9);
		}
		else {
			return;
		}

		if (number_of_functions >= 10) {
			this->functions.push_back(function10);
		}
		else {
			return;
		}

		if (number_of_functions >= 11) {
			this->functions.push_back(function11);
		}
		else {
			return;
		}

		if (number_of_functions >= 12) {
			this->functions.push_back(function12);
		}
		else {
			return;
		}

		if (number_of_functions >= 13) {
			this->functions.push_back(function13);
		}
		else {
			return;
		}

		if (number_of_functions >= 14) {
			this->functions.push_back(function14);
		}
		else {
			return;
		}

		if (number_of_functions >= 15) {
			this->functions.push_back(function15);
		}
		else {
			return;
		}

		if (number_of_functions >= 16) {
			this->functions.push_back(function16);
		}
		else {
			return;
		}
	}

	// Vector constructor
	Delegate(std::vector<_FUNCTION()> functions)
	{
		functions = functions;

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// List constructor
	Delegate(const std::initializer_list<_FUNCTION()> functions)
	{
		this->functions = std::vector<_FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Delegate constructor
	Delegate(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		this->functions = std::vector<_FUNCTION()>();

		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		allDelegates.push_back(this);

		index = allDelegates.size() - 1;
	}

	// Deconstructor
	~Delegate()
	{
		for (int i = index + 1; i < allDelegates.size(); i++)
		{
			allDelegates[i]->index--;
		}

		allDelegates.erase(std::find(allDelegates.begin(), allDelegates.end(), this));
	}


	// DELEGATE FUNCTIONS

	// Returns a dictionary with each key representing the function and the value being the returned data
	std::map<_FUNCTION(), ReturnType> Invoke(ParameterTypes... parameters)
	{
		cancelInvoke = false;

		cancelledAll = false;

		invokeIndex = index;

		invoking = true;

		std::map<_FUNCTION(), ReturnType> returns = std::map<_FUNCTION(), ReturnType>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancelInvoke || cancelledAll)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = ReturnType();
				}

				break;
			}
		}

		invoking = false;

		return returns;
	}

	// Invokes every delegate
	static auto InvokeAll(ParameterTypes... parameters)
	{
		auto returns = std::map<Delegate<ReturnType, ParameterTypes...>*, std::map<_FUNCTION(), ReturnType>>();

		for (int i = 0; i < allDelegates.size(); i++)
		{
			returns[allDelegates[i]] = allDelegates[i]->Invoke(parameters...);

			if (allDelegates[i]->cancelInvoke || cancelledAll)
			{
				break;
			}
		}

		return returns;
	}

	// Reinvokes the current delegate
	static std::map<_FUNCTION(), ReturnType> InvokeCurrent(ParameterTypes... parameters)
	{
		return allDelegates[invokeIndex]->invoke(parameters...);
	}

	// Cancel an invoke
	void Cancel()
	{
		cancelInvoke = true;
	}

	// Cancel all invokes
	static void CancelAll()
	{
		cancelledAll = true;
	}

	// Cancel the current invoke
	static void CancelCurrent()
	{
		allDelegates[invokeIndex]->cancelInvoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool IsInvoking()
	{
		return invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto Get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	Delegate<ReturnType, ParameterTypes...>& Set(int index, _FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(_FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(int number_of_functions, _FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(std::vector<_FUNCTION()> functions)
	{
		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Add a delegate to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Remove a function from the delegate
	Delegate<ReturnType, ParameterTypes...>& Remove(_FUNCTION(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	Delegate<ReturnType, ParameterTypes...>& Remove(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
		}

		return *this;
	}

	// Remove a function from the delegate
	Delegate<ReturnType, ParameterTypes...>& RemoveAt(int index)
	{
		functions.erase(functions.begin() + index);

		return *this;
	}

	// Clear all functions from the delegate
	Delegate<ReturnType, ParameterTypes...>& Clear()
	{
		functions.clear();

		return *this;
	}

	// Return the number of functions in the delegate
	int Count()
	{
		return functions.size();
	}

	// Returns if the delegate contains a function
	bool Contains(_FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return true;
			}
		}

		return false;
	}

	// Returns the index of the function in the delegate, or -1 if it was not found
	int Find(_FUNCTION(function))
	{
		for (int i = 0; i < functions.size(); i++)
		{
			if (functions[i] == function)
			{
				return i;
			}
		}

		return -1;
	}

	// Returns a new pointer to a new array of the current functions (must be deallocated)
	auto ToNewArray()
	{
		auto functions = new ReturnType[this->functions.size()](ParameterTypes...);

		for (int i = 0; i < this->functions.size(); i++)
		{
			functions[i] = this->functions[i];
		}

		return functions;
	}

	// Returns a vector of the functions
	auto ToVector()
	{
		return functions;
	}


	// COLLECTION OPERATORS

	// Adding a function
	Delegate<ReturnType, ParameterTypes...>& operator+(_FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	Delegate<ReturnType, ParameterTypes...>& operator+=(_FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	Delegate<ReturnType, ParameterTypes...>& operator-(_FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	Delegate<ReturnType, ParameterTypes...>& operator-=(_FUNCTION(function))
	{
		return remove(function);
	}
};

// Static variable initialization
template <typename ReturnType, typename ... ParameterTypes> std::vector<Delegate<ReturnType, ParameterTypes...>*> Delegate<ReturnType, ParameterTypes...>::allDelegates = std::vector<Delegate<ReturnType, ParameterTypes...>*>();
template <typename ReturnType, typename ... ParameterTypes> bool Delegate<ReturnType, ParameterTypes...>::cancelledAll = false;
template <typename ReturnType, typename ... ParameterTypes> int Delegate<ReturnType, ParameterTypes...>::invokeIndex = 0;
