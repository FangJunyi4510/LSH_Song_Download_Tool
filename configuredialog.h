#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>


class QDir;
namespace Ui {
class ConfigureDialog;
}

class ConfigureDialog : public QDialog {
    Q_OBJECT

public:
    explicit ConfigureDialog(QWidget *parent = nullptr);
    ~ConfigureDialog();
    void setBrowser(QString* browser);
    void setWebsite(QString* website);
    void setPath(QDir* path);

protected:
    void showEvent(QShowEvent*);

private slots:

    void on_selectBrowser_clicked();

    void on_selectPath_clicked();

    void on_cancel_clicked();

    void on_confirm_clicked();

private:
    Ui::ConfigureDialog *ui;
    QString* browser, *website;
    QDir* path;
};

#endif // CONFIGUREDIALOG_H
