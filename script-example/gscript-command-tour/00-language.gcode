; SOFTWARE ONLY: open and Run, or use delta-x-cli run.
; Writes only Examples.* variables. Successful completion sets Examples.LanguagePassed.
#Examples.LanguagePassed = 0
#Examples.Counter = 0
#Examples.Arithmetic = [6 * 7 + 8 / 2 - 3]
M98 Passert(#Examples.Arithmetic == 43, "arithmetic")
#Examples.Arithmetic = 12 / 2 * 3
M98 Passert(#Examples.Arithmetic == 18, "left associative multiply and divide")
#Examples.Arithmetic = 10 - 4 - 2
M98 Passert(#Examples.Arithmetic == 4, "left associative subtraction")
#Examples.Arithmetic = [6 * 7 + 8 / 2 - 3]
#Examples.Modulo = 17 % 5
M98 Passert(#Examples.Modulo == 2, "modulo")
#Examples.Message = "ready"
M98 Passert(#Examples.Message == "ready", "string variable")
M98 Passert(#Examples.Message != "wrong", "string inequality")
M98 Passert(2 <= 2 AND 3 > 2, "comparison before logical AND")
M98 Passert(-2 < -1 OR 0, "negative comparison")
#Examples.Bool = [1 AND 1]
M98 Passert(#Examples.Bool == 1, "AND")
#Examples.Bool = [0 OR 1]
M98 Passert(#Examples.Bool == 1, "OR")
#Examples.Bool = [1 XOR 1]
M98 Passert(#Examples.Bool == 0, "XOR")
M98 Passert(2 EQ 2, "EQ")
M98 Passert(2 NE 3, "NE")
M98 Passert(2 LT 3, "LT")
M98 Passert(2 LE 2, "LE")
M98 Passert(3 GT 2, "GT")
M98 Passert(3 GE 3, "GE")
IF #Examples.Arithmetic > 50
    #Examples.Branch = 0
ELIF #Examples.Arithmetic >= 43
    #Examples.Branch = 1
ELSE
    #Examples.Branch = 2
ENDIF
M98 Passert(#Examples.Branch == 1, "ELIF")
IF #Examples.Arithmetic < 0
    #Examples.Branch = 0
ELSE
    #Examples.Branch = 2
ENDIF
M98 Passert(#Examples.Branch == 2, "ELSE")
#Examples.Sum = 0
FOR #Examples.i = 1 TO 5 STEP 1
    IF #Examples.i == 3 THEN CONTINUE
    #Examples.Sum = #Examples.Sum + #Examples.i
ENDFOR
M98 Passert(#Examples.Sum == 12, "FOR CONTINUE")
FOR #Examples.i = 3 TO 1 STEP -1
    #Examples.Counter = #Examples.Counter + 1
ENDFOR
M98 Passert(#Examples.Counter == 3, "negative STEP")
WHILE #Examples.Counter < 10
    #Examples.Counter = #Examples.Counter + 1
    IF #Examples.Counter == 5 THEN BREAK
ENDWHILE
M98 Passert(#Examples.Counter == 5, "WHILE BREAK")
SWITCH #Examples.Branch
CASE 1
    #Examples.Switch = 10
CASE 2
    #Examples.Switch = 20
DEFAULT
    #Examples.Switch = 30
ENDSWITCH
M98 Passert(#Examples.Switch == 20, "CASE")
SWITCH 99
CASE 1
    #Examples.Switch = 0
DEFAULT
    #Examples.Switch = 30
ENDSWITCH
M98 Passert(#Examples.Switch == 30, "DEFAULT")
; Object-list iteration uses list.index.X existence.
#Examples.List.0.X = 10
#Examples.List.1.X = 20
#Examples.List.2.X = "NULL"
#Examples.Sum = 0
FOR EACH #Examples.item IN #Examples.List
    #Examples.Sum = #Examples.Sum + #Examples.item_current_X
ENDFOR
M98 Passert(#Examples.Sum == 30, "FOR EACH IN")
FUNCTION ExampleSum(limit)
    LOCAL #i = 0
    LOCAL #total = 0
    WHILE #i < #limit
        #total = #total + #i
        #i = #i + 1
    ENDWHILE
    RETURN #total
ENDFUNCTION
#Examples.Function = #ExampleSum(4)
M98 Passert(#Examples.Function == 6, "FUNCTION LOCAL RETURN")
LABEL NAMED_TARGET
#Examples.Counter = #Examples.Counter + 1
IF #Examples.Counter < 7 THEN JUMP NAMED_TARGET
M98 Passert(#Examples.Counter == 7, "LABEL JUMP")
N100 #Examples.Counter = #Examples.Counter + 1
IF [#Examples.Counter < 9] THEN GOTO 100
M98 Passert(#Examples.Counter == 9, "N GOTO")
M98 P2000
GOTO 200
O2000
#Examples.Subprogram = 42
M99
N200 M98 Passert(#Examples.Subprogram == 42, "O M98 M99")
#Examples.Ready = 1
M98 PwaitUntil(#Examples.Ready == 1, 200, 5, "waitUntil")
M98 Pdelay(20)
#Examples.LanguagePassed = 1
M98 PlogMessage("PASS language")
