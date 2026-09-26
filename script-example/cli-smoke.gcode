; Software-only CLI smoke test. No device commands.
#CliSmoke.Result = 6 * 7
M98 Pdelay(100)
M98 Passert(#CliSmoke.Result == 42, "CLI smoke calculation failed")
