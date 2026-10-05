"""Optional PySide6 desktop frontend. The core can be used without importing it."""

import argparse
import sys


def main(argv=None):
    parser = argparse.ArgumentParser(description="Delta X 3 standalone mouse controller")
    parser.add_argument("--simulate", action="store_true", help="Start connected to the simulator")
    parser.add_argument("--smoke-test", action="store_true", help="Open simulator briefly, then exit")
    args = parser.parse_args(argv)
    try:
        from PySide6.QtWidgets import QApplication
        from PySide6.QtCore import QTimer
        from .window import MainWindow
    except ImportError as exc:
        parser.exit(2, f"GUI dependency missing: {exc}\nInstall with: python -m pip install '.[gui]'\n")
    app = QApplication(sys.argv[:1])
    app.setApplicationName("Delta Mouse Control")
    app.setOrganizationName("DeltaX")
    window = MainWindow()
    window.show()
    if args.simulate or args.smoke_test:
        QTimer.singleShot(0, window.connect_robot)
    if args.smoke_test:
        QTimer.singleShot(1800, window.close)
    return app.exec()
