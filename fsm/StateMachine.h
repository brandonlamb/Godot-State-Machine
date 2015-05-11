#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "scene/main/node.h"
#include "State.h"
#include "object_type_db.h"

template <class entity>
class StateMachine : public Node
{
	OBJ_TYPE(StateMachine,Node);
	
protected:
    static void _bind_methods(){
		ObjectTypeDB::bind_method(_MD("set_current_state","state"),&StateMachine::setCurrentState);
		ObjectTypeDB::bind_method(_MD("set_previous_state","state"),&StateMachine::setPreviousState);
		ObjectTypeDB::bind_method(_MD("set_global_state","state"),&StateMachine::setGlobalState);
		ObjectTypeDB::bind_method(_MD("first_enter"),&StateMachine::FirstEnter);
		ObjectTypeDB::bind_method(_MD("update","delta"),&StateMachine::Update);
		ObjectTypeDB::bind_method(_MD("change_state","newState"),&StateMachine::ChangeState);
		ObjectTypeDB::bind_method(_MD("revert_to_prev_state"),&StateMachine::RevertToPrev);
		ObjectTypeDB::bind_method(_MD("get_current_state"),&StateMachine::CurrentState);
		ObjectTypeDB::bind_method(_MD("get_previous_state"),&StateMachine::PreviousState);
		ObjectTypeDB::bind_method(_MD("get_global_state"),&StateMachine::GlobalState);
		ObjectTypeDB::bind_method(_MD("set_owner","owner"),&StateMachine::setOwner);
	};
	
private:
	//FSM's owner
	entity*					m_Owner;

	//Current State
	State<entity>*			m_currentState;

	//Previous State
	State<entity>*			m_previousState;

	//Global State
	State<entity>*			m_GlobalState;

public:
	StateMachine(){
		m_Owner = NULL;
		m_currentState = NULL;
		m_previousState = NULL;
		m_GlobalState = NULL;
	}

	//~StateMachine(void);
	
	//Set Owner
	void setOwner(Node* o){
		this->set_owner(o);
		this->m_Owner = o;
	}

	//Methods for initializing FSM
	void setCurrentState(Node* s){this->m_currentState = dynamic_cast<State<entity>*>(s);}
	void setPreviousState(Node* s){this->m_previousState = dynamic_cast<State<entity>*>(s);}
	void setGlobalState(Node* s){this->m_GlobalState = dynamic_cast<State<entity>*>(s);}

	//First Enter in First State
	void FirstEnter() const{
		if(this->m_currentState)
			this->m_currentState->Enter(this->m_Owner);
	}

	//Update Method of FSM
	void Update(float delta) const{
		//If exist GlobalState => update
		if(this->m_GlobalState)
			this->m_GlobalState->Execute(this->m_Owner, delta);

		//If exist CurrentState => update
		if(this->m_currentState)
			this->m_currentState->Execute(this->m_Owner, delta);
	}

	//Change State
	void ChangeState(Node* newState){
		//Save actual state in previous state
		this->m_previousState = this->m_currentState;

		//Exit
		this->m_currentState->Exit(this->m_Owner);

		//change state
		this->m_currentState = dynamic_cast<State<entity>*>(newState);

		//Enter
		this->m_currentState->Enter(this->m_Owner);
	}

	//Rever to previous states
	void RevertToPrev(){
		this->ChangeState(this->m_previousState);
	}

	//Getter
	State<entity>* CurrentState() const {return this->m_currentState;};
	State<entity>* PreviousState() const {return this->m_previousState;};
	State<entity>* GlobalState() const {return this->m_GlobalState;};

};

#endif // STATEMACHINE_H
