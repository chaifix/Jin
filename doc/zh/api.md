jin v0.1.0 API 文档



jin.core = {} 
--------
jin.core.run() 
jin.core.onEvent(e)
jin.core.onUpdate(dt)
jin.core.onDraw() 

jin.core.getOS() 

e = 
{
    type: "keydown" or   -- 
          "keyup" or     -- 
          "mousemove" or --  
          "mousedown" or --   
          "mouseup" or   -- 
          "wheeldown" or --
          "wheelup" or   -- 
          "quit",        -- 
    [key: char,]                -- key down code
    [button: "l" or "r" or "m"] -- mouse button down
}

jin.graphics = {} 
--------
Image
Font 
Shader
Canvas
Font
init 
size 
study
write 
draw 
clear 
color
present  
blend 
bind 
use 
point 
line 
rect 
circle 
triangle 
polygon 


jin.audio = {} 
--------


jin.font = {}
--------



jin.keyboard = {} 
-------- 
jin.keyboard.isDown(key: char)


jin.mouse = {}
--------
jin.mouse.getPosition() 
jin.mouse.isDown(key: char) 


jin.net = {} 
--------

jin.debug = {} 
--------





