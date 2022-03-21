#include <iostream>
#include "yoshix_fix_function.h"

using namespace gfx;

namespace
{
    class CApplication : public IApplication
    {
        public:

            CApplication();
            virtual ~CApplication();

        private:

        //own variables
            float m_SquareEdgeLength;
            BHandle m_pFlatLineTetrominoMesh;     
            BHandle m_pSquareTetrominoMesh;     
            BHandle m_pTShapedTetrominoMesh;     
            BHandle m_pLeftHandedLShapedTetrominoMesh;     
            BHandle m_pRightHandedLShapedTetrominoMesh;    
            BHandle m_pLeftHandedZShapedTetrominoMesh;     
            BHandle m_pRightHandedZShapedTetrominoMesh;     

            
        //own functions
            void CreateFlatLinedTetromino(BHandle* _ppMesh);
            void CreateSquareTetromino(BHandle* _ppMesh);
            void CreateTShapedTetromino(BHandle* _ppMesh);
            void CreateLeftHandedLShapedTetromino(BHandle* _ppMesh);
            void CreateRightHandedLShapedTetromino(BHandle* _ppMesh);
            void CreateLeftHandedZShapedTetromino(BHandle* _ppMesh);
            void CreateRightHandedZShapedTetromino(BHandle* _ppMesh);


        //YoshiX-related
            float   m_FieldOfViewY; // Vertical view angle of the camera.
            virtual bool InternOnStartup();
            virtual bool InternOnShutdown();
            virtual bool InternOnCreateMeshes();
            virtual bool InternOnReleaseMeshes();
            virtual bool InternOnResize(int _Width, int _Height);
            virtual bool InternOnUpdate();
            virtual bool InternOnFrame();


    };
} // namespace

namespace
{
    CApplication::CApplication()
        : m_FieldOfViewY        (60.0f)
        , m_pFlatLineTetrominoMesh  (nullptr)
        , m_pSquareTetrominoMesh  (nullptr)
        , m_pTShapedTetrominoMesh  (nullptr)
        , m_pLeftHandedLShapedTetrominoMesh (nullptr)
        , m_pRightHandedLShapedTetrominoMesh (nullptr)
        , m_pLeftHandedZShapedTetrominoMesh (nullptr)
        , m_pRightHandedZShapedTetrominoMesh (nullptr)
        , m_SquareEdgeLength      (1.0f)
    {
    }

    // -----------------------------------------------------------------------------

    CApplication::~CApplication()
    {
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnStartup()
    {
        // -----------------------------------------------------------------------------
        // Define the background color of the window. Colors are always 4D tuples,
        // whereas the components of the tuple represent the red, green, blue, and alpha 
        // channel. The alpha channel indicates the transparency of the color. A value
        // of 1 means the color is completely opaque. A value of 0 means the color is
        // completely transparent. The channels red, green, and blue also are values
        // 0..1 with 0 indicating the minimum intensity and 1 the maximum intensity.
        // -----------------------------------------------------------------------------
        float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f, };

        SetClearColor(ClearColor);
        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnShutdown()
    {
        return true;
    }


    // -----------------------------------------------------------------------------
    
    void CApplication::CreateFlatLinedTetromino(BHandle* _ppMesh)
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
            { 0.0f, 240.0f, 240.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f, 240.0f, 240.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f, 240.0f, 240.0f, 1.0f, },        // Color of vertex 2.
            { 0.0f, 240.0f, 240.0f, 1.0f, },        // Color of vertex 3.
            { 0.0f, 240.0f, 240.0f, 1.0f, },        // Color of vertex 4.
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
        MeshInfo.m_NumberOfVertices = 5;
        MeshInfo.m_NumberOfIndices = 9;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }
    
    // -----------------------------------------------------------------------------

