#include "Transform.h"
#include "oxygine/math/ScalarMath.h"

namespace db
{

	float formatRadian(float radian)
	{
		//return radian;
		radian = fmod(radian, MATH_PI * 2.f);

		if (radian > MATH_PI)
		{
			radian -= MATH_PI * 2.f;
		}

		if (radian < -MATH_PI)
		{
			radian += MATH_PI * 2.f;
		}

		return radian;
	}


	float fixAngle(float a)
	{
		a += 360;
		a = fmod(a, 360);
		//a += 360;
		//a = a + 360 * 10;
		return a;
	}

	bool test()
	{
		float f1 = fixAngle(-147);
		float f2 = fixAngle(177);
		float f3 = fixAngle(-137);
		return true;
	}
	bool s = test();



	pugi::xml_attribute dbTransform::load(pugi::xml_node node)
	{
		pugi::xml_attribute attr;
//Carnage
/*
		x	= find_next_attribute(node, attr, "x").as_float();
		y	= find_next_attribute(node, attr, "y").as_float();
		skX = find_next_attribute(node, attr, "skX").as_float();
		skY = find_next_attribute(node, attr, "skY").as_float();

		skX = fixAngle(skX);
		skY = fixAngle(skY);
		if (std::string(node.attribute("skX").as_string()) == "-147.76")
			int q = 0;
		skX = formatRadian(skX / 180.0f * MATH_PI);
		skY = formatRadian(skY / 180.0f * MATH_PI);
		scX	= find_next_attribute(node, attr, "scX").as_float();
		scY	= find_next_attribute(node, attr, "scY").as_float();
*/		
		return attr;
	}

	void TransformAndPivot::load(pugi::xml_node node)
	{
		pugi::xml_attribute attr = dbTransform::load(node);
//Carnage
/*
		pX = find_next_attribute(node, attr, "pX").as_float();
		pY = find_next_attribute(node, attr, "pY").as_float();
*/
		}

	TransformAndPivot TransformAndPivot::lerp(const TransformAndPivot &r, float p) const
	{
		TransformAndPivot res;
#define LERP(a, b, p)  (a + (b-a) * p)
		
		res.pX = LERP(pX, r.pX, p);
		res.pY = LERP(pY, r.pY, p);
		
		res.x = LERP(x, r.x, p);
		res.y = LERP(y, r.y, p);
		
		res.scX = LERP(scX, r.scX, p);
		res.scY = LERP(scY, r.scY, p);

		float c;
		c = formatRadian(r.skX - skX);
		res.skX = skX + c *p;
		c = formatRadian(r.skY - skY);
		res.skY = skY + c *p;

#undef  LERP
		return res;
	}
}