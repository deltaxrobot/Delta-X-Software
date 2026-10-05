# VERSION.txt is the single source of truth for application releases. The
# extension avoids shadowing the C++ standard library's <version> header on
# case-insensitive filesystems.
DELTA_X_VERSION = $$cat($$DELTA_X_ROOT/VERSION.txt, lines)
isEmpty(DELTA_X_VERSION): error("VERSION.txt is missing or empty")

VERSION = $$DELTA_X_VERSION
DEFINES += DELTA_X_VERSION_STRING=\\\"$$DELTA_X_VERSION\\\"
