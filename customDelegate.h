#ifndef customDelegate_HEADER
#define customDelegate_HEADER

#include <qwidget.h>
#include <qlineedit>
#include <QTableWidget>
#include <QItemDelegate>

class customDelegate : public QItemDelegate
{
public:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
        const QModelIndex& index) const
    {
        QLineEdit* delegateQLineEdit = new QLineEdit(parent);
        // Set validator
        delegateQLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"))); // restricts users to only enter 0 to 9, where 0 means empty
        delegateQLineEdit->setAlignment(Qt::AlignCenter); // aligns text in the center
        delegateQLineEdit->setMaxLength(1); // restricts users to only enter one number
        delegateQLineEdit->setFont(QFont("Arial", 25, QFont::Bold));
        return delegateQLineEdit;
    }
};
// Creating a custom delegate using lineedits to use in sudokutable


#endif