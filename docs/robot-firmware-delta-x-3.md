# Delta X 3 Robot Firmware Reference

This document is the source-derived baseline for inspecting and commissioning the
Delta X 3 robot used with Delta X Software. It describes what this model's
firmware does, not what another Delta X robot is assumed to do.

> **Model scope:** this reference applies only to **Delta X 3** from branch
> `delta-x3-official` at the reviewed commit below. Delta X 1, Delta X 2, and
> Delta X S use other firmware branches and require separate source reviews,
> defaults, pin maps, command matrices, safety findings, and validation records.
> Never transfer calibration or inspection conclusions between models.

> **Safety status:** source review only. The values and protocol below have not
> yet been validated against physical motion, measured dimensions, wiring, or a
> safety assessment. Reading the firmware for this document did not send any
> command to the connected robot. Keep people and equipment outside the robot
> envelope, make the hardware emergency stop independently effective, and begin
> physical validation at reduced speed.

## 1. Source baseline

| Item | Value |
| --- | --- |
| Firmware repository | `D:\working\source\Delta_Firmware` |
| Reviewed branch | `delta-x3-official` |
| Reviewed commit | `4614de962fa39e9c769be7813c90a1e642f2c00f` |
| Commit date | 2026-07-15 09:50:31 +0700 |
| Commit subject | `1.0.8 fix load IMEI String` |
| Firmware version | `1.08` |
| Firmware update string | `15/7/2026` |
| Robot model | `DELTA_X_3` |
| Main board | `V1.02` |
| Default IMEI | `0002-0000-0001` |
| MCU/board | STM32H743VIT6 / DevEBox H743VITX, 480 MHz |
| Framework | Arduino through PlatformIO `ststm32` |

Re-check this document whenever the firmware commit changes. Runtime values can
also differ from the compile-time defaults because many settings are loaded from
external SPI EEPROM or internal flash at boot.

### Firmware family inventory

| Robot family | Branch/profile status | May use this document? |
| --- | --- | --- |
| Delta X 3 | `delta-x3-official`; reviewed at the commit above | Yes, after identity verification |
| Delta X 2 | Local branch `deltax2` exists; not reviewed in this document | No |
| Delta X 1 | Firmware branch mapping still needs to be identified and reviewed | No |
| Delta X S | Firmware branch mapping still needs to be identified and reviewed | No |

Several historical remote refs are also present (`0.9.1AVR`, `0.9.1_AVR_STM`,
`0.9.2_STM32`, `0.9.3-STM32F103RC`, and STM32H743 variants). They must be
classified by hardware/product identity before they can become a model profile.

### Rules for future robot checks

1. Compare the current firmware commit and the robot's reported identity with
   this baseline before interpreting any other result.
2. Confirm the physical robot is Delta X 3 and the firmware is derived from the
   reviewed Delta X 3 branch. A matching serial protocol alone is insufficient.
3. Start with passive commands only. Reading this document is not authorization
   to home, jog, energize an output, reset settings, or rewrite calibration.
4. Treat telemetry as untrusted after boot, a failed/interrupted home, an E-stop,
   or a motor-power interruption until the physical pose is re-established.
5. Use one communication transport at a time and wait for the expected reply to
   each command before sending the next one.
6. Record measured hardware behavior separately from source-derived expectations
   in the validation record; a mismatch is a finding, not a reason to force the
   hardware to match the document.

## 2. Robot model

The compiled configuration exposes five controlled axes:

- `X`, `Y`, `Z`: Cartesian position of the delta platform, solved into three
  stepper-driven arm angles (`theta1`, `theta2`, `theta3`).
- `W`: fourth axis on an RC servo, nominal range 0–180 degrees.
- `U`: fifth axis on an RC servo, nominal range 0–180 degrees.
- A separate end-effector channel selects vacuum, gripper, or pen behavior.

The three arm motors use step/direction/enable drivers. Each arm has one home
switch. W, U, and the gripper are open-loop servos; the reviewed firmware has no
position feedback for them.

Although `CANEncoderRequest` names exist in `enum.h`, this snapshot contains no
implemented CAN/encoder communication path. Do not treat this firmware as
closed-loop or encoder-verified.

