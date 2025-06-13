#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <math.h>

template <class t> struct Vector3 
{    
public:
    t x,y,z;
    Vector3():x(0),y(0),z(0){}
    Vector3(t _x,t _y,t _z) : x(_x),y(_y),z(_z) {}
    Vector3(t _x) : x(_x),y(_x),z(_x) {}
    ~Vector3() {}
    t& operator[](int idx){
        if(idx==0) return x;
        else if(idx==1) return y;
        else return z;
    }
    const t& operator[](int idx) const{
        if(idx==0) return x;
        else if(idx==1) return y;
        else return z;
    }
    inline Vector3<t> operator -(Vector3<t> &other){return Vector3<t>(x-other.x,y-other.y,z-other.z);}
    inline Vector3<t> operator +(Vector3<t> &other){return Vector3<t>(x+other.x,y+other.y,z+other.z);}
    inline Vector3<t> operator *(t other){return Vector3<t>(x*other,y*other,z*other);}
    inline Vector3<t> operator /(t other){return Vector3<t>(x/other,y/other,z/other);}
    inline float norm2() {
        return x*x+y*y+z*z;
    }
    inline float norm() { return std::sqrt(norm2()); }
    inline float dot(const Vector3<t>& other) const {
        return (x * other.x + y * other.y + z * other.z);
    }
    inline Vector3<t> cross(const Vector3<t>& other) const {
        return Vector3<t>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    
    inline Vector3<t> normalize() {
        float _norm = norm();
        return Vector3<t>(x/_norm,y/_norm,z/_norm);
    }

    inline void normalized() {
        float _norm = norm();
        x = x/_norm;
        y = y/_norm;
        z = z/_norm;
    }

    inline Vector3<t> cwise(Vector3<t> other)
    {
        return Vector3<t>(x * other.x , y * other.y , z * other.z);
    }

    inline void print(){ std::cout<<x<<" "<<y<<" "<<z<<std::endl; }

};
template <class t> struct Vector4
{    
public:
    t x,y,z,w;
    Vector4():x(0),y(0),z(0),w(0){}
    Vector4(t _x,t _y,t _z,t _w) : x(_x),y(_y),z(_z),w(_w){}
    Vector4(t _x) : x(_x),y(_x),z(_x),w(_x) {}
    Vector4(Vector3<t> vec3):x(vec3.x),y(vec3.y),z(vec3.z),w(1){}
    ~Vector4() {}
    t& operator[](int idx){
        if(idx==0) return x;
        else if(idx==1) return y;
        else if(idx==2) return z;
        else return w;
    }
    const t& operator[](int idx) const{
        if(idx==0) return x;
        else if(idx==1) return y;
        else if(idx==2) return z;
        else return w;
    }
    inline Vector4<t> operator -(const Vector4<t> &other){return Vector4<t>(x-other.x,y-other.y,z-other.z,w-other.w);}
    inline Vector4<t> operator +(const Vector4<t> &other){return Vector4<t>(x+other.x,y+other.y,z+other.z,w+other.w);}
    inline Vector4<t> operator *(const t other){return Vector4<t>(x*other,y*other,z*other,w*other);}
    inline Vector4<t> operator /(const t other){return Vector4<t>(x/other,y/other,z/other,w/other);}
    inline float norm2() {
        return x*x+y*y+z*z+w*w;
    }
    inline float norm() { return std::sqrt(norm2()); }
    inline float dot(const Vector4<t>& other) const {
        return (x * other.x + y * other.y + z * other.z+ w*other.w);
    }
    
    inline void normalized() {
        float _norm = norm();
        x = x /_norm;
        y = y /_norm;
        z = z /_norm;
        w = w/_norm;
    }
    inline Vector4<t> normalize() {
        float _norm = norm();
        return Vector4<t>(x/_norm,y/_norm,z/_norm,w/_norm);
    }
    inline void print(){ std::cout<<x<<" "<<y<<" "<<z<<" "<<w<<std::endl; }
};



template <class t> struct Vector2
{
public:
    t x,y; 
    Vector2(){}
    Vector2(t _x,t _y) : x(_x),y(_y){}
    Vector2(t _x) : x(_x),y(_x) {}
    ~Vector2() {}
    t& operator[](int idx){
        if(idx==0) return x;
        else if(idx==1) return y;
        else return x;
    }
    const t& operator[](int idx) const{
        if(idx==0) return x;
        else if(idx==1) return y;
        else return x;
    }
    inline Vector2<t> operator-(Vector2<t> &other){return Vector2<t>(x-other.x,y-other.y);}
    inline Vector2<t> operator+(Vector2<t> &other){return Vector2<t>(x+other.x,y+other.y);}
    inline Vector2<t> operator*(t other){return Vector2<t>(x*other,y*other);}
    inline Vector2<t> operator/(t other){return Vector2<t>(x/other,y/other);}

    inline t dot(const Vector2<t>& other) const {
        return x * other.x + y * other.y;
    }

    inline t cross(const Vector2<t>& other) const {
        return x * other.y - y * other.x;
    }
};


template <class T, class U>
Vector3<decltype(T{} + U{})> operator+(const Vector3<T>& a, const Vector3<U>& b) {
    using RT = decltype(T{} + U{});
    return Vector3<RT>(
        static_cast<RT>(a.x) + static_cast<RT>(b.x),
        static_cast<RT>(a.y) + static_cast<RT>(b.y),
        static_cast<RT>(a.z) + static_cast<RT>(b.z)
    );
}

template <class T, class U>
Vector3<decltype(T{} - U{})> operator-(const Vector3<T>& a, const Vector3<U>& b) {
    using RT = decltype(T{} - U{});
    return Vector3<RT>(
        static_cast<RT>(a.x) - static_cast<RT>(b.x),
        static_cast<RT>(a.y) - static_cast<RT>(b.y),
        static_cast<RT>(a.z) - static_cast<RT>(b.z)
    );
}

template <class T, class U>
Vector2<decltype(T{} + U{})> operator+(const Vector2<T>& a, const Vector2<U>& b) {
    using RT = decltype(T{} + U{});
    return Vector2<RT>(
        static_cast<RT>(a.x) + static_cast<RT>(b.x),
        static_cast<RT>(a.y) + static_cast<RT>(b.y)
    );
}

template <class T, class U>
Vector2<decltype(T{} - U{})> operator-(const Vector2<T>& a, const Vector2<U>& b) {
    using RT = decltype(T{} - U{});
    return Vector2<RT>(
        static_cast<RT>(a.x) - static_cast<RT>(b.x),
        static_cast<RT>(a.y) - static_cast<RT>(b.y)
    );
}


typedef Vector4<float> Vector4f;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;


inline Vector3f operator*(float s, Vector3f& v) {
    return v * s;  // 复用上面的成员 operator*
}

inline Vector4f operator*(float s, Vector4f& v) {
    return v * s;
}

#endif