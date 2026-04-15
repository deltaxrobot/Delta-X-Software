# Delta X Virtual Device Simulator

This simulator exposes TCP endpoints that Delta X Software can connect to with the built-in `Socket` connection mode.
It also creates real PTY-backed virtual serial ports on macOS so you can test the `Serial` path as well.
The simulator UI includes buttons to copy the current endpoint mapping and open the mapping file directly.

Default ports:

- `robot`: `127.0.0.1:8855`
- `conveyor`: `127.0.0.1:8856`
- `encoder`: `127.0.0.1:8857`
- `slider`: `127.0.0.1:8858`
- `device`: `127.0.0.1:8859`

Virtual serial ports:

- Each launch creates one PTY serial device per simulated device.
- The current mapping is written to `/tmp/deltax-virtual-device-endpoints.txt`.
- Example lines:
  - `robot,tcp=127.0.0.1:8855,serial=/dev/ttys174`
  - `encoder,tcp=127.0.0.1:8857,serial=/dev/ttys176`

What it emulates:

- `robot`
  - `IsDelta` -> `YesDelta`
  - `Position` -> `X,Y,Z,W,U,V`
  - `G28`, `M85`, `M84`, `G0/G00/G1/G01`, `M03`, `M05`, `M203`, `M204`, `M205`
- `conveyor`
  - `M310`, `M311`, `M312`, `M313`
  - `M422 Cn` -> `Pn:value`
- `encoder`
  - `M316`, `M317`, `M318`, `M319`
  - `M317` -> `P1:value`
- `slider`
  - `M320`, `M321`, `M322`, `M323`
- `device`
  - `PING` -> `PONG`
  - everything else -> `Ok`

## Build

```bash
cd /Users/trungdoanhong/Developer/Delta-X-Software/simulator
mkdir -p build
cd build
"$HOME/Qt/6.10.1/macos/bin/qmake" ../DeltaXVirtualDeviceSimulator.pro
make -j"$(sysctl -n hw.ncpu)"
```

## Package as macOS app

```bash
cd /Users/trungdoanhong/Developer/Delta-X-Software/simulator
./package-simulator-macos.sh
open /Users/trungdoanhong/Developer/Delta-X-Software/simulator/build/DeltaXVirtualDeviceSimulator.app
```

## Run

```bash
cd /Users/trungdoanhong/Developer/Delta-X-Software/simulator
./run-virtual-device-simulator.sh
```

## Connect from Delta X Software

1. Open the device connection flow in Delta X Software.
2. Choose `Socket` and enter one of the simulator addresses above, or choose `Serial`.
3. For `Serial`, use `Enter custom device path...` and paste the PTY path from `/tmp/deltax-virtual-device-endpoints.txt`.
