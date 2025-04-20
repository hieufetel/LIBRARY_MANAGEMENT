#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstring>
#include <commctrl.h>
#include "Source1.cpp"
#pragma comment(lib, "comctl32.lib")
#pragma warning (disable: 28251)
using namespace std;

// Globals
HINSTANCE hInst;
HWND hwndLogin, hwndRegister, hwndMainMenu, hwndBookInfo;
HWND hwndReaderInfo, hwndManagerInfo;

// Controls
HWND txtEmailLogin, txtPassLogin;
HWND txtNameReg, txtSexReg, txtEmailReg, txtPassReg;

// Add book
HWND hwndAddBook;
HWND txtBookID, txtBookName, txtAuthor, txtDate, txtStatus;

// Add book
HWND hwndAddReader;
HWND txtReaderID, txtReaderName, txtKhoa;

// Edit book
HWND hwndEditBook;
HWND txtEditBookID, txtEditBookName, txtEditAuthor, txtEditDate, txtEditStatus;

//delete
HWND hwndDeleteBook, txtDeleteBookID;

// Edit reader
HWND hwndEditReader;
HWND txtEditReaderID, txtEditReaderName, txtEditKhoa;

//sắp xếp sách
HWND hwndSortBook;
HWND cmbSortCriteria;
HWND listSortedBooks;

// book list 
HWND hwndBookList;
HWND listAllBooks;

// reader list
HWND hwndReaderList;
HWND listAllReaders;

//muon sach 
HWND hwndBorrowWindow;
HWND txtMSDD_Borrow, txtBookID_Borrow, txtDate_Borrow;
HWND btnCheckReader, lblReaderInfo;
HWND btnCheckBook, lblBookInfo;

//tra sach
HWND hwndReturnBook;
HWND txtMSDD_Return, txtReturnDate;
HWND btnCheckReturn;
HWND lblReturnInfo;

//danh sach muon sach
HWND hwndBorrowedList;
HWND listBorrowedBooks;

//danh sach tra sach
HWND hwndReturnedList;
HWND listReturnedBooks;

//timkiemsachmuon 
HWND cbSearchType, txtSearchInput, txtSearchResult;

//timkiemsachmuon 
HWND cbDueSearchType, txtDueSearchInput, txtDueSearchResult;

//show list manager
HWND hwndListManager;
HWND listViewManager;

OPERATE libOp;

// ====== Forward Declarations ======
LRESULT CALLBACK LoginProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RegisterProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainMenuProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BookInfoProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ReaderInfoProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ManagerInfoProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AddBookProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AddReaderProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK EditBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditReaderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DeleteBookProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SortBookProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BookListProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ReaderListProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BorrowBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ReturnBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK BorrowedListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ReturnedListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK SearchBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK SearchDueBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ListManagerProc(HWND, UINT, WPARAM, LPARAM);

void ShowLogin();
void ShowRegister();
void ShowMainMenu();
void ShowBookInfo();
void ShowReaderInfo();
void ShowManagerInfo();
void ShowAddBookWindow();
void ShowAddReaderWindow();
void ShowEditBookWindow();
void ShowDeleteBookWindow();
void ShowEditReaderWindow();
void ShowSortBookWindow();
void ShowBookListWindow();
void ShowReaderListWindow();
void ShowBorrowBookWindow();
void ShowReturnBookWindow();
void ShowBorrowedListWindow();
void ShowReturnedListWindow();
void ShowSearchBorrowedBookWindow();
void ShowSearchDueBookWindow();
void ShowListManagerWindow();

void DisplaySortedBooks(HWND hwnd);
void DisplayAllBooks(HWND hwnd);
void DisplayAllReaders(HWND hwnd);
void CheckBook(HWND hwnd);
void CheckReader(HWND hwnd);
void CreateBorrowBookControls(HWND hwnd);
void HandleBorrowing(HWND hwnd);
void CreateReturnBookControls(HWND hwnd);
void CheckReturnMSDD(HWND hwnd);
void HandleReturnBook(HWND hwnd);
void DisplayBorrowedList(HWND hwnd);
void DisplayReturnedList(HWND hwnd);
void DisplayManagerList(HWND hwnd);

string GenerateMCB();
bool CheckMail(const string& email);
bool CheckPassword(const string& pass);
wstring convertToWString(const string& str) {
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wstring wstr(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);
    wstr.pop_back(); // Xoá null terminator
    return wstr;
}
wstring stringToWstring(const string& s) {
    return wstring(s.begin(), s.end());
}
vector<string> TimKiemMuonSachTheoTieuChi(int tieuChi, const string& keyword) {
    vector<string> ketqua;
    libOp.docThongTinMuonSach();

    for (auto& m : libOp.danhsachMuonSach) {
        bool match = false;
        switch (tieuChi) {
        case 0: match = to_string(m.msdd) == keyword; break;
        case 1: match = m.idSach == keyword; break;
        case 2: match = m.tenSach == keyword; break;
        case 3: match = m.tacGia == keyword; break;
        case 4: match = m.ngayMuon == keyword; break;
        }

        if (match) {
            string line = "MSDD: " + to_string(m.msdd) +
                "|\nBook Name: " + m.tenSach +
                "|\nAuthor: " + m.tacGia +
                "|\nBorrowed Date: " + m.ngayMuon;
            ketqua.push_back(line);
        }
    }

    return ketqua;
}
vector<string> TimKiemTraSachTheoTieuChi(int tieuChi, const string& keyword) {
    vector<string> ketqua;
    libOp.docThongTinTraSach();

    for (auto& m : libOp.danhsachTraSach) {
        bool match = false;
        switch (tieuChi) {
        case 0: match = to_string(m.msdd) == keyword; break;
        case 1: match = m.idSach == keyword; break;
        case 2: match = m.tenSach == keyword; break;
        case 3: match = m.tacGia == keyword; break;
        case 4: match = m.ngayMuon == keyword; break;
        case 5: match = m.ngayTra == keyword; break;
        }

        if (match) {
            string line = "MSDD: " + to_string(m.msdd) +
                "|\nBook Name: " + m.tenSach +
                "|\nAuthor: " + m.tacGia +
                "|\nBorrowed Date: " + m.ngayMuon +
                "|\nDue Date: " + m.ngayTra;
            ketqua.push_back(line);
        }
    }

    return ketqua;
}

// ====== WinMain ======
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    hInst = hInstance;

    WNDCLASS wc = {};
    wc.hInstance = hInst;
    wc.lpfnWndProc = LoginProc;
    wc.lpszClassName = L"LoginWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = RegisterProc;
    wc.lpszClassName = L"RegisterWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = MainMenuProc;
    wc.lpszClassName = L"MainMenuWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = BookInfoProc;
    wc.lpszClassName = L"BookInfoWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = ReaderInfoProc;
    wc.lpszClassName = L"ReaderInfoWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = ManagerInfoProc;
    wc.lpszClassName = L"ManagerInfoWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = AddBookProc;
    wc.lpszClassName = L"AddBookWindow";
    RegisterClass(&wc);

    // Đăng ký lớp AddBookWindow
    WNDCLASSW addBookWnd = {};
    addBookWnd.lpszClassName = L"AddBookWindow";
    addBookWnd.hInstance = hInst;
    addBookWnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    addBookWnd.lpfnWndProc = AddBookProc;
    addBookWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassW(&addBookWnd);

    wc.lpfnWndProc = AddReaderProc;
    wc.lpszClassName = L"AddReaderWindow";
    RegisterClass(&wc);

    // Đăng ký lớp AddReaderWindow
    WNDCLASSW addReaderWnd = {};
    addReaderWnd.lpszClassName = L"AddReaderWindow";
    addReaderWnd.hInstance = hInst;
    addReaderWnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    addReaderWnd.lpfnWndProc = AddReaderProc;
    addReaderWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassW(&addReaderWnd);

    wc.lpfnWndProc = EditBookProc;
    wc.lpszClassName = L"EditBookWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = EditReaderProc;
    wc.lpszClassName = L"EditReaderWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = DeleteBookProc;
    wc.lpszClassName = L"DeleteBookWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = SortBookProc;
    wc.lpszClassName = L"SortBookWindow";
    RegisterClass(&wc);

    WNDCLASS wcBookList = { 0 };
    wcBookList.lpfnWndProc = BookListProc;
    wcBookList.hInstance = hInst;
    wcBookList.lpszClassName = L"BookListWindow";
    RegisterClass(&wcBookList);

    WNDCLASS wcReaderList = { 0 };
    wcReaderList.lpfnWndProc = ReaderListProc;
    wcReaderList.hInstance = hInst;
    wcReaderList.lpszClassName = L"ReaderListWindow";
    RegisterClass(&wcReaderList);

    wc.lpfnWndProc = BorrowBookProc;
    wc.lpszClassName = L"BorrowBookWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = ReturnBookProc;
    wc.lpszClassName = L"ReturnBookWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = BorrowedListProc;
    wc.lpszClassName = L"BorrowedListWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = ReturnedListProc;
    wc.lpszClassName = L"ReturnedListWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = SearchBookProc;
    wc.lpszClassName = L"SearchBorrowedWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = SearchDueBookProc;
    wc.lpszClassName = L"SearchDueWindow";
    RegisterClass(&wc);

    wc.lpfnWndProc = ListManagerProc;
    wc.lpszClassName = L"ListManagerWindow";
    RegisterClass(&wc);

    InitCommonControls();
    ShowLogin();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// ====== Show Windows ======
