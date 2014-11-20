#include "CAnimateLayer.h"
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

CAnimateLayer::CAnimateLayer(const char* path_seq, int n, wxSize clientSize)
    :CLayer(),
    m_path(path_seq),
    m_clientSize(clientSize),
    m_total(n),
    m_index(-1),
    m_framesPerImage(1),
    m_frameDelay(1)
{
    for (int i=0; i<MAX_SEQUENCE_LENGTH; i++)
    {
        m_sequence[i] = 0;
    }
    char path[256];
    char index[16];
    for (int i=0; i<n; i++)
    {
        sprintf(index, "%04d.png", i);
        path[0] = '\0';
        strcat(path, m_path);
        strcat(path, index);

        m_sequence[i] = new CImageLayer(path, m_clientSize);
        m_sequence[i]->SetCurrentFrame(m_sequence[i]->GetWidth()/2, m_sequence[i]->GetHeight()/2,
                                     0, 0, 100, 100, 0, 0, 100);
    }
    TEXTURE texture;
    m_sequence[0]->GetTexture(texture);
    SetWidth(texture.w);
    SetHeight(texture.h);
}

CAnimateLayer::~CAnimateLayer()
{
    for (int i=0; i<MAX_SEQUENCE_LENGTH; i++)
    {
        if (0 == m_sequence[i])
        {
            delete m_sequence[i];
            m_sequence[i] = 0;
        }
    }
}

void CAnimateLayer::Update(void)
{
    if (1 == m_frameDelay)
    {
        m_index = (m_index+1)%m_total;
        m_frameDelay = m_framesPerImage;
    }
    else
    {
        m_frameDelay--;
    }
    CLayer::Update();
}

void CAnimateLayer::Render(void)
{
    if (false == m_show)
    {
        return;
    }
    m_sequence[m_index]->SetCurrentFramePosition(m_currentFrame.position.x, m_currentFrame.position.y);
    m_sequence[m_index]->SetCurrentFrameScale(m_currentFrame.scale.x, m_currentFrame.scale.y);
    m_sequence[m_index]->SetCurrentFrameRotation(m_currentFrame.rotation.rotation_count, m_currentFrame.rotation.rotation_angle);
    m_sequence[m_index]->SetCurrentFrameOpacity(m_currentFrame.opacity.opacity);
    m_sequence[m_index]->Render();
}

void CAnimateLayer::SetShown(bool show)
{
    CLayer::SetShown(show);
    for (int i=0; i<m_total; i++)
    {
        m_sequence[i]->SetShown(show);
    }
}

