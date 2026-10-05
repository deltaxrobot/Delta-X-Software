; REAL ROBOT, READ ONLY. Connect robot0 first.
; Queries do not home, move, reset, or change outputs.
SELECT robot0
M98 Psend(robot0, "Position", #Examples.RobotPosition, 3000)
; Numeric comma-separated replies are normalized to a vector by VariableManager.
M98 PlogMessage(#Examples.RobotPosition.X)
M98 PlogMessage(#Examples.RobotPosition.Y)
M98 PlogMessage(#Examples.RobotPosition.Z)
M98 Psend(robot0, "ROBOTMODEL", #Examples.RobotModel, 3000)
M98 PlogMessage(#Examples.RobotModel)
; FirmwareVersion was added in newer Delta X 3 firmware. It is intentionally
; not required here because older supported firmware does not reply to it.
#Examples.RobotQueriesPassed = 1
M98 PlogMessage("PASS robot queries")
