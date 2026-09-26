; ISOLATED HARNESS: camera and encoder replies are simulated.
; The harness verifies tracking ID, frame correlation, UID and owner arguments.
M98 Passert(#Examples.Isolated == 1, "Use the isolated command-tour runner")
M98 PpauseCamera
M98 PcaptureCamera
M98 PresumeCamera
M98 PcaptureAndDetect(0)
M98 PupdateTracking(0)
#Examples.Owner = "robot0"
M98 PclaimObject(0, #Examples.Target, #Examples.Owner, -100, 100, -100, 100, -1, 5000)
M98 Passert(#Examples.Target.Found == 1, "claim snapshot")
M98 PreleaseObject(0, #Examples.Target.UID, #Examples.Owner)
M98 PclaimObject(0, #Examples.Target, #Examples.Owner, -100, 100, -100, 100, -1, 5000)
; Real production code must confirm pickup using a sensor before completing.
M98 PcompleteObject(0, #Examples.Target.UID, #Examples.Owner)
#Examples.VisionPassed = 1
