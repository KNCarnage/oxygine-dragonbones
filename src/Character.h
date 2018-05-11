#pragma once
#include "oxygine/actor/Actor.h"

namespace db
{
	class Armature;
	class Animation;
	class Armature;
	class Skin;
}

namespace oxygine
{
	using namespace db;

	class Resources;
	
	DECLARE_SMART(Character, spCharacter);
	class Character : public Actor
	{
	public:
		Character();
		~Character();

		void setResources(Resources *res);
		void setAnimation(const Animation *anim);
		void setArmature(const Armature *);

	protected:
		void doUpdate(const UpdateState& us);
		void doRender(const RenderState& rs);
		void renderArmature(const Armature *arm, const Animation *anim, const Skin* skin, float time, const RenderState& rs);

		const Armature *_armature;
		const Animation *_animation;
		Resources *_resources;
		float _time;

	};
}
