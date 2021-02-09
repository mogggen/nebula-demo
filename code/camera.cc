//------------------------------------------------------------------------------
//  freecamerautil.cc
//  (C) 2012-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "render/stdneb.h"
#include "camera.h"

namespace RenderUtil
{
    using namespace Math;

    //------------------------------------------------------------------------------
    /**
    */
    TopDownCamera::TopDownCamera() :
                    //x  y  z
        defaultEyePos(0, 8, 0),
        defaultEyeVec(0, -1, 0),
        rotationSpeed(0.01f),
        moveSpeed(0.01f),
        cameraTransform(mat4()),
        rotateButton(false),
        accelerateButton(false),
        forwardsKey(false),
        backwardsKey(false),
        leftStrafeKey(false),
        rightStrafeKey(false),
        upKey(false),
        downKey(false)

    {
        // empty
    }

    //------------------------------------------------------------------------------
    /**
    */
    void
        TopDownCamera::Setup(Math::point defaultEyePos)
    {
        this->defaultEyePos = defaultEyePos;
        this->defaultEyeVec = (0, 0, 1);
        this->position = this->defaultEyePos;
        this->viewAngles.set(this->defaultEyeVec);
        this->Update();
    }

    void
        TopDownCamera::Setup(float height, float yaw, float pitch)
    {
        this->height = height;
        this->pitch = pitch;
        this->yaw = yaw;
        this->defaultEyePos = defaultEyePos;
        this->defaultEyeVec = (0, 0, 1);
        this->position = this->defaultEyePos;
        this->viewAngles.set(this->defaultEyeVec);
        this->Update();
    }

    //------------------------------------------------------------------------------
    /**
    */

    //------------------------------------------------------------------------------
    /** PVM tranlaste Scale rotate
    */
    void
        TopDownCamera::Update()
    {
        mat4 xMat = rotationx(pitch);
        mat4 yMat = rotationy(yaw);

        float currentMoveSpeed = moveSpeed;
        if (this->accelerateButton)
        {
            currentMoveSpeed *= 10;
        }
        vec4 translation = Math::normalize(vec4(
            rightStrafeKey - leftStrafeKey,
            0,
            backwardsKey - forwardsKey, 0)) * currentMoveSpeed;        

        translation = rotationy(-yaw) * -translation;
        this->position.x += translation.x;
        this->position.z += translation.z;
        float temp = height;
        float hypo = temp / Math::sin(pitch);
        if (this->viewAngles.theta > N_PI * 0.5F)
            hypo = temp / Math::sin(N_PI * 0.5F);
        this->cameraTransform = Math::translation(this->position.vec) * yMat * xMat * Math::translation(0, 0, -hypo);
    }


} // namespace RenderUtil