#pragma once

#include <cassert>
#include <initializer_list>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <utility>
#include "Base.hpp"

/// right hand
/// up--y, forward--z, side x
/// major column
namespace LaughCrab {
    namespace LaughMath {
        /// Constants
        template<typename T>
        inline T Pi() { return static_cast<T>(3.14159265358979323846264338327950288); }
        template<typename T>
        inline T TowPi() { return static_cast<T>(6.28318530717958647692528676655900576); }
        template<typename T>
        inline T SqrtPi() { return static_cast<T>(1.772453850905516027); }
        template<typename T>
        inline T HalfPi() { return static_cast<T>(1.57079632679489661923132169163975144); }
        template<typename T>
        inline T PiOverTwo() { return static_cast<T>(1.57079632679489661923132169163975144); }

        /// degrees --> radians
        template<typename T>
        inline T Radians(T degrees) { return degrees * static_cast<T>(0.01745329251994329576923690768489); }
        /// radians --> degrees
        template<typename T>
        inline T Degrees(T radians) { return radians * static_cast<T>(57.295779513082320876798154814105); }

        enum { i_x = 0, i_y = 1, i_z = 2, i_w = 3 };
        enum { i_r = 0, i_g = 1, i_b = 2, i_a = 3 };
        enum { i_s = 0, i_t = 1, i_p = 2, i_q = 3 };

        ///Vector
        template<typename T, Size N>
        struct Vector {
            T storage[N];

            Vector() { Set(0); }
            Vector(T e) { Set(e); }
            Vector(std::initializer_list<T> list) { Set(list); }
            Vector(Vector const &u) = default;
            Vector(Vector &&u) noexcept = default;
            Vector &operator=(Vector const &u) = default;
            Vector &operator=(Vector &&u) noexcept = default;

            T Norm() const { return std::sqrt(NormSquare()); }
            T NormSquare() const {
                T normSquare = 0.0f;
                for (Size i = 0; i < N; i++) {
                    normSquare += storage[i] * storage[i];
                }
                return normSquare;
            }

            T &operator[](Size i) { return storage[i]; }
            T const &operator[](Size i) const { return storage[i]; }

            T *Get() { return reinterpret_cast<T *>(storage); }
            T const *Get() const { return reinterpret_cast<const T *>(storage); }

            void Set(std::initializer_list<T> list) {
                assert(list.size() <= N);
                Size i = 0;
                for (T e : list) {
                    storage[i++] = e;
                }
            }
            void Set(T e) {
                for (Size i = 0; i < N; i++) {
                    storage[i] = e;
                }
            }
            void Set(Size i, T e) {
                assert(i < N);
                storage[i] = e;
            }

            T Trace() {
                T trace = 0.0f;
                for (T e : storage) {
                    trace += e;
                }
                return trace;
            }

            Vector &operator+=(Vector const &v) {
                for (Size i = 0; i < N; i++) {
                    storage[i] += v[i];
                }
                return *this;
            }
            Vector &operator-=(Vector const &v) {
                for (Size i = 0; i < N; i++) {
                    storage[i] -= v[i];
                }
                return *this;
            }

            Vector &operator+=(T e) {
                *this += Vector(e);
                return *this;
            }
            Vector &operator-=(T e) {
                *this -= Vector(e);
                return *this;
            }
            Vector &operator*=(const Vector &u) {
                for (Size i = 0; i < N; ++i) {
                    storage[i] *= u[i];
                }
                return *this;
            }
            Vector &operator*=(T e) {
                for (Size i = 0; i < N; i++) {
                    storage[i] *= e;
                }
                return *this;
            }
            Vector &operator/=(T e) {
                assert(abs(e) > std::numeric_limits<T>::epsilon());
                for (Size i = 0; i < N; i++) {
                    storage[i] /= e;
                }
                return *this;
            }

            Vector operator-() { return *this * static_cast<T>(-1); }
        };

        template<typename T, Size N>
        inline Vector<T, N> operator+(Vector<T, N> const &u, Vector<T, N> const &v) {
            return Vector<T, N>(u) += v;
        }
        ///U + scalar
        template<typename T, Size N>
        inline Vector<T, N> operator+(Vector<T, N> const &u, T e) {
            return u + Vector<T, N>(e);
        }
        ///U - V
        template<typename T, Size N>
        inline Vector<T, N> operator-(Vector<T, N> const &u, Vector<T, N> const &v) {
            return Vector<T, N>(u) -= v;
        }
        ///U - scalar
        template<typename T, Size N>
        inline Vector<T, N> operator-(Vector<T, N> const &u, T e) {
            return u - Vector<T, N>(e);
        }
        /// scalar - U
        template<typename T, Size N>
        inline Vector<T, N> operator-(T e, Vector<T, N> const &u) {
            return Vector<T, N>(e) - u;
        }

