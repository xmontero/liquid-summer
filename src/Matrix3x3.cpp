#include "Matrix3x3.h"
#include "Math.h"

Matrix3x3::Matrix3x3()
{
	identity();
}

Matrix3x3 & Matrix3x3::identity( void )
{
	for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			a[ i ][ j ] = ( i == j ) ? 1 : 0;
		}
	}
	
	return ( * this );
}

Matrix3x3 & Matrix3x3::createRotationX( double angle )
{
	//      |  1    0        0     |
	// Rx = |  0  cos(a)  -sin(a)  |
	//      |  0  sin(a)   cos(a)  |
	
	identity();
	a[ 1 ][ 1 ] = cos( angle );
	a[ 1 ][ 2 ] = -sin( angle );
	a[ 2 ][ 1 ] = sin( angle );
	a[ 2 ][ 2 ] = cos( angle );

	return ( * this );
}

Matrix3x3 & Matrix3x3::createRotationY( double angle )
{
	//      |   cos(b)  0  sin(b)  |
	// Ry = |     0     1    0     |
	//      |  -sin(b)  0  cos(b)  |
	
	identity();
	a[ 0 ][ 0 ] = cos( angle );
	a[ 0 ][ 2 ] = sin( angle );
	a[ 2 ][ 0 ] = -sin( angle );
	a[ 2 ][ 2 ] = cos( angle );
	
	return ( * this );
}

Matrix3x3 & Matrix3x3::createRotationZ( double angle )
{
	//      |  cos(c)  -sin(c)  0  |
	// Rz = |  sin(c)   cos(c)  0  |
	//      |    0        0     1  |
	
	identity();
	a[ 0 ][ 0 ] = cos( angle );
	a[ 0 ][ 1 ] = -sin( angle );
	a[ 1 ][ 0 ] = sin( angle );
	a[ 1 ][ 1 ] = cos( angle );
	
	return ( * this );
}

Matrix3x3 & Matrix3x3::createRotationXYZ( double angleX, double angleY, double angleZ )
{
	Matrix3x3 rX;
	Matrix3x3 rY;
	Matrix3x3 rZ;
	
	rX.createRotationX( angleX );
	rY.createRotationY( angleY );
	rZ.createRotationZ( angleZ );
	
	( * this ) = ( rX * rY ) * rZ;
	
	return ( * this );
}

Matrix3x3 & Matrix3x3::createScaleXYZ( double scaleX, double scaleY, double scaleZ )
{
	identity();
	a[ 0 ][ 0 ] = scaleX;
	a[ 1 ][ 1 ] = scaleY;
	a[ 2 ][ 2 ] = scaleZ;
	
	return ( * this );
}

Matrix3x3 & Matrix3x3::scale( double scale )
{
	for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			a[ i ][ j ] *= scale;
		}
	}
	
	return ( * this );
}

/*
Matrix3x3 & Matrix3x3::operator +( const Matrix3x3 & rhs )
{
	for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			a[ i ][ j ] += rhs.getValue( i, j );
		}
	}
	
	return * this;
}
*/

Matrix3x3 & Matrix3x3::operator *( const Matrix3x3 & rhs )
{
	Vector3d result[ 3 ];
	
	for( int j = 0; j < 3; j++ )
	{
		result[ j ] = ( * this ) * rhs.getColumnVector( j + 1 );
	}
	
	for( int j = 0; j < 3; j++ )
	{
		setColumnVector( result[ j ], j + 1 );
	}
	
	return * this;
}

Vector3d Matrix3x3::operator *( const Vector3d & rhs )
{
	double resultComponents[ 3 ];
	Vector3d result;
	
	for( int i = 0; i < 3; i++ )
	{
		resultComponents[ i ] = this->getRowVector( i + 1 ) * rhs;
	}
	
	result.x = resultComponents[ 0 ];
	result.y = resultComponents[ 1 ];
	result.z = resultComponents[ 2 ];
	
	return result;
}

double Matrix3x3::getValue( int i, int j ) const
{
	return a[ i - 1 ][ j - 1 ];
}

Vector3d Matrix3x3::getColumnVector( int j ) const
{
	Vector3d result;
	
	result.x = a[ 0 ][ j - 1 ];
	result.y = a[ 1 ][ j - 1 ];
	result.z = a[ 2 ][ j - 1 ];
	
	return result;
}

Vector3d Matrix3x3::getRowVector( int i ) const
{
	Vector3d result;
	
	result.x = a[ i - 1 ][ 0 ];
	result.y = a[ i - 1 ][ 1 ];
	result.z = a[ i - 1 ][ 2 ];
	
	return result;
}

void Matrix3x3::setColumnVector( const Vector3d & value, int j )
{
	a[ 0 ][ j - 1 ] = value.x;
	a[ 1 ][ j - 1 ] = value.y;
	a[ 2 ][ j - 1 ] = value.z;
}

void Matrix3x3::setRowVector( const Vector3d & value, int i )
{
	a[ i - 1 ][ 0 ] = value.x;
	a[ i - 1 ][ 1 ] = value.y;
	a[ i - 1 ][ 2 ] = value.z;
}
