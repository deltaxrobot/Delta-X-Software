# GScript Function System Documentation

## Overview
The GScript function system provides a simple and efficient way to define and call functions with parameters and return values. It follows the same pattern as the M98/M99 subprogram system but with modern programming features.

## Basic Syntax

### Function Definition
```gcode
FUNCTION functionName(param1, param2, ...)
    ; Function body
    RETURN value
ENDFUNCTION
```

### Function Call
```gcode
functionName(arg1, arg2, ...)
```

### Function Call with Return Value
```gcode
#result = functionName(arg1, arg2, ...)
```

## Features

### 1. Parameter Passing
- Parameters are defined in parentheses after function name
- Parameters are automatically bound to variables within the function
- Parameters can be used with or without `#` prefix

### 2. Return Values
- Functions can return values using `RETURN value`
- Return values can be assigned to variables
- Return values support expressions and calculations

### 3. Simple Stack Management
- Uses simple array-based stack (similar to M98/M99)
- No complex local variable scoping
- Functions share global variable space

## Examples

### 1. Basic Function without Parameters
```gcode
FUNCTION goHome()
    G28
    RETURN 0
ENDFUNCTION

; Call function
goHome()
```

### 2. Function with Parameters
```gcode
FUNCTION moveToPosition(x, y, z, speed)
    G01 X[#x] Y[#y] Z[#z] F[#speed]
    RETURN 1
ENDFUNCTION

; Call function
moveToPosition(100, 50, -80, 1000)
```

### 3. Function with Return Value
```gcode
FUNCTION calculateDistance(x1, y1, x2, y2)
    #dx = #x2 - #x1
    #dy = #y2 - #y1
    #distance = SQRT(#dx * #dx + #dy * #dy)
    RETURN #distance
ENDFUNCTION

; Call function and use return value
#result = calculateDistance(0, 0, 100, 50)
IF #result > 50 THEN
    G01 Z-100
ENDIF
```

### 4. Function with Conditional Logic
```gcode
FUNCTION safeMove(x, y, z)
    IF #z > -50 THEN
        G01 Z-50 ; Move to safe height first
    ENDIF
    G01 X[#x] Y[#y]
    G01 Z[#z]
    RETURN 1
ENDFUNCTION

; Usage
safeMove(100, 200, -80)
```

### 5. Function with Loop
```gcode
FUNCTION drawSquare(size, speed)
    FOR #i = 1 TO 4
        G01 X[#size] F[#speed]
        G01 Y[#size] F[#speed]
        G01 X[-#size] F[#speed]
        G01 Y[-#size] F[#speed]
    ENDFOR
    RETURN 4
ENDFUNCTION

; Usage
drawSquare(50, 1000)
```

## Integration with Existing Features

### 1. Works with IF-ELIF-ELSE
```gcode
FUNCTION checkPosition(x, y)
    IF #x > 100 THEN
        RETURN 1
    ELIF #y > 100 THEN
        RETURN 2
    ELSE
        RETURN 0
    ENDIF
ENDFUNCTION
```

### 2. Works with FOR Loops
```gcode
FUNCTION multiMove(count, step)
    FOR #i = 1 TO #count
        G01 X[#i * #step]
    ENDFOR
    RETURN #count
ENDFUNCTION
```

### 3. Works with Variables
```gcode
FUNCTION addNumbers(a, b)
    #sum = #a + #b
    RETURN #sum
ENDFUNCTION

#result = addNumbers(10, 20)
```

## Syntax Highlighting

The following keywords are highlighted:
- `FUNCTION` - Function definition
- `ENDFUNCTION` - End of function
- `RETURN` - Return statement

## Implementation Details

### Stack Management
- Uses simple array-based stack: `returnFunctionPointer[20]`
- Stack index: `returnFunctionOrder`
- Similar to M98/M99 mechanism

### Parameter Binding
- Parameters are bound to global variables
- No local variable scoping
- Parameters accessible with `#paramName`

### Return Value Handling
- Return values stored in `__RETURN_VALUE__`
- Assignment handled through `__RETURN_VAR__`
- Supports expressions and calculations

## Best Practices

1. **Function Naming**: Use descriptive names
2. **Parameter Names**: Use clear parameter names
3. **Return Values**: Always return meaningful values
4. **Comments**: Add comments to explain complex functions
5. **Error Handling**: Check parameters and return appropriate values

## Example Program

```gcode
; Define utility functions
FUNCTION moveUp(distance)
    G01 Z[#distance]
    RETURN 1
ENDFUNCTION

FUNCTION moveDown(distance)
    G01 Z[-#distance]
    RETURN 1
ENDFUNCTION

FUNCTION pickAndPlace(x1, y1, x2, y2)
    ; Move to pick position
    G01 X[#x1] Y[#y1]
    moveDown(50)
    
    ; Pick operation
    M98 PcaptureCamera
    
    ; Move to place position
    moveUp(50)
    G01 X[#x2] Y[#y2]
    moveDown(50)
    
    RETURN 1
ENDFUNCTION

; Main program
G28 ; Home
#result = pickAndPlace(100, 100, 200, 200)
IF #result = 1 THEN
    G01 Z0 ; Return to safe height
ENDIF
```

This implementation provides a clean, efficient function system that integrates seamlessly with existing GScript features while maintaining the simplicity and reliability of the M98/M99 approach. 