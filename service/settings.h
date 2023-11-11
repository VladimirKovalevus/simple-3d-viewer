#ifndef SETTINGS_H
#define SETTINGS_H
#include "Mesh/Primitives.h"
enum projection
{
    parallel,
    central
};
enum line_type
{
    dotted,
    solid
};
enum vertex_type
{
    none,
    circle,
    square
};

class Settings
{
public:
    static Settings& getInstance();




private:
    Settings();

    line_type m_line;
    double m_line_size;

    vertex_type m_vertex;
    double m_vertex_size;

    projection m_projection;

    Vec3 m_line_color;
    Vec3 m_vertex_color;
    Vec3 m_background_color;
};

#endif // SETTINGS_H
