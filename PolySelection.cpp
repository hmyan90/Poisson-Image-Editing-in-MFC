#include "StdAfx.h"
#include "PolySelection.h"

CPolySelection::CPolySelection( int x, int y )
{
   m_nextPoint = CPoint( x, y );
   m_verts.push_back( m_nextPoint );
   m_bIsFinished = FALSE;
   m_bShouldPlace = FALSE;
}

CPolySelection::~CPolySelection()
{
}

BOOL CPolySelection::IsPointInSelection( int x, int y )
{
   int i, j;
   BOOL bInPoly = FALSE;
   for (i = 0, j = m_verts.size()-1; i < m_verts.size(); j = i++) 
   {
      if ( ((m_verts[i].y>y) != (m_verts[j].y>y)) &&
         (x < (m_verts[j].x-m_verts[i].x) * (y-m_verts[i].y) / (m_verts[j].y-m_verts[i].y) + m_verts[i].x) )
      {
         bInPoly = !bInPoly;
      }
   }

   return bInPoly;
}

CPoint CPolySelection::GetBasePoint()
{
   return GetBoundingBox().TopLeft();
}

void CPolySelection::OnLButtonDown( DragState dragState, CPoint point, CImage* pImage, CImage* pImage2  )
{
   CImage* image = dragState == CSelection::DRAGGING ? pImage : pImage2;
   point.x = max( 1, point.x );
   point.y = max( 1, point.y );
   point.x = min( image->GetWidth() - 1, point.x );
   point.y = min( image->GetHeight() - 1, point.y );

   if( dragState == CSelection::DRAGGING )
   {
      m_nextPoint = point;
      m_verts.push_back( m_nextPoint );
   }
}

BOOL CPolySelection::OnLButtonDblClk( DragState dragState, CPoint point, std::vector<CSelection*>& selections )
{
   if( m_verts.size() <= 1 )
   {
      return FALSE;
   }

   m_bIsFinished = TRUE;
      
   if( dragState == CSelection::DRAGGING )
   {
      m_nextPoint = point;
      m_verts.push_back( m_nextPoint );
   }

   selections.push_back( this );

   return TRUE;
}

BOOL CPolySelection::OnLButtonUp( DragState dragState, CPoint point, CImage* pImage, std::vector<CSelection*>& selections )
{
   if( m_bShouldPlace )
   {
      selections.push_back( this );
      return TRUE;
   }

   if( m_bIsFinished )
   {
      m_bShouldPlace = TRUE;
   }

   return FALSE;
}

void CPolySelection::OnMouseMove( DragState dragState, CPoint point, CImage* pImage, CImage* pImage2 )
{
   CImage* image = dragState == CSelection::DRAGGING ? pImage : pImage2;

   if( dragState == CSelection::DRAGGING )
   {
      point.x = max( 1, point.x );
      point.y = max( 1, point.y );
      point.x = min( image->GetWidth() - 1, point.x );
      point.y = min( image->GetHeight() - 1, point.y );

      m_nextPoint = point;
   }

   if( dragState == CSelection::FIXED )
   {
      point.x -= pImage->GetWidth();

      point.x = max( 1, point.x );
      point.y = max( 1, point.y );
      point.x = min( image->GetWidth() - GetBoundingBox().Width() - 1, point.x );
      point.y = min( image->GetHeight() - GetBoundingBox().Height() - 1, point.y );

      if( m_verts.size() <= 0 )
      {
         return;
      }

      auto diff = point - GetBasePoint();

      std::vector<CPoint> newVerts;

      for( int i=0; i<(int)m_verts.size(); i++ )
      {
         auto p = m_verts[i];
         newVerts.push_back( p + diff );
      }

      m_verts = newVerts;
   }
}

void CPolySelection::OnDraw( CImage* pImage, COLORREF color )
{
   /*CRect tmpSelection = m_rect;
   CorrectDragRect( &tmpSelection );
   BoundRect( pImage, &tmpSelection );*/

   

   auto hDC = pImage->GetDC();
   auto memoryDC = CDC::FromHandle( hDC );
   CPen    pen( PS_SOLID, 1, color );
   CPen*    pOldPen = memoryDC->SelectObject( &pen );
   //auto origColor = memoryDC->SetDCPenColor( color );

   if( m_verts.size() <= 0 )
   {
      return;
   }

   memoryDC->MoveTo( m_verts[0] );

   for( int i=1; i<(int)m_verts.size(); i++ )
   {
      auto p = m_verts[i];
      memoryDC->LineTo( p );
   }

   if( !m_bIsFinished )
   {
      memoryDC->LineTo( m_nextPoint );
   }
   else
   {
      memoryDC->LineTo( m_verts[0] );
   }

   pImage->ReleaseDC();
}

void CPolySelection::Normalize()
{
   if( m_verts.size() <= 0 )
   {
      return;
   }

   auto point = CPoint(0, 0);
   auto diff = point - GetBasePoint();

   std::vector<CPoint> newVerts;

   for( int i=0; i<(int)m_verts.size(); i++ )
   {
      auto p = m_verts[i];
      newVerts.push_back( p + diff );
   }

   m_verts = newVerts;
   m_bIsFinished = TRUE;
   m_bShouldPlace = FALSE;
}

CSelection* CPolySelection::Copy()
{
   if( m_verts.size() <= 0 )
   {
      return NULL;
   }

   auto sel = new CPolySelection( m_verts[0].x, m_verts[0].y );

   for( int i=1; i<(int)m_verts.size(); i++ )
   {
      sel->AddPoint( m_verts[i].x, m_verts[i].y );
   }

   return sel;
}

CRect CPolySelection::GetBoundingBox()
{
   if( m_verts.size() <= 0 )
   {
      return CRect();
   }

   int minX, maxX, minY, maxY;
   minX = maxX = m_verts[0].x;
   minY = maxY = m_verts[0].y;

   for( int i=1; i<(int)m_verts.size(); i++ )
   {
      minX = min( minX, m_verts[i].x );
      maxX = max( maxX, m_verts[i].x );

      minY = min( minY, m_verts[i].y );
      maxY = max( maxY, m_verts[i].y );
   }

   return CRect( minX, minY, maxX, maxY );
}

void CPolySelection::AddPoint( int x, int y )
{
   m_verts.push_back( CPoint(x, y) );
}