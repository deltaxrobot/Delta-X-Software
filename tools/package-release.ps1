[CmdletBinding()]
param(
    [string]$BuildDirectory,
    [string]$OutputDirectory,
    [string]$QtBinDirectory,
    [string]$QtLicenseDirectory,
    [string]$OpenCvRuntimePath,
    [string]$MsVcRuntimeDirectory,
    [string]$BlockProgrammingPluginPath,
    [string]$IndustrialCameraPluginPath,
    [string]$VendorRuntimeDirectory,
    [switch]$AcknowledgeVendorRuntimeLicense,
    [switch]$AllowDirtySource
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repositoryRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
if ([string]::IsNullOrWhiteSpace($BuildDirectory)) {
    $BuildDirectory = Join-Path $repositoryRoot 'build\cmake-release'
}
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $stamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    $OutputDirectory = Join-Path $repositoryRoot "dist\DeltaRobotSoftware-$stamp"
}

$BuildDirectory = [IO.Path]::GetFullPath($BuildDirectory)
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
if ($OutputDirectory.TrimEnd('\') -eq $repositoryRoot.TrimEnd('\')) {
    throw 'The release output directory cannot be the repository root.'
}
if (Test-Path -LiteralPath $OutputDirectory) {
    throw "Output directory already exists; choose a new path: $OutputDirectory"
}

$executableCandidates = @(
    (Join-Path $BuildDirectory 'DeltaRobotSoftware.exe'),
    (Join-Path $BuildDirectory 'release\DeltaRobotSoftware.exe'),
    (Join-Path $BuildDirectory 'Release\DeltaRobotSoftware.exe')
)
$executable = $executableCandidates |
    Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |
    Select-Object -First 1
if ([string]::IsNullOrWhiteSpace($executable)) {
    throw "DeltaRobotSoftware.exe was not found below: $BuildDirectory"
}
$cliExecutable = Join-Path (Split-Path -Parent $executable) 'delta-x-cli.exe'
if (-not (Test-Path -LiteralPath $cliExecutable -PathType Leaf)) {
    throw 'delta-x-cli.exe was not found next to the application. Build the delta-x-cli target first.'
}

if ([string]::IsNullOrWhiteSpace($QtBinDirectory)) {
    $deployCommand = Get-Command windeployqt.exe -ErrorAction SilentlyContinue
    if ($null -ne $deployCommand) {
        $QtBinDirectory = Split-Path -Parent $deployCommand.Source
    }
    else {
        $cmakeCache = Join-Path $BuildDirectory 'CMakeCache.txt'
        if (Test-Path -LiteralPath $cmakeCache -PathType Leaf) {
            $qtCacheEntry = Get-Content -LiteralPath $cmakeCache |
                Select-String -Pattern '^Qt6_DIR:[^=]*=(.+)$' |
                Select-Object -First 1
            if ($null -ne $qtCacheEntry) {
                $qt6Directory = $qtCacheEntry.Matches[0].Groups[1].Value
                $QtBinDirectory = Split-Path -Parent (
                    Split-Path -Parent (Split-Path -Parent $qt6Directory))
                $QtBinDirectory = Join-Path $QtBinDirectory 'bin'
            }
        }
    }
}
if ([string]::IsNullOrWhiteSpace($QtBinDirectory)) {
    throw 'Qt bin directory was not discovered. Pass -QtBinDirectory explicitly.'
}
$QtBinDirectory = [IO.Path]::GetFullPath($QtBinDirectory)
$deployTool = Join-Path $QtBinDirectory 'windeployqt.exe'
if (-not (Test-Path -LiteralPath $deployTool -PathType Leaf)) {
    throw "windeployqt was not found: $deployTool"
}

if ([string]::IsNullOrWhiteSpace($QtLicenseDirectory)) {
    $dependencies = Get-Content -LiteralPath (
        Join-Path $repositoryRoot 'config\dependencies.json') -Raw | ConvertFrom-Json
    $qtLicenseCandidate = Join-Path $repositoryRoot "build\dependencies\qt-licenses-$($dependencies.qt.ciVersion)"
    if (Test-Path -LiteralPath $qtLicenseCandidate -PathType Container) {
        $QtLicenseDirectory = $qtLicenseCandidate
    }
}
if ([string]::IsNullOrWhiteSpace($QtLicenseDirectory)) {
    throw 'Qt license documents were not discovered. Run tools/install-qt-licenses.ps1 or pass -QtLicenseDirectory.'
}
$QtLicenseDirectory = [IO.Path]::GetFullPath($QtLicenseDirectory)
$qtLgplPath = Join-Path $QtLicenseDirectory 'LGPL-3.0-only.txt'
$qtGplPath = Join-Path $QtLicenseDirectory 'GPL-3.0-only.txt'
foreach ($licensePath in @($qtLgplPath, $qtGplPath)) {
    if (-not (Test-Path -LiteralPath $licensePath -PathType Leaf)) {
        throw "Required Qt license document was not found: $licensePath"
    }
}

if ([string]::IsNullOrWhiteSpace($OpenCvRuntimePath)) {
    $OpenCvRuntimePath = Join-Path $repositoryRoot '3rd-party\opencv\build\x64\vc15\bin\opencv_world400.dll'
}
$OpenCvRuntimePath = [IO.Path]::GetFullPath($OpenCvRuntimePath)
if (-not (Test-Path -LiteralPath $OpenCvRuntimePath -PathType Leaf)) {
    throw "OpenCV runtime was not found. Pass -OpenCvRuntimePath: $OpenCvRuntimePath"
}

if ([string]::IsNullOrWhiteSpace($BlockProgrammingPluginPath)) {
    $blockPluginCandidates = @(
        (Join-Path $BuildDirectory 'plugin\BlockProgrammingPlugin.dll'),
        (Join-Path $BuildDirectory 'plugin\Release\BlockProgrammingPlugin.dll'),
        (Join-Path $BuildDirectory 'release\plugin\BlockProgrammingPlugin.dll'),
        (Join-Path $BuildDirectory 'Release\plugin\BlockProgrammingPlugin.dll')
    )
    $BlockProgrammingPluginPath = $blockPluginCandidates |
        Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |
        Select-Object -First 1
}
if ([string]::IsNullOrWhiteSpace($BlockProgrammingPluginPath)) {
    throw 'Block Programming plugin was not found. Build the default CMake target or pass -BlockProgrammingPluginPath.'
}
$BlockProgrammingPluginPath = [IO.Path]::GetFullPath($BlockProgrammingPluginPath)
if (-not (Test-Path -LiteralPath $BlockProgrammingPluginPath -PathType Leaf)) {
    throw "Block Programming plugin was not found: $BlockProgrammingPluginPath"
}

if (-not [string]::IsNullOrWhiteSpace($IndustrialCameraPluginPath)) {
    $IndustrialCameraPluginPath = [IO.Path]::GetFullPath($IndustrialCameraPluginPath)
    if (-not (Test-Path -LiteralPath $IndustrialCameraPluginPath -PathType Leaf)) {
        throw "Industrial camera plugin was not found: $IndustrialCameraPluginPath"
    }
}
if (-not [string]::IsNullOrWhiteSpace($VendorRuntimeDirectory)) {
    if ([string]::IsNullOrWhiteSpace($IndustrialCameraPluginPath)) {
        throw '-VendorRuntimeDirectory requires -IndustrialCameraPluginPath.'
    }
    if (-not $AcknowledgeVendorRuntimeLicense) {
        throw 'Pass -AcknowledgeVendorRuntimeLicense after verifying vendor redistribution rights.'
    }
    $VendorRuntimeDirectory = [IO.Path]::GetFullPath($VendorRuntimeDirectory)
    if (-not (Test-Path -LiteralPath $VendorRuntimeDirectory -PathType Container)) {
        throw "Vendor runtime directory was not found: $VendorRuntimeDirectory"
    }
}

$gitCommit = 'unknown'
$sourceDirty = $false
if (Test-Path -LiteralPath (Join-Path $repositoryRoot '.git')) {
    $gitCommit = (& git -C $repositoryRoot rev-parse HEAD).Trim()
    if ($LASTEXITCODE -ne 0) {
        throw 'Unable to determine the source Git commit.'
    }
    $sourceDirty = @(& git -C $repositoryRoot status --porcelain).Count -gt 0
    if ($sourceDirty -and -not $AllowDirtySource) {
        throw 'The source tree is dirty. Commit/stash it or pass -AllowDirtySource for a development package.'
    }
}

$outputParent = Split-Path -Parent $OutputDirectory
if (-not (Test-Path -LiteralPath $outputParent -PathType Container)) {
    New-Item -ItemType Directory -Path $outputParent | Out-Null
}
$stagingDirectory = "$OutputDirectory.partial-$PID"
if (Test-Path -LiteralPath $stagingDirectory) {
    throw "Staging directory already exists: $stagingDirectory"
}
New-Item -ItemType Directory -Path $stagingDirectory | Out-Null

$packagedExecutable = Join-Path $stagingDirectory 'DeltaRobotSoftware.exe'
Copy-Item -LiteralPath $executable -Destination $packagedExecutable
Copy-Item -LiteralPath $cliExecutable -Destination $stagingDirectory
Copy-Item -LiteralPath $OpenCvRuntimePath -Destination $stagingDirectory

& $deployTool --release --no-translations --no-compiler-runtime `
    --no-system-dxc-compiler $packagedExecutable
if ($LASTEXITCODE -ne 0) {
    throw "windeployqt failed with exit code $LASTEXITCODE. Partial output: $stagingDirectory"
}

if ([string]::IsNullOrWhiteSpace($MsVcRuntimeDirectory)) {
    $runtimeCandidates = @()
    if (-not [string]::IsNullOrWhiteSpace($env:VCToolsRedistDir)) {
        $environmentCandidate = Join-Path $env:VCToolsRedistDir 'x64\Microsoft.VC143.CRT'
        if (Test-Path -LiteralPath $environmentCandidate -PathType Container) {
            $runtimeCandidates += Get-Item -LiteralPath $environmentCandidate
        }
    }

    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (Test-Path -LiteralPath $vswhere -PathType Leaf) {
        $visualStudioRoots = @(& $vswhere -products * -format value -property installationPath)
        foreach ($visualStudioRoot in $visualStudioRoots) {
            $redistRoot = Join-Path $visualStudioRoot 'VC\Redist\MSVC'
            if (Test-Path -LiteralPath $redistRoot -PathType Container) {
                $runtimeCandidates += Get-ChildItem -LiteralPath $redistRoot -Directory |
                    ForEach-Object {
                        $candidate = Join-Path $_.FullName 'x64\Microsoft.VC143.CRT'
                        if (Test-Path -LiteralPath $candidate -PathType Container) {
                            Get-Item -LiteralPath $candidate
                        }
                    }
            }
        }
    }
    $MsVcRuntimeDirectory = $runtimeCandidates |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
}
if ([string]::IsNullOrWhiteSpace($MsVcRuntimeDirectory) -or
    -not (Test-Path -LiteralPath $MsVcRuntimeDirectory -PathType Container)) {
    throw 'MSVC x64 runtime directory was not found. Pass -MsVcRuntimeDirectory explicitly.'
}
$MsVcRuntimeDirectory = [IO.Path]::GetFullPath($MsVcRuntimeDirectory)
$msvcRuntimeFiles = @(Get-ChildItem -LiteralPath $MsVcRuntimeDirectory -Filter '*.dll' -File)
if ($msvcRuntimeFiles.Count -eq 0) {
    throw "No MSVC runtime DLL was found in: $MsVcRuntimeDirectory"
}
$msvcRuntimeFiles | Copy-Item -Destination $stagingDirectory -Force
$copiedMsVcRuntimes = @($msvcRuntimeFiles | Select-Object -ExpandProperty Name)

$rootReleaseFiles = @(
    'GScript_Documentation.html',
    'LICENSE',
    'NOTICE',
    'THIRD_PARTY_NOTICES.md',
    'VERSION.txt',
    'version.json'
)
foreach ($relativePath in $rootReleaseFiles) {
    $sourcePath = Join-Path $repositoryRoot $relativePath
    if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
        throw "Required release file not found: $sourcePath"
    }
    Copy-Item -LiteralPath $sourcePath -Destination $stagingDirectory
}

$licenseOutput = Join-Path $stagingDirectory 'licenses'
New-Item -ItemType Directory -Path $licenseOutput | Out-Null
$openCvNotice = Join-Path $repositoryRoot 'licenses\OpenCV-notice.md'
if (-not (Test-Path -LiteralPath $openCvNotice -PathType Leaf)) {
    throw "OpenCV dependency notice not found: $openCvNotice"
}
Copy-Item -LiteralPath $openCvNotice -Destination $licenseOutput
Copy-Item -LiteralPath (Join-Path $repositoryRoot 'LICENSE') -Destination (
    Join-Path $licenseOutput 'OpenCV-Apache-2.0.txt')
$qtRuntimeNotice = Join-Path $repositoryRoot 'licenses\Qt-runtime-notice.md'
if (-not (Test-Path -LiteralPath $qtRuntimeNotice -PathType Leaf)) {
    throw "Qt runtime notice not found: $qtRuntimeNotice"
}
Copy-Item -LiteralPath $qtRuntimeNotice -Destination $licenseOutput
Copy-Item -LiteralPath $qtLgplPath -Destination $licenseOutput
Copy-Item -LiteralPath $qtGplPath -Destination $licenseOutput

$scriptOutput = Join-Path $stagingDirectory 'script-example'
New-Item -ItemType Directory -Path $scriptOutput | Out-Null
foreach ($relativePath in @(
    'script-example\cli-smoke.gcode',
    'script-example\dxv1_client.py',
    'script-example\receive_image_json.py',
    'script-example\yolov8_detect.py'
)) {
    $sourcePath = Join-Path $repositoryRoot $relativePath
    if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
        throw "External Vision example not found: $sourcePath"
    }
    Copy-Item -LiteralPath $sourcePath -Destination $scriptOutput
}
$sortingExample = Join-Path $repositoryRoot 'script-example\multi-robot-sorting'
if (-not (Test-Path -LiteralPath $sortingExample -PathType Container)) {
    throw "Multi-robot G-Script example not found: $sortingExample"
}
Copy-Item -LiteralPath $sortingExample -Destination $scriptOutput -Recurse
$commandTour = Join-Path $repositoryRoot 'script-example\gscript-command-tour'
if (-not (Test-Path -LiteralPath $commandTour -PathType Container)) {
    throw "G-Script command tour not found: $commandTour"
}
Copy-Item -LiteralPath $commandTour -Destination $scriptOutput -Recurse
$blockExample = Join-Path $repositoryRoot 'script-example\block-programming'
if (-not (Test-Path -LiteralPath $blockExample -PathType Container)) {
    throw "Block Programming example not found: $blockExample"
}
Copy-Item -LiteralPath $blockExample -Destination $scriptOutput -Recurse

$pythonPluginSource = Join-Path $repositoryRoot 'plugin\python'
if (Test-Path -LiteralPath $pythonPluginSource -PathType Container) {
    $pluginOutput = Join-Path $stagingDirectory 'plugin'
    New-Item -ItemType Directory -Path $pluginOutput -Force | Out-Null
    Copy-Item -LiteralPath $pythonPluginSource -Destination $pluginOutput -Recurse
}
$pluginOutput = Join-Path $stagingDirectory 'plugin'
New-Item -ItemType Directory -Path $pluginOutput -Force | Out-Null
Copy-Item -LiteralPath $BlockProgrammingPluginPath -Destination $pluginOutput

$docsOutput = Join-Path $stagingDirectory 'docs'
New-Item -ItemType Directory -Path $docsOutput | Out-Null
$releaseDocs = @(
    'cli.md',
    'Delta-X-Multi-Robot-Installation-Calibration-Operation-Guide.docx',
    'camera-gige-usb3.md',
    'phone-camera.md',
    'block-programming.md',
    'external-vision.md',
    'gscript-runtime.md',
    'gscript-command-tour.md',
    'gscript-design.md',
    'gcode-motion-engine.md',
    'mouse-robot-control.md',
    'multi-robot-conveyor-sorting.md',
    'variable-manager.md'
)
foreach ($docName in $releaseDocs) {
    $docPath = Join-Path $repositoryRoot "docs\$docName"
    if (-not (Test-Path -LiteralPath $docPath -PathType Leaf)) {
        throw "Release documentation not found: $docPath"
    }
    Copy-Item -LiteralPath $docPath -Destination $docsOutput
}

foreach ($runtimeDirectory in @('gcode', 'models')) {
    New-Item -ItemType Directory -Path (
        Join-Path $stagingDirectory $runtimeDirectory) | Out-Null
}
Copy-Item -LiteralPath $commandTour -Destination (Join-Path $stagingDirectory 'gcode\GScript Command Tour') -Recurse
Copy-Item -LiteralPath $blockExample -Destination (Join-Path $stagingDirectory 'gcode\Block Programming') -Recurse
Set-Content -LiteralPath (Join-Path $stagingDirectory 'gcode\README.txt') -Encoding UTF8 -Value @'
Place operator-reviewed G-Script programs in this directory.
Do not copy machine/customer programs into public release artifacts.
'@
Set-Content -LiteralPath (Join-Path $stagingDirectory 'models\README.txt') -Encoding UTF8 -Value @'
No neural-network model is bundled with Delta X Software.
Install only a model whose source, version, checksum and license are documented.
'@

$vendorRuntimeNames = @(
    'MvCameraControl.dll',
    'GCBase_MD_VC141_v3_1_Basler_pylon.dll',
    'GenApi_MD_VC141_v3_1_Basler_pylon.dll',
    'PylonUtility_v9.dll',
    'PylonBase_v9.dll',
    'PylonGUI_v9.dll'
)
$copiedVendorRuntimes = [System.Collections.Generic.List[string]]::new()
if (-not [string]::IsNullOrWhiteSpace($IndustrialCameraPluginPath)) {
    $pluginOutput = Join-Path $stagingDirectory 'plugin'
    New-Item -ItemType Directory -Path $pluginOutput -Force | Out-Null
    Copy-Item -LiteralPath $IndustrialCameraPluginPath -Destination $pluginOutput

    if (-not [string]::IsNullOrWhiteSpace($VendorRuntimeDirectory)) {
        foreach ($runtimeName in $vendorRuntimeNames) {
            $runtimePath = Get-ChildItem -LiteralPath $VendorRuntimeDirectory -Filter $runtimeName -File -Recurse |
                Select-Object -First 1 -ExpandProperty FullName
            if (-not [string]::IsNullOrWhiteSpace($runtimePath)) {
                Copy-Item -LiteralPath $runtimePath -Destination $stagingDirectory
                $copiedVendorRuntimes.Add($runtimeName)
            }
        }
    }
}

$version = (Get-Content -LiteralPath (Join-Path $repositoryRoot 'VERSION.txt') -Raw).Trim()
$buildMetadata = [ordered]@{
    application = 'Delta X Software'
    version = $version
    createdUtc = (Get-Date).ToUniversalTime().ToString('o')
    gitCommit = $gitCommit
    sourceDirty = $sourceDirty
    qtLicenseDocuments = @('LGPL-3.0-only.txt', 'GPL-3.0-only.txt')
    msvcRuntimes = $copiedMsVcRuntimes
    blockProgrammingPluginIncluded = $true
    industrialCameraPluginIncluded = (-not [string]::IsNullOrWhiteSpace($IndustrialCameraPluginPath))
    vendorRuntimes = @($copiedVendorRuntimes)
}
$buildMetadataJson = $buildMetadata | ConvertTo-Json -Depth 4
Set-Content -LiteralPath (Join-Path $stagingDirectory 'BUILD-METADATA.json') -Value $buildMetadataJson -Encoding UTF8

$cameraStatus = if ([string]::IsNullOrWhiteSpace($IndustrialCameraPluginPath)) {
    'not included'
}
elseif ($copiedVendorRuntimes.Count -eq 0) {
    'plugin included; install vendor runtimes separately'
}
else {
    "plugin included; $($copiedVendorRuntimes.Count) vendor runtime file(s) included"
}
$deploymentNotes = @"
Delta X Software $version - Portable Release
Source commit: $gitCommit
Source dirty: $sourceDirty

The application, Qt runtime, MSVC runtime and OpenCV runtime are included.
The offline Block Programming plugin and operator guide are included.
Industrial camera support: $cameraStatus

UVC USB/USB3 cameras use the built-in Webcam backend. Basler pylon and
Hikrobot MVS runtimes are optional and remain governed by their vendor terms.
No neural-network model, token, machine settings or runtime log is included.
See THIRD_PARTY_NOTICES.md before redistribution.
"@
Set-Content -LiteralPath (Join-Path $stagingDirectory 'DEPLOYMENT.txt') -Value $deploymentNotes -Encoding UTF8

$hashLines = Get-ChildItem -LiteralPath $stagingDirectory -Recurse -File |
    Where-Object Name -ne 'SHA256SUMS.txt' |
    Sort-Object FullName |
    ForEach-Object {
        $relativePath = $_.FullName.Substring(
            $stagingDirectory.TrimEnd('\').Length).TrimStart('\')
        $hash = (Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
        "$hash  $relativePath"
    }
Set-Content -LiteralPath (Join-Path $stagingDirectory 'SHA256SUMS.txt') -Value $hashLines -Encoding ASCII

Move-Item -LiteralPath $stagingDirectory -Destination $OutputDirectory

& (Join-Path $PSScriptRoot 'verify-release.ps1') -PackageDirectory $OutputDirectory
if ($LASTEXITCODE -ne 0) {
    throw "Release-package verification failed: $OutputDirectory"
}

Write-Output "Package created: $OutputDirectory"
Write-Output "Source commit: $gitCommit (dirty: $sourceDirty)"
Write-Output "Industrial camera support: $cameraStatus"