### Default geometry and limits

| Parameter | Default | Firmware meaning |
| --- | ---: | --- |
| `RD_OF` | 64 mm | Tool/platform Z offset |
| `RD_F` | 290 mm | Fixed-base triangle dimension |
| `RD_E` | 105 mm | Moving-platform triangle dimension |
| `RD_RF` | 120 mm | Upper arm length |
| `RD_RE` | 340 mm | Parallel lower arm length |
| `RD_W`, `RD_U` | 0 mm | Additional offsets |
| Moving Z span | 450 mm | Lower workspace bound calculation |
| XY limit | 170 mm | Used by code as a **radius**, despite the name “largest diameter” |
| Steps/revolution | 9600 per arm | 200 full steps × 16 microsteps × 3 ratio |
| Home angles | -34.442°, -34.892°, -35.092° | Theta 1–3 software home angles |
| Joint upper limit | 90° | Theta 1–3 |
| W/U range | 0–180° | 500–2500 us servo pulses |
| Gripper range | 30–125° | 30° open, 125° closed |
| Minimum move | 0.2 mm | Shorter Cartesian moves are treated as zero travel |

### Default motion parameters

| Parameter | Default | Maximum accepted by `M210` |
| --- | ---: | ---: |
| Velocity `F` | 1000 mm/s | 20000 mm/s |
| Acceleration `A` | 10000 mm/s² | 50000 mm/s² |
| Jerk `J` | 350000 mm/s³ | 10000000 mm/s³ |
| Start velocity `S` | 100 mm/s | Below `F - 2` |
| End velocity `E` | 100 mm/s | Below `F - 2` |
| Homing speed | 16 deg/s | No public setter in this snapshot |
| Homing back-off | 10° | No public setter in this snapshot |

These compiled defaults are aggressive for first motion. Commissioning software
must explicitly apply conservative parameters before a supervised motion test.

## 3. Coordinate behavior

`G90` selects absolute positioning and is the boot default. `G91` selects
relative positioning.

For normal absolute moves without a work offset, the user-facing Z value is
converted internally as:

```text
internal_z = commanded_z + RD_OF + DEFAULT_OF_BT
           = commanded_z + 68 mm   (with compiled defaults)
```

`Position` and `G93` convert it back by subtracting the same 68 mm. X and Y are
not shifted unless a work offset is enabled.

`M206 X... Y... Z...` enables a work offset. Sending all three values as zero
disables it. The implementation stores Z in its internal coordinate form, so
host software should use `PositionOffset` when it needs coordinates relative to
the active offset.

Workspace checks include a Z interval, a circular XY bound, inverse kinematics,
and joint-angle limits. However, only the requested endpoint is comprehensively
checked before a linear or circular move; this is not a certified continuous
collision or singularity check.

`M207 Z...` stores a “safe Z”, but the reviewed motion code never uses that value
to plan or reject moves. Safe-Z motion must therefore be enforced by Delta X
Software or G-Script until firmware enforcement exists.

## 4. Hardware I/O map

The following mapping is compiled for `MCU_STM32H743VIT6`.

| Function | Pin(s) | Notes |
| --- | --- | --- |
| Theta 1 pulse/direction/enable | PD11 / PD12 / PD10 | Enable is active low |
| Theta 2 pulse/direction/enable | PC11 / PC12 / PC10 | Enable is active low |
| Theta 3 pulse/direction/enable | PC1 / PC2_C / PC0 | Enable is active low |
| Theta 1/2/3 home switches | PD13 / PD0 / PA7 | Compiled invert flag is `true` |
| W servo / U servo | PA0 / PA1 | 500–2500 us defaults |
| Gripper servo | PA4 | 500–2500 us defaults |
| Vacuum MOSFET | PC3_C | Active low: LOW = on, HIGH = off |
| Digital outputs D0–D3 | PB1 / PB0 / PC5 / PC4 | D4 is a virtual end-effector selector |
| Digital inputs I0–I3 | PE9 / PE8 / PE7 / PB2 | Configured with pull-ups |
| Analog inputs A0–A1 | PA5 / PA6 | Scaled to 0–1023 |
| E-stop channels A/B | PE11 / PE10 | Both HIGH is treated as pressed |
| Power-sense input | PE0 | Firmware accepts digital LOW as power healthy |
| Home button | PE12 | Short release triggers homing; long release triggers reset |
| Status LED R/G/B | PC7 / PC8 / PE13 | Red patterns are used in this snapshot |
| Ethernet SPI | CS PD7, SCK PB3, MISO PB4, MOSI PB5 | W5x00-style Arduino Ethernet API |
| External EEPROM SPI2 | CS PB12, SCK PB13, MISO PB14, MOSI PB15 | 128-kbit configuration |
| Secondary UART | RX PB10 / TX PB11 | Firmware calls this TTL2/Serial3 |

