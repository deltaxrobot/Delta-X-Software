; Requires the test.runtime provider registered by the isolated test harness.
; Installed plugins define their own primitive names and signatures.
M98 Passert(#Examples.Isolated == 1, "Use the isolated command-tour runner")
M98 PtestRuntime(#Examples.PluginProduct, 6, 7)
M98 Passert(#Examples.PluginProduct == 42, "plugin result")
#Examples.PluginPassed = 1
