; One and only one vision loop for tracking0.
; The camera timer is paused because this script triggers each frame explicitly.

N15 M98 PpauseCamera

N25 LABEL VISION_LOOP
; This call blocks until the same frame has capture+detect encoder samples and
; tracking publishes FrameReady. No fixed detector-latency delay is required.
N30 M98 PcaptureAndDetect(0)
N50 M98 Pdelay(20)
N55 JUMP VISION_LOOP
