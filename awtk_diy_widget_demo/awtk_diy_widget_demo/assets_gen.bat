@set AWTK_DIR=D:\OpenLibraries\awtk\awtk
python assets_gen.py %AWTK_DIR%/bin res/assets/default/raw res/assets/default/inc
python assets_c_gen.py res/assets