## 5. Communications protocol

### Transports

| Transport | Default |
| --- | --- |
| USB serial | 115200 baud |
| TTL/Serial2 | Enabled, 115200 baud |
| TTL2/Serial3 | Enabled, 115200 baud |
| Ethernet TCP server | Enabled, `192.168.0.100:8844` |
| Subnet / gateway / DNS | `255.255.0.0` / `192.168.0.1` / `192.168.0.1` |
| MAC | `00:1A:A0:12:34:56` |

Every command is an ASCII line terminated by LF (`\n`). CR is ignored. Commands
and parameter letters are case-sensitive and must be uppercase. Tokens must be
separated by spaces. Comments, quoted strings, standard G-code line numbers, and
standard G-code checksums are not supported.

An optional legacy length check has this exact form:

```text
G93 &3
```

The integer after `&` must equal the number of characters before the separating
space (`G93` has length 3). This is only a length check, not a data-integrity CRC.

Input without a newline is cleared after it grows beyond 80 characters. The
command queue holds at most 50 `String` objects. The receiver does not report a
queue insertion failure, so hosts should send one command and wait for the
expected response instead of streaming an unbounded batch.

### Completion model

Most successful state-changing commands eventually emit the configurable
completion text, default `Ok`. Motion produces `Ok` only after the stepper timer
finishes. Errors generally begin with `Unknown:`. Several query commands return
data without a trailing `Ok`.

The active states reported by `DeltaState` are `Free`, `Running`, `Wait`,
`Executed`, and `Done`. The internal `Stop` and `SendConfirm` states are not
returned by that query. A robust host must match semantic replies and error
lines, not assume that every line ends in `Ok`.

The feedback destination is a single global “last receiving transport” value.
If multiple USB/TTL/Ethernet clients send commands concurrently, a queued
command can reply through the wrong transport. Use one controlling transport at
a time.

## 6. Passive identification commands

These text commands bypass the motion queue and are the preferred first checks.
They do not intentionally command motion or outputs.

| Command | Expected reply |
| --- | --- |
| `IsDelta` | `YesDelta` |
| `Infor` | Board, firmware, and model on multiple lines |
| `FirmwareVersion` | `FirmwareVersion:1.08` for this baseline |
| `ROBOTMODEL` | `MODEL:DELTA_X_3` |
| `IMEI` | `IMEI:<stored value>` |
| `Date` | `Date:15/7/2026` for this baseline |
| `Address` | `Address: <0..255>` |
| `Storage` | `Storage:External EEPROM` or `Storage:Flash EEPROM` |
| `DeltaState` | Current public state |
| `HTs` | Three switch bits in Theta 1, 2, 3 order, for example `000` |
| `Position` | `X,Y,Z` in user coordinates |
| `PositionOffset` | `X,Y,Z` relative to the configured offset |
| `Angle` | `theta1,theta2,theta3` |

`Disconnect` only changes the status LED behavior. It does not close a serial or
Ethernet transport.

## 7. G/M command reference

### Motion and coordinate commands

