#ifndef CIMAGELAYER_H
#define CIMAGELAYER_H

#include "CLayer.h"
#include <wx/wx.h>
#include <wx/glcanvas.h>

typedef struct
{
    int w;
    int h;
    GLuint texture;
}TEXTURE;


class CImageLayer : public CLayer
{
public:
    CImageLayer(const char* path, wxSize clientSize);
    CImageLayer(const TEXTURE& texture, wxSize clientSize);
    virtual ~CImageLayer();

    virtual void Render(void);
    void GetClientSize(wxSize& clientSize)
    {
        clientSize = m_clientSize;
    }
    void GetTexture(TEXTURE& texture)
    {
        texture = m_texture;
    }

protected:
    bool GenerateTextures(void);

private:
    TEXTURE m_texture;
    const char *m_path;
    wxSize m_clientSize;
};

#endif // CIMAGELAYER_H
