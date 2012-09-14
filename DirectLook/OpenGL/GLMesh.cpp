#include "GLMesh.h"

namespace DirectLook
{
	GLMesh::GLMesh(void)
		:
		m_Position( 0.0f, 0.0f, 0.0f ),
		m_Rotation( 0.0f, 0.0f, 0.0f ),
		m_Scale( 1.0f, 1.0f, 1.0f ),
		m_pVertexBuffer( 0 ),
		m_pElementBuffer( 0 ),
		m_pShader( 0 ),
		m_pCamera( 0 )
	{
		initialize();
	}
		
	GLMesh::GLMesh( ElementBufferObject* pElementBuffer, VertexBufferObject* pVertexBuffer, Shader* pShader, GLCamera* pCamera )
		:
		m_Position( 0.0f, 0.0f, 0.0f ),
		m_Rotation( 0.0f, 0.0f, 0.0f ),
		m_Scale( 1.0f, 1.0f, 1.0f ),
		m_pVertexBuffer( 0 ),
		m_pElementBuffer( 0 ),
		m_pShader( 0 ),
		m_pCamera( 0 )
	{
		setElementBuffer( pElementBuffer );
		setVertexBuffer( pVertexBuffer );
		setShader( pShader );
		setCamera( pCamera );
		initialize();
	}

	GLMesh::~GLMesh(void)
	{
		deleteResources();
	}

	void GLMesh::initialize(void)
	{
		if(!m_IsInitialized)
		{
			m_IsInitialized = true;
			m_IsUpdated		= false;
			update();
		}
	}
		
	void GLMesh::update(void)
	{
		if(!m_IsUpdated)
		{
			Matrix matTemp;			// Temp matrix for rotations
			Matrix matRotate;		// Final rotation matrix

			// Create translation matrix;
			translation( &m_MatWorld, m_Position.x, m_Position.y, m_Position.z );

			// Create scaling matrix:
			scaling( &matTemp, m_Scale.x, m_Scale.y, m_Scale.z );
			m_MatWorld = matTemp * m_MatWorld;

			// X axis rotation:
			rotationX( &matTemp, m_Rotation.x );
			matRotate = matRotate * matTemp;
		
			// Y axis rotation
			rotationY( &matTemp, m_Rotation.y );
			matRotate = matRotate * matTemp;
		
			// Z axis rotation
			rotationZ( &matTemp, m_Rotation.z );
			matRotate = matRotate * matTemp;
 
			// Apply the rotation matrices to complete the world matrix:
			m_MatWorld = matRotate * m_MatWorld;

			// Model updated
			m_IsUpdated = true;
		}
	}
		
	void GLMesh::draw(void)
	{
		if(m_pShader != 0 && m_pCamera != 0)
		{
			// Activating the shader program and assigning uniforms
			m_pShader->enable();

			// Activating the camera view projection matrix uniform variable
			m_pShader->setMatrix( &m_pCamera->m_MatViewProjection, "matVP" );

			// Activating the GLMesh world matrix uniform variable
			m_pShader->setMatrix( &m_MatWorld, "matW" );

			// Enable and setting up the vertex buffer object
			m_pShader->setVertexAttribute( m_pVertexBuffer, "position" );
					
			// Submitting the rendering job with an element buffer object
			glBindBuffer( m_pElementBuffer->getTarget(), m_pElementBuffer->getID() );
			glDrawElements(
				GL_TRIANGLES,					// mode 
				m_pElementBuffer->getSize(),	// count
				GL_UNSIGNED_INT,				// type
				(void*) 0						// element array buffer offset
			);

			// Cleaning up after ourselves
			m_pShader->resetVertexAttribute( "position" );

			// Disable shader program
			m_pShader->disable();
		}
	}
		
	void GLMesh::deleteResources(void)
	{
		if(m_pElementBuffer) { delete m_pElementBuffer;	m_pElementBuffer = 0; }
		if(m_pVertexBuffer)	 { delete m_pVertexBuffer;	m_pVertexBuffer	 = 0; }
	}

