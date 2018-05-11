#pragma once
#include "oxygine/pugixml/pugixml.hpp"
#include <vector>
#include "Slot.h"

namespace db
{
	class Armature;

	class Skin
	{
	public:
		Skin(const Armature *arm);
		~Skin();

		void load(pugi::xml_node node, const Armature *arm);

	//protected:
		const Armature *_armature;
		std::string _name;
		std::vector<Slot> _slots;
	};
}