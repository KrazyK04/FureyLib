
// Delegate and Event Data Types Script
// by Kyle Furey

#pragma once
#include <vector>
#include <map>
#include <initializer_list>

// Include this heading to use the class
#include "Delegate.h"

// Define the method data type
#define METHOD(variable) void (*variable) (ParameterTypes...)

// Define the function data type
#define FUNCTION(variable) ReturnType (*variable) (ParameterTypes...)

// Wrapper class for a collection of functions.
// All stored functions must share the same parameters.
// All stored functions must return void.
template <typename ... ParameterTypes> class event
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<METHOD()> functions = std::vector<METHOD()>();

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Whether the delegate is currently invoking functions
	bool is_invoking = false;

public:

	// DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

	// Default constructor
	event()
	{
		functions = std::vector<METHOD()>();
	}

	// Function constructor
	event(METHOD(function))
	{
		this->functions = std::vector<METHOD()>();

		this->functions.push_back(function);
	}

	// Array constructor
	event(METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}
	}

	// Parameter constructor
	event(int number_of_functions,
		METHOD(function1) = nullptr, METHOD(function2) = nullptr, METHOD(function3) = nullptr, METHOD(function4) = nullptr,
		METHOD(function5) = nullptr, METHOD(function6) = nullptr, METHOD(function7) = nullptr, METHOD(function8) = nullptr,
		METHOD(function9) = nullptr, METHOD(function10) = nullptr, METHOD(function11) = nullptr, METHOD(function12) = nullptr,
		METHOD(function13) = nullptr, METHOD(function14) = nullptr, METHOD(function15) = nullptr, METHOD(function16) = nullptr)
	{
		this->functions = std::vector<METHOD()>();

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
	event(std::vector<METHOD()> functions)
	{
		functions = functions;
	}

	// List constructor
	event(const std::initializer_list<METHOD()> functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}
	}

	// Delegate constructor
	event(event<ParameterTypes...>& functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool invoke(ParameterTypes... parameters)
	{
		cancel_invoke = false;

		is_invoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancel_invoke)
			{
				is_invoking = false;

				return false;
			}
		}

		is_invoking = false;

		return true;
	}

	// Cancel an invoke
	void cancel()
	{
		cancel_invoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool is_invoking()
	{
		return is_invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	event<ParameterTypes...>& set(int index, METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	event<ParameterTypes...>& add(METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	event<ParameterTypes...>& add(int number_of_functions, METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	event<ParameterTypes...>& add(std::vector<METHOD()> functions)
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
	event<ParameterTypes...>& remove(METHOD(function))
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
	bool contains(METHOD(function))
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
	int find(METHOD(function))
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
	event<ParameterTypes...>& operator+(METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	event<ParameterTypes...>& operator+=(METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	event<ParameterTypes...>& operator-(METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	event<ParameterTypes...>& operator-=(METHOD(function))
	{
		return remove(function);
	}
};

// Wrapper class for a collection of functions.
// All stored functions must share the same parameters.
// All stored functions must share the same return type.
template <typename ReturnType, typename ... ParameterTypes> class delegate
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<FUNCTION()> functions = std::vector<FUNCTION()>();

	// Delegate cancellation token
	bool cancel_invoke = false;

	// Whether the delegate is currently invoking functions
	bool is_invoking = false;

public:

	// DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

	// Default constructor
	delegate()
	{
		functions = std::vector<FUNCTION()>();
	}

	// Function constructor
	delegate(FUNCTION(function))
	{
		this->functions = std::vector<FUNCTION()>();

		this->functions.push_back(function);
	}

	// Array constructor
	delegate(FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}
	}

	// Parameter constructor
	delegate(int number_of_functions,
		FUNCTION(function1) = nullptr, FUNCTION(function2) = nullptr, FUNCTION(function3) = nullptr, FUNCTION(function4) = nullptr,
		FUNCTION(function5) = nullptr, FUNCTION(function6) = nullptr, FUNCTION(function7) = nullptr, FUNCTION(function8) = nullptr,
		FUNCTION(function9) = nullptr, FUNCTION(function10) = nullptr, FUNCTION(function11) = nullptr, FUNCTION(function12) = nullptr,
		FUNCTION(function13) = nullptr, FUNCTION(function14) = nullptr, FUNCTION(function15) = nullptr, FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<FUNCTION()>();

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
	delegate(std::vector<FUNCTION()> functions)
	{
		functions = functions;
	}

	// List constructor
	delegate(const std::initializer_list<FUNCTION()> functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}
	}

	// Delegate constructor
	delegate(delegate<ReturnType, ParameterTypes...>& functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}
	}


	// DELEGATE FUNCTIONS

	// Returns a dictionary with each key representing the function and the value being the returned data
	std::map<FUNCTION(), ReturnType> invoke(ParameterTypes... parameters)
	{
		cancel_invoke = false;

		is_invoking = true;

		std::map<FUNCTION(), ReturnType> returns = std::map<FUNCTION(), ReturnType>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancel_invoke)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = ReturnType();
				}

				break;
			}
		}

		is_invoking = false;

		return returns;
	}

	// Cancel an invoke
	void cancel()
	{
		cancel_invoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool is_invoking()
	{
		return is_invoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	delegate<ReturnType, ParameterTypes...>& set(int index, FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	delegate<ReturnType, ParameterTypes...>& add(FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	delegate<ReturnType, ParameterTypes...>& add(int number_of_functions, FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	delegate<ReturnType, ParameterTypes...>& add(std::vector<FUNCTION()> functions)
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
	delegate<ReturnType, ParameterTypes...>& remove(FUNCTION(function))
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
	bool contains(FUNCTION(function))
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
	int find(FUNCTION(function))
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
	delegate<ReturnType, ParameterTypes...>& operator+(FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	delegate<ReturnType, ParameterTypes...>& operator+=(FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	delegate<ReturnType, ParameterTypes...>& operator-(FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	delegate<ReturnType, ParameterTypes...>& operator-=(FUNCTION(function))
	{
		return remove(function);
	}
};

// Wrapper class for a collection of functions.
// All stored functions must share the same parameters.
// All stored functions must return void.
template <typename ... ParameterTypes> class Event
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<METHOD()> functions = std::vector<METHOD()>();

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Whether the delegate is currently invoking functions
	bool isInvoking = false;

public:

	// DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

	// Default constructor
	Event()
	{
		functions = std::vector<METHOD()>();
	}

	// Function constructor
	Event(METHOD(function))
	{
		this->functions = std::vector<METHOD()>();

		this->functions.push_back(function);
	}

	// Array constructor
	Event(METHOD(functions[]), int number_of_functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}
	}

	// Parameter constructor
	Event(int number_of_functions,
		METHOD(function1) = nullptr, METHOD(function2) = nullptr, METHOD(function3) = nullptr, METHOD(function4) = nullptr,
		METHOD(function5) = nullptr, METHOD(function6) = nullptr, METHOD(function7) = nullptr, METHOD(function8) = nullptr,
		METHOD(function9) = nullptr, METHOD(function10) = nullptr, METHOD(function11) = nullptr, METHOD(function12) = nullptr,
		METHOD(function13) = nullptr, METHOD(function14) = nullptr, METHOD(function15) = nullptr, METHOD(function16) = nullptr)
	{
		this->functions = std::vector<METHOD()>();

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
	Event(std::vector<METHOD()> functions)
	{
		functions = functions;
	}

	// List constructor
	Event(const std::initializer_list<METHOD()> functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}
	}

	// Delegate constructor
	Event(Event<ParameterTypes...>& functions)
	{
		this->functions = std::vector<METHOD()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}
	}


	// DELEGATE FUNCTIONS

	// Call each function in the delegate and return if the invoke was successful
	bool Invoke(ParameterTypes... parameters)
	{
		cancelInvoke = false;

		isInvoking = true;

		for (int i = 0; i < functions.size(); i++)
		{
			functions[i](parameters...);

			if (cancelInvoke)
			{
				isInvoking = false;

				return false;
			}
		}

		isInvoking = false;

		return true;
	}

	// Cancel an invoke
	void Cancel()
	{
		cancelInvoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool IsInvoking()
	{
		return isInvoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto Get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	Event<ParameterTypes...>& Set(int index, METHOD(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	Event<ParameterTypes...>& Add(METHOD(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	Event<ParameterTypes...>& Add(int number_of_functions, METHOD(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	Event<ParameterTypes...>& Add(std::vector<METHOD()> functions)
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
	Event<ParameterTypes...>& Remove(METHOD(function))
	{
		functions.erase(std::find(functions.begin(), functions.end(), function));

		return *this;
	}

	// Remove a delegate from the delegate
	Event<ParameterTypes...>& Remove(Event<ParameterTypes...>& functions)
	{
		for (int i = 0; i < functions.Count(); i++)
		{
			this->functions.erase(std::find(this->functions.begin(), this->functions.end(), functions[i]));
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
	bool Contains(METHOD(function))
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
	int Find(METHOD(function))
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
	Event<ParameterTypes...>& operator+(METHOD(function))
	{
		return add(function);
	}

	// Adding a function
	Event<ParameterTypes...>& operator+=(METHOD(function))
	{
		return add(function);
	}

	// Removing a function
	Event<ParameterTypes...>& operator-(METHOD(function))
	{
		return remove(function);
	}

	// Removing a function
	Event<ParameterTypes...>& operator-=(METHOD(function))
	{
		return remove(function);
	}
};

// Wrapper class for a collection of functions.
// All stored functions must share the same parameters.
// All stored functions must share the same return type.
template <typename ReturnType, typename ... ParameterTypes> class Delegate
{
private:

	// DELEGATE DATA

	// List of functions included in the delegate
	std::vector<FUNCTION()> functions = std::vector<FUNCTION()>();

	// Delegate cancellation token
	bool cancelInvoke = false;

	// Whether the delegate is currently invoking functions
	bool isInvoking = false;

public:

	// DELEGATE CONSTRUCTOR AND DECONSTRUCTOR

	// Default constructor
	Delegate()
	{
		functions = std::vector<FUNCTION()>();
	}

	// Function constructor
	Delegate(FUNCTION(function))
	{
		this->functions = std::vector<FUNCTION()>();

		this->functions.push_back(function);
	}

	// Array constructor
	Delegate(FUNCTION(functions[]), int number_of_functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}
	}

	// Parameter constructor
	Delegate(int number_of_functions,
		FUNCTION(function1) = nullptr, FUNCTION(function2) = nullptr, FUNCTION(function3) = nullptr, FUNCTION(function4) = nullptr,
		FUNCTION(function5) = nullptr, FUNCTION(function6) = nullptr, FUNCTION(function7) = nullptr, FUNCTION(function8) = nullptr,
		FUNCTION(function9) = nullptr, FUNCTION(function10) = nullptr, FUNCTION(function11) = nullptr, FUNCTION(function12) = nullptr,
		FUNCTION(function13) = nullptr, FUNCTION(function14) = nullptr, FUNCTION(function15) = nullptr, FUNCTION(function16) = nullptr)
	{
		this->functions = std::vector<FUNCTION()>();

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
	Delegate(std::vector<FUNCTION()> functions)
	{
		functions = functions;
	}

	// List constructor
	Delegate(const std::initializer_list<FUNCTION()> functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.size(); i++)
		{
			this->functions.push_back(*(functions.begin() + i));
		}
	}

	// Delegate constructor
	Delegate(Delegate<ReturnType, ParameterTypes...>& functions)
	{
		this->functions = std::vector<FUNCTION()>();

		for (int i = 0; i < functions.count(); i++)
		{
			this->functions.push_back(functions[i]);
		}
	}


	// DELEGATE FUNCTIONS

	// Returns a dictionary with each key representing the function and the value being the returned data
	std::map<FUNCTION(), ReturnType> Invoke(ParameterTypes... parameters)
	{
		cancelInvoke = false;

		isInvoking = true;

		std::map<FUNCTION(), ReturnType> returns = std::map<FUNCTION(), ReturnType>();

		for (int i = 0; i < functions.size(); i++)
		{
			returns[functions[i]] = functions[i](parameters...);

			if (cancelInvoke)
			{
				for (int j = i + 1; j < functions.size(); j++)
				{
					returns[functions[i]] = ReturnType();
				}

				break;
			}
		}

		isInvoking = false;

		return returns;
	}

	// Cancel an invoke
	void Cancel()
	{
		cancelInvoke = true;
	}

	// Returns whether the delegate is currently being invoked
	bool IsInvoking()
	{
		return isInvoking;
	}


	// COLLECTION FUNCTIONS

	// Gets a function in the delegate
	auto Get(int index)
	{
		return functions[index];
	}

	// Sets a function in the delegate
	Delegate<ReturnType, ParameterTypes...>& Set(int index, FUNCTION(function))
	{
		functions[index] = function;

		return *this;
	}

	// Add a new function to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(FUNCTION(function))
	{
		functions.push_back(function);

		return *this;
	}

	// Adds new functions to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(int number_of_functions, FUNCTION(functions[]))
	{
		for (int i = 0; i < number_of_functions; i++)
		{
			this->functions.push_back(functions[i]);
		}

		return *this;
	}

	// Adds new functions to the delegate
	Delegate<ReturnType, ParameterTypes...>& Add(std::vector<FUNCTION()> functions)
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
	Delegate<ReturnType, ParameterTypes...>& Remove(FUNCTION(function))
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
	bool Contains(FUNCTION(function))
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
	int Find(FUNCTION(function))
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
	Delegate<ReturnType, ParameterTypes...>& operator+(FUNCTION(function))
	{
		return add(function);
	}

	// Adding a function
	Delegate<ReturnType, ParameterTypes...>& operator+=(FUNCTION(function))
	{
		return add(function);
	}

	// Removing a function
	Delegate<ReturnType, ParameterTypes...>& operator-(FUNCTION(function))
	{
		return remove(function);
	}

	// Removing a function
	Delegate<ReturnType, ParameterTypes...>& operator-=(FUNCTION(function))
	{
		return remove(function);
	}
};
