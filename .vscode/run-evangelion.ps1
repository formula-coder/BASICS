$workspaceFolder = Split-Path $PSScriptRoot -Parent
$src = Join-Path $workspaceFolder 'Evangelion\src'
$out = Join-Path $workspaceFolder 'Evangelion\out\production\Evangelion'
New-Item -ItemType Directory -Force -Path $out | Out-Null
$files = Get-ChildItem $src -Recurse -Filter *.java | ForEach-Object { $_.FullName }
if (-not $files) {
    throw 'No .java files found in Evangelion/src'
}
& 'C:\Program Files\Eclipse Adoptium\jdk-25.0.3.9-hotspot\bin\javac.exe' -encoding UTF-8 -d $out $files
& 'C:\Program Files\Eclipse Adoptium\jdk-25.0.3.9-hotspot\bin\java.exe' -cp $out evangelion.Main
