#pragma once

#include <math.h>
#include "Constants.h"

namespace DirectLook
{
	/// \brief Die Klasse Vector2 repraesentiert einen 2D-Vektor.
	class Vector2
	{

	public:
		float x;	///< X-Wert des Vektors
		float y;	///< Y-Wert des Vektors

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor: x, y = 0.0f
		///
		/// Erzeugt ein Vector2 Objekt mit den Werten x, y = 0.0f.
		///
		////////////////////////////////////////////////////////////
		Vector2(void);

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Erzeugt eine tiefe Kopie des uebergebenen Vector2 Objektes.
		///
		/// \param copy
		///
		////////////////////////////////////////////////////////////
		Vector2( const Vector2& copy );

		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt einen 2D-Vektor mit den Werten der uebergebenen Parameter.
		///
		/// \param x
		/// \param y
		///
		////////////////////////////////////////////////////////////
		Vector2( const float x, const float y );
 
		////////////////////////////////////////////////////////////
		/// \brief Destruktor
		////////////////////////////////////////////////////////////
		~Vector2(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert die normierte Normale des Vektors zurueck.
		///
		/// \return Normierte Normale
		///
		////////////////////////////////////////////////////////////
		Vector2 perpendicular(void) const;

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
		/// \brief Berechnet den Winkel zwischen zwei Vektoren in Grad.
		///
		/// \param vector 2D-Vektor
		///
		/// \return Winkel in Grad
		///
		////////////////////////////////////////////////////////////
		float angle( const Vector2& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet den Winkel zwischen zwei Vektoren in Radiant.
		///
		/// \param vector 2D-Vektor
		///
		/// \return Winkel in Radiant
		///
		////////////////////////////////////////////////////////////
		float angleRad( const Vector2& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet das Punktprodukt zwischen zwei Vektoren.
		///
		/// \param vector 2D-Vektor
		///
		/// \return Punktprodukt
		///
		////////////////////////////////////////////////////////////
		float dot( const Vector2& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor um den Wert "scale".
		///
		/// \param scale Skalierungsfaktor
		///
		////////////////////////////////////////////////////////////
		void scale( const float scale );

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor in X-Richtung um den Faktor "scaleX" und in Y-Richtung um den Faktor "scaleY".
		///
		/// \param scaleX Skalierungsfaktor fuer den X-Wert
		/// \param scaleY Skalierungsfaktor fuer den Y-Wert
		///
		////////////////////////////////////////////////////////////
		void scale( const float scaleX, const float scaleY );

		////////////////////////////////////////////////////////////
		/// \brief Skaliert den Vektor um den Wert "scale" und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param scale Skalierungsfaktor
		///
		/// \return Den skalierten 2D-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector2 getScale( const float scale ) const;

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
		Vector2 getScaleNormalized( const float length ) const;

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
		Vector2 getNormalize(void) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Mitte zwischen zwei Vektoren und liefert den Ergebnis-Vektor zurueck.
		///
		/// \param vector 2D-Vektor
		///
		/// \return Der mittlere Vektor
		///
		////////////////////////////////////////////////////////////
		Vector2 middle( const Vector2& vector ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet die Distanz zwischen zwei Vektoren.
		///
		/// \param vector 2D-Vektor
		///
		/// \return Distanz
		///
		////////////////////////////////////////////////////////////
		float distance( const Vector2& vector ) const;
	
		////////////////////////////////////////////////////////////
		/// \brief Berechnet die quadratische Distanz zwischen zwei Vektoren.
		///
		/// \param vector 2D-Vektor
		///
		/// \return Quadratische Distanz
		///
		////////////////////////////////////////////////////////////
		float squareDistance( const Vector2& vector ) const;

		///////////////////////////
		// ueberladene Operatoren //
		///////////////////////////

		////////////////////////////////////////////////////////////
		/// Gibt den negierten Ergebnis-Vektor zurueck.
		////////////////////////////////////////////////////////////
		Vector2 operator-(void) const;

		////////////////////////////////////////////////////////////
		/// Gleich und nicht-gleich Operatoren.
		////////////////////////////////////////////////////////////
		bool operator==( const Vector2& vector ) const;
		bool operator!=( const Vector2& vector ) const;

		////////////////////////////////////////////////////////////
		/// Arithmetische- und Zuweisungs-Operatoren fuer Vektoren.
		////////////////////////////////////////////////////////////
		void operator=( const Vector2& vector );
		Vector2 operator+( const Vector2& vector ) const;
		Vector2& operator+=( const Vector2& vector );
		Vector2 operator-( const Vector2& vector) const;
		Vector2& operator-=( const Vector2& vector );
		float operator*( const Vector2& vector ) const;	// Punktprodukt
		float operator/( const Vector2& vector ) const;	// Invertiertes Punktprodukt
	
		////////////////////////////////////////////////////////////
		/// Arithmetische- und Zuweisungs-Operatoren fuer einen numerischen Wert.
		////////////////////////////////////////////////////////////
		void operator=( const float value );
		Vector2 operator+( const float value ) const;
		Vector2& operator+=( const float value );
		Vector2 operator-( const float value) const;
		Vector2& operator-=( const float value );
		Vector2 operator*( const float value ) const;
		Vector2& operator*=( const float value );
		Vector2 operator/( const float value ) const;
		Vector2& operator/=( const float value );

		friend Vector2 operator*( float value, const Vector2& vector );
	};
};
