## Problem

Describe the problem and why this change is needed.

## Solution

Describe the implementation and important trade-offs.

## Validation

- [ ] `python tools/run-tests.py` passes
- [ ] Release build succeeds
- [ ] New timeout/fault/cancellation paths are tested
- [ ] Operator documentation is updated when behavior changes
- [ ] UI screenshots are attached when applicable
- [ ] Hardware-in-the-loop coverage is stated below

Hardware/firmware tested, or reason HIL was not performed:

## Safety and compatibility

- Device commands or stop behavior changed:
- Runtime variables/protocols changed:
- Project/recipe migration required:
- New optional/proprietary dependencies:

## Checklist

- [ ] No credentials, customer data, generated binaries, or vendor installers added
- [ ] No direct `DeviceManager::SendGcode` bypass introduced
- [ ] Queues and waits are bounded
- [ ] Backward compatibility impact is documented
- [ ] Every commit is signed off under DCO 1.1 (`git commit -s`)
- [ ] New dependencies include version, source, license, and redistribution notes
