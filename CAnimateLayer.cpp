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
    m_index(0)
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
        cout << path << endl;

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
    m_index = (m_index+1)%m_total;
}

void CAnimateLayer::Render(void)
{
    m_sequence[m_index]->SetCurrentFrame(m_currentFrame);
    m_sequence[m_index]->Render();
}

