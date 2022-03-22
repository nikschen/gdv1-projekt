#include <iostream>
#include "yoshix_fix_function.h"
#include "../project/app/CTetromino.h"
#include "../project/app/CMeshCreator.h"

using namespace gfx;
const int ESC = 27;

namespace
{
    class CApplication : public IApplication
    {
        public:

            CApplication();
            virtual ~CApplication();

        private:

        //-----------------------------------------------------------------------------
        // own variables
        //-----------------------------------------------------------------------------

            //Meshes
            BHandle m_pLeftAndRightLevelBorderMesh;     
            BHandle m_pTopAndBottomLevelBorderMesh;     
            BHandle m_pFlatLineTetrominoMesh;     
            BHandle m_pSquareTetrominoMesh;     
            BHandle m_pTShapedTetrominoMesh;     
            BHandle m_pLeftHandedLShapedTetrominoMesh;     
            BHandle m_pRightHandedLShapedTetrominoMesh;    
            BHandle m_pLeftHandedZShapedTetrominoMesh;     
            BHandle m_pRightHandedZShapedTetrominoMesh;
            BHandle m_pActiveTetrominoMesh;

            //Gameobjects
            CTetromino* m_activeTetromino;
            
            //Helper variables
            time_t m_lastTimeStemp;
            time_t m_tickLength; //in ms; determines game speed
            
        //-----------------------------------------------------------------------------
        // own functions
        //-----------------------------------------------------------------------------
           
            //Logic
            void ChooseRandomTetromino();
            void SpawnTetromino(CTetromino::ETetrominoShape _tetrominoShape);
            void DrawLevelBorders();

        //-----------------------------------------------------------------------------
        // YoshiX-related variables
        //-----------------------------------------------------------------------------
            float   m_FieldOfViewY; // Vertical view angle of the camera.


        //-----------------------------------------------------------------------------
        // YoshiX-related functions
        //-----------------------------------------------------------------------------
            virtual bool InternOnStartup();
            virtual bool InternOnShutdown();
            virtual bool InternOnCreateMeshes();
            virtual bool InternOnReleaseMeshes();
            virtual bool InternOnResize(int _Width, int _Height);
            virtual bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
            virtual bool InternOnUpdate();
            virtual bool InternOnFrame();


    };
} // namespace

namespace
{
#pragma region application_startUp 

    CApplication::CApplication()
    :m_pLeftAndRightLevelBorderMesh     (nullptr)
    ,m_pTopAndBottomLevelBorderMesh     (nullptr)
    ,m_pFlatLineTetrominoMesh           (nullptr)
    ,m_pSquareTetrominoMesh             (nullptr)
    ,m_pTShapedTetrominoMesh            (nullptr)
    ,m_pLeftHandedLShapedTetrominoMesh  (nullptr)
    ,m_pRightHandedLShapedTetrominoMesh (nullptr)
    ,m_pLeftHandedZShapedTetrominoMesh  (nullptr)
    ,m_pRightHandedZShapedTetrominoMesh (nullptr)
    ,m_activeTetromino                  (nullptr)
    ,m_pActiveTetrominoMesh             (nullptr)
    ,m_lastTimeStemp                    (0)
    ,m_tickLength                       (500)
    ,m_FieldOfViewY                     (60.0f)
    {
    }


    CApplication::~CApplication()
    {
    }

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

    bool CApplication::InternOnShutdown()
    {
        return true;
    }
    
#pragma endregion

#pragma region meshCreation

