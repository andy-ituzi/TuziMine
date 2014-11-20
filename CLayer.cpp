#include "CLayer.h"
#include <cmath>
#include <iostream>
using namespace std;

CLayer::CLayer()
{
    for (int i=0; i<TYPE_TOTAL; i++)
    {
        m_bEnableKeyFrame[i] = false;
        for (int j=0; j<MAX_NUM_KEYFRAME; j++)
        {
            m_keyFrame[i][j].isEnabled = false;
        }
    }
    m_frameCount = -1;

    m_currentFrame.anchorPoint.x = 0;
    m_currentFrame.anchorPoint.y = 0;
    m_currentFrame.position.x = 0;
    m_currentFrame.position.y = 0;
    m_currentFrame.scale.x = 0;
    m_currentFrame.scale.y = 0;
    m_currentFrame.rotation.rotation_count = 0;
    m_currentFrame.rotation.rotation_angle = 0;
    m_currentFrame.opacity.opacity = 0;
    m_repeat = false;
    m_start_frame = 0;
    m_end_frame = 0;
    m_show = false;
}

CLayer::CLayer(int width, int height)
    :m_width(width),
    m_height(height)
{
    for (int i=0; i<TYPE_TOTAL; i++)
    {
        m_bEnableKeyFrame[i] = false;
        for (int j=0; j<MAX_NUM_KEYFRAME; j++)
        {
            m_keyFrame[i][j].isEnabled = false;
        }
    }
    m_frameCount = 0;

    m_currentFrame.anchorPoint.x = 0;
    m_currentFrame.anchorPoint.y = 0;
    m_currentFrame.position.x = 0;
    m_currentFrame.position.y = 0;
    m_currentFrame.scale.x = 0;
    m_currentFrame.scale.y = 0;
    m_currentFrame.rotation.rotation_count = 0;
    m_currentFrame.rotation.rotation_angle = 0;
    m_currentFrame.opacity.opacity = 0;

    m_repeat = false;
    m_start_frame = 0;
    m_end_frame = 0;
//    m_active = false;
}

CLayer::~CLayer()
{

}

bool CLayer::Initialize(void)
{
    return true;
}

void CLayer::Update(void)
{
    UpdateCurrentTime();
    UpdateCurrentFrame();
}

void CLayer::Render(void)
{

}

void CLayer::CloseUp(void)
{

}

void CLayer::SetFirstFrame(double ax, double ay, double px, double py, double sx, double sy, double rc, double ra, double op)
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

//bool
void CLayer::AddKeyFrame(const int type, long frameCount, double v1, double v2)
{
    m_bEnableKeyFrame[type] = true;
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        if (false == m_keyFrame[type][i].isEnabled)
        {
            m_keyFrame[type][i].isEnabled = true;
            m_keyFrame[type][i].frameCount = frameCount;
            m_keyFrame[type][i].value.x = v1;
            m_keyFrame[type][i].value.y = v2;
            break;
        }
    }
}


