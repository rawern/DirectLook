#include "VectorMath.h"

namespace DirectLook
{
	Matrix* scaling( Matrix* pOut, float sx, float sy, float sz )
	{
		pOut->identity();
		pOut->m_11 = sx;
		pOut->m_22 = sy;
		pOut->m_33 = sz;

		return pOut;
	}

	Matrix* translation( Matrix* pOut, float x, float y, float z )
	{
		pOut->identity();
		pOut->m_41 = x;
		pOut->m_42 = y;
		pOut->m_43 = z;

		return pOut;
	}

	Matrix* rotationX( Matrix* pOut, float angle )
	{
		float tempCos = cosf( angle );
		float tempSin = sinf( angle );
	
		pOut->m_11 = 1.0f;	pOut->m_12 = 0.0f; 		pOut->m_13 = 0.0f;		pOut->m_14 = 0.0f;
		pOut->m_21 = 0.0f;	pOut->m_22 =  tempCos;	pOut->m_23 = tempSin;	pOut->m_24 = 0.0f;
		pOut->m_31 = 0.0f;	pOut->m_32 = -tempSin;	pOut->m_33 = tempCos;	pOut->m_34 = 0.0f; 		
		pOut->m_41 = 0.0f;	pOut->m_42 = 0.0f; 		pOut->m_43 = 0.0f; 		pOut->m_44 = 1.0f;  

		return pOut;
	}

	Matrix* rotationY( Matrix* pOut, float angle )
	{
		float tempCos = cosf( angle );
		float tempSin = sinf( angle );

		pOut->m_11 = tempCos;  pOut->m_12 = 0.0f;     pOut->m_13 = -tempSin; pOut->m_14 = 0.0f;
		pOut->m_21 = 0.0f;     pOut->m_22 = 1.0f;     pOut->m_23 = 0.0f;     pOut->m_24 = 0.0f;
		pOut->m_31 = tempSin;  pOut->m_32 = 0.0f;     pOut->m_33 = tempCos;  pOut->m_34 = 0.0f; 		
		pOut->m_41 = 0.0f;     pOut->m_42 = 0.0f;     pOut->m_43 = 0.0f;     pOut->m_44 = 1.0f;  

		return pOut;
	}

	Matrix* rotationZ( Matrix* pOut, float angle )
	{
		float tempCos = cosf( angle );
		float tempSin = sinf( angle );

		pOut->m_11 = tempCos;  pOut->m_12 = tempSin;  pOut->m_13 = 0.0f;     pOut->m_14 = 0.0f;
		pOut->m_21 = -tempSin; pOut->m_22 = tempCos;  pOut->m_23 = 0.0f;     pOut->m_24 = 0.0f;
		pOut->m_31 = 0.0f;     pOut->m_32 = 0.0f;     pOut->m_33 = 1.0f;     pOut->m_34 = 0.0f; 		
		pOut->m_41 = 0.0f;     pOut->m_42 = 0.0f;     pOut->m_43 = 0.0f;     pOut->m_44 = 1.0f; 

		return pOut;
	}

	Matrix* rotationAxis( Matrix* pOut, const Vector3* pV, float angle )
	{ 
		Vector3 axisNormalized;
		axisNormalized = pV->getNormalize();
    
		float tempCos = cosf( angle );
		float tempSin = sinf( angle );

		float tempX = axisNormalized.x;
		float tempY = axisNormalized.y;
		float tempZ = axisNormalized.z;
		float tempDiff = 1.0f - tempCos;

		float temp1Factor = tempX * tempY;
		float temp2Factor = tempX * tempZ;
		float temp3Factor = tempY * tempZ;

		pOut->m_11 = tempX * tempX * tempDiff + tempCos;
		pOut->m_12 = temp1Factor * tempDiff+tempZ * tempSin;
		pOut->m_13 = temp2Factor * tempDiff-tempY * tempSin;
		pOut->m_14 = 0.0f;

		pOut->m_21 = temp1Factor * tempDiff - tempZ * tempSin;
		pOut->m_22 = tempY*tempY * tempDiff + tempCos;
		pOut->m_23 = temp3Factor * tempDiff + tempX * tempSin;
		pOut->m_24 = 0.0f;

		pOut->m_31 = temp2Factor * tempDiff + tempY * tempSin;
		pOut->m_32 = temp3Factor * tempDiff - tempX * tempSin;
		pOut->m_33 = tempZ * tempZ * tempDiff + tempCos;
		pOut->m_34 = 0.0f; 
		
		pOut->m_41 = 0.0f;
		pOut->m_42 = 0.0f;
		pOut->m_43 = 0.0f;
		pOut->m_44 = 1.0f;  

		return pOut;
	}

