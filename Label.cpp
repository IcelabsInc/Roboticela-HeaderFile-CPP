// Company: Icelabs Inc.

// Including some important header files.
#include "Label.h"

// Using some libraries.
#pragma comment(lib, "Build-Data\\Event.lib")
#pragma comment(lib, "Build-Data\\Console.lib")
#pragma comment(lib, "Build-Data\\Font.lib")

namespace __TkinterWindow
{
    COLORREF SetTextColorF(HDC hDC, COLORREF textColor)
    {
        return SetTextColor(hDC, textColor);
    }
}

namespace TkinterWindow
{
    // [ Starting ] - Public Functions.
    // [ Starting ] - Initializers.
    bool Label::InitializeLabel(__TkinterWindow::Widget *parentObject, std::string sClassName)
    {
        // Helps to initialize the label.
        __parentObject = parentObject;

        if (sClassName == "")
        {
            sClassName = "Unknown";
        }

        // Disabiling the error check for console.
        __console.DisableErrorCheck();

        // Setting the class object and name.
        __console.SetLoggerClassObject("Label");
        __console.SetloggerClassName(sClassName);

        // Initializing some stuff.
        __theme = __parentObject->__theme;
        __hInstance = __parentObject->__hInstance;

        __LoadLabelThemeFromTheme();

        // Initializing the font.
        __labelFont.InitializeFont(sClassName);

        // Declaring the window class.
        __console.Log("InitializeLabel", "Initializing the class for the label.");
        WNDCLASSEXA labelClass = {0};
        labelClass.cbSize = sizeof(WNDCLASSEXA);
        labelClass.cbClsExtra = 0;
        labelClass.hbrBackground = CreateSolidBrush(__labelTheme.labelBackgroundColor);
        labelClass.cbWndExtra = 0;
        labelClass.hCursor = NULL;
        labelClass.hIcon = NULL;
        labelClass.hIconSm = NULL;
        labelClass.hInstance = __hInstance;
        labelClass.lpfnWndProc = WndProc;
        labelClass.lpszClassName = __sClassName.c_str();
        labelClass.lpszMenuName = 0;
        labelClass.style = CS_HREDRAW | CS_VREDRAW;

        __console.Log("InitializeLabel", "Registering the class of the label.");
        if (!RegisterClassExA(&labelClass))
        {
            __console.Log("InitializeLabel", "Error: Registeration of the label class failed.");
            return false;
        }

        // Creating the window.
        __console.Log("InitializeLabel", "Creating the label. X: %d, Y: %d, Width: %d, Height: %d", __nXPosition, __nYPosition, __nWidth, __nHeight);

        __windowHandle = CreateWindowExA(0, __sClassName.c_str(), __sLabelText.c_str(), WS_CHILD, __nXPosition, __nYPosition, __nWidth, __nHeight, __parentObject->__windowHandle, 0, __hInstance, this);

        if (__windowHandle == NULL)
        {
            __console.Log("InitializeLabel", "Error: Creating of the label failed.");

            return false;
        }

        // Setting the transparency.
        SetLayeredWindowAttributes(__windowHandle, __theme->transparentColor, 255, LWA_COLORKEY | LWA_ALPHA);

        // Showing the window
        ShowWindow(__windowHandle, SW_SHOW);
        UpdateWindow(__windowHandle);

        return true;
    }

    bool Label::InitializeLabel(__TkinterWindow::Widget *parentObject)
    {
        // Same as InitializeLabel.
        return InitializeLabel(parentObject, "");
    }

    bool Label::Initialize(__TkinterWindow::Widget *parentObject, std::string sClassName)
    {
        // Same as InitializeLabel.
        return InitializeLabel(parentObject, sClassName);
    }

    bool Label::Initialize(__TkinterWindow::Widget *parentObject)
    {
        // Same as InitializeLabel.
        return InitializeLabel(parentObject, "");
    }
    // [ Ending ] - Initializers.

