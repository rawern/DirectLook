#include "Matrix.h"

namespace DirectLook
{
	Matrix::Matrix(void)
		:
		m_11( 1.0f ), m_12( 0.0f ), m_13( 0.0f ), m_14( 0.0f ),
		m_21( 0.0f ), m_22( 1.0f ), m_23( 0.0f ), m_24( 0.0f ),
		m_31( 0.0f ), m_32( 0.0f ), m_33( 1.0f ), m_34( 0.0f ),
		m_41( 0.0f ), m_42( 0.0f ), m_43( 0.0f ), m_44( 1.0f )
	{
	}

	Matrix::Matrix( const Matrix& copy )
		:
		m_11( copy.m_11 ), m_12( copy.m_12 ), m_13( copy.m_13 ), m_14( copy.m_14 ),
		m_21( copy.m_21 ), m_22( copy.m_22 ), m_23( copy.m_23 ), m_24( copy.m_24 ),
		m_31( copy.m_31 ), m_32( copy.m_32 ), m_33( copy.m_33 ), m_34( copy.m_34 ),
		m_41( copy.m_41 ), m_42( copy.m_42 ), m_43( copy.m_43 ), m_44( copy.m_44 )
	{
	}

	Matrix::Matrix(
		float m_11, float m_12, float m_13, float m_14, 
		float m_21, float m_22, float m_23, float m_24, 
		float m_31, float m_32, float m_33, float m_34, 
		float m_41, float m_42, float m_43, float m_44
	)
		:
		m_11( m_11 ), m_12( m_12 ), m_13( m_13 ), m_14( m_14 ),
		m_21( m_21 ), m_22( m_22 ), m_23( m_23 ), m_24( m_24 ),
		m_31( m_31 ), m_32( m_32 ), m_33( m_33 ), m_34( m_34 ),
		m_41( m_41 ), m_42( m_42 ), m_43( m_43 ), m_44( m_44 )
	{
	}
 
	Matrix& Matrix::operator*=( const Matrix& mat )
	{
		Matrix matT;

		matrixMultiply( &matT, this, &mat );
		*this = matT;

		return( *this );
	}

	Matrix& Matrix::operator+=( const Matrix& mat )
	{
		m_11 += mat.m_11; m_12 += mat.m_12; m_13 += mat.m_13; m_14 += mat.m_14;
		m_21 += mat.m_21; m_22 += mat.m_22; m_23 += mat.m_23; m_24 += mat.m_24;
		m_31 += mat.m_31; m_32 += mat.m_32; m_33 += mat.m_33; m_34 += mat.m_34;
		m_41 += mat.m_41; m_42 += mat.m_42; m_43 += mat.m_43; m_44 += mat.m_44;
	
		return( *this );
	}

	Matrix& Matrix::operator-=( const Matrix& mat )
	{
		m_11 -= mat.m_11; m_12 -= mat.m_12; m_13 -= mat.m_13; m_14 -= mat.m_14;
		m_21 -= mat.m_21; m_22 -= mat.m_22; m_23 -= mat.m_23; m_24 -= mat.m_24;
		m_31 -= mat.m_31; m_32 -= mat.m_32; m_33 -= mat.m_33; m_34 -= mat.m_34;
		m_41 -= mat.m_41; m_42 -= mat.m_42; m_43 -= mat.m_43; m_44 -= mat.m_44;
	
		return( *this );
	}

	Matrix& Matrix::operator*=( float value )
	{
		m_11 *= value; m_12 *= value; m_13 *= value; m_14 *= value;
		m_21 *= value; m_22 *= value; m_23 *= value; m_24 *= value;
		m_31 *= value; m_32 *= value; m_33 *= value; m_34 *= value;
		m_41 *= value; m_42 *= value; m_43 *= value; m_44 *= value;
	
		return( *this );
	}

	Matrix& Matrix::operator/=( float value )
	{
		float fInv = 1.0f / value;
		m_11 *= fInv; m_12 *= fInv; m_13 *= fInv; m_14 *= fInv;
		m_21 *= fInv; m_22 *= fInv; m_23 *= fInv; m_24 *= fInv;
		m_31 *= fInv; m_32 *= fInv; m_33 *= fInv; m_34 *= fInv;
		m_41 *= fInv; m_42 *= fInv; m_43 *= fInv; m_44 *= fInv;
	
		return( *this );
	}
 
	Matrix Matrix::operator+(void) const
	{
		return( *this );
	}

	Matrix Matrix::operator-(void) const
	{
		return Matrix(
			-m_11, -m_12, -m_13, -m_14,
			-m_21, -m_22, -m_23, -m_24,
			-m_31, -m_32, -m_33, -m_34,
			-m_41, -m_42, -m_43, -m_44
		);
	}

