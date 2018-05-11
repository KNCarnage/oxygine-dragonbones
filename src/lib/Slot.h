#pragma once
#include "oxygine/pugixml/pugixml.hpp"
#include <vector>
#include "Display.h"

namespace db
{
	class Bone;

	class Slot
	{
	public:
		Slot();
		~Slot();

		void load(pugi::xml_node node, const Bone *parent);

	//protected:
		typedef std::vector<Display> displays;
		displays _displays;

		const Bone *_parent;
		std::string _name;
		int _z;
	};
}