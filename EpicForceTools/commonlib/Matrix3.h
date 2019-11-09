///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#ifndef _Matrix3_h_
#define _Matrix3_h_

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

// The (x,y,z) coordinate system is assumed to be right-handed.  Coordinate
// axis rotation matrices are of the form
//   RX =    1       0       0
//           0     cos(t) -sin(t)
//           0     sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the yz-plane
//   RY =  cos(t)    0     sin(t)
//           0       1       0
//        -sin(t)    0     cos(t)
// where t > 0 indicates a counterclockwise rotation in the zx-plane
//   RZ =  cos(t) -sin(t)    0
//         sin(t)  cos(t)    0
//           0       0       1
// where t > 0 indicates a counterclockwise rotation in the xy-plane.
#include "Stage.h"
#include "EMath.h"
#include "Vector3.h"

namespace EpicForce
{

class Matrix3
{
public:
    // If bZero is true, create the zero matrix.  Otherwise, create the
    // identity matrix.
    Matrix3 (bool bZero = true);

    // copy constructor
    Matrix3 (const Matrix3& rkM);

    // input Mrc is in row r, column c.
    Matrix3 (float fM00, float fM01, float fM02,
             float fM10, float fM11, float fM12,
             float fM20, float fM21, float fM22);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..8]={m00,m01,m02,m10,m11,m12,m20,m21,m22} [row major]
    //   false: entry[0..8]={m00,m10,m20,m01,m11,m21,m02,m12,m22} [col major]
    Matrix3 (const float afEntry[9], bool bRowMajor);

    // Create matrices based on vector input.  The Boolean is interpreted as
    //   true: vectors are columns of the matrix
    //   false: vectors are rows of the matrix
    Matrix3 (const Vector3& rkU, const Vector3& rkV,
        const Vector3& rkW, bool bColumns);
    Matrix3 (const Vector3* akV, bool bColumns);

    // create a diagonal matrix
    Matrix3 (float fM00, float fM11, float fM22);

    // Create rotation matrices (positive angle - counterclockwise).  The
    // angle must be in radians, not degrees.
    Matrix3 (const Vector3& rkAxis, float fAngle);

    // create a tensor product U*V^T
    Matrix3 (const Vector3& rkU, const Vector3& rkV);

    // input Mrc is in row r, column c.
    void Set (float fM00, float fM01, float fM02,
              float fM10, float fM11, float fM12,
              float fM20, float fM21, float fM22);

    // create various matrices
    Matrix3& MakeZero ();
    Matrix3& MakeIdentity ();
    Matrix3& MakeDiagonal (float fM00, float fM11, float fM22);
    Matrix3& FromAxisAngle (const Vector3& rkAxis, float fAngle);
    Matrix3& MakeTensorProduct (const Vector3& rkU,
        const Vector3& rkV);