	Matrix Matrix::operator*( const Matrix& mat ) const
	{
		Matrix matT;
		matrixMultiply( &matT, this, &mat );
	
		return matT;
	}

	Matrix Matrix::operator+( const Matrix& mat ) const
	{
		return Matrix(
			m_11 + mat.m_11, m_12 + mat.m_12, m_13 + mat.m_13, m_14 + mat.m_14,
			m_21 + mat.m_21, m_22 + mat.m_22, m_23 + mat.m_23, m_24 + mat.m_24,
			m_31 + mat.m_31, m_32 + mat.m_32, m_33 + mat.m_33, m_34 + mat.m_34,
			m_41 + mat.m_41, m_42 + mat.m_42, m_43 + mat.m_43, m_44 + mat.m_44
		);
	}

	Matrix Matrix::operator-( const Matrix& mat ) const
	{
		return Matrix(
			m_11 - mat.m_11, m_12 - mat.m_12, m_13 - mat.m_13, m_14 - mat.m_14,
			m_21 - mat.m_21, m_22 - mat.m_22, m_23 - mat.m_23, m_24 - mat.m_24,
			m_31 - mat.m_31, m_32 - mat.m_32, m_33 - mat.m_33, m_34 - mat.m_34,
			m_41 - mat.m_41, m_42 - mat.m_42, m_43 - mat.m_43, m_44 - mat.m_44
		);
	}

	Matrix Matrix::operator*( float value ) const
	{
		return Matrix(
			m_11 * value, m_12 * value, m_13 * value, m_14 * value,
			m_21 * value, m_22 * value, m_23 * value, m_24 * value,
			m_31 * value, m_32 * value, m_33 * value, m_34 * value,
			m_41 * value, m_42 * value, m_43 * value, m_44 * value
		);
	}

	Matrix Matrix::operator/( float value ) const
	{
		float fInv = 1.0f / value;
		return Matrix(
			m_11 * fInv, m_12 * fInv, m_13 * fInv, m_14 * fInv,
			m_21 * fInv, m_22 * fInv, m_23 * fInv, m_24 * fInv,
			m_31 * fInv, m_32 * fInv, m_33 * fInv, m_34 * fInv,
			m_41 * fInv, m_42 * fInv, m_43 * fInv, m_44 * fInv
		);
	}
 
	Matrix operator*( float value, const Matrix& mat )
	{
		return Matrix(
			value * mat.m_11, value * mat.m_12, value * mat.m_13, value * mat.m_14,
			value * mat.m_21, value * mat.m_22, value * mat.m_23, value * mat.m_24,
			value * mat.m_31, value * mat.m_32, value * mat.m_33, value * mat.m_34,
			value * mat.m_41, value * mat.m_42, value * mat.m_43, value * mat.m_44
		);
	}
 
	bool Matrix::operator==( const Matrix& mat ) const
	{
		return m_11 == mat.m_11 && m_12 == mat.m_12 && m_13 == mat.m_13 && m_14 == mat.m_14 &&
			   m_21 == mat.m_21 && m_22 == mat.m_22 && m_23 == mat.m_23 && m_24 == mat.m_24 &&
			   m_31 == mat.m_31 && m_32 == mat.m_32 && m_33 == mat.m_33 && m_34 == mat.m_34 &&
			   m_41 == mat.m_41 && m_42 == mat.m_42 && m_43 == mat.m_43 && m_44 == mat.m_44;
	}

	bool Matrix::operator!=( const Matrix& mat ) const
	{
		return m_11 != mat.m_11 || m_12 != mat.m_12 || m_13 != mat.m_13 || m_14 != mat.m_14 ||
			   m_21 != mat.m_21 || m_22 != mat.m_22 || m_23 != mat.m_23 || m_24 != mat.m_24 ||
			   m_31 != mat.m_31 || m_32 != mat.m_32 || m_33 != mat.m_33 || m_34 != mat.m_34 ||
			   m_41 != mat.m_41 || m_42 != mat.m_42 || m_43 != mat.m_43 || m_44 != mat.m_44;
	}

	void Matrix::operator=( const Matrix& m )
	{
		m_11 = m.m_11;	m_21 = m.m_21;	m_31 = m.m_31;	m_41 = m.m_41;
		m_12 = m.m_12;	m_22 = m.m_22;	m_32 = m.m_32;	m_42 = m.m_42;
		m_13 = m.m_13;	m_23 = m.m_23;	m_33 = m.m_33;	m_43 = m.m_43;
		m_14 = m.m_14;	m_24 = m.m_24;	m_34 = m.m_34;	m_44 = m.m_44;
	}
	
	void Matrix::operator=( const float value )
	{
		m_11 = value;	m_21 = value;	m_31 = value;	m_41 = value;
		m_12 = value;	m_22 = value;	m_32 = value;	m_42 = value;
		m_13 = value;	m_23 = value;	m_33 = value;	m_43 = value;
		m_14 = value;	m_24 = value;	m_34 = value;	m_44 = value;
	}