    bool CApplication::InternOnCreateMeshes()
    {
        CMeshCreator meshCreator = CMeshCreator();
        meshCreator.CreateFlatLinedTetromino(&m_pFlatLineTetrominoMesh);
        meshCreator.CreateSquareTetromino(&m_pSquareTetrominoMesh);
        meshCreator.CreateTShapedTetromino(&m_pTShapedTetrominoMesh);
        meshCreator.CreateLeftHandedLShapedTetromino(&m_pLeftHandedLShapedTetrominoMesh);
        meshCreator.CreateRightHandedLShapedTetromino(&m_pRightHandedLShapedTetrominoMesh);
        meshCreator.CreateLeftHandedZShapedTetromino(&m_pLeftHandedZShapedTetrominoMesh);
        meshCreator.CreateRightHandedZShapedTetromino(&m_pRightHandedZShapedTetrominoMesh);
        meshCreator.CreateLeftAndRightLevelBorder(&m_pLeftAndRightLevelBorderMesh);
        meshCreator.CreateTopAndBottomLevelBorder(&m_pTopAndBottomLevelBorderMesh);
        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnReleaseMeshes()
    {
        ReleaseMesh(m_pFlatLineTetrominoMesh);
        ReleaseMesh(m_pSquareTetrominoMesh);
        ReleaseMesh(m_pTShapedTetrominoMesh);
        ReleaseMesh(m_pLeftHandedLShapedTetrominoMesh);
        ReleaseMesh(m_pRightHandedLShapedTetrominoMesh);
        ReleaseMesh(m_pLeftHandedZShapedTetrominoMesh);
        ReleaseMesh(m_pRightHandedZShapedTetrominoMesh);
        ReleaseMesh(m_pLeftAndRightLevelBorderMesh);
        ReleaseMesh(m_pTopAndBottomLevelBorderMesh);
        return true;
    }

#pragma endregion

#pragma region gameLogic
    void CApplication::ChooseRandomTetromino()
    {
        //zahl zwischen 0 und 6
        std::srand(std::time(nullptr));
        int randomNmb = std::rand() % 7;
        SpawnTetromino(CTetromino::ETetrominoShape(randomNmb));
    }

    void CApplication::SpawnTetromino(CTetromino::ETetrominoShape _tetrominoShape)
    {

        switch (_tetrominoShape)
        {
            case CTetromino::ETetrominoShape::FLATLINED:
                m_activeTetromino = &CTetromino(_tetrominoShape, 2.0f, 2.0f, 0.0f,1.0f);
                m_pActiveTetrominoMesh = m_pFlatLineTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::SQUARE:
                m_activeTetromino = &CTetromino(_tetrominoShape, 0.0f, 2.0f, 0.0f, 2.0f);
                m_pActiveTetrominoMesh = m_pSquareTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::T_SHAPED:
                m_activeTetromino = &CTetromino(_tetrominoShape, 1.0f, 2.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pTShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::LEFT_HANDED_L_SHAPE:
                m_activeTetromino = &CTetromino(_tetrominoShape, 1.0f, 2.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pLeftHandedLShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::RIGHT_HANDED_L_SHAPE:
                m_activeTetromino = &CTetromino(_tetrominoShape, 2.0f, 1.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pRightHandedLShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::LEFT_HANDED_Z_SHAPE:
                m_activeTetromino = &CTetromino(_tetrominoShape, 1.0f, 2.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pLeftHandedZShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::RIGHT_HANDED_Z_SHAPE:
                m_activeTetromino = &CTetromino(_tetrominoShape, 2.0f, 1.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pRightHandedZShapedTetrominoMesh;
                break;
        };

    }

    void CApplication::DrawLevelBorders()
    {
        float WorldMatrix[16];
        GetTranslationMatrix(0.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        //Left Border
        DrawMesh(m_pLeftAndRightLevelBorderMesh);
        
        //Top Border
        DrawMesh(m_pTopAndBottomLevelBorderMesh); 

        //Right Border
        GetTranslationMatrix(55.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        DrawMesh(m_pLeftAndRightLevelBorderMesh);
        
        //Bottom Border
        GetTranslationMatrix(0.0f, -45.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        DrawMesh(m_pTopAndBottomLevelBorderMesh);

    }

    bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
    {
        switch (_Key)
        {
            case 'A':
                m_activeTetromino->MoveTetromino(CTetromino::EMoveDirection::LEFT);
                break;
            case 'D':
                m_activeTetromino->MoveTetromino(CTetromino::EMoveDirection::RIGHT);
                break;
            case 'E':
                m_activeTetromino->RotateTetromino(true);
                break;
            case 'Q':
                m_activeTetromino->RotateTetromino(false);
                break;
            case ESC: //ESC key -> Nr 27
                StopApplication();
                break;    
        }


        return true;
    }
#pragma endregion

#pragma region doPerFrame
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
        Eye[1] = -10.0f; At[1] = -10.0f; Up[1] = 1.0f;
        Eye[2] = -18.0f; At[2] = 0.0f; Up[2] = 0.0f;

        GetViewMatrix(Eye, At, Up, ViewMatrix);

        SetViewMatrix(ViewMatrix);


        return true;
    }


    bool CApplication::InternOnFrame()
    {
        float WorldMatrix[16];
        float RotationMatrix[16];
        float TranslationMatrix[16];

        DrawLevelBorders();
        
        // -----------------------------------------------------------------------------
        // Set the position of the mesh in the world and draw it.
        // -----------------------------------------------------------------------------
        if (m_activeTetromino==nullptr)
        {
            ChooseRandomTetromino();
            m_lastTimeStemp = (time_t)time(0);
        }
        else
        {
            time_t timeDifference=((time_t)time(0)- m_lastTimeStemp)*1000;
            if (timeDifference >= m_tickLength)
            {
                m_lastTimeStemp = (time_t)time(0);
                std::cout << "Vor Move" << roundf(m_activeTetromino->GetMiddleY()) << std::endl;
                m_activeTetromino->MoveTetromino(CTetromino::EMoveDirection::DOWN);
                std::cout << "Nach Move" << roundf(m_activeTetromino->GetMiddleY()) << std::endl;
                //CheckForCollisions();
            }
                
            
           
        }
        GetRotationZMatrix(m_activeTetromino->GetRotationZ(),RotationMatrix);
        GetTranslationMatrix(m_activeTetromino->GetMiddleX(), m_activeTetromino->GetMiddleY(), 0.0f, TranslationMatrix);
        MulMatrix(RotationMatrix, TranslationMatrix, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        
        DrawMesh(m_pActiveTetrominoMesh);

        return true;
    }

#pragma endregion

} // namespace

void main()
{
    CApplication Application;

    RunApplication(600, 800, "YoshiX Tetris", &Application);
}