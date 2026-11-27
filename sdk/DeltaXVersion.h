#ifndef DELTAXVERSION_H
#define DELTAXVERSION_H

#ifndef DELTA_X_VERSION_STRING
#define DELTA_X_VERSION_STRING "0.0.0-dev"
#endif

#ifndef DELTA_X_SOURCE_REVISION
#define DELTA_X_SOURCE_REVISION "source-export"
#endif

namespace DeltaXVersion
{
inline constexpr const char* Application = DELTA_X_VERSION_STRING;
inline constexpr const char* Revision = DELTA_X_SOURCE_REVISION;
}

#endif // DELTAXVERSION_H
