--[[ 
    jin.path extension
]] 

jin.path = jin.path or {} 

-- game root directory 
jin._root = nil 

-- return full path of a given path 
function jin.path.full(path)
    local root = jin._dir .. '/' .. jin._argv[2]
    return root .. '/' .. path 
end

