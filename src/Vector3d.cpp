#include "Vector3d.h"
#include "Math.h"

#include <random>

Vector3d::Vector3d()
{
	zero();
}

Vector3d::Vector3d( double newX, double newY, double newZ )
{
	setXYZ( newX, newY, newZ );
}

void Vector3d::zero( void )
{
	setXYZ( 0, 0 ,0 );
}

Vector3d & Vector3d::setXYZ( double newX, double newY, double newZ )
{
	x = newX;
	y = newY;
	z = newZ;
	
	return ( * this );
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

void Vector3d::scale( double k )
{
	x *= k;
	y *= k;
	z *= k;
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

Vector3d Vector3d::operator+( const Vector3d & rhs ) const
{
	Vector3d result;
	
	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;
	
	return result;
}

Vector3d Vector3d::operator-( const Vector3d & rhs ) const
{
	Vector3d result;
	
	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;
	
	return result;
}

Vector3d & Vector3d::operator+=( const Vector3d & rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return * this;
}

double Vector3d::operator*( const Vector3d & rhs ) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}
