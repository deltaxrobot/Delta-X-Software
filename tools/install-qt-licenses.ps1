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
$qt = $dependencies.qt
if ([string]::IsNullOrWhiteSpace($DestinationDirectory)) {
    $DestinationDirectory = Join-Path $repositoryRoot "build\dependencies\qt-licenses-$($qt.ciVersion)"
}
if ([string]::IsNullOrWhiteSpace($DownloadDirectory)) {
    $DownloadDirectory = Join-Path $repositoryRoot 'build\downloads'
}
$DestinationDirectory = [IO.Path]::GetFullPath($DestinationDirectory)
$DownloadDirectory = [IO.Path]::GetFullPath($DownloadDirectory)

function Test-LicenseSet {
    param([Parameter(Mandatory = $true)][string]$Root)

    if (-not (Test-Path -LiteralPath $Root -PathType Container)) {
        return $false
    }
    foreach ($license in $qt.licenses) {
        $path = Join-Path $Root $license.name
        if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
            return $false
        }
        $actualHash = (Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($actualHash -ne ([string]$license.sha256).ToLowerInvariant()) {
            return $false
        }
    }
    return $true
}

if (Test-LicenseSet -Root $DestinationDirectory) {
    return [pscustomobject]@{
        QtVersion = [string]$qt.ciVersion
        Directory = $DestinationDirectory
    }
}
if (Test-Path -LiteralPath $DestinationDirectory) {
    throw "Qt license destination exists but is incomplete or corrupt: $DestinationDirectory"
}
if (-not (Test-Path -LiteralPath $DownloadDirectory -PathType Container)) {
    New-Item -ItemType Directory -Path $DownloadDirectory | Out-Null
}

$stagingDirectory = "$DestinationDirectory.partial-$PID"
if (Test-Path -LiteralPath $stagingDirectory) {
    throw "Qt license staging directory already exists: $stagingDirectory"
}
New-Item -ItemType Directory -Path $stagingDirectory | Out-Null

foreach ($license in $qt.licenses) {
    $downloadName = "qt-$($qt.ciVersion)-$($license.name)"
    $downloadPath = Join-Path $DownloadDirectory $downloadName
    if (-not (Test-Path -LiteralPath $downloadPath -PathType Leaf)) {
        Write-Information "Downloading pinned Qt license: $($license.name)" -InformationAction Continue
        Invoke-WebRequest -Uri $license.url -OutFile $downloadPath
    }
    $actualHash = (Get-FileHash -LiteralPath $downloadPath -Algorithm SHA256).Hash.ToLowerInvariant()
    $expectedHash = ([string]$license.sha256).ToLowerInvariant()
    if ($actualHash -ne $expectedHash) {
        throw "Qt license checksum mismatch for $($license.name). Expected $expectedHash; got $actualHash."
    }
    Copy-Item -LiteralPath $downloadPath -Destination (
        Join-Path $stagingDirectory $license.name)
}

if (-not (Test-LicenseSet -Root $stagingDirectory)) {
    throw "Qt license staging validation failed: $stagingDirectory"
}
$destinationParent = Split-Path -Parent $DestinationDirectory
if (-not (Test-Path -LiteralPath $destinationParent -PathType Container)) {
    New-Item -ItemType Directory -Path $destinationParent | Out-Null
}
Move-Item -LiteralPath $stagingDirectory -Destination $DestinationDirectory

return [pscustomobject]@{
    QtVersion = [string]$qt.ciVersion
    Directory = $DestinationDirectory
}
