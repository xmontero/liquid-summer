#ifndef LIQUID_SUMMER_FRACTAL_H
#define LIQUID_SUMMER_FRACTAL_H

#include "AffineTransformations.h"
#include "Math.h"

class Fractal
{
	private:
		
		static const int maxPoints = 100000;
		static const int maxReplicas = 10;
		//Matrix3x3 replicaTransforms[ maxReplicas ];
		//Vector3d replicaOffsets[ maxReplicas ];
		//double replicaProbabilityWeights[ maxReplicas ];
		Vector3d starPositions[ maxPoints ];
		
		int numberOfActiveReplicas = 2;
		int numberOfActivePoints = 0;
		
	public:
		
		AffineTransformations affineTransformations;
		Vector3d objectOffset;
		Vector3d starField[ maxPoints ];
		double rotationXAngle = 0.1;
		double rotationYAngle = 0.15;
		double rotationZAngle = 0;
		double rotationXAngularSpeed = 0.050;
		double rotationYAngularSpeed = 0.005;
		double rotationZAngularSpeed = 0.010;
		
	public:
		
		Fractal( int n );
		void step( void );
		
	private:
		
		void initAffineTransformations( void );
};

#endif
