#include "AffineTransformation.h"

#include "Vector3d.h"

Vector3d AffineTransformation::operate( const Vector3d & vectorToBeTransformed, const Vector3d & externalOffset )
{
	Vector3d result;

	result = ( transform * ( vectorToBeTransformed - externalOffset ) ) + offset + externalOffset;

	return result;
}
