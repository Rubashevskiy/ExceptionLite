#include "exceptionlite.h"

ExceptionLite::ExceptionLite(const string &eFile, const string &eFunction, const int eLine, const string &error)
                  : fileErr(eFile), functionErr(eFunction), lineErr(eLine), whatErr(error)
{
  saveTrace();
}

void ExceptionLite::saveTrace()
{
  void *callstack[128];
  const int nMaxFrames = sizeof(callstack) / sizeof(callstack[0]);
  char buf[1024];
  int nFrames = backtrace(callstack, nMaxFrames);
  char **symbols = backtrace_symbols(callstack, nFrames);
  std::ostringstream trace_buf;
  for (int i = 1; i < nFrames; i++) {
    Dl_info info;
    if (dladdr(callstack[i], &info) && info.dli_sname) {
      char *demangled = NULL;
      int status = -1;
      if (info.dli_sname[0] == '_') {
        demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
      }
      snprintf(buf, sizeof(buf), "%-3d %*p %s\n",
        i, int(2 + sizeof(void*) * 2), callstack[i],
        (status == 0) ? (demangled) : (info.dli_sname == 0) ? (symbols[i]) : (info.dli_sname));
      free(demangled);
    } 
    else {
      snprintf(buf, sizeof(buf), "%-3d %*p %s\n", i, int(2 + sizeof(void*) * 2), callstack[i], symbols[i]);
    }
    trace_buf << buf;
  }
  free(symbols);
  traceErr = trace_buf.str();
};