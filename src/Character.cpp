#include "Character.h"
#include "lib/Armature.h"
#include "oxygine/res/Resources.h"
#include "oxygine/RenderState.h"
#include "oxygine/core/Renderer.h"
#include "oxygine/AnimationFrame.h"
#include "oxygine/res/ResAnim.h"
#include "lib/Animation.h"
#include "lib/Skeleton.h"
#include "oxygine/actor/ColorRectSprite.h"
namespace oxygine
{
	Character::Character() :_armature(0), _animation(0), _resources(0), _time(0)
	{
		spColorRectSprite cl = new ColorRectSprite;
		cl->setSize(5, 5);
		cl->setAnchor(0.5f, 0.5f);
		addChild(cl);
	}

	Character::~Character()
	{

	}

	void Character::setArmature(const Armature *arm)
	{
		_armature = arm;
	}

	void Character::setResources(Resources *res)
	{
		_resources = res;
	}

	void Character::setAnimation(const Animation *anim)
	{
		_animation = anim;
	}

	AffineTransform from(const dbTransform& transform)
	{
		AffineTransform tr;
#if 1
		tr.a = scalar::cos(transform.skY) * transform.scX;
		tr.b = scalar::sin(transform.skY) * transform.scX;
		tr.c =-scalar::sin(transform.skX) * transform.scY;
		tr.d = scalar::cos(transform.skX) * transform.scY;
#else		
		tr.a = scalar::cos(transform.skY);
		tr.b = scalar::sin(transform.skY);
		tr.c =-scalar::sin(transform.skX);
		tr.d = scalar::cos(transform.skX);
#endif

		tr.x = transform.x;
		tr.y = transform.y;

		return tr;
	}

	AffineTransform from(const TransformAndPivot& transform)
	{
		AffineTransform tr = from(*(dbTransform*)&transform);

		//tr.x = transform.x;
		//tr.y = transform.y;

		tr.x -= transform.pX * tr.a + transform.pY * tr.c;
		tr.y -= transform.pX * tr.b + transform.pY * tr.d;

		return tr;

	}

	AffineTransform from(const Bone* bone)
	{
		if (bone->getName() == "innerarm_hand")
			int q = 0;
		AffineTransform tr;
		tr = from(bone->getTransform());
		return tr;


		tr.identity();
		//tr = from(bone->getTransform());
		while (bone)
		{
			tr = from(bone->getTransform()) * tr;
			//tr = tr * from(bone->getTransform());
			break;
			bone = bone->getParent();
		}
		return tr;
	}

	void Character::renderArmature(const Armature *arm, const Animation *anim, const Skin* skin, float time_, const RenderState& rs_)
	{
		const Skeleton *sk = arm->getSkeleton();

		float frame = fmod(time_ * sk->getFramerate(), anim->getDuration() * anim->getScale());
		frame /= anim->getScale();
		//log::messageln("frame: %.2f", frame);


		RenderState rs = rs_;

		STDRenderer* renderer = STDRenderer::getCurrent();


		for (const Slot& slot : skin->_slots)
		{
			const Bone *bone = slot._parent;
			

			Frame f = anim->calcFrame(frame, bone);

			if (f._displayIndex == -1)
				continue;

			const Display &display = slot._displays[f._displayIndex];

			TransformAndPivot tt = f.getTransform();

			AffineTransform boneTr = from(tt);

			AffineTransform dt = from(display.getTransform());
			AffineTransform tr = dt * boneTr;

			rs.transform = tr * rs_.transform;

			if (display.getType() == "armature")
			{
				const Armature *arm = _armature->getSkeleton()->getArmature(display.getRef().c_str());
				const Animation *anim = arm->getAnimation(0);
				const Skin	*skin = arm->getSkin(0);
				renderArmature(arm, anim, skin, time_, rs);
				continue;
			}


			ResAnim *res = _resources->getResAnim(display.getRef());
			const AnimationFrame& animFrame = res->getFrame(0);			

			rsCache().setTexture(animFrame.getDiffuse().base, 0);

			Color color(Color::White);

			float tw = 1.0f / animFrame.getWidth();
			float th = 1.0f / animFrame.getHeight();


			for (int y = 0; y < animFrame.getHeight(); ++y)
			{
				for (int x = 0; x < animFrame.getWidth(); ++x)
				{
					int col = animFrame.getColumn();
					int row = animFrame.getRow();

					unsigned int rgba = color.premultiplied().rgba();

					float u = animFrame.getSrcRect().pos.x;
					float v = animFrame.getSrcRect().pos.y;

					float du = animFrame.getSrcRect().size.x;
					float dv = animFrame.getSrcRect().size.y;

					vertexPCT2 vert[4];
					vertexPCT2 vt;
					vertexPCT2* pv = vert;
					vt.color = rgba;

					const Vector2& pos = animFrame.getDestRect().pos;
					const Vector2& size = animFrame.getDestRect().size;

					Vector2 p1(pos.x, pos.y);
					Vector2 p2(pos.x, pos.y + size.y);
					Vector2 p3(pos.x + size.x, pos.y);
					Vector2 p4(pos.x + size.x, pos.y + size.y);

/*
					p1 = transform.transform(p1);
					p2 = transform.transform(p2);
					p3 = transform.transform(p3);
					p4 = transform.transform(p4);
*/
					vt.z = 0;

					vt.x = p1.x;
					vt.y = p1.y;
					vt.u = u;
					vt.v = v;
					*pv = vt;
					++pv;

					vt.x = p2.x;
					vt.y = p2.y;
					vt.u = u;
					vt.v = v + dv;
					*pv = vt;
					++pv;

					vt.x = p3.x;
					vt.y = p3.y;
					vt.u = u + du;
					vt.v = v;
					*pv = vt;
					++pv;

					vt.x = p4.x;
					vt.y = p4.y;
					vt.u = u + du;
					vt.v = v + dv;
					*pv = vt;
					++pv;

					renderer->addVertices(vert, sizeof(vert));
				}
			}

//			rsCache().draw(&rs, Color::White, animFrame.getSrcRect(), animFrame.getDestRect());
		}
	}

	void Character::doUpdate(const UpdateState& us)
	{
		_time += us.dt / 1000.0f;
	}

	void Character::doRender(const RenderState& rs_)
	{
		const Skin *skin = &_armature->_skines.front();

		rsCache().setBlendMode(blend_premultiplied_alpha);
		renderArmature(_armature, _animation, skin, _time, rs_);
	}
}