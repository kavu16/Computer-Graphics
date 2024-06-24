////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
////////////////////////////////////////////////////////////////////////////////

typedef std::complex<double> Point;
typedef std::vector<Point> Polygon;

double inline det(const Point &u, const Point &v) {
	// TODO
	return u.real()*v.imag()-u.imag()*v.real();
}

// Return true iff [a,b] intersects [c,d], and store the intersection in ans
bool intersect_segment(const Point &a, const Point &b, const Point &c, const Point &d, Point &ans) {
	// TODO
	if (det((b-a),(d-c))==0) {
		return false;
	}
	else {
		double x, y;
		x = (det(b,a)*(d.real()-c.real())-det(d,c)*(b.real()-a.real()))/det((b-a),(d-c));
		y = (det(b,a)*(d.imag()-c.imag())-det(d,c)*(b.imag()-a.imag()))/det((b-a),(d-c));
		ans = Point(x,y);

		if (std::max(a.real(),b.real()) < std::min(c.real(),d.real())) {
			return false;
		}
		else if ( (ans.real() < std::max(std::min(a.real(),b.real()),std::min(c.real(),d.real())))||
			ans.real() > std::min(std::max(a.real(),b.real()),std::max(c.real(),d.real()))) {
			return false;
		}
		return true;
	}
}

////////////////////////////////////////////////////////////////////////////////

bool is_inside(const Polygon &poly, const Point &query) {
	// 1. Compute bounding box and set coordinate of a point outside the polygon
	// TODO
	Point outside(0, 0);
	double outside1,outside2;
	for (int i=0; i < poly.size(); i++) {
		if (poly[i].imag() > outside.imag()) {
			outside2 = poly[i].imag();
		}
	}
	for (int i=0; i < poly.size(); i++) {
		if (poly[i].real() > outside.real()) {
			outside1 = poly[i].real();
		}
	}
	outside = Point(outside1+1024,outside2+1024);
	// 2. Cast a ray from the query point to the 'outside' point, count number of intersections
	// TODO
	Point intersect(0,0);
	int intersect_count = 0;
	int vertex = 0;
	for (int i=1; i < poly.size(); i++) {
		if (intersect_segment(query,outside,poly[i-1],poly[i],intersect)) {
			intersect_count += 1;
			if (intersect == poly[i-1] || intersect == poly[i]) {
				vertex = 1;
			}
		}
	}
	if (intersect_segment(query,outside,poly[0],poly[poly.size()-1],intersect)) {
		intersect_count += 1;
		if (intersect == poly[0] || intersect == poly[poly.size()-1]) {
			vertex = 1;
		}
	}
	return (!((intersect_count+vertex) % 2 == 0));
}

////////////////////////////////////////////////////////////////////////////////

std::vector<Point> load_xyz(const std::string &filename) {
	std::vector<Point> points;
	std::ifstream in(filename);
	// TODO
	char buffer[64];
	in.getline(buffer,64);
	int num = atoi(buffer);
	for (int i = 0; i < num; i++) { 
		double p1, p2;
		in.getline(buffer,64,' ');
		p1 = std::stod(buffer);
		in.getline(buffer,64,' ');
		p2 = std::stod(buffer);
		Point coord = Point(p1,p2);
		points.push_back(coord);
		in.ignore();
	}
	return points;
}

Polygon load_obj(const std::string &filename) {
	std::ifstream in(filename);
	// TODO
	char buffer[64];
	Polygon bound;
	in.getline(buffer,2,' ');
	while (strcmp(buffer,"v")==0) {
		double p1,p2;
		in.getline(buffer,64,' ');
		p1 = std::stod(buffer);
		in.getline(buffer,64,' ');
		p2 = std::stod(buffer);
		Point coord = Point(p1,p2);
		bound.push_back(coord);

		in.ignore();
		in.ignore();
		in.getline(buffer,2,' ');
	} 

	return bound;
}

void save_xyz(const std::string &filename, const std::vector<Point> &points) {
	// TODO
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw std::runtime_error("failed to open file " + filename);
	}
	out << std::fixed;
	out << points.size() << "\n";
	for (const auto &v : points) {
		out << v.real() << ' ' << v.imag() << " 0\n";
	}
	out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
	if (argc <= 3) {
		std::cerr << "Usage: " << argv[0] << " points.xyz poly.obj result.xyz" << std::endl;
	}
	std::vector<Point> points = load_xyz(argv[1]);
	Polygon poly = load_obj(argv[2]);
	std::vector<Point> result;
	for (size_t i = 0; i < points.size(); ++i) {
		if (is_inside(poly, points[i])) {
			result.push_back(points[i]);
		}
	}
	save_xyz(argv[3], result);
	return 0;
}
