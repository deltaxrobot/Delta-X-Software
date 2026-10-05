# Third-party dependencies

First-party source in this folder is Apache-2.0; see LICENSE and NOTICE.
Dependencies are installed separately and are not included in the source ZIP.

| Component | Use | Upstream licensing |
| --- | --- | --- |
| Python | Runtime and standard library | Python Software Foundation license |
| PySide6 / Shiboken6 / Qt | Optional desktop UI | Upstream LGPL/GPL/commercial terms; see installed package notices |
| pyserial | Optional serial transport | BSD-3-Clause |
| pytest | Development tests | MIT |
| setuptools | Package build | MIT |

Retain the actual dependency licenses and notices if distributing an environment
or frozen binary. The source handoff does not bundle a Python interpreter, Qt
runtime, robot firmware or vendor libraries.