    // member access
    operator const float* () const;
    operator float* ();
    const float* operator[] (int iRow) const;
    float* operator[] (int iRow);
    float operator() (int iRow, int iCol) const;
    float& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector3& rkV);
    Vector3 GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector3& rkV);
    Vector3 GetColumn (int iCol) const;
    void GetColumnMajor (float* afCMajor) const;

    // assignment
    Matrix3& operator= (const Matrix3& rkM);

    // comparison
    bool operator== (const Matrix3& rkM) const;
    bool operator!= (const Matrix3& rkM) const;
    bool operator<  (const Matrix3& rkM) const;
    bool operator<= (const Matrix3& rkM) const;
    bool operator>  (const Matrix3& rkM) const;
    bool operator>= (const Matrix3& rkM) const;

    // arithmetic operations
    Matrix3 operator+ (const Matrix3& rkM) const;
    Matrix3 operator- (const Matrix3& rkM) const;
    Matrix3 operator* (const Matrix3& rkM) const;
    Matrix3 operator* (float fScalar) const;
    Matrix3 operator/ (float fScalar) const;
    Matrix3 operator- () const;

    // arithmetic updates
    Matrix3& operator+= (const Matrix3& rkM);
    Matrix3& operator-= (const Matrix3& rkM);
    Matrix3& operator*= (float fScalar);
    Matrix3& operator/= (float fScalar);

    // matrix times vector
    Vector3 operator* (const Vector3& rkV) const;  // M * v

    // other operations
    Matrix3 Transpose () const;  // M^T
    Matrix3 TransposeTimes (const Matrix3& rkM) const;  // this^T * M
    Matrix3 TimesTranspose (const Matrix3& rkM) const;  // this * M^T
    Matrix3 Inverse () const;
    Matrix3 Adjoint () const;
    float Determinant () const;
    float QForm (const Vector3& rkU,
        const Vector3& rkV) const;  // u^T*M*v
    Matrix3 TimesDiagonal (const Vector3& rkDiag) const;  // M*D
    Matrix3 DiagonalTimes (const Vector3& rkDiag) const;  // D*M

    // The matrix must be a rotation for these functions to be valid.  The
    // last function uses Gram-Schmidt orthonormalization applied to the
    // columns of the rotation matrix.  The angle must be in radians, not
    // degrees.
    void ToAxisAngle (Vector3& rkAxis, float& rfAngle) const;
    void Orthonormalize ();

    // The matrix must be symmetric.  Factor M = R * D * R^T where
    // R = [u0|u1|u2] is a rotation matrix with columns u0, u1, and u2 and
    // D = diag(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0,
    // d1, and d2.  The eigenvector u[i] corresponds to eigenvector d[i].
    // The eigenvalues are ordered as d0 <= d1 <= d2.
    void EigenDecomposition (Matrix3& rkRot, Matrix3& rkDiag) const;

    // The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
    // where yaw is rotation about the Up vector, pitch is rotation about the
    // Right axis, and roll is rotation about the Direction axis.
    Matrix3& FromEulerAnglesXYZ (float fYAngle, float fPAngle, float fRAngle);
    Matrix3& FromEulerAnglesXZY (float fYAngle, float fPAngle, float fRAngle);
    Matrix3& FromEulerAnglesYXZ (float fYAngle, float fPAngle, float fRAngle);
    Matrix3& FromEulerAnglesYZX (float fYAngle, float fPAngle, float fRAngle);
    Matrix3& FromEulerAnglesZXY (float fYAngle, float fPAngle, float fRAngle);
    Matrix3& FromEulerAnglesZYX (float fYAngle, float fPAngle, float fRAngle);
    bool ToEulerAnglesXYZ (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesXZY (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesYXZ (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesYZX (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesZXY (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;
    bool ToEulerAnglesZYX (float& rfYAngle, float& rfPAngle,
        float& rfRAngle) const;

    // SLERP (spherical linear interpolation) without quaternions.  Computes
    // R(t) = R0*(Transpose(R0)*R1)^t.  If Q is a rotation matrix with
    // unit-length axis U and angle A, then Q^t is a rotation matrix with
    // unit-length axis U and rotation angle t*A.
    static Matrix3 Slerp (float fT, const Matrix3& rkR0,
        const Matrix3& rkR1);

    // Singular value decomposition, M = L*S*R, where L and R are orthogonal
    // and S is a diagonal matrix whose diagonal entries are nonnegative.
    void SingularValueDecomposition (Matrix3& rkL, Matrix3& rkS,
        Matrix3& rkR) const;
    void SingularValueComposition (const Matrix3& rkL, const Matrix3& rkS,
        const Matrix3& rkR);

    // factor M = Q*D*U with orthogonal Q, diagonal D, upper triangular U
    void QDUDecomposition (Matrix3& rkQ, Matrix3& rkD, Matrix3& rkU) const;

    // special matrices
    static const Matrix3 ZERO;
    static const Matrix3 IDENTITY;

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
    // Support for eigendecomposition.  The Tridiagonalize function applies
    // a Householder transformation to the matrix.  If that transformation
    // is the identity (the matrix is already tridiagonal), then the return
    // value is 'false'.  Otherwise, the transformation is a reflection and
    // the return value is 'true'.  The QLAlgorithm returns 'true' iff the
    // QL iteration scheme converged.
    bool Tridiagonalize (float afDiag[3], float afSubd[2]);
    bool QLAlgorithm (float afDiag[3], float afSubd[2]);

    // support for singular value decomposition
    static void Bidiagonalize (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR);
    static void GolubKahanStep (Matrix3& rkA, Matrix3& rkL, Matrix3& rkR);

    // for indexing into the 1D array of the matrix, iCol+N*iRow
    static int I (int iRow, int iCol);

    // support for comparisons
    int CompareArrays (const Matrix3& rkM) const;

    float m_afEntry[9];
};

// c * M
//Matrix3 operator* (float fScalar, const Matrix3& rkM);
// v^T * M
//Vector3 operator* (const Vector3& rkV, const Matrix3& rkM);

#include "Matrix3.inl"

}

#endif

