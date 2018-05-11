#pragma once
#include "oxygine/pugixml/pugixml.hpp"
#include "Transform.h"

namespace db
{
	class Frame
	{
	public:
		Frame();
		~Frame();

		const std::string&	getName() const;
		int					getDuration() const;
		int					getZ() const;
		const TransformAndPivot &getTransform() const;

		void load(pugi::xml_node node);

	//protected:
		friend class Armature;

		float				_tweenEasing;
		TransformAndPivot	_transform;
		int					_duration;
		int					_z;
		int					_displayIndex;

		std::string		_name;
	};
}