#include "musicaudiorecorderwidget.h"
#include "ui_musicaudiorecorderwidget.h"
#include "musictime.h"
#include "musicutils.h"
#include "musicmessagebox.h"
#include "musicaudiorecordercore.h"

#include <QMovie>
#include <QFileDialog>

MusicAudioRecorderWidget::MusicAudioRecorderWidget(QWidget *parent)
    : MusicAbstractMoveDialog(parent),
      ui(new Ui::MusicAudioRecorderWidget), m_mBuffer(BufferSize, 0)
{
    ui->setupUi(this);

    ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->topTitleCloseButton->setToolTip(tr("Close"));

    connect(ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
    ui->startButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    ui->startButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->startButton->setToolTip(tr("startAudio"));
    ui->stopButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    ui->stopButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->stopButton->setToolTip(tr("stopAudio"));
    ui->playButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    ui->playButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->playButton->setToolTip(tr("playAudio"));
    ui->saveButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    ui->saveButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->saveButton->setToolTip(tr("saveButton"));

    connect(ui->startButton, SIGNAL(clicked()), SLOT(onRecordStart()));
    connect(ui->stopButton, SIGNAL(clicked()), SLOT(onRecordStop()));
    connect(ui->playButton, SIGNAL(clicked()), SLOT(onRecordPlay()));
    connect(ui->saveButton, SIGNAL(clicked()), SLOT(onRecordSave()));

    ui->checkBox->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    ui->checkBox_2->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    ui->checkBox_3->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    ui->checkBox_4->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    ui->checkBox_5->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    ui->checkBox->setCursor(QCursor(Qt::PointingHandCursor));
    ui->checkBox_2->setCursor(QCursor(Qt::PointingHandCursor));
    ui->checkBox_3->setCursor(QCursor(Qt::PointingHandCursor));
    ui->checkBox_4->setCursor(QCursor(Qt::PointingHandCursor));
    ui->checkBox_5->setCursor(QCursor(Qt::PointingHandCursor));

    ui->progress->setStyleSheet(MusicUIObject::MProgressBar02);
    ui->horizontalSlider->setStyleSheet(MusicUIObject::MSliderStyle01);

    connect(&m_timer, SIGNAL(timeout()), SLOT(onTimerout()));
    ui->stopButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    m_movie = nullptr;
    m_time = 0;

    m_miMaxValue = 0;
    ui->horizontalSlider->setValue(100);
    m_miVolume = 100;

    m_mpAudioInputSound = nullptr;
    m_mpAudioOutputSound = nullptr;

    m_mpInputDevSound = nullptr;
    m_mpInputDevSound = nullptr;

    m_recordCore = new MusicAudioRecorderCore(this);

    initMonitor();
}

MusicAudioRecorderWidget::~MusicAudioRecorderWidget()
{
    delete m_recordCore;
    delete m_mpAudioInputSound;
    delete m_mpAudioOutputSound;
    delete m_mpInputDevSound;
    delete m_mpOutputDevSound;
    delete m_movie;
    delete ui;
}

QString MusicAudioRecorderWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicAudioRecorderWidget::onTimerout()
{
    QString text = MusicTime::normalTime2Label( ++m_time );
    ui->timer->setText( text );
}

void MusicAudioRecorderWidget::initMonitor()
{
    m_mFormatSound.setSampleSize(16); //set sample sze to 16 bit
    m_mFormatSound.setSampleType(QAudioFormat::UnSignedInt ); //Sample type as usigned integer sample
    m_mFormatSound.setByteOrder(QAudioFormat::LittleEndian); //Byte order
    m_mFormatSound.setCodec("audio/pcm"); //set codec as simple audio/pcm

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(m_mFormatSound))
    {
        //Default format not supported - trying to use nearest
        m_mFormatSound = infoIn.nearestFormat(m_mFormatSound);
    }

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());
    if (!infoOut.isFormatSupported(m_mFormatSound))
    {
        //Default format not supported - trying to use nearest
        m_mFormatSound = infoOut.nearestFormat(m_mFormatSound);
    }

    createAudioInput();
    createAudioOutput();

    m_mpOutputDevSound = m_mpAudioOutputSound->start();
    m_mpInputDevSound = m_mpAudioInputSound->start();
    connect(m_mpInputDevSound, SIGNAL(readyRead()), SLOT(onReadMore()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(onSliderValueChanged(int)));
}

