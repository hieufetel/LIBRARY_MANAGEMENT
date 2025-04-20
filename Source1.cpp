#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <list>

#pragma warning (disable: 26495)
#pragma warning (disable: 4267)
#pragma warning (disable: 4715)

using namespace std;

string ManagerName = "";
bool CheckName(string name) {
    if (name.empty() == 1) {
        cout << "Ban chua nhap ten nhan vien!" << endl;
        return false;
    }
    if (name.length() > 30) {
        cout << "Ban khong duoc nhap qua 30 ky tu!" << endl;
        return false;
    }
    else {
        for (int i = 0; i < name.length(); i++) {
            if (name[0] == ' ') {
                cout << "Ten khong duoc co dau cach o truoc ten!" << endl;
                return false;
            }
        }
        for (int i = 0; i < name.length(); i++) {
            if (name.back() == ' ') {
                cout << "Ten khong duoc co dau cach o cuoi cung!" << endl;
                return false;
            }
        }
        for (int i = 0; i < name.length(); i++) {
            if (name[i] == ' ' && name[i + 1] == ' ') {
                cout << "Giua cac ten khong duoc co nhieu hon 1 dau cach!" << endl;
                return false;
            }
        }
        for (int i = 0; i < name.length(); i++) {
            if (name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || name[i] == ' ') {
                continue;
            }
            else {
                cout << "Ten khong duoc co ky tu nao khac ky tu chu cai ALPHABET!" << endl;
                return false;
            }
        }
        return true;
    }
}
string StandardName(string& name) {
    name[0] = toupper(name[0]);
    for (int i = 1; i < name.length(); i++)
    {
        if (name[i] == ' ')
        {
            name[i + 1] = toupper(name[i + 1]);
            i++;
        }
        else if (name[i] != ' ')
        {
            name[i] = tolower(name[i]);
        }
    }
    return name;
}
string StandardDate(string& date) {
    int demgach = 0, day, month, year, dd, mm;
    string dayy, monthh, datee;
    for (int i = 0; i < date.length(); i++) {
        if (date[i] == '/') {
            demgach++;
        }
    }
    if (demgach == 2) {
        dd = date.find('/', 0);
        mm = date.find('/', dd + 1);
        day = stoi(date.substr(0, dd));						//int day1 = stoi(date1.substr(0, 2));
        month = stoi(date.substr(dd + 1, mm - dd - 1));		//int month1 = stoi(date1.substr(3, 2));
        year = stoi(date.substr(mm + 1, 4));				//int year1 = stoi(date1.substr(6, 4));
        if (year >= 1970) {
            if (day > 0 && day < 10)
                dayy = '0' + to_string(day);
            else 
                dayy = to_string(day);
            if (month > 0 && month < 10)
                monthh = '0' + to_string(month);
            else 
                monthh = to_string(month);
            date = dayy + '/' + monthh + '/' + to_string(year);
            return date;
        }
        else
            cout << "Nam nhap vao phai tu nam chuan, 1970 tro di. Nhap lai!" << endl;
        return date;
    }
    else
        return date;
}
void BacktoMenu(string tenMenu) {
    cout << "Quay lai Menu " << tenMenu << " sau 2 giay." << endl;
    cout << "--- 1 ---" << endl;
    Sleep(1000);
    cout << "--- 2 ---" << endl;
    Sleep(1000);
}

class MANAGER {
private:
    string MCB;
    string HoTen;
    string Sex;
    string Mail;
    string Password;
public:
    MANAGER(string MCB, string HoTen, string Sex, string Mail, string Password) {
        this->MCB = MCB;
        this->HoTen = HoTen;
        this->Sex = Sex;
        this->Mail = Mail;
        this->Password = Password;
    }
    string getMCB() {
        return MCB;
    }
    string getHoTen() {
        return HoTen;
    }
    string getSex() {
        return Sex;
    }
    string getMail() {
        return Mail;
    }
    string getPassword() {
        return Password;
    }
    void setMCB(string MCB) { this->MCB = MCB; }
    void setHoTen(string HoTen) { this->HoTen = HoTen; }
    void setSex(string Sex) { this->Sex = Sex; }
    void setMail(string Mail) { this->Mail = Mail; }
    void setPassword(string Password) { this->Password = Password; }
        void luuThongTinQuanLy(string id, string name, string sex, string email, string password) {
        ofstream file("Manager.txt", ios::app);
        if (!file) return;
        file << id << "," << name << "," << sex << "," << email << "," << password << endl;
        file.close();
    }
};
vector<MANAGER*> danhsachQuanLy;

