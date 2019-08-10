#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<commctrl.h>

#include<iostream>



#include "resource.h"

using namespace std;


LRESULT CALLBACK WinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK PromptProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK TutorialProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK DoneProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK QuitGame(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);




bool CheckInput();
bool submit;

int GenerateRandomX();
int GenerateRandomY();


int cr=1;
int difficulty=0;
static int tries=3;
int* vertex_color;
int* adjacency;
int* adjacencyb;

int choice=0;
int continues=0;
int c=0;

int *coordinatex;
int *coordinatey;
int edgesStart=0;


static bool changeColor=false;




static int vert=0, edges=0;

HWND hw;
HWND prompt;

 HWND button_hw;
 HWND menu;
 HWND hwnd;

HWND quit_button;
 HWND submit_button;

 HWND staticcontrol;

 HBITMAP hbmp;


MSG mesg={0};
int WINAPI WinMain(HINSTANCE curr, HINSTANCE prev, LPSTR arg, int showCmd)
{
WNDCLASS wc={0};




    wc.cbClsExtra=0;
    wc.cbClsExtra=0;
    wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor=LoadCursor(0, IDC_ARROW);
    wc.hIcon=(HICON)LoadIcon(0, "logo.bmp");
    wc.hInstance=curr;
    wc.lpfnWndProc=WinProc;
    wc.lpszClassName="winclass";
    wc.lpszMenuName=0;
    wc.style=CS_VREDRAW|CS_HREDRAW|CS_OWNDC;



    if(!RegisterClass(&wc))
    {
        MessageBox(0,"Fail!", "Class reg Failed", MB_OK);
        return -1;
    }







  prompt=(HWND)DialogBox(0, MAKEINTRESOURCE(IDD_MAIN_MENU),0,DialogProc);
  while(vert<4 || edges<4 || vert>50 || edges>50 )
  {
       prompt=(HWND)DialogBox(0, MAKEINTRESOURCE(IDD_MAIN_MENU),0,DialogProc);

  }




















 return 0;
}

