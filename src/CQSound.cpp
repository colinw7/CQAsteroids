#include <CQSound.h>
#include <QSound>
#include <QAudioDeviceInfo>
#include <CSDLSound.h>

CQSoundGenerator *CQSoundGenerator::s_generator;

CQSoundMgr *
CQSoundMgr::
getInstance()
{
  static CQSoundMgr *instance;

  if (! instance)
    instance = new CQSoundMgr;

  return instance;
}

bool
CQSoundMgr::
isActive() const
{
  return active_;
}

void
CQSoundMgr::
setActive(bool active)
{
  active_ = active;
}

CQSoundMgr::
CQSoundMgr()
{
  auto devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

  if (! devices.isEmpty()) {
//  qsound_ = QSound::isAvailable();
    qsound_ = true;

    qdevice_ = devices[0];
  }
  else
    qsound_ = false;
}

CQSound *
CQSoundMgr::
addSound(const char *filename)
{
  auto *sound = new CQSound(filename, qsound_);

  sounds_.push_back(sound);

  return sound;
}

void
CQSoundMgr::
playSound(CQSound *sound)
{
  if (! isActive())
    return;

  if (qsound_) {
    for (auto *sound1 : sounds_)
      sound1->stop();
  }

  sound->play();
}

//--------------

CQSound::
CQSound(const char *filename, bool qsound) :
 filename_(filename)
{
  if (qsound)
    qsound_ = new QSound(filename);
  else
    sound_ = CSDLSoundMgrInst->createSound(filename);
}

CQSound::
~CQSound()
{
  delete qsound_;
  delete sound_;
}

void
CQSound::
play()
{
  if (qsound_)
    qsound_->play();
  else
    sound_->play();
}

void
CQSound::
stop()
{
  if (qsound_)
    qsound_->stop();
  else
    sound_->stop();
}

//------

#include <QAudioFormat>
#include <QAudioOutput>
#include <QByteArray>
#include <QtEndian>
#include <QBuffer>
#include <QDebug>
#include <qmath.h>

CQSoundGenerator::
CQSoundGenerator(QObject *parent, int sampleRate, int channelCount, int sampleSize,
                 const QString &codec) :
 QObject(parent)
{
  soundBuffer_ = new QByteArray();

  format_ = new QAudioFormat();

  format_->setSampleRate(sampleRate);
  format_->setChannelCount(channelCount);
  format_->setSampleSize(sampleSize);
  format_->setCodec(codec);
  format_->setByteOrder(QAudioFormat::LittleEndian);
  format_->setSampleType(QAudioFormat::UnSignedInt);

  output_ = new QAudioOutput(*format_, this);

  connect(output_, SIGNAL(stateChanged(QAudio::State)), this, SLOT(playbackFinished()));

  outputBuffer_ = new QBuffer(soundBuffer_);

  if (! outputBuffer_->open(QIODevice::ReadOnly)) {
    qCritical() << "Invalid operation while opening QBuffer. " << codec;
    return;
  }
}

CQSoundGenerator::
~CQSoundGenerator()
{
  delete soundBuffer_;
  delete format_;
  delete output_;
  delete outputBuffer_;
}

/*
 * \brief Adds a specific tone to the playlist.
 *
 * \param amplitude The amplitude of this tone from 0.0 to 1.0
 * \param frequency The tone's frequency in Hz
 * \param msecs     The tone's duration. Minimum is 50 msecs, every value below
 *                  that will be set to 50 msecs.
 */
void
CQSoundGenerator::
appendSound(qreal amplitude, quint16 frequency, quint32 msecs, Shape shape)
{
  msecs = qMax(msecs, static_cast<quint32>(50));

  qreal singleWaveTime = 1.0/frequency;
  qreal samplesPerWave = qCeil(format_->sampleRate()*singleWaveTime);

  quint32 waveCount  = qCeil(msecs/(singleWaveTime*1000.0));
  quint32 sampleSize = static_cast<quint32>(format_->sampleSize()/8.0);

  QByteArray data(waveCount*samplesPerWave*sampleSize*format_->channelCount(), '\0');

  unsigned char *dataPointer = reinterpret_cast<unsigned char*>(data.data());

  for (quint32 currentWave = 0; currentWave < waveCount; currentWave++) {
    for (int currentSample = 0; currentSample < samplesPerWave; currentSample++) {
      double f = currentSample/static_cast<double>(samplesPerWave);

      double v = 0.0;

      if      (shape == Shape::SQUARE) {
        if      (f < 0.25) v =  0.0;
        else if (f < 0.50) v =  1.0;
        else if (f < 0.75) v = -1.0;
        else               v =  0.0;
      }
      else if (shape == Shape::TRIANGLE) {
        if      (f < 0.25) v =        4.0* f        ;
        else if (f < 0.50) v =  1.0 - 4.0*(f - 0.25);
        else if (f < 0.75) v =      - 4.0*(f - 0.50);
        else               v = -1.0 + 4.0*(f - 0.75);
      }
      else if (shape == Shape::SAWTOOTH) {
        if      (f < 0.50) v = 2.0* f        ;
        else               v = 2.0*(f - 1.00);
      }
      else
        v = qSin(f*2*M_PI);

      quint16 sampleValue = static_cast<quint16>(amplitude*(v + 1.0)*16383.0);

      for (int channel = 0; channel < format_->channelCount(); channel++) {
        qToLittleEndian(sampleValue, dataPointer);

        dataPointer += sampleSize;
      }
    }
  }

  soundBuffer_->append(data);
}

/*
 * \brief Appends a pause with a specific length to the sound buffer.
 *
 * \param msecs The duration of the pause.
 */
void
CQSoundGenerator::
appendPause(quint32 msecs)
{
  msecs = qMax(msecs, static_cast<quint32>(50));

  QByteArray data(format_->sampleRate()*(msecs/1000.0)*format_->channelCount(), '\0');

  unsigned char* dataPointer = reinterpret_cast<unsigned char*>(data.data());

  for (int i = 0; i < data.size(); i += 2) {
    qToLittleEndian(16383, dataPointer);
    dataPointer += 2;
  }

  soundBuffer_->append(data);
}

/*
 * \brief Clears the sound buffer.
 */
void
CQSoundGenerator::
clear()
{
  soundBuffer_->clear();
}

/*
 * \brief Plays the current sound buffer. Note, this method is asynchronous.
 */
void
CQSoundGenerator::
play()
{
  output_->start(outputBuffer_);
}

/*
 * \brief Internal, currently unused slot when the sound output's state changes, ie. Idle (stop).
 */
void
CQSoundGenerator::
playbackFinished()
{
  if (output_->state() == QAudio::IdleState) {
    //qDebug() << "Playback finished";
  }
}

/*
 * \brief A static function to simply play a single tone.
 *
 * This method runs asynchronous and uses a single soundgenerator, so be careful when
 * playing sounds without any pause.
 */
void
CQSoundGenerator::
playSound(qreal amplitude, quint16 frequency, quint32 msecs, Shape shape)
{
  delete s_generator;

  s_generator = new CQSoundGenerator(nullptr);

  s_generator->clear();
  s_generator->appendSound(amplitude, frequency, msecs, shape);
  s_generator->play();
}
