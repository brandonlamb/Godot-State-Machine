/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"
#include "State.h"
#include "StateMachine.h"
#include "scene/main/node.h"

void register_fsm_types() {

    ObjectTypeDB::register_type<StateMachine<Node> >();
    ObjectTypeDB::register_type<State<Node> >();

}

void unregister_fsm_types() {
   //nothing to do here
}
