#pragma once
#include <vector>
#include "oxygine/pugixml/pugixml.hpp"
#include "Armature.h"


namespace db
{
	class Skeleton
	{
	public:
		Skeleton();

		void load(pugi::xml_node node);

		const Armature* getArmature(const char *name) const;
		const Armature* getArmature(int i) const;
		int				getArmaturesNum() const;		
		int				getFramerate() const;

	protected:
		typedef std::vector<Armature*> armatures;
		armatures	_armatures;
		int			_framerate;
	};
}