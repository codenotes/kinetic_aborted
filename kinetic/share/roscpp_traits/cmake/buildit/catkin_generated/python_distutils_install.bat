@echo off

if DEFINED DESTDIR (
  echo "Destdir.............%DESTDIR%"
  set DESTDIR_ARG="--root=%DESTDIR%"
)

cd "C:/ros/gitsrc/ros_comm/tools/rosmsg"

cmd /V:on /C set PYTHONPATH="C:/Program Files/rosmsg/lib/site-packages;C:/ros/kinetic/share/roscpp_traits/cmake/buildit/lib/site-packages" ^
          && set CATKIN_BINARY_DIR="C:/ros/kinetic/share/roscpp_traits/cmake/buildit" ^
          && "C:/Python27/python.exe" ^
             "C:/ros/gitsrc/ros_comm/tools/rosmsg/setup.py" ^
             build --build-base "C:/ros/kinetic/share/roscpp_traits/cmake/buildit" ^
             install %DESTDIR_ARG%  ^
             --prefix="C:\Program Files\rosmsg" ^
             --install-scripts="C:\Program Files\rosmsg\bin"