    // [ Starting ] - Position and size functions.
    bool Label::SetLabelPosition(int nHorizontalPosition, int nVerticalPosition)
    {
        __CheckWarning("SetLabelPosition");

        // Helps to set the position of the label.
        __console.Log("SetLabelPosition", "Setting the label position. X: %d, Y: %d.", nHorizontalPosition, nVerticalPosition);

        __nXPosition = nHorizontalPosition;
        __nYPosition = nVerticalPosition;

        if (__windowHandle != NULL)
        {
            SetWindowPos(__windowHandle, NULL, __nXPosition, __nYPosition, __nWidth, __nHeight, 0);
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetPosition(int nXPosition, int nYPosition)
    {
        // Same as SetLabelPosition.
        return SetLabelPosition(nXPosition, nYPosition);
    }

    bool Label::SetLabelHorizontalPosition(int nHorizontalPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(nHorizontalPosition, __nYPosition);
    }

    bool Label::SetHorizontalPosition(int nHorizontalPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(nHorizontalPosition, __nYPosition);
    }

    bool Label::SetLabelXPosition(int nXPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(nXPosition, __nYPosition);
    }

    bool Label::SetXPosition(int nXPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(nXPosition, __nYPosition);
    }

    bool Label::SetLabelVerticalPosition(int nVerticalPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(__nXPosition, nVerticalPosition);
    }

    bool Label::SetVerticalPosition(int nVerticalPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(__nXPosition, nVerticalPosition);
    }

    bool Label::SetLabelYPosition(int nYPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(__nXPosition, nYPosition);
    }

    bool Label::SetYPosition(int nYPosition)
    {
        // Same as SetLabelPosition but with different arguments.
        return SetLabelPosition(__nXPosition, nYPosition);
    }

    bool Label::SetLabelSize(int nWidth, int nHeight)
    {
        __CheckWarning("SetLabelSize");

        // Helps to set the size of the label.
        __console.Log("SetLabelSize", "Setting the label size. Width: %d, Height: %d.", nWidth, nHeight);

        __nWidth = nWidth;
        __nHeight = nHeight;

        if (__windowHandle != NULL)
        {
            SetWindowPos(__windowHandle, NULL, __nXPosition, __nYPosition, __nWidth, __nHeight, 0);
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetSize(int nWidth, int nHeight)
    {
        // Same as setLabelSize.
        return SetLabelSize(nWidth, nHeight);
    }

    bool Label::SetLabelWidth(int nWidth)
    {
        // Same as SetLabelSize with different arguments.
        return SetLabelSize(nWidth, __nHeight);
    }

    bool Label::SetWidth(int nWidth)
    {
        // Same as SetLabelSize with different arguments.
        return SetLabelSize(nWidth, __nHeight);
    }

    bool Label::SetLabelHeight(int nHeight)
    {
        // Same as SetLabelSize with different arguments.
        return SetLabelSize(__nWidth, nHeight);
    }

    bool Label::SetHeight(int nHeight)
    {
        // Same as SetLabelSize with different arguments.
        return SetLabelSize(__nWidth, nHeight);
    }
    // [ Ending ] - Position and size functions.

    // [ Starting ] - Filling functions.
    bool Label::SetHorizontalLabelFill(bool bFillLabelHorizontal)
    {
        __CheckWarning("SetHorizontalLabelFill");

        __console.Log("SetHorizontalLabelFill", "Settingt the horizontal label fill to %d.", bFillLabelHorizontal);

        __bXFill = bFillLabelHorizontal;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetXLabelFill(bool bFillLabelHorizontal)
    {
        // Same as SetHorizontalLabelFill.
        return SetHorizontalLabelFill(bFillLabelHorizontal);
    }

    bool Label::SetHorizontaltalFill(bool bFillLabelHorizontal)
    {
        // Same as SetHorizontalLabelFill.
        return SetHorizontalLabelFill(bFillLabelHorizontal);
    }

    bool Label::SetXFill(bool bFillLabelHorizontal)
    {
        // Same as SetHorizontalLabelFill.
        return SetHorizontalLabelFill(bFillLabelHorizontal);
    }

    bool Label::SetVerticalLabelFill(bool bFillLabelVertical)
    {
        __CheckWarning("SetVerticalLabelFill");

        __console.Log("SetVerticalLabelFill", "Settingt the vertical label fill to %d.", bFillLabelVertical);

        __bYFill = bFillLabelVertical;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetYLabelFill(bool bFillLabelVertical)
    {
        // Same as SetVerticalLabelFill.
        return SetVerticalLabelFill(bFillLabelVertical);
    }

    bool Label::SetVerticalFill(bool bFillLabelVertical)
    {
        // Same as SetVerticalLabelFill.
        return SetVerticalLabelFill(bFillLabelVertical);
    }

    bool Label::SetYFill(bool bFillLabelVertical)
    {
        // Same as SetVerticalLabelFill.
        return SetVerticalLabelFill(bFillLabelVertical);
    }
    // [ Ending ] - Filling functions.

    // [ Starting ] - Margin functions.
    bool Label::SetLabelMargin(int nLeftMargin, int nTopMargin, int nRightMargin, int nBottomMargin)
    {
        __CheckWarning("SetLabelMargin");

        __console.Log("SetLabelMargin", "Setting the label margin to Left: %d, Right: %d, Top: %d, Bottom: %d.", nLeftMargin, nRightMargin, nTopMargin, nBottomMargin);

        __nLeftMargin = nLeftMargin;
        __nRightMargin = nRightMargin;
        __nTopMargin = nTopMargin;
        __nBottomMargin = nBottomMargin;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetMargin(int nLeftMargin, int nTopMargin, int nRightMargin, int nBottomMargin)
    {
        // Same as SetLabelMargin.
        return SetLabelMargin(nLeftMargin, nTopMargin, nRightMargin, nBottomMargin);
    }

    bool Label::SetLabelLeftMargin(int nLeftMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(nLeftMargin, __nTopMargin, __nRightMargin, __nBottomMargin);
    }

    bool Label::SetLeftMargin(int nLeftMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(nLeftMargin, __nTopMargin, __nRightMargin, __nBottomMargin);
    }

    bool Label::SetLabelRightMargin(int nRightMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(__nLeftMargin, __nTopMargin, nRightMargin, __nBottomMargin);
    }

    bool Label::SetRightMargin(int nRightMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(__nLeftMargin, __nTopMargin, nRightMargin, __nBottomMargin);
    }

    bool Label::SetLabelTopMargin(int nTopMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(__nLeftMargin, nTopMargin, __nRightMargin, __nBottomMargin);
    }

    bool Label::SetTopMargin(int nTopMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(__nLeftMargin, nTopMargin, __nRightMargin, __nBottomMargin);
    }

    bool Label::SetLabelBottomMargin(int nBottomMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(__nLeftMargin, __nTopMargin, __nRightMargin, nBottomMargin);
    }

    bool Label::SetBottomMargin(int nBottomMargin)
    {
        // Same as SetLabelMargin but with different arguments.
        return SetLabelMargin(__nLeftMargin, __nTopMargin, __nRightMargin, nBottomMargin);
    }
    // [ Ending ] - Margin functions

    // [ Starting ] - Alignment functions.
    bool Label::SetLabelLeftAlignment(bool bLeftAlignment)
    {
        __CheckWarning("SetLabelLeftAlignment");

        __console.Log("SetLabelLeftAlignment", "Setting the left alignment of label to %d.", bLeftAlignment);

        __bLeftAlign = bLeftAlignment;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetLeftAlignment(bool bLeftAlignment)
    {
        // Same as SetLabelLeftAlignment.
        return SetLabelLeftAlignment(bLeftAlignment);
    }

    bool Label::SetLabelRightAlignment(bool bRightAlignment)
    {
        __CheckWarning("SetLabelRightAlignment");

        __console.Log("SetLabelRightAlignment", "Setting the right alignment of label to %d.", bRightAlignment);

        __bRightAlign = bRightAlignment;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetRightAlignment(bool bRightAlignment)
    {
        // Same as SetLabelRightAlignment.
        return SetLabelRightAlignment(bRightAlignment);
    }

    bool Label::SetLabelTopAlignment(bool bTopAlignment)
    {
        __CheckWarning("SetLabelTopAlignment");

        __console.Log("SetLabelTopAlignment", "Setting the top alignment of label to %d.", bTopAlignment);

        __bTopAlign = bTopAlignment;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetTopAlignment(bool bTopAlignment)
    {
        // Same as SetLabelTopAlignment.
        return SetLabelTopAlignment(bTopAlignment);
    }

    bool Label::SetLabelBottomAlignment(bool bBottomAlignment)
    {
        __CheckWarning("SetLabelBottomAlignment");

        __console.Log("SetLabelBottomAlignment", "Setting the bottom alignment of label to %d.", bBottomAlignment);

        __bBottomAlign = bBottomAlignment;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetBottomAlignment(bool bBottomAlignment)
    {
        // Same as SetLabelBottomAlignment.
        return SetLabelBottomAlignment(bBottomAlignment);
    }

    bool Label::SetLabelHorizontalCenterAlignment(bool bHorizontalCenterAlignment)
    {
        __CheckWarning("SetLabelHorizontalCenterAlignment");

        __console.Log("SetLabelHorizontalCenterAlignment", "Setting the horizontal center alignment of label to %d.", bHorizontalCenterAlignment);

        __bXCenterAlign = bHorizontalCenterAlignment;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetHorizontalCenterAlignment(bool bHorizontalCenterAlignment)
    {
        // Same as SetLabelHorizontalCenterAlignment.
        return SetLabelHorizontalCenterAlignment(bHorizontalCenterAlignment);
    }

    bool Label::SetLabelXCenterAlignment(bool bXCenterAlignment)
    {
        // Same as SetLabelHorizontalCenterAlignment.
        return SetLabelHorizontalCenterAlignment(bXCenterAlignment);
    }

    bool Label::SetXCenterAlignment(bool bXCenterAlignment)
    {
        // Same as SetLabelHorizontalCenterAlignment.
        return SetLabelHorizontalCenterAlignment(bXCenterAlignment);
    }

    bool Label::SetLabelVerticalCenterAlignment(bool bVerticalCenterAlignment)
    {
        __CheckWarning("SetLabelVerticalCenterAlignment");

        __console.Log("SetLabelVerticalCenterAlignment", "Setting the vertical center alignment of label to %d.", bVerticalCenterAlignment);

        __bYCenterAlign = bVerticalCenterAlignment;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetVerticalCenterAlignment(bool bVerticalCenterAlignment)
    {
        // Same as SetLabelVerticalCenterAlignment.
        return SetLabelVerticalCenterAlignment(bVerticalCenterAlignment);
    }

    bool Label::SetLabelYCenterAlignment(bool bYCenterAlignment)
    {
        // Same as SetLabelVerticalCenterAlignment.
        return SetLabelVerticalCenterAlignment(bYCenterAlignment);
    }

    bool Label::SetYCenterAlignment(bool bYCenterAlignment)
    {
        // Same as SetLabelVerticalCenterAlignment.
        return SetLabelVerticalCenterAlignment(bYCenterAlignment);
    }
    // [ Ending ] - Alignment functions.

    // [ Starting ] - Place and fill label functions.
    bool Label::PlaceLabel()
    {
        __CheckWarning("PlaceLabel");

        __console.Log("PlaceLabel", "Setting the label filling type to placement.");

        __bPackLabel = false;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::Place()
    {
        // Same as PlaceLabel.
        return PlaceLabel();
    }

    bool Label::PackLabel()
    {
        __CheckWarning("PackLabel");

        __console.Log("PackLabel", "Setting the label filling type to packing.");

        __bPackLabel = true;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::Pack()
    {
        // Same as PackLabel.
        return PackLabel();
    }
    // [ Ending ] - Place and fill label functions.

    // [ Starting ] - Coloring functions.
    bool Label::SetLabelBackgroundColor(COLORREF color)
    {
        // Helps to set the background color of the label.
        __CheckWarning("SetLabelBackgroundColor");

        __console.Log("SetLabelBackgroundColor", "Setting the label background color to Red: %d, Green: %d, Blue: %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __labelTheme.labelBackgroundColor = color;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetLabelBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as the SetLabelBackgroundColor but with different arguments.
        return SetLabelBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Label::SetBackgroundColor(COLORREF color)
    {
        // Same as the SetLabelBackgroundColor.
        return SetLabelBackgroundColor(color);
    }

    bool Label::SetBackgroundColor(int nRed, int nGreen, int nBlue)
    {
        // Same as the SetLabelBackgroundColor.
        return SetLabelBackgroundColor(RGB(nRed, nGreen, nBlue));
    }

    bool Label::SetLabelTextColor(COLORREF color)
    {
        // Helps to set the label text color of the label.
        __CheckWarning("SetLabelTextColor");

        __console.Log("SetLabelTextColor", "Setting the label text color to Red: %d, Green: %d, Blue: %d.", GetRValue(color), GetGValue(color), GetBValue(color));

        __labelTheme.labelTextColor = color;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetLabelTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetLabelTextColor but with different arguments.
        return SetLabelTextColor(RGB(nRed, nGreen, nBlue));
    }

    bool Label::SetTextColor(COLORREF color)
    {
        // Same as SetLabelTextColor.
        return SetLabelTextColor(color);
    }

    bool Label::SetTextColor(int nRed, int nGreen, int nBlue)
    {
        // Same as SetLabelTextColor.
        return SetLabelTextColor(RGB(nRed, nGreen, nBlue));
    }
    // [ Ending ] - Coloring functions.

    // [ Starting ] - Label font Styling.
    bool Label::SetLabelFontItalicStyle(bool bItalicStyle)
    {
        // Helps to set the label font italic style.
        __CheckWarning("SetLabelFontItalicStyle");

        bool bResult = __labelFont.SetFontItalicStyle(bItalicStyle);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontItalicStyle(bool bItalicStyle)
    {
        // Same as the SetLabelFontItalicStyle.
        return SetLabelFontItalicStyle(bItalicStyle);
    }

    bool Label::SetLabelFontUnderlineStyle(bool bUnderlineStyle)
    {
        // Helps to set the label font underline style.
        __CheckWarning("SetLabelFontUnderlineStyle");

        bool bResult = __labelFont.SetFontUnderlineStyle(bUnderlineStyle);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontUnderlineStyle(bool bUnderlineStyle)
    {
        // Same as the SetLabelFontUnderlineStyle.
        return SetLabelFontUnderlineStyle(bUnderlineStyle);
    }

    bool Label::SetLabelFontStrikeoutStyle(bool bStrikeoutStyle)
    {
        // Helps to set the label font strikeout style.
        __CheckWarning("SetLabelFontStrikeoutStyle");

        bool bResult = __labelFont.SetFontStrikeoutStyle(bStrikeoutStyle);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontStrikeoutStyle(bool bStrikeoutStyle)
    {
        // Same as SetLabelFontStrikeout style.
        return SetLabelFontStrikeoutStyle(bStrikeoutStyle);
    }
    // [ Ending ] - Label font Styling.

    // [ Starting ] - Label font Size.
    bool Label::SetLabelFontSize(int nFontSize)
    {
        // Helps to the set the label font size.
        __CheckWarning("SetLabelFontSize");

        bool bResult = __labelFont.SetFontSize(nFontSize);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontSize(int nFontSize)
    {
        // Same as SetLabelFontSize.
        return SetLabelFontSize(nFontSize);
    }

    bool Label::SetLabelFontHeight(int nFontHeight)
    {
        // Helps to set the label font height.
        __CheckWarning("SetLabelFontHeight");

        bool bResult = __labelFont.SetFontHeight(nFontHeight);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontHeight(int nFontHeight)
    {
        // Same as SetLabelFontHeight.
        return SetLabelFontHeight(nFontHeight);
    }

    bool Label::SetLabelFontWidth(int nFontWidth)
    {
        // Helps to set the label font width.
        __CheckWarning("SetLabelFontWidth");

        bool bResult = __labelFont.SetFontWidth(nFontWidth);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontWidth(int nFontWidth)
    {
        // Same as SetLabelFontWidth.
        return SetLabelFontWidth(nFontWidth);
    }
    // [ Ending ] - Label font Size.

    // [ Starting ] - Label font family.
    bool Label::SetLabelFontFamily(std::string sFontFamily)
    {
        // Helps to set the font family of the label.
        __CheckWarning("SetLabelFontFamily");

        bool bResult = __labelFont.SetFontFamily(sFontFamily);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontFamily(std::string sFontFamily)
    {
        // Same as SetLabelFontFamily.
        return SetLabelFontFamily(sFontFamily);
    }

    bool Label::SetLabelFontStyle(std::string sFontStyle)
    {
        /// Same as SetLabelFontFamily.
        return SetLabelFontFamily(sFontStyle);
    }

    bool Label::SetFontStyle(std::string sFontStyle)
    {
        // Same as SetLabelFontFamily.
        return SetLabelFontFamily(sFontStyle);
    }
    // [ Ending ] - Label font family.

    // [ Starting ] - Label font rotation controls.
    bool Label::SetLabelFontEscapement(int nFontEscapement)
    {
        // Helps to set the escapement of the label font.
        __CheckWarning("SetLabelFontEscapement");

        bool bResult = __labelFont.SetEscapement(nFontEscapement);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontEscapement(int nFontEscapement)
    {
        // Same as SetLabelFontEscapement.
        return SetLabelFontEscapement(nFontEscapement);
    }

    bool Label::SetLabelFontOrientation(int nFontOrientation)
    {
        // Helps to set the label font orientation.
        __CheckWarning("SetLabelFontOrientation");

        bool bResult = __labelFont.SetFontOrientation(nFontOrientation);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontOrientation(int nFontOrientation)
    {
        // Same as SetLabelFontOrientation.
        return SetLabelFontOrientation(nFontOrientation);
    }
    // [ Starting ] -  Label font rotation controls.

    // [ Starting ] - SetLabelFontWeight.
    bool Label::SetLabelFontWeight(int nFontWeight)
    {
        // Helps to set the label font weight.
        __CheckWarning("SetLabelFontWeight");

        bool bResult = __labelFont.SetFontWeight(nFontWeight);

        if (__windowHandle != NULL)
        {
            InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return bResult;
    }

    bool Label::SetFontWeight(int nFontWeight)
    {
        // Same as SetLabelFontWeight.
        return SetLabelFontWeight(nFontWeight);
    }
    // [ Ending ] - SetLabelFontWeight.

    // [ Starting ] - debugger controls.
    bool Label::EnableDebugger(void)
    {
        // Helps to enable the debugger.
        return __console.EnableDebugger();
    }

    bool Label::DisableDebugger(void)
    {
        // Helps to disable the debugger.
        return __console.DisableDebugger();
    }
    // [ Ending ] - debugger controls.

    // [ Starting ] - Padding functions.
    bool Label::SetLabelPadding(int nLeftPadding, int nTopPadding, int nRightPadding, int nBottomPadding)
    {
        __CheckWarning("SetLabelPadding");

        __console.Log("SetLabelPadding", "Setting the label padding to Left: %d, Right: %d, Top: %d, Bottom: %d.", nLeftPadding, nTopPadding, nRightPadding, nBottomPadding);

        __nLeftPadding = nLeftPadding;
        __nRightPadding = nRightPadding;
        __nTopPadding = nTopPadding;
        __nBottomPadding = nBottomPadding;

        if (__windowHandle != NULL)
        {
            return SendMessageA(__windowHandle, WM_SIZE, NULL, NULL);
        }

        return true;
    }

    bool Label::SetPadding(int nLeftPadding, int nTopPadding, int nRightPadding, int nBottomPadding)
    {
        // Same as SetLabelPadding.
        return SetLabelPadding(nLeftPadding, nTopPadding, nRightPadding, nBottomPadding);
    }

    bool Label::SetLabelLeftPadding(int nLeftPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(nLeftPadding, __nTopPadding, __nRightPadding, __nBottomPadding);
    }

    bool Label::SetLeftPadding(int nLeftPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(nLeftPadding, __nTopPadding, __nRightPadding, __nBottomPadding);
    }

    bool Label::SetLabelTopPadding(int nTopPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(__nLeftPadding, nTopPadding, __nRightPadding, __nBottomPadding);
    }
    bool Label::SetTopPadding(int nTopPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(__nLeftPadding, nTopPadding, __nRightPadding, __nBottomPadding);
    }

    bool Label::SetLabelRightPadding(int nRightPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(__nLeftPadding, __nTopPadding, nRightPadding, __nBottomPadding);
    }

    bool Label::SetRightPadding(int nRightPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(__nLeftPadding, __nTopPadding, nRightPadding, __nBottomPadding);
    }

    bool Label::SetLabelBottomPadding(int nBottomPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(__nLeftPadding, __nTopPadding, __nRightPadding, nBottomPadding);
    }

    bool Label::SetBottomPadding(int nBottomPadding)
    {
        // Same as SetLabelPadding but with different arguments.
        return SetLabelPadding(__nLeftPadding, __nTopPadding, __nRightPadding, nBottomPadding);
    }
    // [ Ending ] - Padding functions.

    // [ Starting ] - Text Alignment.
    bool Label::SetLabelTextLeftAlignment(bool bLeftAlignment)
    {
        // Helps to set the label text alignment to the left side.
        __CheckWarning("SetLabelTextLeftAlignment");

        __console.Log("SetLabelTextLeftAlignment", "Setting the label left text alignment to %d.", bLeftAlignment);

        __bTextLeftAlign = bLeftAlignment;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextLeftAlignment(bool bLeftAlignment)
    {
        // Same as SetLabelTextLeftAlignment.
        return SetLabelTextLeftAlignment(bLeftAlignment);
    }

    bool Label::SetLabelTextRightAlignment(bool bRightAlignment)
    {
        // Helps to set the label text alignment to the right side.
        __CheckWarning("SetLabelTextRightAlignment");

        __console.Log("SetLabelTextRightAlignment", "Setting the label right text alignment to %d.", bRightAlignment);

        __bTextRightAlign = bRightAlignment;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextRightAlignment(bool bRightAlignment)
    {
        // Same as SetLabelTextRightAlignment.
        return SetLabelTextRightAlignment(bRightAlignment);
    }

    bool Label::SetLabelTextTopAlignment(bool bTopAlignment)
    {
        // Helps to set the label text alignment to the top side.
        __CheckWarning("SetLabelTextTopAlignment");

        __console.Log("SetLabelTextTopAlignment", "Setting the label top text alignment to %d.", bTopAlignment);

        __bTextTopAlign = bTopAlignment;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextTopAlignment(bool bTopAlignment)
    {
        // Same as SetLabelTextTopAlignment.
        return SetLabelTextTopAlignment(bTopAlignment);
    }

    bool Label::SetLabelTextBottomAlignment(bool bBottomAlignment)
    {
        // Helps to set the label text alignment to the top side.
        __CheckWarning("SetLabelTextBottomAlignment");

        __console.Log("SetLabelTextBottomAlignment", "Setting the label bottom text alignment to %d.", bBottomAlignment);

        __bTextBottomAlign = bBottomAlignment;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextBottomAlignment(bool bBottomAlignment)
    {
        // Same as SetLabelTextBottomAlignment.
        return SetLabelTextBottomAlignment(bBottomAlignment);
    }

    bool Label::SetLabelTextHorizontalCenterAlignment(bool bHorizontalCenterAlignment)
    {
        // Helps to set the label text alignment to the top side.
        __CheckWarning("SetLabelTextHorizontalCenterAlignment");

        __console.Log("SetLabelTextHorizontalCenterAlignment", "Setting the label horizontal center text alignment to %d.", bHorizontalCenterAlignment);

        __bTextXCenterAlign = bHorizontalCenterAlignment;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextHorizontalCenterAlignment(bool bHorizontalCenterAlignment)
    {
        // Same as SetLabelTextHorizontalCenterAlignment.
        return SetLabelTextHorizontalCenterAlignment(bHorizontalCenterAlignment);
    }

    bool Label::SetLabelTextXCenterAlignment(bool bXCenterAlignment)
    {
        // Same as SetLabelTextHorizontalCenterAlignment.
        return SetLabelTextHorizontalCenterAlignment(bXCenterAlignment);
    }

    bool Label::SetTextXCenterAlignment(bool bXCenterAlignment)
    {
        // Same as SetLabelTextHorizontalCenterAlignment.
        return SetLabelTextHorizontalCenterAlignment(bXCenterAlignment);
    }

    bool Label::SetLabelTextVerticalCenterAlignment(bool bVerticalCenterAlignment)
    {
        // Helps to set the label text alignment to the top side.
        __CheckWarning("SetLabelTextVerticalCenterAlignment");

        __console.Log("SetLabelTextVerticalCenterAlignment", "Setting the label vertical center text alignment to %d.", bVerticalCenterAlignment);

        __bTextYCenterAlign = bVerticalCenterAlignment;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextVerticalCenterAlignment(bool bVerticalCenterAlignment)
    {
        // Same as SetLabelTextVerticalCenterAlignment.
        return SetLabelTextVerticalCenterAlignment(bVerticalCenterAlignment);
    }

    bool Label::SetLabelTextYCenterAlignment(bool bYCenterAlignment)
    {
        // Same as SetLabelTextVerticalCenterAlignment.
        return SetLabelTextVerticalCenterAlignment(bYCenterAlignment);
    }

    bool Label::SetTextYCenterAlignment(bool bYCenterAlignment)
    {
        // Same as SetLabelTextVerticalCenterAlignment.
        return SetLabelTextVerticalCenterAlignment(bYCenterAlignment);
    }
    // [ Ending ] - Text Alignment.

    // [ Starting ] - Text setting and getting functions.
    bool Label::SetLabelText(std::string sText)
    {
        // Helps to set the label text.
        __CheckWarning("SetLabelText");

        __console.Log("SetLabelText", "Setting the label text to %s", sText.c_str());

        __sLabelText = sText;

        if (__windowHandle != NULL)
        {
            SetWindowTextA(__windowHandle, __sLabelText.c_str());
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetText(std::string sText)
    {
        // Same as SetLabelText.
        return SetLabelText(sText);
    }

    std::string Label::GetLabelText(void)
    {
        // Helps to get the text of the label.
        __CheckWarning("GetLabelText");

        __console.Log("GetLabelText", "Getting the label text. Text: %s", __sLabelText.c_str());

        return __sLabelText;
    }

    std::string Label::GetText(void)
    {
        // Same as GetLabelText.
        return GetLabelText();
    }
    // [ Ending ] - Text setting and getting functions.

    // [ Starting ] - Text Wrap functions.
    bool Label::SetLabelTextWrap(bool bTextWrap)
    {
        // Helps to set the label text wrap.
        __CheckWarning("SetLabelTextWrap");

        __console.Log("SetLabelTextWrap", "Setting the label text wrap to %d.", bTextWrap);

        __bTextWrap = bTextWrap;

        if (__windowHandle != NULL)
        {
            return InvalidateRect(__windowHandle, NULL, FALSE);
        }

        return true;
    }

    bool Label::SetTextWrap(bool bTextWrap)
    {
        return SetLabelTextWrap(bTextWrap);
    }
    // [ Ending ] - Text Wrap functions.
    // [ Ending ] - Public Funtions.

    // [ Starting ] - Private Functions.
    LRESULT Label::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Assigning the procedure to the class procedure.

        if (message == WM_NCCREATE)
        {
            // Setting the class as user data.
            CREATESTRUCT *lParamStruct = (CREATESTRUCT *)lParam;
            TkinterWindow::Label *lpLabelClass = (TkinterWindow::Label *)lParamStruct->lpCreateParams;
            SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)lpLabelClass);

            return DefWindowProcA(hWnd, message, wParam, lParam);
        }
        else
        {
            // Getting the class as user data that stored in NC_CREATE.
            TkinterWindow::Label *windowObject = reinterpret_cast<TkinterWindow::Label *>(static_cast<LONG_PTR>(GetWindowLongPtrA(hWnd, GWLP_USERDATA)));

            if (windowObject)
            {
                // Returning and calling to the class procedure.

                return windowObject->LabelProcedure(hWnd, message, wParam, lParam);
            }
            else
            {
                // Returning and calling to the default window procedure.
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }

        return 0;
    }

    LRESULT Label::LabelProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_NCCALCSIZE:
        {
            // Removing the background.
            if (wParam == TRUE)
            {
                return 0;
            }
        }

        case WM_ERASEBKGND:
        {
            return 1;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT paintStruct;
            HDC paintDC = BeginPaint(hWnd, &paintStruct);

            HDC hDC = CreateCompatibleDC(paintDC);

            RECT rcClientRect;
            GetClientRect(hWnd, &rcClientRect);

            HBITMAP bmp = CreateCompatibleBitmap(paintDC, rcClientRect.right - rcClientRect.left, rcClientRect.bottom - rcClientRect.top);

            HBITMAP oldBmp = (HBITMAP)SelectObject(hDC, bmp);

            // Filling the background.
            HBRUSH backgroundBrush = CreateSolidBrush(__labelTheme.labelBackgroundColor);
            FillRect(hDC, &paintStruct.rcPaint, backgroundBrush);
            DeleteObject(backgroundBrush);

            // Drawing the text.
            __labelFont.GetFontObject(hDC);
            __TkinterWindow::SetTextColorF(hDC, __labelTheme.labelTextColor);
            SetBkMode(hDC, TRANSPARENT);

            RECT textRect;
            textRect = paintStruct.rcPaint;
            textRect.left += __nLeftPadding;
            textRect.right -= __nRightPadding;
            textRect.top += __nTopPadding;
            textRect.bottom -= __nBottomPadding;

            UINT textStyle = 0;

            if (!__bTextWrap)
            {
                textStyle |= DT_SINGLELINE;
            }
            else
            {
                textStyle |= DT_WORDBREAK;
            }

            if (__bTextLeftAlign)
            {
                textStyle |= DT_LEFT;
            }

            if (__bTextRightAlign)
            {
                textStyle |= DT_RIGHT;
            }

            if (__bTextBottomAlign)
            {
                textStyle |= DT_BOTTOM;
            }

            if (__bTextTopAlign)
            {
                textStyle |= DT_TOP;
            }

            if (__bTextXCenterAlign)
            {
                textStyle |= DT_CENTER;
            }

            if (__bTextYCenterAlign)
            {
                textStyle |= DT_VCENTER;
            }

            DrawTextA(hDC, __sLabelText.c_str(), __sLabelText.length(), &textRect, textStyle);

            __labelFont.DeleteFontObject();

            BitBlt(paintDC, 0, 0, rcClientRect.right - rcClientRect.left, rcClientRect.bottom - rcClientRect.top, hDC, 0, 0, SRCCOPY);

            SelectObject(hDC, oldBmp);
            DeleteObject(bmp);
            DeleteDC(hDC);

            EndPaint(hWnd, &paintStruct);
            break;
        }

        case WM_SIZE:
        {
            RECT labelRect;
            GetWindowRect(hWnd, &labelRect);

            int labelUpdateHeight = __nHeight - __theme->__positionDifference, labelUpdateWidth = __nWidth - __theme->__positionDifference;
            int labelUpdateXPosition = __nXPosition + __theme->__positionDifference, labelUpdateYPosition = __nYPosition + __theme->__positionDifference;

            if (__bPackLabel)
            {
                RECT parentRect;
                GetWindowRect(__parentObject->__windowHandle, &parentRect);

                int parentWidth = parentRect.right - parentRect.left - __theme->__positionDifference - __theme->__positionDifference;
                int parentHeight = parentRect.bottom - parentRect.top - __theme->__positionDifference - __theme->__positionDifference - __theme->__nStatusBarHeight - __theme->__nTitleBarHeight;

                if (__bLeftAlign)
                {
                    labelUpdateXPosition = 1 + __theme->__positionDifference;
                }

                if (__bRightAlign)
                {
                    labelUpdateXPosition = parentWidth - 1 - (labelRect.right - labelRect.left) + __theme->__positionDifference;
                }

                if (__bTopAlign)
                {
                    labelUpdateYPosition = __theme->__positionDifference + __theme->__nTitleBarHeight;
                }

                if (__bBottomAlign)
                {
                    labelUpdateYPosition = parentHeight - 1 - (labelRect.bottom - labelRect.top) + __theme->__nTitleBarHeight + __theme->__positionDifference;
                }

                if (__bXFill)
                {
                    labelUpdateWidth = parentRect.right - parentRect.left - 2 - __theme->__positionDifference;
                    labelUpdateXPosition = 1 + __theme->__positionDifference;
                }

                if (__bYFill)
                {
                    labelUpdateHeight = parentRect.bottom - parentRect.top - 1 - __theme->__nStatusBarHeight - __theme->__nTitleBarHeight - (__theme->__positionDifference * 2);
                    labelUpdateYPosition = __theme->__nTitleBarHeight + __theme->__positionDifference;
                }

                if (__bXCenterAlign)
                {
                    labelUpdateXPosition = ((parentWidth - (labelRect.right - labelRect.left)) / 2) + __theme->__positionDifference;
                }

                if (__bYCenterAlign)
                {
                    labelUpdateYPosition = ((parentHeight - (labelRect.bottom - labelRect.top)) / 2) + __theme->__positionDifference + __theme->__nTitleBarHeight;
                }

                labelUpdateXPosition += __nLeftMargin;
                labelUpdateYPosition += __nTopMargin;
                labelUpdateHeight -= __nBottomMargin;
                labelUpdateWidth -= __nRightMargin;
            }

            SetWindowPos(hWnd, NULL, labelUpdateXPosition, labelUpdateYPosition, labelUpdateWidth, labelUpdateHeight, 0);
            InvalidateRect(hWnd, NULL, FALSE);
            InvalidateRect(__parentObject->__windowHandle, NULL, FALSE);
            break;
        }

        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }
        }

        return 0;
    }

    void Label::__CheckWarning(std::string sFunctionName)
    {
        if (__windowHandle == NULL)
        {
            __console.Log(sFunctionName, "Warning: The function is called before the initalization. It can lead to some major problems.");
        }
    }

    void Label::__LoadLabelThemeFromTheme()
    {
        __console.Log("LoadLabelThemeFromTheme", "Loading the label theme from the original theme.");

        if (__labelTheme.labelBackgroundColor == NULL)
        {
            __labelTheme.labelBackgroundColor = __theme->labelTheme.labelBackgroundColor;
        }

        if (__labelTheme.labelTextColor == NULL)
        {
            __labelTheme.labelTextColor = __theme->labelTheme.labelTextColor;
        }
    }
    // [ Ending ] - Private Functions.
}
