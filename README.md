![Wizm logo](https://github.com/SebastianRautenbach/WIZM-Game-Engine/blob/main/RenderEngine/res/Picture1.png 'Wizm logo')
![ScreenShot1](https://github.com/SebastianRautenbach/3D-Game-Engine/blob/main/RenderEngine/res/screenshot2.png)

**Getting Started**
*Step 1: Clone the Repository*
Clone the repository to your local machine using your preferred Git client or the command line.

*Step 2: Build the Engine*
1. Navigate to the `out` directory.
2. Run `cmake` and select the `out` folder as the output directory.
3. Open the generated project in your preferred IDE.
4. Build the engine using your IDE's build tools.

*Step 3: Run the Engine*
1. After successfully building and compiling the code, locate the `DLL` folder.
2. Copy the required DLLs into the `x64/Debug` or `x64/Release` folder, depending on your build configuration.
3. Launch the engine and start exploring!

**Current state**
- *3D Renderer*: Fully supported 3D rendering with clustered forward rendering for optimal performance.
- *Material Editor*: Intuitive material editor for creating and tweaking materials.
- *Scripting*: Built-in scripting support using AngelScript for creating game logic.
- *Asset Manager*: Robust asset manager for handling textures, models, and other game assets.
- *Sound System*: Comprehensive sound system for creating immersive audio experiences.
- *Runtime*: Supports runtime loading and unloading of assets, scripts, and other game data.

**Whats to come**
I want the engine to support a layer system where all scenes can be layered on top of each other making it more modular.

**Resources Used**

Clustered Forward rendering:
- https://www.aortiz.me/2018/12/21/CG.html#forward-shading
- https://www.adriancourreges.com/blog/2016/09/09/doom-2016-graphics-study/#clustered-forward-rendering-of-opaque-objects
- https://www.humus.name/Articles/PracticalClusteredShading.pdf

Scripting:
- https://github.com/FrictionalGames/HPL1Engine
- https://www.angelcode.com/angelscript/
