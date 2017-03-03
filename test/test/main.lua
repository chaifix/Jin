local jc = jin.core 
local je = jin.event
local jg = jin.graphics
local jk = jin.keyboard 
local jm = jin.mouse
local ja = jin.audio
local jf = jin.filesystem
local jn = jin.net
local jt = jin.time
local jd = jin.debug

local img = nil
local fnt = nil 
function jin.core.load() 
    jd.size(3)
    img = jg.Image("./img/icon.png")
    fnt = jg.Font("font.ttf")
    local w, h = fnt:box("nima", 16, 1, 20)
    jd.print("./main.lua:22: debug \n moduie is currently in use.")
    jd.print("./init.lua:13: init graphics subsystem successed.")
    jd.print("./main.lua:13: load subsystems.")
    jd.print("./main.lua:13: init \n games.")
end

local str = ""
function jin.core.onEvent(e)
    if e.type == "quit" then 
        jc.quit() 
    elseif e.type == "wheel" then 
        print(e.y)
    elseif e.type == "keydown" then 
        if e.key == "Escape" then 
            jc.quit()
        end
        if e.key == "Return" then 
            str = str .. '\n'
        elseif e.key == "Space" then 
            str = str .. ' '
        else 
            str = str .. e.key
        end
    end
end

local i = 0
function jin.core.onUpdate(dt)
    i = i + 0.01
    if i > 1 then 
        jin.debug.print(i)
        i = 0
    end 
end

local c = jg.Canvas(500, 500)
local r = 0

function jin.core.onDraw()

    r =r + 0.01
    jg.color()
    jg.circle("fill", 100, 400, 100* math.sin(r))
    img:setAnchor(20, 20)
    local s = 1 + 5 * math.abs(math.sin(r))
    jg.draw(img, 100, 400, s, s, math.cos(r))
    jg.draw(img, 300, 400, s, s, math.cos(r))
  --  jg.color(255, 0, 0, 255)
  --  jg.clear()
    jg.study()
    jg.bind(c)
        jg.clear(0, 0, 0, 0) 
        --jg.color(255,0,0,255)
        jg.write("This is a text test.", 100, 100, 16, 1, 20)
    jg.bind()
    jg.draw(c, 0, 0, 1, 1)

end
