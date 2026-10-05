#pragma once

namespace Ui { class RobotWindow; }

// Presentation only: reuses the existing controls and their command bindings.
// Safe to exercise with a generated form and no device/controller objects.
namespace RobotPanelLayout {
void setup(Ui::RobotWindow& ui);
}
