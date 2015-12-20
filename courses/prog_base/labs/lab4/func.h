#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

void consColor(int color);
void drawForm(int n, int h, int xO, int yO, int start);
void drawConsole(void);
void drawSmile(void);
void drawSad(void);
void clear(void);
int  fileRows(const char * pread);
void downloadStudent(const char * pread);
void downloadGroupSubject(const char * pread);
void downloadSubjectMark(const char * pread);
int  findRow(void);
void pushStudent(void);
void removeStudent(void);
void showStudent(void);
void showSubject(void);
void showMarks(void);
void newMark(void);
void showExceptionStudent(void);
void saveToFile(const char * pwrite, const char * pwrite2);

#endif // FUNC_H_INCLUDED
