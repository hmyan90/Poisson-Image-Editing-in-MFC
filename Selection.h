#pragma once

#include <vector>
#include <atlimage.h>

class CSelection
{
protected:
   CSelection(void);

public:
   enum DragState { IDLE, DRAGGING, FIXED };
   enum Mode { RECT, POLY };

   ~CSelection(void);

   virtual BOOL IsPointInSelection( int x, int y ) = 0;
   virtual CPoint GetBasePoint() = 0;
   virtual void Normalize() = 0;
   virtual CSelection* Copy() = 0;
   virtual CRect GetBoundingBox() = 0;
   virtual void OnLButtonDown( DragState dragState, CPoint point, CImage* pImage, CImage* pImage2  ) = 0;
   virtual BOOL OnLButtonDblClk( DragState dragState, CPoint point, std::vector<CSelection*>& selections ) = 0;
   virtual BOOL OnLButtonUp( DragState dragState, CPoint point, CImage* pImage, std::vector<CSelection*>& selections ) = 0;
   virtual void OnMouseMove( DragState dragState, CPoint point, CImage* pImage, CImage* pImage2 ) = 0;
   virtual void OnDraw( CImage* pImage, COLORREF color ) = 0;

   CPoint TranslatePointToOtherSelection( int x, int y, CSelection* selection );
};

