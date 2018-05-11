#pragma once
//#include "oxygine/pugixml/pugixml.hpp"
#include "Frame.h"
#include "Timeline.h"
#include <vector>

namespace db
{
	class Bone;
	class Armature;
	class Animation
	{
	public:
		Animation(const Armature *arm);
		~Animation();

		const std::string&	getName() const;
		TransformAndPivot   getFrame(int frame, const Bone* bone) const;
		Frame				calcFrame(float time, const Bone* bone) const;
		const Timeline*		getTimeline(const char *name) const;
		int					getDuration() const;
		int					getLoops() const;
		float				getScale() const;

		void load(const Armature *, pugi::xml_node node);

	protected:
		friend class Timeline;
		const Armature *_armature;

		std::string		_name;
		typedef std::vector<Frame> frames;

		int		_duration;
		float	_scale;
		float	_tweenEasing;
		int		_loops;


		typedef std::vector<Timeline>  timelines;
		timelines _timelines;

		frames _frames;
	};
}