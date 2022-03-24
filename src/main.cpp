#include <algorithm>
#include <iostream>
#include "yoshix_fix_function.h"
#include "../project/app/CFieldOfArea.h"
#include "../project/app/CTetromino.h"
#include "../project/app/CMeshCreator.h"

using namespace gfx;
const int ESC = 27;
const int ARROW_KEY_LEFT = 37;
const int ARROW_KEY_RIGHT = 39;
const int ARROW_KEY_DOWN = 40;

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
            BHandle m_pSingleTetrominoCubeMesh;

            //Textures
            BHandle m_pWelcomeScreenTexture;
            BHandle m_pGameOverScreenTexture;

            //Gameobjects
            CTetromino* m_pActiveTetromino;
            bool m_area[20][10]; //true if occupied, false if not occupied
            float m_leftBorderX;
            float m_rightBorderX;
            float m_bottomBorderY;
            

            //Helper variables
            time_t m_lastTimeStemp;
            time_t m_gameTickLength; //in ms; determines game speed
            bool m_gameOver; 
            
        //-----------------------------------------------------------------------------
        // own functions
        //-----------------------------------------------------------------------------
           
            //Logic
            void CheckForCollisions();
            void CheckForGameOver();
            void ChooseRandomTetromino();
            void RemoveFullRows();

            //Graphics
            void DrawLevelBorders();
            void DrawOccupationBlocks();
            void SpawnTetromino(CTetromino::ETetrominoShape _tetrominoShape);
            void TurnIntoPieces();

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
            virtual bool InternOnCreateTextures();
            virtual bool InternOnReleaseTextures();
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
    : m_pLeftAndRightLevelBorderMesh     (nullptr)
    , m_pTopAndBottomLevelBorderMesh     (nullptr)
    , m_pFlatLineTetrominoMesh           (nullptr)
    , m_pSquareTetrominoMesh             (nullptr)
    , m_pTShapedTetrominoMesh            (nullptr)
    , m_pLeftHandedLShapedTetrominoMesh  (nullptr)
    , m_pRightHandedLShapedTetrominoMesh (nullptr)
    , m_pLeftHandedZShapedTetrominoMesh  (nullptr)
    , m_pRightHandedZShapedTetrominoMesh (nullptr)
    , m_pActiveTetromino                 (nullptr)
    , m_area                             {false}
    , m_pActiveTetrominoMesh             (nullptr)
    , m_pSingleTetrominoCubeMesh         (nullptr)
    , m_leftBorderX                      (0)
    , m_rightBorderX                     (10)
    , m_bottomBorderY                    (-20)
    , m_lastTimeStemp                    (0)
    , m_gameTickLength                   (500)
    , m_gameOver                         (false)
    , m_FieldOfViewY                     (60)
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

        // -----------------------------------------------------------------------------
        // Define the position of the light source in 3D space. The fixed function 
        // pipeline of YoshiX only supports one light source.
        // -----------------------------------------------------------------------------
        float LightPosition[3] = { 5.0f, -10.0f, -20.0f, };

        SetLightPosition(LightPosition);

        // -----------------------------------------------------------------------------
        // Define the ambient, diffuse, and specular color of the light source. 
        // -----------------------------------------------------------------------------
        float LightAmbientColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f, };
        float LightDiffuseColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f, };
        float LightSpecularColor[4] = { 0.9f, 0.9f, 0.9f, 1.0f, };

        SetLightColor(LightAmbientColor, LightDiffuseColor, LightSpecularColor, 5);

        return true;
    }

    bool CApplication::InternOnShutdown()
    {
        return true;
    }
    
#pragma endregion

