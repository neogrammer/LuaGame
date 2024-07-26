
local EMPTY = 0
local MID = 1
local TL = 2
local T = 3
local TR = 4
local L = 5
local R = 6
local BL = 7
local B = 8
local BR = 9

local Player = 0
local Bird = 1
local BusterNormal = 2
local Platform = 3
 local dynamics = {DynamicBehaviour1, HorizontalBehaviour}
 local obj
function DynamicBehaviour1(dyno)
	while true do
		cpp_moveObject( dyno, 40.0, 40.0, 5.0)
		coroutine.yield()
		cpp_moveObject(dyno, 40.0, 400.0, 5.0)
		coroutine.yield()
		cpp_moveObject( dyno, 400.0, 400.0, 5.0)
		coroutine.yield()
		cpp_moveObject(dyno, 400.0, 40.0, 5.0)
		coroutine.yield()
	end
end

function HorizontalBehaviour(dyno, maxd, posy)
	print("[LUA] Issueing task for bullet \n")	
		cpp_moveObject(dyno, maxd, posy, 1.0)
end

function IssueNextTask( dyno)
	if coroutine.status(dynamics[dyno].behaviour) ~= 'dead' then
			coroutine.resume(dynamics[dyno].behaviour, dyno)
	end

end

function IssueNextHorizTask(dyno, maxd, posy)
	io.write("about to check the status of a coroutine")
	if coroutine.status(dynamics[dyno].behaviour) ~= 'dead' then
			io.write("Trying to resume coroutine for bullet")
			coroutine.resume(dynamics[dyno].behaviour, dyno, maxd, posy)
end

end

function loopFlyPad()
	io.write("Attempt to kick the coroutine")
	IssueNextTask(Platform)
end

function loop()
	while counter ~= 30
		do
			coroutine.yield(counter);
			counter = counter + 1;
		end
		return counter
end

function LoadLevel(level)

	map = ""
	size = {w=40, h=24}

	cpp_loadLevel(size.w, size.h, level)

		
		PlayerObject = cpp_createDynamicObject(0, 650.0, 460.0, 120.0, 160.0, 0)
		cpp_assignPlayerControl(PlayerObject);
		
		BirdObject = cpp_createDynamicObject( 1, 650.0, 460.0, 220.0, 296.0, 0)
		
		BulletObject = cpp_createDynamicObject( 2, 600.0, 600.0, 24.0, 18.0, 1)
		dynamics[BulletObject] = {behaviour = coroutine.create(HorizontalBehaviour) }
		IssueNextHorizTask( BulletObject, 600.0 + 1280.0 * -1.0 , 600.0)


		Platform = cpp_createDynamicObject( 3, 600.0, 600.0, 67.0, 40.0, 0)
		dynamics[Platform] = {behaviour = coroutine.create(DynamicBehaviour1) }
		IssueNextTask( Platform)
	


		
		return 1

end
