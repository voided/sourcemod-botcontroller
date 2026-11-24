sourcemod-botcontroller
=======================

SourceMod extension for bot controller.

## Builds

The x86 build targets are Team Fortress 2 (`tf2`), Counter-Strike: Source
(`css`), Day of Defeat: Source (`dods`), Half-Life 2: Deathmatch (`hl2dm`),
Source SDK 2013 (`sdk2013`), Left 4 Dead (`l4d`), Left 4 Dead 2 (`l4d2`),
and legacy Counter-Strike: Global Offensive (`csgo`).

The GitHub Actions workflow produces separate Linux and Windows x86 packages
for SourceMod 1.12 (`1.12-dev`) and 1.13 (`master`). Download the package for
both your SourceMod version and server OS, then merge its `addons/` directory
with your game directory. The existing `botcontroller.inc` is included.

Local builds require AMBuild 2.2, a C++17 compiler, SourceMod with its
`hl2sdk-manifests`, `public/amtl`, and `sourcepawn` submodules initialized,
Metamod:Source `1.12-dev`, and the selected HL2SDK branches (each in a `hl2sdk-<name>` directory). For example, with dependencies
checked out under `/path/to/deps`:

```sh
mkdir build
cd build
python ../configure.py --enable-optimize \
  --sm-path=/path/to/deps/sourcemod \
  --mms-path=/path/to/deps/metamod-source \
  --hl2sdk-root=/path/to/deps
ambuild
```

By default, AMBuild builds all supported SDKs. Use `--sdks="tf2 css"` to
select particular engines, or `--sdks=present` to build those installed locally.
The packaged engine-specific extensions and SourcePawn include are in
`build/package/`.