        template<typename T, Size N>
        inline Vector<T, N> operator*(const Vector<T, N> &u, const Vector<T, N> &v) {
            return Vector<T, N>(u) *= v;
        };
        ///U * scalar
        template<typename T, Size N>
        inline Vector<T, N> operator*(Vector<T, N> const &u, T e) {
            return Vector<T, N>(u) *= e;
        }
        ///scalar * U
        template<typename T, Size N>
        inline Vector<T, N> operator*(T e, Vector<T, N> const &u) {
            return u * e;
        }
        ///U / scalar
        template<typename T, Size N>
        inline Vector<T, N> operator/(Vector<T, N> const &u, T e) {
            return Vector<T, N>(u) /= e;
        }
        ///Norm
        template<typename T, Size N>
        inline T Norm(Vector<T, N> const &u) {
            return u.Norm();
        }
        /// Dot
        template<typename T, Size N>
        inline T Dot(Vector<T, N> const &u, Vector<T, N> const &v) {
            return Vector<T, N>(u * v).Trace();
        }
        /// Cross
        template<typename T>
        inline Vector<T, 3> Cross(Vector<T, 3> const &u, Vector<T, 3> const &v) {
            return Vector<T, 3>{u[i_y] * v[i_z] - v[i_y] * u[i_z],
                                u[i_z] * v[i_x] - v[i_z] * u[i_x],
                                u[i_x] * v[i_y] - v[i_x] * u[i_y]};
        }
        /// Normalize
        template<typename T, Size N>
        inline Vector<T, N> Normalize(Vector<T, N> const &u) {
            return Vector<T, N>(u) / Norm(u);
        }
        /// Distance
        template<typename T, Size N>
        inline T Distance(Vector<T, N> const &u, Vector<T, N> const &v) {
            return Norm(u - v);
        }
        /// FaceForward
        template<typename T, Size N>
        inline Vector<T, N> FaceForward(Vector<T, N> const &Nret, Vector<T, N> const &I, Vector<T, N> const &Nref) {
            return Dot(Nref, I) < static_cast<T>(0) ? Nret : -Nret;
        }
        /// For the incident vector I and surface orientation N, the reflection direction : result = I - 2.0 * dot(N, I) * N.
        /// N must be already Normalized
        template<typename T, Size N>
        inline Vector<T, N> Reflect(Vector<T, N> const &I, Vector<T, N> const &Nref) {
            return I - Nref * (Dot(Nref, I) * static_cast<T>(2));
        }
        /// For the incident vector I and surface normal N, and the ratio of indices of refraction eta,
        /// return the refraction vector. I and N must be already Normalized
        /// k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I))
        /// if (k < 0.0) return genType(0.0) // or genDType(0.0)
        /// else return eta * I - (eta * dot(N, I) + sqrt(k)) * N
        template<typename T, Size N>
        inline Vector<T, N> Refract(Vector<T, N> const &I, Vector<T, N> const &Nref, T eta) {
            T const dotValue = Dot(Nref, I);
            T const k = static_cast<T>(1) - eta * eta * (static_cast<T>(1) - dotValue * dotValue);
            return (eta * I - (eta * dotValue + std::sqrt(k)) * Nref) * static_cast<T>(k >= static_cast<T>(0));
        }

        /// matrix
        template<typename T, Size Rows, Size Cols>
        struct Matrix {
            using col_type = Vector<T, Rows>;
            using row_type = Vector<T, Cols>;
            using transpose_type = Matrix<T, Cols, Rows>;
            using col_ref_type = Vector<T &, Rows>;

            col_type storage[Cols];

            Matrix() { SetAll(0); }
            Matrix(T e) { Set(e); }
            Matrix(std::initializer_list<T> list) { Set(list); }
            Matrix(std::initializer_list<col_type> &list) {
                assert(list.size() <= Cols);
                Size i = 0;
                for (auto &r : list) {
                    Set(i++, r);
                }
            }
            Matrix(Matrix const &u) = default;
            Matrix(Matrix &&u) noexcept = default;
            Matrix &operator=(Matrix const &u) = default;
            Matrix &operator=(Matrix &&u) noexcept = default;

