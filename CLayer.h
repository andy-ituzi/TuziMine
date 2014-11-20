#ifndef CLAYER_H
#define CLAYER_H

const int FRAME_PER_SEC = 15;
const int MAX_NUM_KEYFRAME = 10;
const double PI = 3.1415926;

typedef struct
{
    union {
        double x;
        double rotation_count;
        double opacity;
    };
    union {
        double y;
        double rotation_angle;
    };
}LPOINT, LPOSITION, LSCALE, LROTATION, LOPACITY, LVALUE;

typedef struct
{
    bool isEnabled;
    long frameCount;
    LVALUE value;
}KEYFRAME_VALUE;

typedef struct
{
    LPOINT anchorPoint;
    LPOSITION position;
    LSCALE scale;
    LROTATION rotation;
    LOPACITY opacity;
}FRAME_VALUE;

const int TYPE_ANCHORPOINT = 0;
const int TYPE_POSITION = 1;
const int TYPE_SCALE = 2;
const int TYPE_ROTATION = 3;
const int TYPE_OPACITY = 4;
const int TYPE_TOTAL = 5;

//Start from a global time t, the layer was shown on the screen
//layer could use key frames to control attributes
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

    virtual void SetFirstFrame(double ax, double ay, double px, double py, double sx, double sy, double rc, double ra, double op);
    virtual void AddKeyFrame(const int type, long frameCount, double v1, double v2=0);

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
    virtual void SetCurrentFrame(const FRAME_VALUE& value)
    {
        m_currentFrame = value;
    }
    virtual void GetCurrentFrame(FRAME_VALUE& value)
    {
        value = m_currentFrame;
    }
    virtual void SetCurrentTime(long time)
    {
        m_frameCount = time;
    }
    virtual void GetCurrentTime(long& time)
    {
        time = m_frameCount;
    }

    virtual void GetKeyFrame(KEYFRAME_VALUE& kfv, const int type, int index)
    {
        kfv = m_keyFrame[type][index];
    }

    virtual void SetCurrentFramePosition(double x, double y)
    {
        m_currentFrame.position.x = x;
        m_currentFrame.position.y = y;
    }

    virtual void SetCurrentFrameOpacity(double op)
    {
        m_currentFrame.opacity.opacity = op;
    }

    virtual void SetCurrentFrameAnchorPoint(double x, double y)
    {
        m_currentFrame.anchorPoint.x = x;
        m_currentFrame.anchorPoint.y = y;
    }

    virtual void SetCurrentFrameRotation(double rc, double ra)
    {
        m_currentFrame.rotation.rotation_count = rc;
        m_currentFrame.rotation.rotation_angle = ra;
    }

    virtual void SetCurrentFrameScale(double x, double y)
    {
        m_currentFrame.scale.x = x;
        m_currentFrame.scale.y = y;
    }

    virtual void SetCurrentFrame(double ax, double ay, double px, double py, double sx, double sy, double rc, double ra, double op)
    {
        m_currentFrame.anchorPoint.x = ax;
        m_currentFrame.anchorPoint.y = ay;
        m_currentFrame.position.x = px;
        m_currentFrame.position.y = py;
        m_currentFrame.scale.x = sx;
        m_currentFrame.scale.y = sy;
        m_currentFrame.rotation.rotation_count = rc;
        m_currentFrame.rotation.rotation_angle = ra;
        m_currentFrame.opacity.opacity = op;
    }

    virtual void RepeatBetween(int start_frame, int end_frame)
    {
        m_repeat = true;
        m_frameCount = start_frame;
        m_start_frame = start_frame;
        m_end_frame = end_frame;
    }

    virtual void StartAndEndAt(int start_frame, int end_frame)
    {
        m_repeat = false;
        m_frameCount = start_frame;
        m_end_frame = end_frame;
    }
    virtual void SetShown(bool show)
    {
        m_show = show;
    }

protected:
    virtual void UpdateCurrentTime(void);
    virtual void UpdateCurrentFrame(void);
    virtual bool GetPreviousKeyFrame(const int type, KEYFRAME_VALUE& value);
    virtual bool GetNextKeyFrame(const int type, KEYFRAME_VALUE& value);
    virtual void ConvertFromClientToLocal(int cx, int cy, int& x, int& y);
    virtual void ConvertFromLocalToClient(int lx, int ly, int& x, int& y);

protected:
    int m_width;
    int m_height;
    long m_frameCount;
    bool m_bEnableKeyFrame[TYPE_TOTAL];
    KEYFRAME_VALUE m_keyFrame[TYPE_TOTAL][MAX_NUM_KEYFRAME];
    FRAME_VALUE m_currentFrame;
    bool m_repeat;
    int m_start_frame;
    int m_end_frame;
    bool m_show;
};

#endif // CLAYER_H