	Matrix* lookAtLeftHand( Matrix* pOut, const Vector3* pEye, const Vector3* pAt, const Vector3* pUp )
	{
		Vector3 right, rightn, up, upn, vec, vec2;

		vec2	= *pAt - *pEye;
		vec		= vec2.getNormalize();
		right	= pUp->cross( vec );
		up		= vec.cross( right );
		rightn	= right.getNormalize();
		upn		= up.getNormalize();
		
		pOut->m_11 = rightn.x;	pOut->m_21 = rightn.y;	pOut->m_31 = rightn.z;	pOut->m_41 = -rightn.dot( *pEye );
		pOut->m_12 = upn.x;		pOut->m_22 = upn.y;		pOut->m_32 = upn.z;		pOut->m_42 = -upn.dot( *pEye );
		pOut->m_13 = vec.x;		pOut->m_23 = vec.y;		pOut->m_33 = vec.z;		pOut->m_43 = -vec.dot( *pEye );
		pOut->m_14 = 0.0f;		pOut->m_24 = 0.0f;		pOut->m_34 = 0.0f;		pOut->m_44 =  1.0f;
		
		return pOut;
	}

	Matrix* lookAtRightHand( Matrix* pOut, const Vector3* pEye, const Vector3* pAt, const Vector3* pUp )
	{
		Vector3 right, rightn, up, upn, vec, vec2;

		vec2	= *pAt - *pEye;
		vec		= vec2.getNormalize();
		right	= pUp->cross( vec );
		up		= vec.cross( right );
		rightn	= right.getNormalize();
		upn		= up.getNormalize();

		pOut->m_11 = -rightn.x;	pOut->m_21 = -rightn.y;	pOut->m_31 = -rightn.z;	pOut->m_41 =  rightn.dot( *pEye );
		pOut->m_12 =  upn.x;	pOut->m_22 =  upn.y;	pOut->m_32 =  upn.z;	pOut->m_42 = -upn.dot( *pEye );
		pOut->m_13 = -vec.x;	pOut->m_23 = -vec.y;	pOut->m_33 = -vec.z;	pOut->m_43 =  vec.dot( *pEye );
		pOut->m_14 =  0.0f;		pOut->m_24 =  0.0f;		pOut->m_34 =  0.0f;		pOut->m_44 =  1.0f;
		
		return pOut;
	}

	Matrix* perspectiveRightHand( Matrix* pOut, float w, float h, float zn, float zf )
	{
		pOut->m_11 = 2.0f * zn / w;	pOut->m_21 = 0.0f;			pOut->m_31 = 0.0f;				pOut->m_41 = 0.0f;
		pOut->m_12 = 0.0f;			pOut->m_22 = 2.0f * zn / h;	pOut->m_32 = 0.0f;				pOut->m_42 = 0.0f;
		pOut->m_13 = 0.0f;			pOut->m_23 = 0.0f;			pOut->m_33 = zf / (zn - zf);	pOut->m_43 = zn * zf / (zn - zf);
		pOut->m_14 = 0.0f;			pOut->m_24 = 0.0f;			pOut->m_34 = -1.0f;				pOut->m_44 = 0.0f;
		
		return pOut;
	}

	Matrix* perspectiveLeftHand( Matrix* pOut, float w, float h, float zn, float zf )
	{
		pOut->m_11 = 2.0f * zn / w;	pOut->m_21 = 0.0f;			pOut->m_31 = 0.0f;				pOut->m_41 = 0.0f;
		pOut->m_12 = 0.0f;			pOut->m_22 = 2.0f * zn / h;	pOut->m_32 = 0.0f;				pOut->m_42 = 0.0f;
		pOut->m_13 = 0.0f;			pOut->m_23 = 0.0f;			pOut->m_33 = zf / (zf - zn);	pOut->m_43 = zn * zf / (zn - zf);
		pOut->m_14 = 0.0f;			pOut->m_24 = 0.0f;			pOut->m_34 = 1.0f;				pOut->m_44 = 0.0f;
				
		return pOut;
	}

