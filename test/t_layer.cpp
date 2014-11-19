#include <iostream>
using namespace std;
#include "../CLayer.h"

/**
Show layer int 100x100 screen and it lasts 1 seconds.
start:
    (20,20)(50,20)(100,100)(0,0)(100)
keyframe:
    position:
        0f (50,20) -> 14f (50,50) -> 29f (20,50)
    opacity:
        0f (0) -> 13f (100)
    rotation:
        10f  (0, 0) -> 16f (1, 120) -> 20f (1, 200)
    scale:
        2f (100, 100) -> 7f (20, 30)

task:
    1. create an abstract layer with size of 40x40;
    2. add key frames
    3. start showing
*/
void t_layer(void)
{
    CLayer layer(40, 40);
    layer.SetFirstFrame(20, 20, 50, 20, 100, 100, 0, 0, 0);

    layer.AddKeyFrame(TYPE_POSITION, 0, 50, 20);
    layer.AddKeyFrame(TYPE_POSITION, 14, 50, 50);
    layer.AddKeyFrame(TYPE_POSITION, 29, 20, 50);
    layer.AddKeyFrame(TYPE_OPACITY, 0, 0);
    layer.AddKeyFrame(TYPE_OPACITY, 13, 100);
    layer.AddKeyFrame(TYPE_ROTATION, 10, 0, 0);
    layer.AddKeyFrame(TYPE_ROTATION, 16, 1, 120);
    layer.AddKeyFrame(TYPE_ROTATION, 20, 1, 200);
    layer.AddKeyFrame(TYPE_SCALE, 2, 100, 100);
    layer.AddKeyFrame(TYPE_SCALE, 7, 20, 30);


    long time;
    FRAME_VALUE fv;
    for (int i=0; i<2*FRAME_PER_SEC; i++)
    {
        layer.Update();

        layer.GetCurrentTime(time);
        layer.GetCurrentFrame(fv);
        cout << time << ":  ";
        cout << "(" << fv.anchorPoint.x << ", " << fv.anchorPoint.y << ")  ";
        cout << "(" << fv.position.x << ", " << fv.position.y << ")   ";
        cout << "(" << fv.scale.x << ", " << fv.scale.y << ")  ";
        cout << "(" << fv.rotation.rotation_count << ", " << fv.rotation.rotation_angle << ")  ";
        cout << "(" << fv.opacity.opacity << ")" << endl;
    }
}

int main()
{
    t_layer();
    return 0;
}


