#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace DirectLook
{
	/// \brief Die Klasse Matrix repraesentiert eine 4 x 4 Matrix.
	class Matrix
	{

	public:
		float m_11, m_12, m_13, m_14;	///< 1. Zeile der 4x4 Matrix
		float m_21, m_22, m_23, m_24;	///< 2. Zeile der 4x4 Matrix
		float m_31, m_32, m_33, m_34;	///< 3. Zeile der 4x4 Matrix
		float m_41, m_42, m_43, m_44;	///< 4. Zeile der 4x4 Matrix

	public:
		////////////////////////////////////////////////////////////
		/// \brief Standardkonstruktor
		///
		/// Erzeugt eine 4x4 Einheitsmatrix.
		///
		////////////////////////////////////////////////////////////
		Matrix(void); 

		////////////////////////////////////////////////////////////
		/// \brief Kopierkonstruktor
		///
		/// Ezeugt eine Tiefe Kopie der Matrix.
		///
		/// \param copy	
		///
		////////////////////////////////////////////////////////////
		Matrix( const Matrix& copy ); 
		
		////////////////////////////////////////////////////////////
		/// \brief Konstruktor
		///
		/// Erzeugt eine 4x4 Matrix aus den uebergebenen Parametern.
		///
		////////////////////////////////////////////////////////////
		Matrix(
			float _11, float _12, float _13, float _14, 
			float _21, float _22, float _23, float _24, 
			float _31, float _32, float _33, float _34, 
			float _41, float _42, float _43, float _44
		); 
 
		/// Arithmethische Zuweisungs-Operatoren fuer Matrizen. 
		Matrix& operator*=( const Matrix& m ); 
		Matrix& operator+=( const Matrix& m ); 
		Matrix& operator-=( const Matrix& m ); 
		Matrix& operator*=( float value ); 
		Matrix& operator/=( float value ); 
 
		/// Unaere Operatoren fuer Matrizen.
		Matrix operator+(void) const;
		Matrix operator-(void) const; 
 
		/// Arithmetische-Operatoren fuer Matrizen.
		Matrix operator*( const Matrix& m ) const; 
		Matrix operator+( const Matrix& m ) const; 
		Matrix operator-( const Matrix& m ) const; 
		Matrix operator*( float value ) const; 
		Matrix operator/( float value ) const; 
 
		friend Matrix operator*( float value, const Matrix& m ); 
 
		/// Gleich und nicht-gleich Operatoren.
		bool operator==( const Matrix& m ) const; 
		bool operator!=( const Matrix& m ) const;

		/// ueberladung der Vergleichs-Operatoren:
		void operator=( const Matrix& m );
		void operator=( const float value );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Refernzwert von Zeile "row" und Spalte "col" der Matrix zurueck.
		///
		/// \param row	Matrixzeile
		/// \param col	Matrixspalte
		///
		/// \return		Referenzwert
		///
		////////////////////////////////////////////////////////////
		float& dataAt( unsigned int row, unsigned int col );

		////////////////////////////////////////////////////////////
		/// \brief Liefert den Wert von Zeile "row" und Spalte "col" der Matrix zurueck.
		///
		/// \param row	Matrixzeile
		/// \param col	Matrixspalte
		///
		/// \return		Wert
		///
		////////////////////////////////////////////////////////////
		float dataAt( unsigned int row, unsigned int col ) const;

		/// \brief Konvertiert die Matrix in eine Einheitsmatrix.
		void identity(void);
		
		/// \brief Ist die Matrix eine Einheitsmatrix.
		bool isIdentity(void) const;

		/// \brief Berechnet die Determinante der Matrix.
		///
		/// \return Determinante
		///
		float determinant(void) const;

		/// \brief Transponiert die Matrix.
		void transpose(void);

		/// \brief Liefert die transponierte Matrix zurueck.
		///
		/// \return Transponierte Matrix 
		///
		Matrix getTranspose(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Invertiert die Matrix falls die Determinante ungleich Null ist.
		/// Ansonsten bleibt die urspruengliche Matrix bestehen.
		////////////////////////////////////////////////////////////
		void inverse(void);

		////////////////////////////////////////////////////////////
		/// \brief Liefert die Inverse Matrix zurueck, falls die Determinante ungleich Null ist.
		/// Ansosnten wird die urspruengliche Matrix zurueckgeliefert.
		///
		/// \return Inverse Matrix
		///
		////////////////////////////////////////////////////////////
		Matrix getInverse(void) const;

	private:
		////////////////////////////////////////////////////////////
		/// \brief Multipliziert zwei Matrizen und liefert das Ergebnis in "pOut" zurueck.
		///
		/// \param pOut Ergebnis-Matrix
		/// \param pM1 Linke Matrix
		/// \param pM2 Rechte Matrix
		///
		/// \return Ergebnis-Matrix
		///
		////////////////////////////////////////////////////////////
		Matrix* matrixMultiply( Matrix* pOut, const Matrix* pM1, const Matrix* pM2 ) const;

		////////////////////////////////////////////////////////////
		/// \brief Berechnet das erweiterte Kreuzprodukt von drei 4D-Vektoren.
		/// Wird fuer die effiziente Berechnung der inversen Matrix benoetigt.
		///
		/// \param pOut Ergebnis-Vektor
		/// \param pV1  Vektor 1
		/// \param pV2  Vektor 2
		/// \param pV3  Vektor 3 
		///
		/// \return Ergebnis-Vektor
		///
		////////////////////////////////////////////////////////////
		Vector4* cross( Vector4* pOut, const Vector4* pV1, const Vector4* pV2, const Vector4* pV3 ) const;
	};
};
