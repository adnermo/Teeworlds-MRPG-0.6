/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef BASE_VMATH_H
#define BASE_VMATH_H

#include "math.h"

template<typename T>
class vector2_base
{
public:
	union { T x,u; };
	union { T y,v; };

	vector2_base(): x(), y() { }
	vector2_base(T nx, T ny)
	{
		x = nx;
		y = ny;
	}

	vector2_base operator -() const { return vector2_base(-x, -y); }
	vector2_base operator -(const vector2_base &v) const { return vector2_base(x-v.x, y-v.y); }
	vector2_base operator +(const vector2_base &v) const { return vector2_base(x+v.x, y+v.y); }
	vector2_base operator *(const T v) const { return vector2_base(x*v, y*v); }
	vector2_base operator *(const vector2_base &v) const { return vector2_base(x*v.x, y*v.y); }
	vector2_base operator /(const T v) const { return vector2_base(x/v, y/v); }
	vector2_base operator /(const vector2_base &v) const { return vector2_base(x/v.x, y/v.y); }

	const vector2_base &operator +=(const vector2_base &v) { x += v.x; y += v.y; return *this; }
	const vector2_base &operator -=(const vector2_base &v) { x -= v.x; y -= v.y; return *this; }
	const vector2_base &operator *=(const T v) { x *= v; y *= v; return *this;	}
	const vector2_base &operator *=(const vector2_base &v) { x *= v.x; y *= v.y; return *this; }
	const vector2_base &operator /=(const T v) { x /= v; y /= v; return *this;	}
	const vector2_base &operator /=(const vector2_base &v) { x /= v.x; y /= v.y; return *this; }

	bool operator ==(const vector2_base &v) const { return x == v.x && y == v.y; } //TODO: do this with an eps instead
	bool operator !=(const vector2_base &v) const { return x != v.x || y != v.y; }

	operator const T* () { return &x; }
};

template<typename T>
vector2_base<T> rotate(const vector2_base<T> &a, float angle)
{
	angle = angle * pi / 180.0f;
	float s = sinf(angle);
	float c = cosf(angle);
	return vector2_base<T>((T)(c*a.x - s*a.y), (T)(s*a.x + c*a.y));
}

template<typename T>
T distance(const vector2_base<T> &a, const vector2_base<T> &b)
{
	return length(a-b);
}

template<typename T>
T dot(const vector2_base<T> &a, const vector2_base<T> &b)
{
	return a.x*b.x + a.y*b.y;
}

template<typename T>
vector2_base<T> closest_point_on_line(vector2_base<T> line_point0, vector2_base<T> line_point1, vector2_base<T> target_point)
{
	vector2_base<T> c = target_point - line_point0;
	vector2_base<T> v = (line_point1 - line_point0);
	v = normalize(v);
	T d = length(line_point0-line_point1);
	T t = dot(v, c)/d;
	return mix(line_point0, line_point1, clamp(t, (T)0, (T)1));
	/*
	if (t < 0) t = 0;
	if (t > 1.0f) return 1.0f;
	return t;*/
}

template<typename T>
inline bool closest_point_on_line(vector2_base<T> line_pointA, vector2_base<T> line_pointB, vector2_base<T> target_point, vector2_base<T>& out_pos)
{
	vector2_base<T> AB = line_pointB - line_pointA;
	T SquaredMagnitudeAB = dot(AB, AB);
	if (SquaredMagnitudeAB > 0)
	{
		vector2_base<T> AP = target_point - line_pointA;
		T APdotAB = dot(AP, AB);
		T t = APdotAB / SquaredMagnitudeAB;
		out_pos = line_pointA + AB * clamp(t, (T)0, (T)1);
		return true;
	}
	else
		return false;
}

//
inline float total_size_vec2(const vector2_base<float> &a)
{
	return a.x + a.y;
}

inline float length(const vector2_base<float> &a)
{
	return sqrtf(a.x*a.x + a.y*a.y);
}

inline float angle(const vector2_base<float> &a)
{
	return atan2f(a.y, a.x);
}

inline vector2_base<float> normalize(const vector2_base<float> &v)
{
	const float l = (float)(1.0f/sqrtf(v.x*v.x + v.y*v.y));
	return {v.x*l, v.y*l};
}

inline vector2_base<float> direction(float angle)
{
	return {cosf(angle), sinf(angle)};
}

typedef vector2_base<float> vec2;
typedef vector2_base<bool> bvec2;
typedef vector2_base<int> ivec2;


// ------------------------------------
template<typename T>
class vector3_base
{
public:
	union { T x,r,h; };
	union { T y,g,s; };
	union { T z,b,v,l; };

	vector3_base(): x(), y(), z() { }
	vector3_base(T nx, T ny, T nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}

