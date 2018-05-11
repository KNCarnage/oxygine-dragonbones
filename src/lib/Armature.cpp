#include "Armature.h"
#include "oxygine/core/ox_debug.h"

namespace db
{
	Armature::Armature(const Skeleton *sk) :_skeleton(sk)
	{

	}

	void Armature::load(pugi::xml_node armatureNode)
	{
		_name = armatureNode.attribute("name").as_string();
		pugi::xml_node boneFirst = armatureNode.child("bone");
		pugi::xml_node boneNode = boneFirst;
		while (boneNode)
		{
			Bone bone(this);
			bone.load(boneNode);

			_bones.push_back(bone);

			boneNode = boneNode.next_sibling("bone");
		}

		//link
		boneNode = boneFirst;
		while (boneNode)
		{
			const char *name = boneNode.attribute("name").as_string();
			const char *parent = boneNode.attribute("parent").as_string();
			Bone *bone = getBone(name);
			if (*parent)
			{
				Bone *parentBone = getBone(parent);
				bone->_parent = parentBone;
			}
			
			boneNode = boneNode.next_sibling("bone");
		}

		pugi::xml_node skinNode = armatureNode.child("skin");
		while (skinNode)
		{
			Skin skin(this);
			skin.load(skinNode, this);

			_skines.push_back(skin);

			skinNode = skinNode.next_sibling("skin");
		}

		pugi::xml_node animationNode = armatureNode.child("animation");
		while (animationNode)
		{
			Animation animation(this);
			animation.load(this, animationNode);
			_animations.push_back(animation);

			animationNode = animationNode.next_sibling("animation");
		}
	}

	const Skeleton*		Armature::getSkeleton() const
	{
		return _skeleton;
	}

	const std::string&	Armature::getName() const
	{
		return _name;
	}

	int	Armature::getNumAnimations() const
	{
		return _animations.size();
	}

	int	Armature::getNumSkines() const
	{
		return _skines.size();
	}

	const Skin*	Armature::getSkin(int i) const
	{
		return &_skines[i];
	}


	const Animation*	Armature::getAnimation(const std::string &name) const
	{
		for (animations::const_iterator i = _animations.begin(); i != _animations.end(); ++i)
		{
			const Animation &anim = *i;
			if (anim.getName() == name)
				return &anim;
		}
		return 0;
	}

	const Animation*	Armature::getAnimation(int i) const
	{
		return &_animations[i];
	}

	const Bone* Armature::getBone(const char *name) const
	{
		for (bones::const_iterator i = _bones.begin(); i != _bones.end(); ++i)
		{
			const Bone &bone = *i;
			if (bone.getName() == name)
				return &bone;
		}
		OX_ASSERT(0);
		return 0;
	}

	Bone* Armature::getBone(const char *name)
	{
		for (bones::iterator i = _bones.begin(); i != _bones.end(); ++i)
		{
			Bone &bone = *i;
			if (bone.getName() == name)
				return &bone;
		}
		OX_ASSERT(0);
		return 0;
	}
}