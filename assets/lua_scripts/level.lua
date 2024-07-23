

function LoadLevel(host, level)

	map = ""
	size = {w=16, h=15}

	if level == 1 then
		map = 
		"................"..
		"................"..
		"................"..
		"................"..
		".........#######"..
		"............####"..
		"######.......###"..
		"##.............#"..
		"##.............#"..
		"##.............#"..
		"##.....###.....#"..
		"################"..
		"................"..
		"................"..
		"................"
	end

	cpp_loadLevel(host, size.w, size.h)

	for y = 1, size.h do
		for x = 1, size.w do
			c = string.sub(map, ((y - 1) * size.w + x), ((y - 1) * size.w + x) )

			--if c == '.' then _SetTile(host, x-1, y-1, TILE_EMPTY)
			-- else if .. settile(TILE_BLOCK)
			--end
		end
	end

	return 1
end