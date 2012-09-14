#pragma once

#define _CRT_SECURE_NO_DEPRECATE 
#define _SCL_SECURE_NO_DEPRECATE

#include <GL/glew.h>
#include <iostream>
#include <string>

#include "../NonCopyable.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix.h"
#include "TextureObject.h"
#include "VertexBufferObject.h"

namespace DirectLook
{
	/// \brief Die Klasse Shader ist fuer das Laden, Kompilieren und Verwalten der Vertex- und Fragment-Shader-Programme verantwortlich.
	class Shader : public NonCopyable
	{

	private:
		GLuint m_VertexShader;					///< OpenGL Vertex-Shader ID
		GLuint m_FragmentShader;				///< OpenGL Fragment-Shader ID
		GLuint m_ShaderProgram;					///< OpenGL Shaderprogramm ID
		std::string m_VertexShaderFilename;		///< Dateipfad des Vertex-Shader Codes
		std::string m_FragmentShaderFilename;	///< Dateipfad des Fragment-Shader Codes

	public:
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein Shader-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param vertexShaderFilename   Dateipfad des Vertex-Shader Codes
		/// \param fragmentShaderFilename Dateipfad des Fragment-Shader Codes
		///
		////////////////////////////////////////////////////////////
		Shader( const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Loescht das Shader-Obekt aus dem Videospeicher der Grafikkarte.
		///
		////////////////////////////////////////////////////////////
		~Shader(void);

		////////////////////////////////////////////////////////////
		/// \brief Laedt und kompiliert das Shaderprogramm.
		///
		/// \return Shaderprogramm ID
		///
		////////////////////////////////////////////////////////////
		GLuint compile(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Vertex-Shader ID zurueck.
		///
		/// \return Vertex-Shader ID
		///
		////////////////////////////////////////////////////////////
		GLuint getVertexShader(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Fragment-Shader ID zurueck.
		///
		/// \return Fragment-Shader ID
		///
		////////////////////////////////////////////////////////////
		GLuint getFragmentShader(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert die aktuelle Shaderprogramm ID zurueck.
		///
		/// \return Shaderprogramm ID
		///
		////////////////////////////////////////////////////////////
		GLuint getShaderProgram(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Aktiviert das Shaderprogramm.
		////////////////////////////////////////////////////////////
		void enable(void);

		////////////////////////////////////////////////////////////
		/// \brief Deaktiviert das Shaderprogramm.
		////////////////////////////////////////////////////////////
		void disable(void);

		////////////////////////////////////////////////////////////
		/// \brief Laedt und kompiliert erneut das Shaderprogramm.
		///
		/// \return Shaderprogramm ID
		///
		////////////////////////////////////////////////////////////
		GLuint reload(void);

		////////////////////////////////////////////////////////////
		/// \brief Laedt und kompiliert erneut das Shaderprogramm.
		///
		/// \param vertexShaderFilename   Dateipfad des Vertex-Shader Codes
		/// \param fragmentShaderFilename Dateipfad des Fragment-Shader Codes
		///
		/// \return Shaderprogramm ID
		///
		////////////////////////////////////////////////////////////
		GLuint reload( const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename );

		////////////////////////////////////////////////////////////
		/// \brief Loescht das komplette Shaderprogramm aus dem Videospeicher der Grafikkarte.
		////////////////////////////////////////////////////////////
		void deleteShader(void);

		////////////////////////////////////////////////////////////////////////
		// Setter fuer den Vertex-Buffer, die Uniforms und den Textur-Objekten //
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt die Vertex-Buffer-Daten in den Videospeicher der Grafikkarte.
		///
		/// \param pVertexBuffer Vertex-Buffer
		/// \param pParameter	 Attributname des Vertex-Buffers im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setVertexAttribute( const VertexBufferObject* pVertexBuffer, const char* pParameter );

		////////////////////////////////////////////////////////////
		/// \brief Resetet die Vertex-Buffer-Daten im Videospeicher der Grafikkarte.
		///
		/// \param pParameter Attributname des Vertex-Buffers im Shader Code
		///
		////////////////////////////////////////////////////////////
		void resetVertexAttribute( const char* pParameter );
		
		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt einen Float-Wert als Uniform-Variable in den Videospeicher der Grafikkarte.
		///
		/// \param value 	  Float-Wert
		/// \param pParameter Attributname des Float-Wertes im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setFloatValue( const float value, const char* pParameter );

		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt einen Integer-Wert als Uniform-Variable in den Videospeicher der Grafikkarte.
		///
		/// \param value	  Integer-Wert
		/// \param pParameter Attributname des Integer-Wertes im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setIntValue (const int value, const char* pParameter );

		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt einen 2D-Vektor als Uniform-Variable in den Videospeicher der Grafikkarte.
		///
		/// \param pVector	  2D-Vektor
		/// \param pParameter Attributname des 2D-Vektors im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setVector2( const Vector2* pVector, const char* pParameter );

		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt einen 3D-Vektor als Uniform-Variable in den Videospeicher der Grafikkarte.
		///
		/// \param pVector	  3D-Vektor
		/// \param pParameter Attributname des 3D-Vektors im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setVector3( const Vector3* pVector, const char* pParameter );
		
		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt einen 4D-Vektor als Uniform-Variable in den Videospeicher der Grafikkarte.
		///
		/// \param pVector	  4D-Vektor
		/// \param pParameter Attributname des 4D-Vektors im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setVector4( const Vector4* pVector, const char* pParameter );
		
		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt eine Matrix als Uniform-Variable in den Videospeicher der Grafikkarte.
		///
		/// \param pMatrix	  4x4-Matrix
		/// \param pParameter Attributname der Matrix im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setMatrix( const Matrix* pMatrix, const char* pParameter );

		////////////////////////////////////////////////////////////
		/// \brief Uebertraegt die Vertex-Buffer-Daten in den Videospeicher der Grafikkarte.
		///
		/// \param pTexture 	OpenGL Textur-Objekt
		/// \param textureNr	Textur-Nr.: GL_TEXTUR0 bis GL_TEXTUR31
		/// \param stage		Textur-Stage: 0 bis 31
		/// \param pParameter	Attributname der Textur im Shader Code
		///
		////////////////////////////////////////////////////////////
		void setTexture( const TextureObject* pTexture, const long textureNr, const long stage, const char* pParameter );

	private:
		////////////////////////////////////////////////////////////
		/// \brief Laedt den Shader Code aus einer Textdatei.
		///
		/// \param pFileName Dateipfad des Shader Codes
		/// \param pLength   Laenge der Textdatei
		///
		////////////////////////////////////////////////////////////
		void* fileContents( const char* pFileName, GLint* pLength );
	
		////////////////////////////////////////////////////////////
		/// \brief Zeigt in der Konsole Information ueber den Shader Code und aktuelle Fehlermeldungen an.
		///
		/// \param object
		/// \param glGet_iv
		/// \param glGet_InfoLog
		///
		////////////////////////////////////////////////////////////
		void showInfoLog( GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog );

		////////////////////////////////////////////////////////////
		/// \brief Laedt den Shader Code aus einer Textdatei und generiert ein neues OpenGL Shaderprogramm vom Type "type".
		///
		/// \param type		 Shadertyp (Vertex- oder Fragment-Shader)
		/// \param pFileName Dateipfad des Shader Codes
		///
		/// \return Vertex- oder Fragment-Shader ID
		///
		////////////////////////////////////////////////////////////
		GLuint createShader( GLenum type, const char* pFileName );

		////////////////////////////////////////////////////////////
		/// \brief Generiert und kompiliert ein neues OpenGL Shaderprogramm.
		///
		/// \param vertexShader Vertex-Shader ID
		/// \param pixelShader  Fragment-Shader ID
		///
		/// \return Shaderprogramm ID
		///
		////////////////////////////////////////////////////////////
		GLuint createShaderProgram( GLuint vertexShader, GLuint pixelShader );
	};
};
