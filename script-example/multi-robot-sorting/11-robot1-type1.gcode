; Robot 1: claim type 1 in conveyor-frame zone Y=600..750.
; REQUIRED variable from calibration: #0.ConveyorToRobot1

SELECT robot1

#R1SafeZ = -260
#R1PickZ = -335
#R1PlaceX = 180
#R1PlaceY = 40
#R1PlaceZ = -330
#R1AngleOffset = 0
#R1BeltVector = (0,200,0)
#R1Owner = "robot1"
#R1MinConfidence = 0.60
#R1UseVacuumFeedback = 0

M98 Passert(#R1SafeZ > #R1PickZ,"robot1: Safe Z must be above Pick Z")

M05
SYNC robot1 #R1BeltVector

LABEL R1_LOOP
M98 PclaimObject(0,#R1Target,#R1Owner,-180,180,600,750,1,30000)

IF #R1Target.Found == 1
    IF #R1Target.Confidence >= #R1MinConfidence
        #R1Pick = #0.ConveyorToRobot1.Map(#R1Target.X,#R1Target.Y)
        #R1PickA = #R1Target.A + #R1AngleOffset

        G01 X[#R1Pick.X] Y[#R1Pick.Y] Z[#R1SafeZ] W[#R1PickA] F1200 SYNC
        G01 X[#R1Pick.X] Y[#R1Pick.Y] Z[#R1PickZ] W[#R1PickA] F500 SYNC
        M03
        IF #R1UseVacuumFeedback == 1
            M98 PwaitUntil(#Vacuum.R1.OK == 1,500,10,"robot1: vacuum timeout")
        ELSE
            M98 Pdelay(60)
        ENDIF
        M98 PcompleteObject(0,#R1Target.UID,#R1Owner)

        G01 Z[#R1SafeZ] F700
        G01 X[#R1PlaceX] Y[#R1PlaceY] Z[#R1SafeZ] W0 F1200
        G01 Z[#R1PlaceZ] F500
        M05
        M98 Pdelay(60)
        G01 Z[#R1SafeZ] F700
    ELSE
        M98 PreleaseObject(0,#R1Target.UID,#R1Owner)
    ENDIF
ENDIF

M98 Pdelay(20)
JUMP R1_LOOP