	void GLMesh::setPosition( const float xPos, const float yPos, const float zPos )
	{
		m_Position.x = xPos;
		m_Position.y = yPos;
		m_Position.z = zPos;

		m_IsUpdated = false;
	}
	
	void GLMesh::setPosition( const Vector3& position )
	{
		m_Position = position;
		m_IsUpdated = false;
	}

	void GLMesh::setRotation( const float xAngle, const float yAngle, const float zAngle )
	{
		m_Rotation.x = xAngle;
		m_Rotation.y = yAngle;
		m_Rotation.z = zAngle;

		if(m_Rotation.x > TWO_PI) m_Rotation.x -= (float)TWO_PI;
		if(m_Rotation.y > TWO_PI) m_Rotation.y -= (float)TWO_PI;
		if(m_Rotation.z > TWO_PI) m_Rotation.z -= (float)TWO_PI;

		m_IsUpdated = false;
	}

	void GLMesh::setRotation( const Vector3& rotation )
	{
		this->setRotation( rotation.x, rotation.y, rotation.z );
	}

	void GLMesh::setScale( const float xScale, const float yScale, const float zScale )
	{
		if(xScale >= 0.0f)	m_Scale.x = xScale;
		if(yScale >= 0.0f)	m_Scale.y = yScale;
		if(zScale >= 0.0f)	m_Scale.z = zScale;

		m_IsUpdated = false;
	}

	void GLMesh::setScale( const Vector3& scale )
	{
		this->setScale( scale.x, scale.y, scale.z );
	}

	void GLMesh::translate( const float xPos, const float yPos, const float zPos )
	{
		m_Position.x += xPos;
		m_Position.y += yPos;
		m_Position.z += zPos;

		m_IsUpdated = false;
	}

	void GLMesh::translate( const Vector3& translate )
	{
		this->translate( translate.x, translate.y, translate.z );
	}

	void GLMesh::rotate( const float xAngle, const float yAngle, const float zAngle )
	{
		m_Rotation.x += xAngle;
		m_Rotation.y += yAngle;
		m_Rotation.z += zAngle;

		if(m_Rotation.x > TWO_PI) m_Rotation.x -= (float)TWO_PI;
		if(m_Rotation.y > TWO_PI) m_Rotation.y -= (float)TWO_PI;
		if(m_Rotation.z > TWO_PI) m_Rotation.z -= (float)TWO_PI;

		m_IsUpdated = false;
	}

	void GLMesh::rotate( const Vector3& rotate )
	{
		this->rotate( rotate.x, rotate.y, rotate.z );
	}

	void GLMesh::scale( const float xScale, const float yScale, const float zScale )
	{
		if((m_Scale.x + xScale) >= 0.0f) m_Scale.x += xScale;
		if((m_Scale.y + yScale) >= 0.0f) m_Scale.y += yScale;
		if((m_Scale.z + zScale) >= 0.0f) m_Scale.z += zScale;		
		
		m_IsUpdated = false;
	}

	void GLMesh::scale( const Vector3& scale )
	{
		this->scale( scale.x, scale.y, scale.z );
	}

	void GLMesh::setElementBuffer( ElementBufferObject* pElementBuffer )
	{
		if(pElementBuffer)
		{
			m_pElementBuffer = pElementBuffer;
		}
	}

	void GLMesh::setVertexBuffer( VertexBufferObject* pVertexBuffer )
	{
		if(pVertexBuffer)
		{
			m_pVertexBuffer = pVertexBuffer;
		}
	}

	void GLMesh::setShader( Shader* pShader )
	{
		if(pShader)
		{
			m_pShader = pShader;
		}
	}

	void GLMesh::setCamera( GLCamera* pCamera )
	{
		if(pCamera)
		{
			m_pCamera = pCamera;
		}
	}

	const ElementBufferObject* GLMesh::getElementBuffer(void) const
	{
		return m_pElementBuffer;
	}

	const VertexBufferObject* GLMesh::getVertexBuffer(void) const
	{
		return m_pVertexBuffer;
	}
	
	const Shader* GLMesh::getShader(void) const
	{
		return m_pShader;
	}

	const GLCamera* GLMesh::getCamera(void) const
	{
		return m_pCamera;
	}
};
