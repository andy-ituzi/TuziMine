#include "CImageLayer.h"
#include <cstdlib>
#include <iostream>
using namespace std;


CImageLayer::CImageLayer(const char* path, wxSize clientSize)
    :CLayer(),
    m_path(path),
    m_clientSize(clientSize)
{
    GenerateTextures();
    SetWidth(m_texture.w);
    SetHeight(m_texture.h);
}

CImageLayer::CImageLayer(const TEXTURE& texture, wxSize clientSize)
    :CLayer(),
    m_texture(texture),
    m_path(0),
    m_clientSize(clientSize)
{
    SetWidth(m_texture.w);
    SetHeight(m_texture.h);
}

CImageLayer::~CImageLayer()
{
    glDeleteTextures(1, &m_texture.texture);
}

void CImageLayer::Render(void)
{
    if (false == m_show)
    {
        return;
    }
//    cout << "@CImageLayer.." << endl;
//    cout << m_currentFrame.anchorPoint.x << " " << m_currentFrame.anchorPoint.y << endl;
//    cout << m_currentFrame.position.x << " " << m_currentFrame.position.y << endl;
//    cout << m_currentFrame.scale.x << " " << m_currentFrame.scale.y << endl;
//    cout << m_currentFrame.rotation.rotation_count << " " << m_currentFrame.rotation.rotation_angle << endl;
//    cout << m_currentFrame.opacity.opacity << endl;

    glPushMatrix();
    //can not use it
    //glViewport(0, 0, m_clientSize.x, m_clientSize.y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, m_clientSize.x, 0, m_clientSize.y, 1, -1);

    //Ë³Ðò²»ÄÜ¸Ä
    glScalef(m_currentFrame.scale.x/100, m_currentFrame.scale.y/100, 1);
    glTranslatef(m_currentFrame.position.x / m_currentFrame.scale.x * 100 , m_currentFrame.position.y / m_currentFrame.scale.y * 100, 0);
    glRotatef(m_currentFrame.rotation.rotation_count * 360 + m_currentFrame.rotation.rotation_angle, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texture.texture);

    glBegin(GL_QUADS);
        glColor4f(1.f, 1.f, 1.f, m_currentFrame.opacity.opacity/100);
        glTexCoord2f(0, 1.f);     glVertex2f(-m_currentFrame.anchorPoint.x, -m_currentFrame.anchorPoint.y);
        glTexCoord2f(1.f, 1.f);   glVertex2f(m_width-m_currentFrame.anchorPoint.x, -m_currentFrame.anchorPoint.y);
        glTexCoord2f(1.f, 0.f);   glVertex2f(m_width-m_currentFrame.anchorPoint.x, m_height-m_currentFrame.anchorPoint.y);
        glTexCoord2f(0, 0.f);     glVertex2f(-m_currentFrame.anchorPoint.x, m_height-m_currentFrame.anchorPoint.y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();

    glFlush();
}


bool CImageLayer::GenerateTextures(void)
{
    glGenTextures(1, &m_texture.texture);
    glBindTexture(GL_TEXTURE_2D, m_texture.texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    wxImage img;
    if (false == img.LoadFile(m_path, wxBITMAP_TYPE_PNG) )
    {
        return false;
    }
    m_texture.w = img.GetWidth();
    m_texture.h = img.GetHeight();

    if (true == img.HasAlpha())
    {
        int w = m_texture.w;
        int h = m_texture.h;
        unsigned char *buffer = (unsigned char*)malloc(h*w*4* sizeof(char));
        for (int i=0; i<h; i++)
        {
            for (int j=0; j<w; j++)
            {
                buffer[((i*w)+j)*4+3] = img.GetAlpha(j, i);
                buffer[((i*w)+j)*4+2] = img.GetBlue(j, i);
                buffer[((i*w)+j)*4+1] = img.GetGreen(j, i);
                buffer[((i*w)+j)*4]   = img.GetRed(j, i);
            }
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        free(buffer);
        cout << m_path << "->with alpha:" << w << "x" << h << endl;
    }
    else
    {
        cout << m_path << "->no alpha:" << img.GetWidth() << "x" << img.GetHeight() << endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());
    }
    return true;
}