LRESULT CALLBACK WinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{



        int colored=0;



char text[50];
            char number[10];



    bool allColorUsed=false;

bool allColored=false;


            LPDRAWITEMSTRUCT lpaint= (LPDRAWITEMSTRUCT)lp;
    HRGN ellipse;





    switch(msg)
    {
    case WM_CREATE:
        {


        edgesStart=0;

        int addx=0;
        int addy=0;


        coordinatex=new int[vert+difficulty]{0};
    coordinatey= new int[vert+difficulty]{0};
    vertex_color=new int[vert+difficulty]{0};

    //adjacent_vertex=new int [vert]{0}; optional might use it later on

    adjacency=new int[edges+difficulty]{0};

srand(time(0));
    for(int initial=0; initial<vert+difficulty; initial++)
    {

        coordinatex[initial]=GenerateRandomX()+30;
        coordinatey[initial]=GenerateRandomY()+30;
        if(initial<4)
        {
            if(initial==0)
            {
                coordinatex[initial]=rand()%500+30;
                coordinatey[initial]=30;
            }
            if(initial==1)
            {
                coordinatex[initial]=1000;
                coordinatey[initial]=rand()%500+30;
            }
            if(initial==2)
            {
                coordinatex[initial]=rand()%250+30;
                coordinatey[initial]=500;
            }
            if(initial==3)
            {
                coordinatex[initial]=1270;
                coordinatey[initial]=rand()%500+50;
            }

        }
        vertex_color[initial]=0;
    }

 /*  for(int checkco=4; checkco<(vert+difficulty)-4;checkco++)
    {
        for(int checkco2=4; checkco2<(vert+difficulty)-4; checkco2++)
        {
            if(coordinatex[checkco]>coordinatex[checkco2]-20 && coordinatex[checkco]<coordinatex[checkco2]+20 )
            {
                coordinatex[checkco]+=30;

                break;

            }
            if(coordinatey[checkco]>coordinatey[checkco2]-20 && coordinatey[checkco]<coordinatey[checkco2]+20)
            {
                coordinatey[checkco]+=30;
                checkco=3;
                break;
            }
        }
    }*/

srand(time(0));
    for(int edg=0; edg<edges+difficulty; edg++)
    {


        if(edgesStart==(edges+difficulty))
        {
            break;
        }

        adjacency[edg]=rand()%(vert+difficulty);
        edgesStart++;
        while(adjacency[edg]==edg)
        {
            adjacency[edg]=rand()%(vert+difficulty);
        }
        cout << adjacency[edg] << endl;

    }

            for(int button=0; button<vert+difficulty; button++)
        {
            button_hw=CreateWindow("Button", "", WS_CHILD|WS_VISIBLE|BS_OWNERDRAW|WS_CLIPCHILDREN|WS_TABSTOP, coordinatex[button]-21, coordinatey[button]-21,30 ,30, hw,(HMENU)button,0,0);
            InvalidateRect(hw, 0,FALSE);
        }

   submit_button=CreateWindow("button", "Submit!", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 1000,600, 100,50, hw, (HMENU)9009, 0,0);

    EnableWindow(submit_button, FALSE);

}

        SetFocus(button_hw);

        break;

    case WM_CLOSE:
        delete []vertex_color;
        delete [] adjacency;
        delete [] coordinatex;
        delete [] coordinatey;
        DestroyWindow(hw);
         DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAIN_MENU), 0, DialogProc);
        break;

    case WM_NEXTDLGCTL:

        break;

    case DM_SETDEFID:

        break;

    case WM_COMMAND:
        {
            int default_color=1;
            switch(wp)
            {

            case 9009:
                submit=CheckInput();
                if(submit==false)
                {
                    tries-=1;
                    strcpy(text, "Adjacency Detected! You only have: ");
                    itoa(tries, number, 10);
                    strcat(text, number);
                    strcat(text, " try/tries left");
                    MessageBox(hw, text, "Note!", MB_OK);
                    for(int reset=0; reset<vert+difficulty; reset++)
                    {
                        vertex_color[reset]=0;
                        InvalidateRect(hw, 0, TRUE);
                        cr=1;

                        EnableWindow(submit_button, FALSE);
                    }
                    if(tries==0)
                    {

                        MessageBox(hw, "Out of tries.", "Note!", 0);
                        tries=3;
                        for(int lose=0; lose<vert+difficulty; lose++)
                        {
                           vertex_color[lose]=default_color;
                           default_color++;
                               InvalidateRect(hw,0,TRUE);

                           if(default_color==4)
                           {
                               default_color=1;
                           }

                        }
                        DestroyWindow(hw);
                        DialogBox(0,MAKEINTRESOURCE(IDD_MAIN_MENU), 0 , DialogProc);
                    }

                }

                if(submit==true)
                {
                    if(continues<2)
                    {
                    DialogBox(0, MAKEINTRESOURCE(IDD_DONE),0, DoneProc);
                    break;
                    }
                    else
                    {
                        DialogBox(0, MAKEINTRESOURCE(IDD_END),0,DoneProc);
                        continues=0;
                        break;
                    }
                }

                break;
            }

        int commId=LOWORD((wp));
        char number[50];

for(int click=0; click<vert; click++)
{


          if(wp==click) // commid is what I clicked
           {
               itoa(wp, number, 10);
               MessageBox(hw, number, "", 0);

               break;


           }






}
break;
}

