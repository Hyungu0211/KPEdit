#pragma once
#include <string>

using namespace std;

class Document
{
public:
    Document();

    void setFilePath(const string& path);
    string getFilePath() const;

	// dirty 상태 관리
    bool getIsDirty() const;
    void setDirty(bool dirty);

private:
    string filePath;
    bool isDirty;
};