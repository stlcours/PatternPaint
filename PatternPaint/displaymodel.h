#ifndef DISPLAYMODEL
#define DISPLAYMODEL

#include <qimage.h>
#include "patternitem.h"

class DisplayModel
{
public:
    /// Set the source pattern that we are interacting with
    virtual void setSource(PatternItem* newPatternItem) = 0;

    /// True if this model is attached to a pattern item
    virtual bool hasPatternItem() const = 0;

    /// True if the patternEditor should show a playback indication bar
    virtual bool showPlaybackIndicator() const = 0;

    /// Set the index of the active frame
    /// @param newFrame Frame index to interact with
    virtual void setFrameIndex(int newFrame) = 0;

    /// Get the index of the active frame
    /// @return Index of the active fraome
    virtual int getFrameIndex() const = 0;

    /// Delete the frame at the given index
    /// @param frame Index of the frame to delete
    virtual void deleteFrame(int newFrame) = 0;

    /// Insert a frame at the given index
    /// @param frame Index that the frame should be inserted at
    virtual void addFrame(int newFrame) = 0;

    /// Get an image representing the current frame
    /// @return an NxN QImage reperesenting the current frame data
    virtual const QImage& getFrameData() = 0;

    /// Apply instrument data to the current frame
    /// @instrumentFrameData NxN QImage to be painted on top of the current frame data
    virtual void applyInstrument(const QImage& instrumentFrameData) = 0;
};

#endif // DISPLAYMODEL

