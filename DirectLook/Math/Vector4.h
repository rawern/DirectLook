#pragma once

#include "Constants.h"
#include <math.h>

namespace DirectLook
{
	/// \brief Die Klasse Vector4 repraesentiert einen 4D-Vektor.
	class Vector4
	{

	public:
		float x;	///< X-Wert des Vektors
		float y;	///< Y-Wert des Vektors
		float z;	///< Z-Wert des Vektors
		float w;	///< W-Wert des Vektors

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor: x, y, z, w = 0.0f
		///
		/// Erzeugt ein Vector2 Objekt mit den Werten x, y, z, w = 0.0f.
		///
		////////////////////////////////////////////////////////////
		Vector4(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Vector4 Objektes.
		///
		/// \param copy
		///
		////////////////////////////////////////////////////////////
		Vector4( const Vector4& copy );
	
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt einen 4D-Vektor mit den Werten der uebergebenen Parameter.
		///
		/// \param x
		/// \param y
		/// \param z
		/// \param w
		///
		////////////////////////////////////////////////////////////
		Vector4( const float x, const float y, const float z, const float w );

		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		////////////////////////////////////////////////////////////
		~Vector4(void);

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
		/// \param vector 4D-Vektor
		///
		/// \return Punktprodukt
		///
		////////////////////////////////////////////////////////////
		float dot( const Vector4& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet den Winkel zwischen zwei Vektoren in Grad.
		///
		/// \param vector 4D-Vektor
		///
		/// \return Winkel in Grad
		///
		////////////////////////////////////////////////////////////
		float angle( const Vector4& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet den Winkel zwischen zwei Vektoren in Radiant.
		///
		/// \param vector 4D-Vektor
		///
		/// \return Winkel in Radiant
		///
		////////////////////////////////////////////////////////////
		float angleRad( const Vector4& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor um den Wert "scale".
		///
		/// \param scale Skalierungsfaktor
		///
		////////////////////////////////////////////////////////////
		void scale( const float scale );

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor in X-Richtung um den Faktor "scaleX", in Y-Richtung um den Faktor "scaleY", in Z-Richtung um den Faktor "scaleZ" und die Komponente W um den Faktor "scaleW".
		///
		/// \param scaleX Skalierungsfaktor fuer den X-Wert
		/// \param scaleY Skalierungsfaktor fuer den Y-Wert
		/// \param scaleZ Skalierungsfaktor fuer den Z-Wert
		/// \param scaleW Skalierungsfaktor fuer den W-Wert
		///
		////////////////////////////////////////////////////////////
		void scale( const float scaleX, const float scaleY, const float scaleZ, const float scaleW );

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor um den Wert "scale" und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param scale Skalierungsfaktor
		///
		/// \return Den skalierten 4D-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector4 getScale( const float scale ) const;

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
		Vector4 getScaleNormalized( const float length ) const;

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
		Vector4 getNormalize(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Mitte zwischen zwei Vektoren und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param vector 4D-Vektor
		///
		/// \return Der mittlere Vektor
		///
		////////////////////////////////////////////////////////////
		Vector4 middle( const Vector4& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Distanz zwischen zwei Vektoren.
		///
		/// \param vector 4D-Vektor
		///
		/// \return Distanz
		///
		////////////////////////////////////////////////////////////
		float distance( const Vector4& vector ) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Berechnet die quadratische Distanz zwischen zwei Vektoren.
		///
		/// \param vector 4D-Vektor
		///
		/// \return Quadratische Distanz
		///
		////////////////////////////////////////////////////////////
		float squareDistance( const Vector4& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet das erweiterte Kreuzprodukt zwischen drei 4D-Vektoren und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param vector2 4D-Vektor
		/// \param vector3 4D-Vektor
		///
		/// \return Ergebnis-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector4 cross( const Vector4& vector2, const Vector4& vector3 ) const;

		///////////////////////////
		// ueberladene Operatoren //
		///////////////////////////

		/// Gibt den negierten Ergebnis-Vektor zurueck.
		Vector4 operator-(void) const;

		/// Gleich und nicht-gleich Operatoren.
		bool operator==( const Vector4& vector ) const;
		bool operator!=( const Vector4& vector ) const;

		/// Arithmetische- und Zuweisungs-Operatoren fuer Vektoren.
		void operator=( const Vector4& vector );
		Vector4 operator+( const Vector4& vector ) const;
		Vector4& operator+=( const Vector4& vector );
		Vector4 operator-( const Vector4& vector) const;
		Vector4& operator-=( const Vector4& vector );
		float operator*( const Vector4& vector ) const;	// Punktprodukt
		float operator/( const Vector4& vector ) const;	// Invertiertes Punktprodukt
	
		/// Arithmetische- und Zuweisungs-Operatoren fuer einen numerischen Wert.
		void operator=( const float value );
		Vector4 operator+( const float value ) const;
		Vector4& operator+=( const float value );
		Vector4 operator-( const float value) const;
		Vector4& operator-=( const float value );
		Vector4 operator*( const float value ) const;
		Vector4& operator*=( const float value );
		Vector4 operator/( const float value ) const;
		Vector4& operator/=( const float value );

		friend Vector4 operator*( float value, const Vector4& vector );
	};
};
