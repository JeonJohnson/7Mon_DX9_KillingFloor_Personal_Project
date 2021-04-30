::For General
xcopy /y ..\Bin\*.lib ..\..\Reference\Lib\
xcopy /y ..\Header\*.h ..\..\Reference\Header\
xcopy /y ..\Shader\*.fx ..\..\Reference\Shader\

::For Engine
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\Win32\Debug\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\Win32\Release\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\x64\Debug\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\x64\Release\

::For ObjectTool
xcopy /y ..\Bin\*.dll ..\..\Tool\Bin\Win32\Debug\
xcopy /y ..\Bin\*.dll ..\..\Tool\Bin\Win32\Release\
xcopy /y ..\Bin\*.dll ..\..\Tool\Bin\x64\Debug\
xcopy /y ..\Bin\*.dll ..\..\Tool\Bin\x64\Release\

::For NeviMeshTool
::xcopy /y ..\Bin\*.dll ..\..\Tools\NaviMesh_Tool\Bin\Win32\Debug\
::xcopy /y ..\Bin\*.dll ..\..\Tools\NaviMesh_Tool\Bin\Win32\Release\
::xcopy /y ..\Bin\*.dll ..\..\Tools\NaviMesh_Tool\Bin\x64\Debug\
::xcopy /y ..\Bin\*.dll ..\..\Tools\NaviMesh_Tool\Bin\x64\Release\

::For ColliderTool
::xcopy /y ..\Bin\*.dll ..\..\Tools\Collider_Tool\Bin\Win32\Debug\
::xcopy /y ..\Bin\*.dll ..\..\Tools\Collider_Tool\Bin\Win32\Release\
::xcopy /y ..\Bin\*.dll ..\..\Tools\Collider_Tool\Bin\x64\Debug\
::xcopy /y ..\Bin\*.dll ..\..\Tools\Collider_Tool\Bin\x64\Release\

