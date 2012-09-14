#include "Vector3.h"

namespace DirectLook
{
	Vector3::Vector3(void) : x( 0.0f ), y( 0.0f ), z( 0.0f )
	{
	}

	Vector3::Vector3( const Vector3& copy ) : x( copy.x ), y( copy.y ), z( copy.z )
	{
	}

	Vector3::Vector3( const float x, const float y, const float z ) : x( x ), y( y ), z( z )
	{
	}

	Vector3::~Vector3(void)
	{
	}

	Vector3 Vector3::perpendicular( const Vector3& vector ) const
	{
		Vector3 result;
		float crossX = y * vector.z - z * vector.y;
		float crossY = z * vector.x - x * vector.z;
		float crossZ = x * vector.y - y * vector.x;

		float length = sqrt( crossX * crossX + crossY * crossY + crossZ * crossZ );

		if(length > 0)
		{
			result.x = crossX / length;
			result.y = crossY / length;
			result.z = crossZ / length;
		}
		else
		{
			result.x = 0.0f;
			result.y = 0.0f;
			result.z = 0.0f;
		}

		return( result );
	}

	float Vector3::length(void) const
	{
		return sqrt( x * x + y * y + z * z );
	}

	float Vector3::squareLength(void) const
	{
		return( x * x + y * y + z * z );
	}

	float Vector3::angle( const Vector3& vector ) const
	{
		return acosf( getNormalize().dot( vector.getNormalize() ) ) * (float)RAD_TO_DEG;
	}

	float Vector3::angleRad( const Vector3& vector ) const
	{
		return acosf( getNormalize().dot( vector.getNormalize() ) );
	}

	float Vector3::dot( const Vector3& vector ) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	void Vector3::scale( const float scale )
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	void Vector3::scale( const float scaleX, const float scaleY, const float scaleZ )
	{
		x *= scaleX;
		y *= scaleY;
		z *= scaleZ;
	}

	Vector3 Vector3::getScale( const float scale ) const
	{
		return Vector3( x * scale, y * scale, z * scale );
	}

	void Vector3::scaleNormalized( const float length )
	{
		float l = sqrt( x * x + y * y + z * z );
		if(l > 0)
		{
			x = (x / l) * length;
			y = (y / l) * length;
			z = (z / l) * length;
		}
	}

	Vector3 Vector3::getScaleNormalized( const float length ) const
	{
		float l = sqrt( x * x + y * y + z * z );
		if(l > 0)
		{
			return Vector3( (x / l) * length, (y / l) * length, (z / l) * length );
		}

		return Vector3( x, y, z );
	}

	void Vector3::normalize(void)
	{
		float length = sqrt( x * x + y * y + z * z );
		if(length > 0)
		{
			x /= length;
			y /= length;
			z /= length;
		}
	}

	Vector3 Vector3::getNormalize(void) const
	{
		Vector3 result( x, y, z );
		float length = sqrt( x * x + y * y + z * z);
		if(length > 0)
		{
			result.x /= length;
			result.y /= length;
			result.z /= length;
		}
	
		return( result );
	}

	Vector3 Vector3::middle( const Vector3& vector ) const
	{
		Vector3 result;
		result.x = (x + vector.x) / 2.0f;
		result.y = (y + vector.y) / 2.0f;
		result.z = (z + vector.z) / 2.0f;

		return( result );
	}

	float Vector3::distance( const Vector3& vector ) const
	{
		float vX = x - vector.x;
		float vY = y - vector.y;
		float vZ = z - vector.z;

		return sqrt( vX * vX + vY * vY + vZ * vZ );
	}
	
	float Vector3::squareDistance( const Vector3& vector ) const
	{
		float vX = x - vector.x;
		float vY = y - vector.y;
		float vZ = z - vector.z;
	
		return( vX * vX + vY * vY + vZ * vZ );
	}

	Vector3 Vector3::cross( const Vector3& vector ) const
	{
		Vector3 result;

		result.x = y * vector.z - z * vector.y;
		result.y = z * vector.x - x * vector.z;
		result.z = x * vector.y - y * vector.x;

		return( result );
	}

	Vector3 Vector3::operator-(void) const
	{
		return Vector3( -x, -y, -z );
	}

	bool Vector3::operator==( const Vector3& vector ) const
	{
		return (x == vector.x) && (y == vector.y) && (z == vector.z);
	}

	bool Vector3::operator!=( const Vector3& vector ) const
	{
		return (x != vector.x) || (y != vector.y) || (z != vector.z);
	}

	void Vector3::operator=( const Vector3& vector )
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
	}

	Vector3 Vector3::operator+( const Vector3& vector ) const
	{
		return Vector3( x + vector.x, y + vector.y, z + vector.z );
	}

	Vector3& Vector3::operator+=( const Vector3& vector )
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return( *this );
	}

	Vector3 Vector3::operator-( const Vector3& vector) const
	{
		return Vector3( x - vector.x, y - vector.y, z - vector.z );
	}

	Vector3& Vector3::operator-=( const Vector3& vector )
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return( *this );
	}

	float Vector3::operator*( const Vector3& vector ) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	float Vector3::operator/( const Vector3& vector ) const
	{
		return x / vector.x + y / vector.y + z / vector.z;
	}

	void Vector3::operator=( const float value )
	{
		x = value;
		y = value;
		z = value;
	}

	Vector3 Vector3::operator+( const float value ) const
	{
		return Vector3( x + value, y + value, z + value );
	}

	Vector3& Vector3::operator+=( const float value )
	{
		x += value;
		y += value;
		z += value;

		return( *this );
	}

	Vector3 Vector3::operator-( const float value) const
	{
		return Vector3( x - value, y - value, z - value );
	}

	Vector3& Vector3::operator-=( const float value )
	{
		x -= value;
		y -= value;
		z -= value;
	
		return( *this );
	}

	Vector3 Vector3::operator*( const float value ) const
	{
		return Vector3( x * value, y * value, z * value );
	}

	Vector3& Vector3::operator*=( const float value )
	{
		x *= value;
		y *= value;
		z *= value;

		return( *this );
	}

	Vector3 Vector3::operator/( const float value ) const
	{
		if(value == 0)
		{
			return Vector3( x, y, z );
		}

		return Vector3( x / value, y / value, z / value );
	}

	Vector3& Vector3::operator/=( const float value )
	{
		if(value == 0)
		{
			return( *this );
		}
	
		x /= value;
		y /= value;
		z /= value;

		return( *this );
	}

	Vector3 operator*( float value, const Vector3& vector )
	{
		return Vector3( value * vector.x, value * vector.y, value * vector.z );
	}
}
