#ifndef PATTERNITEM_H
#define PATTERNITEM_H

#include <QFileInfo>
#include <QListWidgetItem>
#include <QUndoStack>
#include <QPointer>
#include "patternframemodel.h"


/// Representation of a pattern based on a frame model.
class Pattern
{
public:
    /// Constructor for an empty pattern item
    /// @param size Size of the display, in pixels
    /// @param frameCount Length of the pattern, in frames
    Pattern(QSize size, int frameCount, QListWidget* parent = 0);

    /// Set the pattern image directly without resizing or setting an undo state. This
    /// is used by the undocommand and should probably be refactored.
    /// @param newImage Set the pattern to this image
    void applyUndoState(const QImage& newImage);

    /// Get a pointer to the undo stack. This is used to wire the undo stack
    /// into the main window gui.
    QUndoStack *getUndoStack();

    /// Check if the animation has a valid filename
    /// @return true if the animation filename has been set
    bool hasValidFilename() const;

    /// Get the pattern filename, or a default if one is not set
    /// @return Pattern name
    QString getPatternName() const;

    /// Initialize the pattern from an image file
    /// @param newFileInfo URL of file to load
    bool load(const QString &newFileName);

    /// Save the pattern
    /// Note: The file must already have a filename, otherwise use saveAs
    bool save();

    /// Save the pattern to a new file
    /// newFileInfo URL of the new file to save to.
    bool saveAs(const QString newFileName);

    /// Replace the current image with one from a new file, but don't
    /// change the filename (for drag&drop operations)
    /// @param newFileInfo URL of file to load
    bool replace(const QString newFileInfo);

    /// Resize the image
    /// @param newSize New size of the pattern, in pixels
    /// @param scale If true, scale the image to fit the new size. Otherwise crop/expand the image.
    void resize(QSize newSize,  bool scale);

    /// Get the number of frames contained in the animation
    /// @return Frame count
    int getFrameCount() const;

    /// Get an image representing the current frame
    /// @return an NxN QImage reperesenting the current frame data
    const QImage getFrame(int index) const;

    /// Delete the frame at the given index
    /// @param frame Index of the frame to delete
    void deleteFrame(int index);

    /// Insert a frame at the given index
    /// @param frame Index that the frame should be inserted at
    void addFrame(int newFrame);

    /// Apply changes to the pattern
    void replaceFrame(int index, const QImage& update);

    /// Test if the pattern has unsaved changes
    /// @return true if the pattern has unsaved changes
    bool getModified() const { return modified; }

    /// Set the unsaved pattern state
    /// TODO: Delete me
    /// @param newModified New modified state.
    void setModified(bool newModified);

    /// Get the underlying data model (for connection to a view)
    PatternFrameModel* getFrameModel() {return &frames;}

private:
    PatternFrameModel frames;   ///< New storage container for the images

    bool modified;              ///< True if the image has been modified since last save
};


#endif // PATTERNITEM_H
