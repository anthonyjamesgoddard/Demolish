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
: GLnixAPP(), phi(1.5f*MathHelper::Pi),theta(1.5f*MathHelper::Pi), radius(100)
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


void DEMDriver::UpdateScene(std::vector<demolish::Object>& objects)
{
	float x = radius*sinf(phi)*cosf(theta);
	float z = radius*sinf(phi)*sinf(theta);
	float y = radius*cosf(phi);


	AV4FLOAT position(x,y,z,1.0);
	
	AV4FLOAT target(0.0,0.0,0.0,0.0);
	AV4FLOAT up(0.0,1.0,0.0,0.0);

	viewModelMatrix = formViewModelMatrix(position,target,up);

    for(int i=0;i<VAODynamic.size();i++)
    {
        // this is going to need to change when the moving objects are
        // no longer all spheres.
        //
        // Also, at the moment we are abusing the order in which they 
        // appear. i.e we KNOW that moving object appear first
        // and so this loop will work.
        //

        geoGen.CreateSphere(objects[i].getRad(),
                            30,
                            30,
                            geoGenObjectsDynamic[i],
                            objects[i].getLocation());

        // this is not necc. I think...
        VAOIndexCountsDynamic[i] = geoGenObjectsDynamic[i].Indices.size();

        GLnix_glBindBuffer(GL_ARRAY_BUFFER, VBODynamic[i].first);
        GLnix_glBufferSubData(GL_ARRAY_BUFFER,
                                0,
                                geoGenObjectsDynamic[i].Vertices.size()*sizeof(GLfloat)*11,
                                &geoGenObjectsDynamic[i].Vertices.front());
    }

    RedrawTheWindow();
    
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
        glColor4f(1,0,1,1);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex3f(contactpoints[i].x[0],
                   contactpoints[i].x[1],
                   contactpoints[i].x[2]);
        glEnd();
    }

	glCullFace(GL_BACK);
    glMatrixMode(GL_MODELVIEW);
  
    // then we need to draw all the polygons

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glLoadMatrixf(viewModelMatrix.m);
    glColor4f(1,1,1, 1);

    for(int j=0; j<VAODynamic.size();j++)
    {
        GLnix_glBindVertexArray(VAODynamic[j]);
        glDrawElements(GL_TRIANGLES, VAOIndexCountsDynamic[j], GL_UNSIGNED_INT, 0);
    }
    for(int j=0; j<VAOStatic.size();j++)
    {
        GLnix_glBindVertexArray(VAOStatic[j]);
        glDrawElements(GL_TRIANGLES, VAOIndexCountsStatic[j], GL_UNSIGNED_INT, 0);
    }
     
    glXSwapBuffers(Xdisplay, glX_window_handle);
}

void DEMDriver::setContactPoints(std::vector<demolish::ContactPoint>& cps)
{
    contactpoints = cps;
}

void DEMDriver::BuildBuffers(std::vector<demolish::Object>& objects)
{
    staticCount = 0; dynamicCount=0;
    for(auto& o:objects)
    {
        if(o.getIsSphere())
        {
            if(o.getIsObstacle())
            {
                BuildStaticSphereBuffer(o.getRad(),o.getLocation(),staticCount);
                staticCount++;
            }
            else
            {
                BuildDynamicSphereBuffer(o.getRad(),o.getLocation(),dynamicCount);
                dynamicCount++;
            }
        }
        else
        {
            if(o.getIsObstacle())
            {
                BuildStaticMeshBuffer(o.getMesh());
                staticCount++;
            }
            else
            {

            }
        }
    }
}

void DEMDriver::BuildDynamicSphereBuffer(float radius,std::array<iREAL,3> position,int counter)
{ 
    VAODynamic.push_back(0);
    GLnix_glGenVertexArrays(1,&VAODynamic.back());
    GeometryGenerator::MeshData meshObj;
    geoGenObjectsDynamic.push_back(meshObj);
    geoGen.CreateSphere(radius,30,30,meshObj,position);
   
    UINT BUFFERS[2];

    VAOIndexCountsDynamic.push_back(meshObj.Indices.size());
    GLnix_glGenBuffers(2,BUFFERS);
    GLnix_glBindVertexArray(VAODynamic.back()); 

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

    VBODynamic.push_back(std::make_pair(BUFFERS[0],BUFFERS[1]));
}

void DEMDriver::BuildStaticSphereBuffer(float radius,std::array<iREAL,3> position,int counter)
{ 
    VAOStatic.push_back(0);
    GLnix_glGenVertexArrays(1,&VAOStatic.back());
    GeometryGenerator::MeshData meshObj;
    geoGenObjectsStatic.push_back(meshObj);
    geoGen.CreateSphere(radius,30,30,meshObj,position);
   
    UINT BUFFERS[2];

    VAOIndexCountsStatic.push_back(meshObj.Indices.size());
    GLnix_glGenBuffers(2,BUFFERS);
    GLnix_glBindVertexArray(VAOStatic.back()); 

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

    VBOStatic.push_back(std::make_pair(BUFFERS[0],BUFFERS[1]));
}
void DEMDriver::BuildStaticMeshBuffer(demolish::Mesh* mesh)
{
    VAOStatic.push_back(0);
    GLnix_glGenVertexArrays(1,&VAOStatic.back());
    GeometryGenerator::MeshData geoGenMesh;
    geoGen.CreateMeshFromMesh(mesh,geoGenMesh);
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
    }

    else if(but ==2)
    {

    }
    

    mousex = x;
    mousey = y;
}
