#pragma once
#include "oxygine/pugixml/pugixml.hpp"
#include "Frame.h"
#include <vector>

namespace db
{
	class Animation;
	class Bone;
	class Armature;

	class Timeline
	{
	public:
		Timeline();
		~Timeline();

		const std::string&	getName() const;
		TransformAndPivot getFrame(int f, const Animation *anim) const;
		
		Frame			  calcFrame(float time, const Animation *anim) const;
		
		typedef std::vector<Frame> frames;

		void load(const Armature* , pugi::xml_node node, frames &fs);

	protected:
		int		findFrame(float f, const Animation* anim, int &tm) const;

		friend class Armature;

		float _scale;
		float _offset;
		int _begin;
		int _end;

		const Bone*		_bone;
		std::string		_name;
	};
}