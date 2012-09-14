#pragma once

#include "IRenderObject.h"
#include "ElementBufferObject.h"
#include "VertexBufferObject.h"
#include "Shader.h"
#include "GLCamera.h"

#include "../Math/Constants.h"
#include "../Math/Matrix.h"
#include "../Math/Vector3.h"

namespace DirectLook
{	
	/// \brief Die Klasse GLMesh repraesentiert ein einfaches 3D-Mesh.
	class GLMesh : public IRenderObject 
	{

	protected:
		Matrix m_MatWorld;						///< Weltmatrix
		Vector3 m_Position;						///< Positionsvektor
		Vector3 m_Rotation;						///< Rotationsvektor
		Vector3 m_Scale;						///< Skalierungsvektor

		ElementBufferObject* m_pElementBuffer;	///< Element-Buffer
		VertexBufferObject* m_pVertexBuffer;	///< Vertex-Buffer
		Shader* m_pShader;						///< Shader
		GLCamera* m_pCamera;					///< Virtuelle Kamera der 3D-Szene

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt ein leeres Mesh-Objekt.
		///
		////////////////////////////////////////////////////////////
		GLMesh(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt ein Mesh Objekt mit den Eigenschaften der uebergebenen Parameter.
		///
		/// \param pElementBuffer OpenGL Element-Buffer
		/// \param pVertexBuffer  OpenGL Vertex-Buffer
		/// \param pShader		  Shaderprogramm des Mesh Objektes
		/// \param pCamera		  Virtuelle Kamera der 3D-Szene
		///
		////////////////////////////////////////////////////////////
		GLMesh( ElementBufferObject* pElementBuffer, VertexBufferObject* pVertexBuffer, Shader* pShader, GLCamera* pCamera );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		///
		/// Gibt den belegten Speicher vom Mesh-Objekt wieder frei.
		///
		////////////////////////////////////////////////////////////
		virtual ~GLMesh(void);

		////////////////////////////////////////////////
		// ueberschriebe Render-Object Klassenmethoden //
		////////////////////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Inizialisiert das Mesh-Objekt.
		////////////////////////////////////////////////////////////
		virtual void initialize(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Aktualisiert die Weltmatrix.
		////////////////////////////////////////////////////////////
		virtual void update(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Zeichnet das Mesh-Objekt.
		////////////////////////////////////////////////////////////
		virtual void draw(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Loescht die Meshdaten aus dem Videospeicher der Grafikkarte.
		/// Wird im Destruktor aufgerufen.
		///
		////////////////////////////////////////////////////////////
		virtual void deleteResources(void);

		//////////////////////////////////
		// Manipulative GLMesh Methoden //
		//////////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Position des Meshs.
		///
		/// \param xPos Translationswert in X-Richtung
		/// \param yPos Translationswert in Y-Richtung
		/// \param zPos Translationswert in Z-Richtung
		///
		////////////////////////////////////////////////////////////
		void setPosition( const float xPos, const float yPos, const float zPos );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Position des Meshs als 3D-Vektor.
		///
		/// \param position 3D-Vektor mit den Translationswerten in X-, Y- und Z-Richtung
		///
		////////////////////////////////////////////////////////////
		void setPosition( const Vector3& position );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Rotationswinkel in X-, Y- und Z-Richtung.
		/// Die Winkel muessen in der Einheit Radiant angegeben werden.
		///
		/// \param xAngle Rotationswinkel in Radiant um die X-Achse
		/// \param yAngle Rotationswinkel in Radiant um die Y-Achse
		/// \param zAngle Rotationswinkel in Radiant um die Z-Achse
		///
		////////////////////////////////////////////////////////////
		void setRotation( const float xAngle, const float yAngle, const float zAngle );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die Rotationswinkel in X-, Y- und Z-Richtung als 3D-Vektor.
		/// Die Winkel muessen in der Einheit Radiant angegeben werden.
		///
		/// \param rotation 3D-Vektor mit den Rotationswinkeln in Radiant um die X-, Y- und Z-Achse
		///
		////////////////////////////////////////////////////////////
		void setRotation( const Vector3& rotation );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Skalierungsvektor in X-, Y- und Z-Richtung.
		///
		/// \param xScale Skalierungsfaktor in X-Richtung
		/// \param yScale Skalierungsfaktor in Y-Richtung
		/// \param zScale Skalierungsfaktor in Z-Richtung
		///
		////////////////////////////////////////////////////////////
		void setScale( const float xScale, const float yScale, const float zScale );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den Skalierungsvektor in X-, Y- und Z-Richtung als 3D-Vektor.
		///
		/// \param scale 3D-Vektor mit den X-, Y- und Z-Werten fuer die Skalierung des Meshs
		///
		////////////////////////////////////////////////////////////
		void setScale( const Vector3& scale );

		////////////////////////////////////////////////////////////
		/// \brief Addiert die Werte von "xPos", "yPos" und "zPos" zum aktuellen Positionsvektor hinzu.
		///
		/// \param xPos Translationswert in X-Richtung
		/// \param yPos Translationswert in Y-Richtung
		/// \param zPos Translationswert in Z-Richtung
		///
		////////////////////////////////////////////////////////////
		void translate( const float xPos, const float yPos, const float zPos );

		////////////////////////////////////////////////////////////
		/// \brief Addiert die Werte von "translate" zur aktuellen Positionsvektor hinzu.
		///
		/// \param translate 3D-Vektor mit den Translationswerten in X-, Y- und Z-Richtung
		///
		////////////////////////////////////////////////////////////
		void translate( const Vector3& translate );

		////////////////////////////////////////////////////////////
		/// \brief Addiert die Winkelwerte "xAngle", "yAngle" und "zAngle" zum aktuellen Rotationsvektor hinzu.
		/// Die Winkel muessen in der Einheit Radiant angegeben werden.
		///
		/// \param xAngle Rotationswinkel in Radiant um die X-Achse
		/// \param yAngle Rotationswinkel in Radiant um die Y-Achse
		/// \param zAngle Rotationswinkel in Radiant um die Z-Achse
		///
		////////////////////////////////////////////////////////////
		void rotate( const float xAngle, const float yAngle, const float zAngle );

		////////////////////////////////////////////////////////////
		/// \brief Addiert die Winkelwerte von "rotate" zum aktuellen Rotationsvektor hinzu.
		/// Die Winkel muessen in der Einheit Radiant angegeben werden.
		///
		/// \param rotate 3D-Vektor mit den Rotationswinkeln in Radiant um die X-, Y- und Z-Achse
		///
		////////////////////////////////////////////////////////////
		void rotate( const Vector3& rotate );

		////////////////////////////////////////////////////////////
		/// \brief Addiert die Werte "xScale", "yScale" und "zScale" zum aktuellen Skalierungsvektor hinzu.
		///
		/// \param xScale Skalierungsfaktor in X-Richtung
		/// \param yScale Skalierungsfaktor in Y-Richtung
		/// \param zScale Skalierungsfaktor in Z-Richtung
		///
		////////////////////////////////////////////////////////////
		void scale( const float xScale, const float yScale, const float zScale );

		////////////////////////////////////////////////////////////
		/// \brief Addiert die Werte von "scale" zum aktuellen Skalierungsvektor hinzu.
		///
		/// \param scale 3D-Vektor mit den X-, Y- und Z-Werten fuer die Skalierung des Meshs
		///
		////////////////////////////////////////////////////////////
		void scale( const Vector3& scale );

		//////////////////////////////
		// GLMesh Getter und Setter //
		//////////////////////////////

		////////////////////////////////////////////////////////////
		/// \brief Setzt den OpenGL Element-Buffer.
		///
		/// \param pElementBuffer Element-Buffer
		///
		////////////////////////////////////////////////////////////
		void setElementBuffer( ElementBufferObject* pElementBuffer );

		////////////////////////////////////////////////////////////
		/// \brief Setzt den OpenGL Vertex-Buffer.
		///
		/// \param pVertexBuffer Vertex-Buffer
		///
		////////////////////////////////////////////////////////////
		void setVertexBuffer( VertexBufferObject* pVertexBuffer );

		////////////////////////////////////////////////////////////
		/// \brief Setzt das Shader-Objekt.
		///
		/// \param pShader Shader-Objekt
		///
		////////////////////////////////////////////////////////////
		void setShader( Shader* pShader );

		////////////////////////////////////////////////////////////
		/// \brief Setzt die virtuelle Kamera der 3D-Szene.
		///
		/// \param pCamera Virtuelle Kamera der 3D-Szene
		///
		////////////////////////////////////////////////////////////
		void setCamera( GLCamera* pCamera );

		////////////////////////////////////////////////////////////
		/// \brief Liefert einen konstanten Pointer des Element-Buffers zurueck.
		///
		/// \return Konstanter Element-Buffer-Pointer
		///
		////////////////////////////////////////////////////////////
		const ElementBufferObject* getElementBuffer(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert einen konstanten Pointer des Vertex-Buffers zurueck.
		///
		/// \return Konstanter Vertex-Buffer-Pointer
		///
		////////////////////////////////////////////////////////////
		const VertexBufferObject* getVertexBuffer(void) const;
		
		////////////////////////////////////////////////////////////
		/// \brief Liefert einen konstanten Pointer des Shader-Objektes zurueck.
		///
		/// \return Konstanter Shader-Pointer
		///
		////////////////////////////////////////////////////////////
		const Shader* getShader(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Liefert einen konstanten Pointer der virtuellen Kamera zurueck.
		///
		/// \return Konstanter Kamera-Pointer
		///
		////////////////////////////////////////////////////////////
		const GLCamera* getCamera(void) const;
	};
};
