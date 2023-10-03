#include "Transformer.h"
#include <cmath>

Transformer::Transformer()
    : _matrix(4, 4, 0)
{
    for (size_t i = 0; i < 4; ++i)
    {
        _matrix[i][i] = 1;
    }
}

void Transformer::transform(Vertex &vert) {

    Matrix<double> mat = { {vert.getX(), vert.getY(), vert.getZ(), 1} };
    mat *= _matrix;

    vert = { mat[0][0], mat[0][1], mat[0][2] };
}

void Transformer::setTranslationMatrix(const double dx, const double dy, const double dz) {

    Matrix<double> mat(4, 4, 0);
    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
    mat[3][0] = dx;
    mat[3][1] = dy;
    mat[3][2] = dz;

    _matrix = mat;
}

void Transformer::setRotationMatrix(const double ax, const double ay, const double az) {

    Matrix<double> mat(4, 4, 0);

    double cos_ax = cos(ax), sin_ax = sin(ax);
    double cos_ay = cos(ay), sin_ay = sin(ay);
    double cos_az = cos(az), sin_az = sin(az);

    mat[0][0] = cos_ay * cos_az;
    mat[0][1] = sin_ax * sin_ay * cos_az - cos_ax * sin_az;
    mat[0][2] = cos_ax * sin_ay * cos_az + sin_ax * sin_az;

    mat[1][0] = cos_ay * sin_az;
    mat[1][1] = sin_ax * sin_ay * sin_az + cos_ax * cos_az;
    mat[1][2] = cos_ax * sin_ay * sin_az - sin_ax * cos_az;

    mat[2][0] = -sin_ay;
    mat[2][1] = sin_ax * cos_ay;
    mat[2][2] = cos_ax * cos_ay;

    mat[3][3] = 1;

    _matrix = mat;
}

void Transformer::setScalingMatrix(const double kx, const double ky, const double kz) {

    Matrix<double> mat(4, 4, 0);

    mat[0][0] = kx;
    mat[1][1] = ky;
    mat[2][2] = kz;
    mat[3][3] = 1;

    _matrix = mat;
}
