[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$PackageDirectory
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$PackageDirectory = (Resolve-Path -LiteralPath $PackageDirectory).Path
if (-not (Test-Path -LiteralPath $PackageDirectory -PathType Container)) {
    throw "Release package directory was not found: $PackageDirectory"
}

$requiredFiles = @(
    'BUILD-METADATA.json',
    'DEPLOYMENT.txt',
    'DeltaRobotSoftware.exe',
    'docs\block-programming.md',
    'docs\camera-gige-usb3.md',
    'docs\Delta-X-Multi-Robot-Installation-Calibration-Operation-Guide.docx',
    'docs\external-vision.md',
    'docs\gscript-design.md',
    'docs\gscript-runtime.md',
    'docs\multi-robot-conveyor-sorting.md',
    'docs\variable-manager.md',
    'gcode\README.txt',
    'LICENSE',
    'licenses\OpenCV-Apache-2.0.txt',
    'licenses\OpenCV-notice.md',
    'licenses\GPL-3.0-only.txt',
    'licenses\LGPL-3.0-only.txt',
    'licenses\Qt-runtime-notice.md',
    'NOTICE',
    'plugin\BlockProgrammingPlugin.dll',
    'models\README.txt',
    'SHA256SUMS.txt',
    'THIRD_PARTY_NOTICES.md',
    'VERSION.txt',
    'version.json'
)
foreach ($relativePath in $requiredFiles) {
    if (-not (Test-Path -LiteralPath (Join-Path $PackageDirectory $relativePath) -PathType Leaf)) {
        throw "Required release file is missing: $relativePath"
    }
}

$metadataPath = Join-Path $PackageDirectory 'BUILD-METADATA.json'
$metadata = Get-Content -LiteralPath $metadataPath -Raw | ConvertFrom-Json
if ($metadata.version -notmatch '^\d+\.\d+\.\d+$') {
    throw 'BUILD-METADATA.json does not contain a semantic version.'
}
$version = (Get-Content -LiteralPath (Join-Path $PackageDirectory 'VERSION.txt') -Raw).Trim()
if ($metadata.version -ne $version) {
    throw 'BUILD-METADATA.json version does not match VERSION.txt.'
}

$allFiles = @(Get-ChildItem -LiteralPath $PackageDirectory -Recurse -File)
$forbiddenNames = @(
    'coordinates.txt',
    'customUI.ini',
    'mylog.txt',
    'settings.ini',
    'token.txt'
)
foreach ($file in $allFiles) {
    if ($forbiddenNames -contains $file.Name) {
        throw "Local runtime state must not be packaged: $($file.Name)"
    }
    $relativePath = $file.FullName.Substring(
        $PackageDirectory.TrimEnd('\').Length).TrimStart('\').Replace('\', '/')
    if ($relativePath -match '(?i)(\.vi\.|huong[-_ ]?dan|cai[-_ ]?dat|hieu[-_ ]?chuan|van[-_ ]?hanh)') {
        throw "Localized legacy filename must not be packaged: $relativePath"
    }
    if ($relativePath.StartsWith('models/', [System.StringComparison]::OrdinalIgnoreCase) -and
        $relativePath -ne 'models/README.txt') {
        throw "Model packaging requires a separate provenance review: $relativePath"
    }
}

$pluginPath = Join-Path $PackageDirectory 'plugin\IndustrialCameraPlugin.dll'
$pluginPresent = Test-Path -LiteralPath $pluginPath -PathType Leaf
if ([bool]$metadata.industrialCameraPluginIncluded -ne $pluginPresent) {
    throw 'Industrial-camera plugin presence does not match BUILD-METADATA.json.'
}
$blockPluginPath = Join-Path $PackageDirectory 'plugin\BlockProgrammingPlugin.dll'
$blockPluginPresent = Test-Path -LiteralPath $blockPluginPath -PathType Leaf
if (-not $blockPluginPresent -or
    -not [bool]$metadata.blockProgrammingPluginIncluded) {
    throw 'The required Block Programming plugin is missing or not declared in BUILD-METADATA.json.'
}

$declaredVendorRuntimes = @($metadata.vendorRuntimes)
$knownVendorRuntimes = @(
    'MvCameraControl.dll',
    'GCBase_MD_VC141_v3_1_Basler_pylon.dll',
    'GenApi_MD_VC141_v3_1_Basler_pylon.dll',
    'PylonUtility_v9.dll',
    'PylonBase_v9.dll',
    'PylonGUI_v9.dll'
)
foreach ($runtimeName in $knownVendorRuntimes) {
    $runtimePresent = Test-Path -LiteralPath (
        Join-Path $PackageDirectory $runtimeName) -PathType Leaf
    if ($runtimePresent -ne ($declaredVendorRuntimes -contains $runtimeName)) {
        throw "Vendor runtime declaration does not match package contents: $runtimeName"
    }
}

$manifestPath = Join-Path $PackageDirectory 'SHA256SUMS.txt'
$manifestEntries = @{}
foreach ($line in Get-Content -LiteralPath $manifestPath) {
    if ($line -notmatch '^([0-9a-f]{64})  (.+)$') {
        throw "Malformed SHA256SUMS.txt line: $line"
    }
    $expectedHash = $Matches[1]
    $relativePath = $Matches[2].Replace('\', '/')
    if ($manifestEntries.ContainsKey($relativePath)) {
        throw "Duplicate checksum entry: $relativePath"
    }
    $targetPath = Join-Path $PackageDirectory $relativePath
    if (-not (Test-Path -LiteralPath $targetPath -PathType Leaf)) {
        throw "Checksum target is missing: $relativePath"
    }
    $actualHash = (Get-FileHash -LiteralPath $targetPath -Algorithm SHA256).Hash.ToLowerInvariant()
    if ($actualHash -ne $expectedHash) {
        throw "Checksum mismatch: $relativePath"
    }
    $manifestEntries[$relativePath] = $expectedHash
}

foreach ($file in $allFiles) {
    if ($file.Name -eq 'SHA256SUMS.txt') {
        continue
    }
    $relativePath = $file.FullName.Substring(
        $PackageDirectory.TrimEnd('\').Length).TrimStart('\').Replace('\', '/')
    if (-not $manifestEntries.ContainsKey($relativePath)) {
        throw "File is missing from SHA256SUMS.txt: $relativePath"
    }
}

$msvcRuntimes = @($allFiles | Where-Object {
    $_.DirectoryName -eq $PackageDirectory -and
    $_.Name -match '^(concrt|msvcp|vccorlib|vcruntime).*\.dll$'
})
if ($msvcRuntimes.Count -eq 0) {
    throw 'No MSVC runtime DLL is present in the portable package.'
}

Write-Output "Release package is valid: $PackageDirectory"
Write-Output "Files: $($allFiles.Count); checksums: $($manifestEntries.Count); MSVC runtimes: $($msvcRuntimes.Count)"
