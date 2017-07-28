--[[ 
    program entry
]]  

local function _onEvent(e) 
    -- update keyboard status 
    if e.type == "keydown" then 
        jin.keyboard.set(e.key, true) 
    elseif e.type == "keyup" then 
        jin.keyboard.set(e.key, false)
    end 

    -- call user onEvent function 
    if jin.core.onEvent then 
        jin.core.onEvent(e) 
    end
end 

-------------------------------------------------
-- init file system 
-------------------------------------------------
jin._argv[2] = jin._argv[2] or '.'
jin.filesystem.init()
jin.filesystem.mount(jin._argv[2])

-- config
local conf = {} 
if jin.filesystem.exist("config.lua") then 
	conf = require "config"	
end 
conf.width = conf.width or 600 
conf.height = conf.height or 500 
conf.fps = conf.fps or 60
conf.title = conf.title or ("jin v" .. jin.version())

-- init video subsystem 
jin.graphics.init(conf.width,conf.height,conf.title)

-- open debug mode, must after jin.graphics.init
if jin._argv[3] == '-d' then 
	jin.debug.init()
end

function jin.core.run()
    local now = jin.time.second()
    local last = now
    local fsec = 1/conf.fps
    -- for loading resources
    if jin.core.load then 
        jin.core.load() 
    end
    while(jin.core.running()) do
        -- frame controle
        last = now
        now = jin.time.second()
        if (now - last) < fsec then 
            jin.time.sleep(fsec - now + last)
        end

        -- handle events     
        for _, e in pairs(jin.event.poll()) do 
            if _onEvent then
                _onEvent(e)
            end
        end

        -- update
        local dt = now - last
        if dt < fsec then 
            dt = fsec 
        end
        if jin.core.onUpdate then
            jin.core.onUpdate(dt)
        end
        
		-- bind to default render buffer 
		jin.graphics.bind() 
		jin.graphics.clear() 
		jin.graphics.color()
		jin.graphics.study()

		-- custom drawing
		if jin.core.onDraw then 
            jin.core.onDraw() 
        end
		
		-- render debug window
		if jin.debug.status() then 
			jin.debug.render()
		end 		

        -- swap window buffer 
        jin.graphics.present()

    end
end

local function onError(msg) 
	local tab = '    '
	print("Error:\n" .. msg)
	function jin.core.onEvent(e) 
		if e.type == 'quit' then 
			jin.core.quit()
		end
	end
	local ww, wh = jin.graphics.size() 
	function jin.core.onDraw() 
		jin.graphics.write("Error: ", 10, 10, 30, 3, 30)
		jin.graphics.write(msg, 10, 50) 
	end
end

if jin.filesystem.exist("main.lua") then 
	-- require main game script
	xpcall(function() require"main" end, onError)
	jin.core.run()
else 
	-- no game 
	function jin.core.onEvent(e) 
		if e.type == 'quit' then 
			jin.core.quit()
		end
	end
	function jin.core.onDraw() 
		jin.graphics.clear(111, 134, 125, 255) 
		local ww, wh = jin.graphics.size() 
		local fw, fh = jin.graphics.box("no game", 20, 1, 20)
		jin.graphics.write("no game", ww /2 - fw / 2, wh * 2/3, 16, 1, 18)
	end
	jin.core.run()
end
