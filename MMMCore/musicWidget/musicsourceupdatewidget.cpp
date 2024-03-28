#include "musicsourceupdatewidget.h"
#include "ui_musicsourceupdatewidget.h"
#include "musicsourcedownloadthread.h"
#include "musicdatadownloadthread.h"
#include "musicmessagebox.h"
#include "musicuiobject.h"
#include "musicutils.h"
#include "musicversion.h"

#include <QProcess>

#ifdef MUSIC_GREATER_NEW
#   include <QJsonParseError>
#   include <QJsonObject>
#else
#   ///QJson import
#   include "qjson/parser.h"
#endif

MusicSourceUpdateWidget::MusicSourceUpdateWidget(QWidget *parent)
    : MusicAbstractMoveDialog(parent),
      ui(new Ui::MusicSourceUpdateWidget)
{
    ui->setupUi(this);
    ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->topTitleCloseButton->setToolTip(tr("Close"));
    ui->upgradeButton->setEnabled(false);

    connect(ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui->upgradeFailedLabel, SIGNAL(clicked()), SLOT(upgradeFailedClicked()));
    connect(ui->upgradeButton, SIGNAL(clicked()), SLOT(upgradeButtonClicked()));
}

MusicSourceUpdateWidget::~MusicSourceUpdateWidget()
{
    delete ui;
}

QString MusicSourceUpdateWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicSourceUpdateWidget::upgradeButtonClicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QString localDwonload = "v" + m_newVersionStr + DD_TYPE_EXE;
    MusicDataDownloadThread *download = new MusicDataDownloadThread(QString("%1%2").arg(DOWNLOAD_URL).arg(localDwonload),
                                                                    MusicObject::getAppDir() + localDwonload, MusicDownLoadThreadAbstract::Download_Other, this);
    connect(download, SIGNAL(downloadProgressChanged(float,QString,qint64)), SLOT(downloadProgressChanged(float,QString)));
    connect(download, SIGNAL(downLoadDataChanged(QString)), SLOT(downloadProgressFinished()));
    download->startToDownload();
}

void MusicSourceUpdateWidget::upgradeFailedClicked()
{
    MusicUtils::UCore::openUrl(CSDN_URL, false);
}

void MusicSourceUpdateWidget::downLoadFinished(const QByteArray &data)
{
#ifdef MUSIC_GREATER_NEW
    QJsonParseError jsonError;
    QJsonDocument parseDoucment = QJsonDocument::fromJson(data, &jsonError);
    ///Put the data into Json
    if( jsonError.error != QJsonParseError::NoError ||
        !parseDoucment.isObject())
    {
        return;
    }

    QJsonObject jsonObject = parseDoucment.object();
    m_newVersionStr = jsonObject.value("version").toString();
#else
    QJson::Parser parser;
    bool ok;
    QVariant parseData = parser.parse(data, &ok);
    if(!ok)
    {
        return;
    }

    QVariantMap value = parseData.toMap();
    m_newVersionStr = value["version"].toString();
#endif
    QString text;
    if(m_newVersionStr != MMMMUSIC_VERSION_STR)
    {
        text.append(m_newVersionStr);
        text.append("\r\n");
#ifdef MUSIC_GREATER_NEW
        text.append(jsonObject.value("data").toString());
#else
        text.append(value["data"].toString());
#endif
        ui->upgradeButton->setEnabled(true);
        ui->titleLable_F->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }
    else
    {
        text.append(tr("Current version is updated!"));
        ui->titleLable_F->setAlignment(Qt::AlignCenter);
    }
    ui->titleLable_F->setText( text );
}

void MusicSourceUpdateWidget::downloadProgressChanged(float percent, const QString &total)
{
    ui->fileSizeLabel->setText(tr("FileSize: %1").arg(total));
    ui->downProgressBar->setValue(percent);
    ui->downProgressBarAL->setValue(percent);
}

void MusicSourceUpdateWidget::downloadProgressFinished()
{
    QString localDwonload = "v" + m_newVersionStr + DD_TYPE_EXE;
    MusicMessageBox message(this);
    message.setText(tr("Download Finish, Install Or Not"));
    if(message.exec() == 0)
    {
        QProcess::startDetached(MusicObject::getAppDir() + localDwonload, QStringList());
        MStatic_cast(QWidget*, parent())->close();
    }
}

int MusicSourceUpdateWidget::exec()
{
    setBackgroundPixmap(ui->background, size());

    MusicSourceDownloadThread *download = new MusicSourceDownloadThread(this);
    connect(download, SIGNAL(downLoadByteDataChanged(QByteArray)), SLOT(downLoadFinished(QByteArray)));
    download->startToDownload(VERSION_URL);

    return MusicAbstractMoveDialog::exec();
}
