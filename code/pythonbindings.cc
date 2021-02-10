#pragma once
#include "pybind11/cast.h"
#include "pybind11/embed.h"
#include "pybind11/detail/class.h"
#include "pybind11/stl.h"
#include "pybind11/numpy.h"
#include "foundation/stdneb.h"
#include "pybind11/operators.h"

#include "graphicsfeature/properties/graphics.h"
#include "basegamefeature/managers/entitymanager.h"
#include "managers/playermanager.h"

using namespace Demo;

namespace Python
{
    namespace py = pybind11;

    PYBIND11_EMBEDDED_MODULE(con, m)
    {
        m.def("spawnCube", [](Math::point& p)
            {
                Game::EntityCreateInfo info;
                info.immediate = true;
                info.templateId = Game::GetTemplateId("MovingEntity/cube"_atm);
                Game::Entity entity = Game::CreateEntity(info);
                Game::SetProperty(entity, Game::GetPropertyId("WorldTransform"_atm), Math::translation(p.vec));
                return entity;
            });

        m.def("camZoom", [](float fov)
            {
                auto player = PlayerManager::Instance()->getPlayer();
                GraphicsFeature::Camera camera = Game::GetProperty<GraphicsFeature::Camera>(player, Game::GetPropertyId("Camera"_atm));

                camera.fieldOfView = fov;
                Game::SetProperty(player, Game::GetPropertyId("Camera"_atm), camera);
            });

        m.def("camPos", [](Math::point& p)
            {
                Demo::PlayerManager::Instance()->setPos(p);
            });
    }
} // namespace Python