void CLayer::UpdateCurrentFrame(void)
{
    KEYFRAME_VALUE pv, nv;
    //TYPE_ANCHORPOINT
    if (true == m_bEnableKeyFrame[TYPE_ANCHORPOINT])
    {
        if ( (true == GetPreviousKeyFrame(TYPE_ANCHORPOINT, pv))
         && (true == GetNextKeyFrame(TYPE_ANCHORPOINT, nv)) )
         {
            if (pv.value.x != nv.value.x)
            {
                m_currentFrame.anchorPoint.x = pv.value.x + 1.0 * (m_frameCount - pv.frameCount) \
                *(nv.value.x - pv.value.x)/(nv.frameCount - pv.frameCount);
            }
            if (pv.value.y != nv.value.y)
            {
                m_currentFrame.anchorPoint.y = pv.value.y + 1.0 * (m_frameCount - pv.frameCount) \
                *(nv.value.y - pv.value.y)/(nv.frameCount - pv.frameCount);
            }
         }
    }

    //TYPE_POSITION
    if (true == m_bEnableKeyFrame[TYPE_POSITION])
    {
        if ( (true == GetPreviousKeyFrame(TYPE_POSITION, pv))
         && (true == GetNextKeyFrame(TYPE_POSITION, nv)) )
         {
            if (pv.value.x != nv.value.x)
            {
                m_currentFrame.position.x = pv.value.x + (m_frameCount - pv.frameCount) \
                *(nv.value.x - pv.value.x)/(nv.frameCount - pv.frameCount);
            }
            if (pv.value.y != nv.value.y)
            {
                m_currentFrame.position.y = pv.value.y + (m_frameCount - pv.frameCount) \
                *(nv.value.y - pv.value.y)/(nv.frameCount - pv.frameCount);
            }
         }
    }
    //TYPE_SCALE
     if (true == m_bEnableKeyFrame[TYPE_SCALE])
    {
        if ( (true == GetPreviousKeyFrame(TYPE_SCALE, pv))
         && (true == GetNextKeyFrame(TYPE_SCALE, nv)) )
         {
            if (pv.value.x != nv.value.x)
            {
                m_currentFrame.scale.x = pv.value.x + (m_frameCount - pv.frameCount) \
                *(nv.value.x - pv.value.x)/(nv.frameCount - pv.frameCount);
            }
            if (pv.value.y != nv.value.y)
            {
                m_currentFrame.scale.y = pv.value.y + (m_frameCount - pv.frameCount) \
                *(nv.value.y - pv.value.y)/(nv.frameCount - pv.frameCount);
            }
         }
    }
    //TYPE_ROTATION
    if (true == m_bEnableKeyFrame[TYPE_ROTATION])
    {
        if ( (true == GetPreviousKeyFrame(TYPE_ROTATION, pv))
         && (true == GetNextKeyFrame(TYPE_ROTATION, nv)) )
         {
             double pa = pv.value.rotation_count*360 + pv.value.rotation_angle;
             double na = nv.value.rotation_count*360 + nv.value.rotation_angle;
             double ta;
            if (pa != na)
            {
                ta = pa + (m_frameCount - pv.frameCount) * (na - pa) /(nv.frameCount - pv.frameCount);
                m_currentFrame.rotation.rotation_count = (int)ta/ 360;
                m_currentFrame.rotation.rotation_angle = ta - 360 * m_currentFrame.rotation.rotation_count;
            }
         }
    }
    //TYPE_OPACITY
    if (true == m_bEnableKeyFrame[TYPE_OPACITY])
    {
        if ( (true == GetPreviousKeyFrame(TYPE_OPACITY, pv))
         && (true == GetNextKeyFrame(TYPE_OPACITY, nv)) )
         {
            if (pv.value.opacity != nv.value.opacity)
            {
                m_currentFrame.opacity.opacity = pv.value.opacity + (m_frameCount - pv.frameCount) \
                *(nv.value.opacity - pv.value.opacity)/(nv.frameCount - pv.frameCount);
            }
         }
    }
}

void CLayer::UpdateCurrentTime(void)
{
    if (m_frameCount >= m_end_frame)
    {
        if (true == m_repeat)
        {
            m_frameCount = m_start_frame;
        }
    }
    else
    {
        m_frameCount++;
    }
}

bool CLayer::GetPreviousKeyFrame(const int type, KEYFRAME_VALUE& value)
{
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        if (false == m_keyFrame[type][i].isEnabled)
        {
            break;
        }
        if (m_keyFrame[type][i].frameCount >= m_frameCount)
        {
            if (i > 0)
            {
                value = m_keyFrame[type][i-1];
                //cout << "dubug: true for get previous key frame:" << i-1 << endl;
                return true;
            }
            else
            {
                break;
            }
        }
    }
    ///cout << "dubug: false for get previous key frame" << endl;
    return false;
}

bool CLayer::GetNextKeyFrame(const int type, KEYFRAME_VALUE& value)
{
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        if (false == m_keyFrame[type][i].isEnabled)
        {
            break;
        }
        if (m_keyFrame[type][i].frameCount >= m_frameCount)
        {
            value = m_keyFrame[type][i];
            //cout << "dubug: true for get next key frame:" << i << endl;
            return true;
        }
    }
    //cout << "dubug: false for get next key frame" << endl;
    return false;
}

void CLayer::ConvertFromClientToLocal(int cx, int cy, int& x, int& y)
{
    int xx, yy;
    double theta;
    xx = (cx - m_currentFrame.position.x) / m_currentFrame.scale.x * 100;
    yy = (cy - m_currentFrame.position.y) / m_currentFrame.scale.y * 100;
    if (0 != xx && 0 != yy)
    {
        theta = atan(1.0 * yy / xx);
        x = xx * cos(-m_currentFrame.rotation.rotation_angle*PI/180+ theta) / cos(theta) + m_currentFrame.anchorPoint.x;
        y = yy * sin(-m_currentFrame.rotation.rotation_angle*PI/180+ theta) / sin(theta) + m_currentFrame.anchorPoint.y;
    }
    else if (0 == xx)
    {
        x = yy * sin(-m_currentFrame.rotation.rotation_angle*PI/180) + m_currentFrame.anchorPoint.x;
        y = yy * cos(-m_currentFrame.rotation.rotation_angle*PI/180) + m_currentFrame.anchorPoint.y;
    }
    else
    {
        x = xx * cos(-m_currentFrame.rotation.rotation_angle*PI/180) + m_currentFrame.anchorPoint.x;
        y = -xx * sin(-m_currentFrame.rotation.rotation_angle*PI/180) + m_currentFrame.anchorPoint.y;
    }
}

void CLayer::ConvertFromLocalToClient(int lx, int ly, int& x, int& y)
{

}

