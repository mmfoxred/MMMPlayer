#include "musicvolumegainwidget.h"
#include "ui_musicvolumegainwidget.h"
#include "musicmessagebox.h"
#include "musicuiobject.h"

#include <QProcess>
#include <QEventLoop>
#include <QFileDialog>

#define GAIN_DEFAULT 89
#define GAIN_TRACKDB "Recommended \"Track\" dB change:"
#define GAIN_ALBUMDB "Recommended \"Album\" dB change for all files:"

MusicVolumeGainTableWidget::MusicVolumeGainTableWidget(QWidget *parent)
    : MusicAbstractTableWidget(parent)
{
    setColumnCount(5);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 332);
    headerview->resizeSection(1, 60);
    headerview->resizeSection(2, 60);
    headerview->resizeSection(3, 60);
    headerview->resizeSection(4, 60);
}

MusicVolumeGainTableWidget::~MusicVolumeGainTableWidget()
{

}

QString MusicVolumeGainTableWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicVolumeGainTableWidget::listCellClicked(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
}


MusicVolumeGainWidget::MusicVolumeGainWidget(QWidget *parent)
    : MusicAbstractMoveDialog(parent),
      ui(new Ui::MusicVolumeGainWidget), m_process(nullptr)
{
    ui->setupUi(this);

    ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    ui->addFileButton->setIcon(QIcon(":/toolSets/btn_gain_add_file"));
    ui->addFileButton->setIconSize(QSize(40, 40));
    ui->addFileButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->addFileButton->setToolTip(tr("addFile"));
    ui->addFileButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->addFilesButton->setIcon(QIcon(":/toolSets/btn_gain_add_files"));
    ui->addFilesButton->setIconSize(QSize(40, 40));
    ui->addFilesButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->addFilesButton->setToolTip(tr("addFiles"));
    ui->addFilesButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->rmFileButton->setIcon(QIcon(":/toolSets/btn_gain_rm_file"));
    ui->rmFileButton->setIconSize(QSize(40, 40));
    ui->rmFileButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->rmFileButton->setToolTip(tr("rmFile"));
    ui->rmFileButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->rmFilesButton->setIcon(QIcon(":/toolSets/btn_gain_rm_files"));
    ui->rmFilesButton->setIconSize(QSize(40, 40));
    ui->rmFilesButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->rmFilesButton->setToolTip(tr("rmFiles"));
    ui->rmFilesButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->analysisButton->setIcon(QIcon(":/toolSets/btn_analysis"));
    ui->analysisButton->setIconSize(QSize(40, 40));
    ui->analysisButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->analysisButton->setToolTip(tr("analysis"));
    ui->analysisButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->applyButton->setIcon(QIcon(":/toolSets/btn_analysis_apply"));
    ui->applyButton->setIconSize(QSize(50, 50));
    ui->applyButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    ui->applyButton->setToolTip(tr("apply"));
    ui->applyButton->setCursor(QCursor(Qt::PointingHandCursor));

    ui->volumeLineEdit->setStyleSheet(MusicUIObject::MLineEditStyle01);
    ui->volumeLineEdit->setValidator(new QRegExpValidator(QRegExp("-?[0-9]+$"), this));

    m_currentIndex = -1;
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, SIGNAL(readyReadStandardOutput()), SLOT(analysisOutput()));

    connect(ui->addFileButton, SIGNAL(clicked()), SLOT(addFileButtonClicked()));
    connect(ui->addFilesButton, SIGNAL(clicked()), SLOT(addFilesButtonClicked()));
    connect(ui->rmFileButton, SIGNAL(clicked()), SLOT(rmFileButtonClicked()));
    connect(ui->rmFilesButton, SIGNAL(clicked()), SLOT(rmFilesButtonClicked()));
    connect(ui->analysisButton, SIGNAL(clicked()), SLOT(analysisButtonClicked()));
    connect(ui->applyButton, SIGNAL(clicked()), SLOT(applyButtonClicked()));
    connect(ui->volumeLineEdit, SIGNAL(textChanged(QString)), SLOT(volumeLineTextChanged(QString)));
}

MusicVolumeGainWidget::~MusicVolumeGainWidget()
{
    delete m_process;
    delete ui;
}

QString MusicVolumeGainWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicVolumeGainWidget::createItemFinished(const QString &track, const QString &album)
{
    if(m_currentIndex >= m_paths.count())
    {
        return;
    }

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(MusicUtils::UWidget::elidedText(font(), m_paths[m_currentIndex], Qt::ElideRight, 320));
    item->setToolTip(m_paths[m_currentIndex]);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 0, item);

                      item = new QTableWidgetItem;
    item->setText(QString::number(GAIN_DEFAULT - track.toDouble()));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 1, item);

                      item = new QTableWidgetItem;
    item->setText(QString::number(ui->volumeLineEdit->text().toDouble() - GAIN_DEFAULT + track.toDouble()));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 2, item);

                      item = new QTableWidgetItem;
    item->setText(QString::number(GAIN_DEFAULT - album.toDouble()));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 3, item);

                      item = new QTableWidgetItem;
    item->setText(QString::number(ui->volumeLineEdit->text().toDouble() - GAIN_DEFAULT + album.toDouble()));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 4, item);
}

void MusicVolumeGainWidget::setControlEnable(bool enable)
{
    ui->addFileButton->setEnabled(enable);
    ui->addFilesButton->setEnabled(enable);
    ui->rmFileButton->setEnabled(enable);
    ui->rmFilesButton->setEnabled(enable);
    ui->analysisButton->setEnabled(enable);
    ui->applyButton->setEnabled(enable);
}

