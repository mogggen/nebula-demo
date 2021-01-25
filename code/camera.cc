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
        defaultEyePos(0, 0, 0),
        defaultEyeVec(0, 0, 1),
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
        TopDownCamera::Setup(Math::point defaultEyePos, float height, float yaw, float pitch)
    {
        defaultEyePos.y = height; //set custom height from 1.2
        this->defaultEyePos = defaultEyePos;
        this->defaultEyeVec = (0, -1, 0);
        this->position = this->defaultEyePos;
        this->viewAngles.set(this->defaultEyeVec);
        this->Update();
    }

    //------------------------------------------------------------------------------
    /**
    */

    //------------------------------------------------------------------------------
    /**
    */
    void
        TopDownCamera::Update()
    {
        if (this->rotateButton)
        {
            this->viewAngles.rho += this->mouseMovement.x * rotationSpeed;
            this->viewAngles.theta += this->mouseMovement.y * rotationSpeed;
        }

        mat4 xMat = rotationx(this->viewAngles.theta - N_PI * .5f);
        mat4 yMat = rotationy(this->viewAngles.rho);
        this->cameraTransform = xMat;
        this->cameraTransform = this->cameraTransform * yMat;

        float currentMoveSpeed = moveSpeed;
        if (this->accelerateButton)
        {
            currentMoveSpeed *= 20;
        }
        vec4 translation = vec4(0, 0, 0, 0);
        if (forwardsKey)
        {
            translation.z -= currentMoveSpeed;
        }
        if (backwardsKey)
        {
            translation.z += currentMoveSpeed;
        }
        if (rightStrafeKey)
        {
            translation.x += currentMoveSpeed;
        }
        if (leftStrafeKey)
        {
            translation.x -= currentMoveSpeed;
        }
        if (upKey)
        {
            translation.y += currentMoveSpeed;
        }
        if (downKey)
        {
            translation.y -= currentMoveSpeed;
        }

        //translation = this->cameraTransform * translation;
        this->position += xyz(translation);

        this->cameraTransform.position = point(this->position);
    }


} // namespace RenderUtil