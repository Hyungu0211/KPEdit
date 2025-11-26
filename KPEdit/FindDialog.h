#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class FindDialog : public QDialog {
	Q_OBJECT

public:
	explicit FindDialog(QWidget* parent = nullptr);

signals:
	void findRequested(const QString& findText);
	void replaceRequested(const QString& findText, const QString& replaceText);
	void replaceAllRequested(const QString& findText, const QString& replaceText);

private:
	QLineEdit* findLineEdit;
	QLineEdit* replaceLineEdit;
	QPushButton* findButton;
	QPushButton* replaceButton;
	QPushButton* replaceAllButton;

private slots:
	void onFindClicked();
	void onReplaceClicked();
	void onReplaceAllClicked();
};