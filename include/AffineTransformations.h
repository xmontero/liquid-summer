#ifndef LIQUID_SUMMER_AFFINE_TRANSFORMATIONS_H
#define LIQUID_SUMMER_AFFINE_TRANSFORMATIONS_H

#include "AffineTransformation.h"

class AffineTransformations
{
	public:
		
		static const int maxPossibleTransformations = 10;
		AffineTransformation affineTransformations[ maxPossibleTransformations ];
		
	public:
		
		Vector3d operate( const Vector3d & vectorToBeTransformed, const Vector3d & offset );
};

#endif
