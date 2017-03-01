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
jin.graphics.newCanvas(w: int, h: int) 
jin.graphics.bindCanvas(canvas: Canvas)
jin.graphics.unbindCanvas() 
jin.graphics.clear() -- clear canvas with setting color 
jin.graphics.draw()

jin.graphics.newImage(file: string) 

jin.graphics.Image = 
{
functions: 
    getWidth(), 
    getHeight(), 
    getSize(),
    getPixel(x: int, y:int),
members: 
    width: int, 
    height: int, 
}

jin.graphics.newShader(code: string) 
jin.graphics.newShaderf(path: string) 
jin.graphics.useShader(shader: Shader) 
jin.graphics.unuseShader()

jin.graphics.Shader =
{
functions: 
    setAttribute(name: string, value: any) 
members:
}


jin.audio = {} 
--------


jin.font = {}
--------



jin.keyboard = {} 
-------- 
jin.keyboard.isDown(key: char)


jin.mouse = {}
--------
jin.mouse.getX() 
jin.mouse.getY() 
jin.mouse.getPosition() 
jin.mouse.isDown(key: char) 


jin.net = {} 
--------






