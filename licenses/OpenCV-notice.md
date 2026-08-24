# OpenCV dependency notice

Delta X Software uses OpenCV as an external build and runtime dependency.
The governed Windows dependency version is recorded in
`config/dependencies.json`; it is not vendored into this repository.

OpenCV 4.11.0 is distributed under Apache License 2.0. Its source and release
materials are published by the OpenCV project at
<https://github.com/opencv/opencv/tree/4.11.0>. The portable packager places a
separate copy of the Apache-2.0 terms at
`licenses/OpenCV-Apache-2.0.txt` inside binary artifacts.

OpenCV may contain additional third-party components depending on how it was
built. Release maintainers must inspect the selected OpenCV distribution and
preserve any notices shipped with it.
