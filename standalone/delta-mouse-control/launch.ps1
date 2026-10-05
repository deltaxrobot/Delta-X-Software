param([switch]$Simulate)
$ErrorActionPreference = 'Stop'
$environmentPath = Join-Path $PSScriptRoot '.venv'
$pythonPath = Join-Path $environmentPath 'Scripts\python.exe'
if (-not (Test-Path -LiteralPath $pythonPath)) {
    python -m venv $environmentPath
    if ($LASTEXITCODE -ne 0) { throw 'Could not create the Python virtual environment.' }
}
& $pythonPath -c 'import importlib.util, sys; sys.exit(0 if all(importlib.util.find_spec(name) for name in ("PySide6", "serial")) else 1)'
if ($LASTEXITCODE -ne 0) {
    & $pythonPath -m pip install -r (Join-Path $PSScriptRoot 'requirements.txt')
    if ($LASTEXITCODE -ne 0) { throw 'Could not install dependencies.' }
}
$launchArguments = @((Join-Path $PSScriptRoot 'run.py'))
if ($Simulate) { $launchArguments += '--simulate' }
& $pythonPath @launchArguments
exit $LASTEXITCODE
