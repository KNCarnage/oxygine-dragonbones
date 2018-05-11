#include "Bone.h"
namespace db
{
	Bone::Bone(const Armature *arm) :_parent(0), _armature(arm)
	{

	}

	Bone::~Bone()
	{

	}

	const std::string& Bone::getName() const
	{
		return _name;
	}

	const dbTransform&	Bone::getTransform() const
	{
		return _transform;
	}

	const Bone*			Bone::getParent() const
	{
		return _parent;
	}

	void Bone::load(pugi::xml_node node)
	{
		_name = node.attribute("name").as_string();
		_transform.load(node.child("transform"));
	}
}