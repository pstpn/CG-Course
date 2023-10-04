#include "Solver.h"

Solver::Solver(double _lx, double _ly, double _lz, double _a, double _dx, double _dy, double _dz)
  : lx(_lx), ly(_ly), lz(_lz), a(_a), dx(_dx), dy(_dy), dz(_dz)
{
  _sources.push_back(WaveSource{0, 0, 0});
  _obstacles.push_back(Obstacle{-lx/2., lx/2., -ly/2., ly/2., 0, lz});

  uint32_t Nx = lx / dx, Ny = ly / dy, Nz = lz / dz;

  _prevPressure = new double**[Nx];
  // _pressure = std::make_shared<double ***>(new double**[Nx]);

  for(uint32_t x = 0; x < Nx; x++) {
    _prevPressure[x] = new double*[Ny];
    for(uint32_t y = 0; y < Ny; y++) {
      _prevPressure[x][y] = new double[Nz];
    }
  }
}

void Solver::solve(double dt)
{
  // TODO
}
 
double *** Solver::getPressure() const
{
  return _pressure;
}
