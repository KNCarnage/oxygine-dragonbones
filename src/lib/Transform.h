#pragma once
#include "oxygine/pugixml/pugixml.hpp"

namespace db
{
	class dbTransform
	{
	public:
		pugi::xml_attribute load(pugi::xml_node node);

		bool operator == (const dbTransform &r) const
		{
			return r.x == x && r.y == y && skX == r.skX && skY == r.skY && scX == r.scX && scY == r.scY;
		}

		bool operator != (const dbTransform &r) const
		{
			return !(*this == r);
		}

		float x;
		float y;
		float skX;
		float skY;
		float scX;
		float scY;
	};

	class TransformAndPivot: public dbTransform
	{
	public:
		void load(pugi::xml_node node);

		TransformAndPivot lerp(const TransformAndPivot &r, float p) const;


		float pX;
		float pY;
	};
}