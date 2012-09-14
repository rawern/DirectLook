#pragma once

#include "Vector3.h"
#include "Matrix.h"

namespace DirectLook
{
	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Skalierungsmatrix.
	///
	/// \param pOut Skalierungsmatrix
	/// \param sx   Skalierung in X-Richtung
	/// \param sy   Skalierung in Y-Richtung
	/// \param sz   Skalierung in Z-Richtung
	///
	/// \return Skalierungsmatrix
	///
	////////////////////////////////////////////////////////////
	Matrix* scaling( Matrix* pOut, float sx, float sy, float sz );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Translationsmatrix.
	///
	/// \param pOut Translationsmatrix
	/// \param x    Translation in X-Richtung
	/// \param y    Translation in Y-Richtung
	/// \param z    Translation in Z-Richtung
	///
	/// \return Translationsmatrix
	///
	////////////////////////////////////////////////////////////
	Matrix* translation( Matrix* pOut, float x, float y, float z );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Rotationsmatrix um die X-Achse mit dem Rotationswinkel "angle".
	/// 
	/// Der Winkel muss in Radiant angegeben werden.
	///
	/// \param pOut  Rotationsmatrix
	/// \param angle Rotationswinkel in Radiant
	///
	/// \return Rotationsmatrix
	///
	////////////////////////////////////////////////////////////
	Matrix* rotationX( Matrix* pOut, float angle );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Rotationsmatrix um die Y-Achse mit dem Rotationswinkel "angle".
	/// 
	/// Der Winkel muss in Radiant angegeben werden.
	///
	/// \param pOut  Rotationsmatrix
	/// \param angle Rotationswinkel in Radiant
	///
	/// \return Rotationsmatrix
	///
	////////////////////////////////////////////////////////////
	Matrix* rotationY( Matrix* pOut, float angle );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Rotationsmatrix um die Z-Achse mit dem Rotationswinkel "angle".
	/// 
	/// Der Winkel muss in Radiant angegeben werden.
	///
	/// \param pOut  Rotationsmatrix
	/// \param angle Rotationswinkel in Radiant
	///
	/// \return Rotationsmatrix
	///
	////////////////////////////////////////////////////////////
	Matrix* rotationZ( Matrix* pOut, float angle );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Rotationsmatrix um die Achse "pV" mit dem Rotationswinkel "angle".
	/// 
	/// Der Winkel muss in Radiant angegeben werden.
	///
	/// \param pOut  Rotationsmatrix
	/// \param pV	 Die Rotationsachse als 3D-Vektor
	/// \param angle Rotationswinkel in Radiant
	///
	/// \return Rotationsmatrix
	///
	////////////////////////////////////////////////////////////
	Matrix* rotationAxis( Matrix* pOut, const Vector3* pV, float angle );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine View-Matrix fuer ein linkshaendiges Koordinatensystem.
	///
	/// \param pOut View-Matrix
	/// \param pEye	Position der virtuellen Kamera
	/// \param pAt	Position des Brennpunktes der virtuellen Kamera
	/// \param pUp	Up-Vektor der virtuellen Kamera - meistens (0.0f, 1.0f, 0.0f)
	///
	/// \return View-Matrix
	///
	////////////////////////////////////////////////////////////
	Matrix* lookAtLeftHand( Matrix* pOut, const Vector3* pEye, const Vector3* pAt, const Vector3* pUp );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine View-Matrix fuer ein rechtshaendiges Koordinatensystem.
	///
	/// \param pOut View-Matrix
	/// \param pEye	Position der virtuellen Kamera
	/// \param pAt	Position des Brennpunktes der virtuellen Kamera
	/// \param pUp	Up-Vektor der virtuellen Kamera - meistens (0.0f, 1.0f, 0.0f)
	///
	/// \return View-Matrix
	///
	////////////////////////////////////////////////////////////
	Matrix* lookAtRightHand( Matrix* pOut, const Vector3* pEye, const Vector3* pAt, const Vector3* pUp );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Projektionsmatrix fuer ein rechtshaendiges Koordinatensystem.
	///
	// Die Matrix hat folgenden Aufbau:
	//
	// 2*zn/w  0       0              0
	// 0       2*zn/h  0              0
	// 0       0       zf/(zn-zf)    -1
	// 0       0       zn*zf/(zn-zf)  0
	//
	/// \param pOut Projektionsmatrix
	/// \param w	Breite des Frustums der Near-Clipping-Plane
	/// \param h	Hoehe des Frustums der Near-Clipping-Plane
	/// \param zn	Entfernung der Near-Clipping-Plane
	/// \param zf	Entfernung der Far-Clipping-Plane
	///
	/// \return Projektionsmatrix
	/// 
	////////////////////////////////////////////////////////////
	Matrix* perspectiveRightHand( Matrix* pOut, float w, float h, float zn, float zf );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine Projektionsmatrix fuer ein linkshaendiges Koordinatensystem.
	///
	// Die Matrix hat folgenden Aufbau:
	//
	// 2*zn/w  0       0              0
	// 0       2*zn/h  0              0
	// 0       0       zf/(zf-zn)     1
	// 0       0       zn*zf/(zn-zf)  0
	//
	/// \param pOut Projektionsmatrix
	/// \param w	Breite des Frustums der Near-Clipping-Plane
	/// \param h	Hoehe des Frustums der Near-Clipping-Plane
	/// \param zn	Entfernung der Near-Clipping-Plane
	/// \param zf	Entfernung der Far-Clipping-Plane
	///
	/// \return Projektionsmatrix
	/// 
	////////////////////////////////////////////////////////////
	Matrix* perspectiveLeftHand( Matrix* pOut, float w, float h, float zn, float zf );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine perspektivische Projektionsmatrix fuer ein rechtshaendiges Koordinatensystem.
	///
	// Die Matrix hat folgenden Aufbau:
	//
	// xScale     0          0              0
	// 0        yScale       0              0
	// 0        0        zf/(zn-zf)        -1
	// 0        0        zn*zf/(zn-zf)      0
	//
	/// Wobei:
	/// yScale = cot(fovY/2)    
	/// xScale = yScale / aspect ratio
	///
	/// \param pOut   Perspektivische Projektionsmatrix
	/// \param fovy	  Field of View in Radiant
	/// \param aspect Aspect Ratio
	/// \param zn	  Entfernung der Near-Clipping-Plane
	/// \param zf	  Entfernung der Far-Clipping-Plane
	///
	/// \return Perspektivische Projektionsmatrix
	/// 
	////////////////////////////////////////////////////////////
	Matrix* perspectiveFovRightHand( Matrix* pOut, float fovy, float aspect, float zn, float zf );

