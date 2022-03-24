#include "CMeshCreator.h"
#include <yoshix_fix_function.h>


float m_SquareEdgeLength;


CMeshCreator::CMeshCreator()
    : m_SquareEdgeLength(1.0f)
{

};

CMeshCreator::~CMeshCreator()
{

};

void CMeshCreator::CreateFlatLinedTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {    0 * edgeLength,      0 * edgeLength,     0 * edgeLength},
            {   -2 * edgeLength,      0 * edgeLength,     0 * edgeLength},
            {   -2 * edgeLength,     -1 * edgeLength,     0 * edgeLength},
            {    2 * edgeLength,     -1 * edgeLength,     0 * edgeLength},
            {    2 * edgeLength,      0 * edgeLength,     0 * edgeLength},
        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  0,  1,  2, },
            {  0,  2,  3, },
            {  0,  3,  4, },
        };

        float colors[][4] =
        {
            { 0.0f/255.0f, 240.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f/255.0f, 240.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f/255.0f, 240.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 2.
            { 0.0f/255.0f, 240.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 3.
            { 0.0f/255.0f, 240.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 4.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                          
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 5;
        MeshInfo.m_NumberOfIndices = 9;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateSquareTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {    0 * edgeLength,       0 * edgeLength,     0 * edgeLength},
            {   -1 * edgeLength,       0 * edgeLength,     0 * edgeLength},
            {   -1 * edgeLength,      -2 * edgeLength,     0 * edgeLength},
            {    1 * edgeLength,      -2 * edgeLength,     0 * edgeLength},
            {    1 * edgeLength,       0 * edgeLength,     0 * edgeLength},
        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  0,  1,  2, },
            {  0,  2,  3, },
            {  0,  3,  4, },
        };

        float colors[][4] =
        {
            { 250.0f/255.0f, 250.0f/255.0f, 0.0f/255.0f, 1.0f, },        // Color of vertex 0.
            { 250.0f/255.0f, 250.0f/255.0f, 0.0f/255.0f, 1.0f, },        // Color of vertex 1.
            { 250.0f/255.0f, 250.0f/255.0f, 0.0f/255.0f, 1.0f, },        // Color of vertex 2.
            { 250.0f/255.0f, 250.0f/255.0f, 0.0f/255.0f, 1.0f, },        // Color of vertex 3.
            { 250.0f/255.0f, 250.0f/255.0f, 0.0f/255.0f, 1.0f, },        // Color of vertex 3.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                          
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 5;
        MeshInfo.m_NumberOfIndices = 9;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateTShapedTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {     0 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //0
            {    -1 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //1
            {    -1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //2
            {     2 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //3
            {     2 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //4
            {     1 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //5
            {     1 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //6
            {     0 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //7

        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  0,  1,  2, },
            {  0,  2,  3, },

            {  5,  0,  3, },
            {  5,  3,  4, },

            {  6,  7,  0, },
            {  6,  0,  5, },
        };

        float colors[][4] =
        {
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 0.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 1.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 2.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 3.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 4.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 5.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 6.
            { 160.0f/255.0f,  0.0f/255.0f,   240.0f/255.0f, 1.0f, },        // Color of vertex 7.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                         
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 8;
        MeshInfo.m_NumberOfIndices = 18;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateLeftHandedLShapedTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {      0 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //0
            {      0 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //1
            {     -1 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //2
            {     -1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //3
            {      2 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //4
            {      2 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //5
        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  1,  2,  3, },
            {  1,  3,  0, },
            {  0,  3,  5, },
            {  5,  3,  4, },

        };

        float colors[][4] =
        {
            { 0.0f/255.0f, 0.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f/255.0f, 0.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f/255.0f, 0.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 2.
            { 0.0f/255.0f, 0.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 3.
            { 0.0f/255.0f, 0.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 4.
            { 0.0f/255.0f, 0.0f/255.0f, 240.0f/255.0f, 1.0f, },        // Color of vertex 5.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                          
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 6;
        MeshInfo.m_NumberOfIndices = 12;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateRightHandedLShapedTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {       0 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //0
            {      -2 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //1
            {      -2 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //2
            {       1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //3
            {       1 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //4
            {       0 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //5

        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  0,  1,  2, },
            {  0,  2,  3, },
            {  0,  3,  4, },
            {  0,  4,  5, },
        };


        float colors[][4] =
        {
            { 240.0f/255.0f, 160.0f/255.0f, 0.0f/255.0f, 1.0f },        // Color of vertex 0.
            { 240.0f/255.0f, 160.0f/255.0f, 0.0f/255.0f, 1.0f },        // Color of vertex 1.
            { 240.0f/255.0f, 160.0f/255.0f, 0.0f/255.0f, 1.0f },        // Color of vertex 2.
            { 240.0f/255.0f, 160.0f/255.0f, 0.0f/255.0f, 1.0f },        // Color of vertex 3.
            { 240.0f/255.0f, 160.0f/255.0f, 0.0f/255.0f, 1.0f },        // Color of vertex 4.
            { 240.0f/255.0f, 160.0f/255.0f, 0.0f/255.0f, 1.0f },        // Color of vertex 5.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                          
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 6;
        MeshInfo.m_NumberOfIndices = 12;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateLeftHandedZShapedTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {       0 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //0
            {      -1 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //1
            {      -1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //2
            {       1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //3
            {       1 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //4
            {       2 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //5
            {       2 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //6
            {       0 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //7
        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  0,  1,  2, },
            {  0,  2,  3, },
            {  0,  3,  4, },
            {  4,  7,  0, },
            {  4,  6,  7, },
            {  4,  5,  6, },


        };

        float colors[][4] =
        {
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 2.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 3.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 4.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 5.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 6.
            { 0.0f/255.0f,   240.0f/255.0f,  0.0f/255.0f, 1.0f, },        // Color of vertex 7.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                        
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 8;
        MeshInfo.m_NumberOfIndices = 18;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateRightHandedZShapedTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {       0 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //0
            {       0 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //1
            {      -2 * edgeLength,       1 * edgeLength,     0 * edgeLength}, //2
            {      -2 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //3
            {      -1 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //4
            {      -1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //5
            {       1 * edgeLength,      -1 * edgeLength,     0 * edgeLength}, //6
            {       1 * edgeLength,       0 * edgeLength,     0 * edgeLength}, //7
        };

        float normals[][3] =
        {
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
            { 0, 0, -1 },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a Square, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        int indices[][3] =
        {
            {  1,  2,  3, },
            {  1,  3,  4, },
            {  1,  4,  0, },

            {  0,  4,  5, },
            {  0,  5,  6, },
            {  0,  6,  7, },


        };

        float colors[][4] =
        {
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 0.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 1.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 2.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 3.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 4.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 5.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 6.
            { 240.0f/255.0f,  0.0f/255.0f,   0.0f/255.0f, 1.0f, },        // Color of vertex 7.
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices = &vertices[0][0];
        MeshInfo.m_pNormals = &normals[0][0];                          
        MeshInfo.m_pColors = &colors[0][0];
        MeshInfo.m_pTexCoords = nullptr;
        MeshInfo.m_NumberOfVertices = 8;
        MeshInfo.m_NumberOfIndices = 18;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

void CMeshCreator::CreateLeftAndRightLevelBorder(BHandle* _ppMesh)
{
    float edgeLength = m_SquareEdgeLength;
    //x,y,z x=horizontal y=vertical z=depth
    float vertices[][3] =
    {
        {  -50 * edgeLength,     25 * edgeLength,     0 * edgeLength},
        {  -50 * edgeLength,    -45 * edgeLength,     0 * edgeLength},
        {   -5 * edgeLength,    -45 * edgeLength,     0 * edgeLength},
        {   -5 * edgeLength,     25 * edgeLength,     0 * edgeLength},
    };

    float normals[][3] =
    {
        { 0, 0, -1 },
        { 0, 0, -1 },
        { 0, 0, -1 },
        { 0, 0, -1 },
    };

    // -----------------------------------------------------------------------------
    // Define the topology of the mesh via indices. An index addresses a vertex from
    // the array above. Three indices represent one triangle. When defining the 
    // triangles of a mesh imagine that you are standing in front of the triangle 
    // and looking to the center of the triangle. If the mesh represents a closed
    // body such as a Square, your view position has to be outside of the body. Now
    // define the indices of the addressed vertices of the triangle in counter-
    // clockwise order.
    // -----------------------------------------------------------------------------
    int indices[][3] =
    {
        {  3,  0,  1, },
        {  3,  1,  2, },
    };

    float colors[][4] =
    {
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 0.
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 1.
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 2.
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 3.
    };

    // -----------------------------------------------------------------------------
    // Define the mesh and its material. The material defines the look of the
    // surface covering the mesh. If the material should contain normals, colors, or
    // texture coordinates then their number has to match the number of vertices.
    // If you do not support normals in a mesh, YoshiX will not apply lighting to
    // this mesh. A textured mesh always has to contain texture coordinates and a
    // handle to a texture. A mesh always has to contain vertices and indices.
    // -----------------------------------------------------------------------------
    SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &vertices[0][0];
    MeshInfo.m_pNormals = &normals[0][0];                       
    MeshInfo.m_pColors = &colors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 4;
    MeshInfo.m_NumberOfIndices = 6;
    MeshInfo.m_pIndices = &indices[0][0];
    MeshInfo.m_pTexture = nullptr;

    CreateMesh(MeshInfo, _ppMesh);
}

void CMeshCreator::CreateTopAndBottomLevelBorder(BHandle* _ppMesh)
{
    float edgeLength = m_SquareEdgeLength;
    //x,y,z x=horizontal y=vertical z=depth
    float vertices[][3] =
    {
        {  -50 * edgeLength,     25 * edgeLength,     0 * edgeLength},
        {  -50 * edgeLength,      0 * edgeLength,     0 * edgeLength},
        {   50 * edgeLength,      0 * edgeLength,     0 * edgeLength},
        {   50 * edgeLength,     25 * edgeLength,     0 * edgeLength},
    };

    float normals[][3] =
    {
        { 0, 0, -1 },
        { 0, 0, -1 },
        { 0, 0, -1 },
        { 0, 0, -1 },
    };

    // -----------------------------------------------------------------------------
    // Define the topology of the mesh via indices. An index addresses a vertex from
    // the array above. Three indices represent one triangle. When defining the 
    // triangles of a mesh imagine that you are standing in front of the triangle 
    // and looking to the center of the triangle. If the mesh represents a closed
    // body such as a Square, your view position has to be outside of the body. Now
    // define the indices of the addressed vertices of the triangle in counter-
    // clockwise order.
    // -----------------------------------------------------------------------------
    int indices[][3] =
    {
        {  3,  0,  1, },
        {  3,  1,  2, },
    };

    float colors[][4] =
    {
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 0.
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 1.
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 2.
        { 80.0f/255.0f, 80.0f/255.0f, 80.0f/255.0f, 1.0f, },        // Color of vertex 3.
    };

    // -----------------------------------------------------------------------------
    // Define the mesh and its material. The material defines the look of the
    // surface covering the mesh. If the material should contain normals, colors, or
    // texture coordinates then their number has to match the number of vertices.
    // If you do not support normals in a mesh, YoshiX will not apply lighting to
    // this mesh. A textured mesh always has to contain texture coordinates and a
    // handle to a texture. A mesh always has to contain vertices and indices.
    // -----------------------------------------------------------------------------
    SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &vertices[0][0];
    MeshInfo.m_pNormals = &normals[0][0];
    MeshInfo.m_pColors = &colors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 4;
    MeshInfo.m_NumberOfIndices = 6;
    MeshInfo.m_pIndices = &indices[0][0];
    MeshInfo.m_pTexture = nullptr;

    CreateMesh(MeshInfo, _ppMesh);
}

void CMeshCreator::CreateSingleTetrominoCube(BHandle* _ppMesh)
{
    float edgeLength = m_SquareEdgeLength;
    //x,y,z x=horizontal y=vertical z=depth
    float vertices[][3] =
    {
        {    0 * edgeLength,      0 * edgeLength,     0 * edgeLength},
        {    0 * edgeLength,     -1 * edgeLength,     0 * edgeLength},
        {    1 * edgeLength,     -1 * edgeLength,     0 * edgeLength},
        {    1 * edgeLength,      0 * edgeLength,     0 * edgeLength},
    };

    // -----------------------------------------------------------------------------
    // Define the topology of the mesh via indices. An index addresses a vertex from
    // the array above. Three indices represent one triangle. When defining the 
    // triangles of a mesh imagine that you are standing in front of the triangle 
    // and looking to the center of the triangle. If the mesh represents a closed
    // body such as a Square, your view position has to be outside of the body. Now
    // define the indices of the addressed vertices of the triangle in counter-
    // clockwise order.
    // -----------------------------------------------------------------------------
    int indices[][3] =
    {
        {  3,  0,  1, },
        {  3,  1,  2, },
    };

    float colors[][4] =
    {
        { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f, },        // Color of vertex 0.
        { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f, },        // Color of vertex 1.
        { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f, },        // Color of vertex 2.
        { 255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f, },        // Color of vertex 3.
    };

    // -----------------------------------------------------------------------------
    // Define the mesh and its material. The material defines the look of the
    // surface covering the mesh. If the material should contain normals, colors, or
    // texture coordinates then their number has to match the number of vertices.
    // If you do not support normals in a mesh, YoshiX will not apply lighting to
    // this mesh. A textured mesh always has to contain texture coordinates and a
    // handle to a texture. A mesh always has to contain vertices and indices.
    // -----------------------------------------------------------------------------
    SMeshInfo MeshInfo;

    MeshInfo.m_pVertices = &vertices[0][0];
    MeshInfo.m_pNormals = nullptr;                          // No normals
    MeshInfo.m_pColors = &colors[0][0];
    MeshInfo.m_pTexCoords = nullptr;
    MeshInfo.m_NumberOfVertices = 4;
    MeshInfo.m_NumberOfIndices = 6;
    MeshInfo.m_pIndices = &indices[0][0];
    MeshInfo.m_pTexture = nullptr;

    CreateMesh(MeshInfo, _ppMesh);
}
