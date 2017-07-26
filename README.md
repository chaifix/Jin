# Jin 
[中文版](README_zh.md)   
A game framework for making 2D games in lua. 

## Screenshot   
![doc/screenshot/a.png](doc/screenshot/a.png) 
![doc/screenshot/b.png](doc/screenshot/b.png) 
![doc/screenshot/c.gif](doc/screenshot/c.gif) 

## Getting started    
You can download Jin from the [releases page](https://github.com/neonum/jin/releases). To 
run the game, you need set the first argument as your game directory. For example, if your 
game is in a directory called `mygame`, you would run the following command:    

```batch    
jin mygame
```    
    
If you want to open debug mode, set the second argument to `-d`. You need make a 
`main.lua` file inside game directory, which is entry of the game. If you want to config 
window size, fps and title, create a `config.lua` file inside game directory. The configure 
file would be like this:    

```lua     
return{
    width  = 512, 
    height = 512, 
    fps    = 60, 
    title  = "my title"
}
```
    
To create your game, you need create 4 functions(optional) in `main.lua`. They are:    

```lua     
jin.core.load()       -- run before game loop 
jin.core.onEvent(e)   -- called every event loop 
jin.core.onUpdate(dt) -- called every frame 
jin.core.onDraw()     -- called every frame 
```

Here is a small example which draws a filled circle and prints "hello, world" on screen: 

```lua 
function jin.core.onEvent(e) 
    if e.type == "quit" then 
        jin.core.quit() 
    end 
end 

function jin.core.onDraw() 
    jin.graphics.circle("fill", 10, 10, 20)
    jin.graphics.write("hello, world", 100, 100, 16, 1, 20)
end 
```

See [doc/api.md](doc/api.md) for reference.
    
## Modules   
* Graphics 
* Filesystem 
* Keyboard 
* Mouse 
* Timer 
* Audio[WIP]
* Network[WIP]

## License
See [LICENSE](LICENSE) for details.


