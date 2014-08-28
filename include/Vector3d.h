#ifndef LIQUID_SUMMER_VECTOR3D_H
#define LIQUID_SUMMER_VECTOR3D_H

class Vector3d
{
	public:
		
		double x;
		double y;
		double z;
		
	public:
		
		Vector3d();
		Vector3d( double x, double y, double z );
		void zero( void );
		Vector3d & setXYZ( double x, double y, double z );
		void randomize( double maxModulus );
		void setModulusZenithAndAzimuth( double modulus, double thetaZenith, double phiAzimuth );
		double getModulus();
		double getModulusSquared();
		void scale( double k );
		Vector3d operator +( const Vector3d & rhs ) const;
		Vector3d operator -( const Vector3d & rhs ) const;
		Vector3d & operator +=( const Vector3d & rhs );
		double operator *( const Vector3d & rhs ) const;
};

#endif