    void CApplication::CreateSquareTetromino(BHandle* _ppMesh)
    {
        float edgeLength = m_SquareEdgeLength;
        //x,y,z x=horizontal y=vertical z=depth
        float vertices[][3] =
        {
            {    0 * edgeLength,       0 * edgeLength,     0 * edgeLength},
            {    0 * edgeLength,      -2 * edgeLength,     0 * edgeLength},
            {    2 * edgeLength,      -2 * edgeLength,     0 * edgeLength},
            {    2 * edgeLength,       0 * edgeLength,     0 * edgeLength},
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
            { 242.0f, 242.0f, 0.0f, 1.0f, },        // Color of vertex 0.
            { 242.0f, 242.0f, 0.0f, 1.0f, },        // Color of vertex 1.
            { 242.0f, 242.0f, 0.0f, 1.0f, },        // Color of vertex 2.
            { 242.0f, 242.0f, 0.0f, 1.0f, },        // Color of vertex 3.
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

    // -----------------------------------------------------------------------------

    void CApplication::CreateTShapedTetromino(BHandle* _ppMesh)
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
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 0.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 1.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 2.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 3.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 4.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 5.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 6.
            { 160.0f,  0.0f,   240.0f, 1.0f, },        // Color of vertex 7.
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
        MeshInfo.m_NumberOfVertices = 8;
        MeshInfo.m_NumberOfIndices = 18;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }
    
    // -----------------------------------------------------------------------------
    
    void CApplication::CreateLeftHandedLShapedTetromino(BHandle* _ppMesh)
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
            { 0.0f, 0.0f, 240.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f, 0.0f, 240.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f, 0.0f, 240.0f, 1.0f, },        // Color of vertex 2.
            { 0.0f, 0.0f, 240.0f, 1.0f, },        // Color of vertex 3.
            { 0.0f, 0.0f, 240.0f, 1.0f, },        // Color of vertex 4.
            { 0.0f, 0.0f, 240.0f, 1.0f, },        // Color of vertex 5.
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
        MeshInfo.m_NumberOfVertices = 6;
        MeshInfo.m_NumberOfIndices = 12;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

    // -----------------------------------------------------------------------------

    void CApplication::CreateRightHandedLShapedTetromino(BHandle* _ppMesh)
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
            { 255.0f, 75.0f, 64.0f, 1.0f, },        // Color of vertex 0.
            { 255.0f, 75.0f, 64.0f, 1.0f, },        // Color of vertex 1.
            { 255.0f, 75.0f, 64.0f, 1.0f, },        // Color of vertex 2.
            { 255.0f, 75.0f, 64.0f, 1.0f, },        // Color of vertex 3.
            { 255.0f, 75.0f, 64.0f, 1.0f, },        // Color of vertex 4.
            { 255.0f, 75.0f, 64.0f, 1.0f, },        // Color of vertex 5.
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
        MeshInfo.m_NumberOfVertices = 6;
        MeshInfo.m_NumberOfIndices = 12;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

    // -----------------------------------------------------------------------------

    void CApplication::CreateLeftHandedZShapedTetromino(BHandle* _ppMesh)
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
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 0.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 1.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 2.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 3.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 4.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 5.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 6.
            { 0.0f,   240.0f,  0.0f, 1.0f, },        // Color of vertex 7.
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
        MeshInfo.m_NumberOfVertices = 8;
        MeshInfo.m_NumberOfIndices = 18;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

    // -----------------------------------------------------------------------------

    void CApplication::CreateRightHandedZShapedTetromino(BHandle* _ppMesh)
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
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 0.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 1.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 2.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 3.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 4.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 5.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 6.
            { 240.0f,  0.0f,   0.0f, 1.0f, },        // Color of vertex 7.
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
        MeshInfo.m_NumberOfVertices = 8;
        MeshInfo.m_NumberOfIndices = 18;
        MeshInfo.m_pIndices = &indices[0][0];
        MeshInfo.m_pTexture = nullptr;

        CreateMesh(MeshInfo, _ppMesh);
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnCreateMeshes()
    {
        CreateFlatLinedTetromino(&m_pFlatLineTetrominoMesh);
        CreateSquareTetromino(&m_pSquareTetrominoMesh);
        CreateTShapedTetromino(&m_pTShapedTetrominoMesh);
        CreateLeftHandedLShapedTetromino(&m_pLeftHandedLShapedTetrominoMesh);
        CreateRightHandedLShapedTetromino(&m_pRightHandedLShapedTetrominoMesh);
        CreateLeftHandedZShapedTetromino(&m_pLeftHandedZShapedTetrominoMesh);
        CreateRightHandedZShapedTetromino(&m_pRightHandedZShapedTetrominoMesh);
        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnReleaseMeshes()
    {
        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnResize(int _Width, int _Height)
    {
        float ProjectionMatrix[16];

        // -----------------------------------------------------------------------------
        // The projection matrix defines the size of the camera frustum. The YoshiX
        // camera has the shape of a pyramid with the eye position at the top of the
        // pyramid. The horizontal view angle is defined by the vertical view angle
        // and the ratio between window width and window height.
        // -----------------------------------------------------------------------------
        GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);

        SetProjectionMatrix(ProjectionMatrix);


        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnUpdate()
    {
        float Eye[3];
        float At[3];
        float Up[3];

        float ViewMatrix[16];

        // -----------------------------------------------------------------------------
        // Define position and orientation of the camera in the world.
        // -----------------------------------------------------------------------------
        Eye[0] = 0.0f; At[0] = 0.0f; Up[0] = 0.0f;
        Eye[1] = 0.0f; At[1] = 0.0f; Up[1] = 1.0f;
        Eye[2] = -20.0f; At[2] = 0.0f; Up[2] = 0.0f;

        GetViewMatrix(Eye, At, Up, ViewMatrix);

        SetViewMatrix(ViewMatrix);


        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnFrame()
    {
        float TranslationMatrix[16];
        float WorldMatrix[16];
        float ScaleMatrix[16];

        // -----------------------------------------------------------------------------
        // Set the position of the mesh in the world and draw it.
        // -----------------------------------------------------------------------------
        GetTranslationMatrix(0.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pLeftHandedLShapedTetrominoMesh);


        GetTranslationMatrix(10.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pRightHandedLShapedTetrominoMesh);

        GetTranslationMatrix(0.0f, 5.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pFlatLineTetrominoMesh);

        GetTranslationMatrix(10.0f, 5.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pSquareTetrominoMesh);

        GetTranslationMatrix(-10.0f, 5.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pLeftHandedZShapedTetrominoMesh);
        
        GetTranslationMatrix(-10.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pRightHandedZShapedTetrominoMesh);

        GetTranslationMatrix(0.0f, -5.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);

        DrawMesh(m_pTShapedTetrominoMesh);

        return true;
    }
} // namespace

void main()
{
    CApplication Application;

    RunApplication(800, 600, "YoshiX Tetris", &Application);
}