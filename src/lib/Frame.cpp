#include "Frame.h"
#include "oxygine/pugixml/pugixml.hpp"

namespace db
{
	Frame::Frame() :_z(0), _displayIndex(0), _duration(0)
	{

	}

	Frame::~Frame()
	{

	}

	const std::string&	Frame::getName() const
	{
		return _name;
	}

	int	Frame::getDuration() const
	{
		return _duration;
	}

	int	Frame::getZ() const
	{
		return _z;
	}

	const TransformAndPivot &Frame::getTransform() const
	{
		return _transform;
	}

	void Frame::load(pugi::xml_node node)
	{
		_tweenEasing = node.attribute("tweenEasing").as_float();
		_duration = node.attribute("duration").as_int();
		_z = node.attribute("z").as_int();
		_displayIndex = node.attribute("displayIndex").as_int();
		_transform.load(node.child("transform"));
	}
}