            T *Get() { return reinterpret_cast<T *>(storage); }
            T const *Get() const { return reinterpret_cast<const T *>(storage); }

            col_type &operator[](Size i) { return storage[i]; }
            col_type const &operator[](Size i) const { return storage[i]; }

            row_type GetRow(Size i) const {
                assert(i < Rows);
                row_type row;
                for (Size j = 0; j < Cols; ++j) {
                    row[j] = storage[j][i];
                }
                return row;
            }

            void SetAll(T e) {
                for (Size i = 0; i < Cols; i++) {
                    for (Size j = 0; j < Rows; j++) {
                        storage[i][j] = e;
                    }
                }
            }

            void Set(T e) {
                SetAll(0);
                for (Size i = 0; i < std::min(Rows, Cols); ++i) {
                    storage[i][i] = e;
                }
            }
            void Set(std::initializer_list<T> list) {
                assert(list.size() <= Rows * Cols);
                T *d = reinterpret_cast<T *>(storage);
                for (T e : list) {
                    *d = e;
                    d++;
                }
            }
            void Set(Size i, col_type const &col) {
                assert(i < Cols);
                storage[i] = col;
            }

            transpose_type Transpose() {
                transpose_type mat;
                for (Size i = 0; i < Rows; ++i) {
                    mat.Set(i, GetRow(i));
                }
                return mat;
            }

            Matrix &operator+=(Matrix const &m) {
                for (Size i = 0; i < Cols; ++i) {
                    storage[i] += m[i];
                }
                return *this;
            }
            Matrix &operator-=(Matrix const &m) {
                for (Size i = 0; i < Cols; ++i) {
                    storage[i] -= m[i];
                }
                return *this;
            }

            Matrix &operator+=(T e) {
                for (Size i = 0; i < Cols; i++) {
                    for (Size j = 0; j < Rows; j++) {
                        storage[i][j] += e;
                    }
                }
                return *this;
            }
            Matrix &operator-=(T e) {
                for (Size i = 0; i < Cols; i++) {
                    for (Size j = 0; j < Rows; j++) {
                        storage[i][j] -= e;
                    }
                }
                return *this;
            }
            Matrix &operator*=(const Matrix &m) {
                assert(Rows == Cols);
                Matrix tmp;
                for (Size col = 0; col < Rows; ++col) {//col
                    for (Size row = 0; row < Rows; ++row) {//row
                        tmp[col][row] = Dot(GetRow(row), m[col]);
                    }
                }
                *this = tmp;
                return *this;
            }
            Matrix &operator*=(T e) {
                for (Size i = 0; i < Cols; i++) {
                    for (Size j = 0; j < Rows; j++) {
                        storage[i][j] *= e;
                    }
                }
                return *this;
            }
            Matrix &operator/=(T e) {
                for (Size i = 0; i < Cols; i++) {
                    for (Size j = 0; j < Rows; j++) {
                        storage[i][j] /= e;
                    }
                }
                return *this;
            }
            Matrix operator-() { return *this * static_cast<T>(-1); }
        };

        template<typename T>
        T Determinant(Matrix<T, 4, 4> const &m) {
            T B22_33 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
            T B21_33 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
            T B21_32 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
            T B20_33 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
            T B20_32 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
            T B22_31 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

            T A00 = +(m[1][1] * B22_33 - m[1][2] * B21_33 + m[1][3] * B21_32);
            T A01 = -(m[1][0] * B22_33 - m[1][2] * B20_33 + m[1][3] * B20_32);
            T A02 = +(m[1][0] * B21_33 - m[1][1] * B20_33 + m[1][3] * B22_31);
            T A03 = -(m[1][0] * B21_32 - m[1][1] * B20_32 + m[1][2] * B22_31);

            return m[0][0] * A00 + m[0][1] * A01 + m[0][2] * A02 + m[0][3] * A03;
        };

        template<typename T>
        Matrix<T, 4, 4> Inverse(Matrix<T, 4, 4> const &m) {
            return m;
        };

        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> OuterProduct(Vector<T, Rows> const &u, Vector<T, Cols> const &v) {
            Matrix<T, Rows, Cols> m;
            for (Size col = 0; col < Cols; col++) {
                for (Size row = 0; row < Rows; row++) {
                    m[col][row] = u[row] * v[col];
                }
            }
            return m;
        }

