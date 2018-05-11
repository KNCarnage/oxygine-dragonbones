#include "Skin.h"
#include "Armature.h"

namespace db
{
	Skin::Skin(const Armature *arm) :_armature(arm)
	{

	}

	Skin::~Skin()
	{

	}

	void Skin::load(pugi::xml_node node, const Armature *arm)
	{
		_name = node.attribute("name").as_string();

		pugi::xml_node slotNode = node.child("slot");
		while (slotNode)
		{
			Slot slot;
			
			const Bone *parent = arm->getBone(slotNode.attribute("parent").as_string());
			slot.load(slotNode, parent);
			_slots.push_back(slot);

			slotNode = slotNode.next_sibling("slot");
		}		
	}
}