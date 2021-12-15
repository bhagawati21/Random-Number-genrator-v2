#include <windows.h>
#include <fstream>
#include <sstream>
#include "randnum.h"

using namespace std;

#define BTN_GENERATE 1
#define BTN_SAVE 2
#define CHKBOX_ALPHA 3
#define CHKBOX_NUM 4
#define CHKBOX_SCHAR 5
#define CHKBOX_PREFIX 6
#define CHKBOX_SUFFIX 7
#define CHKBOX_SEPARATOR 8
#define ACTION_EXIT 9
#define HELP_HELP 10
#define HELP_ABOUT 11

HWND hLength, hRandomNumber, hPrefix, hSuffix, hQuantity, hSeparator, hAfter;
HMENU hMenu;
HFONT hFont;
int flag = 1;
string Help = "GENERATE : This Button generates the random number\n"
              "SAVE : To save all your random number in a file (Default file name : untitled.txt)\n"
              "LENGTH : Here you've to provide length of Random Number (1-100) (Default length : 8)\n"
              "QUANTITY : Here you've to provide how many random number you want to generate(1-1000) (Default quantity : 5)\n"
              "\nFunctions mentioned below works only and only if the respective check box is selected\n"
              "SEPARATOR : Here you've to provide a single character separator which will separate the number\n"
              "AFTER : Here you've to provide the number of character after you want separator(1-99)\n"
              "PREFIX : If you want a prefix in random number provide it here(must be less than or equals to half of length)\n"
              "SUFFIX : If you want a suffix in random number provide it here(must be less than or equals to half of length)\n"
              "ALAPHABATS : If you want Alphabet in your random number\n"
              "NUMBERS : If you want Numbers in your random number(Checked by default)\n"
              "SPACIAL CHARACTERS : If you want Special characters in your random number\n"
              "\nThanks for using this Application";

LRESULT CALLBACK winproc(HWND,UINT,WPARAM,LPARAM);
void AddControls(HWND);
void Output(HWND);
void AddMenus(HWND);
void SaveFile(HWND);
void WriteToFile(HWND,char*);
void AddIcons(HWND);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR lpszarg,int nCmdShow)
{
    WNDCLASSW window = {0};
    window.hbrBackground = (HBRUSH)COLOR_WINDOW;
    window.hCursor = LoadCursor(NULL,IDC_ARROW);
    window.hInstance = hInst;
    window.lpfnWndProc = winproc;
    window.lpszClassName = (LPCWSTR)"MyWindow";

    if(!RegisterClassW(&window))
    {
        MessageBox(NULL,"Could not register the window class",NULL,MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowW((LPCWSTR)"MyWindow",(LPCWSTR)"Random Number Generator",
                      WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,400,170,480,420,NULL,NULL,hInst,NULL);
    if(!hWnd)
    {
        MessageBox(NULL,"Could not create a window",NULL,MB_ICONERROR);
        return 0;
    }

    MSG msg;

    while(GetMessage(&msg,NULL,0,0))
    {
       if (IsDialogMessage(hWnd, &msg) == 0)
       {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
       }
    }

    return msg.wParam;
}

LRESULT CALLBACK winproc(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    PAINTSTRUCT ps;
    switch(msg)
    {
    case WM_PAINT:
        BeginPaint(hWnd, &ps);

        hFont = CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,5, VARIABLE_PITCH,TEXT("Comic Sans MS"));

        SendMessage(hRandomNumber,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hLength,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hQuantity,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hPrefix,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hSuffix,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hSeparator,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hAfter,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));

        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
        AddControls(hWnd);
        AddMenus(hWnd);
        AddIcons(hWnd);
        break;
    case WM_COMMAND:
        switch(wp)
        {
        case ACTION_EXIT:
            SendMessage(hWnd,WM_CLOSE,wp,lp);
            break;
        case HELP_ABOUT:
            MessageBox(hWnd,
            "\t    Welcome\n\nName : Random Number Generator\nDeveloper : Bhagawati Lal Ameta\nVersion : 2.0\n\nThanks For using this software",
            "About",MB_OK);
            break;
        case HELP_HELP:
            MessageBox(hWnd,Help.data(),"Help",MB_OK);
            break;
        case BTN_GENERATE:
            Output(hWnd);
            break;
        case BTN_SAVE:
            if(!GetWindowTextLength(hRandomNumber))
            {
                int choice = MessageBox(hWnd, "There is no random number generated yet\n\nDo you still wants to save an empty file",
                            "No Random Number Generated",MB_YESNO | MB_ICONEXCLAMATION);
                if(choice == IDYES)
                    SaveFile(hWnd);
            }
            else
                SaveFile(hWnd);
            break;
        case CHKBOX_ALPHA:
            if(IsDlgButtonChecked(hWnd,CHKBOX_ALPHA))
             {
                 CheckDlgButton(hWnd,CHKBOX_ALPHA,BST_UNCHECKED);
                 flag--;
             }
            else
            {
                CheckDlgButton(hWnd,CHKBOX_ALPHA,BST_CHECKED);
                flag++;
            }
            break;
        case CHKBOX_NUM:
            if(IsDlgButtonChecked(hWnd,CHKBOX_NUM))
             {
                 CheckDlgButton(hWnd,CHKBOX_NUM,BST_UNCHECKED);
                 flag--;
             }
            else
            {
                CheckDlgButton(hWnd,CHKBOX_NUM,BST_CHECKED);
                flag++;
            }
            break;
        case CHKBOX_SCHAR:
            if(IsDlgButtonChecked(hWnd,CHKBOX_SCHAR))
             {
                 CheckDlgButton(hWnd,CHKBOX_SCHAR,BST_UNCHECKED);
                 flag--;
             }
            else
            {
                CheckDlgButton(hWnd,CHKBOX_SCHAR,BST_CHECKED);
                flag++;
            }
            break;

        case CHKBOX_PREFIX:
            if(IsDlgButtonChecked(hWnd,CHKBOX_PREFIX))
                 CheckDlgButton(hWnd,CHKBOX_PREFIX,BST_UNCHECKED);
            else
                CheckDlgButton(hWnd,CHKBOX_PREFIX,BST_CHECKED);
            break;

        case CHKBOX_SUFFIX:
            if(IsDlgButtonChecked(hWnd,CHKBOX_SUFFIX))
                 CheckDlgButton(hWnd,CHKBOX_SUFFIX,BST_UNCHECKED);
            else
                CheckDlgButton(hWnd,CHKBOX_SUFFIX,BST_CHECKED);
            break;
        case CHKBOX_SEPARATOR:
            if(IsDlgButtonChecked(hWnd,CHKBOX_SEPARATOR))
                 CheckDlgButton(hWnd,CHKBOX_SEPARATOR,BST_UNCHECKED);
            else
                CheckDlgButton(hWnd,CHKBOX_SEPARATOR,BST_CHECKED);
            break;
        }
        break;
    case WM_DESTROY:
       PostQuitMessage(0);
       break;
    case WM_CLOSE:
        DeleteObject(hFont);
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd,msg,wp,lp);
    }

    return 0;
}

