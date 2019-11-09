///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline Quaternion::Quaternion ()
{
    // uninitialized for performance in array construction
}
//----------------------------------------------------------------------------
inline Quaternion::Quaternion (float fW, float fX, float fY, float fZ)
{
    m_afTuple[0] = fW;
    m_afTuple[1] = fX;
    m_afTuple[2] = fY;
    m_afTuple[3] = fZ;
}
//----------------------------------------------------------------------------
inline Quaternion::Quaternion (const Quaternion& rkQ)
{
    size_t uiSize = 4*sizeof(float);
    memcpy(m_afTuple,rkQ.m_afTuple,uiSize);
}
//----------------------------------------------------------------------------
inline Quaternion::Quaternion (const Matrix4& rkRot)
{
    FromRotationMatrix(rkRot);
}
//----------------------------------------------------------------------------
inline Quaternion::Quaternion (const Vector3& rkAxis, float fAngle)
{
    FromAxisAngle(rkAxis,fAngle);
}
//----------------------------------------------------------------------------
inline Quaternion::Quaternion (const Vector3 akRotColumn[3])
{
    FromRotationMatrix(akRotColumn);
}
//----------------------------------------------------------------------------
inline void Quaternion::Set (float fW, float fX, float fY, float fZ)
{
    m_afTuple[0] = fW;
    m_afTuple[1] = fX;
    m_afTuple[2] = fY;
    m_afTuple[3] = fZ;
}
//----------------------------------------------------------------------------
inline Quaternion::operator const float* () const
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline Quaternion::operator float* ()
{
    return m_afTuple;
}
//----------------------------------------------------------------------------
inline float Quaternion::operator[] (int i) const
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float& Quaternion::operator[] (int i)
{
    assert(0 <= i && i <= 3);
    return m_afTuple[i];
}
//----------------------------------------------------------------------------
inline float Quaternion::W () const
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float& Quaternion::W ()
{
    return m_afTuple[0];
}
//----------------------------------------------------------------------------
inline float Quaternion::X () const
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float& Quaternion::X ()
{
    return m_afTuple[1];
}
//----------------------------------------------------------------------------
inline float Quaternion::Y () const
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float& Quaternion::Y ()
{
    return m_afTuple[2];
}
//----------------------------------------------------------------------------
inline float Quaternion::Z () const
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline float& Quaternion::Z ()
{
    return m_afTuple[3];
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::operator= (const Quaternion& rkQ)
{
    size_t uiSize = 4*sizeof(float);
    memcpy(m_afTuple,rkQ.m_afTuple,uiSize);
    return *this;
}
//----------------------------------------------------------------------------
inline int Quaternion::CompareArrays (const Quaternion& rkQ) const
{
    return memcmp(m_afTuple,rkQ.m_afTuple,4*sizeof(float));
}
//----------------------------------------------------------------------------
inline bool Quaternion::operator== (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) == 0;
}
//----------------------------------------------------------------------------
inline bool Quaternion::operator!= (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) != 0;
}
//----------------------------------------------------------------------------
inline bool Quaternion::operator< (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) < 0;
}
//----------------------------------------------------------------------------
inline bool Quaternion::operator<= (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) <= 0;
}
//----------------------------------------------------------------------------
inline bool Quaternion::operator> (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) > 0;
}
//----------------------------------------------------------------------------
inline bool Quaternion::operator>= (const Quaternion& rkQ) const
{
    return CompareArrays(rkQ) >= 0;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
    Quaternion kSum;
    for (int i = 0; i < 4; i++)
    {
        kSum.m_afTuple[i] = m_afTuple[i] + rkQ.m_afTuple[i];
    }
    return kSum;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
    Quaternion kDiff;
    for (int i = 0; i < 4; i++)
    {
        kDiff.m_afTuple[i] = m_afTuple[i] - rkQ.m_afTuple[i];
    }
    return kDiff;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

    Quaternion kProd;

    kProd.m_afTuple[0] =
        m_afTuple[0]*rkQ.m_afTuple[0] -
        m_afTuple[1]*rkQ.m_afTuple[1] -
        m_afTuple[2]*rkQ.m_afTuple[2] -
        m_afTuple[3]*rkQ.m_afTuple[3];

    kProd.m_afTuple[1] =
        m_afTuple[0]*rkQ.m_afTuple[1] +
        m_afTuple[1]*rkQ.m_afTuple[0] +
        m_afTuple[2]*rkQ.m_afTuple[3] -
        m_afTuple[3]*rkQ.m_afTuple[2];

    kProd.m_afTuple[2] =
        m_afTuple[0]*rkQ.m_afTuple[2] +
        m_afTuple[2]*rkQ.m_afTuple[0] +
        m_afTuple[3]*rkQ.m_afTuple[1] -
        m_afTuple[1]*rkQ.m_afTuple[3];

    kProd.m_afTuple[3] =
        m_afTuple[0]*rkQ.m_afTuple[3] +
        m_afTuple[3]*rkQ.m_afTuple[0] +
        m_afTuple[1]*rkQ.m_afTuple[2] -
        m_afTuple[2]*rkQ.m_afTuple[1];

    return kProd;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator* (float fScalar) const
{
    Quaternion kProd;
    for (int i = 0; i < 4; i++)
    {
        kProd.m_afTuple[i] = fScalar*m_afTuple[i];
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator/ (float fScalar) const
{
    Quaternion kQuot;
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 4; i++)
        {
            kQuot.m_afTuple[i] = fInvScalar*m_afTuple[i];
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            kQuot.m_afTuple[i] = Math::MAX_REAL;
        }
    }

    return kQuot;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator- () const
{
    Quaternion kNeg;
    for (int i = 0; i < 4; i++)
    {
        kNeg.m_afTuple[i] = -m_afTuple[i];
    }
    return kNeg;
}
//----------------------------------------------------------------------------
inline Quaternion operator* (float fScalar, const Quaternion& rkQ)
{
    Quaternion kProd;
    for (int i = 0; i < 4; i++)
    {
        kProd[i] = fScalar*rkQ[i];
    }
    return kProd;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::operator+= (const Quaternion& rkQ)
{
    for (int i = 0; i < 4; i++)
    {
        m_afTuple[i] += rkQ.m_afTuple[i];
    }
    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::operator-= (const Quaternion& rkQ)
{
    for (int i = 0; i < 4; i++)
    {
        m_afTuple[i] -= rkQ.m_afTuple[i];
    }
    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::operator*= (float fScalar)
{
    for (int i = 0; i < 4; i++)
    {
        m_afTuple[i] *= fScalar;
    }
    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::operator/= (float fScalar)
{
    int i;

    if (fScalar != (float)0.0)
    {
        float fInvScalar = ((float)1.0)/fScalar;
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] *= fInvScalar;
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] = Math::MAX_REAL;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::FromRotationMatrix (
    const Matrix4& rkRot)
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "Quaternion Calculus and Fast Animation".

    float fTrace = rkRot(0,0) + rkRot(1,1) + rkRot(2,2);
    float fRoot;

    if (fTrace > (float)0.0)
    {
        // |w| > 1/2, may as well choose w > 1/2
        fRoot = Math::Sqrt(fTrace + (float)1.0);  // 2w
        m_afTuple[0] = ((float)0.5)*fRoot;
        fRoot = ((float)0.5)/fRoot;  // 1/(4w)
        m_afTuple[1] = (rkRot(2,1)-rkRot(1,2))*fRoot;
        m_afTuple[2] = (rkRot(0,2)-rkRot(2,0))*fRoot;
        m_afTuple[3] = (rkRot(1,0)-rkRot(0,1))*fRoot;
    }
    else
    {
        // |w| <= 1/2
        int i = 0;
        if (rkRot(1,1) > rkRot(0,0))
        {
            i = 1;
        }
        if (rkRot(2,2) > rkRot(i,i))
        {
            i = 2;
        }
        int j = ms_iNext[i];
        int k = ms_iNext[j];

        fRoot = Math::Sqrt(rkRot(i,i)-rkRot(j,j)-rkRot(k,k)+(float)1.0);
        float* apfQuat[3] = { &m_afTuple[1], &m_afTuple[2], &m_afTuple[3] };
        *apfQuat[i] = ((float)0.5)*fRoot;
        fRoot = ((float)0.5)/fRoot;
        m_afTuple[0] = (rkRot(k,j)-rkRot(j,k))*fRoot;
        *apfQuat[j] = (rkRot(j,i)+rkRot(i,j))*fRoot;
        *apfQuat[k] = (rkRot(k,i)+rkRot(i,k))*fRoot;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline void Quaternion::ToRotationMatrix (Matrix4& rkRot) const
{
    float fTx  = ((float)2.0)*m_afTuple[1];
    float fTy  = ((float)2.0)*m_afTuple[2];
    float fTz  = ((float)2.0)*m_afTuple[3];
    float fTwx = fTx*m_afTuple[0];
    float fTwy = fTy*m_afTuple[0];
    float fTwz = fTz*m_afTuple[0];
    float fTxx = fTx*m_afTuple[1];
    float fTxy = fTy*m_afTuple[1];
    float fTxz = fTz*m_afTuple[1];
    float fTyy = fTy*m_afTuple[2];
    float fTyz = fTz*m_afTuple[2];
    float fTzz = fTz*m_afTuple[3];

    rkRot[0][0] = 1.0f-(fTyy+fTzz);
    rkRot[0][1] = fTxy-fTwz;
    rkRot[0][2] = fTxz+fTwy;
	rkRot[0][3] = 0;
    
	rkRot[1][0] = fTxy+fTwz;
    rkRot[1][1] = 1.0f-(fTxx+fTzz);
    rkRot[1][2] = fTyz-fTwx;
	rkRot[1][3] = 0;
    
	rkRot[2][0] = fTxz-fTwy;
    rkRot[2][1] = fTyz+fTwx;
    rkRot[2][2] = 1.0f-(fTxx+fTyy);
	rkRot[2][3] = 0;
	
	rkRot[3][0] = 0;
	rkRot[3][1] = 0;
	rkRot[3][2] = 0;
	rkRot[3][3] = 1;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::FromRotationMatrix(const Vector3 akRotColumn[3])
{
    Matrix4 kRot;
    for (int iCol = 0; iCol < 3; iCol++)
    {
        kRot(0,iCol) = akRotColumn[iCol][0];
        kRot(1,iCol) = akRotColumn[iCol][1];
        kRot(2,iCol) = akRotColumn[iCol][2];
    }
    return FromRotationMatrix(kRot);
}
//----------------------------------------------------------------------------
inline void Quaternion::ToRotationMatrix (Vector3 akRotColumn[3]) const
{
    Matrix4 kRot;
    ToRotationMatrix(kRot);
    for (int iCol = 0; iCol < 3; iCol++)
    {
        akRotColumn[0][iCol] = kRot(0,iCol);
        akRotColumn[1][iCol] = kRot(1,iCol);
        akRotColumn[2][iCol] = kRot(2,iCol);
    }
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::FromAxisAngle (const Vector3& rkAxis, float fAngle)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    float fHalfAngle = ((float)0.5)*fAngle;
    float fSin = Math::Sin(fHalfAngle);
    m_afTuple[0] = Math::Cos(fHalfAngle);
    m_afTuple[1] = fSin*rkAxis[0];
    m_afTuple[2] = fSin*rkAxis[1];
    m_afTuple[3] = fSin*rkAxis[2];

    return *this;
}
//----------------------------------------------------------------------------
inline void Quaternion::ToAxisAngle (Vector3& rkAxis, float& rfAngle)
    const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    float fSqrLength = m_afTuple[1]*m_afTuple[1] + m_afTuple[2]*m_afTuple[2]
        + m_afTuple[3]*m_afTuple[3];
    if (fSqrLength > Math::ZERO_TOLERANCE)
    {
        rfAngle = ((float)2.0)*Math::ACos(m_afTuple[0]);
        float fInvLength = Math::InvSqrt(fSqrLength);
        rkAxis[0] = m_afTuple[1]*fInvLength;
        rkAxis[1] = m_afTuple[2]*fInvLength;
        rkAxis[2] = m_afTuple[3]*fInvLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        rfAngle = (float)0.0;
        rkAxis[0] = (float)1.0;
        rkAxis[1] = (float)0.0;
        rkAxis[2] = (float)0.0;
    }
}

inline void Quaternion::ToEulerZXY(float &Z, float &X, float &Y)
{
	/*
	double test = q1.x*q1.y + q1.z*q1.w;
	if (test > 0.499) { // singularity at north pole
		heading = 2 * atan2(q1.x,q1.w);
		attitude = Math.PI/2;
		bank = 0;
		return;
	}	if (test < -0.499) { // singularity at south pole
		heading = -2 * atan2(q1.x,q1.w);
		attitude = - Math.PI/2;
		bank = 0;
		return;
	}    double sqx = q1.x*q1.x;    double sqy = q1.y*q1.y;    double sqz = q1.z*q1.z;
    heading = atan2(2*q1.y*q1.w-2*q1.x*q1.z , 1 - 2*sqy - 2*sqz);
	attitude = asin(2*test);
	bank = atan2(2*q1.x*q1.w-2*q1.y*q1.z , 1 - 2*sqx - 2*sqz)
	*/

	double test = m_afTuple[1]*m_afTuple[2] + m_afTuple[3]*m_afTuple[0];
	if (test > 0.499) 
	{ 
		// singularity at north pole
		Y = 2 * Math::ATan2(m_afTuple[1], m_afTuple[0]);
		X = Math::ONE_PI/2;
		Z = 0;
		return;
	}	
	if (test < -0.499) 
	{ 
		// singularity at south pole
		Y = -2 * Math::ATan2(m_afTuple[1], m_afTuple[0]);
		X = - Math::ONE_PI/2;
		Z = 0;
		return;
	}    

	float sqx	= m_afTuple[1]*m_afTuple[1];    
	float sqy	= m_afTuple[2]*m_afTuple[2];
	float sqz	= m_afTuple[3]*m_afTuple[3];
	Y       	= Math::ATan2(2*m_afTuple[2]*m_afTuple[0]-2*m_afTuple[1]*m_afTuple[3], 1 - 2*sqy - 2*sqz);
	X       	= Math::ASin(2*test);
	Z    		= Math::ATan2(2*m_afTuple[1]*m_afTuple[0]-2*m_afTuple[2]*m_afTuple[3], 1 - 2*sqx - 2*sqz);
}

//----------------------------------------------------------------------------
inline float Quaternion::Length () const
{
    return Math::Sqrt(
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] +
        m_afTuple[3]*m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline float Quaternion::SquaredLength () const
{
    return
        m_afTuple[0]*m_afTuple[0] +
        m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] +
        m_afTuple[3]*m_afTuple[3];
}
//----------------------------------------------------------------------------
inline float Quaternion::Dot (const Quaternion& rkQ) const
{
    float fDot = (float)0.0;
    for (int i = 0; i < 4; i++)
    {
        fDot += m_afTuple[i]*rkQ.m_afTuple[i];
    }
    return fDot;
}
//----------------------------------------------------------------------------
inline float Quaternion::Normalize ()
{
    float fLength = Length();
    int i;

    if (fLength > Math::ZERO_TOLERANCE)
    {
        float fInvLength = ((float)1.0)/fLength;
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] *= fInvLength;
        }
    }
    else
    {
        fLength = (float)0.0;
        for (i = 0; i < 4; i++)
        {
            m_afTuple[i] = (float)0.0;
        }
    }

    return fLength;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::Inverse () const
{
    Quaternion kInverse;

    float fNorm = (float)0.0;
    int i;
    for (i = 0; i < 4; i++)
    {
        fNorm += m_afTuple[i]*m_afTuple[i];
    }

    if (fNorm > (float)0.0)
    {
        float fInvNorm = ((float)1.0)/fNorm;
        kInverse.m_afTuple[0] = m_afTuple[0]*fInvNorm;
        kInverse.m_afTuple[1] = -m_afTuple[1]*fInvNorm;
        kInverse.m_afTuple[2] = -m_afTuple[2]*fInvNorm;
        kInverse.m_afTuple[3] = -m_afTuple[3]*fInvNorm;
    }
    else
    {
        // return an invalid result to flag the error
        for (i = 0; i < 4; i++)
        {
            kInverse.m_afTuple[i] = (float)0.0;
        }
    }

    return kInverse;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::Conjugate () const
{
    return Quaternion(m_afTuple[0],-m_afTuple[1],-m_afTuple[2],-m_afTuple[3]);
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::Exp () const
{
    // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    Quaternion kResult;

    float fAngle = Math::Sqrt(m_afTuple[1]*m_afTuple[1] +
        m_afTuple[2]*m_afTuple[2] + m_afTuple[3]*m_afTuple[3]);

    float fSin = Math::Sin(fAngle);
    kResult.m_afTuple[0] = Math::Cos(fAngle);

    int i;

    if (Math::FAbs(fSin) >= Math::ZERO_TOLERANCE)
    {
        float fCoeff = fSin/fAngle;
        for (i = 1; i <= 3; i++)
        {
            kResult.m_afTuple[i] = fCoeff*m_afTuple[i];
        }
    }
    else
    {
        for (i = 1; i <= 3; i++)
        {
            kResult.m_afTuple[i] = m_afTuple[i];
        }
    }

    return kResult;
}
//----------------------------------------------------------------------------
inline Quaternion Quaternion::Log () const
{
    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    Quaternion kResult;
    kResult.m_afTuple[0] = (float)0.0;

    int i;

    if (Math::FAbs(m_afTuple[0]) < (float)1.0)
    {
        float fAngle = Math::ACos(m_afTuple[0]);
        float fSin = Math::Sin(fAngle);
        if (Math::FAbs(fSin) >= Math::ZERO_TOLERANCE)
        {
            float fCoeff = fAngle/fSin;
            for (i = 1; i <= 3; i++)
            {
                kResult.m_afTuple[i] = fCoeff*m_afTuple[i];
            }
            return kResult;
        }
    }

    for (i = 1; i <= 3; i++)
    {
        kResult.m_afTuple[i] = m_afTuple[i];
    }
    return kResult;
}
//----------------------------------------------------------------------------
inline Vector3 Quaternion::Rotate (const Vector3& rkVector) const
{
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no float work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in Quaternion::ToRotationMatrix.
    // The vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...

    Matrix4 kRot;
    ToRotationMatrix(kRot);
    return kRot*rkVector;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::Slerp (float fT, const Quaternion& rkP, const Quaternion& rkQ)
{
    float fCos = rkP.Dot(rkQ);
    float fAngle = Math::ACos(fCos);

    if (Math::FAbs(fAngle) >= Math::ZERO_TOLERANCE)
    {
        float fSin = Math::Sin(fAngle);
        float fInvSin = ((float)1.0)/fSin;
        float fCoeff0 = Math::Sin(((float)1.0-fT)*fAngle)*fInvSin;
        float fCoeff1 = Math::Sin(fT*fAngle)*fInvSin;
        *this = fCoeff0*rkP + fCoeff1*rkQ;
    }
    else
    {
        *this = rkP;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::SlerpExtraSpins (float fT,
    const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins)
{
    float fCos = rkP.Dot(rkQ);
    float fAngle = Math::ACos(fCos);

    if (Math::FAbs(fAngle) >= Math::ZERO_TOLERANCE)
    {
        float fSin		= Math::Sin(fAngle);
        float fPhase	= Math::ONE_PI*iExtraSpins*fT;
        float fInvSin	= ((float)1.0)/fSin;
        float fCoeff0	= Math::Sin(((float)1.0-fT)*fAngle-fPhase)*fInvSin;
        float fCoeff1	= Math::Sin(fT*fAngle + fPhase)*fInvSin;
        *this = fCoeff0*rkP + fCoeff1*rkQ;
    }
    else
    {
        *this = rkP;
    }

    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::Intermediate (const Quaternion& rkQ0,
    const Quaternion& rkQ1, const Quaternion& rkQ2)
{
    // assert:  Q0, Q1, Q2 all unit-length
    Quaternion kQ1Inv = rkQ1.Conjugate();
    Quaternion kP0 = kQ1Inv*rkQ0;
    Quaternion kP2 = kQ1Inv*rkQ2;
    Quaternion kArg = -((float)0.25)*(kP0.Log()+kP2.Log());
    Quaternion kA = rkQ1*kArg.Exp();
    *this = kA;

    return *this;
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::Squad (float fT, const Quaternion& rkQ0,
    const Quaternion& rkA0, const Quaternion& rkA1, const Quaternion& rkQ1)
{
    float fSlerpT = ((float)2.0)*fT*((float)1.0-fT);
    Quaternion kSlerpP = Slerp(fT,rkQ0,rkQ1);
    Quaternion kSlerpQ = Slerp(fT,rkA0,rkA1);
    return Slerp(fSlerpT,kSlerpP,kSlerpQ);
}
//----------------------------------------------------------------------------
inline Quaternion& Quaternion::Align (const Vector3& rkV1,
    const Vector3& rkV2)
{
    // If V1 and V2 are not parallel, the axis of rotation is the unit-length
    // vector U = Cross(V1,V2)/Length(Cross(V1,V2)).  The angle of rotation,
    // A, is the angle between V1 and V2.  The quaternion for the rotation is
    // q = cos(A/2) + sin(A/2)*(ux*i+uy*j+uz*k) where U = (ux,uy,uz).
    //
    // (1) Rather than extract A = acos(Dot(V1,V2)), multiply by 1/2, then
    //     compute sin(A/2) and cos(A/2), we reduce the computational costs by
    //     computing the bisector B = (V1+V2)/Length(V1+V2), so cos(A/2) =
    //     Dot(V1,B).
    //
    // (2) The rotation axis is U = Cross(V1,B)/Length(Cross(V1,B)), but
    //     Length(Cross(V1,B)) = Length(V1)*Length(B)*sin(A/2) = sin(A/2), in
    //     which case sin(A/2)*(ux*i+uy*j+uz*k) = (cx*i+cy*j+cz*k) where
    //     C = Cross(V1,B).
    //
    // If V1 = V2, then B = V1, cos(A/2) = 1, and U = (0,0,0).  If V1 = -V2,
    // then B = 0.  This can happen even if V1 is approximately -V2 using
    // floating point arithmetic, since Vector3::Normalize checks for
    // closeness to zero and returns the zero vector accordingly.  The test
    // for exactly zero is usually not recommend for floating point
    // arithmetic, but the implementation of Vector3::Normalize guarantees
    // the comparison is robust.  In this case, the A = pi and any axis
    // perpendicular to V1 may be used as the rotation axis.

    Vector3 kBisector = rkV1 + rkV2;
    kBisector.Normalize();

    float fCosHalfAngle = rkV1.Dot(kBisector);
    Vector3 kCross;

    m_afTuple[0] = fCosHalfAngle;

    if (fCosHalfAngle != (float)0.0)
    {
        kCross = rkV1.Cross(kBisector);
        m_afTuple[1] = kCross.X();
        m_afTuple[2] = kCross.Y();
        m_afTuple[3] = kCross.Z();
    }
    else
    {
        float fInvLength;
        if (Math::FAbs(rkV1[0]) >= Math::FAbs(rkV1[1]))
        {
            // V1.x or V1.z is the largest magnitude component
            fInvLength = Math::InvSqrt(rkV1[0]*rkV1[0] +
                rkV1[2]*rkV1[2]);
            m_afTuple[1] = -rkV1[2]*fInvLength;
            m_afTuple[2] = (float)0.0;
            m_afTuple[3] = +rkV1[0]*fInvLength;
        }
        else
        {
            // V1.y or V1.z is the largest magnitude component
            fInvLength = Math::InvSqrt(rkV1[1]*rkV1[1] +
                rkV1[2]*rkV1[2]);
            m_afTuple[1] = (float)0.0;
            m_afTuple[2] = +rkV1[2]*fInvLength;
            m_afTuple[3] = -rkV1[1]*fInvLength;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------
inline void Quaternion::DecomposeTwistTimesSwing (const Vector3& rkV1, Quaternion& rkTwist, Quaternion& rkSwing)
{
    Vector3 kV2 = Rotate(rkV1);
    rkSwing = Align(rkV1,kV2);
    rkTwist = (*this)*rkSwing.Conjugate();
}
//----------------------------------------------------------------------------
inline void Quaternion::DecomposeSwingTimesTwist (const Vector3& rkV1, Quaternion& rkSwing, Quaternion& rkTwist)
{
    Vector3 kV2 = Rotate(rkV1);
    rkSwing = Align(rkV1,kV2);
    rkTwist = rkSwing.Conjugate()*(*this);
}
//----------------------------------------------------------------------------
inline void Quaternion::read(InputStream &is)
{
	is >> m_afTuple[0] >> m_afTuple[1] >> m_afTuple[2] >> m_afTuple[3];
}
//----------------------------------------------------------------------------
inline void Quaternion::write(OutputStream &os) const
{
	os << m_afTuple[0] << m_afTuple[1] << m_afTuple[2] << m_afTuple[3];
}