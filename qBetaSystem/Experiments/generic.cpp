#include <iostream>
using namespace std;
// Generic (template) class
template <typename T>
class Box {
private:
    T value;        // member variable of generic type
public:
    // Constructor with parameter of generic type
    Box(T initialValue) : value(initialValue) { }  
    // Method with parameter of generic type
    void setValue(T newValue) { value = newValue; }
    // Method returning generic type
    T getValue() { return value; }
    void update() { value.x = 100.0; }
};
struct Point {
    double x, y;
    Point(double xVal, double yVal) : x(xVal), y(yVal) {}
};
struct Point3D : Point {
    double z;
    Point3D(double xVal, double yVal, double zVal)
        : Point(xVal, yVal), z(zVal) {}
};
int main() {
    Box<Point> BP(Point(10.0,12.0));
    Point3D p3d(1.0, 2.0, 3.0);
    Point p = BP.getValue();
    Point *px;
    cout << "Point in Box: (" << p.x << ", " << p.y << ")" << endl;
    cout << "Point3D p3d(" << p3d.x << ", " << p3d.y << ", " << p3d.z << ")"  << endl;
    BP.setValue(p3d);
    cout << "Point3D in Box: (" << p3d.x << ", " << p3d.y << ", " << p3d.z << ")"  << endl;
    p = BP.getValue();
    cout << "Point in Box: (" << p.x << ", " << p.y << ")" << endl;
    BP.update();
    cout << "Point3D p3d after update(" << p3d.x << ", " << p3d.y << ", " << p3d.z << ")"  << endl;
    p = BP.getValue();
    cout << "Point p(" << p.x << ", " << p.y << ")" << endl;
    // BP.setValue(px);
    return 0;
}