// Created by Muhammad Shahsawar.
// Company: Muhammad Technology.

#pragma once

// Including some header files.
#include "Common.h"
#include "Event.h"
#include "Console.h"
#include "Font.h"

namespace TkinterWindow
{
    class EXPORTIMPORT Label : public __TkinterWindow::Widget, public TkinterWindow::Event
    {
    private:
        // [ Starting ] - Variables.
        __TkinterWindow::Widget *__parentObject;
        TkinterWindow::Console __console;
        std::string __sLabelText = "Label";
        std::string __sClassName = "Static";
        __TkinterWindow::LABELTHEME __labelTheme;
        TkinterWindow::Font __labelFont;
        int __nXPosition = 10, __nYPosition = 50;
        int __nWidth = 98, __nHeight = 98;
        bool __bXFill = false, __bYFill = false;
        bool __bXCenterAlign = false, __bYCenterAlign = false, __bLeftAlign = false, __bRightAlign = false, __bTopAlign = false, __bBottomAlign = false;
        int __nLeftMargin = 0, __nRightMargin = 0, __nTopMargin = 0, __nBottomMargin = 0;
        bool __bPackLabel = false;
        int __nLeftPadding = 0, __nRightPadding = 0, __nTopPadding = 0, __nBottomPadding = 0;
        bool __bTextLeftAlign = false, __bTextRightAlign = false, __bTextTopAlign = false, __bTextBottomAlign = false, __bTextXCenterAlign = false, __bTextYCenterAlign = false;
        bool __bTextWrap = false;
        // [ Ending ] - Variables.

        // [ Starting ] - Private Functions.
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT LabelProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        void __CheckWarning(std::string sFunctionName);
        void __LoadLabelThemeFromTheme();
        // [ Ending ] - Private Functions.

    public:
        // [ Starting ] - Public Functions.
        // [ Starting ] - Initializers.
        bool InitializeLabel(__TkinterWindow::Widget *parentObject, std::string sClassName);
        bool InitializeLabel(__TkinterWindow::Widget *parentObject);
        bool Initialize(__TkinterWindow::Widget *parentObject, std::string sClassName);
        bool Initialize(__TkinterWindow::Widget *parentObject);
        // [ Ending ] - Initializers.

        // [ Starting ] - Position and size functions.
        bool SetLabelPosition(int nHorizontalPosition, int nVerticalPosition);
        bool SetPosition(int nXPosition, int nYPosition);

        bool SetLabelHorizontalPosition(int nHorizontalPosition);
        bool SetHorizontalPosition(int nHorizontalPosition);
        bool SetLabelXPosition(int nXPosition);
        bool SetXPosition(int nXPosition);

        bool SetLabelVerticalPosition(int nVerticalPosition);
        bool SetVerticalPosition(int nVerticalPosition);
        bool SetLabelYPosition(int nYPosition);
        bool SetYPosition(int nYPosition);

        bool SetLabelSize(int nWidth, int nHeight);
        bool SetSize(int nWidth, int nHeight);

        bool SetLabelWidth(int nWidth);
        bool SetWidth(int nWidth);

        bool SetLabelHeight(int nHeight);
        bool SetHeight(int nHeight);
        // [ Ending ] - Position and size functions.

        // [ Starting ] - Filling functions.
        bool SetHorizontalLabelFill(bool bFillLabelHorizontal);
        bool SetXLabelFill(bool bFillLabelHorizontal);
        bool SetHorizontaltalFill(bool bFillLabelHorizontal);
        bool SetXFill(bool bFillLabelHorizontal);

        bool SetVerticalLabelFill(bool bFillLabelVertical);
        bool SetYLabelFill(bool bFillLabelVertical);
        bool SetVerticalFill(bool bFillLabelVertical);
        bool SetYFill(bool bFillLabelVertical);
        // [ Ending ] - Filling functions.

        // [ Starting ] - Margin functions.
        bool SetLabelMargin(int nLeftMargin, int nTopMargin, int nRightMargin, int nBottomMargin);
        bool SetMargin(int nLeftMargin, int nTopMargin, int nRightMargin, int nBottomMargin);

        bool SetLabelLeftMargin(int nLeftMargin);
        bool SetLeftMargin(int nLeftMargin);

        bool SetLabelRightMargin(int nRightMargin);
        bool SetRightMargin(int nRightMargin);

        bool SetLabelTopMargin(int nTopMargin);
        bool SetTopMargin(int nTopMargin);

        bool SetLabelBottomMargin(int nBottomMargin);
        bool SetBottomMargin(int nBottomMargin);
        // [ Ending ] - Margin functions

        // [ Starting ] - Alignment functions.
        bool SetLabelLeftAlignment(bool bLeftAlignment);
        bool SetLeftAlignment(bool bLeftAlignment);

        bool SetLabelRightAlignment(bool bRightAlignment);
        bool SetRightAlignment(bool bRightAlignment);

        bool SetLabelTopAlignment(bool bTopAlignment);
        bool SetTopAlignment(bool bTopAlignment);

        bool SetLabelBottomAlignment(bool bBottomAlignment);
        bool SetBottomAlignment(bool bBottomAlignment);

        bool SetLabelHorizontalCenterAlignment(bool bHorizontalCenterAlignment);
        bool SetHorizontalCenterAlignment(bool bHorizontalCenterAlignment);
        bool SetLabelXCenterAlignment(bool bXCenterAlignment);
        bool SetXCenterAlignment(bool bXCenterAlignment);

