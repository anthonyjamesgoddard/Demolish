#include"DEMDriver.h"
#include"myextloader.h"


PFNGLBINDBUFFERPROC GLnix_glBindBuffer;
PFNGLGENBUFFERSPROC GLnix_glGenBuffers;
PFNGLDELETEBUFFERSPROC GLnix_glDeleteBuffer;
PFNGLBUFFERDATAPROC GLnix_glBufferData;
PFNGLBUFFERSUBDATAPROC GLnix_glBufferSubData;
PFNGLMAPBUFFERPROC GLnix_glMapBuffer;
PFNGLUNMAPBUFFERPROC GLnix_glUnmapBuffer;
PFNGLBINDVERTEXARRAYPROC GLnix_glBindVertexArray;
PFNGLGENVERTEXARRAYSPROC GLnix_glGenVertexArrays;


float const light0_dir[]={1,0,0,0};
float const light0_color[]={78./255., 8./255., 184./255.,1};

float const light1_dir[]={0,0,1,0};
float const light1_color[]={25./255., 220./255., 70./255.,1};

float const light2_dir[]={0,1,0,0};
float const light2_color[]={31./255., 75./255., 160./255.,1};

DEMDriver::DEMDriver()
: GLnixAPP(), phi(1.5f*MathHelper::Pi),theta(1.5f*MathHelper::Pi), radius(10)
{
    load_extension_function_pointers();
    mousex = 0;
    mousey = 0;
    AV4FLOAT r(1,1,1,1);
    AV4X4FLOAT I;
    I.diag (r);

    projMatrix = I;
    viewModelMatrix = I;

}



bool DEMDriver::Init()
{
    

    if(!GLnixAPP::Init())
        return false; 
    
    projMatrix =formProjMatrix(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    return true;
}


void DEMDriver::UpdateScene(float dt)
{
	float x = radius*sinf(phi)*cosf(theta);
	float z = radius*sinf(phi)*sinf(theta);
	float y = radius*cosf(phi);


	AV4FLOAT position(x,y,z,1.0);
	
	AV4FLOAT target(0.0,0.0,0.0,0.0);
	AV4FLOAT up(0.0,1.0,0.0,0.0);

	viewModelMatrix = formViewModelMatrix(position,target,up);

    
    // use a for loop to go through all objects in VAO and execute similar code to below.
    //
}

void DEMDriver::RedrawTheWindow()
{
    float const aspect = AspectRatio();
	glDrawBuffer(GL_BACK);

	glViewport(0, 0, width, height);
	glClearColor(0.0, 0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projMatrix.m);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_dir);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_dir);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color);

	glLightfv(GL_LIGHT2, GL_POSITION, light2_dir);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_color);


	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    for(int i=0;i<contactpoints.size();i++)
    {
        glBegin(GL_POINT);
        glVertex3f(contactpoints[i].x[0],
                   contactpoints[i].x[1],
                   contactpoints[i].x[2]);
        glEnd();
    }

	glCullFace(GL_BACK);
    glMatrixMode(GL_MODELVIEW);
  
    // then we need to draw all the polygons

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glLoadMatrixf(viewModelMatrix.m);
    glColor4f(1,1,1, 1);
    for(int j=0; j<VAO.size();j++)
    {
        GLnix_glBindVertexArray(VAO[j]);
        glDrawElements(GL_TRIANGLES, VAOIndexCounts[j], GL_UNSIGNED_INT, 0);
    }
    
    glXSwapBuffers(Xdisplay, glX_window_handle);
}

void DEMDriver::setContactPoints(std::vector<demolish::ContactPoint>& cps)
{
    contactpoints = cps;
}

void DEMDriver::BuildBuffers(std::vector<demolish::Object> objects)
{
    for(auto& o:objects)
    {
        if(o.getIsSphere())
            BuildSphereBuffer(o.getRad(),o.getCentre());
    }
}

void DEMDriver::BuildSphereBuffer(float radius,std::array<iREAL,3> position)
{ 

    GeometryGenerator::MeshData meshObj;
    geoGenObjects.push_back(meshObj);
    geoGen.CreateSphere(radius,30,30,meshObj,position);

    VAOIndexCounts.push_back(meshObj.Indices.size());
    VAO.push_back(0);

    GLnix_glGenVertexArrays(1,&VAO.back());
    GLnix_glGenBuffers(2,BUFFERS);
    GLnix_glBindVertexArray(VAO.back()); 

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    GLnix_glBindBuffer(GL_ARRAY_BUFFER,BUFFERS[0]);
    GLnix_glBufferData(GL_ARRAY_BUFFER,
                                  meshObj.Vertices.size()*sizeof(GLfloat)*11,
                                  &meshObj.Vertices.front(), GL_STATIC_DRAW);

    
    GLnix_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BUFFERS[1]);
    GLnix_glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                   meshObj.Indices.size() * sizeof(UINT), 
                                   &meshObj.Indices.front(), GL_STATIC_DRAW);
    
    glVertexPointer(3, GL_FLOAT,sizeof(GLfloat)*11, 0); 
    glNormalPointer(GL_FLOAT,sizeof(GLfloat)*11,(GLvoid*)(3*sizeof(GLfloat)));
}

void DEMDriver::BuildMeshBuffer(demolish::Mesh& mesh)
{
}


void DEMDriver::OnMouseDown(XButtonEvent btn,int x, int y)
{
    mousex = x;
    mousey = y;
    but = btn.button;
}
void DEMDriver::OnMouseUp(XButtonEvent btn,int x, int y)
{

}
void DEMDriver::OnMouseMove(int x, int y)
{
    if(but == 1)
    {
        // Make each pixel correspond to a quarter of a degree.
        float dx = ANTMATHConvertToRadians(0.25f*static_cast<float>(x - mousex));
        float dy = ANTMATHConvertToRadians(0.25f*static_cast<float>(y -mousey));

        // Update angles based on input to orbit camera around box.
        theta += dx;
        phi   += dy;

        // Restrict the angle mPhi.
        phi = MathHelper::Clamp(phi, 0.1f, MathHelper::Pi-0.1f);
        std::cout << "Left Button Pressed" << std::endl;
    }
    else if (but == 3)
    {
        // Make each pixel correspond to 0.2 unit in the scene.
        float dx = 0.2f*static_cast<float>(x - mousex);
        float dy = 0.2f*static_cast<float>(y - mousey);

        // Update the camera radius based on input.
        radius += dx - dy;

        // Restrict the radius.
        radius = MathHelper::Clamp(radius, 1.0f, 200.0f);
        std::cout << "Right Button Pressed" << std::endl;
    }

    else if(but ==2)
    {
        std::cout << "Middle Button Pressed" << std::endl;
    }
    

    mousex = x;
    mousey = y;
}
