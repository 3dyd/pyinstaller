# PyInstaller for XP+

This is unofficial PyInstaller patch to restore support for Windows XP and above.

## How to Build

Ready-to-use builds are available here: [3dyd.github.io/pyinstaller-builds/](https://3dyd.github.io/pyinstaller-builds/). Read readme in corresponding repo ([3dyd/pyinstaller-builds](https://github.com/3dyd/pyinstaller-builds)) if you want to build it yourself using GitHub Actions.

To build manually you need Python3 and MinGW (specifically mingw32 is enough):

```sh
git clone --branch 6.16.0-xp --single-branch https://github.com/3dyd/pyinstaller.git
cd pyinstaller
python -m venv .venv
source .venv/bin/activate
cd bootloader
python waf all --target-arch=32bit --gcc
cd ..
pip install --upgrade pip hatchling
python -m hatchling build
```

On Linux you might need to point it to mingw32 explicitly:

```sh
CC=i686-w64-mingw32-gcc AR=i686-w64-mingw32-ar python waf all --target-arch=32bit --gcc
```

On Windows you may try to initialize virtual environment this way:

```sh
py -m venv .venv
source .venv/Scripts/activate
```
