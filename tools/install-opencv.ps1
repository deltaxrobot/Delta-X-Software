[CmdletBinding()]
param(
    [string]$DestinationDirectory,
    [string]$DownloadDirectory
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$repositoryRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$dependencyFile = Join-Path $repositoryRoot 'config\dependencies.json'
$dependencies = Get-Content -LiteralPath $dependencyFile -Raw | ConvertFrom-Json
if ($dependencies.schemaVersion -ne 1) {
    throw "Unsupported dependency schema: $($dependencies.schemaVersion)"
}

$opencv = $dependencies.opencv
$windowsPackage = $opencv.windows
if ([string]::IsNullOrWhiteSpace($DestinationDirectory)) {
    $DestinationDirectory = Join-Path $repositoryRoot "build\dependencies\opencv-$($opencv.version)"
}
if ([string]::IsNullOrWhiteSpace($DownloadDirectory)) {
    $DownloadDirectory = Join-Path $repositoryRoot 'build\downloads'
}
$DestinationDirectory = [IO.Path]::GetFullPath($DestinationDirectory)
$DownloadDirectory = [IO.Path]::GetFullPath($DownloadDirectory)

function Get-OpenCvInstallation {
    param([Parameter(Mandatory = $true)][string]$Root)

    if (-not (Test-Path -LiteralPath $Root -PathType Container)) {
        return $null
    }
    $config = Get-ChildItem -LiteralPath $Root -Filter 'OpenCVConfig.cmake' -File -Recurse |
        Select-Object -First 1
    if ($null -eq $config) {
        return $null
    }
    $cmakeDirectory = $config.Directory.FullName
    $runtime = Get-ChildItem -LiteralPath $cmakeDirectory -File -Recurse |
        Where-Object { $_.Name -eq "opencv_world$($windowsPackage.worldVersion).dll" } |
        Select-Object -First 1
    $importLibrary = Get-ChildItem -LiteralPath $cmakeDirectory -File -Recurse |
        Where-Object { $_.Name -eq "opencv_world$($windowsPackage.worldVersion).lib" } |
        Select-Object -First 1
    if ($null -eq $runtime -or $null -eq $importLibrary) {
        return $null
    }
    return [pscustomobject]@{
        Version = [string]$opencv.version
        WorldVersion = [string]$windowsPackage.worldVersion
        RootDirectory = $cmakeDirectory
        CMakeDirectory = $cmakeDirectory
        RuntimeDirectory = $runtime.Directory.FullName
        RuntimePath = $runtime.FullName
        ImportLibraryPath = $importLibrary.FullName
    }
}

$existing = Get-OpenCvInstallation -Root $DestinationDirectory
if ($null -ne $existing) {
    Write-Information "Using cached OpenCV $($opencv.version): $DestinationDirectory" -InformationAction Continue
    return $existing
}
if (Test-Path -LiteralPath $DestinationDirectory) {
    throw "OpenCV destination exists but is incomplete: $DestinationDirectory"
}

if (-not (Test-Path -LiteralPath $DownloadDirectory -PathType Container)) {
    New-Item -ItemType Directory -Path $DownloadDirectory | Out-Null
}
$archiveName = Split-Path -Leaf ([Uri]$windowsPackage.url).AbsolutePath
$archivePath = Join-Path $DownloadDirectory $archiveName
if (-not (Test-Path -LiteralPath $archivePath -PathType Leaf)) {
    Write-Information "Downloading OpenCV $($opencv.version) from the pinned official release..." -InformationAction Continue
    Invoke-WebRequest -Uri $windowsPackage.url -OutFile $archivePath
}

$actualHash = (Get-FileHash -LiteralPath $archivePath -Algorithm SHA256).Hash.ToLowerInvariant()
$expectedHash = ([string]$windowsPackage.sha256).ToLowerInvariant()
if ($actualHash -ne $expectedHash) {
    throw "OpenCV archive checksum mismatch. Expected $expectedHash; got $actualHash. Remove the cached archive before retrying."
}

$destinationParent = Split-Path -Parent $DestinationDirectory
if (-not (Test-Path -LiteralPath $destinationParent -PathType Container)) {
    New-Item -ItemType Directory -Path $destinationParent | Out-Null
}
$stagingDirectory = "$DestinationDirectory.partial-$PID"
if (Test-Path -LiteralPath $stagingDirectory) {
    throw "OpenCV staging directory already exists: $stagingDirectory"
}
New-Item -ItemType Directory -Path $stagingDirectory | Out-Null

Write-Information "Extracting verified OpenCV archive..." -InformationAction Continue
& $archivePath -y -o"$stagingDirectory" | Out-Null
if ($LASTEXITCODE -ne 0) {
    throw "OpenCV extraction failed with exit code $LASTEXITCODE. Partial output: $stagingDirectory"
}
$staged = Get-OpenCvInstallation -Root $stagingDirectory
if ($null -eq $staged) {
    throw "Extracted OpenCV package is incomplete: $stagingDirectory"
}

Move-Item -LiteralPath $stagingDirectory -Destination $DestinationDirectory
$installed = Get-OpenCvInstallation -Root $DestinationDirectory
if ($null -eq $installed) {
    throw "Installed OpenCV package validation failed: $DestinationDirectory"
}
Write-Information "OpenCV $($opencv.version) installed: $($installed.RootDirectory)" -InformationAction Continue
return $installed
