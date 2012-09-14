#include "Vector2.h"

namespace DirectLook
{
	Vector2::Vector2(void) : x( 0.0f ), y( 0.0f )
	{
	}

	Vector2::Vector2( const Vector2& copy ) : x( copy.x ), y( copy.y )
	{
	}

	Vector2::Vector2( const float x, const float y ) : x( x ), y( y )
	{
	}

	Vector2::~Vector2(void)
	{
	}

	Vector2 Vector2::perpendicular(void) const
	{
		Vector2 result;
		float length = (float) sqrt( x * x + y * y );
		if( length > 0 )
		{
			float xTmp = x;
			result.x = -(y / length);
			result.y = xTmp / length;
		}
		
		return( result ) ;
	}

	float Vector2::length(void) const
	{
		return sqrt( x * x + y * y );
	}

	float Vector2::squareLength(void) const
	{
		return( x * x + y * y );
	}

	float Vector2::angle( const Vector2& vector ) const
	{
		return acosf( getNormalize().dot( vector.getNormalize() ) ) * (float)RAD_TO_DEG;
	}

	float Vector2::angleRad( const Vector2& vector ) const
	{
		return acosf( getNormalize().dot( vector.getNormalize() ) );
	}

	float Vector2::dot( const Vector2& vector ) const
	{
		return x * vector.x + y * vector.y;
	}

	void Vector2::scale( const float scale )
	{
		x *= scale;
		y *= scale;
	}

	void Vector2::scale( const float scaleX, const float scaleY )
	{
		x *= scaleX;
		y *= scaleY;
	}

	Vector2 Vector2::getScale( const float scale ) const
	{
		return Vector2( x * scale, y * scale );
	}

	void Vector2::scaleNormalized( const float length )
	{
		float l = sqrt( x * x + y * y );
		if(l > 0)
		{
			x = (x / l) * length;
			y = (y / l) * length;
		}
	}

	Vector2 Vector2::getScaleNormalized( const float length ) const
	{
		float l = sqrt( x * x + y * y );
		if(l > 0)
		{
			return Vector2( (x / l) * length, (y / l) * length );
		}

		return Vector2( x, y );
	}

	void Vector2::normalize(void)
	{
		float length = sqrt( x * x + y * y );
		if(length > 0)
		{
			x /= length;
			y /= length;
		}
	}

	Vector2 Vector2::getNormalize(void) const
	{
		Vector2 result( x, y );
		float length = sqrt( x * x + y * y );
		if(length > 0)
		{
			result.x /= length;
			result.y /= length;
		}
	
		return( result );
	}

	Vector2 Vector2::middle( const Vector2& vector ) const
	{
		Vector2 result;
		result.x = (x + vector.x) / 2.0f;
		result.y = (y + vector.y) / 2.0f;

		return( result );
	}

	float Vector2::distance( const Vector2& vector ) const
	{
		float vX = x - vector.x;
		float vY = y - vector.y;

		return sqrt( vX * vX + vY * vY );
	}
	
	float Vector2::squareDistance( const Vector2& vector ) const
	{
		float vX = x - vector.x;
		float vY = y - vector.y;

		return( vX * vX + vY * vY );
	}

	Vector2 Vector2::operator-(void) const
	{
		return Vector2( -x, -y );
	}

	bool Vector2::operator==( const Vector2& vector ) const
	{
		return (x == vector.x) && (y == vector.y);
	}

	bool Vector2::operator!=( const Vector2& vector ) const
	{
		return (x != vector.x) || (y != vector.y);
	}

	void Vector2::operator=( const Vector2& vector )
	{
		x = vector.x;
		y = vector.y;
	}

	Vector2 Vector2::operator+( const Vector2& vector ) const
	{
		return Vector2( x + vector.x, y + vector.y );
	}

	Vector2& Vector2::operator+=( const Vector2& vector )
	{
		x += vector.x;
		y += vector.y;
	
		return( *this );
	}

	Vector2 Vector2::operator-( const Vector2& vector) const
	{
		return Vector2( x - vector.x, y - vector.y );
	}

	Vector2& Vector2::operator-=( const Vector2& vector )
	{
		x -= vector.x;
		y -= vector.y;
	
		return( *this );
	}

	float Vector2::operator*( const Vector2& vector ) const
	{
		return x * vector.x + y * vector.y;
	}

	float Vector2::operator/( const Vector2& vector ) const
	{
		return x / vector.x + y / vector.y;
	}

	void Vector2::operator=( const float value )
	{
		x = value;
		y = value;
	}

	Vector2 Vector2::operator+( const float value ) const
	{
		return Vector2( x + value, y + value );
	}

	Vector2& Vector2::operator+=( const float value )
	{
		x += value;
		y += value;

		return( *this );
	}

	Vector2 Vector2::operator-( const float value) const
	{
		return Vector2( x - value, y - value );
	}

	Vector2& Vector2::operator-=( const float value )
	{
		x -= value;
		y -= value;
	
		return( *this );
	}

	Vector2 Vector2::operator*( const float value ) const
	{
		return Vector2( x * value, y * value );
	}

	Vector2& Vector2::operator*=( const float value )
	{
		x *= value;
		y *= value;
	
		return( *this );
	}

	Vector2 Vector2::operator/( const float value ) const
	{
		if(value == 0)
		{
			return Vector2( x, y );
		}

		return Vector2( x / value, y / value );
	}

	Vector2& Vector2::operator/=( const float value )
	{
		if(value == 0)
		{
			return( *this );
		}
	
		x /= value;
		y /= value;
	
		return( *this );
	}

	Vector2 operator*( float value, const Vector2& vector )
	{
		return Vector2( value * vector.x, value * vector.y );
	}
};
