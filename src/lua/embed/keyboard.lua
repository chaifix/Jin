--[[ 
    jin.keyboard extension 
]] 

jin.keyboard = jin.keyboard or {} 

local keys = {} 

function jin.keyboard.isDown(k) 
    return keys[k]
end  

function jin.keyboard.set(k, status) 
    keys[k] = status 
end 