| Command | Parameters | Firmware behavior |
| --- | --- | --- |
| `G0` | `X Y Z W U F A J S E` | Linear Cartesian interpolation |
| `G1` | `X Y Z W U F A J S E` | Identical implementation to `G0` |
| `G2` | `I J X Y W U F A S E` | Circular XY move at current Z; one direction |
| `G3` | `I J X Y W U F A S E` | Circular XY move at current Z; opposite direction |
| `G4` | `P` | Dwell in milliseconds |
| `G6` | `X Y Z F A J S E` | Direct Theta 1/2/3 joint-angle move |
| `G28` | none | Three-phase homing; also writes all servos |
| `G90` | none | Absolute coordinates |
| `G91` | none | Relative coordinates |
| `G93` | none | Return current `X,Y,Z`; no trailing `Ok` |

W and U servo writes occur immediately before the delta-arm planner runs; they
are not time-synchronized with Cartesian motion. Missing axes keep their current
position in absolute mode and become zero increments in relative mode.

### End effector and I/O

| Command | Parameters | Behavior |
| --- | --- | --- |
| `M3 S<n>` | `S` | Turn on selected end effector; gripper uses 0–100% |
| `M5` | none | Turn off selected end effector |
| `M3 D<n>` | D0–D3, D4 | Set digital output(s) HIGH; D4 turns on end effector |
| `M6 D<n>` | D0–D3, D4 | Set digital output(s) LOW; D4 turns off end effector |
| `M3 P<n> W<v>` | P0/P1, W 0–255 | 8-bit PWM on output 0 or 1 |
| `M4 P<n> W<v>` | P0/P1, W 0–65535 | 16-bit PWM on output 0 or 1 |
| `M7 I<n>` | one or more I0–I3 | Read digital inputs; replies `I<n> V<0|1>` |
| `M7 A<n>` | A0/A1 | Read analog inputs; replies `A<n> V<0..1023>` |
| `M8 I<n> B<0|1>` | I0–I3 | Disable/enable change-driven digital reports |
| `M8 A<n> C<n>` | A0/A1 | Enable periodic analog reports when `C > 50`; current timer code reports about every `C / 10` ms |
| `M9 A<n>` | A0/A1 | Disable periodic analog reports |
| `M360 E<n>` | 0/1/2 | Select vacuum/gripper/pen |

Multiple selector tokens may appear on one line, for example `M7 I0 I1`. Vacuum
is active-low. Pen mode has no implemented on/off action in this snapshot.
Selecting an end effector also resets the stored W-axis current position to zero,
which can make the next W command inconsistent with the physical servo pose.

### Non-G-code text controls

| Command | Behavior |
| --- | --- |
| `Emergency:Stop` | Set the software stop flag |
| `Emergency:Pause` | Same stop-flag behavior as Stop |
| `Emergency:Resume` | Clear the software stop flag and acknowledge |
| `Emergency:Reset` | Acknowledge and reboot the MCU after 100 ms |
| `Address:<0..255>` | Change and save the logical robot address |
| `IMEI:<text>` | Change and save the robot identity string |
| `FEEDBACK:<text>` | Write a new completion string to storage; current RAM value is not updated until reload/reboot |

### Runtime, query, and configuration commands

| Command | Parameters | Behavior / persistence |
| --- | --- | --- |
| `M43 A B` | enable, baud | Configure TTL/Serial2; saved immediately |
| `M44 A B` | enable, baud | Configure TTL2/Serial3; saved immediately |
| `M50 A` | 0/1 | Disable/enable Ethernet; saved immediately |
| `M51 B` | TCP port | Save Ethernet port |
| `M52 A B C D E F` | six bytes | Save MAC address |
| `M53`–`M56 A B C D` | four bytes | Save IP, DNS, gateway, subnet respectively |
| `M57` | none | Query configured IP; no trailing `Ok` |
| `M58` | none | Query complete Ethernet settings; no trailing `Ok` |
| `M60 P Q H A B` | max, min, home, min/max pulse | Configure W; saved immediately |
| `M61 P Q H A B` | max, min, home, min/max pulse | Configure U; saved immediately |
| `M62 P Q H` | max, min, home | Configure gripper; saved immediately |
| `M84` / `M85` | none | Disable / enable arm stepper drivers |
| `M203 S` | jerk | Set runtime jerk |
| `M204 A` | acceleration | Set runtime acceleration |
| `M205 S` | edge velocity | Set both start and end velocity |
| `M206 X Y Z` | offset | Set work offset; all zero disables it |
| `M207 Z` | safe Z | Store runtime safe Z; not enforced by motion code |
| `M210 F A J S E` | motion profile | Set all runtime motion parameters |
| `M220 I0..I3` | section index | Query motion/W/U/gripper parameters; no trailing `Ok` |
| `M361 P` | distance | Set minimum moving distance, at least 0.05 mm |
| `M420` / `M421` | none | Query W / U configuration |
| `M500` | none | Save current configuration |
| `M501` | none | **Reset to compiled defaults and persist them** |
| `M502` | none | **Reload stored geometry, ports, home, steps, W/U, and gripper settings** |