        template<typename T, Size Rows, Size Cols>
        Matrix<T, Rows, Rows> operator*(Matrix<T, Rows, Cols> const &u, Matrix<T, Cols, Rows> const &v) {
            Matrix<T, Rows, Rows> tmp;
            for (Size col = 0; col < Rows; ++col) {//col
                for (Size row = 0; row < Rows; ++row) {//row
                    tmp[col][row] = Dot(u.GetRow(row), v[col]);
                }
            }
            return tmp;
        };

        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator+(Matrix<T, Rows, Cols> const &u, Matrix<T, Rows, Cols> const &v) {
            return Matrix<T, Rows, Cols>(u) += v;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator+(Matrix<T, Rows, Cols> const &u, T e) {
            return Matrix<T, Rows, Cols>(u) += e;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator+(T e, Matrix<T, Rows, Cols> const &v) {
            return v + e;
        }
        /// -
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator-(Matrix<T, Rows, Cols> const &u, Matrix<T, Rows, Cols> const &v) {
            return Matrix<T, Rows, Cols>(u) -= v;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator-(Matrix<T, Rows, Cols> const &u, T e) {
            return Matrix<T, Rows, Cols>(u) -= e;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator-(T e, Matrix<T, Rows, Cols> const &v) {
            return (-v) + e;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator*(Matrix<T, Rows, Cols> const &u, T e) {
            return Matrix<T, Rows, Cols>(u) *= e;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator*(T e, Matrix<T, Rows, Cols> const &v) {
            return v * e;
        }
        template<typename T, Size Rows, Size Cols>
        inline Matrix<T, Rows, Cols> operator/(Matrix<T, Rows, Cols> const &u, T e) {
            return Matrix<T, Rows, Cols>(u) /= e;
        }

        template<typename T, Size N>
        std::ostream &operator<<(std::ostream &out, Vector<T, N> vector) {
            out.precision(4);
            out.setf(std::ios::fixed);
            out << "( ";
            for (Size i = 0; i < N; i++) {
                out << vector[i] << ' ';
            }
            out << ")" << std::endl;

            return out;
        }

        template<typename T, Size Rows, Size Cols>
        std::ostream &operator<<(std::ostream &out, Matrix<T, Rows, Cols> matrix) {
            for (Size i = 0; i < Rows; ++i) {
                out << matrix.GetRow(i);
            }
            out << std::endl;
            return out;
        };
        /// Matrix44 --> Matrix33
        template<typename T>
        Matrix<T, 3, 3> LinerMatrix(const Matrix<T, 4, 4> &m) {
            Matrix<T, 3, 3> mat;
            for (Size col = 0; col < 3; col++) {
                for (Size row = 0; row < 3; row++) {
                    mat[col][row] = m[col][row];
                }
            }
            return mat;
        }
        /// Matrix33 --> Matrix44
        template<typename T>
        Matrix<T, 4, 4> AffineMatrix(Matrix<T, 3, 3> const &m) {
            Matrix<T, 4, 4> mat;
            for (Size col = 0; col < 3; col++) {
                for (Size row = 0; row < 3; row++) {
                    mat[col][row] = m[col][row];
                }
            }
            mat[3][3] = static_cast<T>(1);
            return mat;
        };
        /// only remain R,S
        template<typename T>
        void ClearTranslate(Matrix<T, 4, 4> &m) {
            m[3][0] = m[3][1] = m[3][2] = 0;
            m[3][3] = static_cast<T>(1);
            m[0][3] = m[1][3] = m[2][3] = 0;
        };
        /// translate matrix
        template<typename T>
        Matrix<T, 4, 4> TranslateMatrix(T v0, T v1, T v2) {
            Matrix<T, 4, 4> mat(static_cast<T>(1));
            mat[3][0] = v0;
            mat[3][1] = v1;
            mat[3][2] = v2;
            return mat;
        };
        template<typename T>
        Matrix<T, 4, 4> TranslateMatrix(Vector<T, 3> const &v) {
            return TranslateMatrix(v[0], v[1], v[2]);
        };
        /// Scale matrix
        template<typename T>
        Matrix<T, 4, 4> ScaleMatrix(T s0, T s1, T s2) {
            Matrix<T, 4, 4> mat;
            mat[0][0] = s0;
            mat[1][1] = s1;
            mat[2][2] = s2;
            mat[3][3] = static_cast<T>(1);
            return mat;
        };
        template<typename T>
        Matrix<T, 4, 4> ScaleMatrix(Vector<T, 3> const &s) {
            return ScaleMatrix(s[0], s[1], s[2]);
        };
        /// Rotate matrix
        template<typename T>
        Matrix<T, 4, 4> RotateXMatrix(T angle) {
            Matrix<T, 4, 4> mat;
            T c = std::cos(angle);
            T s = std::sin(angle);
            mat[3][3] = mat[0][0] = static_cast<T>(1);
            mat[1][1] = mat[2][2] = c;
            mat[1][2] = s;
            mat[2][1] = -s;
            return mat;
        };
        template<typename T>
        Matrix<T, 4, 4> RotateYMatrix(T angle) {
            Matrix<T, 4, 4> mat;
            T c = std::cos(angle);
            T s = std::sin(angle);
            mat[3][3] = mat[1][1] = static_cast<T>(1);
            mat[0][0] = mat[2][2] = c;
            mat[2][0] = s;
            mat[0][2] = -s;
            return mat;
        };
        template<typename T>
        Matrix<T, 4, 4> RotateZMatrix(T angle) {
            Matrix<T, 4, 4> mat;
            T c = std::cos(angle);
            T s = std::sin(angle);
            mat[3][3] = mat[2][2] = static_cast<T>(1);
            mat[1][1] = mat[0][0] = c;
            mat[0][1] = s;
            mat[1][0] = -s;
            return mat;
        };
        template<typename T>
        Matrix<T, 4, 4> RotateAxisMatrix(Vector<T, 3> const &axis, T angle) {
            Matrix<T, 4, 4> mat;
            T c = std::cos(angle);
            T s = std::sin(angle);
            T _1_c = static_cast<T>(1) - c;
            T xx = axis[0] * axis[0] * _1_c;
            T yy = axis[1] * axis[1] * _1_c;
            T zz = axis[2] * axis[2] * _1_c;
            T xy = axis[0] * axis[1] * _1_c;
            T yz = axis[1] * axis[2] * _1_c;
            T zx = axis[2] * axis[0] * _1_c;
            T xs = axis[0] * s;
            T ys = axis[1] * s;
            T zs = axis[2] * s;
            mat[0][0] = c + xx;
            mat[0][1] = zs + xy;
            mat[0][2] = -ys + zx;
            mat[1][0] = -zs + xy;
            mat[1][1] = c + yy;
            mat[1][2] = xs + yz;
            mat[2][0] = ys + zx;
            mat[2][1] = -xs + yz;
            mat[2][2] = c + zz;
            mat[3][3] = static_cast<T>(1);
            return mat;
        };

        /// matrix transform
        template<typename T>
        void Translate(Matrix<T, 4, 4> &m, Vector<T, 3> const &v) {
            m[3] += m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
        }

        /// matrix rotate
        template<typename T>
        void Rotate(Matrix<T, 4, 4> &m, T angle, Vector<T, 3> const &v) {
            m *= RotateAxisMatrix(Normalize(v), angle);
        }

        /// matrix scale
        template<typename T>
        void Scale(Matrix<T, 4, 4> &m, Vector<T, 3> const &v) {
            m[0] *= v[0];
            m[1] *= v[1];
            m[2] *= v[2];
        }
        /*
        /// matrix ortho 2 - dim
        template<typename T>
        Matrix<T> Orthogonal(T left, T right, T bottom, T top) {
        Matrix<T> tmp(static_cast<T>(1));

        tmp[0][0] = static_cast<T>(2) / (right - left);
        tmp[1][1] = static_cast<T>(2) / (top - bottom);
        tmp[2][2] = static_cast<T>(1);
        tmp[3][0] = -(right + left) / (right - left);
        tmp[3][1] = -(top + bottom) / (top - bottom);

        return tmp;
        }

        /// matrix frustum
        template<typename T>
        Matrix<T> Frustum(T left, T right, T bottom, T top, T nearPlane, T farPlane) {
        Matrix<T> tmp(0);

        tmp[0][0] = (static_cast<T>(2) * nearPlane) / (right - left);
        tmp[1][1] = (static_cast<T>(2) * nearPlane) / (top - bottom);
        tmp[2][0] = (right + left) / (right - left);
        tmp[2][1] = (top + bottom) / (top - bottom);
        tmp[2][3] = static_cast<T>(1);
        #ifdef _DIRECTX_RENDER
        tmp[2][2] = farPlane / (farPlane - nearPlane);
        tmp[3][2] = -(farPlane * nearPlane) / (farPlane - nearPlane);
        #else
        tmp[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane);
        tmp[3][2] = -(static_cast<T>(2) * farPlane * nearPlane) / (farPlane - nearPlane);
        #endif
        return tmp;
        }
        */
        /// matrix perspective
        template<typename T>
        Matrix<T, 4, 4> PerspectiveRH(T fovy, T aspect, T nearPlane, T farPlane) {
            assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

            T const tanHalfFovy = tan(fovy / static_cast<T>(2));

            Matrix<T, 4, 4> tmp(0);
            tmp[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
            tmp[1][1] = static_cast<T>(1) / (tanHalfFovy);
            tmp[2][3] = -static_cast<T>(1);

            tmp[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            tmp[3][2] = -(static_cast<T>(2) * farPlane * nearPlane) / (farPlane - nearPlane);
            return tmp;
        }
        template<typename T>
        Matrix<T, 4, 4> PerspectiveLH(T fovy, T aspect, T nearPlane, T farPlane) {
            assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

            T const tanHalfFovy = tan(fovy / static_cast<T>(2));

            Matrix<T, 4, 4> tmp(0);
            tmp[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
            tmp[1][1] = static_cast<T>(1) / (tanHalfFovy);
            tmp[2][3] = static_cast<T>(1);

            tmp[2][2] = (farPlane + nearPlane) / (farPlane - nearPlane);
            tmp[3][2] = -(static_cast<T>(2) * farPlane * nearPlane) / (farPlane - nearPlane);
            return tmp;
        }
        template<typename T>
        Matrix<T, 4, 4> PerspectiveFovRH(T fovy, T width, T height, T nearPlane, T farPlane) {
            assert(fovy > static_cast<T>(0) && width > static_cast<T>(0) && height > static_cast<T>(0));

            return {};
        }
        template<typename T>
        Matrix<T, 4, 4> PerspectiveFovLH(T fovy, T width, T height, T nearPlane, T farPlane) {
            assert(fovy > static_cast<T>(0) && width > static_cast<T>(0) && height > static_cast<T>(0));

            return {};
        }

        /// matrix Orthogonal
        template<typename T>
        Matrix<T, 4, 4> OrthogonalRH(T left, T right, T bottom, T top, T nearPlane, T farPlane) {
            Matrix<T, 4, 4> tmp;
            tmp[0][0] = static_cast<T>(2) / (right - left);
            tmp[1][1] = static_cast<T>(2) / (top - bottom);
            tmp[3][0] = -(right + left) / (right - left);
            tmp[3][1] = -(top + bottom) / (top - bottom);
            tmp[2][2] = -static_cast<T>(2) / (farPlane - nearPlane);
            tmp[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            tmp[3][3] = static_cast<T>(1);
            return tmp;
        }
        template<typename T>
        Matrix<T, 4, 4> OrthogonalLH(T left, T right, T bottom, T top, T nearPlane, T farPlane) {
            Matrix<T, 4, 4> tmp;
            tmp[0][0] = static_cast<T>(2) / (right - left);
            tmp[1][1] = static_cast<T>(2) / (top - bottom);
            tmp[3][0] = -(right + left) / (right - left);
            tmp[3][1] = -(top + bottom) / (top - bottom);
            tmp[2][2] = static_cast<T>(2) / (farPlane - nearPlane);
            tmp[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            tmp[3][3] = static_cast<T>(1);
            return tmp;
        }

        /// matrix lookAt
        template<typename T>
        Matrix<T, 4, 4> LookAtViewRH(Vector<T, 3> const &eye, Vector<T, 3> const &center, Vector<T, 3> const &up) {
            Vector<T, 3> const f(Normalize(center - eye));
            Vector<T, 3> const s(Normalize(Cross(f, up)));
            Vector<T, 3> const u(Cross(s, f));

            Matrix<T, 4, 4> view(1.0f);
            view[0][0] = s[0];
            view[1][0] = s[1];
            view[2][0] = s[2];
            view[0][1] = u[0];
            view[1][1] = u[1];
            view[2][1] = u[2];
            view[0][2] = -f[0];
            view[1][2] = -f[1];
            view[2][2] = -f[2];
            view[3][0] = -Dot(eye, s);
            view[3][1] = -Dot(eye, u);
            view[3][2] = Dot(eye, f);
            return view;
        }
        template<typename T>
        Matrix<T, 4, 4> LookAtViewLH(Vector<T, 3> const &eye, Vector<T, 3> const &center, Vector<T, 3> const &up) {
            Vector<T, 3> const f(Normalize(center - eye));
            Vector<T, 3> const s(Normalize(Cross(up, f)));
            Vector<T, 3> const u(Cross(f, s));

            Matrix<T, 4, 4> view;
            view[0][0] = s[0];
            view[1][0] = s[1];
            view[2][0] = s[2];
            view[0][1] = u[0];
            view[1][1] = u[1];
            view[2][1] = u[2];
            view[0][2] = f[0];
            view[1][2] = f[1];
            view[2][2] = f[2];
            view[3][0] = -Dot(eye, s);
            view[3][1] = -Dot(eye, u);
            view[3][2] = -Dot(eye, f);
            return view;
        }

        /// Quaternion
        template<typename T>
        struct Quat : public Vector<T, 4> {
            using base_type = Vector<T, 4>;
            using vector_type = Vector<T, 3>;
            using scalar_type = T;

            using base_type::storage;

            Quat() : base_type() {}
            Quat(T e) : base_type(e) {}
            Quat(std::initializer_list<T> list) : base_type(list) {}
            Quat(const vector_type &v, T s = static_cast<T>(0)) : base_type{v[0], v[1], v[2], s} {}
            Quat(const base_type &v) : base_type(v) {}
            Quat(Quat const &u) = default;
            Quat(Quat &&u) noexcept = default;
            Quat &operator=(Quat const &u) = default;
            Quat &operator=(Quat &&u) noexcept = default;

            vector_type GetV() const { return {storage[0], storage[1], storage[2]}; }
            T GetS() const { return storage[3]; }

            void SetV(const vector_type &v) {
                storage[0] = v[0];
                storage[1] = v[1];
                storage[2] = v[2];
            }
            void SetS(T s) { storage[3] = s; }

            /// pq = [p_s*q_v + q_s*p_v + cross(p_v,q_v)    p_s*q_s - dot(p_v, q_v)]
            Quat &operator*=(const Quat &q) {
                Quat p(*this);
                storage[0] = p[3] * q[0] + q[3] * p[0] + p[1] * q[2] - p[2] * q[1];
                storage[1] = p[3] * q[1] + q[3] * p[1] + p[2] * q[0] - p[0] * q[2];
                storage[2] = p[3] * q[2] + q[3] * p[2] + p[0] * q[1] - p[1] * q[0];
                storage[3] = p[3] * q[3] - p[0] * q[0] - p[1] * q[1] - p[2] * q[2];
                return *this;
            }

        };

        template<typename T>
        Quat<T> operator*(const Quat<T> &p, const Quat<T> &q) {
            return Quat(p) *= q;
        }
        template<typename T>
        Quat<T> RotateQuaternion(const Vector<T, 3> &v, T angle) {
            return Quat(Normalize(v) * std::sin(angle * static_cast<T>(0.5)), std::cos(angle * static_cast<T>(0.5)));
        }
        template<typename T>
        Quat<T> Conjugate(const Quat<T> &q) {
            return Quat<T>(-q.GetV(), q.GetS());
        }
        template<typename T>
        Quat<T> Inverse(const Quat<T> &q) {
            return Conjugate(q) / q.NormSquare();
        }
        template<typename T>
        Quat<T> InverseRotateQuaternion(const Quat<T> &q) {
            return Conjugate(q);
        }
        /// qvq-1  qvq* ; q must be rotate quaternion
        template<typename T>
        Vector<T, 3> Rotate(const Vector<T, 3> &v, const Quat<T> &q) {
            Quat<T> v0 = q * Quat<T>(v, 0) * Conjugate(q);
            return v0.GetV();
        };
        /// rotate q by angle with v
        template<typename T>
        void Rotate(Quat<T> &q, const Vector<T, 3> &v, T angle) {
            q = RotateQuaternion(v, angle) * q;
        }
        ///
        template<typename T>
        Matrix<T, 3, 3> QuaternionRotateMatrix(const Quat<T> &q) {
            Matrix<T, 3, 3> m;
            T xx = q[0] * q[0];
            T yy = q[1] * q[1];
            T zz = q[2] * q[2];
            T xy = q[0] * q[1];
            T yz = q[1] * q[2];
            T zx = q[2] * q[0];
            T sx = q[3] * q[0];
            T sy = q[3] * q[1];
            T sz = q[3] * q[2];

            m[0][0] = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
            m[0][1] = static_cast<T>(2) * (xy + sz);
            m[0][2] = static_cast<T>(2) * (zx - sy);
            m[1][0] = static_cast<T>(2) * (xy - sz);
            m[1][1] = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
            m[1][2] = static_cast<T>(2) * (yz + sx);
            m[2][0] = static_cast<T>(2) * (zx + sy);
            m[2][1] = static_cast<T>(2) * (yz - sx);
            m[2][2] = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);

            return m;
        };
        template<typename T>
        Quat<T> MatrixRotateQuaternion(const Matrix<T, 3, 3> &m) {
            return Quat<T>();
        }
        /// Get Quaternion angle
        template<typename T>
        T QuaternionRotateAngle(const Quat<T> &q) {
            return std::acos(q[3]) * static_cast<T>(2);
        }
        /// Get Quaternion axis
        template<typename T>
        Vector<T, 3> QuaternionRotateAxis(const Quat<T> &q) {
            T sinSquare = static_cast<T>(1) - q[3] * q[3];
            if (sinSquare < static_cast<T>(0)) {
                return {0, 0, static_cast<T>(1)};
            }
            T oneOverSin = 1 / std::sqrt(sinSquare);
            return Vector<T, 3>{q[0], q[1], q[2]} * oneOverSin;
        };
        /// lerp
        template<typename T, Size N>
        Vector<T, N> Lerp(const Vector<T, N> &u, const Vector<T, N> &v, T t) {
            assert(t >= static_cast<T>(0) && t <= static_cast<T>(1));
            return u * (static_cast<T>(1) - t) + v * t;
        };
        /// quat lerp : rotate quaternion must be normalize
        template<typename T>
        Quat<T> Lerp(const Quat<T> &u, const Quat<T> &v, T t) {
            assert(t >= static_cast<T>(0) && t <= static_cast<T>(1));
            return u * (static_cast<T>(1) - t) + v * t;
        };
        /// slerp rotate quaternion must be normalize
        template<typename T>
        Quat<T> Slerp(const Quat<T> &u, const Quat<T> &v, T t) {
            Quat<T> q(v);
            T cosTheta = Dot(u, v);
            if (cosTheta < static_cast<T>(0)) {
                q = -v;
                cosTheta = -cosTheta;
            }

            if (std::abs(static_cast<T>(1) - cosTheta) < std::numeric_limits<T>::epsilon()) {
                return Lerp(u, q, t);
            }
            else {
                T theta = std::acos(cosTheta);
                T oneOverSinTheta = static_cast<T>(1) - std::sin(theta);
                return (u * std::sin((static_cast<T>(1) - t) * theta) + q * std::sin(t * theta)) * oneOverSinTheta;
            }
        }
        /// euler angle: x:pitch   y:yaw   z:roll
        template<typename T>
        T Roll(const Quat<T> &q) {
            return std::atan2(static_cast<T>(2) * (q[0] * q[1] + q[3] * q[2]),
                              q[3] * q[3] + q[0] * q[0] - q[1] * q[1] - q[2] * q[2]);
        }
        template<typename T>
        T Pitch(const Quat<T> &q) {
            return std::atan2(static_cast<T>(2) * (q[1] * q[2] + q[3] * q[1]),
                              q[3] * q[3] - q[0] * q[0] - q[1] * q[1] + q[2] * q[2]);
        }
        template<typename T>
        T Yaw(const Quat<T> &q) {
            return std::asin(
                    std::clamp(static_cast<T>(-2) * (q[0] * q[2] - q[3] * q[1]), static_cast<T>(-1),
                               static_cast<T>(1)));
        }
        template<typename T>
        Vector<T, 3> EulerAngle(const Quat<T> &q) {
            return {Pitch(q), Yaw(q), Roll(q)};
        };

        /// typedef
        using Vector3 = Vector<Float, 3>;
        using Vector4 = Vector<Float, 4>;
        using Matrix33 = Matrix<Float, 3, 3>;
        using Matrix44 = Matrix<Float, 4, 4>;
        using Quaternion = Quat<Float>;
    }
}
