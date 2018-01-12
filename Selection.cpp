#include "StdAfx.h"
#include "Selection.h"


CSelection::CSelection(void)
{
}


CSelection::~CSelection(void)
{
}

CPoint CSelection::TranslatePointToOtherSelection( int x, int y, CSelection* selection )
{
   auto thisPoint = GetBasePoint();
   auto diffX = x - thisPoint.x;
   auto diffY = y - thisPoint.y;

   auto otherPoint = selection->GetBasePoint();
   return CPoint( otherPoint.x + diffX, otherPoint.x + diffY );
}