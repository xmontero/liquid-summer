#include "AffineTransformations.h"
#include "AffineTransformation.h"

#include <random>

Vector3d AffineTransformations::operate( const Vector3d & vectorToBeTransformed, const Vector3d & externalOffset )
{
	double maxKnifePosition;
	double knifePosition;
	double accumulatedProbability;
	Vector3d result;
	int currentAffineTransformation;
	
	maxKnifePosition = 0;
	for( int n = 0; n < maxPossibleTransformations; n++ )
	{
		maxKnifePosition += affineTransformations[ n ].probabilityWeight;
	}
	
	knifePosition = rand() / ( double( RAND_MAX ) / maxKnifePosition );
	
	accumulatedProbability = 0;
	for( int n = 0; n < maxPossibleTransformations; n++ )
	{
		accumulatedProbability += affineTransformations[ n ].probabilityWeight;
		
		if( knifePosition < accumulatedProbability )
		{
			currentAffineTransformation = n;
			break;
		}
		
	}
	
	result = affineTransformations[ currentAffineTransformation ].operate( vectorToBeTransformed, externalOffset );
	return result;
}
