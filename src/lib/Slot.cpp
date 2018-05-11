#include "Slot.h"
#include "Display.h"
#include "oxygine/core/ox_debug.h"

namespace db
{
	Slot::Slot() :_parent(0)
	{

	}

	Slot::~Slot()
	{

	}

	void Slot::load(pugi::xml_node node, const Bone *parent)
	{
		OX_ASSERT(parent);
		_parent = parent;
		_name = node.attribute("name").as_string();

		pugi::xml_node displayNode = node.child("display");
		while (displayNode)
		{
			Display display;
			display.load(displayNode);

			_displays.push_back(display);

			displayNode = displayNode.next_sibling("display");
			//break;
		}

		if (_displays.size() > 1)
			int q = 0;
	}
}