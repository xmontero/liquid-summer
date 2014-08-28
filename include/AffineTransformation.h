#ifndef LIQUID_SUMMER_AFFINE_TRANSFORMATION_H
#define LIQUID_SUMMER_AFFINE_TRANSFORMATION_H

#include "Math.h"

class AffineTransformation
{
	public:
		
		Matrix3x3 transform;
		Vector3d offset;
		double probabilityWeight = 0;
		
		Vector3d operate( const Vector3d & vectorToBeTransformed, const Vector3d & offset );
};

#endif
