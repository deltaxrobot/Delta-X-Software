; ISOLATED TEST HARNESS ONLY. The commands below may move hardware or change outputs.
M98 Passert(#Examples.Isolated == 1, "Use the isolated command-tour runner")
SELECT robot0
G28
G01 X[10 + 5] F200
robot1 G01 X20
conveyor0 M311 S10
encoder0 M317
slider0 M320
device0 M42 P1
M98 Psend(device0, "M42 P0", #Examples.Reply, 1000)
M98 Passert(#Examples.Reply == "Ok", "send response")
; sendGcode is a compatibility alias with the same arguments as send.
M98 PsendGcode(device0, "M42 P1", #Examples.Reply, 1000)
SYNC robot0 (10, 0, 0)
; Legacy flags are accepted but do not implement tracking compensation.
; Use SYNC and commissioned tracking settings for actual synchronization.
M98 PsyncConveyor
robot0 G01 X20
M98 PstopSyncConveyor
robot0 G01 X0
#Examples.RoutingPassed = 1
