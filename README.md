sourcemod-botcontroller
=======================

SourceMod extension for bot controller.

## Builds

| Engine | Linux | Windows |
| --- | --- | --- |
| Team Fortress 2 (`tf2`) | x86, x64 | x86, x64 |
| Counter-Strike: Source (`css`) | x86, x64 | x86, x64 |
| Day of Defeat: Source (`dods`) | x86, x64 | x86, x64 |
| Half-Life 2: Deathmatch (`hl2dm`) | x86, x64 | x86, x64 |
| Source SDK 2013 (`sdk2013`) | x86 | x86 |
| Left 4 Dead (`l4d`) | x86 | x86 |
| Left 4 Dead 2 (`l4d2`) | x86 | x86 |
| Counter-Strike: Global Offensive (legacy dedicated server, `csgo`) | x86 | x86 |

The GitHub Actions workflow produces separate Linux and Windows packages
for SourceMod 1.12 (`1.12-dev`) and 1.13 (`master`). Download the package for
both your SourceMod version and server OS, then merge its `addons/` directory
with your game directory. Packages include the x86 extensions in
`addons/sourcemod/extensions/`, the x64 extensions in
`addons/sourcemod/extensions/x64/`, and the existing `botcontroller.inc`.

Local builds require AMBuild 2.2, a C++17 compiler, SourceMod with its
`hl2sdk-manifests`, `public/amtl`, and `sourcepawn` submodules initialized,
Metamod:Source `1.12-dev`, and the selected HL2SDK branches (each in a
`hl2sdk-<name>` directory). For example, with dependencies checked out under
`/path/to/deps`:

```sh
mkdir build
cd build
python ../configure.py --enable-optimize \
  --sm-path=/path/to/deps/sourcemod \
  --mms-path=/path/to/deps/metamod-source \
  --hl2sdk-root=/path/to/deps
ambuild
```

By default, AMBuild builds all supported SDKs and both architectures.
Use `--sdks="tf2 css"` to select particular engines or `--sdks=present` to
build those installed locally.
Use `--targets=x86` or `--targets=x86_64` for a single server architecture.
On Linux, building both architectures requires the multilib toolchain.
The packaged engine-specific extensions and SourcePawn include are in
`build/package/`.
