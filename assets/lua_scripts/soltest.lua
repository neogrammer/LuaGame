a = 24
b = "hello"
c = "world"

player = {name="Justin", age=38, height=70.1}

function DoAThing(a, b)
	io.write("[LUA] DoAThing from cpp("..a..", "..b..") called \n")
	return a + 10
end

function DoAThing2(a, b)
	print("[LUA] DoAThing2("..a..", "..b..") called \n")
	c = cpp_DoAFunction(a + 10, b * 3)
	return c
end

function CreateTest1()
	io.write("[LUA S2] CreateTest1() called\n")

	local p = test:new()

	p.name = "Saladin"
	p.age = 44
	p.height = 65.7

	return p
end

function CreateTest2(n)
	io.write("[LUA S6] CreateTest2() called\n")

	allTests:clear()

	for i=1, n  do
		allTests:add(CreateTest1())
	end
end

