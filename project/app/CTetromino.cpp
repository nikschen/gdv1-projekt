#include "CTetromino.h"
#include <iostream>
#include <utility>
#include <corecrt_math_defines.h>

CTetromino::CTetromino()
{

};

CTetromino::CTetromino(ETetrominoShape _shape, CPoint _middlePoint1, CPoint _middlePoint2, CPoint _middlePoint3, CPoint _middlePoint4, float _distanceMiddleToLeftMostX, float _distanceMiddleToRightMostX, float _distanceMiddleToHighestY, float _distanceMiddleToLowestY)
    : m_isCurrentActiveTetromino    (true)
    , m_middlePoint1                (_middlePoint1)
    , m_middlePoint2                (_middlePoint2)
    , m_middlePoint3                (_middlePoint3)
    , m_middlePoint4                (_middlePoint4)
    , m_shape                       (_shape)
    , m_middlePointX                (5)
    , m_middlePointY                (0)
    , m_distanceMiddleToLeftMostX   (_distanceMiddleToLeftMostX)
    , m_distanceMiddleToRightMostX  (_distanceMiddleToRightMostX)
    , m_distanceMiddleToHighestY    (_distanceMiddleToHighestY)
    , m_distanceMiddleToLowestY     (_distanceMiddleToLowestY)
    , m_squareEdgeLength            (1)
    , m_zRotation                   (0)
{
}

CTetromino::~CTetromino()
{
}

float CTetromino::GetLeftMostX()
{

    return m_middlePointX-m_distanceMiddleToLeftMostX;
}

float CTetromino::GetRightMostX()
{
    return m_middlePointX+m_distanceMiddleToRightMostX;
}

float CTetromino::GetHighestY()
{
    return m_middlePointY + m_distanceMiddleToHighestY;
}

float CTetromino::GetLowestY()
{
    return m_middlePointY-m_distanceMiddleToLowestY;
}

float CTetromino::GetMiddleX()
{
    return m_middlePointX;
}

float CTetromino::GetMiddleY()
{
    return m_middlePointY;
}

float CTetromino::GetRotationZ()
{
    return m_zRotation;
}

float CTetromino::GetDistanceMiddleToLeftMostX()
{
    return m_distanceMiddleToLeftMostX;
}

float CTetromino::GetDistanceMiddleToRightMostX()
{
    return m_distanceMiddleToRightMostX;
}

float CTetromino::GetDistanceMiddleToHighestY()
{
    return m_distanceMiddleToHighestY;
}

float CTetromino::GetDistanceMiddleToLowestY()
{
    return m_distanceMiddleToLowestY;
}

void CTetromino::SetMiddleX(float _middleX)
{
    m_middlePointX=_middleX;
}

void CTetromino::SetMiddleY(float _middleY)
{
    m_middlePointY=_middleY;
}

void CTetromino::RotateMiddlePointsAroundZAxis(float _degrees)
{
    float rad = _degrees * (M_PI / 180.0f);
    float oldX, oldY = 0;
    oldX = m_middlePoint1.m_x;
    oldY = m_middlePoint1.m_y;
    m_middlePoint1.m_x = oldX * cos(rad) - oldY * sin(rad);
    m_middlePoint1.m_y = oldX * sin(rad) + oldY * cos(rad);
    oldX = m_middlePoint2.m_x;
    oldY = m_middlePoint2.m_y;
    m_middlePoint2.m_x = oldX * cos(rad) - oldY * sin(rad);
    m_middlePoint2.m_y = oldX * sin(rad) + oldY * cos(rad);
    oldX = m_middlePoint3.m_x;
    oldY = m_middlePoint3.m_y;
    m_middlePoint3.m_x = oldX * cos(rad) - oldY * sin(rad);
    m_middlePoint3.m_y = oldX * sin(rad) + oldY * cos(rad);
    oldX = m_middlePoint4.m_x;
    oldY = m_middlePoint4.m_y;
    m_middlePoint4.m_x = oldX * cos(rad) - oldY * sin(rad);
    m_middlePoint4.m_y = oldX * sin(rad) + oldY * cos(rad);
}
void CTetromino::RotateTetromino(bool _rotateClockwise)
{
    
    if (_rotateClockwise)
    {
        m_zRotation = ((int) m_zRotation - 90) % 360; //don't rotate more than 360 degrees
        float temp = m_distanceMiddleToHighestY;
        m_distanceMiddleToHighestY=m_distanceMiddleToLeftMostX;
        m_distanceMiddleToLeftMostX = m_distanceMiddleToLowestY;
        m_distanceMiddleToLowestY = m_distanceMiddleToRightMostX;
        m_distanceMiddleToRightMostX = temp;
        RotateMiddlePointsAroundZAxis(-90);
    }
    else
    {
        m_zRotation = ((int) m_zRotation+90) % 360; //don't rotate more than 360 degrees
        float temp = m_distanceMiddleToHighestY;
        m_distanceMiddleToHighestY = m_distanceMiddleToRightMostX;
        m_distanceMiddleToRightMostX = m_distanceMiddleToLowestY;
        m_distanceMiddleToLowestY = m_distanceMiddleToLeftMostX;
        m_distanceMiddleToLeftMostX = temp;
        RotateMiddlePointsAroundZAxis(90);

    }
}

void CTetromino::MoveTetromino(EMoveDirection _direction)
{
    switch (_direction)
    {
        case EMoveDirection::LEFT:
            m_middlePointX -= m_squareEdgeLength;
            break;
        case EMoveDirection::RIGHT: 
            m_middlePointX += m_squareEdgeLength;
            break;
        case EMoveDirection::DOWN:
            m_middlePointY -= m_squareEdgeLength;
            break;
    }
}


void CTetromino::GetMiddlePoints(CPoint* _pMiddlePoints)
{
    _pMiddlePoints[0] = m_middlePoint1;
    _pMiddlePoints[1] = m_middlePoint2;
    _pMiddlePoints[2] = m_middlePoint3;
    _pMiddlePoints[3] = m_middlePoint4;
}
