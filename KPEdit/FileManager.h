#pragma once
#include <QString>

class FileManager
{
public:
    FileManager();
    ~FileManager();

	// 파일 읽기/쓰기
	// Qstring으로 그대로 반환/입력
    QString ReadFile(const QString& path);
    bool WriteFile(const QString& path, const QString& content);
};