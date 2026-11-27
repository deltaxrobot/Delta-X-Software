# G-Script acceptance and commissioning

Use this checklist when qualifying a change to the interpreter, device broker,
CLI, plugin primitives, or a production recipe. Record the commit and actual
results; a passing software fixture does not qualify a physical sorting cell.

## Automated software acceptance

Run from the repository root with the development dependencies installed:

```bash
python tools/run-tests.py --test gscript_runtime --test gscript_analyzer --test cli_integration --test control_plane --test variable_manager --test tracking_claim --test plugin_contract --test plugin_manager
```

Use `--build-root` for an isolated test build and `--qt-bin` / `--opencv-dir`
when the dependencies are outside the normal discovery locations. Tests use
temporary settings and simulated providers. Do not connect a physical device to
the test fixtures.

| Boundary | Required evidence |
| --- | --- |
| Language structure | Invalid scope-crossing jumps fail preflight. BREAK, CONTINUE, RETURN, and M99 leave the correct enclosing frames intact. |
| Expressions and parameters | Invalid input faults with a source location; an invalid command is not dispatched to a default device. |
| Worker scheduling | A CPU-only infinite loop accepts queued Stop. A restarted delay is not completed by an old continuation or timer. |
| CLI lifecycle | Run, duplicate-run rejection, Stop, client disconnect, fault reporting, and explicit cell-fault recovery use the real editor/worker composition. |
| Shared variables | Two actual worker threads can communicate through the same project scope. A similarly named variable in another project remains unchanged. |
| Camera callbacks | Pause/resume reaches the window thread. A late result from a stopped capture cannot complete a new capture request. |
| Device ownership | FIFO responses go only to their owner and request. Cancelling queued-only work preserves other owners. |
| Ambiguous device replies | Timeout, active-owner cancellation, disconnect, and safety preemption quarantine the transport. Late replies cannot complete new work; a reentrant timeout callback cannot submit a retry. |
| Transport recovery | A repeated open-state information snapshot and cell Reset do not unlock quarantine. A confirmed closed-to-open transport transition can restore correlation. |
| Plugin failures | A provider rejection and a thrown provider exception become a failed run. The next source statement does not execute, and the provider is called on its owner thread. |
| Tracking ownership | Competing claims, lease expiry, release, completion, and tracking-health faults preserve single ownership. |
| Tracking callbacks | Claim/release/complete/update replies carry a unique request ID. A stopped run's claim result cannot overwrite a restarted run's target, and old legacy replies cannot complete a correlated encoder update. |

Thread-safe variable access does not make a compound expression such as
`#Count = #Count + 1` an atomic transaction across workers. Assign a single writer
to shared counters and use tracking claims for object ownership. Statement
batching is cooperative scheduling, not a hard real-time guarantee. A synchronous
plugin callback can delay Stop until the callback returns.

The desktop uses the correlated tracking API. Older C++ integrations that wire
only the legacy tracking signals retain the legacy uncorrelated reply contract;
new integrations must use the correlated signals and slots. A Stop does not
automatically release an existing claim or mark a physical part completed:
claims expire according to their lease, or the recipe explicitly releases or
completes them after establishing the actual part state.

## Recovering response correlation

The current serial G-code protocol does not echo host request IDs. After an
active request is interrupted, an arriving `Ok` could belong to that request or
to a subsequent stop command. The broker therefore rejects new ordinary work
for that device rather than guessing which request produced the response.

1. Stop/reset the controller so the old operation is no longer producing data.
2. Disconnect and reconnect the affected device to establish a fresh transport
   session. A normal position/settings refresh does not count as a reconnect.
3. If the cell is Faulted, wait for all workers to stop, then use the existing
   explicit cell Reset action after inspecting the machine.
4. Re-establish the recipe's required home/encoder/reference state before Run.

Plugin device providers that do not use the built-in transport controls need an
equivalent confirmed transport/session reset before the host calls
`DeviceCommandBroker::ResetDeviceCommunication(deviceId)`. The method refuses
to reset a device with pending work; it must not be called for an arbitrary
success response or simply because the cell became Ready.

## Physical commissioning record

Record the following for each tested cell:

- Software version, commit, operating system, and Qt/OpenCV versions.
- Robot model and firmware branch/version for every robot; Delta X 3 parameters
  must not be copied to Delta X 1, Delta X 2, or Delta X S without verification.
- Verified device identity/address, conveyor and encoder configuration, camera
  identity, calibration version, and tool/output configuration.
- A reviewed working envelope, home/reference state, pick/place poses, and a
  person supervising the physical test with access to the machine stop.

Perform these steps in order and record pass/fail with observations:

1. Verify read-only identification, telemetry, encoder sign/scale, and camera
   image acquisition against the documented firmware/device contract.
2. Verify guarded Home, low-speed moves, tool output, normal completion, and
   controlled Stop separately for each device.
3. Verify camera-to-conveyor and conveyor-to-robot calibration using stationary
   reference objects, then repeat at a known conveyor speed.
4. Verify capture timestamp/encoder alignment, object position, orientation,
   type, association, and object expiry while the conveyor runs without picking.
5. Verify a single robot picking one known object at reduced speed; measure
   error and account for capture, communication, and tool latency.
6. Verify multiple objects and robots, single ownership per object, unreachable
   object handling, placement rules, and tool-release success/failure handling.
7. Exercise timeout, cable disconnect, camera failure, stopped encoder, plugin
   rejection, Stop/restart, controller reset, and recovery with the actual cell.

## Current review boundary

The 2026-11-28 hardening work exercises software fixtures and mocked device or
camera replies. No physical ports were opened or physical commands sent for
this review. Serial-port enumeration did not establish the identity of a
connected Delta X 3. Motion, live encoder tracking accuracy, vacuum behavior,
multi-robot picking performance, and controller/transport reset recovery remain
unverified on hardware and require the supervised commissioning record above.

The authoritative test results are the logs produced for the checked-out
commit and the matching CI run. This checklist is not a substitute for those
results and does not mark unexecuted hardware steps as passed.
