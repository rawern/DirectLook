#include "Vector4.h"

namespace DirectLook
{
	Vector4::Vector4(void) : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 1.0f )
	{
	}

	Vector4::Vector4( const Vector4& copy ) : x( copy.x ), y( copy.y ), z( copy.z ), w( copy.w ) 
	{
	}

	Vector4::Vector4( const float x, const float y, const float z, const float w ) : x( x ), y( y ), z( z ), w( w )
	{
	}

	Vector4::~Vector4(void)
	{
	}

	float Vector4::length(void) const
	{
		return sqrt( x * x + y * y + z * z + w * w );
	}

	float Vector4::squareLength(void) const
	{
		return( x * x + y * y + z * z + w * w );
	}

	float Vector4::angle( const Vector4& vector ) const
	{
		return acosf( getNormalize().dot( vector.getNormalize() ) ) * (float)RAD_TO_DEG;
	}

	float Vector4::angleRad( const Vector4& vector ) const
	{
		return acosf( getNormalize().dot( vector.getNormalize() ) );
	}

	float Vector4::dot( const Vector4& vector ) const
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	void Vector4::scale( const float scale )
	{
		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
	}

	void Vector4::scale( const float scaleX, const float scaleY, const float scaleZ, const float scaleW )
	{
		x *= scaleX;
		y *= scaleY;
		z *= scaleZ;
		w *= scaleW;
	}

	Vector4 Vector4::getScale( const float scale ) const
	{
		return Vector4( x * scale, y * scale, z * scale, w * scale );
	}

	void Vector4::scaleNormalized( const float length )
	{
		float l = sqrt( x * x + y * y + z * z + w * w );
		if(l > 0)
		{
			x = (x / l) * length;
			y = (y / l) * length;
			z = (z / l) * length;
			w = (w / l) * length;
		}
	}

	Vector4 Vector4::getScaleNormalized( const float length ) const
	{
		float l = sqrt( x * x + y * y + z * z + w * w );
		if(l > 0)
		{
			return Vector4( (x / l) * length, (y / l) * length, (z / l) * length, (w / l) * length );
		}

		return Vector4( x, y, z, w );
	}

	void Vector4::normalize(void)
	{
		float length = sqrt( x * x + y * y + z * z + w * w );
		if(length > 0)
		{
			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}
	}

	Vector4 Vector4::getNormalize(void) const
	{
		Vector4 result( x, y, z, w );
		float length = sqrt( x * x + y * y + z * z + w * w);
		if(length > 0)
		{
			result.x /= length;
			result.y /= length;
			result.z /= length;
			result.w /= length;
		}
	
		return( result );
	}

	Vector4 Vector4::middle( const Vector4& vector ) const
	{
		Vector4 result;
		result.x = (x + vector.x) / 2.0f;
		result.y = (y + vector.y) / 2.0f;
		result.z = (z + vector.z) / 2.0f;
		result.w = (w + vector.w) / 2.0f;

		return( result );
	}

	float Vector4::distance( const Vector4& vector ) const
	{
		float vX = x - vector.x;
		float vY = y - vector.y;
		float vZ = z - vector.z;
		float vW = w - vector.w;

		return sqrt( vX * vX + vY * vY + vZ * vZ + vW * vW );
	}
	
	float Vector4::squareDistance( const Vector4& vector ) const
	{
		float vX = x - vector.x;
		float vY = y - vector.y;
		float vZ = z - vector.z;
		float vW = w - vector.w;
	
		return( vX * vX + vY * vY + vZ * vZ + vW * vW );
	}

	Vector4 Vector4::cross( const Vector4& vector2, const Vector4& vector3 ) const
	{
		Vector4 result;

		result.x =    y * (vector2.z * vector3.w - vector3.z * vector2.w) - z * (vector2.y * vector3.w - vector3.y * vector2.w) + w * (vector2.y * vector3.z - vector2.z * vector3.y);
		result.y = -( x * (vector2.z * vector3.w - vector3.z * vector2.w) - z * (vector2.x * vector3.w - vector3.x * vector2.w) + w * (vector2.x * vector3.z - vector3.x * vector2.z) );
		result.z =    x * (vector2.y * vector3.w - vector3.y * vector2.w) - y * (vector2.x * vector3.w - vector3.x * vector2.w) + w * (vector2.x * vector3.y - vector3.x * vector2.y);
		result.w = -( x * (vector2.y * vector3.z - vector3.y * vector2.z) - y * (vector2.x * vector3.z - vector3.x * vector2.z) + z * (vector2.x * vector3.y - vector3.x * vector2.y) );
	
		return( result );
	}

	Vector4 Vector4::operator-(void) const
	{
		return Vector4( -x, -y, -z, -w );
	}

	bool Vector4::operator==( const Vector4& vector ) const
	{
		return (x == vector.x) && (y == vector.y) && (z == vector.z) && (w == vector.w);
	}

	bool Vector4::operator!=( const Vector4& vector ) const
	{
		return (x != vector.x) || (y != vector.y) || (z != vector.z) || (w != vector.w);
	}

	void Vector4::operator=( const Vector4& vector )
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;
	}

	Vector4 Vector4::operator+( const Vector4& vector ) const
	{
		return Vector4( x + vector.x, y + vector.y, z + vector.z, w + vector.w );
	}

	Vector4& Vector4::operator+=( const Vector4& vector )
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;

		return( *this );
	}

	Vector4 Vector4::operator-( const Vector4& vector) const
	{
		return Vector4( x - vector.x, y - vector.y, z - vector.z, w - vector.w );
	}

	Vector4& Vector4::operator-=( const Vector4& vector )
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;

		return( *this );
	}

	float Vector4::operator*( const Vector4& vector ) const
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	float Vector4::operator/( const Vector4& vector ) const
	{
		return x / vector.x + y / vector.y + z / vector.z + w / vector.w;
	}

	void Vector4::operator=( const float value )
	{
		x = value;
		y = value;
		z = value;
		w = value;
	}

	Vector4 Vector4::operator+( const float value ) const
	{
		return Vector4( x + value, y + value, z + value, w + value );
	}

	Vector4& Vector4::operator+=( const float value )
	{
		x += value;
		y += value;
		z += value;
		w += value;

		return( *this );
	}

	Vector4 Vector4::operator-( const float value ) const
	{
		return Vector4( x - value, y - value, z - value, w - value );
	}

	Vector4& Vector4::operator-=( const float value )
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;

		return( *this );
	}

	Vector4 Vector4::operator*( const float value ) const
	{
		return Vector4( x * value, y * value, z * value, w * value );
	}

	Vector4& Vector4::operator*=( const float value )
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;

		return( *this );
	}

	Vector4 Vector4::operator/( const float value ) const
	{
		if(value == 0)
		{
			return Vector4( x, y, z, w );
		}

		return Vector4( x / value, y / value, z / value, w / value );
	}

	Vector4& Vector4::operator/=( const float value )
	{
		if(value == 0)
		{
			return( *this );
		}
	
		x /= value;
		y /= value;
		z /= value;
		w /= value;

		return( *this );
	}

	Vector4 operator*( float value, const Vector4& vector )
	{
		return Vector4( value * vector.x, value * vector.y, value * vector.z, value * vector.w );
	}
}