        bool SetLabelVerticalCenterAlignment(bool bVerticalCenterAlignment);
        bool SetVerticalCenterAlignment(bool bVerticalCenterAlignment);
        bool SetLabelYCenterAlignment(bool bYCenterAlignment);
        bool SetYCenterAlignment(bool bYCenterAlignment);
        // [ Ending ] - Alignment functions.

        // [ Starting ] - Place and fill label functions.
        bool PlaceLabel();
        bool Place();

        bool PackLabel();
        bool Pack();
        // [ Ending ] - Place and fill label functions.

        // [ Starting ] - Coloring functions.
        bool SetLabelBackgroundColor(COLORREF color);
        bool SetLabelBackgroundColor(int nRed, int nGreen, int nBlue);
        bool SetBackgroundColor(COLORREF color);
        bool SetBackgroundColor(int nRed, int nGreen, int nBlue);

        bool SetLabelTextColor(COLORREF color);
        bool SetLabelTextColor(int nRed, int nGreen, int nBlue);
        bool SetTextColor(COLORREF color);
        bool SetTextColor(int nRed, int nGreen, int nBlue);
        // [ Ending ] - Coloring functions.

        // [ Starting ] - Label font Styling.
        bool SetLabelFontItalicStyle(bool bItalicStyle);
        bool SetFontItalicStyle(bool bItalicStyle);

        bool SetLabelFontUnderlineStyle(bool bUnderlineStyle);
        bool SetFontUnderlineStyle(bool bUnderlineStyle);

        bool SetLabelFontStrikeoutStyle(bool bStrikeoutStyle);
        bool SetFontStrikeoutStyle(bool bStrikeoutStyle);
        // [ Ending ] - Label font Styling.

        // [ Starting ] - Label font Size.
        bool SetLabelFontSize(int nFontSize);
        bool SetFontSize(int nFontSize);

        bool SetLabelFontHeight(int nFontHeight);
        bool SetFontHeight(int nFontHeight);

        bool SetLabelFontWidth(int nFontWidth);
        bool SetFontWidth(int nFontWidth);
        // [ Ending ] - Label font Size.

        // [ Starting ] - Label font family.
        bool SetLabelFontFamily(std::string sFontFamily);
        bool SetFontFamily(std::string sFontFamily);

        bool SetLabelFontStyle(std::string sFontStyle);
        bool SetFontStyle(std::string sFontStyle);
        // [ Ending ] - Label font family.

        // [ Starting ] - Label font rotation controls.
        bool SetLabelFontEscapement(int nFontEscapement);
        bool SetFontEscapement(int nFontEscapement);

        bool SetLabelFontOrientation(int nFontOrientation);
        bool SetFontOrientation(int nFontOrientation);
        // [ Starting ] -  Label font rotation controls.

        // [ Starting ] - SetLabelFontWeight.
        bool SetLabelFontWeight(int nFontWeight);
        bool SetFontWeight(int nFontWeight);
        // [ Ending ] - SetLabelFontWeight.

        // [ Starting ] - debugger controls.
        bool EnableDebugger(void);
        bool DisableDebugger(void);
        // [ Ending ] - debugger controls.

        // [ Starting ] - Padding functions.
        bool SetLabelPadding(int nLeftPadding, int nTopPadding, int nRightPadding, int nBottomPadding);
        bool SetPadding(int nLeftPadding, int nTopPadding, int nRightPadding, int nBottomPadding);

        bool SetLabelLeftPadding(int nLeftPadding);
        bool SetLeftPadding(int nLeftPadding);

        bool SetLabelTopPadding(int nTopPadding);
        bool SetTopPadding(int nTopPadding);

        bool SetLabelRightPadding(int nRightPadding);
        bool SetRightPadding(int nRightPadding);

        bool SetLabelBottomPadding(int nBottomPadding);
        bool SetBottomPadding(int nBottomPadding);
        // [ Ending ] - Padding functions.

        // [ Starting ] - Text Alignment.
        bool SetLabelTextLeftAlignment(bool bLeftAlignment);
        bool SetTextLeftAlignment(bool bLeftAlignment);

        bool SetLabelTextRightAlignment(bool bRightAlignment);
        bool SetTextRightAlignment(bool bRightAlignment);

        bool SetLabelTextTopAlignment(bool bTopAlignment);
        bool SetTextTopAlignment(bool bTopAlignment);

        bool SetLabelTextBottomAlignment(bool bBottomAlignment);
        bool SetTextBottomAlignment(bool bBottomAlignment);

        bool SetLabelTextHorizontalCenterAlignment(bool bHorizontalCenterAlignment);
        bool SetTextHorizontalCenterAlignment(bool bHorizontalCenterAlignment);
        bool SetLabelTextXCenterAlignment(bool bXCenterAlignment);
        bool SetTextXCenterAlignment(bool bXCenterAlignment);

        bool SetLabelTextVerticalCenterAlignment(bool bVerticalCenterAlignment);
        bool SetTextVerticalCenterAlignment(bool bVerticalCenterAlignment);
        bool SetLabelTextYCenterAlignment(bool bYCenterAlignment);
        bool SetTextYCenterAlignment(bool bYCenterAlignment);
        // [ Ending ] - Text Alignment.

        // [ Starting ] - Text setting and getting functions.
        bool SetLabelText(std::string sText);
        bool SetText(std::string sText);

        std::string GetLabelText(void);
        std::string GetText(void);
        // [ Ending ] - Text setting and getting functions.

        // [ Starting ] - Text Wrap functions.
        bool SetLabelTextWrap(bool bTextWrap);
        bool SetTextWrap(bool bTextWrap);
        // [ Ending ] - Text Wrap functions.

        // [ Ending ] - Public Funtions.
    };
}
