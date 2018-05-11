#include "Display.h"
namespace db
{
	Display::Display()// :_armature(false)
	{

	}

	void Display::load(pugi::xml_node node)
	{
		_ref = node.attribute("name").as_string();
		_type = node.attribute("type").as_string();
		//_armature = strcmp(node.attribute("type").as_string(), "armature") == 0 ? true : false;
		//if (strcmp(node.attribute("type").as_string(), "armature") == 0)
		//	_ref = "";
		_transform.load(node.child("transform"));
	}
}