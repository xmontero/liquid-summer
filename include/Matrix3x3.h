#ifndef LIQUID_SUMMER_MATRIX3X3_H
#define LIQUID_SUMMER_MATRIX3X3_H

#include "Vector3d.h"

//     | a11 a12 a13 |   | a[1][1] a[1][2] a[1][3] |
// A = | a21 a22 a23 | = | a[2][1] a[2][2] a[2][3] | = | a[i][j] |, i={1,2,3}, j={1,2,3}
//     | a31 a32 a33 |   | a[3][1] a[3][2] a[3][3] |

class Matrix3x3
{
	private:
		
		double a[ 3 ][ 3 ];
		
	public:
		
		Matrix3x3();
		void identity( void );
		void createRotationX( double angle );
		void createRotationY( double angle );
		void createRotationZ( double angle );
		void createRotationXYZ( double angleX, double angleY, double angleZ );
		//Matrix3x3 & operator +( const Matrix3x3 & rhs );
		Matrix3x3 & operator *( const Matrix3x3 & rhs );
		Vector3d operator *( const Vector3d & rhs );
		double getValue( int i, int j ) const;
		void setValue( double value, int i, int j );
		Vector3d getColumnVector( int j ) const;
		Vector3d getRowVector( int i ) const;
		void setColumnVector( const Vector3d & value, int j );
};

#endif
