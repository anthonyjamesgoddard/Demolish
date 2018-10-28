#include"GLnixAPP.h"
#include"MathHelper.h"
#include"GeometryGenerator.h"
#include"../Object.h"
using std::vector;

class DEMDriver : public GLnixAPP
{
public:
    DEMDriver(); /* Constructor */
    bool Init(); /* Initialisation routine */
    void UpdateScene(float dt);
    void RedrawTheWindow();
      
    void BuildBuffers(std::vector<demolish::object> objects);
    void OnMouseDown(XButtonEvent btn,int x, int y);
    void OnMouseUp(XButtonEvent btn,int x, int y);
    void OnMouseMove(int x, int y);
private:
    void BuildMeshBuffer(demolish::Mesh& mesh);
public:
    std::vector<UINT> VAO;
    std::vector<UINT> VAOIndexCounts;
    UINT buffers[2];          
 
    int mousex;
    int mousey;
    int but;
    
    std::vector<GeometryGenerator::MeshData>  geoGenObjects;

    AV4X4FLOAT viewModelMatrix;
    AV4X4FLOAT projMatrix;
        
        // Used in mouse momement overrides
    float theta;
    float phi;
    float radius;
};
