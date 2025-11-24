#include "Document.h"

Document::Document() : isDirty(false) {}

void Document::setFilePath(const string& path) { filePath = path; }
string Document::getFilePath() const { return filePath; }

bool Document::getIsDirty() const { return isDirty; }
void Document::setDirty(bool dirty) { isDirty = dirty; }