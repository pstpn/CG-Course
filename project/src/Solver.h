#pragma once

/* This is solver of PDE
 * u_xx = a^2 u_tt
 * with boundary conditions:
 * u_x (x = 0, lx) = 0
 * u_y (y = 0, ly) = 0
 * u_z (z = 0, lz) = 0
 * and more boundary conditions for obstacles and sound sources.
 */
/* for every cube obstacle:
 * Cube is given as (x1, x2, y1, y2, z1, z2) so
 * u_x (x = x1, x2) = 0
 * u_y (y = y1, y2) = 0
 * u_z (z = z1, z2) = 0
 */
/* for every source:
 * source is given as (x1, y1, z1, nu1, A),
 * where nu1 is frequency and A is amplitude, so
 * u(x1, y1, z1) = A * sin(nu1 * t)
 */

#include <vector>
#include <memory>

struct WaveSource
{
  double x, y, z, nu;
};

struct Obstacle
{
  double x1, x2, y1, y2, z1, z2;
};

class Solver
{
  private:
    double lx, ly, lz, a; // params of the PDE
    double dx, dy, dz; // params
    std::vector<WaveSource> _sources;
    std::vector<Obstacle> _obstacles;
    
    // TODO make shared_ptr:
    double *** _prevPressure;
    double *** _pressure;

  public:
    explicit Solver(double _lx, double _ly, double _lz, double _a, double _dx = 0.1, double _dy = 0.1, double _dz = 0.1);
    void solve(double dt = 0.1);
    double ***getPressure() const;
};