break;



    case WM_DRAWITEM:
        {

         HBRUSH draw;
        HPEN button_pen;





           for(int color=0; color<vert+difficulty; color++)
           {


               if(lpaint->CtlID==(UINT)color)
               {

                if(vertex_color[color]==0)
                {

                draw=CreateSolidBrush(RGB(255,255,255));
                button_pen=CreatePen(PS_SOLID, 5, RGB(0,0,0));
                ellipse = CreateEllipticRgn(0,0,30,30);
                SetWindowRgn(lpaint->hwndItem, ellipse, TRUE);
                SelectObject(lpaint->hDC, draw);
                SelectObject(lpaint->hDC, button_pen);

                Ellipse(lpaint->hDC, 0,0,30,30);

                }

                if(vertex_color[color]==1)
                {
                draw=CreateSolidBrush(RGB(0,255,255)); //blue
                     button_pen=CreatePen(PS_SOLID, 5, RGB(0,0,0));
                ellipse = CreateEllipticRgn(0,0,30,30);
                SetWindowRgn(lpaint->hwndItem, ellipse, TRUE);
                SelectObject(lpaint->hDC, draw);
                SelectObject(lpaint->hDC, button_pen);
                Ellipse(lpaint->hDC, 0,0,30,30);

                }

                if(vertex_color[color]==2)
                {
                draw=CreateSolidBrush(RGB(255,0,255)); //purple
                button_pen=CreatePen(PS_SOLID, 5, RGB(0,0,0));
                ellipse = CreateEllipticRgn(0,0,30,30);
                SetWindowRgn(lpaint->hwndItem, ellipse, TRUE);
                SelectObject(lpaint->hDC, draw);
                SelectObject(lpaint->hDC, button_pen);
                Ellipse(lpaint->hDC, 0,0,30,30);
                }

                if(vertex_color[color]==3)
                {
                draw=CreateSolidBrush(RGB(255,0,0)); //red
                button_pen=CreatePen(PS_SOLID, 5, RGB(0,0,0));
                ellipse = CreateEllipticRgn(0,0,30,30);
                SetWindowRgn(lpaint->hwndItem, ellipse, TRUE);
                SelectObject(lpaint->hDC, draw);
                SelectObject(lpaint->hDC, button_pen);
                Ellipse(lpaint->hDC, 0,0,30,30);
                }

                 if(vertex_color[color]==4)
                {
                draw=CreateSolidBrush(RGB(255,255,0));  //yellow
                button_pen=CreatePen(PS_SOLID, 5, RGB(0,0,0));
                ellipse = CreateEllipticRgn(0,0,30,30);
                SetWindowRgn(lpaint->hwndItem, ellipse, TRUE);
                SelectObject(lpaint->hDC, draw);
                SelectObject(lpaint->hDC, button_pen);
                Ellipse(lpaint->hDC, 0,0,30,30);
                }
                if(lpaint->itemState & ODS_FOCUS)
                {
                button_pen=CreatePen(PS_SOLID, 10, RGB(0,255,0));
                ellipse = CreateEllipticRgn(0,0,30,30);
                SetWindowRgn(lpaint->hwndItem, ellipse, TRUE);
                SelectObject(lpaint->hDC, button_pen);
                Ellipse(lpaint->hDC, 0,0,30,30);
                }


                }



           }

            DeleteObject(draw);
        DeleteObject(button_pen);
        if(changeColor==true)
    {
        cr++;
        if(cr==5)
        {
            cr=1;
        }
InvalidateRect(hw, 0,FALSE);
        changeColor=false;
    }
                return 0;

 }




    case WM_SIZE:
        InvalidateRect(hw, 0, FALSE);
        UpdateWindow(hw);
        return 0;





    case WM_PAINT:
        {


        HDC hdc;


        int purple=0, red=0, blue=0, yellow=0;
        PAINTSTRUCT ps;
        HBRUSH paintb;
       int vertexDrawn=0;

        allColored=false;
        allColorUsed=true;
        char szBuffer[50]={' '};


        int edgesCount=0;

        hdc=BeginPaint(hw, &ps);
        GetDC(hw);
        int  curve=20;
         for(int paint=0; paint<(edges+difficulty); paint++)
         {
             if(edgesCount==(edges+difficulty))
             {
                 break;
             }

             if(vertexDrawn==(vert+difficulty))
             {
                 vertexDrawn=0;

             }



                POINT points[4]={{coordinatex[vertexDrawn], coordinatey[vertexDrawn]}, {coordinatex[vertexDrawn]+30,coordinatey[vertexDrawn]+30}, {coordinatex[vertexDrawn]+50,coordinatey[vertexDrawn]+50}, {coordinatex[adjacency[paint]], coordinatey[adjacency[paint]]}};
                PolyBezier(hdc, points, 4);



                edgesCount++;
            vertexDrawn++;


         }









            if(cr==1)
            {
                strcpy(szBuffer, "Current Color: Blue");

                paintb=CreateSolidBrush(RGB(0,255,255));
            }
            if(cr==2)
            {
                strcpy(szBuffer, "Current Color: Purple");
                paintb=CreateSolidBrush(RGB(255,0,255));
            }
            if(cr==3)
            {
                strcpy(szBuffer, "Current Color: Red");
                paintb=CreateSolidBrush(RGB(255,0,0));
            }
            if(cr==4)
            {
                strcpy(szBuffer, "Current Color: Yellow");
                paintb=CreateSolidBrush(RGB(255,255,0));
            }
            SelectObject(hdc, paintb);
            TextOut(hdc, 200,650, szBuffer, 25);
            itoa(tries, number, 10);
            strcpy(text, "Try/Tries left: ");
            strcat(text, number);
            TextOut(hdc, 500,650, text, 20);
            Ellipse(hdc,10,600,180,730);




        for(int colorcheck=0; colorcheck<vert+difficulty; colorcheck++)
        {
            if(vertex_color[colorcheck]>0)
            {
                colored++;
            }
            if(colored==vert+difficulty)
            {
                allColored=true;
                break;
            }
        }

        for(int check=0; check<vert+difficulty; check++)
        {
            if(vertex_color[check]==1)
            {
                blue+=1;
            }
            else if(vertex_color[check]==2)
            {
                purple+=1;
            }
            else if(vertex_color[check]==3)
            {
                red+=1;
            }
            else if(vertex_color[check]==4)
            {
                yellow+=1;
            }

            if(red >=1 && purple>=1 && yellow>=1 && red>=1)
            {
                allColorUsed=true;
                break;
            }
        }

        if(allColored && allColorUsed)
        {
            EnableWindow(submit_button, TRUE);

        }
        EndPaint(hw, &ps);
        DeleteObject(paintb);
        ReleaseDC(hw, hdc);
        break;
        }

        default: return DefWindowProc(hw, msg, wp,lp);
    }
    return DefWindowProc(hw, msg, wp,lp);
}

