#!/bin/bash

# Stop at any error
set -e

# Pull in the QT tools
export QTDIR=~/Qt5.4.1/5.4/clang_64/

OUTPUTDIR=`pwd`
echo "Output to: " ${OUTPUTDIR}

# Move to a temporary directory
pushd $(mktemp -d -t PatternPaint)
echo "Building in: " `pwd`

# Get the repository
git clone https://github.com/Blinkinlabs/PatternPaint.git

# Build PatternPaint
cd PatternPaint/PatternPaint
${QTDIR}/bin/qmake MOC_DIR=build OBJECTS_DIR=build RCC_DIR=build UI_DIR=build   DESTDIR=bin VERSION=1.6.1
make
cd ..

# Deploy and sign the release
${QTDIR}/bin/macdeployqt PatternPaint/bin/PatternPaint.app/ -codesign="Developer ID Application: Blinkinlabs, LLC" -dmg
codesign --verify --verbose=4 PatternPaint/bin/PatternPaint.app

# Test the signature
hdiutil mount PatternPaint/bin/PatternPaint.dmg
codesign --verify --verbose=4 /Volumes/PatternPaint:bin:PatternPaint/PatternPaint.app
umount /Volumes/PatternPaint\:bin\:PatternPaint/

# And copy out the resulting disk image
mv PatternPaint/bin/PatternPaint.dmg ${OUTPUTDIR}/PatternPaint_1.6.1.dmg

# TODO: Clean up temp dir