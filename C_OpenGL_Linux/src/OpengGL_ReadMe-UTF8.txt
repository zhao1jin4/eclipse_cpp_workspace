
C/C++ Build -> Tool Chain Editor-> MacOSX GCC  /MinGW /CygWin /LinuxGCC

-------------MinGW
右击项目->properties->C/C++ Build -> Settings -> MinGW C++ Linker -> Libaraies->在 l  中 增加三项
-lopengl32
-lglut32 
-lglu32

preprocessor 中加   _STDCALL_SUPPORTED
提示加 -fpermissive

linux下的freeglut,#include 是GL的大写目录,glut.h在GL目录下,lib是加  
-lglut
-lGL
-lGLU


扩展名是大写的C表示cpp,是用g++编译
Debug 要把*.dll文件放在　PATH中


使用MinGW编译 可能要加其它选项
gcc -o helloOpenGL helloOpenGL.c -D_STDCALL_SUPPORTED  glut32.lib -lopengl32 -lglu32  

//把*.dll 复制到 C:\WINDOWS\system32 后 ,下dir  看不到,要用 ls 可以看到, attrib -s -h -r 也找不到, 用regsvr32 glut32.dll也找不到
//rm 后提示  write-protected regular file
  
 ----------------Cygwin下编译OK
$ gcc -o helloOpenGL helloOpenGL.c -lglut32 -lglu32 -lopengl32 -I glutdlls37beta -L glutdlls37beta/


CDT 下集成Cygwin, 编译OK,CDT运行效果,要手工双击.exe文件

把*.lib文件复制到 C:\cygwin\lib	
把glut.h复制到C:\cygwin\usr\include\w32api\GL

右击项目->properties->C/C++ Build -> Settings -> 在Cygwin C++ Linker -> Libaraies->
在 l  中 增加三项,glut32,glu32,opengl32

Cygwin中必须加#include <windows.h>,而Gnusetup可以部分不加的


Debug默认是不能显示源码的,报错,/cygdrive/d/Program/
要设置 Window -> Preferences -> C/C++ -> Debug->Source Lookup Path -> Add->Path Mapping->Add->
输入 \cygdrive\d	对应 d:\,就OK了


Cygwin 错误的提示是中文乱码,不能定位到文件中,加环境变量 LANG=en 就OK了
右击项目->properties->C/C++ Build -> Enviroment->Add ...

文件的扩展名是大写的C 是用g++编译,才认识namespace

------------------GNUSetup中也可gcc g++
默认加的PATH
D:\program\GNUstep\GNUstep\System\Tools;D:\program\GNUstep\bin

GNUSetup也可以使用gcc编译CDT中的 openGL debug 也是OK,也可编译C++
只加默认的PATH就可以了,CDT会自动加相当的include 

C是(32位机)
D:\program\GNUstep\include
D:\program\GNUstep\lib\gcc\mingw32\4.6.1\include
D:\program\GNUstep\lib\gcc\mingw32\4.6.1\include-fixed

C++ 多加的是(32位机)
D:\program\GNUstep\lib\gcc\mingw32\4.6.1\include\c++
D:\program\GNUstep\lib\gcc\mingw32\4.6.1\include\c++\backward
D:\program\GNUstep\lib\gcc\mingw32\4.6.1\include\c++\mingw32


命令行编译也OK,只加默认的PATH就可以了
D:\program\GNUstep\bin\gcc -o helloOpenGL helloOpenGL.c glut32.lib -lopengl32 -lglu32  //OK

D:\program\GNUstep\bin\g++ -o CPP_STL.exe CPP_STL.cpp  //OK

GNUSetup可以和Cyginw混合使用
eclipse CDT建立项目后->右击项目->properties->tool chain edit 中多了一个MacOSX GCC,但不能使用


------------------linux freeGLUT
gcc -o helloOpenGL helloOpenGL.c -lglut -lGL -lGLU  测试OK
------------------Mac 下
安装Command line tools后有 /System/Library/Frameworks/GLUT.framework
GLUT.framework有 <GLUT/GLUT.h> 会自动引入 <OpenGL/gl.h>,<OpenGL/glu.h>,有 #pragma comment (lib, "glut32.lib") ,依赖于OpenGL.framework

g++  -framework GLUT -framework OpenGL  helloOpenGL.c -o helloOpenGL 
CDT->C/C++ Build->Settings->Linker->Miscellaneous->在Linker flags中加入 -framework GLUT -framework OpenGL  测试OK
Tool Chain Editor 为MacOS GCC 应该有/Library/Framework 和 /System/Library/Framework 的include

----------VC++
VC2010 设置环境变量
path=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin;
lib=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib
include=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include

cl /I "C:\temp\glut\include" /c  helloOpenGL.c
/D同gcc的-D
/Zi  生成完整的调试信息 ( Information )
/EHs 同步异常处理模型 (Exception Handling)

link helloOpenGL.obj /LIBPATH:"C:\temp\glut\lib"  //如果要生成.dll文件加  /DLL

------CDT使用VC++
.C 大C结尾的文件在cl编译器被认为是C,要用.cpp才是C++
不用加 glut32 ...,不用加-D ,不能使用debug



 
 
 