	////////////////////////////////////////////////////////////
	/// \brief Erzeugt eine perspektivische Projektionsmatrix fuer ein linkshaendiges Koordinatensystem.
	///
	// Die Matrix hat folgenden Aufbau:
	//
	// xScale     0          0               0
	// 0        yScale       0               0
	// 0          0       zf/(zf-zn)         1
	// 0          0       -zn*zf/(zf-zn)     0
	//
	// Wobei:
	// yScale = cot(fovY/2)
	// xScale = yScale / aspect ratio
	//
	/// \param pOut   Perspektivische Projektionsmatrix
	/// \param fovy	  Field of View in Radiant
	/// \param aspect Aspect Ratio
	/// \param zn	  Entfernung der Near-Clipping-Plane
	/// \param zf	  Entfernung der Far-Clipping-Plane
	///
	/// \return Perspektivische Projektionsmatrix
	/// 
	////////////////////////////////////////////////////////////
	 Matrix* perspectiveFovLeftHand( Matrix* pOut, float fovy, float aspect, float zn, float zf );
	
	////////////////////////////////////////////////////////////
	/// \brief Multipliziert einen 3D-Vektor mit einer 4x4-Rotationsmatrix.
	///
	/// \param pOut Ergebnis-Vektor
	/// \param pV   3D-Vektor
	/// \param pM	Rotationsmatrix
	///
	/// \return Ergebnis-Vektor
	///
	////////////////////////////////////////////////////////////
	Vector3* multiplyVector3WithRotationMatrix( Vector3* pOut, const Vector3* pV, const Matrix* pM );
	
	////////////////////////////////////////////////////////////
	/// \brief Multipliziert einen 3D-Vektor mit einer 4x4-Matrix.
	///
	/// \param pOut Ergebnis-Vektor
	/// \param pV   3D-Vektor
	/// \param pM	Matrix
	///
	/// \return Ergebnis-Vektor
	///
	////////////////////////////////////////////////////////////
	Vector3* multiplyVector3WithMatrix( Vector3* pOut, const Vector3* pV, const Matrix* pM );

	Matrix* ortoFovLeftHand( Matrix* pOut, float r, float l, float t, float b, float n, float f );

	Matrix* orthoLeftHand( Matrix* pOut, float w, float h, float zn, float zf );

	/*
	2/w  0    0           0
	0    2/h  0           0
	0    0    1/(zn-zf)   0
	0    0    zn/(zn-zf)  l
	*/
	Matrix* orthoRightHand( Matrix* pOut, float w, float h, float zn, float zf );
};
