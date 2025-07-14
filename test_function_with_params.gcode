; Test function system with parameters and return values

; Define a function with parameters
FUNCTION moveToPosition(x, y, z, speed)
    G01 X[#x] Y[#y] Z[#z] F[#speed]
    RETURN 1
ENDFUNCTION

; Define a function with calculation
FUNCTION calculateDistance(x1, y1, x2, y2)
    #dx = #x2 - #x1
    #dy = #y2 - #y1
    #distance = SQRT(#dx * #dx + #dy * #dy)
    RETURN #distance
ENDFUNCTION

; Define a function without parameters
FUNCTION goHome()
    G28
    RETURN 0
ENDFUNCTION

; Main program
G28 ; Home

; Call function with parameters
moveToPosition(100, 50, -80, 1000)

; Call function and use return value
#result = calculateDistance(0, 0, 100, 50)
IF #result > 50 THEN
    G01 Z-100
ENDIF

; Call function without parameters
goHome()

; Test function call with spaces
moveToPosition (200, 100, -60, 800)

; End
M30 