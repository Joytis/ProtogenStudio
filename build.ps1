

param (
    [ValidateSet("Debug", "Release")]
    [string]$Mode
)

Write-Host "__________                __                                  _________ __            .___.__        " -ForegroundColor Green
Write-Host "\______   \_______  _____/  |_  ____   ____   ____   ____    /   _____//  |_ __ __  __| _/|__| ____  " -ForegroundColor Green
Write-Host " |     ___/\_  __ \/  _ \   __\/  _ \ / ___\_/ __ \ /    \   \_____  \\   __\  |  \/ __ | |  |/  _ \ " -ForegroundColor Green
Write-Host " |    |     |  | \(  <_> )  | (  <_> ) /_/  >  ___/|   |  \  /        \|  | |  |  / /_/ | |  (  <_> )" -ForegroundColor Green
Write-Host " |____|     |__|   \____/|__|  \____/\___  / \___  >___|  / /_______  /|__| |____/\____ | |__|\____/ " -ForegroundColor Green
Write-Host "                                    /_____/      \/     \/          \/                 \/            " -ForegroundColor Green

# Useful functions
function MakeBuildDirectory {
    param (
        $Directory
    )
    if (-not (test-path $Directory) ) {
        Write-Host "Directory" $Directory "doesn't exist, creating..." -ForegroundColor Green
        md $Directory | out-null
    } else {
        Write-Host "Directory" $Directory "exists, skipping..."
    }
}

Write-Host "Building protogen studio at location: " (Get-Location) -ForegroundColor Green

$RootLocation = '.\build\' + $Mode
$LibraryLocation = $RootLocation + '\lib'
$StudioLocation = $RootLocation + '\studio'
$EmbedLocation = $RootLocation + '\embed'
$SDLBuildLocation = $RootLocation + '\SDL'

$SDLLocation = $SDLBuildLocation + '\SDL3.lib'

# Get build arguments. 
if ($Mode = "Debug") {
    $BuildFlags = "/DEBUG:FULL"
}
else {
    $BuildFlags = "/O2"
}

$BuildDirectories = ($RootLocation, $LibraryLocation, $StudioLocation, $EmbedLocation, $SDLBuildLocation)

foreach ($item in $BuildDirectories) {
    # Code to execute for each $item
    MakeBuildDirectory -Directory $item
}

Write-Host "`n=============== Building All Projects ===============" -ForegroundColor Green

# ----------- Build SDL Distribution
Write-Host "Project: SDL3" -ForegroundColor Green
if (Test-Path -Path $SDLLocation) {
    Write-Host "SDL 3 Library already exits in build folder - skipping..."
}
else {
    $SDLocation = '.\libs\SDL'
    $SDLBuildOutDirArg = "/p:OutDir=..\..\..\..\" + $SDLBuildLocation + "\"
    $SDLBuildConfig = "/p:Configuration=" + $Mode
    msbuild.exe '.\libs\SDL\VisualC\SDL\SDL.vcxproj' $SDLBuildOutDirArg $SDLBuildConfig
}

# ----------- Build protogen library
Write-Host "Project: Protogen Library" -ForegroundColor Green

# ----------- Build protogen studio
Write-Host "Project: Protogen Studio" -ForegroundColor Green
$Includes = (
    '/I', '.\libs',
    '/I', '.\libs\imgui',
    '/I', '.\libs\imgui\backends',
    '/I', '.\libs\lodepng',
    '/I', '.\libs\SDL\include',
    '/I', '.\src'
)

$StudioMain = 'src\studio\main.cpp'
$StudioExecutableArg = '/Fe:'+$StudioLocation+'protogen_studio.exe'

& 'cl' '/std:c++20' $StudioExecutableArg $Includes $BuildFlags $StudioMain $SDLLocation "opengl32.lib"