#pragma region meshAndTextureCreation

    bool CApplication::InternOnCreateTextures()
    {
        // -----------------------------------------------------------------------------
        // Load an image from the given path and create a YoshiX texture representing
        // the image.
        // -----------------------------------------------------------------------------
        //CreateTexture("..\\data\\images\\welcome_screen.dds", &m_pWelcomeScreenTexture);
        //CreateTexture("..\\data\\images\\game_over_screen.dds", &m_pGameOverScreenTexture);

        return true;
    }

    bool CApplication::InternOnReleaseTextures()
    {
        // -----------------------------------------------------------------------------
        // Important to release the texture again when the application is shut down.
        // -----------------------------------------------------------------------------
        //ReleaseTexture(m_pWelcomeScreenTexture);
        //ReleaseTexture(m_pGameOverScreenTexture);

        return true;
    }

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
        meshCreator.CreateSingleTetrominoCube(&m_pSingleTetrominoCubeMesh);
        return true;
    }

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
        ReleaseMesh(m_pSingleTetrominoCubeMesh);
        return true;
    }

#pragma endregion

#pragma region gameLogic
    void CApplication::CheckForCollisions()
    {
        if (m_pActiveTetromino->GetLeftMostX() < m_leftBorderX)
        {
            float currentMiddleX = m_pActiveTetromino->GetMiddleX();
            float distanceMiddleToLeftMostX = m_pActiveTetromino->GetDistanceMiddleToLeftMostX();
            float distanceBorderToMiddleX = m_leftBorderX - currentMiddleX;
            float distanceToBeMoved = distanceMiddleToLeftMostX - abs(distanceBorderToMiddleX);
            m_pActiveTetromino->SetMiddleX(currentMiddleX+distanceToBeMoved);
        }
        if (m_pActiveTetromino->GetRightMostX() > m_rightBorderX)
        {
            float currentMiddleX = m_pActiveTetromino->GetMiddleX();
            float distanceMiddleToRightMostX = m_pActiveTetromino->GetDistanceMiddleToRightMostX();
            float distanceBorderToMiddleX = m_rightBorderX - currentMiddleX;
            float distanceToBeMoved = distanceMiddleToRightMostX - abs(distanceBorderToMiddleX);
            m_pActiveTetromino->SetMiddleX(currentMiddleX - distanceToBeMoved);
        }
        if (m_pActiveTetromino->GetLowestY() < m_bottomBorderY)
        {
            TurnIntoPieces();
            m_pActiveTetromino = nullptr;
        }

        if (m_pActiveTetromino != nullptr)
        {
            CPoint middlePoints[4];
            m_pActiveTetromino->GetMiddlePoints(middlePoints); //gets middlePoints described from a tetrominos middlePoint as the starting point
            for (CPoint point : middlePoints)
            {
                int rowOfArea = abs((int)(m_pActiveTetromino->GetMiddleY() + point.m_y));
                int columnOfArea =  (int)(m_pActiveTetromino->GetMiddleX() + point.m_x);
                if (m_area[rowOfArea][columnOfArea])
                {
                    TurnIntoPieces();
                    m_pActiveTetromino = nullptr;
                    break;
                }
            }
        }


    }

    void CApplication::CheckForGameOver()
    {
        if (m_area[0][3] || m_area[0][4] || m_area[0][5] || m_area[0][6]) m_gameOver = true;
        
    }

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
                m_pActiveTetromino= new CTetromino(_tetrominoShape, CPoint(-1.5,-0.5), CPoint(-0.5,-0.5), CPoint(0.5,-0.5), CPoint(1.5,-0.5), 2.0f, 2.0f, 0.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pFlatLineTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::SQUARE:
                m_pActiveTetromino = new CTetromino(_tetrominoShape, CPoint(-0.5,-0.5), CPoint(0.5,-0.5), CPoint(-0.5,-1.5), CPoint(0.5,-1.5), 1.0f, 1.0f, 0.0f, 2.0f);
                m_pActiveTetrominoMesh = m_pSquareTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::T_SHAPED:
                m_pActiveTetromino = new CTetromino(_tetrominoShape, CPoint(-0.5,-0.5), CPoint(0.5,-0.5), CPoint(1.5,-0.5), CPoint(0.5,0.5), 1.0f, 2.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pTShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::LEFT_HANDED_L_SHAPE:
                m_pActiveTetromino = new CTetromino(_tetrominoShape, CPoint(-0.5,0.5), CPoint(-0.5,-0.5), CPoint(0.5,-0.5), CPoint(1.5,-0.5), 1.0f, 2.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pLeftHandedLShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::RIGHT_HANDED_L_SHAPE:
                m_pActiveTetromino = new CTetromino(_tetrominoShape, CPoint(-1.5,-0.5), CPoint(-0.5,-0.5), CPoint(0.5,-0.5), CPoint(0.5,0.5), 2.0f, 1.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pRightHandedLShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::LEFT_HANDED_Z_SHAPE:
                m_pActiveTetromino = new CTetromino(_tetrominoShape, CPoint(-0.5,-0.5), CPoint(0.5,-0.5), CPoint(0.5,0.5), CPoint(1.5,0.5), 1.0f, 2.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pLeftHandedZShapedTetrominoMesh;
                break;
            case CTetromino::ETetrominoShape::RIGHT_HANDED_Z_SHAPE:
                m_pActiveTetromino = new CTetromino(_tetrominoShape, CPoint(-1.5,0.5), CPoint(-0.5,0.5), CPoint(-0.5,-0.5), CPoint(0.5,-0.5), 2.0f, 1.0f, 1.0f, 1.0f);
                m_pActiveTetrominoMesh = m_pRightHandedZShapedTetrominoMesh;
                break;
        };
    }

    void CApplication::TurnIntoPieces()
    {
         CPoint middlePoints[4];
        m_pActiveTetromino->GetMiddlePoints(middlePoints); //gets middlePoints described from a tetrominos middlePoint as the starting point
        for (CPoint point : middlePoints)
        {
            int rowOfArea = abs((int)(m_pActiveTetromino->GetMiddleY() + 1 + point.m_y));
            int columnOfArea =(int)(m_pActiveTetromino->GetMiddleX() + point.m_x);
            m_area[rowOfArea][columnOfArea] = true;
        }
    }

    void CApplication::DrawLevelBorders()
    {
        float WorldMatrix[16];
        GetTranslationMatrix(5.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        //Left Border
        DrawMesh(m_pLeftAndRightLevelBorderMesh);
        
        //Top Border
        DrawMesh(m_pTopAndBottomLevelBorderMesh); 

        //Right Border
        GetTranslationMatrix(60.0f, 0.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        DrawMesh(m_pLeftAndRightLevelBorderMesh);
        
        //Bottom Border
        GetTranslationMatrix(5.0f, -45.0f, 0.0f, WorldMatrix);
        SetWorldMatrix(WorldMatrix);
        DrawMesh(m_pTopAndBottomLevelBorderMesh);

    }

    void CApplication::DrawOccupationBlocks()
    {
        float translationMatrix[16];
        int row, column = 0;
        for (row = 0; row < 20; row++)
        {
            for (column = 0; column < 10; column++)
            {
                if (m_area[row][column])
                {
                    GetTranslationMatrix(column, -row, 0, translationMatrix);
                    SetWorldMatrix(translationMatrix);
                    DrawMesh(m_pSingleTetrominoCubeMesh);
                }
            }
        }
    }

    void CApplication::RemoveFullRows()
    {
        int row, column;
        for (row = 19; row >= 0; row--)
        {
            int occupiedFields = 0;
            for (column = 0; column < 10; column++)
            {
                if (m_area[row][column]) occupiedFields++;
                else break;
            }

            if (occupiedFields == 10)
            {
                //move all rows until lowest rowToBeRemoved except first row (idx 0)
                for (int rowToBeRemoved = row, idxOfRowTeBeMovedDown = rowToBeRemoved - 1; idxOfRowTeBeMovedDown >= 0; rowToBeRemoved--, idxOfRowTeBeMovedDown--)
                {
                    for (int columnToBeCopied = 0; columnToBeCopied < 10; columnToBeCopied++)
                    {
                        m_area[rowToBeRemoved][columnToBeCopied] = m_area[idxOfRowTeBeMovedDown][columnToBeCopied];

                    }
                }

                //reset first row to false after moving all rows
                for (int columnToBeCopied = 0; columnToBeCopied < 10; columnToBeCopied++)
                {
                    m_area[0][columnToBeCopied] = false;
                }
            }

        }
    }

    bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
    {
        if (_IsKeyDown && (m_pActiveTetromino!=nullptr || _Key==ESC))
        {
            switch (_Key)
            {
                case 'A': //move Tetromino to the left
                case ARROW_KEY_LEFT: //move Tetromino to the left
                    m_pActiveTetromino->MoveTetromino(CTetromino::EMoveDirection::LEFT);
                    break;
                case 'D': //move Tetromino to the right
                case ARROW_KEY_RIGHT: //move Tetromino to the right
                    m_pActiveTetromino->MoveTetromino(CTetromino::EMoveDirection::RIGHT);
                    break;
                case 'E': //rotate Tetromino clockwise
                    m_pActiveTetromino->RotateTetromino(true);
                    break;
                case 'Q': //rotate Tetromino counter-clockwise
                    m_pActiveTetromino->RotateTetromino(false);
                    break;
                case ' ': //force Tetromino down
                case 'S': //force Tetromino down
                case ARROW_KEY_DOWN: //force Tetromino down
                    m_pActiveTetromino->MoveTetromino(CTetromino::EMoveDirection::DOWN);
                    break;
                case 'R': //Reset Game
                    std::fill(&m_area[0][0], &m_area[0][0] + sizeof(m_area), false);
                    m_pActiveTetromino=nullptr;
                    m_gameOver = false;
                    break;
                case ESC: //ESC key -> Nr 27
                    StopApplication();
                    break;    
            }
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
        Eye[0] = 5.0f; At[0] = 5.0f; Up[0] = 0.0f;
        Eye[1] = -10.0f; At[1] = -10.0f; Up[1] = 1.0f;
        Eye[2] = -18.0f; At[2] = 0.0f; Up[2] = 0.0f;

        GetViewMatrix(Eye, At, Up, ViewMatrix);

        SetViewMatrix(ViewMatrix);


        return true;
    }


    bool CApplication::InternOnFrame()
    {
        
        if (!m_gameOver)
        {
            float WorldMatrix[16];
            float RotationMatrix[16];
            float TranslationMatrix[16];

            DrawLevelBorders();

            if (m_pActiveTetromino == nullptr)
            {
                ChooseRandomTetromino();
                m_lastTimeStemp = (time_t)time(0);
            }
            else
            {
                time_t timeDifference = ((time_t)time(0) - m_lastTimeStemp) * 1000;
                if (timeDifference >= m_gameTickLength)
                {
                    m_lastTimeStemp = (time_t)time(0);
                    m_pActiveTetromino->MoveTetromino(CTetromino::EMoveDirection::DOWN);
                }
            }

            CheckForCollisions();

            if (m_pActiveTetromino != nullptr)
            {
                GetRotationZMatrix(m_pActiveTetromino->GetRotationZ(), RotationMatrix);
                GetTranslationMatrix(m_pActiveTetromino->GetMiddleX(), m_pActiveTetromino->GetMiddleY(), 0.0f, TranslationMatrix);
                MulMatrix(RotationMatrix, TranslationMatrix, WorldMatrix);
                SetWorldMatrix(WorldMatrix);
                DrawMesh(m_pActiveTetrominoMesh);
            }
            RemoveFullRows();
            DrawOccupationBlocks();
            CheckForGameOver();
        }
        else
        {
            
            std::cout << "Game Over" << std::endl;
            system("pause");
        }
        
        return true;
    }

#pragma endregion

} // namespace

void main()
{
    CApplication Application;

    RunApplication(800, 800, "YoshiX Tetris", &Application);
}