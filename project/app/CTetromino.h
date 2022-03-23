#pragma once
#include <yoshix_fix_function.h>
#include "CPoint.h"

using namespace gfx;

class CTetromino
{
public:
    enum ETetrominoShape {
        FLATLINED,
        SQUARE,
        T_SHAPED,
        LEFT_HANDED_L_SHAPE,
        RIGHT_HANDED_L_SHAPE,
        LEFT_HANDED_Z_SHAPE,
        RIGHT_HANDED_Z_SHAPE,
    };

    enum EMoveDirection {
        LEFT,
        RIGHT,
        DOWN
    };
    CTetromino();

    CTetromino(
        ETetrominoShape _shape,
        CPoint _middlePoint1,
        CPoint _middlePoint2,
        CPoint _middlePoint3,
        CPoint _middlePoint4,
        float _distanceMiddleToLeftMostX, 
        float _distanceMiddleToRightMostX,
        float _distanceMiddleToHighestY,
        float _distanceMiddleToLowestY
    );
    ~CTetromino();


    bool m_isCurrentActiveTetromino;
    ETetrominoShape m_shape;
    
private:

    CPoint m_middlePoint1;
    CPoint m_middlePoint2;
    CPoint m_middlePoint3;
    CPoint m_middlePoint4;
    float m_middlePointX;
    float m_middlePointY;
    float m_distanceMiddleToLeftMostX;
    float m_distanceMiddleToRightMostX;
    float m_distanceMiddleToHighestY;
    float m_distanceMiddleToLowestY;
    float m_squareEdgeLength;
    float m_zRotation;

public:
    float GetLeftMostX();
    float GetRightMostX();
    float GetHighestY();
    float GetLowestY();
    float GetMiddleX();
    float GetMiddleY();
    float GetRotationZ();
    float GetDistanceMiddleToLeftMostX();
    float GetDistanceMiddleToRightMostX();
    float GetDistanceMiddleToHighestY();
    float GetDistanceMiddleToLowestY();

    void SetMiddleX(float _middleX);
    void SetMiddleY(float _middleY);
    void RotateTetromino(bool _rotateClockwise);
    void MoveTetromino(EMoveDirection _direction);
    void GetMiddlePoints(CPoint* _pMiddlePoints); 
    void RotateMiddlePointsAroundZAxis(float _degrees);


};