void ShowLogin() {
    hwndLogin = CreateWindowEx(0, L"LoginWindow", L"Login",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 250,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndLogin, SW_SHOW);
}

void ShowRegister() {
    hwndRegister = CreateWindowEx(0, L"RegisterWindow", L"Register",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndRegister, SW_SHOW);
}

void ShowMainMenu() {
    hwndMainMenu = CreateWindowEx(0, L"MainMenuWindow", L"Library Manager",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndMainMenu, SW_SHOW);
}

void ShowBookInfo() {
    hwndBookInfo = CreateWindowEx(0, L"BookInfoWindow", L"Book Information",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndBookInfo, SW_SHOW);
}

void ShowReaderInfo() {
    hwndReaderInfo = CreateWindowEx(0, L"ReaderInfoWindow", L"Reader Information",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndReaderInfo, SW_SHOW);
}

void ShowManagerInfo() {
    hwndManagerInfo = CreateWindowEx(0, L"ManagerInfoWindow", L"Manager Information",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndManagerInfo, SW_SHOW);
}

void ShowAddBookWindow() {
    hwndAddBook = CreateWindowEx(0, L"AddBookWindow", L"Thêm sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 350,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndAddBook, SW_SHOW);
    UpdateWindow(hwndAddBook);
}

void ShowAddReaderWindow() {
    hwndAddReader = CreateWindowEx(0, L"AddReaderWindow", L"Thêm độc giả",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 350,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndAddReader, SW_SHOW);
    UpdateWindow(hwndAddReader);
}

void ShowEditBookWindow() {
    hwndEditBook = CreateWindowEx(0, L"EditBookWindow", L"Sửa thông tin sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 350,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndEditBook, SW_SHOW);
    UpdateWindow(hwndEditBook);
}

void ShowDeleteBookWindow() {
    hwndDeleteBook = CreateWindowEx(0, L"DeleteBookWindow", L"Xóa sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 350, 200,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndDeleteBook, SW_SHOW);
    UpdateWindow(hwndDeleteBook);
}

void ShowEditReaderWindow() {
    hwndEditReader = CreateWindowEx(0, L"EditReaderWindow", L"Edit Reader Information",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 350,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndEditReader, SW_SHOW);
    UpdateWindow(hwndEditReader);
}

void ShowSortBookWindow() {
    hwndSortBook = CreateWindowEx(0, L"SortBookWindow", L"Sắp xếp sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 650, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndSortBook, SW_SHOW);
    UpdateWindow(hwndSortBook);
}

void ShowBookListWindow() {
    hwndBookList = CreateWindowEx(0, L"BookListWindow", L"Danh sách sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 650, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndBookList, SW_SHOW);
    UpdateWindow(hwndBookList);
}

void ShowReaderListWindow() {
    hwndReaderList = CreateWindowEx(0, L"ReaderListWindow", L"Danh sách độc giả",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 650, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndReaderList, SW_SHOW);
    UpdateWindow(hwndReaderList);
}

void ShowBorrowBookWindow() {
    hwndBorrowWindow = CreateWindowEx(0, L"BorrowBookWindow", L"Mượn sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 280,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndBorrowWindow, SW_SHOW);
    UpdateWindow(hwndBorrowWindow);
}

void ShowReturnBookWindow() {
    hwndReturnBook = CreateWindowEx(0, L"ReturnBookWindow", L"Trả sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 450, 350,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndReturnBook, SW_SHOW);
    UpdateWindow(hwndReturnBook);
}

void ShowBorrowedListWindow() {
    hwndBorrowedList = CreateWindowEx(0, L"BorrowedListWindow", L"Danh sách mượn sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndBorrowedList, SW_SHOW);
    UpdateWindow(hwndBorrowedList);
}

void ShowReturnedListWindow() {
    hwndReturnedList = CreateWindowEx(0, L"ReturnedListWindow", L"Danh sách trả sách",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndReturnedList, SW_SHOW);
    UpdateWindow(hwndReturnedList);
}

void ShowSearchBorrowedBookWindow() {
    WNDCLASS wc = {};
    wc.hInstance = hInst;
    wc.lpfnWndProc = SearchBookProc;
    wc.lpszClassName = L"SearchBorrowedWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    CreateWindowW(L"SearchBorrowedWindow", L"Tìm kiếm sách mượn",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 150, 500, 400, NULL, NULL, hInst, NULL);
}

void ShowSearchDueBookWindow() {
    WNDCLASS wc = {};
    wc.hInstance = hInst;
    wc.lpfnWndProc = SearchDueBookProc;
    wc.lpszClassName = L"SearchDueWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    CreateWindowW(L"SearchDueWindow", L"Search Returned Book",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        400, 150, 500, 400, NULL, NULL, hInst, NULL);
}

void ShowListManagerWindow() {
    hwndListManager = CreateWindowEx(0, L"ListManagerWindow", L"Danh sách quản lý",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 700, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwndListManager, SW_SHOW);
    UpdateWindow(hwndListManager);
}

// ===== Display =====
void DisplaySortedBooks(HWND hwnd) {
    ListView_DeleteAllItems(listSortedBooks);
    int index = 0;
    for (auto sach : danhsachSach) {
        wstring id = stringToWstring(sach->getBookID());
        wstring name = stringToWstring(sach->getBookName());
        wstring author = stringToWstring(sach->getAuthor());
        wstring date = stringToWstring(sach->getInDay());
        wstring status = stringToWstring(sach->getBookMode());

        LVITEM lvItem = { 0 };
        lvItem.mask = LVIF_TEXT;
        lvItem.iItem = index;
        lvItem.pszText = (LPWSTR)id.c_str();
        ListView_InsertItem(listSortedBooks, &lvItem);

        ListView_SetItemText(listSortedBooks, index, 1, (LPWSTR)name.c_str());
        ListView_SetItemText(listSortedBooks, index, 2, (LPWSTR)author.c_str());
        ListView_SetItemText(listSortedBooks, index, 3, (LPWSTR)date.c_str());
        ListView_SetItemText(listSortedBooks, index, 4, (LPWSTR)status.c_str());

        index++;
    }
}

void DisplayAllBooks(HWND hwnd) {
    ListView_DeleteAllItems(listAllBooks);
    int index = 0;
    for (auto sach : danhsachSach) {
        wstring id = stringToWstring(sach->getBookID());
        wstring name = stringToWstring(sach->getBookName());
        wstring author = stringToWstring(sach->getAuthor());
        wstring date = stringToWstring(sach->getInDay());
        wstring status = stringToWstring(sach->getBookMode());

        LVITEM lvItem = { 0 };
        lvItem.mask = LVIF_TEXT;
        lvItem.iItem = index;
        lvItem.pszText = (LPWSTR)id.c_str();
        ListView_InsertItem(listAllBooks, &lvItem);

        ListView_SetItemText(listAllBooks, index, 1, (LPWSTR)name.c_str());
        ListView_SetItemText(listAllBooks, index, 2, (LPWSTR)author.c_str());
        ListView_SetItemText(listAllBooks, index, 3, (LPWSTR)date.c_str());
        ListView_SetItemText(listAllBooks, index, 4, (LPWSTR)status.c_str());

        index++;
    }
}

void DisplayAllReaders(HWND hwnd) {
    ListView_DeleteAllItems(listAllReaders);
    int index = 0;
    for (auto reader : danhsachDocGia) {
        wstring msdd = to_wstring(reader->getMSDD());
        wstring hoten = stringToWstring(reader->getHoTen());
        wstring khoa = stringToWstring(reader->getKhoa());

        LVITEM lvItem = { 0 };
        lvItem.mask = LVIF_TEXT;
        lvItem.iItem = index;
        lvItem.pszText = (LPWSTR)msdd.c_str();
        ListView_InsertItem(listAllReaders, &lvItem);

        ListView_SetItemText(listAllReaders, index, 1, (LPWSTR)hoten.c_str());
        ListView_SetItemText(listAllReaders, index, 2, (LPWSTR)khoa.c_str());

        index++;
    }
}

void DisplayBorrowedList(HWND hwnd) {
    libOp.docThongTinMuonSach();
    if (libOp.danhsachMuonSach.empty()) {
        MessageBoxW(hwnd, L"Hiện chưa có sách nào được mượn!", L"Thông báo", MB_OK | MB_ICONINFORMATION);
        return;
    }
    listBorrowedBooks = CreateWindowW(WC_LISTVIEW, L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
        10, 10, 760, 320, hwnd, NULL, hInst, NULL);

    // Add columns
    LVCOLUMN col;
    col.mask = LVCF_TEXT | LVCF_WIDTH;

    wstring headers[] = { L"MSDD", L"Họ tên", L"ID Sách", L"Tên sách", L"Tác giả", L"Ngày mượn", L"Trạng thái" };
    int widths[] = { 80, 120, 80, 120, 120, 100, 100 };

    for (int i = 0; i < 7; ++i) {
        col.cx = widths[i];
        col.pszText = (LPWSTR)headers[i].c_str();
        ListView_InsertColumn(listBorrowedBooks, i, &col);
    }

    // Add data
    int index = 0;
    for (auto& b : libOp.danhsachMuonSach) {
        LVITEM item = { 0 };
        item.mask = LVIF_TEXT;
        item.iItem = index;

        wstring msdd = to_wstring(b.msdd);
        wstring hoten = convertToWString(b.hoTen);
        wstring bookID = convertToWString(b.idSach);
        wstring ten = convertToWString(b.tenSach);
        wstring tg = convertToWString(b.tacGia);
        wstring date = convertToWString(b.ngayMuon);
        wstring stt = convertToWString(b.trangThaiMuon);

        item.pszText = (LPWSTR)msdd.c_str();
        ListView_InsertItem(listBorrowedBooks, &item);

        ListView_SetItemText(listBorrowedBooks, index, 1, (LPWSTR)hoten.c_str());
        ListView_SetItemText(listBorrowedBooks, index, 2, (LPWSTR)bookID.c_str());
        ListView_SetItemText(listBorrowedBooks, index, 3, (LPWSTR)ten.c_str());
        ListView_SetItemText(listBorrowedBooks, index, 4, (LPWSTR)tg.c_str());
        ListView_SetItemText(listBorrowedBooks, index, 5, (LPWSTR)date.c_str());
        ListView_SetItemText(listBorrowedBooks, index, 6, (LPWSTR)stt.c_str());

        index++;
    }
}

void DisplayReturnedList(HWND hwnd) {
    libOp.docThongTinTraSach(); // đọc từ file TraSach.txt
    listReturnedBooks = CreateWindowW(WC_LISTVIEW, L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
        10, 10, 860, 320, hwnd, NULL, hInst, NULL);

    // Add columns
    LVCOLUMN col;
    col.mask = LVCF_TEXT | LVCF_WIDTH;

    wstring headers[] = {
        L"MSDD", L"Họ tên", L"ID Sách", L"Tên sách", L"Tác giả",
        L"Ngày mượn", L"Trạng thái mượn", L"Ngày trả", L"Trạng thái trả"
    };
    int widths[] = { 60, 100, 80, 120, 100, 100, 100, 100, 100 };

    for (int i = 0; i < 9; ++i) {
        col.cx = widths[i];
        col.pszText = (LPWSTR)headers[i].c_str();
        ListView_InsertColumn(listReturnedBooks, i, &col);
    }

    int index = 0;
    for (auto& b : libOp.danhsachTraSach) {
        LVITEM item = { 0 };
        item.mask = LVIF_TEXT;
        item.iItem = index;

        wstring msdd = to_wstring(b.msdd);
        wstring hoten = convertToWString(b.hoTen);
        wstring bookID = convertToWString(b.idSach);
        wstring ten = convertToWString(b.tenSach);
        wstring tg = convertToWString(b.tacGia);
        wstring ngaymuon = convertToWString(b.ngayMuon);
        wstring stmuon = convertToWString(b.trangThaiMuon);
        wstring ngaytra = convertToWString(b.ngayTra);
        wstring sttra = convertToWString(b.trangThaiTra);

        item.pszText = (LPWSTR)msdd.c_str();
        ListView_InsertItem(listReturnedBooks, &item);

        ListView_SetItemText(listReturnedBooks, index, 1, (LPWSTR)hoten.c_str());
        ListView_SetItemText(listReturnedBooks, index, 2, (LPWSTR)bookID.c_str());
        ListView_SetItemText(listReturnedBooks, index, 3, (LPWSTR)ten.c_str());
        ListView_SetItemText(listReturnedBooks, index, 4, (LPWSTR)tg.c_str());
        ListView_SetItemText(listReturnedBooks, index, 5, (LPWSTR)ngaymuon.c_str());
        ListView_SetItemText(listReturnedBooks, index, 6, (LPWSTR)stmuon.c_str());
        ListView_SetItemText(listReturnedBooks, index, 7, (LPWSTR)ngaytra.c_str());
        ListView_SetItemText(listReturnedBooks, index, 8, (LPWSTR)sttra.c_str());

        index++;
    }
}

void DisplayManagerList(HWND hwnd) {
    ListView_DeleteAllItems(listViewManager); // Xóa hết dữ liệu cũ
    libOp.docThongTinQuanLy(); // Load từ file vào danhsachQuanLy

    int index = 0;
    for (auto& ql : danhsachQuanLy) {
        LVITEM item = { 0 };
        item.mask = LVIF_TEXT;
        item.iItem = index;

        wstring mcb = convertToWString(ql->getMCB());
        wstring name = convertToWString(ql->getHoTen());
        wstring sex = convertToWString(ql->getSex());
        wstring mail = convertToWString(ql->getMail());

        item.pszText = (LPWSTR)mcb.c_str();
        ListView_InsertItem(listViewManager, &item);

        ListView_SetItemText(listViewManager, index, 1, (LPWSTR)name.c_str());
        ListView_SetItemText(listViewManager, index, 2, (LPWSTR)sex.c_str());
        ListView_SetItemText(listViewManager, index, 3, (LPWSTR)mail.c_str());

        index++;
    }
}

void CheckBook(HWND hwnd) {
    wchar_t wID[256];
    GetWindowTextW(txtBookID_Borrow, wID, 256);
    char cID[256];
    size_t c;
    wcstombs_s(&c, cID, 256, wID, _TRUNCATE);
    string id = cID;

    libOp.docThongTinSach();
    auto it = find_if(danhsachSach.begin(), danhsachSach.end(), [&](LIBRARY* b) {
        return b->getBookID() == id;
        });

    if (it == danhsachSach.end()) {
        SetWindowTextW(lblBookInfo, L"Không tìm thấy sách.");
    }
    else {
        wstring info = L"Tên: " + convertToWString((*it)->getBookName()) + L" | TG: " + convertToWString((*it)->getAuthor());
        SetWindowTextW(lblBookInfo, info.c_str());
    }
}
void CheckReader(HWND hwnd) {
    wchar_t wMSDD[256];
    GetWindowTextW(txtMSDD_Borrow, wMSDD, 256);
    char cMSDD[256];
    size_t c;
    wcstombs_s(&c, cMSDD, 256, wMSDD, _TRUNCATE);
    int msdd = atoi(cMSDD);

    libOp.docThongTinDocGia();
    auto it = find_if(danhsachDocGia.begin(), danhsachDocGia.end(), [&](READER* r) {
        return r->getMSDD() == msdd;
        });

    if (it == danhsachDocGia.end()) {
        SetWindowTextW(lblReaderInfo, L"Không tìm thấy độc giả.");
    }
    else {
        wstring info = L"Họ tên: " + convertToWString((*it)->getHoTen()) + L" | Khoa: " + convertToWString((*it)->getKhoa());
        SetWindowTextW(lblReaderInfo, info.c_str());
    }
}
void CreateBorrowBookControls(HWND hwnd) {
    CreateWindowW(L"STATIC", L"MSDD:", WS_CHILD | WS_VISIBLE, 30, 30, 80, 25, hwnd, NULL, NULL, NULL);
    txtMSDD_Borrow = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 30, 150, 25, hwnd, NULL, NULL, NULL);
    btnCheckReader = CreateWindowW(L"BUTTON", L"Kiểm tra", WS_CHILD | WS_VISIBLE, 280, 30, 80, 25, hwnd, (HMENU)100, NULL, NULL);
    lblReaderInfo = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE, 120, 60, 240, 20, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"ID Sách:", WS_CHILD | WS_VISIBLE, 30, 90, 80, 25, hwnd, NULL, NULL, NULL);
    txtBookID_Borrow = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 90, 150, 25, hwnd, NULL, NULL, NULL);
    btnCheckBook = CreateWindowW(L"BUTTON", L"Kiểm tra", WS_CHILD | WS_VISIBLE, 280, 90, 80, 25, hwnd, (HMENU)101, NULL, NULL);
    lblBookInfo = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE, 120, 120, 240, 20, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"Ngày mượn:", WS_CHILD | WS_VISIBLE, 30, 150, 80, 25, hwnd, NULL, NULL, NULL);
    txtDate_Borrow = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 150, 240, 25, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"BUTTON", L"Mượn sách", WS_CHILD | WS_VISIBLE, 150, 190, 100, 30, hwnd, (HMENU)102, NULL, NULL);
}
void HandleBorrowing(HWND hwnd) {
    wchar_t wMSDD[256], wBookID[256], wDate[256];
    GetWindowTextW(txtMSDD_Borrow, wMSDD, 256);
    GetWindowTextW(txtBookID_Borrow, wBookID, 256);
    GetWindowTextW(txtDate_Borrow, wDate, 256);

    char cMSDD[256], cBookID[256], cDate[256];
    size_t c;
    wcstombs_s(&c, cMSDD, 256, wMSDD, _TRUNCATE);
    wcstombs_s(&c, cBookID, 256, wBookID, _TRUNCATE);
    wcstombs_s(&c, cDate, 256, wDate, _TRUNCATE);

    int msdd = atoi(cMSDD);
    string bookID = cBookID;
    string date = cDate;

    libOp.docThongTinDocGia();
    libOp.docThongTinSach();

    auto itDG = find_if(danhsachDocGia.begin(), danhsachDocGia.end(), [&](READER* r) {
        return r->getMSDD() == msdd;
        });

    if (itDG == danhsachDocGia.end()) {
        MessageBoxW(hwnd, L"Không tìm thấy độc giả!", L"Lỗi", MB_OK | MB_ICONERROR);
        return;
    }

    auto itBook = find_if(danhsachSach.begin(), danhsachSach.end(), [&](LIBRARY* b) {
        return b->getBookID() == bookID;
        });

    if (itBook == danhsachSach.end()) {
        MessageBoxW(hwnd, L"Không tìm thấy sách!", L"Lỗi", MB_OK | MB_ICONERROR);
        return;
    }

    string tenSach = (*itBook)->getBookName();
    string tacGia = (*itBook)->getAuthor();
    string tenDG = (*itDG)->getHoTen();
    StandardDate(date); 
    libOp.luuThongTinMuonSach(msdd, tenDG, bookID, tenSach, tacGia, date, "Dang muon");
    MessageBoxW(hwnd, L"Mượn sách thành công!", L"Thành công", MB_OK | MB_ICONINFORMATION); //done
}
void CreateReturnBookControls(HWND hwnd) {
    CreateWindowW(L"STATIC", L"MSDD:", WS_CHILD | WS_VISIBLE, 30, 30, 80, 25, hwnd, NULL, NULL, NULL);
    txtMSDD_Return = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 30, 180, 25, hwnd, NULL, NULL, NULL);
    btnCheckReturn = CreateWindowW(L"BUTTON", L"Kiểm tra", WS_CHILD | WS_VISIBLE, 310, 30, 90, 25, hwnd, (HMENU)200, NULL, NULL);

    lblReturnInfo = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE, 30, 70, 370, 100, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"STATIC", L"Ngày trả:", WS_CHILD | WS_VISIBLE, 30, 190, 80, 25, hwnd, NULL, NULL, NULL);
    txtReturnDate = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 190, 280, 25, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"BUTTON", L"Xác nhận trả", WS_CHILD | WS_VISIBLE, 170, 240, 120, 30, hwnd, (HMENU)201, NULL, NULL);
}
OPERATE muonTemp; // tạm lưu thông tin mượn cho bước trả
void CheckReturnMSDD(HWND hwnd) {
    wchar_t wMSDD[256];
    GetWindowTextW(txtMSDD_Return, wMSDD, 256);
    char cMSDD[256];
    size_t c;
    wcstombs_s(&c, cMSDD, 256, wMSDD, _TRUNCATE);
    int msdd = atoi(cMSDD);

    libOp.docThongTinMuonSach();
    auto it = find_if(libOp.danhsachMuonSach.begin(), libOp.danhsachMuonSach.end(), [&](OPERATE& m) {
        return m.msdd == msdd;
        });

    if (it == libOp.danhsachMuonSach.end()) {
        SetWindowTextW(lblReturnInfo, L"Không tìm thấy thông tin mượn.");
    }
    else {
        muonTemp = *it; // lưu lại để dùng khi xác nhận trả
        wstring info =
            L"Họ tên: " + convertToWString(it->hoTen) +
            L"\nID sách: " + convertToWString(it->idSach) +
            L"\nTên sách: " + convertToWString(it->tenSach) +
            L"\nTác giả: " + convertToWString(it->tacGia) +
            L"\nNgày mượn: " + convertToWString(it->ngayMuon);
        SetWindowTextW(lblReturnInfo, info.c_str());
    }
}
void HandleReturnBook(HWND hwnd) {
    wchar_t wDate[256];
    GetWindowTextW(txtReturnDate, wDate, 256);
    char cDate[256];
    size_t c;
    wcstombs_s(&c, cDate, 256, wDate, _TRUNCATE);
    string ngayTra = cDate;
    StandardDate(ngayTra);
    if (!libOp.CheckDate(ngayTra)) {
        MessageBoxW(hwnd, L"Ngày trả không hợp lệ!", L"Lỗi", MB_OK | MB_ICONERROR);
        return;
    }

    if (!libOp.CheckReturnbookDay(muonTemp.ngayMuon, ngayTra)) {
        MessageBoxW(hwnd, L"Ngày trả phải sau hoặc bằng ngày mượn!", L"Lỗi", MB_OK | MB_ICONERROR);
        return;
    }
    muonTemp.trangThaiMuon = "Da muon";
    muonTemp.ngayTra = ngayTra;
    muonTemp.trangThaiTra = "Da tra";

    ofstream file("TraSach.txt", ios::app);
    file << muonTemp.msdd << "," << muonTemp.hoTen << "," << muonTemp.idSach << ","
        << muonTemp.tenSach << "," << muonTemp.tacGia << "," << muonTemp.ngayMuon << ","
        << muonTemp.trangThaiMuon << "," << muonTemp.ngayTra << "," << muonTemp.trangThaiTra << endl;
    file.close();

    ofstream fileMuon("Muonsach.txt");
    fileMuon.close();
    for (auto& i : libOp.danhsachMuonSach) {
        if (i.msdd == muonTemp.msdd) {
            continue;
        }
        else {
            libOp.luuThongTinMuonSach(i.msdd, i.hoTen, i.idSach, i.tenSach, i.tacGia, i.ngayMuon, "Dang muon");
        }
    }
    MessageBoxW(hwnd, L"Trả sách thành công!", L"Thành công", MB_OK | MB_ICONINFORMATION);

}

