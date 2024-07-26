#include <pch.hpp>
#include "util/lua_util.hpp"

void Game::manipulate(float dt, sol::state& L)
{
	for (auto& m : mNewManipulators)
	{
		Manipulator* man{ std::move(m) };
		mManipulators.emplace_back(std::move(man));
		man = nullptr;
		m = nullptr;
	}
	mNewManipulators.clear();
	mNewManipulators.shrink_to_fit();
	for (auto& m : mManipulators)
	{
		if (m->update(dt))
		{
			if (m->dyno->dType == DynamicType::BusterShot_Normal)
			{
			
				
				L["IssueNextHorizTask"](m->dyno, dynamic_cast<DynBullet*>(m->dyno)->maxDist, m->dyno->pos.y);
				//L["IssueNextHorizTask"]( &m->dyno, dynamic_cast<DynBullet*>(m->dyno)->maxDist, m->dyno->pos.y);

				//lua_getglobal(L, "IssueNextHorizTask");
				//if (L, lua_isfunction(L, -1))
				//{
				//	lua_pushlightuserdata(L, this);
				//	lua_pushlightuserdata(L, m->dyno);
				//	lua_pushnumber(L, dynamic_cast<DynBullet*>(m->dyno)->maxDist);
				//	lua_pushnumber(L, m->dyno->pos.y);
				//	if (!mylua::CheckLua(L, lua_pcall(L, 4, 1, 0)))
				//	{
				//		// script bad
				//	}
				//}
			}
			else
			{

				
					L["loopFlyPad"]();

				//	L["IssueNextTask"](m->dyno, dynamic_cast<DynBullet*>(m->dyno)->maxDist, m->dyno->pos.y);


	
				
			

				

			/*	sol::protected_function func = L["IssueNextTask"];
				if (func.valid())
				{

				}
				else
				{



				}*/

				//lua_getglobal(L, "IssueNextTask");
				//if (L, lua_isfunction(L, -1))
				//{
				//	lua_pushlightuserdata(L, this);
				//	lua_pushlightuserdata(L, m->dyno);
				//	if (!mylua::CheckLua(L, lua_pcall(L, 2, 1, 0)))
				//	{
				//		// script bad
				//	}
				//}
			}
		}
	}


	cleanupManipluators(mManipulators);

	//bool found = false;
	//auto it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool { if (m->complete == true) found = true; return found; });
	//return found;

	//bool found = false;
	//	 if (found)
	//	{
	//		delete (*it);
	//		*it = nullptr;
	//		mManipulators.erase(it);
	//		mManipulators.shrink_to_fit();

	//		it = std::find_if(mManipulators.begin(), mManipulators.end(), [&found](Manipulator* m)->bool  { if (m->complete == true) found = true; return found; });
	//	}
	//std::erase_if(mManipulators, [](Manipulator* m)
		//{ return m->complete; });
}


Game::ManInterpPos::ManInterpPos(Dynamic* obj, float x, float y, float time)
	: elapsed{ 0.f }
{
	dyno = obj;
	startPos = dyno->pos;
	targetPos = { x, y };
	completionTime = time;

}

bool Game::ManInterpPos::update(float dt)
{
	elapsed += dt;
	dyno->pos = { (targetPos.x - startPos.x) * (elapsed / completionTime) + startPos.x, (targetPos.y - startPos.y) * (elapsed / completionTime) + startPos.y };

	if (elapsed >= completionTime)
	{
		dyno->pos = targetPos;
		complete = true;
	}

	return complete;
}