	float& Matrix::dataAt( unsigned int row, unsigned int col )
	{
		switch (row){
			case 0:
				switch(col)
				{	
					case 0:	return m_11;
					case 1:	return m_12;
					case 2:	return m_13;
					case 3:	return m_14;
				}
				break;
			case 1:
				switch(col)
				{
					case 0:	return m_21;
					case 1:	return m_22;
					case 2:	return m_23;
					case 3:	return m_24;
				}
				break;
			case 2:
				switch(col)
				{
					case 0:	return m_31;
					case 1:	return m_32;
					case 2:	return m_33;
					case 3:	return m_34;
				}
				break;
			case 3:
				switch(col)
				{
					case 0:	return m_41;
					case 1:	return m_42;
					case 2:	return m_43;
					case 3:	return m_44;
				}
				break;
		}		
		float *warningKillReturnValue = new float(0.0f);
		return *warningKillReturnValue;
	}
	
	float Matrix::dataAt( unsigned int row, unsigned int col ) const
	{
		switch (row){
			case 0:
				switch(col)
				{	
					case 0:	return m_11;
					case 1:	return m_12;
					case 2:	return m_13;
					case 3:	return m_14;
				}
				break;
			case 1:
				switch(col)
				{
					case 0:	return m_21;
					case 1:	return m_22;
					case 2:	return m_23;
					case 3:	return m_24;
				}
				break;
			case 2:
				switch(col)
				{
					case 0:	return m_31;
					case 1:	return m_32;
					case 2:	return m_33;
					case 3:	return m_34;
				}
				break;
			case 3:
				switch(col)
				{
					case 0:	return m_41;
					case 1:	return m_42;
					case 2:	return m_43;
					case 3:	return m_44;
				}
				break;
		}	
		float warningKillReturnValue = 0.0f;
		return warningKillReturnValue;
	}

	void Matrix::identity(void)
	{
		m_12 = m_13 = m_14 =
		m_21 = m_23 = m_24 =
		m_31 = m_32 = m_34 =
		m_41 = m_42 = m_43 = 0.0f;

		m_11 = m_22 = m_33 = m_44 = 1.0f;
	}

	bool Matrix::isIdentity(void) const
	{
		return m_11 == 1.0f && m_12 == 0.0f && m_13 == 0.0f && m_14 == 0.0f &&
			   m_21 == 0.0f && m_22 == 1.0f && m_23 == 0.0f && m_24 == 0.0f &&
			   m_31 == 0.0f && m_32 == 0.0f && m_33 == 1.0f && m_34 == 0.0f &&
			   m_41 == 0.0f && m_42 == 0.0f && m_43 == 0.0f && m_44 == 1.0f;
	}
	
	float Matrix::determinant(void) const
	{
		Vector4 minor, v1, v2, v3;
		float det;

		v1.x = m_11; v1.y = m_21; v1.z = m_31; v1.w = m_41;
		v2.x = m_12; v2.y = m_22; v2.z = m_32; v2.w = m_42;
		v3.x = m_13; v3.y = m_23; v3.z = m_33; v3.w = m_43;
		cross( &minor, &v1, &v2, &v3 );
		det =  - (m_14 * minor.x + m_24 * minor.y + m_34 * minor.z + m_44 * minor.w);
		return det;
	}
	
