#ifndef PATTERN_H
#define PATTERN_H

#include <QImage>
#include <QString>

/// Container for a compressed pattern
/// This class performs a 1-shot compression of an image from a QIMage.
class PatternOutput
{
public:
    enum Encoding {
        RGB24       = 0,     /// RGB24 mode (uncompressed 24 bit)
        RGB565_RLE  = 1,     /// RGB 565 + RLE mode (compressed 16 bit)
        INDEXED     = 2,     /// 8-bit indexed mode (pallated 8 bit)
        INDEXED_RLE = 3,     /// 8-bit indexed mode + RLE (pallated 8 bit)
    };

    // TODO: Move me to a converter class
    enum ColorMode {
        RGB = 0,
        GRB = 1
    };

    // Create an pattern from a QImage
    PatternOutput(QImage image, int frameDelay, Encoding encoding, ColorMode colorMode);

    // TODO: create an pattern from byte array

    Encoding encoding;  /// Encoding used to compress the pattern
    QImage image;       /// QImage representation of the pattern
    QByteArray data;    /// Byte array representation of the pattern
    QString header;     /// C++ header representation of the pattern

    int frameCount;     /// Number of frames in this pattern
    int ledCount;       /// Number of LEDs attached to this blinky
    int frameDelay;     /// Length of time between frames of data, in ms
    ColorMode colorMode;    /// Pattern color mode

    int colorCount() const;  /// Number of unique colors in the original image

private:
    // Compress an RGB color to the 565 color space
    // TODO: Improve this conversion using a lookup table, instead of
    // decimation.
    int QRgbTo565(QColor color);

    void encodeImageRGB24();
    void encodeImageRGB16_RLE();
    void encodeImageIndexed();
    void encodeImageIndexed_RLE();
};


#endif // PATTERN_H