BOOL CALLBACK TutorialProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
        case WM_INITDIALOG:
        return TRUE;

        case WM_COMMAND:
            switch(wp)
            {
            case IDOK:
                EndDialog(hwnd, NULL);
                DialogBox(0,MAKEINTRESOURCE(IDD_MAIN_MENU), 0, DialogProc);
                break;
            }

        default: return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) //main menu
{
HDC hdc;
HFONT hfont;

    switch(msg)
    {


case WM_CTLCOLORDLG:
    return (BOOL)CreateSolidBrush(RGB(0,120,120));


    case WM_SETFONT:



    case WM_INITDIALOG:
        staticcontrol=CreateWindow("static", "The Four Color Conjecture Game", WS_CHILD|WS_VISIBLE|SS_CENTER,150,30, 300,100,hwnd,(HMENU)-1,0,0);
        hfont=CreateFont(40,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE, ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Elephant");
        SendMessage(staticcontrol, WM_SETFONT, (WPARAM)hfont,TRUE);
        return TRUE;

    case WM_CTLCOLORSTATIC:
        SetBkMode((HDC)wp, TRANSPARENT);

        return (BOOL)CreateSolidBrush(RGB(0,120,120));

    case WM_COMMAND:
        switch(wp)
        {

        case IDD_PLAY:
            EndDialog(hwnd, NULL);
            DialogBox(0, MAKEINTRESOURCE(IDD_PROMPT), 0, PromptProc);
            break;

        case IDD_TUT:
            EndDialog(hwnd,NULL);
            DialogBox(0, MAKEINTRESOURCE(IDD_INSTRUCT),0,TutorialProc);
            break;

        case IDOK:
            EndDialog(hwnd, NULL);
            break;

        case IDD_EXIT:
            EndDialog(hwnd, NULL);
            difficulty=0;
            exit(0);
            break;


        }
        break;

        case WM_CLOSE:
            EndDialog(hwnd, NULL);
            exit(0);
            difficulty=0;
            break;

        case WM_PAINT:
            {

            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);






            EndPaint(hwnd, &ps);

}
break;



    default: return FALSE;
    }
    return TRUE;

}