void MusicVolumeGainWidget::addFileButtonClicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles );
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilters( QStringList() << "All File(*.*)" << "MP3 File(*.mp3)" );
    if(dialog.exec())
    {
        setControlEnable(false);
        int orcount = m_paths.count();
        foreach(const QString &path, dialog.selectedFiles())
        {
            if(!m_paths.contains(path))
            {
                m_paths << path;
            }
        }
        for(int i=orcount; i<m_paths.count(); ++i)
        {
            m_currentIndex = i;
            QEventLoop loop(this);
            connect(m_process, SIGNAL(finished(int)), &loop, SLOT(quit()));
            m_process->start(MAKE_GAIN_FULL, QStringList() << m_paths[i]);
            loop.exec();
        }
        setControlEnable(true);
    }
}

void MusicVolumeGainWidget::addFilesButtonClicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory );
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        setControlEnable(false);
        QList<QFileInfo> file(dialog.directory().entryInfoList());
        foreach(const QFileInfo &info, file)
        {
            if( QString("mp3").contains(info.suffix().toLower()) &&
                !m_paths.contains(info.absoluteFilePath()) )
            {
                m_currentIndex = m_paths.count();
                m_paths << info.absoluteFilePath();

                QEventLoop loop(this);
                connect(m_process, SIGNAL(finished(int)), &loop, SLOT(quit()));
                m_process->start(MAKE_GAIN_FULL, QStringList() << m_paths.last());
                loop.exec();
            }
        }
        setControlEnable(true);
    }
}

void MusicVolumeGainWidget::rmFileButtonClicked()
{
    int row = ui->tableWidget->currentRow();
    if(row < 0)
    {
        MusicMessageBox message;
        message.setText(tr("please select one item"));
        message.exec();
        return;
    }
    ui->tableWidget->removeRow(row);
}

void MusicVolumeGainWidget::rmFilesButtonClicked()
{
    m_paths.clear();
    ui->tableWidget->clear();
    m_currentIndex = -1;
}

void MusicVolumeGainWidget::analysisButtonClicked()
{
    ///do nothing here
}

void MusicVolumeGainWidget::applyButtonClicked()
{
    if(m_paths.isEmpty())
    {
        MusicMessageBox message;
        message.setText(tr("Music gain list is empty!"));
        message.exec();
        return;
    }

    disconnect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(analysisOutput()));
    connect(m_process, SIGNAL(readyReadStandardOutput()), SLOT(applyOutput()));

    setControlEnable(false);
    ui->progressBarAll->setRange(0, ui->tableWidget->rowCount());
    for(int i=0; i<ui->tableWidget->rowCount(); ++i)
    {
        QEventLoop loop(this);
        connect(m_process, SIGNAL(finished(int)), &loop, SLOT(quit()));
        m_process->start(MAKE_GAIN_FULL, QStringList() << "-g" <<
                         ui->tableWidget->item(i, 2)->text() << m_paths[i]);
        ui->progressBarAll->setValue(i + 1);
        loop.exec();
    }
    setControlEnable(true);
    rmFilesButtonClicked();

    disconnect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(applyOutput()));
    connect(m_process, SIGNAL(readyReadStandardOutput()), SLOT(analysisOutput()));

    MusicMessageBox message;
    message.setText(tr("Music gain finished!"));
    message.exec();
}

void MusicVolumeGainWidget::volumeLineTextChanged(const QString &text)
{
    double d = text.toDouble();
    for(int i=0; i<ui->tableWidget->rowCount(); ++i)
    {
        QString v = ui->tableWidget->item(i, 1)->text();
        ui->tableWidget->item(i, 2)->setText(QString::number(d - v.toDouble()));
                v = ui->tableWidget->item(i, 3)->text();
        ui->tableWidget->item(i, 4)->setText(QString::number(d - v.toDouble()));
    }
}

void MusicVolumeGainWidget::analysisOutput()
{
    QString track, album;
    while(m_process->canReadLine())
    {
        QByteArray data = m_process->readLine();
        if(data.contains( GAIN_TRACKDB ))
        {
            data.replace(GAIN_TRACKDB, QByteArray());
            data.replace("\r\n", QByteArray());
            track = QString(data.trimmed());
        }
        if(data.contains( GAIN_ALBUMDB ))
        {
            data.replace(GAIN_ALBUMDB, QByteArray());
            data.replace("\r\n", QByteArray());
            album = QString(data.trimmed());
        }
    }

    if(!track.isEmpty() || !album.isEmpty())
    {
        createItemFinished(track, album);
    }
}

void MusicVolumeGainWidget::applyOutput()
{
    while(m_process->canReadLine())
    {
        QByteArray data = m_process->readLine();
        if(data.contains("Applying gain change"))
        {
            ui->progressBar->setValue(40);
        }
        else if(data.contains("done"))
        {
            ui->progressBar->setValue(100);
        }
        else
        {
            ui->progressBar->setValue(80);
        }
    }
}

int MusicVolumeGainWidget::exec()
{
    if(!QFile::exists(MAKE_GAIN_FULL))
    {
        MusicMessageBox message;
        message.setText(tr("Lack of plugin file!"));
        message.exec();
        return -1;
    }

    setBackgroundPixmap(ui->background, size());
    return MusicAbstractMoveDialog::exec();
}
