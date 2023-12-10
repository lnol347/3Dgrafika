#pragma once
#include <cmath>
#include "geometry.h"
#include "ray.h"
#include "material.h"
#include <limits>
#include <iostream>
using namespace std;

class Object 
{
  public:
    Material material;
    virtual bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const = 0;  
};

class Sphere : public Object
{
    float r;
    Vec3f c;
      
  public:
    Sphere(const Vec3f &c, const float &r) : c(c), r(r) { }
    Sphere(const Vec3f &c, const float &r, const Material &mat) : c(c), r(r)
    { 
        Object::material = mat;
    }

    bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const
    {
        Vec3f e_minus_c = ray.origin - c;
        float d2 = ray.direction * ray.direction;
        
        float disc = pow(ray.direction * e_minus_c, 2) - d2 * (e_minus_c * e_minus_c - r * r);
        
        if (disc < 0)
        {
            return false;
        }
        else
        {
            bool ray_inside_sphere = e_minus_c * e_minus_c <= r * r;
            if (ray_inside_sphere)
            {
                float t1 = (-ray.direction * e_minus_c + sqrt(disc)) / d2;
                t = t1;
            }
            else
            {
                float t2 = (-ray.direction * e_minus_c - sqrt(disc)) / d2;
                t = t2;
            }
            
            Vec3f hit_point = ray.origin + ray.direction * t;
            normal = (hit_point - c).normalize();
            return true;
        }
    }
};

struct Cuboid : public Object
{
    Vec3f c1;
    Vec3f c2;

    Cuboid(const Vec3f &c1, const Vec3f &c2, const Material &mat): c1(c1), c2(c2) {
        Object::material = mat;
    }

    bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const{
        float t_min = numeric_limits<float>::min(); // najmanji broj u float obliku
        float t_max = numeric_limits<float>::max(); // najveci broj u float obliku

        // strane kvadra
        float min_x = min(c1.x, c2.x);
        float max_x = max(c1.x, c2.x);

        float min_y = min(c1.y, c2.y);
        float max_y = max(c1.y, c2.y);

        float min_z = min(c1.z, c2.z);
        float max_z = max(c1.z, c2.z);
        
        //x
        if(ray.direction.x == 0){
            if(ray.origin.x < min_x || ray.origin.x > max_x){
                return false; // tocka ne lezi u kvadru
            }
        }else{
            float t1 = (min_x - ray.origin.x) / ray.direction.x;
            float t2 = (max_x - ray.origin.x) / ray.direction.x;

            if(t1 > t2){
                swap(t1, t2);
            }

            t_min = max(t_min, t1);
            t_max = min(t_max, t2); 

            if(t_min > t_max || t_max < 0){
                return false;
            }
        }

        t = t_min;

        //y
        if(ray.direction.y == 0){
            if(ray.origin.y < min_y || ray.origin.y > max_y){
                return false;
            }
        }else{
            float t1 = (min_y - ray.origin.y) / ray.direction.y;
            float t2 = (max_y - ray.origin.y) / ray.direction.y;

            if(t1 > t2){
                swap(t1,t2);
            }

            t_min = max(t_min, t1);
            t_max = min(t_max, t2);

            if(t_min > t_max || t_max < 0){
                return false;
            }
        }

        t = t_min;

        //z
        if(ray.direction.z == 0){
            if(ray.origin.z < min_z || ray.origin.z > max_z){
                return false;
            }
        }else{
            float t1 = (min_z - ray.origin.z) / ray.direction.z;
            float t2 = (max_z - ray.origin.z) / ray.direction.z;

            if(t1 > t2){
                swap(t1, t2);
            }

            t_min = max(t_min, t1);
            t_max = min(t_max, t2);

            if(t_min > t_max || t_max < 0){
                return false;
            }
        }

        t = t_min;

        //normale

        if(abs(ray.origin.x - c1.x) < 0.01){
            normal = Vec3f(1, 0, 0);
        }else if(abs(ray.origin.x - c2.x) < 0.01){
            normal = Vec3f(-1, 0, 0);
        }else if(abs(ray.origin.y - c1.y) < 0.01){
            normal = Vec3f(0, 1, 0);
        }else if(abs(ray.origin.y - c2.y) < 0.01){
            normal = Vec3f(0, -1, 0);
        }else if(abs(ray.origin.z - c1.z) < 0.01){
            normal = Vec3f(0, 0, 1);
        }else if(abs(ray.origin.z - c2.z) < 0.01){
            normal = Vec3f(0, 0, -1);
        }


        return true;
    }
};