// ====== CheckMail and Password ======
bool CheckMail(const string& email) {
    regex pattern("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
    if (!regex_match(email, pattern)) return false;
    for (auto ql : danhsachQuanLy) {
        if (ql->getMail() == email) return false;
    }
    return true;
}
bool CheckPassword(const string& pass) {
    return pass.length() >= 6;
}
string GenerateMCB() {
    libOp.docThongTinQuanLy();
    int count = (int)danhsachQuanLy.size() + 1;
    char buffer[10];
    sprintf(buffer, "QL%04d", count);
    return string(buffer);
}

// ====== Login Window ======
LRESULT CALLBACK LoginProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"MCB:", WS_CHILD | WS_VISIBLE, 50, 40, 60, 20, hwnd, NULL, NULL, NULL);
        txtEmailLogin = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 40, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Password:", WS_CHILD | WS_VISIBLE, 50, 80, 60, 20, hwnd, NULL, NULL, NULL);
        txtPassLogin = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD, 120, 80, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Login", WS_CHILD | WS_VISIBLE, 120, 120, 90, 25, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Register", WS_CHILD | WS_VISIBLE, 230, 120, 90, 25, hwnd, (HMENU)2, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            wchar_t wID[256], wPass[256];
            GetWindowTextW(txtEmailLogin, wID, 256);
            GetWindowTextW(txtPassLogin, wPass, 256);

            char id[256], pass[256];
            size_t c;
            wcstombs_s(&c, id, 256, wID, _TRUNCATE);
            wcstombs_s(&c, pass, 256, wPass, _TRUNCATE);

            libOp.docThongTinQuanLy();
            for (auto ql : danhsachQuanLy) {
                if (ql->getMCB() == id && ql->getPassword() == pass) {
                    ShowWindow(hwnd, SW_HIDE);
                    ShowMainMenu();
                    return 0;
                }
            }
            MessageBoxW(hwnd, L"Sai MCB hoặc mật khẩu", L"Lỗi", MB_OK);
        }
        else if (LOWORD(wParam) == 2) {
            ShowWindow(hwnd, SW_HIDE);
            ShowRegister();
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Register Window ======
LRESULT CALLBACK RegisterProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
    {
        CreateWindowW(L"STATIC", L"Họ tên:", WS_VISIBLE | WS_CHILD,
            50, 30, 100, 20, hwnd, NULL, NULL, NULL);
        txtNameReg = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            160, 30, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Giới tính:", WS_VISIBLE | WS_CHILD,
            50, 70, 100, 20, hwnd, NULL, NULL, NULL);
        txtSexReg = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            160, 70, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Email:", WS_VISIBLE | WS_CHILD,
            50, 110, 100, 20, hwnd, NULL, NULL, NULL);
        txtEmailReg = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            160, 110, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Mật khẩu:", WS_VISIBLE | WS_CHILD,
            50, 150, 100, 20, hwnd, NULL, NULL, NULL);
        txtPassReg = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
            160, 150, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Đăng ký", WS_VISIBLE | WS_CHILD,
            160, 200, 100, 30, hwnd, (HMENU)1, NULL, NULL);

        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            wchar_t wName[256], wSex[256], wEmail[256], wPass[256];
            GetWindowTextW(txtNameReg, wName, 256);
            GetWindowTextW(txtSexReg, wSex, 256);
            GetWindowTextW(txtEmailReg, wEmail, 256);
            GetWindowTextW(txtPassReg, wPass, 256);

            char name[256], sex[256], email[256], pass[256];
            size_t c;
            wcstombs_s(&c, name, 256, wName, _TRUNCATE);
            wcstombs_s(&c, sex, 256, wSex, _TRUNCATE);
            wcstombs_s(&c, email, 256, wEmail, _TRUNCATE);
            wcstombs_s(&c, pass, 256, wPass, _TRUNCATE);

            if (!CheckMail(email)) {
                MessageBoxW(hwnd, L"Email sai định dạng hoặc đã tồn tại!", L"Lỗi", MB_OK | MB_ICONERROR);
                return 0;
            }

            if (!CheckPassword(pass)) {
                MessageBoxW(hwnd, L"Mật khẩu phải có ít nhất 6 ký tự!", L"Lỗi", MB_OK | MB_ICONERROR);
                return 0;
            }

            string id = GenerateMCB();
            libOp.luuThongTinQuanLy(id, name, sex, email, pass);
            wstring wID(id.begin(), id.end());
            wstring msg = L"Đăng ký thành công!\nMCB của bạn là: " + wID;
            MessageBoxW(hwnd, msg.c_str(), L"Thành công", MB_OK | MB_ICONINFORMATION);

            ShowWindow(hwnd, SW_HIDE);
            ShowLogin();
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Main Menu ======
LRESULT CALLBACK MainMenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"Thông tin sách", WS_CHILD | WS_VISIBLE, 30, 30, 180, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Thông tin độc giả", WS_CHILD | WS_VISIBLE, 30, 70, 180, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Thông tin quản lý", WS_CHILD | WS_VISIBLE, 30, 110, 180, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Đăng xuất", WS_CHILD | WS_VISIBLE, 30, 160, 180, 30, hwnd, (HMENU)99, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: ShowBookInfo(); break;
        case 2: ShowReaderInfo(); break;
        case 3: ShowManagerInfo(); break;
        case 99:
            DestroyWindow(hwnd);
            ShowLogin();
            break;
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Book Info Window ======
LRESULT CALLBACK BookInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        // Các nút chức năng
        CreateWindowW(L"BUTTON", L"Thêm sách", WS_CHILD | WS_VISIBLE, 30, 30, 180, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Sửa sách", WS_CHILD | WS_VISIBLE, 30, 70, 180, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Xóa sách", WS_CHILD | WS_VISIBLE, 30, 110, 180, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Sắp xếp", WS_CHILD | WS_VISIBLE, 30, 150, 180, 30, hwnd, (HMENU)4, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Hiển thị danh sách sách", WS_CHILD | WS_VISIBLE, 30, 190, 180, 30, hwnd, (HMENU)5, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Thoát", WS_CHILD | WS_VISIBLE, 30, 230, 180, 30, hwnd, (HMENU)6, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            ShowAddBookWindow();
            break;
        case 2:
            ShowEditBookWindow();
            break;
        case 3:
            ShowDeleteBookWindow();
            break;
        case 4:
            ShowSortBookWindow();
            break;
        case 5:
            ShowBookListWindow();
            break;
        case 6:
            // Thoát về cửa sổ trước
            ShowWindow(hwnd, SW_HIDE);
            // Quay lại cửa sổ chính hoặc trước đó
            ShowMainMenu();
            break;
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Reader Info Window ======
LRESULT CALLBACK ReaderInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"Thêm độc giả", WS_CHILD | WS_VISIBLE, 30, 30, 200, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Sửa thông tin độc giả", WS_CHILD | WS_VISIBLE, 30, 70, 200, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Hiển thị danh sách độc giả", WS_CHILD | WS_VISIBLE, 30, 110, 200, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Thoát", WS_CHILD | WS_VISIBLE, 30, 150, 200, 30, hwnd, (HMENU)4, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            ShowAddReaderWindow();
            break;
        case 2:
            ShowEditReaderWindow();
            break;
        case 3:
            ShowReaderListWindow();
            break;
        case 4:
            ShowWindow(hwnd, SW_HIDE);
            ShowMainMenu();
            break;
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Manager Info Window ======
LRESULT CALLBACK ManagerInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"Mượn sách", WS_CHILD | WS_VISIBLE, 30, 30, 220, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Trả sách", WS_CHILD | WS_VISIBLE, 30, 70, 220, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Danh sách mượn sách", WS_CHILD | WS_VISIBLE, 30, 110, 220, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Danh sách trả sách", WS_CHILD | WS_VISIBLE, 30, 150, 220, 30, hwnd, (HMENU)4, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Tìm kiếm sách mượn", WS_CHILD | WS_VISIBLE, 30, 190, 220, 30, hwnd, (HMENU)5, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Tìm kiếm sách trả", WS_CHILD | WS_VISIBLE, 30, 230, 220, 30, hwnd, (HMENU)6, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Xem danh sách quản lý", WS_CHILD | WS_VISIBLE, 30, 270, 220, 30, hwnd, (HMENU)7, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Thoát", WS_CHILD | WS_VISIBLE, 30, 310, 220, 30, hwnd, (HMENU)8, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            ShowBorrowBookWindow();
            break;
        case 2:
            ShowReturnBookWindow();
            break;
        case 3:
            ShowBorrowedListWindow();
            break;
        case 4:
            ShowReturnedListWindow();
            break;
        case 5:
            ShowSearchBorrowedBookWindow();
            break;
        case 6:
            ShowSearchDueBookWindow();
            break;
        case 7:
            ShowListManagerWindow();
            break;
        case 8:
            ShowWindow(hwnd, SW_HIDE);
            ShowMainMenu();
            break;
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Add Book Window ======
LRESULT CALLBACK AddBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Mã sách:", WS_CHILD | WS_VISIBLE, 30, 30, 100, 20, hwnd, NULL, NULL, NULL);
        txtBookID = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 30, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Tên sách:", WS_CHILD | WS_VISIBLE, 30, 70, 100, 20, hwnd, NULL, NULL, NULL);
        txtBookName = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 70, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Tác giả:", WS_CHILD | WS_VISIBLE, 30, 110, 100, 20, hwnd, NULL, NULL, NULL);
        txtAuthor = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 110, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Ngày nhập:", WS_CHILD | WS_VISIBLE, 30, 150, 100, 20, hwnd, NULL, NULL, NULL);
        txtDate = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 150, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Trạng thái:", WS_CHILD | WS_VISIBLE, 30, 190, 100, 20, hwnd, NULL, NULL, NULL);
        txtStatus = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 190, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Lưu sách", WS_CHILD | WS_VISIBLE, 140, 240, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            wchar_t wID[256], wBookName[256], wAuthor[256], wDate[256], wStatus[256];
            GetWindowTextW(txtBookID, wID, 256);
            GetWindowTextW(txtBookName, wBookName, 256);
            GetWindowTextW(txtAuthor, wAuthor, 256);
            GetWindowTextW(txtDate, wDate, 256);
            GetWindowTextW(txtStatus, wStatus, 256);

            if (wcslen(wID) == 0 || wcslen(wBookName) == 0 || wcslen(wAuthor) == 0 || wcslen(wDate) == 0 || wcslen(wStatus) == 0) {
                MessageBoxW(hwnd, L"Vui lòng nhập đầy đủ thông tin sách!", L"Thiếu thông tin", MB_OK | MB_ICONWARNING);
                return 0;
            }

            char idbook[256], bookname[256], author[256], date[256], status[256];
            size_t c;
            wcstombs_s(&c, idbook, 256, wID, _TRUNCATE);
            wcstombs_s(&c, bookname, 256, wBookName, _TRUNCATE);
            wcstombs_s(&c, author, 256, wAuthor, _TRUNCATE);
            wcstombs_s(&c, date, 256, wDate, _TRUNCATE);
            wcstombs_s(&c, status, 256, wStatus, _TRUNCATE);

            // Kiểm tra trùng mã sách
            for (auto sach : danhsachSach) {
                if (sach->getBookID() == idbook) {
                    MessageBoxW(hwnd, L"Mã sách đã tồn tại!", L"Trùng mã", MB_OK | MB_ICONERROR);
                    return 0;
                }
            }

            libOp.luuThongTinSach(idbook, bookname, author, date, status); 

            MessageBoxW(hwnd, L"Đã thêm sách thành công!", L"Thành công", MB_OK);
            DestroyWindow(hwnd);
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK EditBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static LIBRARY* currentBook = nullptr;

    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(L"STATIC", L"Nhập ID sách cần sửa:", WS_CHILD | WS_VISIBLE,
            30, 20, 200, 20, hwnd, NULL, NULL, NULL);
        txtEditBookID = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            30, 45, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Tìm sách", WS_CHILD | WS_VISIBLE,
            250, 45, 100, 25, hwnd, (HMENU)1, NULL, NULL);

        // Các control sẽ hiện sau khi tìm thấy sách
        CreateWindowW(L"STATIC", L"Tên sách:", WS_CHILD, 30, 80, 100, 20, hwnd, NULL, NULL, NULL);
        txtEditBookName = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_BORDER,
            140, 80, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Tác giả:", WS_CHILD, 30, 110, 100, 20, hwnd, NULL, NULL, NULL);
        txtEditAuthor = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_BORDER,
            140, 110, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Ngày nhập:", WS_CHILD, 30, 140, 100, 20, hwnd, NULL, NULL, NULL);
        txtEditDate = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_BORDER,
            140, 140, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Trạng thái:", WS_CHILD, 30, 170, 100, 20, hwnd, NULL, NULL, NULL);
        txtEditStatus = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_BORDER,
            140, 170, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Lưu thay đổi", WS_CHILD,
            100, 220, 120, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Hủy", WS_CHILD,
            240, 220, 80, 30, hwnd, (HMENU)3, NULL, NULL);

        // Ẩn các control ban đầu
        ShowWindow(txtEditBookName, SW_HIDE);
        ShowWindow(txtEditAuthor, SW_HIDE);
        ShowWindow(txtEditDate, SW_HIDE);
        ShowWindow(txtEditStatus, SW_HIDE);
        ShowWindow(GetDlgItem(hwnd, 2), SW_HIDE); // Nút Lưu
        ShowWindow(GetDlgItem(hwnd, 3), SW_HIDE); // Nút Hủy
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: { // Tìm sách
            wchar_t wID[256];
            GetWindowTextW(txtEditBookID, wID, 256);
            char id[256];
            size_t c;
            wcstombs_s(&c, id, 256, wID, _TRUNCATE);
            string idbook(id);
            libOp.docThongTinSach();
            currentBook = nullptr;
            for (auto sach : danhsachSach) {
                if (sach->getBookID() == idbook) {
                    currentBook = sach;
                    break;
                }
            }

            if (currentBook) {
                // Chuyển đổi từ string sang wstring
                string tempName = currentBook->getBookName();
                wstring wBookName(tempName.begin(), tempName.end());

                string tempAuthor = currentBook->getAuthor();
                wstring wAuthor(tempAuthor.begin(), tempAuthor.end());

                string tempDate = currentBook->getInDay();
                wstring wDate(tempDate.begin(), tempDate.end());

                string tempStatus = currentBook->getBookMode();
                wstring wStatus(tempStatus.begin(), tempStatus.end());


                // Hiển thị thông tin sách
                SetWindowTextW(txtEditBookName, wBookName.c_str());
                SetWindowTextW(txtEditAuthor, wAuthor.c_str());
                SetWindowTextW(txtEditDate, wDate.c_str());
                SetWindowTextW(txtEditStatus, wStatus.c_str());

                // Hiện các control
                ShowWindow(txtEditBookName, SW_SHOW);
                ShowWindow(txtEditAuthor, SW_SHOW);
                ShowWindow(txtEditDate, SW_SHOW);
                ShowWindow(txtEditStatus, SW_SHOW);
                ShowWindow(GetDlgItem(hwnd, 2), SW_SHOW); // Nút Lưu
                ShowWindow(GetDlgItem(hwnd, 3), SW_SHOW); // Nút Hủy
            }
            else {
                MessageBoxW(hwnd, L"Không tìm thấy sách có ID này!", L"Lỗi", MB_OK | MB_ICONERROR);
            }
            break;
        }

        case 2: { // Lưu thay đổi
            if (!currentBook) break;

            wchar_t wName[256], wAuthor[256], wDate[256], wStatus[256];
            GetWindowTextW(txtEditBookName, wName, 256);
            GetWindowTextW(txtEditAuthor, wAuthor, 256);
            GetWindowTextW(txtEditDate, wDate, 256);
            GetWindowTextW(txtEditStatus, wStatus, 256);

            // Chuyển đổi từ wchar_t sang string
            char name[256], author[256], date[256], status[256];
            size_t c;
            wcstombs_s(&c, name, 256, wName, _TRUNCATE);
            wcstombs_s(&c, author, 256, wAuthor, _TRUNCATE);
            wcstombs_s(&c, date, 256, wDate, _TRUNCATE);
            wcstombs_s(&c, status, 256, wStatus, _TRUNCATE);

            // Cập nhật thông tin
            currentBook->setBookName(name);
            currentBook->setAuthor(author);
            currentBook->setInDay(date);
            currentBook->setBookMode(status);

            // Lưu lại vào file
            ofstream file("Sach.txt");
            for (auto sach : danhsachSach) {
                libOp.luuThongTinSach(sach->getBookID(), sach->getBookName(),
                    sach->getAuthor(), sach->getInDay(), sach->getBookMode());
            }
            file.close();

            MessageBoxW(hwnd, L"Đã cập nhật thông tin sách!", L"Thành công", MB_OK);
            DestroyWindow(hwnd);
            break;
        }

        case 3: 
            DestroyWindow(hwnd);
            break;
        }
        break;

    case WM_DESTROY:
        currentBook = nullptr;
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK DeleteBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Mã sách cần xóa:", WS_CHILD | WS_VISIBLE, 30, 40, 120, 20, hwnd, NULL, NULL, NULL);
        txtDeleteBookID = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 160, 40, 120, 20, hwnd, NULL, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Xóa", WS_CHILD | WS_VISIBLE, 110, 90, 80, 30, hwnd, (HMENU)1, NULL, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            wchar_t wID[256];
            GetWindowTextW(txtDeleteBookID, wID, 256);
            if (wcslen(wID) == 0) {
                MessageBoxW(hwnd, L"Vui lòng nhập mã sách!", L"Lỗi", MB_OK | MB_ICONWARNING);
                return 0;
            }

            // Convert sang string
            char iddelete[256];
            size_t c;
            wcstombs_s(&c, iddelete, 256, wID, _TRUNCATE);
            string idbookDelete(iddelete);

            libOp.docThongTinSach();
            bool found = false;
            bool yesdelete = false;
            auto vitriDel = danhsachSach.end();
            auto it = danhsachSach.begin();
            for (; it != danhsachSach.end(); ++it) {
                if ((*it)->getBookID() == idbookDelete) {
                    // Hiện tên sách trước khi xác nhận
                    wstring wsName = convertToWString((*it)->getBookName());
                    wstring confirmMsg = L"Bạn có chắc chắn muốn xóa sách:\n[" + wsName + L"] không?";

                    int confirm = MessageBoxW(hwnd, confirmMsg.c_str(), L"Xác nhận", MB_YESNO | MB_ICONQUESTION);
                    if (confirm == IDYES) {
                        found = true;
                        yesdelete = true;
                        vitriDel = it;
                    }
                    break;
                }
            }

            if (found && yesdelete) {
                danhsachSach.erase(vitriDel);

                ofstream fout("Sach.txt");
                for (auto sach : danhsachSach) {
                    fout << sach->getBookID() << "," << sach->getBookName() << ","
                        << sach->getAuthor() << "," << sach->getInDay() << "," << sach->getBookMode() << endl;
                }
                fout.close();

                MessageBoxW(hwnd, L"Đã xóa sách thành công!", L"Thành công", MB_OK);
                DestroyWindow(hwnd);
            }
            else if (found && !yesdelete) {
                MessageBoxW(hwnd, L"Không xóa sách!", L"Thành công", MB_OK);
                DestroyWindow(hwnd);
            }
            else if (!found) {
                MessageBoxW(hwnd, L"Không tìm thấy mã sách!", L"Lỗi", MB_OK | MB_ICONERROR);
            }
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK SortBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(L"STATIC", L"Chọn tiêu chí sắp xếp:", WS_CHILD | WS_VISIBLE, 30, 20, 200, 20, hwnd, NULL, NULL, NULL);

        cmbSortCriteria = CreateWindowW(L"COMBOBOX", NULL,
            CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
            30, 50, 250, 150, hwnd, (HMENU)1001, NULL, NULL);

        SendMessage(cmbSortCriteria, CB_ADDSTRING, 0, (LPARAM)L"Theo ID sách");
        SendMessage(cmbSortCriteria, CB_ADDSTRING, 0, (LPARAM)L"Theo Tên sách");
        SendMessage(cmbSortCriteria, CB_ADDSTRING, 0, (LPARAM)L"Theo Tác giả");
        SendMessage(cmbSortCriteria, CB_ADDSTRING, 0, (LPARAM)L"Theo Ngày nhập");
        SendMessage(cmbSortCriteria, CB_ADDSTRING, 0, (LPARAM)L"Theo Trạng thái");

        CreateWindowW(L"BUTTON", L"Sắp xếp", WS_CHILD | WS_VISIBLE, 300, 50, 100, 30, hwnd, (HMENU)2, NULL, NULL);

        // ListView
        InitCommonControls();
        listSortedBooks = CreateWindowW(WC_LISTVIEW, L"",
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS,
            30, 100, 580, 220, hwnd, (HMENU)2001, hInst, NULL);

        LVCOLUMN lvCol;
        ZeroMemory(&lvCol, sizeof(LVCOLUMN));
        lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        lvCol.pszText = (LPWSTR)L"ID"; lvCol.cx = 80;
        ListView_InsertColumn(listSortedBooks, 0, &lvCol);
        lvCol.pszText = (LPWSTR)L"Tên sách"; lvCol.cx = 150;
        ListView_InsertColumn(listSortedBooks, 1, &lvCol);
        lvCol.pszText = (LPWSTR)L"Tác giả"; lvCol.cx = 120;
        ListView_InsertColumn(listSortedBooks, 2, &lvCol);
        lvCol.pszText = (LPWSTR)L"Ngày nhập"; lvCol.cx = 100;
        ListView_InsertColumn(listSortedBooks, 3, &lvCol);
        lvCol.pszText = (LPWSTR)L"Trạng thái"; lvCol.cx = 100;
        ListView_InsertColumn(listSortedBooks, 4, &lvCol);
        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 2) {
            int selected = SendMessage(cmbSortCriteria, CB_GETCURSEL, 0, 0);
            libOp.docThongTinSach();

            switch (selected) {
            case 0: libOp.sortBooksByID(danhsachSach); break;
            case 1: libOp.sortBooksByName(danhsachSach); break;
            case 2: libOp.sortBooksByAuthor(danhsachSach); break;
            case 3: libOp.sortBooksByInDay(danhsachSach); break;
            case 4: libOp.sortBooksByMode(danhsachSach); break;
            }

            DisplaySortedBooks(hwnd);
        }
        break;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK BookListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        InitCommonControls();
        listAllBooks = CreateWindowW(WC_LISTVIEW, L"",
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS,
            30, 30, 580, 300, hwnd, (HMENU)4001, hInst, NULL);

        LVCOLUMN lvCol;
        ZeroMemory(&lvCol, sizeof(LVCOLUMN));
        lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        lvCol.pszText = (LPWSTR)L"ID"; lvCol.cx = 80;
        ListView_InsertColumn(listAllBooks, 0, &lvCol);
        lvCol.pszText = (LPWSTR)L"Tên sách"; lvCol.cx = 150;
        ListView_InsertColumn(listAllBooks, 1, &lvCol);
        lvCol.pszText = (LPWSTR)L"Tác giả"; lvCol.cx = 120;
        ListView_InsertColumn(listAllBooks, 2, &lvCol);
        lvCol.pszText = (LPWSTR)L"Ngày nhập"; lvCol.cx = 100;
        ListView_InsertColumn(listAllBooks, 3, &lvCol);
        lvCol.pszText = (LPWSTR)L"Trạng thái"; lvCol.cx = 100;
        ListView_InsertColumn(listAllBooks, 4, &lvCol);

        // Gọi hàm load dữ liệu
        libOp.docThongTinSach();
        DisplayAllBooks(hwnd);
        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 3001) {
            ShowBookListWindow();
        }
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


