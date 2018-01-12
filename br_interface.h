#pragma once

#include <atlimage.h>
#include <vector>
#include "Selection.h"

namespace br
{
    class Transform;
}

class brInterface
{
public:
    brInterface();

    static void init();

    static void destruct();

    //br::Transform * keyPointDetector;
   
    void pointCorrespondence( CImage & src, CImage & dst, std::vector<CSelection*>  & srcRegions, std::vector<CSelection*> & dstRegions, CSelection::Mode selectMode );

//    void clone(CImage & src, CImage & dst, std::vector<CRect> & srcRegions, std::vector<CRect> & dstRegions);

};

void clone(CImage & src, CImage & dst, std::vector<CSelection*> & srcRegions, std::vector<CSelection*> & dstRegions);
void clone2(CImage & src, CImage & dst, std::vector<CSelection*> & srcRegions, std::vector<CSelection*> & dstRegions);