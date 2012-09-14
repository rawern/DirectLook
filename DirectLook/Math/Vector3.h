#pragma once

#include "Constants.h"
#include "Matrix.h"
#include <math.h>

namespace DirectLook
{
	/// \brief Die Klasse Vector3 repraesentiert einen 3D-Vektor.
	class Vector3
	{

	public:
		float x;	///< X-Wert des Vektors
		float y;	///< Y-Wert des Vektors
		float z;	///< Z-Wert des Vektors

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor: x, y, z = 0.0f
		///
		/// Erzeugt ein Vector3 Objekt mit den Werten x, y, z = 0.0f.
		///
		////////////////////////////////////////////////////////////
		Vector3(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Vector3 Objektes.
		///
		/// \param copy
		///
		////////////////////////////////////////////////////////////
		Vector3( const Vector3& copy );
	
		// Konstruktor
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt einen 3D-Vektor mit den Werten der uebergebenen Parameter.
		///
		/// \param x
		/// \param y
		/// \param z
		///
		////////////////////////////////////////////////////////////
		Vector3( const float x, const float y, const float z );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		////////////////////////////////////////////////////////////
		~Vector3(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert die normierte Normale des Vektors zurueck.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Normierte Normale
		///
		////////////////////////////////////////////////////////////
		Vector3 perpendicular( const Vector3& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Laenge des Vektors.
		///
		/// \return Laenge des Vektors
		///
		////////////////////////////////////////////////////////////
		float length(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die quadratische Vektorlaenge.
		///
		/// \return Quadratische Vektorlaenge
		///
		////////////////////////////////////////////////////////////
		float squareLength(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet das Punktprodukt zwischen zwei Vektoren.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Punktprodukt
		///
		////////////////////////////////////////////////////////////
		float dot( const Vector3& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet den Winkel zwischen zwei Vektoren in Grad.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Winkel in Grad
		///
		////////////////////////////////////////////////////////////
		float angle( const Vector3& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet den Winkel zwischen zwei Vektoren in Radiant.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Winkel in Radiant
		///
		////////////////////////////////////////////////////////////
		float angleRad( const Vector3& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor um den Wert "scale".
		///
		/// \param scale Skalierungsfaktor
		///
		////////////////////////////////////////////////////////////
		void scale( const float scale );

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor in X-Richtung um den Faktor "scaleX", in Y-Richtung um den Faktor "scaleY" und in Z-Richtung um den Faktor "scaleZ".
		///
		/// \param scaleX Skalierungsfaktor fuer den X-Wert
		/// \param scaleY Skalierungsfaktor fuer den Y-Wert
		/// \param scaleZ Skalierungsfaktor fuer den Z-Wert
		///
		////////////////////////////////////////////////////////////
		void scale( const float scaleX, const float scaleY, const float scaleZ );

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor um den Wert "scale" und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param scale Skalierungsfaktor
		///
		/// \return Den skalierten 3D-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector3 getScale( const float scale ) const;

		////////////////////////////////////////////////////////////
		/// \brief Normiert und skaliert den Vektor um den Wert "length".
		///
		/// \param length
		///
		////////////////////////////////////////////////////////////
		void scaleNormalized( const float length );

		////////////////////////////////////////////////////////////
		/// \brief Normiert und skaliert den Vektor um den Wert "length" und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param length
		///
		/// \return Skalierter Ergebnis-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector3 getScaleNormalized( const float length ) const;

		////////////////////////////////////////////////////////////
		/// \brief Normiert den Vektor.
		////////////////////////////////////////////////////////////
		void normalize(void);
	
		////////////////////////////////////////////////////////////
		/// \brief Normiert den Vektor und liefert den Ergebnis-Vektor zurueck.
		///
		/// \return Normierter Ergebnis-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector3 getNormalize(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Mitte zwischen zwei Vektoren und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Der mittlere Vektor
		///
		////////////////////////////////////////////////////////////
		Vector3 middle( const Vector3& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Distanz zwischen zwei Vektoren.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Distanz
		///
		////////////////////////////////////////////////////////////
		float distance( const Vector3& vector ) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Berechnet die quadratische Distanz zwischen zwei Vektoren.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Quadratische Distanz
		///
		////////////////////////////////////////////////////////////
		float squareDistance( const Vector3& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet das Kreuzprodukt zwischen zwei Vektoren und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param vector 3D-Vektor
		///
		/// \return Ergebnis-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector3 cross( const Vector3& vector ) const;

		///////////////////////////
		// ueberladene Operatoren //
		///////////////////////////

		/// Gibt den negierten Ergebnis-Vektor zurueck.
		Vector3 operator-(void) const;

		/// Gleich und nicht-gleich Operatoren.
		bool operator==( const Vector3& vector ) const;
		bool operator!=( const Vector3& vector ) const;

		/// Arithmetische- und Zuweisungs-Operatoren fuer Vektoren.
		void operator=( const Vector3& vector );
		Vector3 operator+( const Vector3& vector ) const;
		Vector3& operator+=( const Vector3& vector );
		Vector3 operator-( const Vector3& vector) const;
		Vector3& operator-=( const Vector3& vector );
		float operator*( const Vector3& vector ) const;	// Punktprodukt
		float operator/( const Vector3& vector ) const;	// Invertiertes Punktprodukt
	
		/// Arithmetische- und Zuweisungs-Operatoren fuer einen numerischen Wert.
		void operator=( const float value );
		Vector3 operator+( const float value ) const;
		Vector3& operator+=( const float value );
		Vector3 operator-( const float value) const;
		Vector3& operator-=( const float value );
		Vector3 operator*( const float value ) const;
		Vector3& operator*=( const float value );
		Vector3 operator/( const float value ) const;
		Vector3& operator/=( const float value );

		friend Vector3 operator*( float value, const Vector3& vector );
	};
};
