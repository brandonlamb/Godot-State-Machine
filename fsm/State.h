#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "scene/main/node.h"
#include "object.h"
#include "string_db.h"

template <class entity>
class State : public Node
{
	OBJ_TYPE(State,Node);

protected:
    static void _bind_methods(){
		
	}
	
public:
	State(void){}

	//This method is called when first enter in the state
	virtual void Enter(entity* e){
		get_script_instance()->call(strEnterMth, e);
	}

	//This method is executed every FSM update
	virtual void Execute(entity* e, float delta){
		get_script_instance()->call(strExecuteMth, e, delta);
	}

	//This method is called when exit from the state
	virtual void Exit(entity* e){
		get_script_instance()->call(strExitMth, e);
	}

	virtual ~State(void){}
	
	const StringName strEnterMth = StaticCString::create("state_enter");
	const StringName strExecuteMth = StaticCString::create("state_execute");
	const StringName strExitMth = StaticCString::create("state_exit");
};

#endif // STATE_H_INCLUDED
