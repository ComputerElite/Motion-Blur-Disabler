# Builds a .zip file for loading with BMBF
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk

Compress-Archive -Path "./libs/arm64-v8a/libMotionBlurDisabler_1_2_0.so", "./libs/arm64-v8a/libbeatsaber-hook_0_8_4.so", "./bmbfmod.json", "./libs/arm64-v8a/libcodegen_0_3_6.so" -DestinationPath "./MotionBlurDisabler_v1.2.0.zip" -Update