	vector3_base operator -(const vector3_base &v) const { return vector3_base(x-v.x, y-v.y, z-v.z); }
	vector3_base operator -() const { return vector3_base(-x, -y, -z); }
	vector3_base operator +(const vector3_base &v) const { return vector3_base(x+v.x, y+v.y, z+v.z); }
	vector3_base operator *(const T v) const { return vector3_base(x*v, y*v, z*v); }
	vector3_base operator *(const vector3_base &v) const { return vector3_base(x*v.x, y*v.y, z*v.z); }
	vector3_base operator /(const T v) const { return vector3_base(x/v, y/v, z/v); }
	vector3_base operator /(const vector3_base &v) const { return vector3_base(x/v.x, y/v.y, z/v.z); }

	const vector3_base &operator +=(const vector3_base &v) { x += v.x; y += v.y; z += v.z; return *this; }
	const vector3_base &operator -=(const vector3_base &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	const vector3_base &operator *=(const T v) { x *= v; y *= v; z *= v; return *this;	}
	const vector3_base &operator *=(const vector3_base &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	const vector3_base &operator /=(const T v) { x /= v; y /= v; z /= v; return *this;	}
	const vector3_base &operator /=(const vector3_base &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

	bool operator ==(const vector3_base &v) const { return x == v.x && y == v.y && z == v.z; } //TODO: do this with an eps instead
	bool operator !=(const vector3_base &v) const { return x != v.x || y != v.y || z != v.z; }

	operator const T* () { return &x; }
};

template<typename T>
T distance(const vector3_base<T> &a, const vector3_base<T> &b)
{
	return length(a-b);
}

template<typename T>
T dot(const vector3_base<T> &a, const vector3_base<T> &b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template<typename T>
vector3_base<T> cross(const vector3_base<T> &a, const vector3_base<T> &b)
{
	return vector3_base<T>(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x);
}

inline float length(const vector3_base<float> &a)
{
	return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

inline vector3_base<float> normalize(const vector3_base<float> &v)
{
	const float l = (float)(1.0f/sqrtf(v.x*v.x + v.y*v.y + v.z*v.z));
	return {v.x*l, v.y*l, v.z*l};
}

typedef vector3_base<float> vec3;
typedef vector3_base<bool> bvec3;
typedef vector3_base<int> ivec3;

// ------------------------------------

template<typename T>
class vector4_base
{
public:
	union { T x,r; };
	union { T y,g; };
	union { T w,b; };
	union { T h,a; };

	vector4_base(): x(), y(), w(), h() {}
	vector4_base(T nx, T ny, T nw, T nh)
	{
		x = nx;
		y = ny;
		w = nw;
		h = nh;
	}

	vector4_base operator +(const vector4_base& v) const { return vector4_base(x + v.x, y + v.y, w + v.w, h + v.h); }
	vector4_base operator -(const vector4_base& v) const { return vector4_base(x - v.x, y - v.y, w - v.w, h - v.h); }
	vector4_base operator -() const { return vector4_base(-x, -y, -w, -h); }
	vector4_base operator *(const vector4_base& v) const { return vector4_base(x * v.x, y * v.y, w * v.w, h * v.h); }
	vector4_base operator *(const T v) const { return vector4_base(x * v, y * v, w * v, h * v); }
	vector4_base operator /(const vector4_base& v) const { return vector4_base(x/v.x, y/v.y, w/v.w, h/v.h); }
	vector4_base operator /(const T v) const { return vector4_base(x/v, y/v, w/v, h/v); }

	const vector4_base& operator +=(const vector4_base& v) { x += v.x; y += v.y; w += v.w; h += v.h; return *this; }
	const vector4_base& operator -=(const vector4_base& v) { x -= v.x; y -= v.y; w -= v.w; h -= v.h; return *this; }
	const vector4_base& operator *=(const T v) { x *= v; y *= v; w *= v; h *= v; return *this; }
	const vector4_base& operator *=(const vector4_base& v) { x *= v.x; y *= v.y; w *= v.w; h *= v.h; return *this; }
	const vector4_base& operator /=(const T v) { x /= v; y /= v; w /= v; h /= v; return *this; }
	const vector4_base& operator /=(const vector4_base& v) { x /= v.x; y /= v.y; w /= v.w; h /= v.h; return *this; }

	bool operator ==(const vector4_base& v) const { return x == v.x && y == v.y && w == v.w && h == v.h; } //TODO: do this with an eps instead
	bool operator !=(const vector4_base &v) const { return x != v.x || y != v.y || w != v.w || h != v.h; }

	operator const T* () { return &x; }
};

typedef vector4_base<float> vec4;
typedef vector4_base<bool> bvec4;
typedef vector4_base<int> ivec4;

#endif
