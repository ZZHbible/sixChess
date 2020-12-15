//#include<iostream>
//using namespace std;
//#include<vector>
//struct Point
//{
//	int x;
//	int y;
//	Point() {};
//	Point(int a, int b) :x(a), y(b) {}
//};
//int main() {
//	vector<Point> p;
//	p.push_back(Point(1, 2));
//	p.push_back(Point(2, 3));
//	p.push_back(Point(3, 4)); p.push_back(Point(5, 6));
//	for (vector<Point>::iterator it1 = p.begin(); it1 != p.end(); ++it1) {
//		Point p1 = *it1;
//		for (vector<Point>::iterator it2 = it1 + 1; it2 != p.end(); ++it2) {
//			Point p2 = *it2;
//			cout << "Point2.x" << p2.x << "Point2.y" << p2.y << endl;
//			cout << "Point1.x" << p1.x << "Point1.y" << p1.y << endl;
//		}
//	}
//}