	Matrix* perspectiveFovRightHand( Matrix* pOut, float fovy, float aspect, float zn, float zf )
	{
		pOut->m_12 = 0.0f;
		pOut->m_13 = 0.0f;
		pOut->m_14 = 0.0f;

		pOut->m_21 = 0.0f;
		pOut->m_23 = 0.0f;
		pOut->m_24 = 0.0f;

		pOut->m_31 = 0.0f;
		pOut->m_32 = 0.0f;
	
		pOut->m_41 = 0.0f;
		pOut->m_42 = 0.0f;
		pOut->m_44 = 0.0f;

		pOut->m_11 =  1.0f / (aspect * tan( fovy / 2.0f ));
		pOut->m_22 =  1.0f / tan( fovy / 2.0f );
		pOut->m_33 =  zf / (zn - zf);
		pOut->m_34 = -1.0f;
		pOut->m_43 =  (zf * zn) / (zn - zf);
    
		return pOut;
	}

	 Matrix* perspectiveFovLeftHand( Matrix* pOut, float fovy, float aspect, float zn, float zf )
	{
		pOut->m_12 = 0.0f;
		pOut->m_13 = 0.0f;
		pOut->m_14 = 0.0f;

		pOut->m_21 = 0.0f;
		pOut->m_23 = 0.0f;
		pOut->m_24 = 0.0f;

		pOut->m_31 = 0.0f;
		pOut->m_32 = 0.0f;
	
		pOut->m_41 = 0.0f;
		pOut->m_42 = 0.0f;
		pOut->m_44 = 0.0f;

		pOut->m_11 = 1.0f / (aspect * tan( fovy / 2.0f ));
		pOut->m_22 = 1.0f / tan( fovy / 2.0f );
		pOut->m_33 = zf / (zf - zn);
		pOut->m_34 = 1.0f;
		pOut->m_43 = (zf * zn) / (zn - zf);
    
		return pOut;
	}
	
	Vector3* multiplyVector3WithRotationMatrix( Vector3* pOut, const Vector3* pV, const Matrix* pM )
	{
		pOut->x = pM->m_11 * pV->x + pM->m_21 * pV->y + pM->m_31 * pV->z;
		pOut->y = pM->m_12 * pV->x + pM->m_22 * pV->y + pM->m_32 * pV->z;
		pOut->z = pM->m_13 * pV->x + pM->m_23 * pV->y + pM->m_33 * pV->z;
		
		return pOut;
	}
	
	Vector3* multiplyVector3WithMatrix( Vector3* pOut, const Vector3* pV, const Matrix* pM )
	{
		pOut->x = pM->m_11 * pV->x + pM->m_21 * pV->y + pM->m_31 * pV->z + pM->m_41;
		pOut->y = pM->m_12 * pV->x + pM->m_22 * pV->y + pM->m_32 * pV->z + pM->m_42;
		pOut->z = pM->m_13 * pV->x + pM->m_23 * pV->y + pM->m_33 * pV->z + pM->m_43;
			
		return pOut;
	}

	Matrix* ortoFovLeftHand( Matrix* pOut, float r, float l, float t, float b, float n, float f )
	{
		pOut->m_12 = 0.0f;
		pOut->m_13 = 0.0f;
		pOut->m_14 = 0.0f;

		pOut->m_21 = 0.0f;
		pOut->m_23 = 0.0f;
		pOut->m_24 = 0.0f;

		pOut->m_31 = 0.0f;
		pOut->m_32 = 0.0f;
	
		pOut->m_14 = -( (r + l) / (r - l) );
		pOut->m_24 = -( (t + b) / (t - b) );
		pOut->m_34 = -( (f + n) / (f - n) );
		pOut->m_44 = 1.0f;

		pOut->m_11 = 2.0f / (r - l);
		pOut->m_22 = 2.0f / (t - b);
		pOut->m_33 = 2.0f / (f - n);
		pOut->m_34 = 1.0f;
    
		return pOut;
	}

	Matrix* orthoLeftHand( Matrix* pOut, float w, float h, float zn, float zf )
	{
		pOut->identity();
		pOut->m_11 = 2.0f / w;
		pOut->m_22 = 2.0f / h;
		pOut->m_33 = 1.0f / (zf - zn);
		pOut->m_43 = zn / (zn - zf);
		return pOut;
	}

	Matrix* orthoRightHand( Matrix* pOut, float w, float h, float zn, float zf )
	{
		pOut->identity();
		pOut->m_11 = 2.0f / w;
		pOut->m_22 = 2.0f / h;
		pOut->m_33 = 1.0f / (zn - zf);
		pOut->m_43 = zn / (zn - zf);
		return pOut;
	}
};
