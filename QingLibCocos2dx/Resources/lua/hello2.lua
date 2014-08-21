

print("begin debugger")


--require('mobdebug').start() --<-- only insert this line

function myadd(x, y)
    return x + y
end


-- int string bool
-- return int
function funReturnInt(nNum, str, bIsOk)
	result = 10
	power = 0
	if nNum == 100 then
	    power = power +1
	end
	if str == "aaa" then
		power = power + 1
	end
	if bIsOk then
	    power = power + 1
	end

    return (result^power)
end

-- int string bool
-- return string
function funReturnString(nNum, str, bIsOk)
    return string.format("%d%s%s", nNum, str, tostring(bIsOk))
end


-- int string bool
-- return bool
function funReturnBool(nNum, str, bIsOk)
    return nNum == 100 and str == "aaa" and bIsOk == true
end



--print(funReturnInt(100, "aaa", true))

--print(funReturnString(999, ";Kevin;", true))

--print(funReturnBool(100, "aaa", true))