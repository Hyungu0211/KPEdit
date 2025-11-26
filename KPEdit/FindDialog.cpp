#include "FindDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

FindDialog::FindDialog(QWidget* parent)
	: QDialog(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QHBoxLayout* findLayout = new QHBoxLayout;
	findLayout->addWidget(new QLabel("Find:"));
	findLineEdit = new QLineEdit(this);
	findLayout->addWidget(findLineEdit);

	QHBoxLayout* replaceLayout = new QHBoxLayout;
	replaceLayout->addWidget(new QLabel("Replace:"));
	replaceLineEdit = new QLineEdit(this);
	replaceLayout->addWidget(replaceLineEdit);

	mainLayout->addLayout(findLayout);
	mainLayout->addLayout(replaceLayout);

	findButton = new QPushButton("Find", this);
	replaceButton = new QPushButton("Replace", this);
	replaceAllButton = new QPushButton("Replace All", this);

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(findButton);
	buttonLayout->addWidget(replaceButton);
	buttonLayout->addWidget(replaceAllButton);

	mainLayout->addLayout(buttonLayout);

	setWindowTitle("Find/Replace");

	connect(findButton, &QPushButton::clicked, this, &FindDialog::onFindClicked);
	connect(replaceButton, &QPushButton::clicked, this, &FindDialog::onReplaceClicked);
	connect(replaceAllButton, &QPushButton::clicked, this, &FindDialog::onReplaceAllClicked);
}

void FindDialog::onFindClicked() {
	emit findRequested(findLineEdit->text());
}

void FindDialog::onReplaceClicked() {
	emit replaceRequested(findLineEdit->text(), replaceLineEdit->text());
}

void FindDialog::onReplaceAllClicked() {
	emit replaceAllRequested(findLineEdit->text(), replaceLineEdit->text());
}