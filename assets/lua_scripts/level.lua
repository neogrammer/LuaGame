

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

			if c == '.' then cpp_setTile(host, x-1, y-1, 0)
			end
			if c == '#' then cpp_setTile(host, x-1, y-1, 1)
			end


			if c == 'Q' then cpp_setTile(host, x-1, y-1, 2)
			end
			if c == 'W' then cpp_setTile(host, x-1, y-1, 3)
			end
			
			if c == 'E' then cpp_setTile(host, x-1, y-1, 4)
			end
			if c == 'L' then cpp_setTile(host, x-1, y-1, 5)
			end

			if c == 'R' then cpp_setTile(host, x-1, y-1, 6)

			end
			if c == 'A' then cpp_setTile(host, x-1, y-1, 7)

			end
			if c == 'S' then cpp_setTile(host, x-1, y-1, 8)

			end
			if c == 'D' then cpp_setTile(host, x-1, y-1, 9)

			end
		end
		end
	end
	--PlayerObject = cpp_createDynamicObject(host, 0, 100.0, 40.0)
