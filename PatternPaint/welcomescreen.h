#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "colormode.h"

#include <QDialog>

namespace Ui {
class WelcomeScreen;
}

// TODO: Something more flexible
struct SceneTemplate {
    QString name;
    QString photo;
    QString examples;
    QString controllerType;
    QString fixtureType;
    ColorMode colorMode;
    int height;
    int width;
};

class WelcomeScreen : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = 0);
    ~WelcomeScreen();

    SceneTemplate getSelectedTemplate();

private:
    Ui::WelcomeScreen *ui;
};

#endif // WELCOMESCREEN_H
