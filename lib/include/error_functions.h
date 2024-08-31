#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(
    const char *format,
    ...); // 在标准错误设备上打印错误信息，并打出与当前error值对应的错误文本。

void errExit(const char *format, ...); // 与errMsg类似，此外还会终止程序

void err_exit(const char *format, ...);

void errExitEN(int errnum, const char *format, ...); // 只打印错误号

void fatal(const char *format, ...); // 诊断一般性错误，终止程序

void usageErr(const char *format, ...); // 诊断命令函错误

void cmdLineErr(const char *format, ...); // 类似usageErr

#endif