// ====== Add Reader Window ======
LRESULT CALLBACK AddReaderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Mã số độc giả:", WS_CHILD | WS_VISIBLE, 30, 30, 100, 20, hwnd, NULL, NULL, NULL);
        txtReaderID = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 30, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Tên độc giả:", WS_CHILD | WS_VISIBLE, 30, 70, 100, 20, hwnd, NULL, NULL, NULL);
        txtReaderName = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 70, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Khoa:", WS_CHILD | WS_VISIBLE, 30, 110, 100, 20, hwnd, NULL, NULL, NULL);
        txtKhoa = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 110, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Lưu độc giả", WS_CHILD | WS_VISIBLE, 140, 240, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            wchar_t wReaderID[256], wReaderName[256], wKhoa[256];
            GetWindowTextW(txtReaderID, wReaderID, 256);
            GetWindowTextW(txtReaderName, wReaderName, 256);
            GetWindowTextW(txtKhoa, wKhoa, 256);

            if (wcslen(wReaderID) == 0 || wcslen(wReaderName) == 0 || wcslen(wKhoa) == 0) {
                MessageBoxW(hwnd, L"Vui lòng nhập đầy đủ thông tin độc giả!", L"Thiếu thông tin", MB_OK | MB_ICONWARNING);
                return 0;
            }

            char idreader[256], readername[256], khoa[256];
            size_t c;
            wcstombs_s(&c, idreader, 256, wReaderID, _TRUNCATE);
            wcstombs_s(&c, readername, 256, wReaderName, _TRUNCATE);
            wcstombs_s(&c, khoa, 256, wKhoa, _TRUNCATE);

            // Kiểm tra trùng mã độc giả
            for (auto docgia : danhsachDocGia) {
                if (docgia->getMSDD() == stoi(idreader)) {
                    MessageBoxW(hwnd, L"Mã số định danh của độc giả đã tồn tại!", L"Trùng mã", MB_OK | MB_ICONERROR);
                    return 0;
                }
            }

            libOp.luuThongTinDocGia(stoi(idreader), readername, khoa);

            MessageBoxW(hwnd, L"Đã thêm độc giả thành công!", L"Thành công", MB_OK);
            DestroyWindow(hwnd);
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK EditReaderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static READER* currentReader = nullptr;

    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(L"STATIC", L"Nhập MSDD sách cần sửa:", WS_CHILD | WS_VISIBLE,
            30, 20, 200, 20, hwnd, NULL, NULL, NULL);
        txtEditReaderID = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            30, 45, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Find", WS_CHILD | WS_VISIBLE,
            250, 45, 100, 25, hwnd, (HMENU)1, NULL, NULL);

        // Các control sẽ hiện sau khi tìm thấy sách
        CreateWindowW(L"STATIC", L"Name:", WS_CHILD, 30, 80, 100, 20, hwnd, NULL, NULL, NULL);
        txtEditReaderName = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_BORDER,
            140, 80, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", L"Khoa:", WS_CHILD, 30, 110, 100, 20, hwnd, NULL, NULL, NULL);
        txtEditKhoa = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_BORDER,
            140, 110, 200, 20, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Save Changes", WS_CHILD,
            100, 220, 120, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"BUTTON", L"Cancel", WS_CHILD,
            240, 220, 80, 30, hwnd, (HMENU)3, NULL, NULL);

        // Ẩn các control ban đầu
        ShowWindow(txtEditReaderName, SW_HIDE);
        ShowWindow(txtEditKhoa, SW_HIDE);
        ShowWindow(GetDlgItem(hwnd, 2), SW_HIDE); // Nút Lưu
        ShowWindow(GetDlgItem(hwnd, 3), SW_HIDE); // Nút Hủy
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: { 
            wchar_t wID[256];
            GetWindowTextW(txtEditReaderID, wID, 256);
            char msdd[256];
            size_t c;
            wcstombs_s(&c, msdd, 256, wID, _TRUNCATE);
            string idreader(msdd);
            libOp.docThongTinDocGia();
            currentReader = nullptr;
            for (auto& docgia : danhsachDocGia) {
                if (docgia->getMSDD() == stoi(idreader)) {
                    currentReader = docgia;
                    break;
                }
            }

            if (currentReader) {
                // Chuyển đổi từ string sang wstring
                string tempReaderName = currentReader->getHoTen();
                wstring wReaderName(tempReaderName.begin(), tempReaderName.end());

                string tempKhoa = currentReader->getKhoa();
                wstring wKhoa(tempKhoa.begin(), tempKhoa.end());


                // Hiển thị thông tin doc gia
                SetWindowTextW(txtEditReaderName, wReaderName.c_str());
                SetWindowTextW(txtEditKhoa, wKhoa.c_str());

                // Hiện các control
                ShowWindow(txtEditReaderName, SW_SHOW);
                ShowWindow(txtEditKhoa, SW_SHOW);
                ShowWindow(GetDlgItem(hwnd, 2), SW_SHOW); // Nút Lưu
                ShowWindow(GetDlgItem(hwnd, 3), SW_SHOW); // Nút Hủy
            }
            else {
                MessageBoxW(hwnd, L"Không tìm thấy doc gia có MSDD này!", L"Lỗi", MB_OK | MB_ICONERROR);
            }
            break;
        }

        case 2: { // Lưu thay đổi
            if (!currentReader) break;

            wchar_t wReaderName[256], wKhoa[256];
            GetWindowTextW(txtEditReaderName, wReaderName, 256);
            GetWindowTextW(txtEditKhoa, wKhoa, 256);

            // Chuyển đổi từ wchar_t sang string
            char readername[256], khoa[256];
            size_t c;
            wcstombs_s(&c, readername, 256, wReaderName, _TRUNCATE);
            wcstombs_s(&c, khoa, 256, wKhoa, _TRUNCATE);

            // Cập nhật thông tin
            currentReader->setHoTen(readername);
            currentReader->setKhoa(khoa);

            // Lưu lại vào file
            ofstream file("Docgia.txt");
            for (auto docgia : danhsachDocGia) {
                libOp.luuThongTinDocGia(docgia->getMSDD(), docgia->getHoTen(),
                    docgia->getKhoa());
            }
            file.close();

            MessageBoxW(hwnd, L"Đã cập nhật thông tin doc gia!", L"Thành công", MB_OK);
            DestroyWindow(hwnd);
            break;
        }

        case 3:
            DestroyWindow(hwnd);
            break;
        }
        break;

    case WM_DESTROY:
        currentReader = nullptr;
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK ReaderListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        InitCommonControls();
        listAllReaders = CreateWindowW(WC_LISTVIEW, L"",
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS,
            30, 30, 580, 300, hwnd, (HMENU)5001, hInst, NULL);

        LVCOLUMN lvCol;
        ZeroMemory(&lvCol, sizeof(LVCOLUMN));
        lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        lvCol.pszText = (LPWSTR)L"MSDD"; lvCol.cx = 80;
        ListView_InsertColumn(listAllReaders, 0, &lvCol);
        lvCol.pszText = (LPWSTR)L"Họ tên"; lvCol.cx = 200;
        ListView_InsertColumn(listAllReaders, 1, &lvCol);
        lvCol.pszText = (LPWSTR)L"Khoa"; lvCol.cx = 200;
        ListView_InsertColumn(listAllReaders, 2, &lvCol);

        libOp.docThongTinDocGia(); // load danh sách từ file
        DisplayAllReaders(hwnd);
        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 3001) {
            ShowBookListWindow();
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====== Manager Window ======
LRESULT CALLBACK BorrowBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateBorrowBookControls(hwnd);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 100: CheckReader(hwnd); break;
        case 101: CheckBook(hwnd); break;
        case 102: HandleBorrowing(hwnd); break;
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK ReturnBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateReturnBookControls(hwnd);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 200: CheckReturnMSDD(hwnd); break;
        case 201: HandleReturnBook(hwnd); break;
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK BorrowedListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        DisplayBorrowedList(hwnd);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK ReturnedListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        DisplayReturnedList(hwnd);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK SearchBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Chọn tiêu chí:", WS_VISIBLE | WS_CHILD,
            30, 20, 100, 25, hwnd, NULL, NULL, NULL);

        cbSearchType = CreateWindowW(L"COMBOBOX", NULL,
            CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
            140, 20, 180, 200, hwnd, NULL, NULL, NULL);

        SendMessage(cbSearchType, CB_ADDSTRING, 0, (LPARAM)L"MSDD");
        SendMessage(cbSearchType, CB_ADDSTRING, 0, (LPARAM)L"Mã sách");
        SendMessage(cbSearchType, CB_ADDSTRING, 0, (LPARAM)L"Tên sách");
        SendMessage(cbSearchType, CB_ADDSTRING, 0, (LPARAM)L"Tác giả");
        SendMessage(cbSearchType, CB_ADDSTRING, 0, (LPARAM)L"Ngày mượn");
        SendMessage(cbSearchType, CB_SETCURSEL, 0, 0);

        CreateWindowW(L"STATIC", L"Nội dung tìm:", WS_VISIBLE | WS_CHILD,
            30, 60, 100, 25, hwnd, NULL, NULL, NULL);

        txtSearchInput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            140, 60, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Tìm kiếm", WS_VISIBLE | WS_CHILD,
            360, 60, 90, 25, hwnd, (HMENU)1, NULL, NULL);

        txtSearchResult = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            30, 100, 420, 220, hwnd, NULL, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            int sel = SendMessage(cbSearchType, CB_GETCURSEL, 0, 0);

            wchar_t wInput[256];
            GetWindowTextW(txtSearchInput, wInput, 256);
            char input[256];
            size_t c;
            wcstombs_s(&c, input, 256, wInput, _TRUNCATE);

            vector<string> result = TimKiemMuonSachTheoTieuChi(sel, input);

            if (result.empty()) {
                SetWindowTextW(txtSearchResult, L"Không tìm thấy kết quả.");
            }
            else {
                wstring output;
                for (auto& s : result)
                    output += wstring(s.begin(), s.end()) + L"\r\n";
                SetWindowTextW(txtSearchResult, output.c_str());
            }
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK SearchDueBookProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"STATIC", L"Chọn tiêu chí:", WS_VISIBLE | WS_CHILD,
            30, 20, 100, 25, hwnd, NULL, NULL, NULL);

        cbDueSearchType = CreateWindowW(L"COMBOBOX", NULL,
            CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
            140, 20, 180, 200, hwnd, NULL, NULL, NULL);

        SendMessage(cbDueSearchType, CB_ADDSTRING, 0, (LPARAM)L"MSDD");
        SendMessage(cbDueSearchType, CB_ADDSTRING, 0, (LPARAM)L"Mã sách");
        SendMessage(cbDueSearchType, CB_ADDSTRING, 0, (LPARAM)L"Tên sách");
        SendMessage(cbDueSearchType, CB_ADDSTRING, 0, (LPARAM)L"Tác giả");
        SendMessage(cbDueSearchType, CB_ADDSTRING, 0, (LPARAM)L"Ngày mượn");
        SendMessage(cbDueSearchType, CB_ADDSTRING, 0, (LPARAM)L"Ngày trả");
        SendMessage(cbDueSearchType, CB_SETCURSEL, 0, 0);

        CreateWindowW(L"STATIC", L"Nội dung tìm:", WS_VISIBLE | WS_CHILD,
            30, 60, 100, 25, hwnd, NULL, NULL, NULL);

        txtDueSearchInput = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            140, 60, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"BUTTON", L"Tìm kiếm", WS_VISIBLE | WS_CHILD,
            360, 60, 90, 25, hwnd, (HMENU)1, NULL, NULL);

        txtDueSearchResult = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            30, 100, 420, 220, hwnd, NULL, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            int sel = SendMessage(cbDueSearchType, CB_GETCURSEL, 0, 0);

            wchar_t wInput[256];
            GetWindowTextW(txtDueSearchInput, wInput, 256);
            char input[256];
            size_t c;
            wcstombs_s(&c, input, 256, wInput, _TRUNCATE);

            vector<string> result = TimKiemTraSachTheoTieuChi(sel, input);

            if (result.empty()) {
                SetWindowTextW(txtDueSearchResult, L"Không tìm thấy kết quả.");
            }
            else {
                wstring output;
                for (auto& s : result)
                    output += wstring(s.begin(), s.end()) + L"\r\n";
                SetWindowTextW(txtDueSearchResult, output.c_str());
            }
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK ListManagerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        listViewManager = CreateWindowW(WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | LVS_REPORT,
            30, 30, 620, 300, hwnd, (HMENU)2001, hInst, NULL);

        LVCOLUMN lvCol = { 0 };
        lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        lvCol.pszText = (LPWSTR)L"MCB"; lvCol.cx = 100;
        ListView_InsertColumn(listViewManager, 0, &lvCol);

        lvCol.pszText = (LPWSTR)L"Họ tên"; lvCol.cx = 150;
        ListView_InsertColumn(listViewManager, 1, &lvCol);

        lvCol.pszText = (LPWSTR)L"Giới tính"; lvCol.cx = 100;
        ListView_InsertColumn(listViewManager, 2, &lvCol);

        lvCol.pszText = (LPWSTR)L"Email"; lvCol.cx = 250;
        ListView_InsertColumn(listViewManager, 3, &lvCol);

        DisplayManagerList(hwnd);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
