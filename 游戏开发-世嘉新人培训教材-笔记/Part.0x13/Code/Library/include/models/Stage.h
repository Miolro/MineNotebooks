// 舞台
#pragma once
#include "base/calculate/Vector3.h"
namespace base
{
    namespace calculate
    {
        class Matrix44;
    }
}
namespace engine
{
    namespace collision
    {
        class Triangle;
    }
}
namespace Model
{
    using namespace base::calculate;
    using namespace engine::collision;
	class Stage
	{
	public:
		Stage();
        void restrictMove(Vector3* v, const Vector3& position) const;
		void draw(const Matrix44&)const;
		Vector3 mPosition[4];
		unsigned mColor[4];
        Triangle** mTriangle;
	};

}

