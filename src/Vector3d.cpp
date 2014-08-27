#include "Vector3d.h"
#include "Math.h"

#include <random>

Vector3d::Vector3d()
{
	zero();
}

void Vector3d::zero( void )
{
	x = 0;
	y = 0;
	z = 0;
}

void Vector3d::randomize( double maxModulus )
{
	double modulus;
	double thetaZenith;
	double phiAzimuth;
	
	modulus = ( rand() / ( double( RAND_MAX ) / maxModulus ) );
	thetaZenith = ( rand() / ( double( RAND_MAX ) / pi ) );
	phiAzimuth = ( rand() / ( double( RAND_MAX ) / ( 2 * pi ) ) );
	
	setModulusZenithAndAzimuth( modulus, thetaZenith, phiAzimuth );
}

void Vector3d::setModulusZenithAndAzimuth( double modulus, double thetaZenith, double phiAzimuth )
{
	x = modulus * sin( thetaZenith ) * cos( phiAzimuth );
	y = modulus * sin( thetaZenith ) * sin( phiAzimuth );
	z = modulus * cos( thetaZenith );
}

double Vector3d::getModulusSquared( void )
{
	return x * x + y * y + z * z;
}

double Vector3d::getModulus( void )
{
	double modulusSquared = getModulusSquared();
	return sqrt( modulusSquared );
}

Vector3d & Vector3d::operator+=( const Vector3d & rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return * this;
}

double Vector3d::operator*( const Vector3d & rhs )
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}
