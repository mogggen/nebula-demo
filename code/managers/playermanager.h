#pragma once
//------------------------------------------------------------------------------
/**
	@class	Demo::PlayerManager

	(C) 2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/refcounted.h"
#include "core/singleton.h"
#include "game/manager.h"
#include "util/stringatom.h"
#include "renderutil/freecamerautil.h"
#include "camera.h"
#include "game/entity.h"
#include "properties/input.h"

namespace Demo
{

class PlayerManager
{
	__DeclareSingleton(PlayerManager);
public:
	/// Create the singleton
	static Game::ManagerAPI Create();

	/// Destroy the singleton
	static void Destroy();
	Game::Entity getPlayer()
	{
		return playerEntity;
	}
private:
	/// constructor
	PlayerManager();
	/// destructor
	~PlayerManager();
	

	/// called when attached to game server.
	static void OnActivate();
    /// called once before every rendered frame
    static void OnBeginFrame();
	/// called once every frame
	static void OnFrame();

	Game::Entity playerEntity;
	
	//RenderUtil::FreeCamUtil freeCamUtil;
	RenderUtil::TopDownCamera topDownCam;
};

} // namespace Demo
