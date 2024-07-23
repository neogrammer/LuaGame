
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

 local dynamics = {}

function DynamicBehavior1(host, dyno)
	while true do
		_MoveObject(host, dyno, 40.0, 40.0, 5.0)
		coroutine.yield()
		_MoveObject(host, dyno, 40.0, 400.0, 5.0)
		coroutine.yield()
		_MoveObject(host, dyno, 400.0, 400.0, 5.0)
		coroutine.yield()
		_MoveObject(host, dyno, 400.0, 40.0, 5.0)
		coroutine.yield()
	end
end

function IssueNextTask(host, dyno)
	if coroutine.status(dynamics[dyno].behaviour) ~= 'dead' then
			coroutine.resume(dynamics[dyno].behaviour, host, dyno)
	end

end

function LoadLevel(host, level)

	map = ""
	size = {w=40, h=24}

	if level == 1 then
		map = 
		"........................................"..
		"........................................"..
		"........................................"..
		"..............................QWWWWWWWWW"..
		"............QWWE..............ASSS######"..
		"WWWWWE......A##R..................AS####"..
		"##SSSD.......A#R....................AS##"..
		"#R............LR......................L#"..
		"#R............LR......................L#"..
		"#R............LR......................L#"..
		"#R....QWE.....LR......................L#"..
		"#R....L##WWWWW#R......................L#"..
		"#R....ASSSSSSSSD......................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R....................................L#"..
		"#R..........QWWWE.....................L#"..
		"##WWWWWWWWWW#####WWWWWWWWWWWWWWWWWWWWW##"
	end

	cpp_loadLevel(host, size.w, size.h)

	for y = 1, size.h do
		for x = 1, size.w do
			c = string.sub(map, ((y - 1) * size.w + x), ((y - 1) * size.w + x) )

			if c == '.' then cpp_setTile(host, x-1, y-1, EMPTY)
			end
			if c == '#' then cpp_setTile(host, x-1, y-1, MID)
			end


			if c == 'Q' then cpp_setTile(host, x-1, y-1, TL)
			end
			if c == 'W' then cpp_setTile(host, x-1, y-1, T)
			end
			
			if c == 'E' then cpp_setTile(host, x-1, y-1, TR)
			end
			if c == 'L' then cpp_setTile(host, x-1, y-1, L)
			end

			if c == 'R' then cpp_setTile(host, x-1, y-1, R)

			end
			if c == 'A' then cpp_setTile(host, x-1, y-1, BL)

			end
			if c == 'S' then cpp_setTile(host, x-1, y-1, B)

			end
			if c == 'D' then cpp_setTile(host, x-1, y-1, BR)

			end
		end
		end
		
		PlayerObject = cpp_createDynamicObject(host, 0, 650.0, 460.0, 120.0, 160.0)
		cpp_assignPlayerControl(host, PlayerObject);
		
		BirdObject = cpp_createDynamicObject(host, 1, 650.0, 460.0, 220.0, 296.0)
		
		BulletObject = cpp_createDynamicObject(host, 2, 60.0, 500.0, 24.0, 18.0)
		dynamics[BulletObject] = {behaviour = coroutine.create(DynamicBehavior1) }
		IssueNextTask(host, BulletObject)
		return 1

end
