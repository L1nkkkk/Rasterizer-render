#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector.h"
#include <vector>

class Matrix4f
{
private:
public:
    Vector4f a[4];//raw
    Vector4f b[4];//col
    bool aIsRaw;
    Matrix4f(std::vector<Vector4f> vec)
    {
        aIsRaw = true;
        if(vec.size()!=4) return;
        for(int i=0;i<4;++i)
        {
            a[i]=vec[i];
            for(int j=0;j<4;++j)
                b[j][i]=vec[i][j];
        }
            
    };
    Matrix4f()
    {
        a[0]=b[0]=Vector4f(1,0,0,0);
        a[1]=b[1]=Vector4f(0,1,0,0);
        a[2]=b[2]=Vector4f(0,0,1,0);
        a[3]=b[3]=Vector4f(0,0,0,1);
    }
    ~Matrix4f(){};
    Matrix4f Identity(){return Matrix4f();}
    void transposition() {aIsRaw=!aIsRaw;}
    inline Vector4f operator*(const Vector4f& other) const
    {
        if(aIsRaw) return Vector4f(a[0].dot(other),a[1].dot(other),a[2].dot(other),a[3].dot(other));
        else return Vector4f(b[0].dot(other),b[1].dot(other),b[2].dot(other),b[3].dot(other));
    }
    inline Matrix4f operator*(const Matrix4f& o) const 
    {
        // 这里 aIsRaw、b 已经在 this 上，你可以照之前的逻辑：
        if (o.aIsRaw) {
        return Matrix4f({
            (*this) * o.b[0],
            (*this) * o.b[1],
            (*this) * o.b[2],
            (*this) * o.b[3]
        });
        } else {
        return Matrix4f({
            (*this) * o.a[0],
            (*this) * o.a[1],
            (*this) * o.a[2],
            (*this) * o.a[3]
        });
        }
    }

    inline Matrix4f operator*(float k) {for(int i=0;i<4;++i){a[i]=a[i]*k;b[i]=b[i]*k;} return *this;}

    inline void print(){for(int i=0;i<4;++i) a[i].print();}
};

inline Matrix4f operator*(float k,Matrix4f v) {return v*k;}
#endif