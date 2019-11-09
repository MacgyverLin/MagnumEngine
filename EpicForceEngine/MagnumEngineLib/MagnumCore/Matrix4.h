///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Matrix4_h_
#define _Matrix4_h_

// Matrix operations are applied on the left.  For example, given a matrix M
// and a vector V, matrix-times-vector is M*V.  That is, V is treated as a
// column vector.  Some graphics APIs use V*M where V is treated as a row
// vector.  In this context the "M" matrix is floatly a transpose of the M as
// represented in Wild Magic.  Similarly, to apply two matrix operations M0
// and M1, in that order, you compute M1*M0 so that the transform of a vector
// is (M1*M0)*V = M1*(M0*V).  Some graphics APIs use M0*M1, but again these
// matrices are the transpose of those as represented in Wild Magic.  You
// must therefore be careful about how you interface the transformation code
// with graphics APIS.
//
// For memory organization it might seem natural to chose float[N][N] for the
// matrix storage, but this can be a problem on a platform/console that
// chooses to store the data in column-major rather than row-major format.
// To avoid potential portability problems, the matrix is stored as float[N*N]
// and organized in row-major order.  That is, the entry of the matrix in row
// r (0 <= r < N) and column c (0 <= c < N) is stored at index i = c+N*r
// (0 <= i < N*N).
#include "Stage.h"
#include "Plane3.h"
#include "Vector4.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace Magnum
{

class Matrix4
{
public:
    // If bZero is true, create the zero matrix.  Otherwise, create the
    // identity matrix.
    Matrix4 (bool bZero = true);

    // copy constructor
    Matrix4 (const Matrix4& rkM);

    // input Mrc is in row r, column c.
    Matrix4 (float fM00, float fM01, float fM02, float fM03,
             float fM10, float fM11, float fM12, float fM13,
             float fM20, float fM21, float fM22, float fM23,
             float fM30, float fM31, float fM32, float fM33);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..15]={m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,
    //                        m23,m30,m31,m32,m33} [row major]
    //   false: entry[0..15]={m00,m10,m20,m30,m01,m11,m21,m31,m02,m12,m22,
    //                        m32,m03,m13,m23,m33} [col major]
    Matrix4 (const float afEntry[16], bool bRowMajor=true);

    // input Mrc is in row r, column c.
    void Set (float fM00, float fM01, float fM02, float fM03,
              float fM10, float fM11, float fM12, float fM13,
              float fM20, float fM21, float fM22, float fM23,
              float fM30, float fM31, float fM32, float fM33);

    void initZero (); 
	void initIdentity();
	void initTranslate(float x, float y, float z);
	void initRotateX(float radian);
	void initRotateY(float radian);
	void initRotateZ(float radian);
	void initRotateZXY(float z, float x, float y);
	void initRotateZYX(float z, float y, float x);
	void initRotateAxisAngle(const Vector3 &axis, float radian);
	void initScale(float scale);
	void initScale(float x, float y, float z);

	void initTranslateRotZXYScale(float tx, float ty, float tz, float rz, float rx, float ry, float scale);
	void initTranslateRotZYXScale(float tx, float ty, float tz, 
		                          float rz, float ry, float rx, 
								  float scale);
	void initTranslateRotZYXScale(float tx, float ty, float tz, 
	                              float rx, float ry, float rz, 
								  float sx, float sy, float sz);
	void initTranslateRotAxisAngleScale(float tx, float ty, float tz, const Vector3 &axis, const float radian, float scale);
	void initTranslateScale(float tx, float ty, float tz, float scale);

	void initLookAt(const Vector3 &position, const Vector3 &objective, const Vector3 &up);
	void initLookAtScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale);
	void initStandOn(const Vector3 &position, const Vector3 &objective, const Vector3 &up);
	void initStandOnScale(const Vector3 &position, const Vector3 &objective, const Vector3 &up, float scale);
	
	void initPerspective(float w, float h, float n, float f);
	void initPerspectiveFov(float fovY, float aspect, float n, float f);
	void initPerspectiveOffCenter(float l, float r, float b, float t, float n, float f);

	void initOrthogonal(float w, float h, float n, float f);
	void initOrthogonalOffCenter(float l, float r, float b, float t, float n, float f);

	void orthonormalize();
    // member access
    operator const float* () const;
    operator float* ();
    const float* operator[] (int iRow) const;
    float* operator[] (int iRow);
    float operator() (int iRow, int iCol) const;
    float& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector4& rkV);
    Vector4 GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector4& rkV);
    Vector4 GetColumn (int iCol) const;
    void GetColumnMajor (float* afCMajor) const;

    // assignment
    Matrix4& operator= (const Matrix4& rkM);

    // comparison
    bool operator== (const Matrix4& rkM) const;
    bool operator!= (const Matrix4& rkM) const;
    bool operator<  (const Matrix4& rkM) const;
    bool operator<= (const Matrix4& rkM) const;
    bool operator>  (const Matrix4& rkM) const;
    bool operator>= (const Matrix4& rkM) const;

    // arithmetic operations
    Matrix4 operator+ (const Matrix4& rkM) const;
    Matrix4 operator- (const Matrix4& rkM) const;
    Matrix4 operator* (const Matrix4& rkM) const;
    Matrix4 operator* (float fScalar) const;
    Matrix4 operator/ (float fScalar) const;
    Matrix4 operator- () const;

    // arithmetic updates
    Matrix4& operator+= (const Matrix4& rkM);
    Matrix4& operator-= (const Matrix4& rkM);
    Matrix4& operator*= (float fScalar);
    Matrix4& operator/= (float fScalar);

    // matrix times vector
    Vector4 operator* (const Vector4& rkV) const;  // M * v
	Vector3 operator* (const Vector3& rkV) const;  // M * v
	Vector3 TimesPositionVector(const Vector3& rkV) const;  // M * v
	Vector3 TimesDirectionVector(const Vector3& rkV) const;  // M * v

    // other operations
    Matrix4 Transpose () const;  // M^T
    Matrix4 TransposeTimes (const Matrix4& rkM) const;  // this^T * M
    Matrix4 TimesTranspose (const Matrix4& rkM) const;  // this * M^T
    Matrix4 Inverse () const;
    Matrix4 Adjoint () const;
    float Determinant () const;
    float QForm (const Vector4& rkU, const Vector4& rkV) const;  // u^T*M*v

    // The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
    // where yaw is rotation about the Up vector, pitch is rotation about the
    // Right axis, and roll is rotation about the Direction axis.
    Matrix4 &FromEulerAnglesXYZ (float fYAngle, float fPAngle, float fRAngle);
    Matrix4 &FromEulerAnglesXZY (float fYAngle, float fPAngle, float fRAngle);
    Matrix4 &FromEulerAnglesYXZ (float fYAngle, float fPAngle, float fRAngle);
    Matrix4 &FromEulerAnglesYZX (float fYAngle, float fPAngle, float fRAngle);
    Matrix4 &FromEulerAnglesZXY (float fYAngle, float fPAngle, float fRAngle);
    Matrix4 &FromEulerAnglesZYX (float fYAngle, float fPAngle, float fRAngle);
    bool ToEulerAnglesXYZ(float &rfYAngle, float &rfPAngle, float &rfRAngle) const;
    bool ToEulerAnglesXZY (float &rfYAngle, float &rfPAngle, float &rfRAngle) const;
    bool ToEulerAnglesYXZ (float &rfYAngle, float &rfPAngle, float &rfRAngle) const;
    bool ToEulerAnglesYZX (float &rfYAngle, float &rfPAngle, float &rfRAngle) const;
    bool ToEulerAnglesZXY (float &rfYAngle, float &rfPAngle, float &rfRAngle) const;
    bool ToEulerAnglesZYX (float &rfYAngle, float &rfPAngle, float &rfRAngle) const;

	void FromSRT(const Vector3 &s, const Vector3 &r, const Vector3 &t);
	void ToSRT(Vector3 &s, Vector3 &r, Vector3 &t) const;

    // special matrices
    static const Matrix4 ZERO;
    static const Matrix4 IDENTITY;

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // for indexing into the 1D array of the matrix, iCol+N*iRow
    static int I (int iRow, int iCol);
	static const int RowStartIdxs[4];

    // support for comparisons
    int CompareArrays (const Matrix4& rkM) const;

    float m_afEntry[16];
};

// c * M
//inline Matrix4 operator* (float fScalar, const Matrix4& rkM);
// v^T * M
//inline Vector4 operator* (const Vector4& rkV, const Matrix4& rkM);

#include "Matrix4.inl"

};

#endif

