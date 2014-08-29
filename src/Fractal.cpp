#include "Fractal.h"
#include "Math.h"

#include <random>

Fractal::Fractal( int n )
{
	if( n > maxPoints )
	{
		throw "Fractal cannot accept so many points.";
	}
	
	numberOfActivePoints = n;
	
	initAffineTransformations();
}

void Fractal::initAffineTransformations( void )
{
	int affineTransformationId;
	double scale = 0.5;
	
	objectOffset.setXYZ( 0, -400, 0 ).scale( scale );
	
	// http://mathworld.wolfram.com/BarnsleysFern.html
	// http://en.wikipedia.org/wiki/Barnsley_fern
	// f_1(x,y) = [0.85 0.04; -0.04 0.85][x; y]+[0.00; 1.60]
	// f_2(x,y) = [-0.15 0.28; 0.26 0.24][x; y]+[0.00; 0.44]
	// f_3(x,y) = [0.20 -0.26; 0.23 0.22][x; y]+[0.00; 1.60]
	// f_4(x,y) = [0.00 0.00; 0.00 0.16][x; y]
	
	affineTransformationId = 0;
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d(  0.85,  0.04, 0.00 ), 1 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( -0.04,  0.85, 0.05 ), 2 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d(  0.00, -0.05, 0.85 ), 3 );
	affineTransformations.affineTransformations[ affineTransformationId ].offset.setXYZ( 0, 160, 0 ).scale( scale );
	affineTransformations.affineTransformations[ affineTransformationId ].probabilityWeight = 0.70; // 0.85;
	
	affineTransformationId = 1;
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( -0.15, 0.28,  0.00 ), 1 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d(  0.26, 0.24, -0.10 ), 2 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d(  0.00, 0.10,  0.4  ), 3 );
	affineTransformations.affineTransformations[ affineTransformationId ].offset.setXYZ( 0, 44, 0 ).scale( scale );
	affineTransformations.affineTransformations[ affineTransformationId ].probabilityWeight = 0.07;

	affineTransformationId = 2;
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( 0.20, -0.26, 0.00 ), 1 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( 0.23,  0.22, 0.00 ), 2 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( 0.00,  0.00, 0.40 ), 3 );
	affineTransformations.affineTransformations[ affineTransformationId ].offset.setXYZ( 0, 160, 0 ).scale( scale );
	affineTransformations.affineTransformations[ affineTransformationId ].probabilityWeight = 0.07;

	affineTransformationId = 3;
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( 0.00, 0.00, 0.00 ), 1 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( 0.00, 0.16, 0.00 ), 2 );
	affineTransformations.affineTransformations[ affineTransformationId ].transform.setRowVector( Vector3d( 0.00, 0.00, 0.00 ), 3 );
	affineTransformations.affineTransformations[ affineTransformationId ].offset.setXYZ( 0, 0, 0 ).scale( scale );
	affineTransformations.affineTransformations[ affineTransformationId ].probabilityWeight = 0.001; // 0.01;

	affineTransformationId = 4;
	affineTransformations.affineTransformations[ affineTransformationId ].transform.createRotationXYZ( pi / 4, -pi / 2, 0 ).scale( 0.25 );
	affineTransformations.affineTransformations[ affineTransformationId ].offset.setXYZ( 0, 120, 0 ).scale( scale );
	affineTransformations.affineTransformations[ affineTransformationId ].probabilityWeight = 0.07;

	affineTransformationId = 5;
	affineTransformations.affineTransformations[ affineTransformationId ].transform.createRotationXYZ( -pi / 4, -pi / 2, pi / 8 ).scale( 0.35 );
	affineTransformations.affineTransformations[ affineTransformationId ].offset.setXYZ( 0, 80, 0 ).scale( scale );
	affineTransformations.affineTransformations[ affineTransformationId ].probabilityWeight = 0.07;

	/*
	// Replica 1
	replica = 1;
	tmpScale.createScaleXYZ( 0.9, 0.9, 0.9 );
	tmpRotation.createRotationXYZ( -pi / 10, pi / 4, pi );
	replicaTransforms[ replica ] = tmpRotation * tmpScale;
	replicaOffsets[ replica ].setXYZ( 100, -100, 100 );
	
	// Replica 2
	replica = 2;
	tmpScale.createScaleXYZ( 0.200, -0.400, 0.300 );
	tmpRotation.createRotationXYZ( pi / 3, pi / 2, -pi / 4 );
	replicaTransforms[ replica ] = tmpRotation * tmpScale;
	replicaOffsets[ replica ].setXYZ( 100, -100, 100 );
	*/
}

void Fractal::step( void )
{
	Matrix3x3 rotation;
	Vector3d rotated;
	Vector3d currentPoint;
	
	rotationXAngle += rotationXAngularSpeed;
	rotationYAngle += rotationYAngularSpeed;
	rotationZAngle += rotationZAngularSpeed;
	
	rotation.createRotationXYZ( rotationXAngle, rotationYAngle, rotationZAngle );
	
	//currentPoint = affineTransformations.affineTransformations[ 0 ].offset;
	currentPoint.zero();
	
	for( int i = 0; i < numberOfActivePoints; i++ )
	{
		Vector3d tmpPoint;
		
		tmpPoint = currentPoint;
		currentPoint = affineTransformations.operate( tmpPoint, objectOffset );
		
		starPositions[ i ] = currentPoint;
	}
	
	for( int i = 0; i < numberOfActivePoints; i++ )
	{
		rotated = rotation * starPositions[ i ];
		
		starField[ i ].x = rotated.x;
		starField[ i ].y = rotated.y;
		starField[ i ].z = rotated.z;
	}
}
