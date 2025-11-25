#pragma once
#include <QTimer>
#include <QObject>
#include "AutoSaveMode.h"


class AutoSaveManager : public QObject {
	Q_OBJECT
public:
	AutoSaveManager(QObject* parent = nullptr);

	void setMode(AutoSaveMode mode);
	AutoSaveMode getMode() const;
	void onInputTextEdited(int charCountAdd);

signals:
	void requestSave();

private slots:
	void handleTimerTimeout();

private:
	QTimer* autoSaveTimer;
	AutoSaveMode CurrentMode;
	int Timelimit;
	int Stringlimit;
	int StringCount;

};