The meanings of `M501` and `M502` are opposite to common RepRap conventions.
Treat both as high-impact commands and never expose them as an ordinary “read”
operation.

### Factory/private commands

These commands can invalidate kinematics or calibration. They must be hidden
from normal operation and used only with a configuration backup and a supervised
recommissioning plan.

| Command | Parameters | Behavior |
| --- | --- | --- |
| `M400 A B C` | home angles | Runtime-only home angles; not password protected or persisted |
| `M401 P1144 U F R E Q` | pass, OF, F, RF, RE, E | Change and save geometry |
| `M402 P1144 Z` | pass, Z span | Change moving Z span in RAM; the save call omits this field, so it is lost at reboot |
| `M403 P1144 R` | pass, XY bound | Change and save XY bound |
| `M404 P1144` | pass | Query geometry |
| `M405 P1144 A B C` | pass, steps/rev | Change and save Theta steps/revolution |
| `M406 P1144` | pass | Query Theta steps/revolution |
| `M609 P1144 A B C` | pass, angles | Change and save home angles |
| `M610 P1144` | pass | Query home angles |

The password is compiled into the open-source firmware and is only an accidental
change guard, not authentication.

`M410` and `M422` have empty implementations and are not dispatched by the
parser. `M600` and `M601` acknowledge but do no work. They must not be presented
as working features.

## 8. Boot, persistence, homing, and stop behavior

At boot, compiled defaults are created first, then stored values overwrite many
of them. The firmware prefers a 128-kbit external SPI EEPROM; if it cannot be
initialized, it falls back to internal flash EEPROM. It prints `Init Success!`
after initialization.

The main arm stepper drivers are enabled during startup. The end-effector output
is reset to vacuum-off (MOSFET HIGH), all digital outputs are driven LOW, and all
three servo objects are initially written to 90°. The configured gripper “open”
position is not applied after servo attachment, so startup must not be assumed to
leave the gripper mechanically open.

`G28` performs three homing phases: seek switches, back off 10°, then approach
again at half the initial speed. It sets the software current position to the
configured home before the physical routine completes. An interrupted or failed
home therefore leaves the reported pose untrustworthy. It also writes all servo
channels; in the current initialization path that can send W to 90° and U and
the gripper toward 0°, independently of the arm homing motion.

The two-channel firmware E-stop condition is both inputs HIGH. It sets a software
stop flag and stops further trajectory generation, but it does **not** disable
stepper drivers or force vacuum/digital outputs off. Releasing the inputs clears
the stop flags in the next main loop iteration. This is not a safety-rated stop
and must not replace hardwired removal of hazardous energy.

Text controls exist for `Emergency:Stop`, `Emergency:Pause`,
`Emergency:Resume`, and `Emergency:Reset`. Reset reboots the MCU. Stop and pause
set the same software flag. Resume clears it. These commands are operational
controls, not functional-safety functions.

The physical home-button handler appears polarity/state inverted for an
`INPUT_PULLUP` input. As written, it starts timing on a release and performs an
action on the next press, based on the intervening HIGH interval: 100 ms–2 s
requests homing and 2 s or longer requests an MCU reset. Treat the button as
unsafe/unverified until this is corrected and physically tested.

## 9. Inspection procedure for this specific robot

Record every observed result in the validation record at the end of this file.
Do not proceed to the next phase if identity, wiring, or safety behavior differs
from this baseline.