	void Matrix::transpose(void)
	{
		Matrix m;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				m.dataAt( i, j ) = dataAt( j, i );
			}
		}
		*this = m;
	}
	
	Matrix Matrix::getTranspose(void) const
	{
		Matrix m;
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				m.dataAt( i, j ) = dataAt( j, i );
			}
		}

		return m;
	}

	void Matrix::inverse(void)
	{
		Matrix m;
		int a, i, j;
		Vector4 v, vec[3];
		float det;
		float temp;
 
		det = determinant();
	
		if(det)	// Matrix invertierbar?
		{
			for(i = 0; i < 4; i++)
			{
				for(j = 0; j < 4; j++)
				{
					if(j != i )
					{
						a = j;
				
						if(j > i)
						{
							a = a - 1;
						}
				
						vec[a].x = dataAt( j, 0 );
						vec[a].y = dataAt( j, 1 );
						vec[a].z = dataAt( j, 2 );
						vec[a].w = dataAt( j, 3 );
					}
				}
		
				v = vec[0].cross( vec[1], vec[2] );
		
				temp = pow( -1.0f, i );
		
				m.dataAt( 0, i ) = temp * v.x / det;
				m.dataAt( 1, i ) = temp * v.y / det;
				m.dataAt( 2, i ) = temp * v.z / det;
				m.dataAt( 3, i ) = temp * v.w / det;
			}

			*this = m;
		}
	}
	
	Matrix Matrix::getInverse(void) const
	{
		Matrix m( *this );
		m.inverse();
		return m;
	}

	Matrix* Matrix::matrixMultiply( Matrix* pOut, const Matrix* pM1, const Matrix* pM2 ) const
	{
		pOut->m_11 = pM1->m_11 * pM2->m_11 + pM1->m_12 * pM2->m_21 + pM1->m_13 * pM2->m_31 + pM1->m_14 * pM2->m_41;
		pOut->m_12 = pM1->m_11 * pM2->m_12 + pM1->m_12 * pM2->m_22 + pM1->m_13 * pM2->m_32 + pM1->m_14 * pM2->m_42;
		pOut->m_13 = pM1->m_11 * pM2->m_13 + pM1->m_12 * pM2->m_23 + pM1->m_13 * pM2->m_33 + pM1->m_14 * pM2->m_43;
		pOut->m_14 = pM1->m_11 * pM2->m_14 + pM1->m_12 * pM2->m_24 + pM1->m_13 * pM2->m_34 + pM1->m_14 * pM2->m_44;

		pOut->m_21 = pM1->m_21 * pM2->m_11 + pM1->m_22 * pM2->m_21 + pM1->m_23 * pM2->m_31 + pM1->m_24 * pM2->m_41;
		pOut->m_22 = pM1->m_21 * pM2->m_12 + pM1->m_22 * pM2->m_22 + pM1->m_23 * pM2->m_32 + pM1->m_24 * pM2->m_42;
		pOut->m_23 = pM1->m_21 * pM2->m_13 + pM1->m_22 * pM2->m_23 + pM1->m_23 * pM2->m_33 + pM1->m_24 * pM2->m_43;
		pOut->m_24 = pM1->m_21 * pM2->m_14 + pM1->m_22 * pM2->m_24 + pM1->m_23 * pM2->m_34 + pM1->m_24 * pM2->m_44;

		pOut->m_31 = pM1->m_31 * pM2->m_11 + pM1->m_32 * pM2->m_21 + pM1->m_33 * pM2->m_31 + pM1->m_34 * pM2->m_41;
		pOut->m_32 = pM1->m_31 * pM2->m_12 + pM1->m_32 * pM2->m_22 + pM1->m_33 * pM2->m_32 + pM1->m_34 * pM2->m_42;
		pOut->m_33 = pM1->m_31 * pM2->m_13 + pM1->m_32 * pM2->m_23 + pM1->m_33 * pM2->m_33 + pM1->m_34 * pM2->m_43;
		pOut->m_34 = pM1->m_31 * pM2->m_14 + pM1->m_32 * pM2->m_24 + pM1->m_33 * pM2->m_34 + pM1->m_34 * pM2->m_44;

		pOut->m_41 = pM1->m_41 * pM2->m_11 + pM1->m_42 * pM2->m_21 + pM1->m_43 * pM2->m_31 + pM1->m_44 * pM2->m_41;
		pOut->m_42 = pM1->m_41 * pM2->m_12 + pM1->m_42 * pM2->m_22 + pM1->m_43 * pM2->m_32 + pM1->m_44 * pM2->m_42;
		pOut->m_43 = pM1->m_41 * pM2->m_13 + pM1->m_42 * pM2->m_23 + pM1->m_43 * pM2->m_33 + pM1->m_44 * pM2->m_43;
		pOut->m_44 = pM1->m_41 * pM2->m_14 + pM1->m_42 * pM2->m_24 + pM1->m_43 * pM2->m_34 + pM1->m_44 * pM2->m_44;

		return pOut;
	}

	Vector4* Matrix::cross( Vector4* pOut, const Vector4* pV1, const Vector4* pV2, const Vector4* pV3 ) const
	{
		pOut->x = pV1->y * (pV2->z * pV3->w - pV3->z * pV2->w) - pV1->z * (pV2->y * pV3->w - pV3->y * pV2->w) + pV1->w * (pV2->y * pV3->z - pV2->z *pV3->y);
		pOut->y = -(pV1->x * (pV2->z * pV3->w - pV3->z * pV2->w) - pV1->z * (pV2->x * pV3->w - pV3->x * pV2->w) + pV1->w * (pV2->x * pV3->z - pV3->x * pV2->z));
		pOut->z = pV1->x * (pV2->y * pV3->w - pV3->y * pV2->w) - pV1->y * (pV2->x *pV3->w - pV3->x * pV2->w) + pV1->w * (pV2->x * pV3->y - pV3->x * pV2->y);
		pOut->w = -(pV1->x * (pV2->y * pV3->z - pV3->y * pV2->z) - pV1->y * (pV2->x * pV3->z - pV3->x *pV2->z) + pV1->z * (pV2->x * pV3->y - pV3->x * pV2->y));
		return pOut;
	}
};
