#include "configuredialog.h"
#include "ui_configuredialog.h"
#include <QFileDialog>

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigureDialog) {
    ui->setupUi(this);
}

ConfigureDialog::~ConfigureDialog() {
    delete ui;
}

void ConfigureDialog::setBrowser(QString *browser_) {
    browser = browser_;
}

void ConfigureDialog::setWebsite(QString *website_) {
    website = website_;
}

void ConfigureDialog::setPath(QDir *path_) {
    path = path_;
}

void ConfigureDialog::showEvent(QShowEvent *) {
    ui->browserPath->setText(*browser);
    ui->website->setText(*website);
    ui->path->setText(path->path());
}


void ConfigureDialog::on_selectBrowser_clicked() {
    QString selectedBrowser = QFileDialog::getOpenFileName(this, "选择浏览器可执行文件", ui->browserPath->text(), "所有文件 (*);;可执行文件 (*.exe);;");
    if(!selectedBrowser.isEmpty()) {
        ui->browserPath->setText(selectedBrowser);
    }
}


void ConfigureDialog::on_selectPath_clicked() {
    QString selectedPath = QFileDialog::getExistingDirectory(this, "选择下载文件夹", ui->path->text());
    if(!selectedPath.isEmpty()) {
        ui->path->setText(selectedPath);
    }
}


void ConfigureDialog::on_cancel_clicked() {
    reject();
}


void ConfigureDialog::on_confirm_clicked() {
    *browser = ui->browserPath->text();
    *path = ui->path->text();
    *website = ui->website->text();
    accept();
}

