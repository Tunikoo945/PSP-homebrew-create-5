#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("HelloPSP", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// Programdan çıkış fonksiyonu
int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();
    return 0;
}

// Callback thread
int callback_thread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

// Callback başlat
int setup_callbacks(void)
{
    int thid = sceKernelCreateThread(
        "update_thread",
        callback_thread,
        0x11,
        0xFA0,
        0,
        0
    );

    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);

    return thid;
}

int main()
{
    setup_callbacks();

    // Ekranı başlat
    pspDebugScreenInit();

    // Yazı yaz
    pspDebugScreenPrintf("Merhaba PSP!\n");
    pspDebugScreenPrintf("start tusuna basip cikabilirsiniz\n");

    // Sonsuz döngü
    while (1)
    {
        sceKernelDelayThread(10000);
    }

    if(pad.Buttons & PSP_CTRL_START)
       {
          sceKernelExitGame()

}

    return 0;
}