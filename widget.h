#ifndef WIDGET_H
#define WIDGET_H

#include "configuredialog.h"
#include <QFileSystemWatcher>
#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_update_clicked();

    void on_index_valueChanged(int arg1);

    void on_open_clicked();

    void on_rename_clicked();

    void on_next_clicked();

    void on_superNext_clicked();

    void on_configure_clicked();

private:
    Ui::Widget *ui;
    QStringList list;
    QDir path;
    QString website = "https://www.ihaoge.net/search/result?nsid=4&q=";
    QString browser = QDir::rootPath();

    ConfigureDialog dialog = ConfigureDialog(this);

    void updateName();
    void rename();

    void addInfo(const QString& info);
};
#endif // WIDGET_H
