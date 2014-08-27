#ifndef LIQUID_SUMMER_STARFIELD_H
#define LIQUID_SUMMER_STARFIELD_H

#include "Math.h"

class StarField
{
	private:
		
		static const int maxPoints = 100000;
		Vector3d starPositions[ maxPoints ];
		Vector3d starSpeeds[ maxPoints ];
		int numberOfActivePoints = 0;
		double rotationXAngle = 0.1;
		double rotationYAngle = 0.15;
		double rotationZAngle = 0;
		
	public:
		
		Vector3d starField[ maxPoints ];
		double rotationXAngularSpeed = 0.0050;
		double rotationYAngularSpeed = 0.0005;
		double rotationZAngularSpeed = 0.0000;
		
	public:
		
		StarField( int n );
		void step( void );
};

#endif
