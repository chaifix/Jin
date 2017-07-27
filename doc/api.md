# Jin API List

##### [Modules](#modules-1)
* [jin](#jin)
* [jin.core](#jincore)
* [jin.graphics](#jingraphics)
* [jin.time](#jintime)
* [jin.keyboard](#jinkeyboard)
* [jin.mouse](#jinmouse)
* [jin.filesystem](#jinfilesystem)
* [jin.debug](#jindebug)

##### [Classes](#Classes-1)
* [Image](#image)
* [Font](#font)
* [Canvas](#canvas)



## Modules 

### jin 

#### jin.author() 
Return author of jin. 

#### jin.os() 
Return operating system type. 

#### jin.version() 
Return jin version. 


### jin.core

#### jin.core.quit()
Quit Jin. 

#### jin.core.load() 
A callback for loading resources. 

#### jin.core.onEvent(e) 
Handle events inside this function. Argument e is a table which contains 
event type and event value. There are 7 kind of types:    

Event Type        | Description
------------------|--------------------------------------
"quit"            | Occurs when exit whole program. 
"keydown"         | Occurs when key is pressed. 
"keyup"           | Occurs when key is up. 
"mousemotion"     | Occurs when mouse moves. 
"mousebuttondown" | Occurs when mouse button is pressed.
"mousebuttonup"   | Occurs when mouse button is released.
"wheel"           | Occurs when mouse wheel state changes. 

For quit event, `e` only take its type and has no value.   

For keydown and keyup events, `e` has type and key fields. You can use `e.key` to get the 
name of the key. `e.key` would be one of the following values:    

Key Name                                                                            |
------------------------------------------------------------------------------------|
"0"                                                                                 |
"1"                                                                                 |
"2"                                                                                 |
"3"                                                                                 |
"4"                                                                                 |
"5"                                                                                 |
"6"                                                                                 |
"7"                                                                                 |
"8"                                                                                 |
"9"                                                                                 |
"A"                                                                                 |
"AC Back" (the Back key (application control keypad))                               |
"AC Bookmarks" (the Bookmarks key (application control keypad))                     |
"AC Forward" (the Forward key (application control keypad))                         |
"AC Home" (the Home key (application control keypad))                               |
"AC Refresh" (the Refresh key (application control keypad))                         |
"AC Search" (the Search key (application control keypad))                           |
"AC Stop" (the Stop key (application control keypad))                               |
"Again" (the Again key (Redo))                                                      |
"AltErase" (Erase-Eaze)                                                             |
"'"                                                                                 |
"Application" (the Application / Compose / Context Menu (Windows) key)              |
"AudioMute" (the Mute volume key)                                                   |
"AudioNext" (the Next Track media key)                                              |
"AudioPlay" (the Play media key)                                                    |
"AudioPrev" (the Previous Track media key)                                          |
"AudioStop" (the Stop media key)                                                    |
"B"                                                                                 |
"\"                                                                                 |
"Backspace"                                                                         |
"BrightnessDown" (the Brightness Down key)                                          |
"BrightnessUp" (the Brightness Up key)                                              |
"C"                                                                                 |
"Calculator" (the Calculator key)                                                   |
"Cancel"                                                                            |
"CapsLock"                                                                          |
"Clear"                                                                             |
"Clear / Again"                                                                     |
","                                                                                 |
"Computer" (the My Computer key)                                                    |
"Copy"                                                                              |
"CrSel"                                                                             |
"CurrencySubUnit" (the Currency Subunit key)                                        |
"CurrencyUnit" (the Currency Unit key)                                              |
"Cut"                                                                               |
"D"                                                                                 |
"DecimalSeparator" (the Decimal Separator key)                                      |
"Delete"                                                                            |
"DisplaySwitch" (display mirroring/dual display switch, video mode switch)          |
"Down" (the Down arrow key (navigation keypad))                                     |
"E"                                                                                 |
"Eject" (the Eject key)                                                             |
"End"                                                                               |
"="                                                                                 |
"Escape" (the Esc key)                                                              |
"Execute"                                                                           |
"ExSel"                                                                             |
"F"                                                                                 |
"F1"                                                                                |
"F10"                                                                               |
"F11"                                                                               |
"F12"                                                                               |
"F13"                                                                               |
"F14"                                                                               |
"F15"                                                                               |
"F16"                                                                               |
"F17"                                                                               |
"F18"                                                                               |
"F19"                                                                               |
"F2"                                                                                |
"F20"                                                                               |
"F21"                                                                               |
"F22"                                                                               |
"F23"                                                                               |
"F24"                                                                               |
"F3"                                                                                |
"F4"                                                                                |
"F5"                                                                                |
"F6"                                                                                |
"F7"                                                                                |
"F8"                                                                                |
"F9"                                                                                |
"Find"                                                                              |
"G"                                                                                 |
"`"                                                                                 |
"H"                                                                                 |
"Help"                                                                              |
"Home"                                                                              |
"I"                                                                                 |
"Insert"                                                                            |
"J"                                                                                 |
"K"                                                                                 |
"KBDIllumDown" (the Keyboard Illumination Down key)                                 |
"KBDIllumToggle" (the Keyboard Illumination Toggle key)                             |
"KBDIllumUp" (the Keyboard Illumination Up key)                                     |
"Keypad 0" (the 0 key (numeric keypad))                                             |
"Keypad 00" (the 00 key (numeric keypad))                                           |
"Keypad 000" (the 000 key (numeric keypad))                                         |
"Keypad 1" (the 1 key (numeric keypad))                                             |
"Keypad 2" (the 2 key (numeric keypad))                                             |
"Keypad 3" (the 3 key (numeric keypad))                                             |
"Keypad 4" (the 4 key (numeric keypad))                                             |
"Keypad 5" (the 5 key (numeric keypad))                                             |
"Keypad 6" (the 6 key (numeric keypad))                                             |
"Keypad 7" (the 7 key (numeric keypad))                                             |
"Keypad 8" (the 8 key (numeric keypad))                                             |
"Keypad 9" (the 9 key (numeric keypad))                                             |
"Keypad A" (the A key (numeric keypad))                                             |
"Keypad &" (the & key (numeric keypad))                                             |
"Keypad @" (the @ key (numeric keypad))                                             |
"Keypad B" (the B key (numeric keypad))                                             |
"Keypad Backspace" (the Backspace key (numeric keypad))                             |
"Keypad Binary" (the Binary key (numeric keypad))                                   |
"Keypad C" (the C key (numeric keypad))                                             |
"Keypad Clear" (the Clear key (numeric keypad))                                     |
"Keypad ClearEntry" (the Clear Entry key (numeric keypad))                          |
"Keypad :" (the : key (numeric keypad))                                             |
"Keypad ," (the Comma key (numeric keypad))                                         |
"Keypad D" (the D key (numeric keypad))                                             |
"Keypad &&" (the && key (numeric keypad))                                           |
"Keypad ||" (the || key (numeric keypad))                                           |
"Keypad Decimal" (the Decimal key (numeric keypad))                                 |
"Keypad /" (the / key (numeric keypad))                                             |
"Keypad E" (the E key (numeric keypad))                                             |
"Keypad Enter" (the Enter key (numeric keypad))                                     |
"Keypad =" (the = key (numeric keypad))                                             |
"Keypad = (AS400)" (the Equals AS400 key (numeric keypad))                          |
"Keypad !" (the ! key (numeric keypad))                                             |
"Keypad F" (the F key (numeric keypad))                                             |
"Keypad >" (the Greater key (numeric keypad))                                       |
"Keypad #" (the # key (numeric keypad))                                             |
"Keypad Hexadecimal" (the Hexadecimal key (numeric keypad))                         |
"Keypad {" (the Left Brace key (numeric keypad))                                    |
"Keypad (" (the Left Parenthesis key (numeric keypad))                              |
"Keypad <" (the Less key (numeric keypad))                                          |
"Keypad MemAdd" (the Mem Add key (numeric keypad))                                  |
"Keypad MemClear" (the Mem Clear key (numeric keypad))                              |
"Keypad MemDivide" (the Mem Divide key (numeric keypad))                            |
"Keypad MemMultiply" (the Mem Multiply key (numeric keypad))                        |
"Keypad MemRecall" (the Mem Recall key (numeric keypad))                            |
"Keypad MemStore" (the Mem Store key (numeric keypad))                              |
"Keypad MemSubtract" (the Mem Subtract key (numeric keypad))                        |
"Keypad -" (the - key (numeric keypad))                                             |
"Keypad *" (the * key (numeric keypad))                                             |
"Keypad Octal" (the Octal key (numeric keypad))                                     |
"Keypad %" (the Percent key (numeric keypad))                                       |
"Keypad ." (the . key (numeric keypad))                                             |
"Keypad +" (the + key (numeric keypad))                                             |
"Keypad +/-" (the +/- key (numeric keypad))                                         |
"Keypad ^" (the Power key (numeric keypad))                                         |
"Keypad }" (the Right Brace key (numeric keypad))                                   |
"Keypad )" (the Right Parenthesis key (numeric keypad))                             |
"Keypad Space" (the Space key (numeric keypad))                                     |
"Keypad Tab" (the Tab key (numeric keypad))                                         |
"Keypad |" (the | key (numeric keypad))                                             |
"Keypad XOR" (the XOR key (numeric keypad))                                         |
"L"                                                                                 |
"Left Alt" (alt, option)                                                            |
"Left Ctrl"                                                                         |
"Left" (the Left arrow key (navigation keypad))                                     |
"["                                                                                 |
"Left GUI" (windows, command (apple), meta)                                         |
"Left Shift"                                                                        |
"M"                                                                                 |
"Mail" (the Mail/eMail key)                                                         |
"MediaSelect" (the Media Select key)                                                |
"Menu"                                                                              |
"-"                                                                                 |
"ModeSwitch"                                                                        |
"Mute"                                                                              |
"N"                                                                                 |
"Numlock" (the Num Lock key (PC) / the Clear key (Mac))                             |
"O"                                                                                 |
"Oper"                                                                              |
"Out"                                                                               |
"P"                                                                                 |
"PageDown"                                                                          |
"PageUp"                                                                            |
"Paste"                                                                             |
"Pause"                                                                             |
"."                                                                                 |
"Power"                                                                             |
"PrintScreen"                                                                       |
"Prior"                                                                             |
"Q"                                                                                 |
"R"                                                                                 |
"Right Alt" (alt gr, option)                                                        |
"Right Ctrl"                                                                        |
"Return" (the Enter key (main keyboard))                                            |
"Return"                                                                            |
"Right GUI" (windows, command (apple), meta)                                        |
"Right" (the Right arrow key (navigation keypad))                                   |
"]"                                                                                 |
"Right Shift"                                                                       |
"S"                                                                                 |
"ScrollLock"                                                                        |
"Select"                                                                            |
";"                                                                                 |
"Separator"                                                                         |
"/"                                                                                 |
"Sleep" (the Sleep key)                                                             |
"Space" (the Space Bar key(s))                                                      |
"Stop"                                                                              |
"SysReq" (the SysReq key)                                                           |
"T"                                                                                 |
"Tab" (the Tab key)                                                                 |
"ThousandsSeparator" (the Thousands Separator key)                                  |
"U"                                                                                 |
"Undo"                                                                              |
"" (no name, empty string)                                                          |
"Up" (the Up arrow key (navigation keypad))                                         |
"V"                                                                                 |
"VolumeDown"                                                                        |
"VolumeUp"                                                                          |
"W"                                                                                 |
"WWW" (the WWW/World Wide Web key)                                                  |
"X"                                                                                 |
"Y"                                                                                 |
"Z"                                                                                 |

For mousemotion event, you may use `e.x` or `e.y` to get the position of mouse. 

For mousebuttondown and mousebuttoup events, you may use `e.button` to get the pushed 
mouse button, they are: 

Mouse Button  | 
--------------|
"left"        |           
"right"       |
"middle"      | 
"wheelup"     | 
"wheeldown"   | 

For wheel event, you may use `e.x` to get wheel motion in x direction, they are: 

X Direction      | 
-----------------|
"left"           | 
"right"          | 
"none"           | 

Or use `e.y` to get wheel motion in y direction, they are: 

Y Direction      | 
-----------------|
"near"           | 
"far"            | 
"none"           | 

            
#### jin.core.onUpdate(dt)
Do some updating stuff inside this funciton. 

#### jin.core.onDraw() 
Draw things inside this function. 


### jin.graphics

#### jin.graphics.size() 
Return size of the window. 

#### jin.graphics.Image(file)
Create a new image.

#### jin.graphics.Canvas(width, height)
Create a new canvas. 

#### jin.graphics.Font(file)
Create a new ttf font. 

#### jin.graphics.study(font)
Study a ttf font, use it as current font style. 

#### jin.graphics.box(text) 
Get bounding box of text. 

#### jin.graphics.write(text, posx, posy, fontheight, spacing, lineheight)
Print text on screen. 

#### jin.graphics.clear([r, g, b, a]) 
Clear canvas with color. 

#### jin.graphics.draw(canvas or image, posx, posy[, scalex, scaley, rotation])
Draw a canvas or image to screen(or another canvas). 

#### jin.graphics.color([r, g, b, a])
Set current render color, white by default. 

#### jin.graphics.palette() 
Return current render color. 

#### jin.graphics.bind([canvas])
Bind a canvas, screen by default. 

#### jin.graphics.point(x, y)
Draw a pixel. 

#### jin.graphics.line(x1, y1, x2, y2)
Draw a line. 

#### jin.graphics.rect(mode, x, y, w, h)
Draw a rectangle. `mode` should be one of: 

Mode        | 
------------|
"fill"      | 
"line"      | 

#### jin.graphics.circle(mode, x, y, r)
Draw a circle. 

#### jin.graphics.triangle(mode, x, y, x1, y1, x2, y2)
Draw a triangle. 

#### jin.graphics.polygon(mode, n, {x1, y1, x2, y2, ...})
Draw a polygon.


### jin.time

#### jin.time.second() 
Get seconds since program launched. 

#### jin.time.sleep(sec) 
Sleep for sec seconds. 

### jin.keyboard

#### jin.keyboard.isDown(k) 
Returns true if the given key is currently pressed.


### jin.mouse

#### jin.mouse.position()
Return mouse position. 

#### jin.mouse.isDown(btn) 
Returns true if the given button is down. 


### jin.filesystem

#### jin.filesystem.isdir(path) 
Return true if the given path is a directory. 

#### jin.filesystem.exist(path)
Return true if the given path is existed.


### jin.debug 

#### jin.debug.print(str)
Print to debug window.

#### jin.debug.size(bsize)
Set debug buffer size. 


## Classes

### Image

#### Image:getSize() 
Return width and height. 

#### Image:getWidth() 
Return width. 

#### Image:getHeight() 
Return height. 

#### Image:getPixel(x, y) 
Return pixel color. 

#### Image:setAnchor(x, y)
Set anchor of the image. 


### Font 

#### Font:box(text, fontheight, spacing, lineheight) 
Return bounding box of text. 


### Canvas

#### Canvas:getWidth() 
Return width. 

#### Canvas:getHeight() 
Return height. 

#### Canvas:getSize() 
Return width and height. 

#### Canvas:setAnchor() 
Set anchor of the canvas.