void MusicAudioRecorderWidget::onRecordStart()
{
    m_recordCore->onRecordStart();

    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    m_timer.start(MT_S2MS);

    if(m_movie == nullptr)
    {
        m_movie = new QMovie(":/toolSets/lb_rate", QByteArray(), this);
    }
    ui->timer_2->setMovie(m_movie);
    m_movie->start();
}

void MusicAudioRecorderWidget::onRecordPlay()
{
    m_recordCore->onRecordPlay();
    m_movie->start();
}

void MusicAudioRecorderWidget::onRecordStop()
{
    m_recordCore->onRecordStop();

    m_timer.stop();
    m_movie->stop();
    m_time = 0;
    ui->playButton->setEnabled(true);
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->saveButton->setEnabled(true);
}

void MusicAudioRecorderWidget::onRecordSave()
{
    QString filename = QFileDialog::getSaveFileName( this,
        tr("choose a filename to save under"), QDir::currentPath(), "Wav(*.wav)");
    if(!filename.isEmpty())
    {
        m_recordCore->addWavHeader(MusicUtils::UCore::toLocal8Bit(filename));
    }
}

void MusicAudioRecorderWidget::onStateChange(QAudio::State state)
{
    if(state == QAudio::IdleState)
    {
        onRecordStop();
    }
}

void MusicAudioRecorderWidget::createAudioInput()
{
    if (m_mpInputDevSound != 0)
    {
        disconnect(m_mpInputDevSound, 0, this, 0);
        m_mpInputDevSound = 0;
    }
    QAudioDeviceInfo inputDevice(QAudioDeviceInfo::defaultInputDevice());
    m_mpAudioInputSound = new QAudioInput(inputDevice, m_mFormatSound, this);
}

void MusicAudioRecorderWidget::createAudioOutput()
{
    QAudioDeviceInfo outputDevice(QAudioDeviceInfo::defaultOutputDevice());
    m_mpAudioOutputSound = new QAudioOutput(outputDevice, m_mFormatSound, this);
}

int MusicAudioRecorderWidget::applyVolumeToSample(short iSample)
{
    //Calculate volume, Volume limited to  max 30000 and min -30000
    return std::max(std::min(((iSample * m_miVolume) / 50), 30000), -30000);
}

void MusicAudioRecorderWidget::onSliderValueChanged(int value)
{
    m_miVolume = value;
}

void MusicAudioRecorderWidget::onReadMore()
{
    //Return if audio input is nullptr
    if(!m_mpAudioInputSound)
    {
        return;
    }
    //Check the number of samples in input buffer
    qint64 len = m_mpAudioInputSound->bytesReady();
    //Limit sample size
    if(len > 4096)
    {
        len = 4096;
    }
    //Read sound samples from input device to buffer
    qint64 l = m_mpInputDevSound->read(m_mBuffer.data(), len);
    if(l > 0)
    {
        //Assign sound samples to short array
        short* resultingData = (short*)m_mBuffer.data();
        short *outdata=resultingData;
        outdata[ 0 ] = resultingData [ 0 ];
        int iIndex;
        if(false)
        {
            //Remove noise using Low Pass filter algortm[Simple algorithm used to remove noise]
            for ( iIndex=1; iIndex < len; iIndex++ )
            {
                outdata[ iIndex ] = 0.333 * resultingData[iIndex ] + ( 1.0 - 0.333 ) * outdata[ iIndex-1 ];
            }
        }
        m_miMaxValue = 0;
        for ( iIndex=0; iIndex < len; iIndex++ )
        {
            //Cange volume to each integer data in a sample
            int value = applyVolumeToSample( outdata[ iIndex ]);
            outdata[ iIndex ] = value;
            m_miMaxValue = m_miMaxValue >= value ? m_miMaxValue : value;
        }
        //write modified sond sample to outputdevice for playback audio
        m_mpOutputDevSound->write((char*)outdata, len);
        QTimer::singleShot(MT_S2MS, this, SLOT(onTimeOut()));
    }
}

void MusicAudioRecorderWidget::onTimeOut()
{
    ui->progress->setValue(m_miMaxValue);
}

int MusicAudioRecorderWidget::exec()
{
    setBackgroundPixmap(ui->background, size());
    return MusicAbstractMoveDialog::exec();
}
