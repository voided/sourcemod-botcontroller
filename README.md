sourcemod-botcontroller
=======================

SourceMod extension for bot controller.

## Builds

The GitHub Actions workflow produces separate Linux and Windows x86 packages
for SourceMod 1.12 (`1.12-dev`) and 1.13 (`master`). Download the package for
both your SourceMod version and server OS, then merge its `addons/` directory
with your game directory. The existing `botcontroller.inc` is included.

Local builds require AMBuild 2.2, a C++17 compiler, SourceMod with its
`hl2sdk-manifests`, `public/amtl`, and `sourcepawn` submodules initialized,
Metamod:Source `1.12-dev`, and the TF2 HL2SDK. For example, with dependencies
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

The packaged extension and SourcePawn include are in `build/package/`.
