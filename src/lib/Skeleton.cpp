#include "Skeleton.h"
namespace db
{
	Skeleton::Skeleton() :_framerate(0)
	{

	}

	void Skeleton::load(pugi::xml_node node)
	{
		_framerate = node.attribute("frameRate").as_int();

		pugi::xml_node armatureNode = node.child("armature");
		while (armatureNode)
		{ 
			Armature *arm = new Armature(this);
			arm->load(armatureNode);
			_armatures.push_back(arm);

			armatureNode = armatureNode.next_sibling("armature");
		}
	}

	const Armature* Skeleton::getArmature(const char *name) const
	{
		for (const Armature* arm : _armatures)
			if (arm->getName() == name)
				return arm;
		return 0;
	}

	const Armature* Skeleton::getArmature(int i) const
	{
		return _armatures[i];
	}

	int				Skeleton::getArmaturesNum() const
	{
		return (int)_armatures.size();
	}

	int				Skeleton::getFramerate() const
	{
		return _framerate;
	}
}