#include "CTetromino.h"
#include <utility>
#include <iostream>


CTetromino::CTetromino(ETetrominoShape _shape, float _distanceMiddleToLeftMostX, float _distanceMiddleToRightMostX, float _distanceMiddleToHighestY, float _distanceMiddleToLowestY)
    : m_isCurrentActiveTetromino    (true)
    , m_shape                       (_shape)
    , m_middlePointX                (0.0f)
    , m_middlePointY                (0.0f)
    , m_distanceMiddleToLeftMostX   (_distanceMiddleToLeftMostX)
    , m_distanceMiddleToRightMostX  (_distanceMiddleToRightMostX)
    , m_distanceMiddleToHighestY    (_distanceMiddleToHighestY)
    , m_distanceMiddleToLowestY     (_distanceMiddleToLowestY)
    , m_squareEdgeLength            (1.0f)
    , m_zRotation                   (0.0f)
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

void CTetromino::SetMiddleX(float _middleX)
{
    m_middlePointX=_middleX;
}

void CTetromino::SetMiddleY(float _middleY)
{
    m_middlePointY=_middleY;
}

void CTetromino::RotateTetromino(bool _rotateClockwise)
{
    
    if (_rotateClockwise)
    {
        m_zRotation += 90.0f;
        float temp = m_distanceMiddleToHighestY;
        m_distanceMiddleToHighestY=m_distanceMiddleToLeftMostX;
        m_distanceMiddleToLeftMostX = m_distanceMiddleToLowestY;
        m_distanceMiddleToLowestY = m_distanceMiddleToRightMostX;
        m_distanceMiddleToRightMostX = temp;
    }
    else
    {
        m_zRotation -= 90.0f;
        float temp = m_distanceMiddleToHighestY;
        m_distanceMiddleToHighestY = m_distanceMiddleToRightMostX;
        m_distanceMiddleToRightMostX = m_distanceMiddleToLowestY;
        m_distanceMiddleToLowestY = m_distanceMiddleToLeftMostX;
        m_distanceMiddleToLeftMostX = temp;
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
            SetMiddleY(GetMiddleY() - m_squareEdgeLength);
            break;
    }
}
