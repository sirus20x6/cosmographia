/*
 * $Revision: 477 $ $Date: 2010-08-31 11:49:37 -0700 (Tue, 31 Aug 2010) $
 *
 * Copyright by Astos Solutions GmbH, Germany
 *
 * this file is published under the Astos Solutions Free Public License
 * For details on copyright and terms of use see 
 * http://www.astos.de/Astos_Solutions_Free_Public_License.html
 */

#ifndef _VESTA_ARROW_GEOMETRY_H_
#define _VESTA_ARROW_GEOMETRY_H_

#include <Eigen/Core>
#include "Geometry.h"
#include "Submesh.h"
#include "Material.h"
#include <vector>

namespace vesta
{
class PrimitiveBatch;
class VertexArray;

/** ArrowGeometry is a Geometry object used for visualizers with one or
  * more arrows: body axes, frame axes, direction arrows, etc.
  */
class ArrowGeometry : public Geometry
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    enum
    {
        XAxis = 1,
        YAxis = 2,
        ZAxis = 4,
        AllAxes = 7
    };

    ArrowGeometry(float shaftLength,
                  float shaftRadius,
                  float headLength,
                  float headRadius);
    virtual ~ArrowGeometry();

    void render(RenderContext& rc,
                double animationClock) const;

    float boundingSphereRadius() const;

    virtual bool isOpaque() const
    {
        return m_opacity >= 1.0f;
    }

    double scale() const
    {
        return m_scale;
    }

    void setScale(double scale)
    {
        m_scale = scale;
    }

    /** Return a bit mask indicating which arrows are visible.
      */
    unsigned int visibleArrows() const
    {
        return m_visibleArrows;
    }

    /** Set which arrows should be visible.
      *
      * @param visibleArrows a bit mask of the values XAxis, YAxis, and ZAxis
      */
    void setVisibleArrows(unsigned int visibleArrows)
    {
        m_visibleArrows = visibleArrows;
    }

    Spectrum arrowColor(unsigned int which) const;
    void setArrowColor(unsigned int which, const Spectrum& color);

    /** Get the opacity (0 = completely transparent, 1 = opaque) of
      * the arrow geometry.
      */
    float opacity() const
    {
        return m_opacity;
    }

    /** Set opacity of the arrows (0 = completely transparent, 1 = opaque).
      */
    void setOpacity(float opacity)
    {
        m_opacity = opacity;
    }

private:
    void buildArrowGeometry(float shaftLength,
                            float shaftRadius,
                            float headLength,
                            float headRadius);
    void drawArrow(RenderContext& rc) const;

private:
    double m_scale;
    Spectrum m_arrowColors[3];
    float m_opacity;
    unsigned int m_visibleArrows;

    float m_geometryBoundingRadius;
    PrimitiveBatch* m_cap;
    PrimitiveBatch* m_shaft;
    PrimitiveBatch* m_annulus;
    PrimitiveBatch* m_point;
    VertexArray* m_vertices;
};

}

#endif // _VESTA_ARROW_GEOMETRY_H_

