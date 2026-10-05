; ISOLATED HARNESS: legacy deletion targets the active object list.
M98 Passert(#Examples.Isolated == 1, "Use the isolated command-tour runner")
M98 PaddObject(Examples.Parts, 0, 10, 20, -300, 5, 6, 90)
M98 PclearObjects(Examples.Parts)
M98 PdeleteFirstObject
M98 PdeleteObject(3)
#Examples.ObjectsPassed = 1
