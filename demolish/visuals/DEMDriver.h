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
    void UpdateScene(std::vector<demolish::Object>& objects);
    void RedrawTheWindow();

    void setContactPoints(std::vector<demolish::ContactPoint>& cps);

    void BuildBuffers(std::vector<demolish::Object> &objects);
    void OnMouseDown(XButtonEvent btn,int x, int y);
    void OnMouseUp(XButtonEvent btn,int x, int y);
    void OnMouseMove(int x, int y);

private:
    void BuildSphereBuffer(float radius,std::array<iREAL,3> position,int counter);
    void BuildMeshBuffer(demolish::Mesh& mesh);
public:
    std::vector<UINT>                   VAO;
    std::vector<UINT>                   VAOIndexCounts;
    std::vector<std::pair<UINT,UINT>>   VBO;          
 
    int mousex;
    int mousey;
    int but;
   
    GeometryGenerator geoGen;
    std::vector<GeometryGenerator::MeshData>  geoGenObjects;
    std::vector<demolish::ContactPoint>       contactpoints;

    AV4X4FLOAT viewModelMatrix;
    AV4X4FLOAT projMatrix;
        
        // Used in mouse momement overrides
    float theta;
    float phi;
    float radius;

    int  fill = 0;
};
