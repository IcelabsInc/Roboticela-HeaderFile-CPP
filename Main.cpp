#include "Roboticela.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
    TkinterWindow::Window window;
    window.InitializeWindow();

    TkinterWindow::Label label;
    label.InitializeLabel(&window);
    label.SetXCenterAlignment(true);
    label.SetYCenterAlignment(true);
    label.SetFontSize(30);
    label.SetXCenterAlignment(false);
    label.Pack();
    label.SetLabelTextWrap(true);
    label.SetBackgroundColor(255, 255, 255);
    label.SetTextColor(20, 20, 20);
    label.SetTextVerticalCenterAlignment(true);
    label.SetTextHorizontalCenterAlignment(true);
    label.SetText("Something is wenting wrong. We have to fix it.");
    label.SetWidth(300);

    window.StartMainLoop();

    return 0;
}
