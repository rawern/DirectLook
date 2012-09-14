#include "GLCamera.h"

namespace DirectLook
{
	GLCamera::GLCamera(void)
		:
		m_Direction( 0.0f, 0.0f, 0.0f ),
		m_Position( 0.0f, 0.0f, 2.0f ),
		m_WorldUp( 0.0f, 1.0f, 0.0f ),
		m_LookAt( 0.0f, 0.0f, 0.0f ),
		
		m_FieldOfView( (GLfloat) HALF_PI ),
		m_AspectRatio( 4.0f / 3.0f ),
		m_NearClipPlane( 0.5f ),
		m_FarClipPlane( 5000.0f )
	{
		update();
	}

	GLCamera::GLCamera( const GLCamera& copy )
		:
		m_Direction( copy.m_Direction ),
		m_Position( copy.m_Position ),
		m_WorldUp( copy.m_WorldUp ),
		m_LookAt( copy.m_LookAt ),
		
		m_FieldOfView( copy.m_FieldOfView ),
		m_AspectRatio( copy.m_AspectRatio ),
		m_NearClipPlane( copy.m_NearClipPlane ),
		m_FarClipPlane( copy.m_FarClipPlane ),

		m_MatView( copy.m_MatView ),
		m_MatProjection( copy.m_MatProjection ),
		m_MatViewProjection( copy.m_MatViewProjection ),
		m_MatRotation( copy.m_MatRotation )
	{
	}

	GLCamera::GLCamera( GLfloat fieldOfView, GLfloat aspectRatio, GLfloat nearClipPlane, GLfloat farClipPlane )
		:
		m_Direction( 0.0f, 0.0f, 0.0f ),
		m_Position( 0.0f, 0.0f, 2.0f ),
		m_WorldUp( 0.0f, 1.0f, 0.0f ),
		m_LookAt( 0.0f, 0.0f, 0.0f ),
		
		m_FieldOfView( fieldOfView ),
		m_AspectRatio( aspectRatio ),
		m_NearClipPlane( nearClipPlane ),
		m_FarClipPlane( farClipPlane )
	{
		update();
	}

	GLCamera::~GLCamera(void)
	{
	}

	void GLCamera::update(void)
	{
		m_Direction = m_LookAt - m_Position;
		m_Direction.normalize();

		lookAtRightHand( &m_MatView, &m_Position, &m_LookAt, &m_WorldUp );
		//perspectiveFovRightHand( &m_MatProjection, m_FieldOfView, m_AspectRatio, m_NearClipPlane, m_FarClipPlane );
		orthoRightHand( &m_MatProjection, 640.f, 480.0f, m_NearClipPlane, m_FarClipPlane );
		m_MatViewProjection = m_MatView * m_MatProjection;
	}
	
	void GLCamera::addToCamera( float strafe, float upDown, float forBack )
	{
		Vector3 direction = m_Direction;
		Vector3 orthogonal( -direction.z, 0.0f, direction.x );
		orthogonal *= strafe;

		direction *= forBack;
		Vector3 vectorUpDown( 0.0f, 1.0f * upDown, 0.0f );

		m_LookAt   = m_LookAt   + direction + vectorUpDown + orthogonal;
		m_Position = m_Position + direction + vectorUpDown + orthogonal;

		update();
	}
	
	void GLCamera::rotateAroundPosition( float xAngle, float yAngle )
	{
		Matrix rotationMatrix;

		// Rotation left/right
		m_LookAt = m_LookAt - m_Position;
		rotationAxis( &rotationMatrix, &Vector3( 0.0f, 1.0f, 0.0f ), xAngle );
		multiplyVector3WithRotationMatrix( &m_LookAt, &Vector3( m_LookAt ), &rotationMatrix );
		m_LookAt = m_LookAt + m_Position;

		m_Direction = m_LookAt - m_Position;
		m_Direction.normalize();
		m_MatRotation = rotationMatrix;

		// Rotation up/down
		Vector3 orthogonal( -m_Direction.z, 0.0f, m_Direction.x );

		m_LookAt = m_LookAt - m_Position;
		rotationAxis( &rotationMatrix, &orthogonal, yAngle );
		multiplyVector3WithRotationMatrix( &m_LookAt, &Vector3( m_LookAt ), &rotationMatrix );
		m_LookAt = m_LookAt + m_Position;
		
		m_MatRotation *= rotationMatrix;
		update();
	}

	void GLCamera::reset(void)
	{
		m_Direction = Vector3( 0.0f, 0.0f, 0.0f );
		m_Position	= Vector3( 0.0f, 0.0f, 2.0f );
		m_WorldUp	= Vector3( 0.0f, 1.0f, 0.0f );
		m_LookAt	= Vector3( 0.0f, 0.0f, 0.0f );
		
		m_MatRotation.identity();
		update();
	}
}
