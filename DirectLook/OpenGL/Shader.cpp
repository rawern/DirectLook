#include "Shader.h"

namespace DirectLook
{
	Shader::Shader( const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename )
		:
		m_VertexShader( 0 ),
		m_FragmentShader( 0 ),
		m_ShaderProgram( 0 ),
		m_VertexShaderFilename( vertexShaderFilename ),
		m_FragmentShaderFilename( fragmentShaderFilename )
	{
	}

	Shader::~Shader(void)
	{
		// Delete complete shader program
		deleteShader();
	}

	GLuint Shader::compile(void)
	{
		// Generate vertex shader
		m_VertexShader = createShader( GL_VERTEX_SHADER, m_VertexShaderFilename.c_str() );
		if(m_VertexShader == 0)
		{
			return 0;
		}
		
		// Generate fragment shader
		m_FragmentShader = createShader( GL_FRAGMENT_SHADER, m_FragmentShaderFilename.c_str() );
		if(m_FragmentShader == 0)
		{
			return 0;
		}

		// Generate shader program
		m_ShaderProgram = createShaderProgram( m_VertexShader, m_FragmentShader );
		if(m_ShaderProgram == 0)
		{
			return 0;
		}

		// No errors
		return 1;
	}

	GLuint Shader::getVertexShader(void) const
	{
		return m_VertexShader;
	}

	GLuint Shader::getFragmentShader(void) const
	{
		return m_FragmentShader;
	}

	GLuint Shader::getShaderProgram(void) const
	{
		return m_ShaderProgram;
	}
	
	void Shader::enable(void)
	{
		// Activating the shader program and assigning uniforms
		glUseProgram( m_ShaderProgram );
	}

	void Shader::disable(void)
	{
		// Disable the shader program
		glUseProgram( 0 );
	}

	GLuint Shader::reload(void)
	{
		// Loesche den Shader Code aus dem Grafikspeicher und weise allen IDs den Wert 0 zu:
		deleteShader();
		m_VertexShader   = 0;
		m_FragmentShader = 0;
		m_ShaderProgram  = 0;

		// Create vertex shader
		m_VertexShader = createShader( GL_VERTEX_SHADER, m_VertexShaderFilename.c_str() );
		if(m_VertexShader == 0)
		{
			return 0;
		}
		
		// Create fragment shader
		m_FragmentShader = createShader( GL_FRAGMENT_SHADER, m_FragmentShaderFilename.c_str() );
		if(m_FragmentShader == 0)
		{
			return 0;
		}

		// Generate shader program
		m_ShaderProgram = createShaderProgram( m_VertexShader, m_FragmentShader );
		if(m_ShaderProgram == 0)
		{
			return 0;
		}

		// No errors
		return 1;
	}
	
	GLuint Shader::reload( const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename )
	{
		m_VertexShaderFilename = vertexShaderFilename;
		m_FragmentShaderFilename = fragmentShaderFilename;		
		return reload();
	}

	void Shader::deleteShader(void)
	{
		// Detach vertex and fragment shader code
		glDetachShader( m_ShaderProgram, m_FragmentShader );
		glDetachShader( m_ShaderProgram, m_VertexShader );
    
		// Delete fragment and vertex shader
		glDeleteShader( m_FragmentShader );
		glDeleteShader( m_VertexShader );

		// Delete shader program
		glDeleteProgram( m_ShaderProgram );
	}

	void Shader::setVertexAttribute( const VertexBufferObject* pVertexBuffer, const char* pParameter )
	{
		if(glGetAttribLocation( m_ShaderProgram, pParameter ) != -1)
		{
			// Enable shader atrribute
			GLuint attributeID = glGetAttribLocation( m_ShaderProgram, pParameter );
			glEnableVertexAttribArray( attributeID );

			// Setting up the vertex buffer object
			glBindBuffer( pVertexBuffer->getTarget(), pVertexBuffer->getID() );
			glVertexAttribPointer(
				attributeID,					// attribute
				pVertexBuffer->getLength(),		// size
				GL_FLOAT,						// type
				GL_FALSE,						// normalized?
				pVertexBuffer->getStride(),		// stride
				(void*) 0						// array buffer offset
			);
		}
	}

