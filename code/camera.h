#pragma once
#include "application/stdneb.h"
#include "math/mat4.h"
#include "math/vec2.h"
#include "math/polar.h"
#include "math/scalar.h"

//------------------------------------------------------------------------------
namespace RenderUtil
{
    class TopDownCamera
    {
    public:
        TopDownCamera();

        void Setup(Math::point Pos);
        /// updates camera matrix
        void Update();
        /// gets camera transform
        const Math::mat4& GetTransform() const;

        /// sets the state of the rotate button
        void SetRotateButton(bool state);
        /// sets the state of the accelerate button
        void SetAccelerateButton(bool state);
        /// sets the mouse movement
        void SetMouseMovement(Math::vec2 movement);
        /// sets the rotation speed
        void SetRotationSpeed(float speed);
        /// sets the movement speed
        void SetMovementSpeed(float speed);

        /// sets the forward movement key
        void SetForwardsKey(bool state);
        /// sets the backward movement key
        void SetBackwardsKey(bool state);
        /// sets the left strafe key
        void SetLeftStrafeKey(bool state);
        /// sets the right strafe key
        void SetRightStrafeKey(bool state);
        /// sets the up movement key
        void SetUpKey(bool state);
        /// sets the down movement key
        void SetDownKey(bool state);

        float*
            getHeigthPtr();

    private:
        Math::point defaultEyePos;
        Math::vector defaultEyeVec;
        Math::vec2 mouseMovement;

        Math::polar viewAngles;
        Math::point position;
        Math::mat4 cameraTransform;

        float rotationSpeed;
        float moveSpeed;
        
        float height;

        bool rotateButton;
        bool accelerateButton;

        bool forwardsKey;
        bool backwardsKey;
        bool leftStrafeKey;
        bool rightStrafeKey;
        bool upKey;
        bool downKey;
    };
    inline const Math::mat4&
        TopDownCamera::GetTransform() const
    {
        return this->cameraTransform;
    }
    inline void
        TopDownCamera::SetRotateButton(bool state)
    {
        this->rotateButton = state;
    }
    inline void
        TopDownCamera::SetAccelerateButton(bool state)
    {
        this->accelerateButton = state;
    }
    inline void
        TopDownCamera::SetMouseMovement(Math::vec2 movement)
    {
        this->mouseMovement = movement;
    }

    inline float*
        TopDownCamera::getHeigthPtr()
    {
        return &this->height;
    }
    inline void
        TopDownCamera::SetRotationSpeed(float speed)
    {
        this->rotationSpeed = speed;
    }
    inline void
        TopDownCamera::SetMovementSpeed(float speed)
    {
        this->moveSpeed = speed;
    }
    inline void
        TopDownCamera::SetForwardsKey(bool state)
    {
        this->forwardsKey = state;
    }
    inline void
        TopDownCamera::SetBackwardsKey(bool state)
    {
        this->backwardsKey = state;
    }
    inline void
        TopDownCamera::SetLeftStrafeKey(bool state)
    {
        this->leftStrafeKey = state;
    }
    inline void
        TopDownCamera::SetRightStrafeKey(bool state)
    {
        this->rightStrafeKey = state;
    }
    inline void
        TopDownCamera::SetUpKey(bool state)
    {
        this->upKey = state;
    }
    inline void
        TopDownCamera::SetDownKey(bool state)
    {
        this->downKey = state;
    }
}