#include "Solver.h"

bool checkCollision(const Point& point, const Obstacle& obstacle) {
    return (point.x >= obstacle.x1 && point.x <= obstacle.x2 &&
            point.y >= obstacle.y1 && point.y <= obstacle.y2 &&
            point.z >= obstacle.z1 && point.z <= obstacle.z2);
}

bool checkCollisionWithRoom(const Point& point, const Obstacle& room) {
    return (point.x < room.x1 || point.x > room.x2 ||
            point.y < room.y1 || point.y > room.y2 ||
            point.z < room.z1 || point.z > room.z2);
}

void handleCollisionWithObstacle(Point& point, const Obstacle& obstacle) {
    // Calculate the normal vector of the obstacle
    double nx = 0.0, ny = 0.0, nz = 0.0;

    // Determine which side of the obstacle was hit and set the corresponding normal
    if (point.x < obstacle.x1 || point.x > obstacle.x2) {
        nx = (point.x < obstacle.x1) ? -1.0 : 1.0;
    }
    if (point.y < obstacle.y1 || point.y > obstacle.y2) {
        ny = (point.y < obstacle.y1) ? -1.0 : 1.0;
    }
    if (point.z < obstacle.z1 || point.z > obstacle.z2) {
        nz = (point.z < obstacle.z1) ? -1.0 : 1.0;
    }

    // Calculate the reflection of velocity vector
    double dotProduct = 2 * (point.vx * nx + point.vy * ny + point.vz * nz);
    point.vx -= dotProduct * nx;
    point.vy -= dotProduct * ny;
    point.vz -= dotProduct * nz;
}

void handleCollisionWithRoom(Point& point, const Obstacle& room) {
    // Calculate the reflection of velocity vector for room boundaries
    if (point.x < room.x1 || point.x > room.x2) {
        point.vx = -point.vx;
    }
    if (point.y < room.y1 || point.y > room.y2) {
        point.vy = -point.vy;
    }
    if (point.z < room.z1 || point.z > room.z2) {
        point.vz = -point.vz;
    }
}

void Solver::generateWave(double x_center, double y_center, double z_center)
{
  int sectorCount = 20;
  int stackCount = 20;
  float radius = 0.1f;
  float sectorStep = 2 * M_PI / sectorCount;
  float stackStep = M_PI / stackCount;

  float speed = 1000.f;

  std::vector<Point> points;
  std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> triangles;

  for (int i = 0; i <= stackCount; ++i) {
      float stackAngle = M_PI / 2 - i * stackStep;
      float xy = radius * std::cos(stackAngle);
      float z = radius * std::sin(stackAngle);

      for (int j = 0; j <= sectorCount; ++j) {
          float sectorAngle = j * sectorStep;
          float x = xy * std::cos(sectorAngle);
          float y = xy * std::sin(sectorAngle);

          points.push_back({
              x + x_center, y + y_center, z + z_center, // cooridnates
              x / radius * speed, y / radius * speed, z / radius * speed}); // velocity
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
    points, triangles
  });
}

Solver::Solver()
  : global_time(0)
{}

void Solver::solve(double dt)
{
  const double wave_lifetime = 0.25f;

  global_time += dt;

  // TODO
  // if(_waves.size() == 0)
  for(auto &source : _sources) {
    if(!source.last_wave_time or source.last_wave_time < global_time - 1.f / source.nu) {
      generateWave(source.x, source.y, source.z);
      _waves[_waves.size() - 1].spawn_time = global_time;
      source.last_wave_time = global_time;

      std::cout << "New wave spawned:" << global_time << std::endl;
    }
  }

  for (auto it = _waves.begin(); it != _waves.end(); ) {
    if (it->spawn_time < global_time - wave_lifetime) {
      it = _waves.erase(it);
      std::cout << "Wave removed:" << global_time << std::endl;
    } else
      ++it;
  }

  for(auto &wave : _waves) {
    for(auto &point : wave.points) {
      point.x += point.vx * dt;
      point.y += point.vy * dt;
      point.z += point.vz * dt;

      // Check for collisions with obstacles and room boundaries
      bool collided = false;

      for (const Obstacle& obstacle : _obstacles) {
        if (checkCollision(point, obstacle)) {
          // Handle collision with the obstacle
          handleCollisionWithObstacle(point, obstacle);
          collided = true;
          break;
        }
      }

      if (!collided) {
        handleCollisionWithRoom(point, room);
      } else {
        point.collision_count ++;
      }
    }
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

void Solver::setRoom(const Obstacle &tmp)
{
  room = tmp;
}

std::vector<Wave> &Solver::getWaves()
{
    return _waves;
}
