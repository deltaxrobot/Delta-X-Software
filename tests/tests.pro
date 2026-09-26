TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    mouse_jog \
    phone_camera \
    drawing \
    cli_transport \
    cli_integration \
    ui_theme \
    control_plane \
    device_state \
    gscript_analyzer \
    block_programming \
    variable_manager \
    tracking_claim \
    vision_pipeline \
    filter_worker \
    calibration_core \
    socket_vision_protocol \
    gscript_runtime \
    plugin_contract \
    plugin_manager \
    industrial_camera_optional_runtime

control_plane.file = $$PWD/control_plane/control_plane.pro
mouse_jog.file = $$PWD/mouse_jog/mouse_jog.pro
phone_camera.file = $$PWD/phone_camera/phone_camera.pro
drawing.file = $$PWD/drawing/drawing.pro
cli_transport.file = $$PWD/cli_transport/cli_transport.pro
cli_integration.file = $$PWD/cli_integration/cli_integration.pro
ui_theme.file = $$PWD/ui_theme/ui_theme.pro
device_state.file = $$PWD/device_state/device_state.pro
gscript_analyzer.file = $$PWD/gscript_analyzer/gscript_analyzer.pro
block_programming.file = $$PWD/block_programming/block_programming.pro
variable_manager.file = $$PWD/variable_manager/variable_manager.pro
tracking_claim.file = $$PWD/tracking_claim/tracking_claim.pro
vision_pipeline.file = $$PWD/vision_pipeline/vision_pipeline.pro
filter_worker.file = $$PWD/filter_worker/filter_worker.pro
calibration_core.file = $$PWD/calibration_core/calibration_core.pro
socket_vision_protocol.file = $$PWD/socket_vision_protocol/socket_vision_protocol.pro
gscript_runtime.file = $$PWD/gscript_runtime/gscript_runtime.pro
plugin_contract.file = $$PWD/plugin_contract/plugin_contract.pro
plugin_manager.file = $$PWD/plugin_manager/plugin_manager.pro
industrial_camera_optional_runtime.file = \
    $$PWD/industrial_camera_optional_runtime/industrial_camera_optional_runtime.pro