### Phase A — offline and power-isolated

1. Confirm board revision, motor-driver type, reduction ratio, servo models,
   end-effector type, and all connector labels against the pin table.
2. Measure arm dimensions instead of trusting EEPROM or compile-time geometry.
3. Verify that the physical E-stop removes hazardous energy independently of the
   MCU and application.
4. Check switch polarity and mechanical overtravel by measurement/continuity.
5. Back up the firmware binary and configuration before changing anything.

### Phase B — powered, motion inhibited

1. Mechanically prevent unexpected motion or disable motor power while keeping
   controller communications available.
2. Open exactly one transport. For USB use 115200 baud, 8-N-1, LF termination.
3. Run only the passive identification sequence below, one line at a time:

   ```text
   IsDelta
   Infor
   FirmwareVersion
   ROBOTMODEL
   IMEI
   Date
   Address
   Storage
   DeltaState
   Position
   PositionOffset
   Angle
   HTs
   ```

4. Manually actuate each home switch with motor power inhibited and confirm the
   corresponding `HTs` bit changes in Theta 1/2/3 order.
5. Read I0–I3 and A0–A1 individually with `M7`, verifying wiring and scaling.
6. Query, but do not change, the stored configuration:

   ```text
   M58
   M220 I0
   M220 I1
   M220 I2
   M220 I3
   M404 P1144
   M406 P1144
   M420
   M421
   M610 P1144
   ```

### Phase C — supervised homing

1. Establish an exclusion zone, low-energy setup, external stop observer, and a
   recovery plan for a switch that is not reached.
2. Confirm each arm moves toward its own switch with a very small manual test or
   driver-level procedure. Do not use `G28` to discover motor direction.
3. Confirm that the application can stop transmission and that the hardwired
   E-stop removes motion energy.
4. Run `G28` once under direct observation. Abort on wrong direction, unexpected
   servo motion, switch mismatch, or failure to finish promptly.
5. Re-read `Angle`, `Position`, `HTs`, and `DeltaState`; compare the physical pose
   to the reported home pose.

### Phase D — reduced-speed motion validation

1. Apply a conservative temporary motion profile; do not begin with firmware
   defaults.
2. With no payload and the end effector off, validate small single-axis Cartesian
   increments near the center of the workspace.
3. Measure actual X/Y/Z displacement and direction. Then validate W and U
   separately because they move asynchronously.
4. Test workspace rejection, loss of communications, software stop, physical
   E-stop, and power recovery without relying on the application UI alone.
5. Only after those checks, validate vacuum/gripper outputs and production-speed
   trajectories.

## 10. Known firmware concerns to account for

The following findings are source-review results, not hypothetical UI concerns:

1. **The firmware E-stop is not safety-rated.** It does not disable drivers or
   outputs, and releasing the inputs clears the stop flags automatically.
2. **Homing can fail without a defined timeout/error result.** If a switch is not
   reached, the homing state can remain active indefinitely.
3. **Software pose is set to home before homing completes.** Interrupted homing
   can make telemetry incorrect.
4. **Safe Z is stored but not enforced.** Host-side safe-Z logic remains required.
5. **G0 and G1 are identical.** Do not assume rapid versus feed semantics.
6. **W/U motion is not synchronized with XYZ motion.** Servo commands are issued
   before the main-arm trajectory.
7. **The variable named diameter is used as a radius.** Confirm the intended
   physical XY envelope before relying on the 170 mm default.
8. **Inverse-kinematics return values are ignored in some motion paths.** Endpoint
   and trajectory validation need firmware hardening before unattended use.
9. **Persistence validation is incomplete.** Several EEPROM-loaded values are
   accepted without range/version/CRC checks.
10. **Queue replies are transport-global.** Concurrent clients can receive each
    other's replies; queue overflow is not reported.
11. **Parser failures can become numeric zero.** Unknown tokens are ignored and
    malformed numbers use Arduino `toFloat()` behavior.
12. **Factory validation has gaps.** Geometry checks permit some negative or
    partially invalid values; the factory password is public.
