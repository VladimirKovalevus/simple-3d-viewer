#include "settings.h"
#include <fstream>

Settings& Settings::getSettings(){
    static Settings instance;
    return instance;
}


Settings::Settings():m_line(line_type::solid),
                    m_vertex(vertex_type::none),
                    m_projection(projection::parallel),
                    m_vertex_color(),
                    m_line_color(),
                    m_background_color(),
                    m_line_size{0},
                    m_vertex_size{0}
{
    std::ifstream a("settings.choom");
    if (a.is_open()){
        std::string s;
        a >> s;
        m_line = s=="dotted"? line_type::dotted: line_type::solid;
        a >> s;
        m_vertex = s=="circle"? vertex_type::circle :
                    s=="sqare" ? vertex_type::square
                    :vertex_type::none;
        a >> s;
        m_projection = s=="central"? projection::central: projection::parallel;
        
        double x,y,z;
        
        a >> x >> y >> z;
        m_line_color.x =x;
        m_line_color.y =y;
        m_line_color.z =z;

        a >> x >> y >> z;
        m_vertex_color.x =x;
        m_vertex_color.y =y;
        m_vertex_color.z =z;
        
        a >> x >> y >> z;
        m_background_color.x =x;
        m_background_color.y =y;
        m_background_color.z =z;
        
        a>>x;
        m_line_size =x;
        a>>x;
        m_vertex_size =x;
    }
    a.close();
}

Settings::~Settings(){
    std::ofstream a("settings.choom");
    if (a.is_open()){
        a << (m_line ==line_type::dotted? "dotted": "solid")<<"\n";
        
        a << (m_vertex ==vertex_type::square
                ? "square": m_vertex==vertex_type::circle 
                ? "circle": "none")<<"\n";
        a<< (m_projection == projection::central?"central": "parallel")<<"\n";
        
        a <<m_line_color.x <<" "
          <<m_line_color.y <<" "
          <<m_line_color.z <<"\n";

        a <<m_vertex_color.x<<" " 
          <<m_vertex_color.y<<" "
          <<m_vertex_color.z<<"\n";
        
         a<<m_background_color.x<<" " 
          <<m_background_color.y<<" "
          <<m_background_color.z<<"\n";
        
        a<<m_line_size<<"\n";
        a<<m_vertex_size<<"\n";
    }
    a.close();
}



line_type Settings::getLineType() const{
    return m_line;   
}
double Settings::getLineSize() const{
    return m_line_size;
}
Vec3 Settings::getLineColor() const{
    return m_line_color;
}
vertex_type Settings::getVertexType() const{
    return m_vertex;
}
Vec3 Settings::getVertexColor() const{
    return  m_vertex_color;
}
double Settings::getVertexSize() const{
    return m_vertex_size;
}
projection Settings::getProjectionType() const{
    return m_projection;
}
Vec3 Settings::getBackgroundColor() const{
    return m_background_color;
}
void Settings::setLineType(line_type type){
    m_line =type;
}
void Settings::setLineSize(double size){
    m_line_size = size;
}
void Settings::setLineColor(Vec3 color){
    m_line_color = color;
}
void Settings::setVertexColor(Vec3 color){
    m_vertex_color = color;
}
void Settings::setVertexType(vertex_type type){
    m_vertex = type;
}
void Settings::setVertexSize(double size){
    m_vertex_size =size;
}
void Settings::setProjectionType(projection type){
    m_projection = type;
}
void Settings::setBackgroundColor(Vec3 color){
    m_background_color = color;
}