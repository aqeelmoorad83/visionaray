// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

namespace visionaray
{


//--------------------------------------------------------------------------------------------------
// spectrum members
//

template <typename T>
VSNRAY_FUNC
inline spectrum<T>::spectrum(T c)
    : samples_(c)
{
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T>::spectrum(vector<spectrum<T>::num_samples, T> const& samples)
    : samples_(samples)
{
}

template <typename T>
template <typename U>
VSNRAY_FUNC
inline spectrum<T>::spectrum(spectrum<U> const& rhs)
    : samples_(rhs.samples())
{
}

template <typename T>
template <typename U>
VSNRAY_FUNC
inline spectrum<T>& spectrum<T>::operator=(spectrum<U> const& rhs)
{
    samples_ = rhs.samples_;
    return *this;
}

template <typename T>
VSNRAY_FUNC
inline vector<spectrum<T>::num_samples, T>& spectrum<T>::samples()
{
    return samples_;
}

template <typename T>
VSNRAY_FUNC
inline vector<spectrum<T>::num_samples, T> const& spectrum<T>::samples() const
{
    return samples_;
}


//--------------------------------------------------------------------------------------------------
// Basic arithmetic
//

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator-(spectrum<T> const& s)
{
    return spectrum<T>( -s.samples() );
}

// spectrum op spectrum

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator+(spectrum<T> const& s, spectrum<T> const& t)
{
    return spectrum<T>( s.samples() + t.samples() );
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator-(spectrum<T> const& s, spectrum<T> const& t)
{
    return spectrum<T>( s.samples() - t.samples() );
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator*(spectrum<T> const& s, spectrum<T> const& t)
{
    return spectrum<T>( s.samples() * t.samples() );
}

// spectrum op scalar

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator+(spectrum<T> const& s, T t)
{
    return spectrum<T>( s.samples() + t );
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator-(spectrum<T> const& s, T t)
{
    return spectrum<T>( s.samples() - t );
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator*(spectrum<T> const& s, T t)
{
    return spectrum<T>( s.samples() * t );
}

// scalar op spectrum

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator+(T s, spectrum<T> const& t)
{
    return spectrum<T>( s + t.samples() );
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator-(T s, spectrum<T> const& t)
{
    return spectrum<T>( s - t.samples() );
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> operator*(T s, spectrum<T> const& t)
{
    return spectrum<T>( s * t.samples() );
}

// append operations

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& operator+=(spectrum<T>& s, spectrum<T> const& t)
{
    s = spectrum<T>(s + t);
    return s;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& operator-=(spectrum<T>& s, spectrum<T> const& t)
{
    s = spectrum<T>(s - t);
    return s;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& operator*=(spectrum<T>& s, spectrum<T> const& t)
{
    s = spectrum<T>(s * t);
    return s;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& operator+=(spectrum<T>& s, T t)
{
    s = spectrum<T>(s + t);
    return s;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& operator-=(spectrum<T>& s, T t)
{
    s = spectrum<T>(s - t);
    return s;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& operator*=(spectrum<T>& s, T t)
{
    s = spectrum<T>(s * t);
    return s;
}


//-------------------------------------------------------------------------------------------------
// Misc.
//

template <typename M, typename T>
VSNRAY_FUNC
inline spectrum<T> select(M const& m, spectrum<T> const& s, spectrum<T> const& t)
{
    return spectrum<T>( select(m, s.samples(), t.samples()) );
}

template <typename T>
VSNRAY_FUNC
inline T mean_value(spectrum<T> const& s)
{
    return hadd( s.samples() ) / T(spectrum<T>::num_samples);
}


//-------------------------------------------------------------------------------------------------
// Conversions
//

// RGB -> SPD

template <typename T>
VSNRAY_FUNC
inline spectrum<T> from_rgb(vector<3, T> const& rgb)
{
#if 1
    return spectrum<T>(rgb);
#endif
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> from_rgb(T r, T g, T b)
{
    return from_rgb( vector<3, T>(r, g, b) );
}

// RGBA -> SPD

template <typename T>
VSNRAY_FUNC
inline spectrum<T> from_rgba(vector<4, T> const& rgba)
{
#if 1
    auto inv = select( rgba.w != T(0.0), T(1.0) / rgba.w, T(1.0) );
    return from_rgb( rgba.x * inv, rgba.y * inv, rgba.z * inv );
#endif
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> from_rgba(T r, T g, T b, T a)
{
    return from_rgba(r, g, b, a);
}

// SPD -> RGBA

template <typename T>
VSNRAY_FUNC
inline vector<4, T> to_rgba(spectrum<T> const& s)
{
#if 1
    return vector<4, T>( s.samples(), T(1.0) );
#endif
}


namespace simd
{

//-------------------------------------------------------------------------------------------------
// SIMD conversions
//

inline spectrum<float4> pack(
        spectrum<float> const& s1,
        spectrum<float> const& s2,
        spectrum<float> const& s3,
        spectrum<float> const& s4
        )
{
    return spectrum<float4>(pack(
            s1.samples(),
            s2.samples(),
            s3.samples(),
            s4.samples()
            )
        );
}

} // simd

} // visionaray
