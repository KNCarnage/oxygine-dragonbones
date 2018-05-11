#pragma once
#include "oxygine/pugixml/pugixml.hpp"
#include "Transform.h"

namespace db
{
	class Armature;

	class Bone
	{
	public:
		Bone(const Armature *arm);
		~Bone();

		const std::string&	getName() const;
		const dbTransform&	getTransform() const;
		const Bone*			getParent() const;

		void load(pugi::xml_node node);		

	protected:
		friend class Armature;

		const Armature*	_armature;
		Bone*			_parent;
		dbTransform		_transform;
		std::string		_name;
	};
}