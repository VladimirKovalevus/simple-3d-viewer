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
    static Settings& getSettings();

    line_type getLineType() const;
    double getLineSize() const;
    Vec3 getLineColor() const;
    vertex_type getVertexType() const;
    Vec3 getVertexColor() const;
    double getVertexSize() const;
    projection getProjectionType() const;
    Vec3 getBackgroundColor() const;
    void setLineType(line_type type);
    void setLineSize(double size);
    void setLineColor(Vec3 color);
    void setVertexColor(Vec3 color);
    void setVertexType(vertex_type type);
    void setVertexSize(double size);
    void setProjectionType(projection type);
    void setBackgroundColor(Vec3 color);

private:
    Settings();
    ~Settings();
    line_type m_line;
    double m_line_size;
    Vec3 m_line_color;

    vertex_type m_vertex;
    Vec3 m_vertex_color;
    double m_vertex_size;

    projection m_projection;
    Vec3 m_background_color;
};

#endif // SETTINGS_H