void AddControls(HWND hWnd)
{
    //Edit Controls and Buttons
    hRandomNumber = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_AUTOHSCROLL
                            | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL ,50,40,250,100,hWnd,NULL,NULL,NULL);
    hLength = CreateWindowW(L"Edit",L"8",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_GROUP | ES_NUMBER | ES_CENTER ,
                            350,40,80,25,hWnd,NULL,NULL,NULL);
    hQuantity = CreateWindowW(L"Edit",L"5",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_NUMBER | ES_CENTER ,
                            350,105,80,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Separator",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,60,155,90,25,hWnd,(HMENU)CHKBOX_SEPARATOR,NULL,NULL);
    hSeparator = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_CENTER,
                            160,155,40,25,hWnd,NULL,NULL,NULL);
    hAfter = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_CENTER | ES_NUMBER,
                            370,155,40,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Prefix",WS_VISIBLE | WS_CHILD | WS_GROUP | WS_TABSTOP | BS_CHECKBOX,60,200,60,25,hWnd,(HMENU)CHKBOX_PREFIX,NULL,NULL);
    hPrefix = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_CENTER | ES_AUTOHSCROLL,
                            130,200,80,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Suffix",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,260,200,60,25,hWnd,(HMENU)CHKBOX_SUFFIX,NULL,NULL);
    hSuffix = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_CENTER | ES_AUTOHSCROLL,
                            330,200,80,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button",L"Alphabets",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,60,240,90,25,hWnd,(HMENU)CHKBOX_ALPHA,NULL,NULL);
    CreateWindowW(L"Button",L"Numbers",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,170,240,80,25,hWnd,(HMENU)CHKBOX_NUM,NULL,NULL);
    CreateWindowW(L"Button",L"Special Characters",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,270,240,160,25,hWnd,(HMENU)CHKBOX_SCHAR,NULL,NULL);
    HWND hGenerate = CreateWindowW(L"Button",L"Generate",WS_VISIBLE | WS_CHILD | WS_TABSTOP ,100,300,80,30,hWnd,(HMENU)BTN_GENERATE,NULL,NULL);
    CreateWindowW(L"Button",L"Save",WS_VISIBLE | WS_CHILD | WS_TABSTOP ,300,300,50,30,hWnd,(HMENU)BTN_SAVE,NULL,NULL);

    //Static Controls
    CreateWindowW(L"Static",L"Random Number",WS_VISIBLE | WS_CHILD,110,15,110,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Length",WS_VISIBLE | WS_CHILD,365,15,60,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Quantity",WS_VISIBLE | WS_CHILD,358,80,80,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"After",WS_VISIBLE | WS_CHILD ,320,160,50,25,hWnd,NULL,NULL,NULL);

    //CheckDlgButton(hWnd,CHKBOX_ALPHA,BST_CHECKED);
    //CheckDlgButton(hWnd,CHKBOX_SCHAR,BST_CHECKED);
    CheckDlgButton(hWnd,CHKBOX_NUM,BST_CHECKED);

    SetClassLong(hGenerate, GCL_HCURSOR, (LONG)LoadCursor (NULL, IDC_HAND));
}

