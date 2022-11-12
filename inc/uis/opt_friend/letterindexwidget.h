#ifndef LETTERINDEXWIDGET_H
#define LETTERINDEXWIDGET_H

#include <QWidget>

namespace Ui {
class LetterIndexWidget;
}

class LetterIndexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LetterIndexWidget(QWidget *parent = nullptr);
    ~LetterIndexWidget();

private:
    Ui::LetterIndexWidget *ui;
};

#endif // LetterIndexWidget_H
