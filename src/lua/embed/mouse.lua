--[[ 
    jin.mouse extension
]] 

jin.mouse = jin.mouse or {} 

local button = {} 

function jin.mouse.isDown(btn) 
    return button[btn]
end 

function jin.mouse.set(btn, status) 
    button[btn] = status
end 
