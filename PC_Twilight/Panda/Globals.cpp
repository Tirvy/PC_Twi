
#include "pandaFramework.h"
#include "pandaSystem.h"
#include "PGButton.h"
#include "pgEntry.h"
#include "mouseButton.h"
#include "cardMaker.h"
#include "mouseWatcher.h"
#include "planeNode.h"
#include "collisionPlane.h"
#include "texturePool.h"
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "fontPool.h"
#include "collisionRay.h"
#include "collisionTraverser.h"
#include "collisionHandlerQueue.h"
#include "nodePathCollection.h"
#include "queuedConnectionListener.h"
#include "queuedConnectionManager.h"
#include "queuedConnectionReader.h"
#include "audioManager.h"


// Here's what we'll store the camera in.
NodePath _Camera;
PT(MouseWatcher) _Mouse;
PT(CollisionRay) _Picker;


PandaFramework _Framework;
WindowFramework * _Window;
CollisionTraverser _Traverser;
PT(CollisionHandlerQueue) _Handler;

PT(TextFont) font=FontPool::load_font("Slicker Regular.ttf");
PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr(); 
PT(ClockObject) _GlobalClock = ClockObject::get_global_clock();

void LMB(const Event *ev, void *data);
void RMB(const Event *ev, void *data);
void MMB(const Event *ev, void *data);

void LaunchPanda(int argc, char** argv){

	font->set_line_height(1.0);
	TextNode("nothing").set_default_font(font);// PLACEd!!!
	PandaFramework* framework = &_Framework;
	framework->open_framework(argc, argv);
	framework->set_window_title("Twi_PC");
	_Window = framework->open_window();
    // Get the camera and store it in a variable.
    _Camera = _Window->get_camera_group();
	_Window->setup_trackball();
	_Window->enable_keyboard();
	MouseButton::init_mouse_buttons();


	_Mouse = (MouseWatcher*)_Window->get_mouse().node();
	PT(CollisionNode) pickerNode;
	NodePath pickerNP;
	 
	pickerNode = new CollisionNode("mouseRay");
	pickerNP = _Window->get_camera_group().attach_new_node (pickerNode);
	pickerNode->set_from_collide_mask(GeomNode::get_default_collide_mask());
	_Picker = new CollisionRay();
	pickerNode->add_solid(_Picker);
	_Handler = new CollisionHandlerQueue();
	_Traverser.add_collider(pickerNP, _Handler);
	_Framework.define_key("mouse1","lmb",&LMB,0);
	_Framework.define_key("mouse3","rmb",&RMB,0);
	_Framework.define_key("mouse2","mmb",&MMB,0);
}

class ActionArea;