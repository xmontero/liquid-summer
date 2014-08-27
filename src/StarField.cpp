#include "StarField.h"

StarField::StarField( int n )
{
	if( n > maxPoints )
	{
		throw "StarField cannot accept so many points.";
	}
	
	for( int i = 0; i < n; i++ )
	{
		starSpeeds[ i ].randomize( 2 );
		starPositions[ i ].randomize( 10 );
	}
	
	numberOfActivePoints = n;
}

void StarField::step( void )
{
	Matrix3x3 rotation;
	Vector3d rotated;
	
	rotationXAngle += rotationXAngularSpeed;
	rotationYAngle += rotationYAngularSpeed;
	rotationZAngle += rotationZAngularSpeed;
	
	rotation.createRotationXYZ( rotationXAngle, rotationYAngle, rotationZAngle );
	
	for( int i = 0; i < numberOfActivePoints; i++ )
	{
		starPositions[ i ] += starSpeeds[ i ];
		
		if( starPositions[ i ].getModulus() > 300 )
		{
			starPositions[ i ].zero();
			starSpeeds[ i ].randomize( 10 );
		}
		
		rotated = rotation * starPositions[ i ];
		
		starField[ i ].x = rotated.x;
		starField[ i ].y = rotated.y;
		starField[ i ].z = rotated.z;
	}
}