void Output(HWND hWnd)
{
    //all the variables used in this function.
    char clength[5], cQuantity[5];
    GetWindowText(hLength,clength,5);
    GetWindowText(hQuantity,cQuantity,5);
    unsigned int Quantity = atoi(cQuantity);
    unsigned int length = atoi(clength);
    stringstream ss;

    bool Schar, Num, Alpha, Prefix, Suffix, Separator;
    Alpha = IsDlgButtonChecked(hWnd,CHKBOX_ALPHA);
    Num = IsDlgButtonChecked(hWnd,CHKBOX_NUM);
    Schar = IsDlgButtonChecked(hWnd,CHKBOX_SCHAR);
    Prefix = IsDlgButtonChecked(hWnd,CHKBOX_PREFIX);
    Suffix = IsDlgButtonChecked(hWnd,CHKBOX_SUFFIX);
    Separator = IsDlgButtonChecked(hWnd,CHKBOX_SEPARATOR);

    string RandomNumber;
    RANDNUM RandomNum;

    if(length > 0 && length <= 100 && flag && Quantity <= 1000)
    {
        for(unsigned int i=1; i <= Quantity; i++)
        {
        //Generating Random Numbers according to user's choice.
        if(Alpha && !Num && !Schar)
            RandomNumber = RandomNum.GenerateRandNum(0,0,1,length);

        else if(Num && !Alpha && !Schar)
            RandomNumber = RandomNum.GenerateRandNum(0,1,0,length);

        else if(Schar && !Num && !Alpha)
            RandomNumber = RandomNum.GenerateRandNum(1,0,0,length);

        else if(Alpha && Num && !Schar)
            RandomNumber = RandomNum.GenerateRandNum(0,1,1,length);

        else if(Alpha && Schar && !Num)
            RandomNumber = RandomNum.GenerateRandNum(1,0,1,length);

        else if(Num && Schar && !Alpha)
            RandomNumber = RandomNum.GenerateRandNum(1,1,0,length);

        else
            RandomNumber = RandomNum.GenerateRandNum(1,1,1,length);

        if(Prefix)
        {
            char *cptr = new char[GetWindowTextLength(hPrefix)+1];
            GetWindowText(hPrefix,cptr,GetWindowTextLength(hPrefix)+1);
            if(strlen(cptr) <= (length/2))
                RandomNumber = RandomNum.AddPrefix((char*)RandomNumber.data(),cptr);
            else
            {
                MessageBox(hWnd,"Prefix Length is high\n\nIt must be less than or equals to half of the length\n\nGenerating without Prefix",
                           "High Prefix length",MB_OK | MB_ICONERROR);
                CheckDlgButton(hWnd,CHKBOX_PREFIX,BST_UNCHECKED);
                Prefix = false;
            }

            delete cptr;
        }
        if(Suffix)
        {
            char *cptr = new char[GetWindowTextLength(hSuffix)+1];
            GetWindowText(hSuffix,cptr,GetWindowTextLength(hSuffix)+1);
            if(strlen(cptr) <= (length/2))
                RandomNumber = RandomNum.AddSuffix((char*)RandomNumber.data(),cptr);
            else
            {
                MessageBox(hWnd,"Suffix Length is high\n\nIt must be less than or equals to half of the length\n\nGenerating without Suffix",
                           "High Suffix length",MB_OK | MB_ICONERROR);
                CheckDlgButton(hWnd,CHKBOX_SUFFIX,BST_UNCHECKED);
                Suffix = false;
            }

            delete cptr;
        }
        if(Separator)
        {
            char cSeparator[2],after[3];
            GetWindowText(hSeparator,cSeparator,2);
            GetWindowText(hAfter,after,3);
                RandomNumber = RandomNum.AddSeparator((char*)RandomNumber.data(),cSeparator,atoi(after));
        }
        ss << i << " :  " << RandomNumber << "\r\n";
        }
        SetWindowText(hRandomNumber,ss.str().data());
    }

    else if(length > 100)
        MessageBox(hWnd,"Too high Length\n\nPlease try with low length","High Length",MB_ICONERROR);
    else if(!strcmp(clength,"0"))
        MessageBox(hWnd,"Length can't be zero","Zero Length",MB_ICONERROR);
    else if(!flag)
        MessageBox(hWnd,"Please select at least one check box","No check box selected",MB_ICONERROR);
    else if(Quantity > 1000)
        MessageBox(hWnd,"It can only generate 1000 Random Numbers at once","Can't Generate",MB_OK | MB_ICONERROR);
    else
        MessageBox(hWnd,"Please enter a length","No Length",MB_ICONERROR);
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hActionMenu = CreateMenu();
    HMENU hHelpMenu = CreateMenu();
    HMENU hCheckBoxMenu = CreateMenu();
    //Items of Action Menu.
    AppendMenu(hActionMenu,MF_STRING,BTN_GENERATE,"&Generate");
    AppendMenu(hActionMenu,MF_STRING,BTN_SAVE,"Sa&ve");
    AppendMenu(hActionMenu,MF_SEPARATOR,0,NULL);
    AppendMenu(hActionMenu,MF_STRING,ACTION_EXIT,"E&xit");
    //Items of Check Boxes Menu.
    AppendMenu(hCheckBoxMenu,MF_STRING,CHKBOX_ALPHA,"A&lphabets");
    AppendMenu(hCheckBoxMenu,MF_STRING,CHKBOX_NUM,"&Numbers");
    AppendMenu(hCheckBoxMenu,MF_STRING,CHKBOX_SCHAR,"Spe&cial Character");
    AppendMenu(hCheckBoxMenu,MF_SEPARATOR,0,NULL);
    AppendMenu(hCheckBoxMenu,MF_STRING,CHKBOX_PREFIX,"&Prefix");
    AppendMenu(hCheckBoxMenu,MF_STRING,CHKBOX_SUFFIX,"&Suffix");
    AppendMenu(hCheckBoxMenu,MF_SEPARATOR,0,NULL);
    AppendMenu(hCheckBoxMenu,MF_STRING,CHKBOX_SEPARATOR,"Sep&arator");
    //Items of Help Menu.
    AppendMenu(hHelpMenu,MF_STRING,HELP_HELP,"H&elp");
    AppendMenu(hHelpMenu,MF_STRING,HELP_ABOUT,"A&bout");
    //Menus
    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hActionMenu,"&Action");
    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hCheckBoxMenu,"&Check Boxes");
    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hHelpMenu,"&Help");
    //To show Menus in window
    SetMenu(hWnd,hMenu);

}

