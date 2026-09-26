; SOFTWARE ONLY: legacy point assignment and affine Map helper.
; Matrix string: m11,m12,m21,m22,dx,dy (identity plus translation).
#Examples.Transform = "1,0,0,1,10,20"
#Examples.Point2D = (2,3)
#Examples.Point3D = (2,3,-300)
M98 Passert(#Examples.Point2D.X == 2, "point X")
M98 Passert(#Examples.Point2D.Y == 3, "point Y")
M98 Passert(#Examples.Point3D.Z == -300, "point Z")
#Examples.Mapped = #Examples.Transform.Map(2 + 1,3)
M98 Passert(#Examples.Mapped.X == 13, "affine Map X")
M98 Passert(#Examples.Mapped.Y == 23, "affine Map Y")
#Examples.PointsPassed = 1
M98 PlogMessage("PASS points and Map")
