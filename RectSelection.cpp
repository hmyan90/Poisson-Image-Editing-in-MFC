#include "StdAfx.h"
#include "RectSelection.h"
#include <atlimage.h>

CRectSelection::CRectSelection( int l, int t, int r, int b )
{
   m_rect.left = l;
   m_rect.top = t;
   m_rect.right = r;
   m_rect.bottom = b;
}

CRectSelection::CRectSelection( CRect rect )
{
   m_rect = rect;
}

CRectSelection::~CRectSelection()
{
}

BOOL CRectSelection::IsPointInSelection( int x, int y )
{
   if( x >= m_rect.left && x < m_rect.right &&
         y >= m_rect.top && y<m_rect.bottom )
   {
      return TRUE;
   }

   return FALSE;
}

CPoint CRectSelection::GetBasePoint()
{
   return CPoint( m_rect.left, m_rect.top );
}

void CRectSelection::OnLButtonDown( DragState dragState, CPoint point, CImage* pImage, CImage* pImage2  )
{
   
}

BOOL CRectSelection::OnLButtonDblClk( DragState dragState, CPoint point, std::vector<CSelection*>& selections )
{
   return FALSE;
}

BOOL CRectSelection::OnLButtonUp( DragState dragState, CPoint point, CImage* pImage, std::vector<CSelection*>& selections )
{
   if( dragState == DRAGGING )
   {     
      CorrectDragRect( &m_rect );
      BoundRect( pImage, &m_rect );

      if( m_rect.Width() >= 4 && m_rect.Height() >= 4 )
      {
         selections.push_back( this );
      }
   }
   else if( dragState == FIXED )
   {
      if( m_rect.Width() >= 4 && m_rect.Height() >= 4 )
      {
         selections.push_back( this );
      }
   }

   return TRUE;
}

void CRectSelection::OnMouseMove( DragState dragState, CPoint point, CImage* pImage, CImage* pImage2 )
{
   if( dragState == DRAGGING )
   {
      m_rect.right = min( point.x, pImage->GetWidth()-1 );
      m_rect.bottom = min( point.y, pImage->GetHeight()-1 );
   }
   else if( dragState == FIXED )
   {
      point.x -= pImage->GetWidth();

      if( point.x >= 0 && point.y >= 0 )
      {
         m_rect.SetRect( point.x, point.y, point.x + m_rect.Width(), point.y + m_rect.Height() );

         if( m_rect.right > pImage2->GetWidth() )
         {
            m_rect.SetRect( pImage2->GetWidth() - 1 - m_rect.Width(), m_rect.top, pImage2->GetWidth() - 1, m_rect.bottom );
         }

         if( m_rect.bottom > pImage2->GetHeight() )
         {
            m_rect.SetRect( m_rect.left, pImage2->GetHeight() - 1 - m_rect.Height(), m_rect.right, pImage2->GetHeight() - 1 );
         }
      }       
   }
}

void CRectSelection::BoundRect( CImage* pImage, CRect* rect )
{
   rect->left = max(rect->left, 1);
   rect->top = max(rect->top, 1);
   rect->right = min(rect->right, pImage->GetWidth()-1);
   rect->bottom = min(rect->bottom, pImage->GetHeight()-1);
}

void CRectSelection::CorrectDragRect( CRect* rect )
{
   if( rect->left > rect->right )
   {
      auto tmp = rect->left;
      rect->left = rect->right;
      rect->right = tmp;
   }

   if( rect->top > rect->bottom )
   {
      auto tmp = rect->top;
      rect->top = rect->bottom;
      rect->bottom = tmp;
   }
}

void CRectSelection::OnDraw( CImage* pImage, COLORREF color )
{
   CRect tmpSelection = m_rect;
   CorrectDragRect( &tmpSelection );
   BoundRect( pImage, &tmpSelection );

   for( int x=tmpSelection.left; x<tmpSelection.right; x++ )
   {
      for( int y=tmpSelection.top; y<tmpSelection.bottom; y++ )
      {
         if( x == tmpSelection.left || x == tmpSelection.right - 1 ||
            y == tmpSelection.top || y == tmpSelection.bottom - 1)
         {
            pImage->SetPixel( x, y, color );
         }
      }
   }
}

void CRectSelection::Normalize()
{
   m_rect.SetRect( 0, 0, m_rect.Width(), m_rect.Height() );
}

CSelection* CRectSelection::Copy()
{
   return new CRectSelection( m_rect.left, m_rect.top, m_rect.right, m_rect.bottom );
}

CRect CRectSelection::GetBoundingBox()
{
   return m_rect;
}