13. **`M501` and `M502` use nonstandard meanings.** A mistaken UI mapping can
    overwrite calibration with defaults.
14. **`Stepper::resume()` pauses the timer.** Any future code relying on this
    method will not resume motion as its name suggests.
15. **The build is not fully reproducible.** The firmware README requires manual
    edits to PlatformIO's STM32 Arduino framework for SPI and UART definitions.
16. **The repository Ethernet test is stale.** It targets `192.168.1.211:23`,
    sends a non-protocol string without LF, and does not match current defaults.
17. **The physical home-button state machine appears inverted.** It can home or
    reset on a later button transition using the interval between transitions,
    rather than a conventional measured press duration.
18. **`M402` does not really persist the Z span.** It calls the geometry-save
    routine, but that routine does not write `MOVING_AREA_Z`.
19. **Arc direction should not be assumed to follow standard G-code.** `G2` and
    `G3` pass opposite boolean values to an implementation whose positive-angle
    convention needs physical verification.
20. **Required parameters are not always enforced.** For example, omitting `S`
    from `M203` or `M205`, or `A` from `M204`, can apply the parser sentinel or a
    clamped maximum instead of rejecting the command.

Until these items are resolved and physically validated, Delta X Software should
label the connection as “unverified”, serialize all commands, gate motion behind
an explicit homed state, and keep configuration commands out of normal operator
workflows.

## 11. Validation record

Create a dated copy of this table for each robot and firmware update.

| Check | Expected baseline | Observed | Pass/Fail | Date / operator |
| --- | --- | --- | --- | --- |
| Firmware identity | 1.08 / DELTA_X_3 / V1.02 |  |  |  |
| Firmware commit/build provenance | Recorded and reproducible |  |  |  |
| Storage backend | External or flash, explicitly recorded |  |  |  |
| Theta home switches | Correct bit, polarity, and order |  |  |  |
| Hardwired E-stop | Hazardous energy removed independently |  |  |  |
| Software stop | Behavior characterized, not safety credited |  |  |  |
| Motor directions | All three move toward expected switch |  |  |  |
| Homing | Completes once, pose physically verified |  |  |  |
| Geometry | Measured values match stored values |  |  |  |
| Steps/revolution | Measured values match stored values |  |  |  |
| XYZ direction/scale | Small moves measured correctly |  |  |  |
| W/U direction/range | Separately measured correctly |  |  |  |
| Vacuum/gripper safe state | Off and safe mechanical position independently verified |  |  |  |
| DI/AI mapping | All channels verified |  |  |  |
| DOUT mapping | All channels verified at safe load |  |  |  |
| Communication loss | Defined, tested recovery |  |  |  |
| Workspace rejection | Boundary cases rejected safely |  |  |  |

## 12. Firmware source map

| Concern | Primary source |
| --- | --- |
| Identity, limits, Ethernet defaults | `Delta_Firmware/config.h` |
| Geometry and home defaults | `Delta_Firmware/Geometry.h` |
| MCU pin mapping | `Delta_Firmware/pin.h` |
| Boot sequence and queue capacity | `Delta_Firmware/Delta_Firmware.cpp` |
| Text protocol and passive queries | `Delta_Firmware/GCodeReceiver.cpp` |
| G/M parsing and dispatch | `Delta_Firmware/GCodeExecute.cpp` |
| Motion preparation | `Delta_Firmware/Motion.cpp` |
| Trajectory and homing | `Delta_Firmware/Planner.cpp`, `Stepper.cpp` |
| Workspace/power/E-stop checks | `Delta_Firmware/Tool.cpp` |
| Outputs, inputs, configuration | `Delta_Firmware/Control.cpp`, `EndEffector.cpp` |
| Persistence | `Delta_Firmware/Storage.cpp`, `Storage.h` |
| Response formats | `Delta_Firmware/GCodeSend.cpp` |
| Build setup | `platformio.ini`, firmware `README.md` |

This reference deliberately distinguishes firmware behavior from application
features. Camera detection, conveyor tracking, multi-robot scheduling, and
G-Script orchestration belong to Delta X Software and are not implemented by
this robot-controller firmware.
