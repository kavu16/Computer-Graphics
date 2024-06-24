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
	return u.real()*v.imag() - v.real()*u.imag(); //calculate determinant of two points
}

struct Compare {
	Point p0; // Leftmost point of the poly
	bool operator ()(const Point &p1, const Point &p2) {
		// TODO
		if (det(p1-p0,p2-p0)==0) {
			return (p1.real()<p2.real()); //uses left most point if colinear from p0 (<= leads to infinite loop on sort, must oscillate between the two points)
		}
		else {
			return (det(p1-p0,p2-p0)>=0);
		}
	}
};

bool inline salientAngle(Point &a, Point &b, Point &c) {
	// TODO
	return (det(b-a,c-b)<=0); //determinant of two vectors gives the signed area of the polygon between them, positive if moving CCW (left turn), negative if CW (right turn)
}

////////////////////////////////////////////////////////////////////////////////

Polygon convex_hull(std::vector<Point> &points) {
	Compare order;
	// TODO
	order.p0 = Point(0, 0);
	std::sort(points.begin(), points.end(), order);  //find first point CCW from pos x-axis
	order.p0 = points.front();
	std::sort(points.begin(), points.end(), order);  //sort CCW from first point
	Polygon hull;
	// TODO
	// use salientAngle(a, b, c) here
	for (int i=0; i<points.size(); i++) {
		//While adding points to the hull, check the last two points added with the new point to check for right turn, pop the last added ("middle" point) if so
		while (hull.size() > 1 && salientAngle(hull.end()[-2],hull.end()[-1],points[i])) {
			hull.pop_back();
		}
		hull.push_back(points[i]);
	}

	return hull;
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

void save_obj(const std::string &filename, Polygon &poly) {
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw std::runtime_error("failed to open file " + filename);
	}
	out << std::fixed;
	for (const auto &v : poly) {
		out << "v " << v.real() << ' ' << v.imag() << " 0\n";
	}
	for (size_t i = 0; i < poly.size(); ++i) {
		out << "l " << i+1 << ' ' << 1+(i+1)%poly.size() << "\n";
	}
	out << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {
	if (argc <= 2) {
		std::cerr << "Usage: " << argv[0] << " points.xyz output.obj" << std::endl;
	}
	std::vector<Point> points = load_xyz(argv[1]);
	Polygon hull = convex_hull(points);
	save_obj(argv[2], hull);
	return 0;
}
