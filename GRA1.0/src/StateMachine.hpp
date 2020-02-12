#pragma once 

#include <memory>
#include <stack>

#include "state.hpp"

namespace Bado
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine( ) { }
		~StateMachine( ) { }

		void AddState( StateRef newState, bool isReplacing = true );
	
		void ProcessStateChanges( );
	
		StateRef &GetActiveState();

	private:
		std::stack<StateRef> _states;
		StateRef _newState;

		bool _isReplacing;
		bool _isAdding;
		bool _isRemoving;

	};



}

