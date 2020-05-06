#include"GLnixAPP.h"
#include"MathHelper.h"
#include"GeometryGenerator.h"
#include"../Object.h"
#include"../ContactPoint.h"
using std::vector;

class DEMDriver : public GLnixAPP
{
public:
    DEMDriver(); /* Constructor */
    bool Init(); /* Initialisation routine */
    void UpdateScene(std::vector<crashr::Object>& objects);
    void RedrawTheWindow();

    void setContactPoints(std::vector<crashr::ContactPoint>& cps);

    void BuildBuffers(std::vector<crashr::Object> &objects);
    void OnMouseDown(XButtonEvent btn,int x, int y);
    void OnMouseUp(XButtonEvent btn,int x, int y);
    void OnMouseMove(int x, int y);

private:
    void BuildDynamicSphereBuffer(float radius,std::array<double,3> position,int counter);
    void BuildDynamicMeshBuffer(crashr::Mesh* mesh);
    void BuildStaticSphereBuffer(float radius,std::array<double,3> position,int counter);
    void BuildStaticMeshBuffer(crashr::Mesh* mesh);
public:
    //graphics pipeline stuff for moving things
    std::vector<UINT>                   VAODynamic;
    std::vector<UINT>                   VAOIndexCountsDynamic;
    std::vector<std::pair<UINT,UINT>>   VBODynamic;         

    //graphics pipeline stuff for non-moving things
    std::vector<UINT>                   VAOStatic;
    std::vector<UINT>                   VAOIndexCountsStatic;
    std::vector<std::pair<UINT,UINT>>   VBOStatic;          
 
    int mousex;
    int mousey;
    int but;
  
    int staticCount;
    int dynamicCount;
    GeometryGenerator                         geoGen;
    std::vector<GeometryGenerator::MeshData>  geoGenObjectsDynamic;
    std::vector<GeometryGenerator::MeshData>  geoGenObjectsStatic;
    std::vector<crashr::ContactPoint>       contactpoints;

    AV4X4FLOAT viewModelMatrix;
    AV4X4FLOAT projMatrix;
        
        // Used in mouse momement overrides
    float theta;
    float phi;
    float radius;

    int  fill = 0;
};
