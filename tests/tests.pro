TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    control_plane \
    device_state \
    gscript_analyzer \
    variable_manager \
    tracking_claim \
    vision_pipeline \
    filter_worker \
    calibration_core \
    socket_vision_protocol \
    gscript_runtime \
    plugin_contract \
    industrial_camera_optional_runtime

control_plane.file = $$PWD/control_plane/control_plane.pro
device_state.file = $$PWD/device_state/device_state.pro
gscript_analyzer.file = $$PWD/gscript_analyzer/gscript_analyzer.pro
variable_manager.file = $$PWD/variable_manager/variable_manager.pro
tracking_claim.file = $$PWD/tracking_claim/tracking_claim.pro
vision_pipeline.file = $$PWD/vision_pipeline/vision_pipeline.pro
filter_worker.file = $$PWD/filter_worker/filter_worker.pro
calibration_core.file = $$PWD/calibration_core/calibration_core.pro
socket_vision_protocol.file = $$PWD/socket_vision_protocol/socket_vision_protocol.pro
gscript_runtime.file = $$PWD/gscript_runtime/gscript_runtime.pro
plugin_contract.file = $$PWD/plugin_contract/plugin_contract.pro
industrial_camera_optional_runtime.file = \
    $$PWD/industrial_camera_optional_runtime/industrial_camera_optional_runtime.pro
