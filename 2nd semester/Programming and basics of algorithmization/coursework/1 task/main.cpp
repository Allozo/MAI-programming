#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

struct TPlot {
    TPlot() = default;

    TPlot(double x_coord, double y_coord) {
        x = x_coord;
        y = y_coord;
    }

    double x;
    double y;
};

class Polygon {
public:
    Polygon();

    explicit Polygon(int n);

    Polygon(Polygon &p);

    friend Polygon operator*(Polygon &old_polygon, double value);

    friend Polygon operator*(double value, Polygon &old_polygon);

    friend ostream &operator<<(ostream &, const Polygon &);

    Polygon &operator++();

    const Polygon operator++(int);

    TPlot operator[](int i);

    double perimeter();

    int size();

private:

    vector<TPlot> coordinate;
    int number;
};

Polygon::Polygon() {
    number = 0;
    coordinate.resize(0);
};

Polygon::Polygon(int n) {
    number = n;
    for (int i = 0; i < n; i++) {
        double x = cos(2 * M_PI * i / n);
        double y = sin(2 * M_PI * i / n);
        TPlot new_point(x, y);
        coordinate.push_back(new_point);
    }
}

Polygon::Polygon(Polygon &p) {
    this->coordinate = p.coordinate;
    this->number = p.size();
}

Polygon operator*(Polygon &old_polygon, double value) {
    Polygon res(old_polygon);
    for (int i = 0; i < old_polygon.size(); i++) {
        res.coordinate[i].x *= value;
        res.coordinate[i].y *= value;
    }
    return res;
}

Polygon operator*(double value, Polygon &old_polygon) {
    Polygon res(old_polygon);
    for (int i = 0; i < old_polygon.size(); i++) {
        res.coordinate[i].x *= value;
        res.coordinate[i].y *= value;
    }
    return res;
}

ostream &operator<<(ostream &str, const Polygon &plot) {
    for (auto i: plot.coordinate) {
        cout << i.x << " " << i.y << endl;
    }
}

Polygon &Polygon::operator++(){
    for (int i = 0; i < number; i++) {
        coordinate[i].x++;
    }
}

const Polygon Polygon::operator++(int) {
    Polygon res = *this;
    ++(*this);
    return *this;
}

TPlot Polygon::operator[](int i){
    return coordinate[i];
}

double Polygon::perimeter() {
    double res = 0;
    for (int i = 0; i < number - 1; i++) {
        double x1 = coordinate[i].x;
        double x2 = coordinate[i+1].x;
        double y1 = coordinate[i].y;
        double y2 = coordinate[i+1].y;
        res += sqrt(pow((x2-x1), 2) + pow((y2 - y1), 2));
    }
    return res;
}

int Polygon::size() {
    return number;
}

int main() {
    Polygon t(4);
    cout << t;
    cout << "----------" << endl;
    t = 3 * t;
    t = t * 3;
    cout << t;
    cout << "----------" << endl;
    ++t;
    t++;
    cout << t;
    cout << "----------" << endl;
    cout << t[0].x << " " << t[0].y << endl;
    cout << "----------" << endl;
    cout << t.perimeter() << endl;
    return 0;
}