void SaveFile(HWND hWnd)
{
    OPENFILENAME ofn;   //structure that stores info about save file dialog

    char FileName[MAX_PATH] = "Untitled.txt";   //default file name

    ZeroMemory(&ofn,sizeof(OPENFILENAME));  //Assigning zero to all members of structure

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = FileName;
    ofn.nMaxFile = MAX_PATH;     //260
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0";    //Types of file in drop down list of save file dialog
    ofn.nFilterIndex = 2;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = ".txt";   //default extension

    if(GetSaveFileName(&ofn))

   /* again:
    if(GetSaveFileName(&ofn))       //Manual function to detect for existence of a file.
    {
        ifstream *file = new ifstream;
        file->open(FileName);
        if(file->is_open())
        {
            file->close();
            delete file;
            int choice = MessageBox(hWnd,"File already exist\nDo you want to overwrite it.",
                       "Already exist",MB_YESNOCANCEL | MB_ICONERROR);
            if(choice == IDYES) //checking which button is pressed
                WriteToFile(FileName);
            else if(choice == IDNO)
                goto again;
        }
        else
            WriteToFile(FileName);
    }*/
    WriteToFile(hWnd,FileName);
}

void WriteToFile(HWND hWnd, char* Path)
{
        ofstream file;
        char *str = new char[GetWindowTextLength(hRandomNumber)+1]; //Making a char array dynamically
        file.open(Path);
        GetWindowText(hRandomNumber,str,GetWindowTextLength(hRandomNumber));
        str[GetWindowTextLength(hRandomNumber)+1] = '\0';
        for(int i = 0; str[i] != '\0'; i++)
        if(str[i] == '\r')  //To not write extra new line character in file
            str[i] = ' ';   //To change all "\r\n" to " \n" in whole string
        file << str;
        file << "\n\nCreated by Random Number Generator 2.0\nDeveloper : Bhagawati Lal Ameta";
        file.close();
        MessageBox(hWnd,"File saved successfully","Saved",MB_OK | MB_ICONINFORMATION);
        delete [] str;  //To delete the character array.
}

void AddIcons(HWND hWnd)
{
    HICON hIcon = (HICON)LoadImage(NULL, "icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if(hIcon)
        SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    else
        MessageBox(hWnd,"Could not load Icon","Icon not fount",MB_OK);
}
