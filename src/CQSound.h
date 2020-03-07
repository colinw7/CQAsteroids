#ifndef CQSound_H
#define CQSound_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <list>
#include <string>

#define CQSoundMgrInst CQSoundMgr::getInstance()

class CQSound;
class QSound;
class CSDLSound;

class CQSoundMgr : public QObject {
  Q_OBJECT

  Q_PROPERTY(bool active READ isActive WRITE setActive)

 public:
  static CQSoundMgr *getInstance();

  bool isActive() const;
  void setActive(bool active);

  CQSound *addSound(const char *filename);

  void playSound(CQSound *sound);

 private:
  CQSoundMgr();
 ~CQSoundMgr() { }

 private:
  typedef std::list<CQSound *> SoundList;

  bool             active_ { true };
  bool             qsound_ { false };
  QAudioDeviceInfo qdevice_;
  SoundList        sounds_;
};

//---

class CQSound {
 public:
  CQSound(const char *filename, bool qsound);

 ~CQSound();

  const std::string &getFilename() const { return filename_; }

  void play();

  void stop();

 private:
  std::string filename_;
  QSound*     qsound_  { nullptr };
  CSDLSound*  sound_   { nullptr };
};

//------

class QAudioFormat;
class QAudioOutput;
class QBuffer;

/*
 * This class is used to do platform independant simple sound output.
 *
 * appendSound() can be used to build multiple tones in a continous sound. Pauses
 * have to be built with a frequency of 0 Hz. After you finished building up the
 * playlist, you can start playback with play(). The QxtSoundGenerator object must
 * exist until the playback finished because of the asynchronous nature of play().
 *
 * If you just want to play a single frequency you can also use the static method playSound().
 */
class CQSoundGenerator : public QObject {
  Q_OBJECT

 public:
  enum class Shape {
    SINE,
    SQUARE,
    TRIANGLE,
    SAWTOOTH
  };

 public:
  CQSoundGenerator(QObject* parent, int sampleRate=8000, int channelCount=1,
                   int sampleSize=16, const QString &codec = "audio/pcm");

  virtual ~CQSoundGenerator();

  void appendSound(qreal amplitude, quint16 frequency, quint32 msecs,
                   Shape shape=Shape::SINE);

  void appendPause(quint32 msecs);

  void clear();

  void play();

  static void playSound(qreal amplitude, quint16 frequency, quint32 msecs,
                        Shape shape=Shape::SINE);

  static QByteArray *staticSoundBuffer() {
    return (s_generator ? s_generator->soundBuffer_ : nullptr);
  }

 private slots:
  void playbackFinished();

 private:
  static CQSoundGenerator *s_generator;

  QByteArray*   soundBuffer_  { nullptr };
  QBuffer*      outputBuffer_ { nullptr };
  QAudioFormat* format_       { nullptr };
  QAudioOutput* output_       { nullptr };
};

#endif
