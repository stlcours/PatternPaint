#ifndef AVRPATTERNUPLOADER_H
#define AVRPATTERNUPLOADER_H

#include <QObject>
#include <QTimer>
#include <iostream>
#include "patternwriter.h"
#include "avrprogrammer.h"

#include "blinkyuploader.h"

struct FlashSection {
    /// Create a new flash section
    /// @param address Address in the flash memory where the data should be stored
    /// @param data Data to store
    FlashSection(int address,
                 QByteArray data) :
        address(address),
        data(data) {}

    /// Address to store the data
    int address;

    /// Data to store
    QByteArray data;
};

/// This is an re-entreant version of an pattern uploader.
/// Each task in the upload process is broken into a single state, and the state
/// machine is driven forward by receiving events from the connected serial port,
/// or in the case of a timeout, from the timeout timer.
///
/// This seems convoluted, but the goal is to avoid ever waiting on a serial read
/// event. For some reason, doing so seems to block the main thread even if we are
/// in a different thread; it's possible serial sits on the main lock?
///
/// While the upload process is underway, it will send periodic progress updates
/// via the progressUpdate() signal.
class BlinkyTapeUploader : public BlinkyUploader
{
    Q_OBJECT

public:
    BlinkyTapeUploader(QObject *parent=0);

    bool startUpload(BlinkyController& tape, std::vector<PatternWriter> patterns);
    bool upgradeFirmware(BlinkyController& tape);
    bool upgradeFirmware(int timeout);
    QString getErrorString() const;

    QList<PatternWriter::Encoding> getSupportedEncodings() const;

private slots:
    void doWork();  /// Handle the next section of work, whatever it is

    void handleProgrammerError(QString error);

    void handleProgrammerCommandFinished(QString command, QByteArray returnData);

    /// Delay timer, lets us wait some time between receiving a finished command, and
    /// passing the message along (to give the serial device some time to reset itself).
    void handleResetTimer();

private:
    enum State {
        State_Ready,                    ///< Ready for a command.
        State_WaitForBootloaderPort,    ///< We are waiting for the bootloader device to show up.
        State_WaitAfterBootloaderPort,  ///< Short delay after the device shows up
    };

    /// Start an upload, using the passed blinkytape as a launching point
    /// Note that the blinkytape will be disconnected during the upload process,
    /// and will need to be reconnected manually afterwards.
    bool startUpload(BlinkyController& tape);

    /// Timer used to poll for the bootloader device to show up
    QPointer<QTimer> bootloaderResetTimer;

    qint64 bootloaderPollTimeout;

    /// Current upload progress, in command counts
    float progress;

    QString errorString;

    /// Time that we transitioned into the current state
    QDateTime stateStartTime;

    /// Current command state
    State state;

    /// Update any listeners with the maximum progress
    void setMaxProgress(int newProgress);

    /// Update any listeners with the latest progress
    void setProgress(int newProgress);

    AvrProgrammer programmer;

    QQueue<FlashSection> flashData; ///< Queue of memory sections to write
};

#endif // AVRPATTERNUPLOADER_H