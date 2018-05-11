#pragma once
#include <vector>
#include "oxygine/pugixml/pugixml.hpp"
#include "Bone.h"
#include "Skin.h"
#include "Animation.h"

namespace db
{
	class Bone;
	class Skeleton;

	class Armature
	{
	public:
		Armature(const Skeleton *sk);
		void load(pugi::xml_node node);

		const Skeleton*		getSkeleton() const;
		Bone*				getBone(const char *);
		const Bone*			getBone(const char *) const;
		const std::string&	getName() const;
		const Animation*	getAnimation(const std::string &name) const;
		const Animation*	getAnimation(int i) const;
		int					getNumAnimations() const;

		const Skin*			getSkin(int i) const;
		int					getNumSkines() const;

	//protected:
		std::string _name;
		typedef std::vector<Bone> bones;
		bones _bones;

		typedef std::vector<Skin> skines;
		skines _skines;

		typedef std::vector<Animation> animations;
		animations _animations;

		const Skeleton *_skeleton;
	};
}