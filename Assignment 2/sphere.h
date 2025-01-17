#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"


//Original 
// class sphere: public hitable {
// public:
// 	sphere() {}
// 	sphere(vec3 cen, float r) : center(cen), radius(r) {};
// 	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
// 	vec3 center;
// 	float radius; 
// };

// bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
// 	vec3 oc = r.origin() - center;
// 	float a = dot(r.direction(), r.direction());
// 	float b = dot(oc, r.direction());
// 	float c = dot(oc, oc) - radius*radius;
// 	float discriminant = b*b - a*c;
// 	if (discriminant > 0) {
// 		float temp = (-b - sqrt(b*b-a*c))/a;
// 		if (temp < t_max && temp > t_min) {
// 			rec.t = temp;
// 			rec.p = r.point_at_parameter(rec.t);
// 			rec.normal = (rec.p - center) / radius;
// 			return true;
// 		}
// 		temp = (-b + sqrt(b*b-a*c))/a;
// 		if (temp < t_max && temp > t_min) {
// 			rec.t = temp;
// 			rec.p = r.point_at_parameter(rec.t);
// 			rec.normal = (rec.p - center) / radius;
// 			return true;
// 		}
// 	}
// 	return false;
// }

// Sphere w/Material
class sphere: public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), s_mat_ptr(m) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	vec3 center;
	float radius;
	material *s_mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b*b-a*c))/a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = s_mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b*b-a*c))/a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = s_mat_ptr;
			return true;
		}
	}
	return false;
}

#endif