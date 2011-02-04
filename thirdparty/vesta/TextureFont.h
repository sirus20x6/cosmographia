/*
 * $Revision: 521 $ $Date: 2010-10-04 15:44:05 -0700 (Mon, 04 Oct 2010) $
 *
 * Copyright by Astos Solutions GmbH, Germany
 *
 * this file is published under the Astos Solutions Free Public License
 * For details on copyright and terms of use see 
 * http://www.astos.de/Astos_Solutions_Free_Public_License.html
 */

#ifndef _VESTA_TEXTURE_FONT_H_
#define _VESTA_TEXTURE_FONT_H_

#include "Object.h"
#include "TextureMap.h"
#include <Eigen/Core>
#include <GL/glew.h>
#include <string>
#include <vector>


namespace vesta
{

class DataChunk;

class TextureFont : public Object
{
public:
    struct Glyph
    {
        unsigned int characterId;
        Eigen::Vector2f textureCoords[4];

        Eigen::Vector2f offset;
        Eigen::Vector2f size;

        float advance;
    };

    TextureFont();
    ~TextureFont();

    Eigen::Vector2f render(const std::string& text,
                           const Eigen::Vector2f& startPosition) const;
    float textWidth(const std::string& text) const;
    const Glyph* lookupGlyph(wchar_t ch) const;

    void addGlyph(const Glyph& glyph);
    void buildCharacterSet();
    bool buildFontTexture(unsigned int width,
                          unsigned int height,
                          unsigned char* pixels);

    void bind() const;
    TextureMap* glyphTexture() const
    {
        return m_glyphTexture.ptr();
    }

    bool loadTxf(const DataChunk* data);

    static TextureFont* LoadTxf(const DataChunk* data);

private:
    counted_ptr<TextureMap> m_glyphTexture;
    std::vector<Glyph> m_glyphs;
    std::vector<unsigned int> m_characterSet;
    unsigned int m_maxCharacterId;
};

}

#endif // _VESTA_TEXTURE_FONT_H_

