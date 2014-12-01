#include "CLayer.h"
#include <cmath>
#include <iostream>
using namespace std;

CLayer::CLayer()
    :m_width(0),
    m_height(0),
    m_frameCount(0),
    m_repeat(false),
    m_start_frame(0),
    m_end_frame(0),
    m_show(false),
    m_active(false)
{
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        m_keyFrame[i].isEnabled = false;
    }
}

CLayer::CLayer(int width, int height)
    :m_width(width),
    m_height(height),
    m_frameCount(0),
    m_repeat(false),
    m_start_frame(0),
    m_end_frame(0),
    m_show(false),
    m_active(false)

{
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        m_keyFrame[i].isEnabled = false;
    }
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
    if (true == m_active)
    {
        UpdateCurrentTime();
        UpdateCurrentFrame();
    }
}

void CLayer::Render(void)
{

}

void CLayer::CloseUp(void)
{

}

void CLayer::AddKeyFrame(long frameCount, double ax, double ay, double px, double py, double sx, double sy, int rc, double ra, double op)
{
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        if (false == m_keyFrame[i].isEnabled)
        {
            m_keyFrame[i].isEnabled = true;
            m_keyFrame[i].frameCount = frameCount;
            m_keyFrame[i].value.ax = ax;
            m_keyFrame[i].value.ay = ay;
            m_keyFrame[i].value.px = px;
            m_keyFrame[i].value.py = py;
            m_keyFrame[i].value.sx = sx;
            m_keyFrame[i].value.sy = sy;
            m_keyFrame[i].value.rc = rc;
            m_keyFrame[i].value.ra = ra;
            m_keyFrame[i].value.op = op;
            break;
        }
    }
}


void CLayer::UpdateCurrentFrame(void)
{
    KEYFRAME_VALUE pv, nv;

    if ( true == GetPreAndNextKeyFrame(pv, nv) )
    {
        if (pv.value.ax != nv.value.ax) {
            m_currentFrame.ax = pv.value.ax + 1.0 * (m_frameCount - pv.frameCount) \
            *(nv.value.ax - pv.value.ax)/(nv.frameCount - pv.frameCount);
        }
        if (pv.value.ay != nv.value.ay) {
            m_currentFrame.ay = pv.value.ay + 1.0 * (m_frameCount - pv.frameCount) \
            *(nv.value.ay - pv.value.ay)/(nv.frameCount - pv.frameCount);
        }
       if (pv.value.px != nv.value.px)
        {
            m_currentFrame.px = pv.value.px + (m_frameCount - pv.frameCount) \
            *(nv.value.px - pv.value.px)/(nv.frameCount - pv.frameCount);
        }
        if (pv.value.py != nv.value.py)
        {
            m_currentFrame.py = pv.value.py + (m_frameCount - pv.frameCount) \
            *(nv.value.py - pv.value.py)/(nv.frameCount - pv.frameCount);
        }
        if (pv.value.sx != nv.value.sx)
        {
            m_currentFrame.sx = pv.value.sx + (m_frameCount - pv.frameCount) \
            *(nv.value.sx - pv.value.sx)/(nv.frameCount - pv.frameCount);
        }
        if (pv.value.sy != nv.value.sy)
        {
            m_currentFrame.sy = pv.value.sy + (m_frameCount - pv.frameCount) \
            *(nv.value.sy - pv.value.sy)/(nv.frameCount - pv.frameCount);
        }
        double pa = pv.value.rc*360 + pv.value.ra;
        double na = nv.value.rc*360 + nv.value.ra;
        double ta;
        if (pa != na)
        {
            ta = pa + (m_frameCount - pv.frameCount) * (na - pa) /(nv.frameCount - pv.frameCount);
            m_currentFrame.rc = (int)ta/ 360;
            m_currentFrame.ra = ta - 360 * m_currentFrame.rc;
        }
        if (pv.value.op != nv.value.op)
        {
            m_currentFrame.op = pv.value.op + (m_frameCount - pv.frameCount) \
            *(nv.value.op - pv.value.op)/(nv.frameCount - pv.frameCount);
        }
    }
    else
    {
        m_currentFrame = m_keyFrame[0].value;
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
        else
        {
            m_active = false;
        }
    }
    else
    {
        m_frameCount++;
    }
}

bool CLayer::GetPreAndNextKeyFrame(KEYFRAME_VALUE& pv, KEYFRAME_VALUE& nv)
{
    for (int i=0; i<MAX_NUM_KEYFRAME; i++)
    {
        if (false == m_keyFrame[i].isEnabled)
        {
            break;
        }
        if (m_keyFrame[i].frameCount > m_frameCount)
        {
            nv = m_keyFrame[i];
            if (i > 0)
            {
                pv = m_keyFrame[i-1];
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (m_keyFrame[i].frameCount == m_frameCount)
        {
            nv = m_keyFrame[i];
            pv = m_keyFrame[i];
            return true;
        }
        else
        {
            //..
        }
    }
    return false;
}

void CLayer::ConvertFromClientToLocal(int cx, int cy, int& x, int& y)
{
    int xx, yy;
    double theta;
    xx = (cx - m_currentFrame.px) / m_currentFrame.sx * 100;
    yy = (cy - m_currentFrame.py) / m_currentFrame.sy * 100;
    if (0 != xx && 0 != yy)
    {
        theta = atan(1.0 * yy / xx);
        x = xx * cos(-m_currentFrame.ra*PI/180+ theta) / cos(theta) + m_currentFrame.ax;
        y = yy * sin(-m_currentFrame.ra*PI/180+ theta) / sin(theta) + m_currentFrame.ay;
    }
    else if (0 == xx)
    {
        x = yy * sin(-m_currentFrame.ra*PI/180) + m_currentFrame.ax;
        y = yy * cos(-m_currentFrame.ra*PI/180) + m_currentFrame.ay;
    }
    else
    {
        x = xx * cos(-m_currentFrame.ra*PI/180) + m_currentFrame.ax;
        y = -xx * sin(-m_currentFrame.ra*PI/180) + m_currentFrame.ay;
    }
}

void CLayer::ConvertFromLocalToClient(int lx, int ly, int& x, int& y)
{

}

