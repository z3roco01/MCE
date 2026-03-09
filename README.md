# Minecraft: MCE - Modern Console Edition
This is a modification of the Minecraft October 2014 LCE leak.

# Features
- nothing right now...
## Planned
- Keyboard + mouse
- playing around

# Compiling
## Requirements
- You must provide the assets on your own, they are not included here
- To compile you need Visual Studio ( probably 2012, other versions may work )
## Instructions
1. Copy over the `Minecraft.Client` over to the full leak, replacing code files
2. Open `MinecraftConsoles.sln` in Visual Studio
3. Build the `Minecraft.World` project first, then the `Minecraft.Client` project
4. Find the compiled exe ( either in `x64/Debug` or `x64/Release`, copy over the directories: `Minecraft.Client/Common`, `Minecraft.Client/Durango` and `Minecraft.Client/Windows64` into the directory with the compiled exe
