/****************************************************************************
* cansocket-qt.lib - Qt socketcan library
* Copyright (C) 2016 Georgije Bosiger <gbosiger@gmail.com>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef CANFRAME_H
#define CANFRAME_H

#include <QtCore/qshareddata.h>
#include <QtCore/qmetatype.h>

#include <cansocketglobal.h>

class CanFrame;
class CanFrameData;

#ifndef QT_NO_DATASTREAM
    CANSOCKET_EXPORT QDataStream &operator<<(QDataStream &, const CanFrame &);
    CANSOCKET_EXPORT QDataStream &operator>>(QDataStream &, CanFrame &);
#endif //QT_NO_DATASTREAM

#ifndef QT_NO_DEBUG_STREAM
    CANSOCKET_EXPORT QDebug operator<<(QDebug, const CanFrame &);
#endif //QT_NO_DEBUG_STREAM

class CANSOCKET_EXPORT CanFrame
{
public:
    enum CanFrameType {
        DataFrame,
        FDFrame,
        ErrorFrame,
        RTRFrame,

        UnknownFrame = -1,
    };

    enum CanFrameError {
        NoError = 0x000,
        TXTimeoutError = 0x001,
        LostArbitrationError = 0x002,
        ControllerProblemsError = 0x004,
        ProtocolViolationsError = 0x008,
        TransceiverStatusError = 0x010,
        NoACKOnTransmissionError = 0x020,
        BusOffError = 0x040,
        BusError = 0x080,
        ControllerRestartedError = 0x100,

        UnknownCanFrameError = 0x200,

        AllCanFrameErrors = 0x1FFFFFFF,
    };
    Q_DECLARE_FLAGS(CanFrameErrors, CanFrameError)

    enum CanFrameFormat {
        StandardFrameFormat,
        ExtendedFrameFormat
    };

    enum CanFrameFullIdMask {
        SFFIdMask = 0x000007FF,
        EFFIdMask = 0x1FFFFFFF
    };
    Q_DECLARE_FLAGS(CanFrameFullIdMasks, CanFrameFullIdMask)

    enum CanFrameFullIdFlag {
        EFFIdFlag = 0x80000000,
        RTRIdFlag = 0x40000000,
        ErrorIdFlag = 0x20000000
    };
    Q_DECLARE_FLAGS(CanFrameFullIdFlags, CanFrameFullIdFlag)

    CanFrame();
    CanFrame(CanFrameType type);
    CanFrame(const CanFrame &rhs);
    ~CanFrame();

    void swap(CanFrame &other);

    bool isValid() const;
    bool isEmpty() const;
    bool isNull() const;

    void clear();

    int maxDataLength() const;
    int maxDataTransferUnit() const;

    CanFrameType frameType() const;
    void setFrameType(CanFrameType frameType);

    bool isDataFrame() const;
    bool isFDFrame() const;
    bool isErrorFrame() const;
    bool isRTRFrame() const;

    void toDataFrame();
    void toFDFrame();
    void toErrorFrame();
    void toRTRFrame();

    bool operator ==(const CanFrame &rhs) const;
    bool operator !=(const CanFrame &rhs) const { return !operator==(rhs); }
    bool operator >(const CanFrame &rhs) const;
    bool operator <(const CanFrame &rhs) const;

    uint id() const;
    void setId(uint id);

    uint fullId() const;
    void setFullId(uint id);

    CanFrameFormat frameFormat() const;
    void setFrameFormat(CanFrameFormat format);

    int dataLength() const;
    virtual bool setDataLength(int bytes);

    char *data();
    const char *data() const;
    const char *constData() const { return data(); }

    const char &at(int i) const;
    const char &operator[](int i) const;
    char &operator[](int i);

    void setData(const char* data, int len = -1);

    CanFrameErrors error() const;

protected:
    QSharedDataPointer<CanFrameData> d;

private:
    friend CANSOCKET_EXPORT QDataStream &operator<<(QDataStream &, const CanFrame &);
    friend CANSOCKET_EXPORT QDataStream &operator>>(QDataStream &, CanFrame &);
};


Q_DECLARE_SHARED(CanFrame)

Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFrameErrors)
Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFrameFullIdMasks)
Q_DECLARE_OPERATORS_FOR_FLAGS(CanFrame::CanFrameFullIdFlags)

Q_DECLARE_METATYPE(CanFrame)
Q_DECLARE_METATYPE(CanFrame::CanFrameError)
Q_DECLARE_METATYPE(CanFrame::CanFrameErrors)


#endif // CANFRAME_H