# DxfView

App to display dxf-files

## Why

most apps just display 2D dxf files and fail with those written by freecad.
I wanted to view those files too and lets see, where it goes ...

## Base

My app is based on [simple_cam](https://github.com/grotius-cnc/simple_cam), but I did not
create a fork, as I have quite different plans ...

## Build and run

When you load DxfView.pro in qtcreator, go to project tab and change configuration.
Go to "build steps" qmake and click on details.
Then enter as additional arguments: **CONFIG+=configA**
