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
#include "Vertex.h"
#include <tuple>
#include <cmath>

struct WaveSource
{
  double x, y, z, nu;
};

struct Obstacle // TODO подумать над произвольными объектами
{
  double x1, x2, y1, y2, z1, z2;
};

struct Wave
{
  std::vector<Vertex> points;
  std::vector<Vertex> velocities;
  std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> triangles;
};

class Solver
{
  private:
    double velocity;
    
    std::vector<WaveSource> _sources;
    std::vector<Obstacle> _obstacles;
    
    std::vector<Wave> _waves;

    void generateWave(double x, double y, double z);

  public:
    explicit Solver(double _a);
    void solve(double dt = 0.001);
    
    void addWaveSource(const WaveSource &tmp);
    void addObstacle(const Obstacle &tmp);


    std::vector<Wave> &getWaves();
};
