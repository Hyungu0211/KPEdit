#include "AutoSaveManager.h"

AutoSaveManager::AutoSaveManager(QObject* parent)
	: QObject(parent),
	autoSaveTimer(new QTimer(this)),
	StringCount(0),
	CurrentMode(AutoSaveMode::None),
	Stringlimit(100),
	Timelimit(60000)
{
	connect(autoSaveTimer, &QTimer::timeout, this, &AutoSaveManager::handleTimerTimeout);
}

void AutoSaveManager::setMode(AutoSaveMode mode) {
	CurrentMode = mode;
	if (mode == AutoSaveMode::TimeBased) {
		autoSaveTimer->start(Timelimit);
		StringCount = 0;
	}
	else {
		autoSaveTimer->stop();
		StringCount = 0;
	}
}

void AutoSaveManager::onInputTextEdited(int charCountAdd) {
	if (CurrentMode != AutoSaveMode::InputBased)
		return;
	StringCount += charCountAdd;
	if (StringCount >= Stringlimit) {
		emit requestSave();
		StringCount = 0;
	}
}

void AutoSaveManager::handleTimerTimeout() {
	if (CurrentMode == AutoSaveMode::TimeBased) {
		emit requestSave();
	}
}

AutoSaveMode AutoSaveManager::getMode() const {
	return CurrentMode;
}