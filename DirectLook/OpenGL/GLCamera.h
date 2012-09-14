#pragma once

#include "../Math/Constants.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix.h"
#include "../Math/VectorMath.h"

#include <math.h>
#include <GL/glew.h>

namespace DirectLook
{
	/// \brief Die Klasse GLCamera repraesentiert eine virtuelle Kamera.
	class GLCamera
	{

	public:
		Vector3 m_Direction;		///< Kamerarichtung
		Vector3 m_Position;			///< Position der Kamera
		Vector3 m_WorldUp;			///< Up-Vektor der Kamera
		Vector3 m_LookAt;			///< Brennpunkt der Kamera

		GLfloat m_FieldOfView;		///< Field of View
		GLfloat m_AspectRatio;		///< Seitenverhaeltnis
		GLfloat m_NearClipPlane;	///< Near-Clipping-Plane
		GLfloat m_FarClipPlane;		///< Far-Clipping-Plane

		Matrix m_MatView;			///< View-Matrix
		Matrix m_MatProjection;		///< Projektionsmatrix
		Matrix m_MatViewProjection;	///< View-Projection-Matrix
		Matrix m_MatRotation;		///< Rotationsmatrix

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt eine neues Kamera-Objekt mit den Werten:
		///
		/// Kamerarichtung		: ( 0.0f, 0.0f, 0.0f )
		/// Kameraposition		: ( 0.0f, 0.0f, 2.0f )
		/// Up-Vektor der Kamera: ( 0.0f, 1.0f, 0.0f )
		/// Brennpunkt			: ( 0.0f, 0.0f, 0.0f )
		/// Field of View		: PI / 2.0 
		/// Seitenverhaeltnis	: 4.0f / 3.0f
		/// Near-Clipping-Plane	: 0.5f
		/// Far-Clipping-Plane	: 5000.0f
		///
		////////////////////////////////////////////////////////////
		GLCamera(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Kamera Objektes.
		///
		/// \param copy
		///
		////////////////////////////////////////////////////////////
		GLCamera( const GLCamera& copy );
	
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein Kamera-Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param fieldOfView	 Field of View in Radiant
		/// \param aspectRatio	 Seitenverhaeltnis
		/// \param nearClipPlane Near-Clipping-Plane
		/// \param farClipPlane	 Far-Clipping-Plane
		///
		////////////////////////////////////////////////////////////
		GLCamera( GLfloat fieldOfView, GLfloat aspectRatio, GLfloat nearClipPlane, GLfloat farClipPlane );

		///////////////////////////////////////////////////////////
		/// \brief Destruktor
		///////////////////////////////////////////////////////////
		~GLCamera(void);

		///////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Kameramatrizen.
		///
		///////////////////////////////////////////////////////////
		void update(void);

		///////////////////////////////////////////////////////////
		/// \brief Setzt die Translationen der Kamera in X-, Y- und Z-Richtung.
		/// 
		/// \param strafe  Translation in X-Richtung
		/// \param upDown  Translation in Y-Richtung
		/// \param forBack Translation in Z-Richtung
		///
		///////////////////////////////////////////////////////////
		void addToCamera( float strafe, float upDown, float forBack );

		///////////////////////////////////////////////////////////
		/// \brief Setzt die Rotationswinkel der Kamera um die X- und Y-Achse.
		/// Die Rotationswinkel muessen in der Einheit Radiant angegeben werden.
		///
		/// \param xAngle Rotationswinkel um die X-Achse
		/// \param yAngle Rotationswinkel umd die Y-Achse
		///
		///////////////////////////////////////////////////////////
		void rotateAroundPosition( float xAngle, float yAngle );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Kamera auf die Standartwerte zurueck.
		///
		/// Kamerarichtung		: ( 0.0f, 0.0f, 0.0f )
		/// Kameraposition		: ( 0.0f, 0.0f, 2.0f )
		/// Up-Vektor der Kamera: ( 0.0f, 1.0f, 0.0f )
		/// Brennpunkt			: ( 0.0f, 0.0f, 0.0f )
		/// Field of View		: PI / 2.0 
		/// Seitenverhaeltnis	: 4.0f / 3.0f
		/// Near-Clipping-Plane	: 0.5f
		/// Far-Clipping-Plane	: 5000.0f
		///
		////////////////////////////////////////////////////////////
		void reset(void);
	};
};
