#include <cmath>

#include "Vertex.h"

double toRadians(const double angle) {
    return angle * (M_PI / 180);
}

Vertex::Vertex(double v)
    : _x(v),
      _y(v),
      _z(v)
{
}

Vertex::Vertex(const double x, const double y, const double z)
    : _x(x),
      _y(y),
      _z(z)
{
}


Vertex::Vertex(Vertex &&other) noexcept
{
    setX(other._x);
    setY(other._y);
    setZ(other._z);

    other.~Vertex();
}


Vertex &Vertex::operator=(Vertex &&other) noexcept
{
    setX(other._x);
    setY(other._y);
    setZ(other._z);

    other.~Vertex();

    return *this;
}

double Vertex::getX() const noexcept
{
    return _x;
}

double Vertex::getY() const noexcept
{
    return _y;
}

double Vertex::getZ() const noexcept
{
    return _z;
}

void Vertex::setX(const double x)
{
    _x = x;
}

void Vertex::setY(const double y)
{
    _y = y;
}

void Vertex::setZ(const double z)
{
    _z = z;
}

bool Vertex::operator==(const Vertex &other) const noexcept
{
    return (other._x == _x) && (other._y == _y) && (other._z == _z);
}

bool Vertex::isEqual(const Vertex &other) const noexcept
{
    return *this == other;
}

bool Vertex::operator!=(const Vertex &other) const noexcept
{
    return !(*this == other);
}

bool Vertex::isNotEqual(const Vertex &other) const noexcept
{
    return !(*this == other);
}

Vertex Vertex::operator+(const Vertex &other) const
{
    Vertex d{*this};

    d.setX(d._x + other._x);
    d.setY(d._y + other._y);
    d.setZ(d._z + other._z);

    return d;
}

Vertex Vertex::operator-(const Vertex &other) const
{
    Vertex d{*this};

    d.setX(d._x - other._x);
    d.setY(d._y - other._y);
    d.setZ(d._z - other._z);

    return d;
}

Vertex Vertex::operator*(const Vertex &other) const
{
    Vertex d{*this};

    d.setX(d._x * other._x);
    d.setY(d._y * other._y);
    d.setZ(d._z * other._z);

    return *this;
}

Vertex Vertex::operator*(const double &coef) const
{
    Vertex d{*this};

    d.setX(d._x * coef);
    d.setY(d._y * coef);
    d.setZ(d._z * coef);

    return *this;
}

Vertex &Vertex::operator+=(const Vertex &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;

    return *this;
}

Vertex &Vertex::operator-=(const Vertex &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;

    return *this;
}


void Vertex::transform(const Matrix<double> &mat)
{
    Matrix<double> curLocation = {{_x, _y, _z, 1}};
    Matrix<double> newLocation = curLocation * mat;

    _x = newLocation[0][0];
    _y = newLocation[0][1];
    _z = newLocation[0][2];
}

double Vertex::dotProduct(const Vertex &a, const Vertex &b) noexcept
{
    return (a._x * b._x) + (a._y * b._y) + (a._z * b._z);
}

Vertex Vertex::crossProduct(const Vertex &a, const Vertex &b) noexcept
{
    Vertex result;

    result._x = a._y * b._z - a._z * b._y;
    result._y = -(a._x * b._z - a._z * b._x);
    result._z = a._x * b._y - a._y * b._x;

    return result;
}

Vertex Vertex::getOrigin() const
{
    return *this;
}

Vertex Vertex::getAbsVertex(const Vertex &center)
{
    return (*this) + center;
}

void Vertex::normalize()
{
    double length = sqrt(_x * _x + _y * _y + _z * _z);
    _x /= length;
    _y /= length;
    _z /= length;
}
