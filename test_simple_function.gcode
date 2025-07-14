; Test simple function system (similar to M98/M99)

; Define a simple function
FUNCTION moveUp
    G01 Z-50
    G01 Z-100
ENDFUNCTION

; Define another function
FUNCTION moveDown
    G01 Z-80
    G01 Z-60
ENDFUNCTION

; Main program
G28 ; Home
moveUp ; Call function
G01 X100 ; Move X
moveDown ; Call function
G01 X0 ; Return to X0
RETURN 