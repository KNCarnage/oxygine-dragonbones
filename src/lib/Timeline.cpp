#include "Timeline.h"
#include "Animation.h"
#include "Armature.h"
#include "Bone.h"
#include "oxygine/math/ScalarMath.h"
#include "oxygine/core/log.h"

namespace db
{
	using namespace oxygine;

	const float AUTO_TWEEN_EASING = 10.f;
	const float NO_TWEEN_EASING = 20.f;
	const float USE_FRAME_TWEEN_EASING = 30.f;


	inline float getEaseValue(float value, float easing)
	{
		float valueEase = 1.f;

		if (easing > 1)    // ease in out
		{
			valueEase = 0.5f * (1.f - cos(value * MATH_PI));
			easing -= 1.f;
		}
		else if (easing > 0)    // ease out
		{
			valueEase = 1.f - pow(1.f - value, 2);
		}
		else if (easing < 0)    // ease in
		{
			easing *= -1.f;
			valueEase = pow(value, 2);
		}

		return (valueEase - value) * easing + value;
	}

	Timeline::Timeline()
	{

	}

	Timeline::~Timeline()
	{

	}

	const std::string&	Timeline::getName() const
	{
		return _name;
	}

	void Timeline::load(const Armature* arm, pugi::xml_node node, frames &fs)
	{
		_scale = node.attribute("scale").as_float();
		_offset = node.attribute("offset").as_float();
		_name = node.attribute("name").as_string();
		_bone = arm->getBone(_name.c_str());

		pugi::xml_node frameNode = node.child("frame");
		
		_begin = fs.size();
		while (frameNode)
		{
			Frame frame;
			frame.load(frameNode);
			fs.push_back(frame);


			frameNode = frameNode.next_sibling();
		}


		_end = fs.size();
	}

	TransformAndPivot Timeline::getFrame(int f, const Animation *anim) const
	{
		int pos = 0;
		const Frame *last = 0;
		for (int i = _begin; i != _end; ++i)
		{
			last = &anim->_frames[i];

			pos += last->getDuration();

			if (pos >= f)
				break;
		}

		TransformAndPivot res = last->getTransform();
		return res;
	}

	int				Timeline::findFrame(float f, const Animation* anim, int &tm) const
	{
		tm = 0;
		int pos = 0;
		const Frame *last = 0;
		for (int i = _begin; i != _end; ++i)
		{
			last = &anim->_frames[i];

			pos += last->getDuration();

			if (pos >= f)
			{
				tm = pos;
				return i;
			}
		}

		return _begin;
	}

	Frame			  Timeline::calcFrame(float time, const Animation *anim) const
	{
		/*
		const float tweenEasing = currentFrame->tweenEasing;

		if (tweenEasing && tweenEasing != NO_TWEEN_EASING && tweenEasing != AUTO_TWEEN_EASING)
		{
			progress = getEaseValue(progress, tweenEasing);
		}
		*/

		time /= _scale;
		time += _offset / anim->getScale();
		time = fmod(time, anim->getDuration());

		if (time > 1)
		{
			if (_name == "horseBody")
				int q = 0;
		}

		int tm = 0;
		int a = findFrame(time, anim, tm);
		int b = a + 1;

		if (b >= _end)
			b = _begin;

		const Frame &fa = anim->_frames[a];
		const Frame &fb = anim->_frames[b];
		

		int duration = fa.getDuration();
		float p = 1.0f - ((tm - time)) / duration;

		Frame res = fa;
		res._transform = fa._transform.lerp(fb._transform, p);

		if (anim->getDuration() != 60)
/*		if (_name == "head")
		log::messageln("%s - %.2f - %.2f, (%d, %d)", _name.c_str(), time, p, a-_begin, b-_begin);
*/		return res;
	}
}