BOOL CALLBACK PromptProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) //input user
{
    HDC handledc;
    HFONT font;
    HFONT fontc;
    HWND statica;
    HWND staticb;
    HWND staticc;
    switch(msg)
    {

case WM_CTLCOLORSTATIC:
    SetBkMode((HDC)wp, TRANSPARENT);
    return(BOOL)GetStockObject(NULL_BRUSH);

    case WM_CTLCOLORDLG:
        return (BOOL)CreateSolidBrush(RGB(66,164,244));

        case WM_INITDIALOG:
            statica=CreateWindow("static", "Input number of Vertices:", WS_VISIBLE|WS_CHILD,15,35,200,50,hwnd, NULL, 0,0);
            staticb=CreateWindow("static", "Input number of Edges:", WS_VISIBLE|WS_CHILD,15,250,200,50,hwnd, NULL, 0,0);
            staticc=CreateWindow("static", "Note: Maximum of 50 Vertices and 50 Edges are allowed and Minimum of 4 Vertices and 4 Edges", WS_VISIBLE|WS_CHILD|WS_BORDER,20,100,250,100,hwnd, NULL, 0,0);
            font=CreateFont(20,0,0,0,400,FALSE,TRUE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Brittanic");
            fontc=CreateFont(25,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Brittanic");
            SendMessage(statica, WM_SETFONT, (WPARAM)font, TRUE);
            SendMessage(staticb, WM_SETFONT, (WPARAM)font, TRUE);
            SendMessage(staticc, WM_SETFONT, (WPARAM)fontc, TRUE);
            return TRUE;

        case WM_CLOSE:
            EndDialog(hwnd, NULL);
            DialogBox(0, MAKEINTRESOURCE(IDD_MAIN_MENU), 0, DialogProc);
            difficulty=0;
            break;

        case WM_COMMAND:
            switch(wp)
            {
        case RETURN:
            EndDialog(hwnd, NULL);
            DialogBox(0, MAKEINTRESOURCE(IDD_MAIN_MENU), 0, DialogProc);
            difficulty=0;
            break;

            case GENERATE_GRAPH:
            difficulty=0;
            vert=(int)GetDlgItemInt(hwnd, IDD_INPUT_VERTEX, FALSE, FALSE);
            edges=(int)GetDlgItemInt(hwnd, IDD_INPUT_EDGES, FALSE, FALSE);
            while(vert<4 || edges<4|| vert>50 ||edges>50)
  {
      EndDialog(hwnd, GENERATE_GRAPH);
       DialogBox(0, MAKEINTRESOURCE(IDD_PROMPT),0,PromptProc);

  }
            EndDialog(hwnd, GENERATE_GRAPH);

 hw=CreateWindow("winclass", " Four Color Conjecture Game", WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CAPTION|WS_MINIMIZEBOX, 100, 100, 800  ,600, 0,0,0,0);
    ShowWindow(hw, SW_MAXIMIZE);

    while(GetMessage(&mesg,0,0,0))
    {




IsDialogMessage(hw,&mesg);
    TranslateMessage(&mesg);
    DispatchMessage(&mesg);
    if(GetAsyncKeyState(VK_END))
        {


            DialogBox(0,MAKEINTRESOURCE(IDD_QUIT_DIALOG),0,QuitGame);
        }
        if(GetAsyncKeyState(VK_SPACE))
        {
           if(GetDlgCtrlID(GetFocus())==9009)
           {
               continue;
           }
            vertex_color[GetDlgCtrlID(GetFocus())]=cr;
            changeColor=true;
        }



    }
            break;


                }

            break;

        default: return FALSE;
    }
    return TRUE;
    }

BOOL CALLBACK DoneProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
            case YEET:
                    EndDialog(hwnd, IDOK);
                    DestroyWindow(hw);
                    tries=3;
                    continues+=1;
                    difficulty+=5;
                    hw=CreateWindow("winclass", " Four Color Conjecture Game", WS_VISIBLE|WS_CAPTION|WS_MINIMIZEBOX, 100, 100, 800  ,600, 0,0,0,0);
                    ShowWindow(hw, SW_MAXIMIZE);

                    while(GetMessage((LPMSG)&msg,0,0,0))
    {


IsDialogMessage(hw,(LPMSG)&msg);
    TranslateMessage((LPMSG)&msg);
    DispatchMessage((LPMSG)&msg);



        if(GetAsyncKeyState(VK_SPACE))
        {
            if(GetDlgCtrlID(GetFocus())==9009)
           {
               continue;
           }

                vertex_color[GetDlgCtrlID(GetFocus())]=cr;
            changeColor=true;


        }
        if(GetAsyncKeyState(VK_END))
        {

            DialogBox(0,MAKEINTRESOURCE(IDD_QUIT_DIALOG),0,QuitGame);
        }
    }
    break;


                case NOOT:
                    EndDialog(hwnd, NOOT);
                    difficulty=0;
                    DestroyWindow(hw);
                    continues=0;
                    DialogBox(0,MAKEINTRESOURCE(IDD_MAIN_MENU), 0, DialogProc);
                break;

                case IDNO:
                    EndDialog(hwnd, NOOT);
                    difficulty=0;
                    DestroyWindow(hw);
                    continues=0;
                    DialogBox(0,MAKEINTRESOURCE(IDD_MAIN_MENU), 0, DialogProc);
        }
        default: return FALSE;
    }
    return TRUE;
}
BOOL CALLBACK QuitGame(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch(wp)
        {
        case IDOK:
            EndDialog(hwnd,NULL);
            DestroyWindow(hw);
            difficulty=0;
            continues=0;
            DialogBox(0,MAKEINTRESOURCE(IDD_MAIN_MENU), 0,DialogProc);
            break;

        case IDNO:
            EndDialog(hwnd,NULL);
            break;
        }
        break;

    default: return FALSE;
    }
    return TRUE;
}

int GenerateRandomX()
{
    return rand()%1270+30;
}

                //addx=1300;                addy=500;
int GenerateRandomY()
{
    return rand()%500+30;
}

bool CheckInput()
{
    int checking=0;
    for(int checkAdjacency=0; checkAdjacency<edges+difficulty; checkAdjacency++)
    {
        if(checking==(edges+difficulty)-1)
        {
            break;
        }
        if(vertex_color[checkAdjacency]== vertex_color[adjacency[checkAdjacency]])
        {
            return false;
        }
        if(checkAdjacency==(vert+difficulty)-1)
        {
            checkAdjacency=0;
        }
        checking++;
    }
    return true;
}
