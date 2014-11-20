#ifndef CANIMATELAYER_H
#define CANIMATELAYER_H

#include "CLayer.h"
#include "CImageLayer.h"

const int MAX_SEQUENCE_LENGTH = 50;


class CAnimateLayer : public CLayer
{
public:
    CAnimateLayer(const char* path_seq, int n, wxSize clientSize);
    virtual ~CAnimateLayer();

    virtual void Update(void);
    virtual void Render(void);

private:
    const char *m_path;
    wxSize m_clientSize;
    CImageLayer *m_sequence[MAX_SEQUENCE_LENGTH];
    int m_total;
    int m_index;
};

#endif // CANIMATELAYER_H
