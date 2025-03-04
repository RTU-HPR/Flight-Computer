#include "logger.hpp"

static inline void stop() {
  fflush(stdout);
  printf("Stopping...\n");
}

void logger_task(void *pvParameters)
{
  printf("\n%s: Hello, world!\n", pcTaskGetName(NULL));

  FF_Disk_t *pxDisk = FF_SDDiskInit("sd0");
  configASSERT(pxDisk);
  FF_Error_t xError = FF_SDDiskMount(pxDisk);
  if (FF_isERR(xError) != pdFALSE) {
      FF_PRINTF("FF_SDDiskMount: %s\n",
                (const char *)FF_GetErrMessage(xError));
      stop();
  }
  FF_FS_Add("/sd0", pxDisk);

  FF_FILE *pxFile = ff_fopen("/sd0/filename.txt", "a");
  if (!pxFile) {
      FF_PRINTF("ff_fopen failed: %s (%d)\n", strerror(stdioGET_ERRNO()),
                stdioGET_ERRNO());
      stop();
  }
  if (ff_fprintf(pxFile, "Hello, world!\n") < 0) {
      FF_PRINTF("ff_fprintf failed: %s (%d)\n", strerror(stdioGET_ERRNO()),
                stdioGET_ERRNO());
      stop();
  }
  if (-1 == ff_fclose(pxFile)) {
      FF_PRINTF("ff_fclose failed: %s (%d)\n", strerror(stdioGET_ERRNO()),
                stdioGET_ERRNO());
      stop();
  }
  FF_FS_Remove("/sd0");
  FF_Unmount(pxDisk);
  FF_SDDiskDelete(pxDisk);
  puts("Goodbye, world!");

  vTaskDelete(NULL);
}