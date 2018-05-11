#pragma once
#include "oxygine/pugixml/pugixml.hpp"
#include "Transform.h"

namespace db
{
	class Armature;

	class Display
	{
	public:
		Display();

		void load(pugi::xml_node node);

		const std::string&			getRef() const { return _ref; }
		const std::string&			getType() const { return _type; }
		//const const Armature*		getArmature() const { return _armature; }
		const TransformAndPivot&	getTransform() const { return _transform; }

	protected:
		std::string			_ref;
		std::string			_type;
		TransformAndPivot	_transform;
	};
}