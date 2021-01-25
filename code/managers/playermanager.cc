//------------------------------------------------------------------------------
//  playermanager.cc
//  (C) 2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "application/stdneb.h"
#include "playermanager.h"
#include "input/inputserver.h"
#include "graphics/cameracontext.h"
#include "visibility/visibilitycontext.h"
#include "imgui.h"
#include "dynui/im3d/im3dcontext.h"
#include "graphicsfeature/graphicsfeatureunit.h"
#include "basegamefeature/managers/entitymanager.h"
#include "input/mouse.h"
#include "renderutil/mouserayutil.h"
#include "game/api.h"

namespace Demo
{

__ImplementSingleton(PlayerManager)

//------------------------------------------------------------------------------
/**
*/
Game::ManagerAPI
PlayerManager::Create()
{
    n_assert(!PlayerManager::HasInstance());
    Singleton = n_new(PlayerManager);

    Game::ManagerAPI api;
    api.OnActivate = &PlayerManager::OnActivate;
    api.OnBeginFrame = &PlayerManager::OnBeginFrame;
    api.OnFrame = &PlayerManager::OnFrame;
    return api;
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::Destroy()
{
    n_assert(PlayerManager::HasInstance());
    n_delete(Singleton);
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::OnActivate()
{
    auto view = GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultView();
    auto stage = GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultStage();

    auto const windowId = Base::DisplayDeviceBase::Instance()->GetMainWindow();
    auto const displayMode = CoreGraphics::WindowGetDisplayMode(windowId);
    SizeT width = displayMode.GetWidth();
    SizeT height = displayMode.GetHeight();

    Game::EntityCreateInfo playerCreateInfo;
    playerCreateInfo.templateId = Game::GetTemplateId("Player/player"_atm);
    playerCreateInfo.immediate = true;

    struct TopDownCamConfig
    {
        float height;
        float yaw;
        float pitch;
    };

    Singleton->playerEntity = Game::CreateEntity(playerCreateInfo);

    GraphicsFeature::Camera camera = Game::GetProperty<GraphicsFeature::Camera>(Singleton->playerEntity, Game::GetPropertyId("Camera"_atm));
    TopDownCamConfig topDownCamConfig = Game::GetProperty<TopDownCamConfig>(Singleton->playerEntity, Game::GetPropertyId("TopDownCamConfig"_atm)); //get player.json values for input.nidl
    camera.aspectRatio = (float)width / (float)height;
    camera.viewHandle = GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultViewHandle();
    Game::SetProperty<GraphicsFeature::Camera>(Singleton->playerEntity, Game::GetPropertyId("Camera"_atm), camera);

    Singleton->topDownCam.Setup(Math::point(0, topDownCamConfig.height, 0), 0, -1, 0);

    GraphicsFeature::GraphicsFeatureUnit::Instance()->AddRenderUICallback([]()
    {
        //static Math::line ray;
        //if (Input::InputServer::Instance()->GetDefaultMouse()->ButtonPressed(Input::MouseButton::Code::RightButton))
        //{
        //    const Math::mat4 proj = Singleton->camera.GetProjectionMatrix();
        //    ray = RenderUtil::MouseRayUtil::ComputeWorldMouseRay(
        //        Input::InputServer::Instance()->GetDefaultMouse()->GetScreenPosition(),
        //        1000.0f,
        //        Math::inverse(Singleton->camera.view),
        //        Math::inverse(proj),
        //        0.1f
        //    );
        //}
        //Im3d::Im3dContext::DrawLine(ray, 2.0f, { 1.0f, 0.3f, 0.0f, 1.0f });
    });
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::OnBeginFrame()
{
    auto& io = ImGui::GetIO();
    if (!ImGui::GetIO().WantCaptureMouse)
    {
        Singleton->topDownCam.SetForwardsKey(io.KeysDown[Input::Key::W]);
        Singleton->topDownCam.SetBackwardsKey(io.KeysDown[Input::Key::S]);
        Singleton->topDownCam.SetRightStrafeKey(io.KeysDown[Input::Key::D]);
        Singleton->topDownCam.SetLeftStrafeKey(io.KeysDown[Input::Key::A]);
        Singleton->topDownCam.SetUpKey(io.KeysDown[Input::Key::Q]);
        Singleton->topDownCam.SetDownKey(io.KeysDown[Input::Key::E]);
        Singleton->topDownCam.SetMouseMovement({ -io.MouseDelta.x, -io.MouseDelta.y });
        Singleton->topDownCam.SetAccelerateButton(io.KeyShift);
        Singleton->topDownCam.SetRotateButton(io.MouseDown[Input::MouseButton::RightButton]);
        Singleton->topDownCam.SetMovementSpeed(0.1f);
        Singleton->topDownCam.Update();
    }

    //Math::mat4 worldTransform = Game::GetProperty(Singleton->playerEntity, Game::GetPropertyId("WorldTransform"_atm));
    Game::SetProperty<Math::mat4>(Singleton->playerEntity, Game::GetPropertyId("WorldTransform"_atm), Singleton->topDownCam.GetTransform());
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::OnFrame()
{
    
}

//------------------------------------------------------------------------------
/**
*/
PlayerManager::PlayerManager()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
PlayerManager::~PlayerManager()
{
    // empty
}

} // namespace Game


