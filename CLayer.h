#ifndef CLAYER_H
#define CLAYER_H

const int FRAME_PER_SEC = 15;
const int MAX_NUM_KEYFRAME = 100;
const double PI = 3.1415926;

typedef struct
{
    double ax, ay;//pixel
    double px, py;//pixel
    double sx, sy;//0-1
    int rc;
    double ra;
    double op;//0-1
}FRAME_VALUE;

typedef struct
{
    bool isEnabled;
    long frameCount;
    FRAME_VALUE value;
}KEYFRAME_VALUE;

const int TYPE_ANCHORPOINT = 0;
const int TYPE_POSITION = 1;
const int TYPE_SCALE = 2;
const int TYPE_ROTATION = 3;
const int TYPE_OPACITY = 4;
const int TYPE_TOTAL = 5;

class CLayer
{
public:
    CLayer();
    CLayer(int width, int height);
    virtual ~CLayer();
    virtual bool Initialize(void);
    virtual void Update(void);
    virtual void Render(void);
    virtual void CloseUp(void);

    virtual void AddKeyFrame(long frameCount, double ox, double oy,
                             double px, double py, double sx, double sy,
                             int rc, double ra, double op);

    virtual void SetWidth(int w)
    {
        m_width = w;
    }
    virtual int GetWidth(void)
    {
        return m_width;
    }
    virtual void SetHeight(int h)
    {
        m_height = h;
    }
    virtual int GetHeight(void)
    {
        return m_height;
    }

    virtual void GetCurrentFrame(FRAME_VALUE& value)
    {
        value = m_currentFrame;
    }

    virtual void SetCurrentFramePosition(double x, double y)
    {
        m_currentFrame.px = x;
        m_currentFrame.py = y;
    }

    virtual void SetCurrentFrameAnchorPoint(double x, double y)
    {
        m_currentFrame.ax = x;
        m_currentFrame.ay = y;
    }

    virtual void SetCurrentFrameScale(double x, double y)
    {
        m_currentFrame.sx = x;
        m_currentFrame.sy = y;
    }

    virtual void SetCurrentFrameRotation(int rc, double ra)
    {
        m_currentFrame.rc = rc;
        m_currentFrame.ra = ra;
    }

    virtual void SetCurrentFrameOpacity(double op)
    {
        m_currentFrame.op = op;
    }

    virtual void SetCurrentFrame(const FRAME_VALUE& value)
    {
        m_currentFrame = value;
    }

    virtual void SetCurrentFrame(double ax, double ay, double px, double py, double sx, double sy, int rc, double ra, double op)
    {
        m_currentFrame.ax= ax;
        m_currentFrame.ay = ay;
        m_currentFrame.px = px;
        m_currentFrame.py = py;
        m_currentFrame.sx = sx;
        m_currentFrame.sy = sy;
        m_currentFrame.rc = rc;
        m_currentFrame.ra = ra;
        m_currentFrame.op = op;
    }

    virtual void RepeatBetween(int start_frame, int end_frame)
    {
        m_active = true;
        m_repeat = true;
        m_frameCount = start_frame-1;
        m_start_frame = start_frame;
        m_end_frame = end_frame;
    }

    virtual void StartAndEndAt(int start_frame, int end_frame)
    {
        m_active = true;
        m_repeat = false;
        m_frameCount = start_frame;
        m_start_frame = start_frame;
        m_end_frame = end_frame;
    }

    virtual void SetShown(bool show)
    {
        m_show = show;
    }
    virtual void SetActive(bool active)
    {
        m_active = active;
    }

protected:
    virtual void UpdateCurrentTime(void);
    virtual void UpdateCurrentFrame(void);
    virtual bool GetPreAndNextKeyFrame(KEYFRAME_VALUE& pv, KEYFRAME_VALUE& nv);
    virtual void ConvertFromClientToLocal(int cx, int cy, int& x, int& y);
    virtual void ConvertFromLocalToClient(int lx, int ly, int& x, int& y);

protected:
    int m_width;
    int m_height;
    long m_frameCount;
    KEYFRAME_VALUE m_keyFrame[MAX_NUM_KEYFRAME];
    FRAME_VALUE m_currentFrame;
    bool m_repeat;
    int m_start_frame;
    int m_end_frame;
    bool m_show;
    bool m_active;
};

#endif // CLAYER_H
