--[[ 
    for debug purpose 
    +-------------------+
    |debug msg old      |
    |...                |
    |...                |
    |...                |
    |debug msg new      |
    +-------------------+
]] 

jin.debug = jin.debug or {} 

-- render panel 
local panel = nil 

local debug = false

-- debug msg buffer 
local buffer = {} 

-- configure 
local bsize   = 10
local fsize   = 15
local lheight = 18
local alpha   = 220
local margin  = 10

-- refresh buffer or not 
local refresh = true 

function jin.debug.init()
    debug = true
	panel = jin.graphics.Canvas(jin.graphics.size()) 
end

-- set buffer size 
function jin.debug.size(c)
	bsize = c
end 

function jin.debug.print(msg)
	if not debug then return end 

	msg = tostring(msg)
	local tp = type(msg)
	if tp ~= "string" and tp ~= "number" then 
		msg = string.format("print failed, expect string or number but get a %s", tp)
	end
	
    -- remove the first one (old msg)
	if #buffer >= bsize then 
		table.remove(buffer, 1)
	end 
    
    buffer[#buffer + 1] = msg
    refresh = true
end

-- clear debug buffer 
function jin.debug.clear()
	buffer = {} 
end

local function getStrHeight(str, lheight) 
	local h = lheight
	if #str == 0 then 
		h = 0
	end 
	for i = 1, #str do 
		local c = string.sub(str, i, i)
		if c == '\n' then 
			h = h + lheight
		end 
	end 
	return h 
end

local  function getBgQuad() 
	local width, height = 0, 0 	
	for i = 1, #buffer do
		local w, h = jin.graphics.box( buffer[i], fsize, 1, lheight)
		height = height + h 
		if width < w then
			width = w 
		end 
	end	
	return width, height
end 

-- render to screen
function jin.debug.render() 
    if not debug then return end
    
    if refresh then 
       
        jin.graphics.bind(panel)

            jin.graphics.clear(0, 0, 0, 0)
            
            jin.graphics.study()
            
            local ww, wh = jin.graphics.size()
            local bgw, bgh = getBgQuad()
            jin.graphics.color(0, 0, 0, alpha)
            jin.graphics.rect("fill", 0, wh - bgh - margin, bgw + margin, bgh + margin)
            
            jin.graphics.color()
            local y = wh 
            for i = #buffer, 1, -1 do
                local msg = buffer[i] 
                local h = getStrHeight(msg, lheight)
                y = y - h 
                jin.graphics.write(msg, margin / 2, y - margin/ 2, fsize, 1, lheight) 
            end
	
        jin.graphics.bind()
    
        refresh = false
    end 
    
    jin.graphics.color()
    jin.graphics.draw(panel, 0, 0)
end

function jin.debug.status() 
	return debug 
end
