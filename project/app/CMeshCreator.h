﻿#pragma once
#include <yoshix_fix_function.h>
using namespace gfx;

class CMeshCreator
{
public:

    CMeshCreator();
    ~CMeshCreator();

private:
    float m_SquareEdgeLength;

public:
    // -----------------------------------------------------------------------------
    // Produces Shape:
    // ████
    // -----------------------------------------------------------------------------
    void CreateFlatLinedTetromino(BHandle* _ppMesh);

    // -----------------------------------------------------------------------------
    // Produces Shape:
    // ██
    // ██
    // -----------------------------------------------------------------------------
    void CreateSquareTetromino(BHandle* _ppMesh);


    // -----------------------------------------------------------------------------
    // Produces Shape:
    //  █
    // ███
    // -----------------------------------------------------------------------------
    void CreateTShapedTetromino(BHandle* _ppMesh);


    // -----------------------------------------------------------------------------
    // Produces Shape:
    // █
    // ███
    // -----------------------------------------------------------------------------
    void CreateLeftHandedLShapedTetromino(BHandle* _ppMesh);


    // -----------------------------------------------------------------------------
    // Produces Shape:
    //   █
    // ███
    // -----------------------------------------------------------------------------
    void CreateRightHandedLShapedTetromino(BHandle* _ppMesh);


    // -----------------------------------------------------------------------------
    // Produces Shape:
    //  ██
    // ██
    // -----------------------------------------------------------------------------
    void CreateLeftHandedZShapedTetromino(BHandle* _ppMesh);


    // -----------------------------------------------------------------------------
    // Produces Shape:
    // ██
    //  ██
    // -----------------------------------------------------------------------------
    void CreateRightHandedZShapedTetromino(BHandle* _ppMesh);

    // -----------------------------------------------------------------------------
    // Produces left and right level border
    // -----------------------------------------------------------------------------
    void CreateLeftAndRightLevelBorder(BHandle* _ppMesh);

    // -----------------------------------------------------------------------------
    // Produces top and bottom level border
    // -----------------------------------------------------------------------------
    void CreateTopAndBottomLevelBorder(BHandle* _ppMesh);

};

