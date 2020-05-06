#include "GeometryBuilder.h"

void crashr::CreateBox(double dim1, double dim2, double dim3,
      std::vector<crashr::Vertex>& meshVertices,
      std::vector<std::array<int, 3>>& meshTriangles)
{

      crashr::Vertex A(-0.5*dim1,0.5*dim2,0.5*dim3);
      crashr::Vertex B(-0.5*dim1,0.5*dim2,-0.5*dim3);
      crashr::Vertex C(0.5*dim1,0.5*dim2,-0.5*dim3);
      crashr::Vertex D(0.5*dim1,0.5*dim2,0.5*dim3);
      crashr::Vertex E(-0.5*dim1,-0.5*dim2,0.5*dim3);
      crashr::Vertex F(-0.5*dim1,-0.5*dim2,-0.5*dim3);
      crashr::Vertex G(0.5*dim1,-0.5*dim2,-0.5*dim3);
      crashr::Vertex H(0.5*dim1,-0.5*dim2,0.5*dim3);
      std::array<int,3> tri1 = {0,2,1};
      std::array<int,3> tri2 = {2,0,3};
      std::array<int,3> tri3 = {4,5,6};
      std::array<int,3> tri4 = {4,6,7};
      std::array<int,3> tri5 = {0,1,4};
      std::array<int,3> tri6 = {5,4,1};
      std::array<int,3> tri7 = {1,2,5};
      std::array<int,3> tri8 = {2,6,5};
      std::array<int,3> tri9 = {2,3,6};
      std::array<int,3> tri10 = {7,6,3};
      std::array<int,3> tri11 = {4,7,0};
      std::array<int,3> tri12 = {0,7,3};
      meshVertices.push_back(A);
      meshVertices.push_back(B);
      meshVertices.push_back(C);
      meshVertices.push_back(D);
      meshVertices.push_back(E);
      meshVertices.push_back(F);
      meshVertices.push_back(G);
      meshVertices.push_back(H);
      meshTriangles.push_back(tri1);
      meshTriangles.push_back(tri2);
      meshTriangles.push_back(tri3);
      meshTriangles.push_back(tri4);
      meshTriangles.push_back(tri5);
      meshTriangles.push_back(tri6);
      meshTriangles.push_back(tri7);
      meshTriangles.push_back(tri8);
      meshTriangles.push_back(tri9);
      meshTriangles.push_back(tri10);
      meshTriangles.push_back(tri11);
      meshTriangles.push_back(tri12);
}


void crashr::CreateTrunCone(double topRadius, double bottomRadius,double height,int resolution,
                    std::vector<crashr::Vertex> &meshVertices,
                    std::vector<std::array<int, 3>>& meshTriangles)
{
    // create coordinates of top
    for(int i=0;i<resolution;i++)
        meshVertices.push_back(Vertex(topRadius*cos(2*M_PI*(i*1.0)/resolution),
                                                              height,
                                      topRadius*sin(2*M_PI*(i*1.0)/resolution)));
    // create coordinates of bottom
    for(int i=0;i<resolution;i++)
        meshVertices.push_back(Vertex(bottomRadius*cos(2*M_PI*(i*1.0)/resolution),
                                                              -1*height,
                                      bottomRadius*sin(2*M_PI*(i*1.0)/resolution)));


    std::array<int, 3> tri1,tri2;
    for(int i=0;i<resolution-1;i++)
    {
        tri1 = {i,resolution+i,1+i};
        tri2 = {resolution+i,resolution+i+1,i+1};
        meshTriangles.push_back(tri1);
        meshTriangles.push_back(tri2);
    } 
    
    tri1 = {resolution-1, 2*resolution-1,0};
    tri2 = {2*resolution-1,resolution,0};
    meshTriangles.push_back(tri1);
    meshTriangles.push_back(tri2);
}

void crashr::CreateHopper(double topRadius,
                            double bottomRadius,
                            double height,
                            std::vector<crashr::Vertex>    &meshVertices,
                            std::vector<std::array<int, 3>>  &meshTriangles)
{

   // ***************************
   // CONSTRUCTION OF INNER AND OUTER SHELL
   // ***************************

   // calling CreateTrunCone twice will fill in the meshVertices and meshTriangles.
   // the second time we call this method we should increase the size of the parameters
   // topRadius and bottomRadius so as to give the hopper some thickness.
   int   resolution = 4;
   std::vector<crashr::Vertex> verts1,verts2;
   std::vector<std::array<int, 3>> tris1,tris2;
   CreateTrunCone(topRadius,bottomRadius,height,resolution,verts1,tris1);
   CreateTrunCone(topRadius+2,bottomRadius+2,height,resolution,verts2,tris2);
  
   // concatenate the verts;
   meshVertices.reserve(verts1.size()+verts2.size());
   meshVertices.insert(meshVertices.end(),verts1.begin(),verts1.end());
   meshVertices.insert(meshVertices.end(),verts2.begin(),verts2.end());

   // correct the indices of the outside shell
   for(int i=0;i<2*resolution;i++)
   {
        tris2[i][0] += 2*resolution;
        tris2[i][1] += 2*resolution;
        tris2[i][2] += 2*resolution;
   }

   meshTriangles.reserve(tris1.size()+tris2.size());
   meshTriangles.insert(meshTriangles.end(),tris1.begin(),tris1.end());
   meshTriangles.insert(meshTriangles.end(),tris2.begin(),tris2.end());
   
   // now we must reverse the triangle ordering in the second call of CreateTrunCone.
   for(int i=2*resolution;i<4*resolution;i++)
   {
       auto temp = meshTriangles[i][1];
       meshTriangles[i][1] = meshTriangles[i][2];
       meshTriangles[i][2] = temp;
   }

   // ***************************
   // CONSTRUCTION OF CONNECTING PANELS
   // ***************************

    std::array<int, 3> tri1,tri2;

   for(int i=0;i< resolution-1;i++)
   {
     tri1 = {i,i+1,2*resolution+i+1}; 
     tri2 = {i,2*resolution+i+1,2*resolution+i}; 
     meshTriangles.push_back(tri1);
     meshTriangles.push_back(tri2);
   }

   tri1 = {resolution-1 ,0             ,2*resolution  }; 
   tri2 = {resolution-1 ,2*resolution  ,3*resolution-1};

   meshTriangles.push_back(tri1);
   meshTriangles.push_back(tri2);
   
   for(int i=resolution;i< 2*resolution-1;i++)
   {
     tri1 = {i,2*resolution+i+1,i+1}; 
     tri2 = {i,2*resolution+i,2*resolution+i+1}; 
     meshTriangles.push_back(tri1);
     meshTriangles.push_back(tri2);
   }

   tri1 = {2*resolution-1 , 3*resolution  ,   resolution}; 
   tri2 = {2*resolution-1 , 4*resolution-1, 3*resolution};

   meshTriangles.push_back(tri1);
   meshTriangles.push_back(tri2);

}

