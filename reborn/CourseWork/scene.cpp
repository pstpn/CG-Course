#include "scene.hpp"
#include "model.hpp"
#include "sphere.hpp"

#include <windows.h>


const float EPS = 9.5*1e-2;

void Scene::addObject(Model& obj)
{
    objects.push_back(&obj);
}

void Scene::addObject(Model* obj)
{
    objects.push_back(obj);
}

void Scene::removeObject(int index)
{
    if (index >= 0 && index < objects.size())
        objects.erase(objects.begin() + index);
}

void Scene::removeSphere(int index)
{
    if (index >= 0 && index < spheres.size())
        spheres.erase(spheres.begin() + index);
}

std::vector<Model*>& Scene::getObjects()
{
    return objects;
}

void Scene::updateObjectColor(glm::vec4& newColor, int& modelIndex)
{
    objects[modelIndex]->setColor(newColor);
}

glm::vec4 Scene::getObjectColor(int& modelIndex)
{
    return objects[modelIndex]->getColor();
}

void Scene::addSphere(Model& sphere)
{
    spheres.push_back(&sphere);
}

void Scene::addSphere(Model* sphere)
{
    spheres.push_back(sphere);
}

LARGE_INTEGER
getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return (t);
}

int
clock_gettime(int X, struct timeval* tv)
{
    LARGE_INTEGER           t;
    FILETIME            f;
    double                  microseconds;
    static LARGE_INTEGER    offset;
    static double           frequencyToMicroseconds;
    static int              initialized = 0;
    static BOOL             usePerformanceCounter = 0;

    if (!initialized) {
        LARGE_INTEGER performanceFrequency;
        initialized = 1;
        usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
        if (usePerformanceCounter) {
            QueryPerformanceCounter(&offset);
            frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
        }
        else {
            offset = getFILETIMEoffset();
            frequencyToMicroseconds = 10.;
        }
    }
    if (usePerformanceCounter) QueryPerformanceCounter(&t);
    else {
        GetSystemTimeAsFileTime(&f);
        t.QuadPart = f.dwHighDateTime;
        t.QuadPart <<= 32;
        t.QuadPart |= f.dwLowDateTime;
    }

    t.QuadPart -= offset.QuadPart;
    microseconds = (double)t.QuadPart / frequencyToMicroseconds;
    t.QuadPart = microseconds;
    tv->tv_sec = t.QuadPart / 1000000;
    tv->tv_usec = t.QuadPart % 1000000;
    return (0);
}

void Scene::render(Shader& shaders, float& glTime)
{
    struct timeval start, end;
    double elapsed;

    clock_gettime(0, &start);
    for (auto& obj : objects)
        obj->Draw(shaders, glTime, *this);
    clock_gettime(0, &end);

    if (objects.size() == 8)
    {
        elapsed = (end.tv_sec - start.tv_sec) * 1000.0;
        elapsed += (end.tv_usec - start.tv_usec);
        printf("%f\n", elapsed);
    }

    for (unsigned int i = 0; i < spheres.size(); ++i)
        if (spheres[i]->getColor().w < EPS)
            removeSphere(i--);
        else
            spheres[i]->Draw(shaders, glTime, *this);
}