	void Shader::resetVertexAttribute( const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glDisableVertexAttribArray( glGetAttribLocation( m_ShaderProgram, pParameter ) );
		}
	}

	void Shader::setFloatValue( const float value, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glUniform1f( glGetUniformLocation( m_ShaderProgram, pParameter ), value );
		}
	}

	void Shader::setIntValue( const int value, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glUniform1i( glGetUniformLocation( m_ShaderProgram, pParameter ), value );
		}
	}

	void Shader::setVector2( const Vector2* pVector, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glUniform2f( glGetUniformLocation( m_ShaderProgram, pParameter ), pVector->x, pVector->y );
		}
	}

	void Shader::setVector3( const Vector3* pVector, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glUniform3f( glGetUniformLocation( m_ShaderProgram, pParameter ), pVector->x, pVector->y, pVector->z );
		}
	}

	void Shader::setVector4( const Vector4* pVector, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glUniform4f( glGetUniformLocation( m_ShaderProgram, pParameter ), pVector->x, pVector->y, pVector->z, pVector->w );
		}
	}

	void Shader::setMatrix( const Matrix* pMatrix, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			GLfloat data[16];
			data[0]  = pMatrix->m_11;	data[1]  = pMatrix->m_12;	data[2]  = pMatrix->m_13;	data[3]  = pMatrix->m_14;
			data[4]  = pMatrix->m_21;	data[5]  = pMatrix->m_22;	data[6]  = pMatrix->m_23;	data[7]  = pMatrix->m_24;
			data[8]  = pMatrix->m_31;	data[9]  = pMatrix->m_32;	data[10] = pMatrix->m_33;	data[11] = pMatrix->m_34;
			data[12] = pMatrix->m_41;	data[13] = pMatrix->m_42;	data[14] = pMatrix->m_43;	data[15] = pMatrix->m_44;

			glUniformMatrix4fv( glGetUniformLocation( m_ShaderProgram, pParameter ), 1, GL_FALSE, data );
		}
	}

	void Shader::setTexture( const TextureObject* pTexture, const long textureNr, const long stage, const char* pParameter )
	{
		if(glGetUniformLocation( m_ShaderProgram, pParameter ) != -1)
		{
			glActiveTexture( textureNr );
			glBindTexture( pTexture->getTarget(), pTexture->getID() );
			glUniform1i( glGetUniformLocation( m_ShaderProgram, pParameter ), stage );
		}
	}

	void* Shader::fileContents( const char* pFileName, GLint* pLength )
	{
		FILE* pFile = fopen( pFileName, "r" );
		void* pBuffer;

		if(!pFile)
		{
			fprintf( stderr, "Unable to open %s for reading\n", pFileName );
			return NULL;
		}

		fseek( pFile, 0, SEEK_END );
		*pLength = ftell( pFile );
		fseek( pFile, 0, SEEK_SET );

		pBuffer = malloc(*pLength + 1);
		*pLength = fread( pBuffer, 1, *pLength, pFile );
		fclose( pFile );
		((char*) pBuffer)[*pLength] = '\0';

		return pBuffer;
	}
	
	void Shader::showInfoLog( GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog )
	{
		GLint logLength;
		char* pLog;

		glGet__iv( object, GL_INFO_LOG_LENGTH, &logLength );
		pLog = (char*) malloc( logLength );
		glGet__InfoLog( object, logLength, NULL, pLog );
		fprintf( stderr, "%s", pLog );
		free( pLog );
	}

	GLuint Shader::createShader( GLenum type, const char* pFileName )
	{
		GLint length;
		char* pSource = (char*) fileContents( pFileName, &length );
		GLuint shader;
		GLint shaderOK;

		if(!pSource)
		{
			return 0;
		}
		
		shader = glCreateShader( type );
		glShaderSource( shader, 1, (const char**) &pSource, &length );
		free( pSource );
		glCompileShader( shader );

		glGetShaderiv( shader, GL_COMPILE_STATUS, &shaderOK );
		if(!shaderOK)
		{
			fprintf(stderr, "Failed to compile %s:\n", pFileName );
			showInfoLog( shader, glGetShaderiv, glGetShaderInfoLog );
			glDeleteShader( shader );
			return 0;
		}   

		// No errors return shader ID
		return shader;
	}

	GLuint Shader::createShaderProgram( GLuint vertexShader, GLuint pixelShader )
	{
		GLint programOK;

		GLuint program = glCreateProgram();
		glAttachShader( program, m_VertexShader );
		glAttachShader( program, m_FragmentShader );
		glLinkProgram( program );

		glGetProgramiv( program, GL_LINK_STATUS, &programOK );
		if(!programOK)
		{
			fprintf( stderr, "Failed to link shader program:\n" );
			showInfoLog( program, glGetProgramiv, glGetProgramInfoLog );
			glDeleteProgram( program );
			return 0;
		}

		return program;
	}
}
