#include "Animation.h"
#include "Bone.h"
namespace db
{
	Animation::Animation(const Armature *arm) :_armature(arm)
	{

	}

	Animation::~Animation()
	{

	}

	const std::string&	Animation::getName() const
	{
		return _name;
	}

	int					Animation::getDuration() const
	{
		return _duration;
	}

	int					Animation::getLoops() const
	{
		return _loops;
	}

	float				Animation::getScale() const
	{
		return _scale;
	}

	const Timeline* Animation::getTimeline(const char *name) const
	{
		for (const Timeline &tm : _timelines)
		{
			if (tm.getName() == name)
				return &tm;
		}

		return 0;
	}

	TransformAndPivot Animation::getFrame(int frame, const Bone* bone) const
	{
		const Timeline *tm = getTimeline(bone->getName().c_str());
		if (tm)
			return tm->getFrame(frame, this);
		TransformAndPivot tp;
		*((dbTransform*)&tp) = bone->getTransform();

		return tp;
	}

	Frame				Animation::calcFrame(float time, const Bone* bone) const
	{
		const Timeline *tm = getTimeline(bone->getName().c_str());
		if (tm)
			return tm->calcFrame(time, this);

		Frame f;
		return f;
	}

	void Animation::load(const Armature *arm, pugi::xml_node node)
	{
		_duration = node.attribute("duration").as_int();
		_loops = node.attribute("loops").as_int();

		_tweenEasing = node.attribute("tweenEasing").as_float();
		_scale = node.attribute("scale").as_float();
		if (_scale == 0)
			_scale = 1;

		_name = node.attribute("name").as_string();
		pugi::xml_node tmNode = node.child("timeline");
		while (tmNode)
		{
			Timeline tm;
			tm.load(arm, tmNode, _frames);
			_timelines.push_back(tm);

			tmNode = tmNode.next_sibling("timeline");
		}
		int q = 0;
	}
}