class LIBRARY {
private:
    string BookID;
    string BookName;
    string Author;
    string InDay;
    string BookMode;
public:
    LIBRARY(string BookID, string BookName, string Author, string InDay, string BookMode) {
        this->BookID = BookID;
        this->BookName = BookName;
        this->Author = Author;
        this->InDay = InDay;
        this->BookMode = BookMode;
    }
    string getBookID() {
        return BookID;
    }
    string getBookName() {
        return BookName;
    }
    string getAuthor() {
        return Author;
    }
    string getInDay() {
        return InDay;
    }
    string getBookMode() {
        return BookMode;
    }
    void setBookId(string BookID) { this->BookID = BookID; }
    void setBookName(string BookName) { this->BookName = BookName; }
    void setAuthor(string Author) { this->Author = Author; }
    void setInDay(string InDay) { this->InDay = InDay; }
    void setBookMode(string mode) { this->BookMode = BookMode; }
 
};
vector<LIBRARY*> danhsachSach;

class READER {
private:
    int MSDD;
    string HoTen;
    string Khoa;
public:
    READER(int MSDD, string HoTen, string Khoa) {
        this->MSDD = MSDD;
        this->HoTen = HoTen;
        this->Khoa = Khoa;
    }
    int getMSDD() {
        return MSDD;
    }
    string getHoTen() {
        return HoTen;
    }
    string getKhoa() {
        return Khoa;
    }
    void setMSDD(int MSDD) { this->MSDD = MSDD; }
    void setHoTen(string HoTen) { this->HoTen = HoTen; }
    void setKhoa(string Khoa) { this->Khoa = Khoa; }
};
vector<READER*> danhsachDocGia;
class OPERATE {
public:
    int msdd;
    string hoTen;
    string idSach;
    string tenSach;
    string tacGia;
    string ngayMuon;
    string trangThaiMuon;
    string ngayTra;
    string trangThaiTra;
    list<OPERATE> danhsachMuonSach;
    list<OPERATE> danhsachTraSach;
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    bool CheckDate(string date) {
        int demgach = 0, day, month, year, dd, mm;
        if (date.length() > 10 || date.length() < 10) {
            return false;
        }
        else {
            for (int i = 0; i < date.length(); i++) {
                if (date[i] == '/') {
                    demgach++;
                }
            }
            if (demgach != 2) {
                return false;
            }
            dd = date.find('/', 0);
            mm = date.find('/', dd + 1);
            day = stoi(date.substr(0, dd));						//int day1 = stoi(date1.substr(0, 2));
            month = stoi(date.substr(dd + 1, mm - dd - 1));		//int month1 = stoi(date1.substr(3, 2));
            year = stoi(date.substr(mm + 1, 4));				//int year1 = stoi(date1.substr(6, 4));
            if (year < 1 || month < 1 || month > 12 || day < 1)
                return false;
            int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31 };
            if (month == 2 && isLeapYear(year))
                return day <= 29;
            return day <= daysInMonth[month];
        }
    }
    bool CheckID(string id) {
        if (id.length() != 6) {
            return false;
        }
        for (int i = 0; i < id.length(); i++) {
            if (id[i] >= '0' && id[i] <= '9' || id[i] >= 'A' && id[i] <= 'Z') {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }
    bool CheckReturnbookDay(string ngayMuon, string ngayTra) {
        int dayM = stoi(ngayMuon.substr(0, 2));
        int monthM = stoi(ngayMuon.substr(3, 2));
        int yearM = stoi(ngayMuon.substr(6, 4));

        int dayT = stoi(ngayTra.substr(0, 2));
        int monthT = stoi(ngayTra.substr(3, 2));
        int yearT = stoi(ngayTra.substr(6, 4));
        if (yearT > yearM) return true;
        else if (yearT == yearM) {
            if (monthT > monthM) return true;
            else if (monthT == monthM) {
                return dayT >= dayM;
            }
        }
        return false;
    }
    bool CheckExistingId(string id) {
        bool fl = false;
        docThongTinSach();
        for (auto& sach : danhsachSach) {
            if (sach->getBookID() == id) {
                fl = true;
                return true;
            }
        }
        if (fl == false) {
            return false;
        }
    }
    bool CheckMSDD(int MSDD) {
        if (MSDD > 10000000 && MSDD < 100000000) {
            return true;
        }
        return false;
    }
    int laySoTuID(const string& id) {
        if (id.length() < 6) return 0;
        string so = id.substr(2);  // Lấy 4 ký số cuối
        return stoi(so);
    }
    int soSanhNgay(const string& a, const string& b) {
        auto extractDate = [](const string& s, int& day, int& month, int& year) -> bool {
            if (s.length() != 10 || s[2] != '/' || s[5] != '/') return false;
            try {
                day = stoi(s.substr(0, 2));
                month = stoi(s.substr(3, 2));
                year = stoi(s.substr(6, 4));
                return true;
            }
            catch (...) {
                return false;
            }
            };
        int dayA, monthA, yearA;
        int dayB, monthB, yearB;

        if (!extractDate(a, dayA, monthA, yearA)) return 0;
        if (!extractDate(b, dayB, monthB, yearB)) return 0;

        if (yearA != yearB)
            return yearA - yearB;
        else if (monthA != monthB)
            return monthA - monthB;
        else
            return dayA - dayB;
    }

    void luuThongTinSach(string id, string ten, string tacGia, string NgayNhapSach, string BookMode) {
        ofstream file;
        file.open("Sach.txt", ios::app);
        if (!file) {
            cout << "Khong the mo file de ghi!" << endl;
        }
        else {
            file << id << ',' << ten << ',' << tacGia << ',' << StandardDate(NgayNhapSach) << ',' << BookMode << endl;
        }
        file.close();
    }
    void docThongTinSach() {
        danhsachSach.clear();
        ifstream file;
        file.open("Sach.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            string id, ten, tacGia, nam, mode;
            size_t pos = 0, pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
            pos = line.find(',');
            id = line.substr(0, pos);
            pos1 = line.find(',', pos + 1);
            ten = line.substr(pos + 1, pos1 - pos - 1);
            pos2 = line.find(',', pos1 + 1);
            tacGia = line.substr(pos1 + 1, pos2 - pos1 - 1);
            pos3 = line.find(',', pos2 + 1);
            nam = line.substr(pos2 + 1, pos3 - pos2 - 1);
            pos4 = line.find('\n', pos3 + 1);
            mode = line.substr(pos3 + 1);
            LIBRARY* sach = new LIBRARY(id, ten, tacGia, nam, mode);
            danhsachSach.push_back(sach);
        }
        file.close();
    }
    void luuThongTinDocGia(int MSDD, string ten, string khoahoc) {
        ofstream write;
        write.open("Docgia.txt", ios::app);
        if (!write) {
            cout << "Khong the mo file de ghi!" << endl;
        }
        else {
            write << to_string(MSDD) << ',' << ten << ',' << khoahoc << endl;
        }
        write.close();
    }
    void docThongTinDocGia() {
        danhsachDocGia.clear();
        ifstream read;
        read.open("Docgia.txt");
        if (!read.is_open()) {
            cout << "Khong the mo file de doc!" << endl;
            return;
        }
        else {
            string line;
            while (getline(read, line)) {
                int MSDD;
                string ten, khoa;
                size_t pos = 0, pos1 = 0, pos2 = 0;
                pos = line.find(',');
                MSDD = stoi(line.substr(0, pos));
                pos1 = line.find(',', pos + 1);
                ten = line.substr(pos + 1, pos1 - pos - 1);
                pos2 = line.find('\n', pos1 + 1);
                khoa = line.substr(pos1 + 1, pos2 - pos1 - 1);
                READER* docgia = new READER(MSDD, ten, khoa);
                danhsachDocGia.push_back(docgia);
            }
        }
        read.close();
    }
    void luuThongTinMuonSach(int msdd, string hoTen, string idSach, string tenSach, string tacGia, string ngayMuon, string trangThaiMuon) {
        ofstream file;
        file.open("MuonSach.txt", ios::app);
        if (!file) {
            cout << "Khong the mo file de ghi!" << endl;
        }
        else {
            file << to_string(msdd) << ',' << hoTen << ',' << idSach << ',' << tenSach << ',' << tacGia << ',' << ngayMuon << ',' << trangThaiMuon << endl;
        }
        file.close();
    }
    void docThongTinMuonSach() {
        danhsachMuonSach.clear();
        ifstream file;
        OPERATE muon;
        file.open("MuonSach.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            size_t pos = 0, pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0, pos5 = 0, pos6 = 0;
            pos = line.find(',');
            muon.msdd = stoi(line.substr(0, pos));
            pos1 = line.find(',', pos + 1);
            muon.hoTen = line.substr(pos + 1, pos1 - pos - 1);
            pos2 = line.find(',', pos1 + 1);
            muon.idSach = line.substr(pos1 + 1, pos2 - pos1 - 1);
            pos3 = line.find(',', pos2 + 1);
            muon.tenSach = line.substr(pos2 + 1, pos3 - pos2 - 1);
            pos4 = line.find(',', pos3 + 1);
            muon.tacGia = line.substr(pos3 + 1, pos4 - pos3 - 1);
            pos5 = line.find(',', pos4 + 1);
            muon.ngayMuon = line.substr(pos4 + 1, pos5 - pos4 - 1);
            pos6 = line.find('\n', pos5 + 1);
            muon.trangThaiMuon = line.substr(pos5 + 1, pos6 - pos5 - 1);
            muon.ngayTra = "", muon.trangThaiTra = "";
            danhsachMuonSach.push_back(muon);
        }
        file.close();
    }
    void docThongTinTraSach() {
        danhsachTraSach.clear();
        ifstream file;
        OPERATE tra;
        file.open("TraSach.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            size_t pos = 0, pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0, pos5 = 0, pos6 = 0, pos7 = 0, pos8 = 0;
            pos = line.find(',');
            tra.msdd = stoi(line.substr(0, pos));
            pos1 = line.find(',', pos + 1);
            tra.hoTen = line.substr(pos + 1, pos1 - pos - 1);
            pos2 = line.find(',', pos1 + 1);
            tra.idSach = line.substr(pos1 + 1, pos2 - pos1 - 1);
            pos3 = line.find(',', pos2 + 1);
            tra.tenSach = line.substr(pos2 + 1, pos3 - pos2 - 1);
            pos4 = line.find(',', pos3 + 1);
            tra.tacGia = line.substr(pos3 + 1, pos4 - pos3 - 1);
            pos5 = line.find(',', pos4 + 1);
            tra.ngayMuon = line.substr(pos4 + 1, pos5 - pos4 - 1);
            pos6 = line.find(',', pos5 + 1);
            tra.trangThaiMuon = line.substr(pos5 + 1, pos6 - pos5 - 1);
            pos7 = line.find(',', pos6 + 1);
            tra.ngayTra = line.substr(pos6 + 1, pos7 - pos6 - 1);
            pos8 = line.find('\n', pos7 + 1);
            tra.trangThaiTra = line.substr(pos7 + 1, pos8 - pos7 - 1);
            danhsachTraSach.push_back(tra);
        }
        file.close();
    }
    void docThongTinQuanLy() {
        danhsachQuanLy.clear();
        ifstream file;
        file.open("Manager.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            string mcb, hoten, gioitinh, mail, matkhau;
            size_t pos = 0, pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
            pos = line.find(',');
            mcb = line.substr(0, pos);
            pos1 = line.find(',', pos + 1);
            hoten = line.substr(pos + 1, pos1 - pos - 1);
            pos2 = line.find(',', pos1 + 1);
            gioitinh = line.substr(pos1 + 1, pos2 - pos1 - 1);
            pos3 = line.find(',', pos2 + 1);
            mail = line.substr(pos2 + 1, pos3 - pos2 - 1);
            pos4 = line.find('\n', pos3 + 1);
            matkhau = line.substr(pos3 + 1, pos4 - pos3 - 1);
            MANAGER* qly = new MANAGER(mcb, hoten, gioitinh, mail, matkhau);
            danhsachQuanLy.push_back(qly);
        }
        file.close();
    }
    void sortBooksByID(vector<LIBRARY*>& danhsachSach) {
        for (size_t i = 0; i < danhsachSach.size() - 1; ++i) {
            for (size_t j = 0; j < danhsachSach.size() - i - 1; ++j) {
                string prefixA = danhsachSach[j]->getBookID().substr(0, 2);
                string prefixB = danhsachSach[j + 1]->getBookID().substr(0, 2);
                if (prefixA != prefixB) {
                    if (prefixA > prefixB)
                        swap(danhsachSach[j], danhsachSach[j + 1]);
                }
                else {
                    int numA = laySoTuID(danhsachSach[j]->getBookID());
                    int numB = laySoTuID(danhsachSach[j + 1]->getBookID());
                    if (numA > numB)
                        swap(danhsachSach[j], danhsachSach[j + 1]);
                }
            }
        }
        ofstream file("Sach.txt");
        if (!file) {
            cout << "Khong the mo file de ghi!" << endl;
            return;
        }
        file << "";
        file.close();
        for (auto& sach : danhsachSach) {
            luuThongTinSach(sach->getBookID(), sach->getBookName(), sach->getAuthor(), sach->getInDay(), sach->getBookMode());
        }
    }
    void sortBooksByName(vector<LIBRARY*>& danhsachSach) {
        for (size_t i = 0; i < danhsachSach.size() - 1; ++i) {
            for (size_t j = 0; j < danhsachSach.size() - i - 1; ++j) {
                if (danhsachSach[j]->getBookName() > danhsachSach[j + 1]->getBookName()) {
                    swap(danhsachSach[j], danhsachSach[j + 1]);
                }
            }
        }
        ofstream file;
        file.open("Sach.txt");
        file << "";
        file.close();
        for (auto& sach : danhsachSach) {
            luuThongTinSach(sach->getBookID(), sach->getBookName(), sach->getAuthor(), sach->getInDay(), sach->getBookMode());
        }
    }
    void sortBooksByAuthor(vector<LIBRARY*>& danhsachSach) {
        for (size_t i = 0; i < danhsachSach.size() - 1; ++i) {
            for (size_t j = 0; j < danhsachSach.size() - i - 1; ++j) {
                if (danhsachSach[j]->getAuthor() > danhsachSach[j + 1]->getAuthor()) {
                    swap(danhsachSach[j], danhsachSach[j + 1]);
                }
            }
        }
        ofstream file;
        file.open("Sach.txt");
        file << "";
        file.close();
        for (auto& i : danhsachSach) {
            luuThongTinSach(i->getBookID(), i->getBookName(), i->getAuthor(), i->getInDay(), i->getBookMode());
        }
    }
    void sortBooksByInDay(vector<LIBRARY*>& danhsachSach) {
        for (size_t i = 0; i < danhsachSach.size() - 1; ++i) {
            for (size_t j = 0; j < danhsachSach.size() - i - 1; ++j) {
                int cmp = soSanhNgay(danhsachSach[j]->getInDay(), danhsachSach[j + 1]->getInDay());
                if (cmp < 0) { 
                    swap(danhsachSach[j], danhsachSach[j + 1]);
                }
            }
        }
        ofstream file;
        file.open("Sach.txt");
        file << "";
        file.close();
        for (auto& i : danhsachSach) {
            luuThongTinSach(i->getBookID(), i->getBookName(), i->getAuthor(), i->getInDay(), i->getBookMode());
        }
    }
    void sortBooksByMode(vector<LIBRARY*>& danhsachSach) {
        for (size_t i = 0; i < danhsachSach.size() - 1; ++i) {
            for (size_t j = 0; j < danhsachSach.size() - i - 1; ++j) {
                if (danhsachSach[j]->getBookMode() > danhsachSach[j + 1]->getBookMode()) {
                    swap(danhsachSach[j], danhsachSach[j + 1]);
                }
            }
        }
        ofstream file;
        file.open("Sach.txt");
        file << "";
        file.close();
        for (auto& i : danhsachSach) {
            luuThongTinSach(i->getBookID(), i->getBookName(), i->getAuthor(), i->getInDay(), i->getBookMode());
        }
    }
    void luuThongTinQuanLy(string id, string name, string sex, string email, string password) {
        ofstream file("Manager.txt", ios::app);
        if (!file) return;
        file << id << "," << name << "," << sex << "," << email << "," << password << endl;
        file.close();
    }
};

class ACCOUNT {
public:
    string MCB;
    string Name;
    string Sex;
    string Mail;
    string Password;

};
class REGISTER : public ACCOUNT {
public:
    bool checkMCB(string MCB) {
        ifstream readID;
        readID.open("Manager.txt", ios::app);
        if (readID.is_open()) {
            string line;
            while (getline(readID, line)) {
                size_t pos = line.find(',');			//MCB
                if (pos != SIZE_MAX && (line.substr(0, pos) == MCB)) {
                    readID.close();
                    return true;
                }
            }
            readID.close();
        }
        return false;
    }
    bool CheckEmail(string email) {
        string mailname, addressmail;
        size_t pos = email.find("@");	//tim @
        if (pos == SIZE_MAX) {
            return false;
        }
        mailname = email.substr(0, pos);
        addressmail = email.substr(pos);
        if (mailname.length() < 6 || mailname.length() > 30) {
            return false;
        }
        int dotsearch = addressmail.find(".");		//tim . sau @
        if (addressmail.length() < 10 || dotsearch == SIZE_MAX) {
            return false;
        }
        if (!(mailname[0] >= 'a' && mailname[0] <= 'z' || mailname[0] >= 'A' && mailname[0] <= 'Z' || mailname[0] >= '0' && mailname[0] <= '9')) {
            return false;
        }
        for (int i = 1; i < mailname.length(); i++) {
            if (mailname[i] >= 'a' && mailname[i] <= 'z' || mailname[i] >= 'A' && mailname[i] <= 'Z' || mailname[i] >= '0' && mailname[i] <= '9' || mailname[i] == '.') {
                continue;
            }
            if (mailname[i] == '.' && mailname[i + 1] == '.') {
                return false;
            }
            else {
                return false;
            }
        }
        if (!(addressmail.back() >= 'a' && addressmail.back() >= 'z' || addressmail.back() >= 'A' && addressmail.back() >= 'Z')) {
            return false;
        }
        for (int j = 1; j < addressmail.length(); j++) {
            if (addressmail[j] >= 'a' && addressmail[j] <= 'z' || addressmail[j] >= 'A' && addressmail[j] <= 'Z' || addressmail[j] >= '0' && addressmail[j] <= '9' || addressmail[j] == '.') {
                continue;
            }
            if (addressmail[j] == '.' && addressmail[j + 1] == '.') {
                return false;
            }
            else {
                return false;
            }
        }
        return true;
    }
    bool CheckPassword(string password) {
        if (password.length() >= 8 && password.length() <= 16) {
            for (int i = 0; i < password.length(); i++) {
                if (password[i] == ' ') {
                    cout << "Password khong duoc chua ky tu khoang trang!" << endl;
                    return false;
                }
                else {
                    return true;
                }
            }
        }
        else {
            cout << "Password phai tu (8 - 16) ky tu." << endl;
            return false;
        }
    }
};
class LOGIN : public ACCOUNT {
public:
    bool checkmcb(string MCB) {
        ifstream readid;
        readid.open("Manager.txt", ios::out);
        if (readid.is_open()) {
            string line;
            while (getline(readid, line)) {
                size_t pos = line.find(','); //ID
                if (pos != SIZE_MAX && (line.substr(0, pos) == MCB)) {
                    readid.close();
                    return true;
                }
            }
            readid.close();
        }
        return false;
    }
    bool checkmail(string Mail) {
        ifstream readmail;
        readmail.open("Manager.txt");
        if (readmail.is_open()) {
            string line;
            while (getline(readmail, line)) {
                size_t pos = line.find(',');            //ID
                size_t pos1 = line.find(',', pos + 1);  //name
                size_t pos2 = line.find(',', pos1 + 1); //sex
                size_t pos3 = line.find(',', pos2 + 1);	//email
                if (Mail == line.substr(pos2 + 1, pos3 - pos2 - 1)) {
                    readmail.close();
                    return true;
                }
            }
            readmail.close();
        }
        return false;
    }
    bool checkpass(string username, string Password) {
        ifstream readpass;
        readpass.open("Manager.txt");
        if (readpass.is_open()) {
            string line;
            while (getline(readpass, line)) {
                size_t pos = line.find(',');            //MCB
                size_t pos1 = line.find(',', pos + 1);  //name
                size_t pos2 = line.find(',', pos1 + 1); //sex
                size_t pos3 = line.find(',', pos2 + 1);	//email
                size_t pos4 = line.find('\n', pos3 + 1);//pass
                if ((pos != SIZE_MAX && (line.substr(0, pos) == username)) || (pos3 != SIZE_MAX && line.substr(pos2 + 1, pos3 - pos2 - 1) == username)) {
                    if (Password == line.substr(pos3 + 1, pos4 - pos3 - 1)) {
                        ManagerName = line.substr(pos + 1, pos1 - pos - 1);
                        readpass.close();
                        return true;
                    }
                }
            }
            readpass.close();
        }
        return false;
    }
};
