#include "Solver.h"

void Solver::generateWave(double x_center, double y_center, double z_center)
{
  int sectorCount = 100;
  int stackCount = 100;
  float radius = 100.0f;
  float sectorStep = 2 * M_PI / sectorCount;
  float stackStep = M_PI / stackCount;

  std::vector<Vertex> points;
  std::vector<Vertex> velocities;
  std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> triangles;

  for (int i = 0; i <= stackCount; ++i) {
      float stackAngle = M_PI / 2 - i * stackStep;
      float xy = radius * std::cos(stackAngle);
      float z = radius * std::sin(stackAngle);

      for (int j = 0; j <= sectorCount; ++j) {
          float sectorAngle = j * sectorStep;
          float x = xy * std::cos(sectorAngle);
          float y = xy * std::sin(sectorAngle);

          points.push_back({x + x_center, y + y_center, z + z_center});
          velocities.push_back({x, y, z});
      }
  }

  for (int i = 0; i < stackCount; ++i) {
      int k1 = i * (sectorCount + 1);
      int k2 = k1 + sectorCount + 1;

      for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
          if (i != 0) {
              triangles.push_back({k1, k2, k1 + 1});
          }

          if (i != stackCount - 1) {
              triangles.push_back({k1 + 1, k2, k2 + 1});
          }
      }
  }

  _waves.push_back(Wave{
    points, velocities, triangles
  });
}

Solver::Solver(double _a)
{}

void Solver::solve(double dt)
{
  // TODO
  if(_waves.size() == 0)
    for(auto &source : _sources) {
      generateWave(source.x, source.y, source.z);
    }
  for(auto &wave : _waves)
    for(uint32_t index=0; index<wave.points.size(); ++index) {
      wave.points[index] += wave.velocities[index] * dt;
    }
}

void Solver::addWaveSource(const WaveSource &tmp)
{
  _sources.push_back(tmp);
}

void Solver::addObstacle(const Obstacle &tmp)
{
  _obstacles.push_back(tmp);
}

std::vector<Wave> &Solver::getWaves()
{
    return _waves;
}
