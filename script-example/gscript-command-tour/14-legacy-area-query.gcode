; ISOLATED HARNESS ONLY: legacy area lookup does not reserve an object.
; Production multi-robot picking should use claimObject/releaseObject/completeObject.
M98 Passert(#Examples.Isolated == 1, "Use the isolated command-tour runner")
#Examples.Area = #GetObjectInArea(0, X_MIN=-100, X_MAX=100)
#Examples.Area = #GetObjectInArea(0, Y_MIN=-100, Y_MAX=100)
#Examples.AreaPassed = 1
