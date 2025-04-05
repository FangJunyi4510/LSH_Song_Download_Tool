#include "widget.h"
#include "ui_widget.h"
#include "configuredialog.h"

#include <QClipboard>
#include <QFileSystemWatcher>
#include <QProcess>
#include <QRegularExpression>
#include <QDir>
#include <QThread>
#include <QSettings>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    const QList<QDir> tryList = {
        QDir::homePath() + "/下载",
        QDir::homePath() + "/Download",
        QDir::homePath() + "/桌面",
        QDir::homePath() + "/Desktop",
        QDir::homePath()
    };
    for(const auto &each : tryList) {
        path = each;
        if(path.exists()) {
            break;
        }
    }

    dialog.setBrowser(&browser);
    dialog.setPath(&path);
    dialog.setWebsite(&website);

    QSettings settings;
    if(!settings.allKeys().isEmpty()) {
        browser = settings.value("BrowserPath").toString();
        path = settings.value("DownloadPath").toString();
        website = settings.value("Website").toString();
    }
}

Widget::~Widget() {
    delete ui;
    QSettings settings;
    settings.setValue("BrowserPath", browser);
    settings.setValue("DownloadPath", path.path());
    settings.setValue("Website", website);
}

void Widget::on_update_clicked() {
    list.clear();
    QString text = ui->input->toPlainText();
    list = text.split(QRegularExpression("\\s+"));
    updateName();
}

void Widget::updateName() {
    ui->count->setText("/ " + QString::number(list.size()));
    if(ui->index->value() < 0) {
        ui->index->setValue(list.size() - 1);
        return;
    }
    if(ui->index->value() >= list.size()) {
        ui->index->setValue(0);
        return;
    }
    ui->name->setText(list[ui->index->value()]);
}

void Widget::rename() {
    if(!path.exists()) {
        addInfo("下载文件夹不正确");
        return;
    }
    QStringList files = path.entryList(QDir::Files, QDir::Time);

    if(files.isEmpty()) {
        addInfo("没有下载文件");
        return;
    }
    QFile file = path.filePath(files.first());
    QFileInfo info(file);

    QString newFilename = ui->name->text() + "." + info.suffix();
    QString newFilePath = path.filePath(newFilename);
    QString state = "失败";
    if(file.rename(newFilePath)) {
        state = "成功";
    }
    addInfo("重命名 " + info.fileName() + " => " + newFilename + " : " + state);
}

void Widget::addInfo(const QString &info) {
    ui->message->setText(info);
}


void Widget::on_open_clicked() {
    QString url, name = ui->name->text();
    url = website + name + "%20" + ui->addition->text() ;

    QProcess* firefox = new QProcess(this);
    firefox->setProgram(browser);
    firefox->setArguments({url});
    if(!firefox->startDetached()) {
        addInfo("无法启动浏览器: 浏览器配置不正确");
        return;
    }
}


void Widget::on_index_valueChanged(int arg1) {
    updateName();
}


void Widget::on_next_clicked() {
    ui->index->setValue(ui->index->value() + 1);
}


void Widget::on_rename_clicked() {
    rename();
}


void Widget::on_superNext_clicked() {
    on_rename_clicked();
    on_next_clicked();
    on_open_clicked();
}


void Widget::on_configure_clicked() {
    dialog.open();
}

