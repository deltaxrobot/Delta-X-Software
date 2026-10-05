; Robot 0: claim type 0 in conveyor-frame zone Y=300..450.
; REQUIRED variable from calibration: #0.ConveyorToRobot0

SELECT robot0

#R0SafeZ = -260
#R0PickZ = -335
#R0PlaceX = -180
#R0PlaceY = 40
#R0PlaceZ = -330
#R0AngleOffset = 0
#R0BeltVector = (0,200,0)
#R0Owner = "robot0"
#R0MinConfidence = 0.60
#R0UseVacuumFeedback = 0

M98 Passert(#R0SafeZ > #R0PickZ,"robot0: Safe Z must be above Pick Z")

M05
SYNC robot0 #R0BeltVector

LABEL R0_LOOP
M98 PclaimObject(0,#R0Target,#R0Owner,-180,180,300,450,0,30000)

IF #R0Target.Found == 1
    IF #R0Target.Confidence >= #R0MinConfidence
        #R0Pick = #0.ConveyorToRobot0.Map(#R0Target.X,#R0Target.Y)
        #R0PickA = #R0Target.A + #R0AngleOffset

        G01 X[#R0Pick.X] Y[#R0Pick.Y] Z[#R0SafeZ] W[#R0PickA] F1200 SYNC
        G01 X[#R0Pick.X] Y[#R0Pick.Y] Z[#R0PickZ] W[#R0PickA] F500 SYNC
        M03
        IF #R0UseVacuumFeedback == 1
            M98 PwaitUntil(#Vacuum.R0.OK == 1,500,10,"robot0: vacuum timeout")
        ELSE
            M98 Pdelay(60)
        ENDIF
        M98 PcompleteObject(0,#R0Target.UID,#R0Owner)

        G01 Z[#R0SafeZ] F700
        G01 X[#R0PlaceX] Y[#R0PlaceY] Z[#R0SafeZ] W0 F1200
        G01 Z[#R0PlaceZ] F500
        M05
        M98 Pdelay(60)
        G01 Z[#R0SafeZ] F700
    ELSE
        M98 PreleaseObject(0,#R0Target.UID,#R0Owner)
    ENDIF
ENDIF

M98 Pdelay(20)
JUMP R0_LOOP
