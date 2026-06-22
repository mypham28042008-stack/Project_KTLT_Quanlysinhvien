#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "../datastructures/LinkedList.h"
#include "../datastructures/HashMap.h"
#include "../models/SinhVien.h"
#include "../models/HocPhan.h"
#include "../models/NganhHoc.h"
#include "../models/LopHocPhan.h"
#include <iostream>
#include <iomanip>
#include <utility>

class StudentManager {
private:
    HashMap<std::string, SinhVien*> danhSachSinhVien; // Key: MSSV
    HashMap<std::string, HocPhan*> danhSachHocPhan;   // Key: MaHP
    HashMap<std::string, NganhHoc*> danhSachNganhHoc; // Key: MaNganh
    HashMap<std::string, LopHocPhan*> danhSachLopHocPhan; // Key: MaLop

public:
    StudentManager() {}

    LinkedList<SinhVien*>* getAllSinhVien() const { return danhSachSinhVien.values(); }
    LinkedList<HocPhan*>* getAllHocPhan() const { return danhSachHocPhan.values(); }
    LinkedList<NganhHoc*>* getAllNganhHoc() const { return danhSachNganhHoc.values(); }
    LinkedList<LopHocPhan*>* getAllLopHocPhan() const { return danhSachLopHocPhan.values(); }

    ~StudentManager() {
        cleanUp();
    }

    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;

    void cleanUp() {
        // Free SinhVien objects
        LinkedList<SinhVien*>* svList = danhSachSinhVien.values();
        if (svList) {
            Node<SinhVien*>* current = svList->getHead();
            while (current != nullptr) {
                delete current->data; 
                current = current->next;
            }
            delete svList;
        }
        danhSachSinhVien.clear();

        // Free HocPhan objects
        LinkedList<HocPhan*>* hpList = danhSachHocPhan.values();
        if (hpList) {
            Node<HocPhan*>* current = hpList->getHead();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete hpList;
        }
        danhSachHocPhan.clear();

        // Free NganhHoc objects
        LinkedList<NganhHoc*>* nganhList = danhSachNganhHoc.values();
        if (nganhList) {
            Node<NganhHoc*>* current = nganhList->getHead();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete nganhList;
        }
        danhSachNganhHoc.clear();

        // Free LopHocPhan objects
        LinkedList<LopHocPhan*>* lhpList = danhSachLopHocPhan.values();
        if (lhpList) {
            Node<LopHocPhan*>* current = lhpList->getHead();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete lhpList;
        }
        danhSachLopHocPhan.clear();
    }

    // Nganh Hoc Management
    bool addNganhHoc(NganhHoc* nh) {
        if (nh == nullptr) return false;
        if (danhSachNganhHoc.get(nh->getMaNganh()) != nullptr) return false;
        danhSachNganhHoc.put(nh->getMaNganh(), nh);
        return true;
    }

    NganhHoc* findNganhHocByMa(const std::string& maNganh) const {
        return danhSachNganhHoc.get(maNganh);
    }

    bool updateNganhHoc(NganhHoc* nh) {
        if (nh == nullptr) return false;
        if (danhSachNganhHoc.get(nh->getMaNganh()) == nullptr) return false;
        danhSachNganhHoc.put(nh->getMaNganh(), nh); // put updates if key exists
        return true;
    }

    bool removeNganhHoc(const std::string& maNganh) {
        NganhHoc* nh = danhSachNganhHoc.get(maNganh);
        if (nh) {
            if (danhSachNganhHoc.remove(maNganh)) {
                delete nh;
                return true;
            }
        }
        return false;
    }

    // Học Phần Management
    bool addHocPhan(HocPhan* hp) {
        if (hp == nullptr) return false;
        if (danhSachHocPhan.get(hp->getMaHP()) != nullptr) return false;
        danhSachHocPhan.put(hp->getMaHP(), hp);
        return true;
    }

    HocPhan* findHocPhanByMa(const std::string& maHP) const {
        return danhSachHocPhan.get(maHP);
    }
    
    bool updateHocPhan(HocPhan* hp) {
        if (hp == nullptr) return false;
        if (danhSachHocPhan.get(hp->getMaHP()) == nullptr) return false;
        danhSachHocPhan.put(hp->getMaHP(), hp);
        return true;
    }

    bool removeHocPhan(const std::string& maHP) {
        HocPhan* hp = danhSachHocPhan.get(maHP);
        if (hp) {
            if (danhSachHocPhan.remove(maHP)) {
                delete hp;
                return true;
            }
        }
        return false;
    }
    // Sinh Viên Management
    bool addSinhVien(SinhVien* sv) {
        if (sv == nullptr) return false;
        if (danhSachSinhVien.get(sv->getMSSV()) != nullptr) return false;
        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }

    SinhVien* findSinhVienByMSSV(const std::string& mssv) const {
        return danhSachSinhVien.get(mssv);
    }

    bool updateSinhVien(SinhVien* sv) {
        if (sv == nullptr) return false;
        if (danhSachSinhVien.get(sv->getMSSV()) == nullptr) return false;
        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }

    bool removeSinhVien(const std::string& mssv) {
        SinhVien* sv = danhSachSinhVien.get(mssv);
        if (sv) {
            if (danhSachSinhVien.remove(mssv)) {
                delete sv;
                return true;
            }
        }
        return false;
    }

    size_t getStudentCount() const {
        return danhSachSinhVien.getSize();
    }

    // Lớp Học Phần Management
    bool addLopHocPhan(LopHocPhan* lhp) {
        if (lhp == nullptr) return false;
        if (danhSachLopHocPhan.get(lhp->getMaLop()) != nullptr) return false;
        danhSachLopHocPhan.put(lhp->getMaLop(), lhp);
        return true;
    }

    LopHocPhan* findLopHocPhanByMa(const std::string& maLop) const {
        return danhSachLopHocPhan.get(maLop);
    }
    
    bool removeLopHocPhan(const std::string& maLop) {
        LopHocPhan* lhp = danhSachLopHocPhan.get(maLop);
        if (lhp) {
            if (danhSachLopHocPhan.remove(maLop)) {
                delete lhp;
                return true;
            }
        }
        return false;
    }
    
    bool registerSinhVienToLop(const std::string& mssv, const std::string& maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        if (sv && lhp) {
            return lhp->addSinhVien(sv);
        }
        return false;
    }
    
    bool unregisterSinhVienFromLop(const std::string& mssv, const std::string& maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        if (sv && lhp) {
            return lhp->removeSinhVien(sv);
        }
        return false;
    }

    // Điểm (Kết Quả Học Tập) Management
    std::string xepLoaiDiemChu(float diemHP) const {
        if (diemHP >= 8.5) return "A";
        if (diemHP >= 8.0) return "B+";
        if (diemHP >= 7.0) return "B";
        if (diemHP >= 6.5) return "C+";
        if (diemHP >= 5.5) return "C";
        if (diemHP >= 5.0) return "D+";
        if (diemHP >= 4.0) return "D";
        return "F";
    }

    float quyDoiHe4(float diemHP) const {
        if (diemHP >= 8.5) return 4.0f;
        if (diemHP >= 8.0) return 3.5f;
        if (diemHP >= 7.0) return 3.0f;
        if (diemHP >= 6.5) return 2.5f;
        if (diemHP >= 5.5) return 2.0f;
        if (diemHP >= 5.0) return 1.5f;
        if (diemHP >= 4.0) return 1.0f;
        return 0.0f;
    }

    bool addDiem(const std::string& mssv, const std::string& maLop, const std::string& maHP, float diemQTr, float diemCK, float trongSoQTr = 0.3f) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if (!sv) return false;
        
        float diemHP = diemQTr * trongSoQTr + diemCK * (1.0f - trongSoQTr);
        KetQuaHocTap* kq = new KetQuaHocTap(maLop, maHP, diemQTr, diemCK, diemHP, xepLoaiDiemChu(diemHP), quyDoiHe4(diemHP));
        if (sv->themKetQuaHocTap(kq)) {
            return true;
        } else {
            delete kq;
            return false;
        }
    }

    bool updateDiem(const std::string& mssv, const std::string& maLop, float diemQTrMoi, float diemCKMoi, float trongSoQTr = 0.3f) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if (!sv) return false;
        
        Node<KetQuaHocTap*>* current = sv->getDanhSachDiem().getHead();
        while (current != nullptr) {
            if (current->data->getMaLop() == maLop) {
                float diemHP = diemQTrMoi * trongSoQTr + diemCKMoi * (1.0f - trongSoQTr);
                current->data->setDiemQTr(diemQTrMoi);
                current->data->setDiemCK(diemCKMoi);
                current->data->setDiemHP(diemHP);
                current->data->setDiemChu(xepLoaiDiemChu(diemHP));
                current->data->setThang4(quyDoiHe4(diemHP));
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool removeDiem(const std::string& mssv, const std::string& maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if (!sv) return false;
        
        Node<KetQuaHocTap*>* current = sv->getDanhSachDiem().getHead();
        while (current != nullptr) {
            if (current->data->getMaLop() == maLop) {
                KetQuaHocTap* kq = current->data;
                sv->getDanhSachDiem().remove(kq);
                delete kq;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // === MODULE 2: CHIET XUAT VA HIEN THI THONG TIN ===
    void displayBangDiemCaNhan(const std::string& mssv) const {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if (!sv) {
            std::cout << "Khong tim thay sinh vien co MSSV: " << mssv << std::endl;
            return;
        }

        std::cout << "\n=== BANG DIEM CA NHAN ===" << std::endl;
        std::cout << "MSSV: " << sv->getMSSV() << " | Ho ten: " << sv->getHoTen() << std::endl;
        std::cout << "Lop: " << sv->getLop() << " | Nganh: " << sv->getMaNganh() << std::endl;
        
        std::cout << "+" << std::string(103, '-') << "+" << std::endl;
        std::cout << "| " << std::left << std::setw(12) << "Ma Lop"
                  << " | " << std::setw(10) << "Ma HP"
                  << " | " << std::setw(25) << "Ten HP"
                  << " | " << std::setw(5) << "STC"
                  << " | " << std::setw(7) << "D.QTr"
                  << " | " << std::setw(7) << "D.CK"
                  << " | " << std::setw(7) << "D.HP"
                  << " | " << std::setw(5) << "Chu"
                  << " | " << std::setw(5) << "He 4"
                  << " |" << std::endl;
        std::cout << "+" << std::string(103, '-') << "+" << std::endl;

        Node<KetQuaHocTap*>* current = sv->getDanhSachDiem().getHead();
        if (current == nullptr) {
            std::cout << "| " << std::setw(101) << "Chua co du lieu diem" << " |" << std::endl;
        }

        while (current != nullptr) {
            KetQuaHocTap* kq = current->data;
            HocPhan* hp = findHocPhanByMa(kq->getMaHP());
            std::string tenHP = hp ? hp->getTenHP() : "N/A";
            if (tenHP.length() > 25) tenHP = tenHP.substr(0, 22) + "...";
            std::string stc = hp ? std::to_string(hp->getSoTinChi()) : "N/A";

            std::cout << "| " << std::left << std::setw(12) << kq->getMaLop()
                      << " | " << std::setw(10) << kq->getMaHP()
                      << " | " << std::setw(25) << tenHP
                      << " | " << std::setw(5) << stc
                      << " | " << std::fixed << std::setprecision(1) << std::setw(7) << kq->getDiemQTr()
                      << " | " << std::setw(7) << kq->getDiemCK()
                      << " | " << std::setw(7) << kq->getDiemHP()
                      << " | " << std::setw(5) << kq->getDiemChu()
                      << " | " << std::setw(5) << kq->getThang4()
                      << " |" << std::endl;
            current = current->next;
        }
        std::cout << "+" << std::string(103, '-') << "+" << std::endl;
    }

    void displayBangDiemLopHP(const std::string& maLop) const {
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        if (!lhp) {
            std::cout << "Khong tim thay lop hoc phan co ma: " << maLop << std::endl;
            return;
        }

        HocPhan* hp = findHocPhanByMa(lhp->getMaHP());
        std::string tenHP = hp ? hp->getTenHP() : "N/A";

        std::cout << "\n=== BANG DIEM LOP HOC PHAN ===" << std::endl;
        std::cout << "Ma Lop: " << lhp->getMaLop() << " | Hoc Ky: " << lhp->getHocKy() << std::endl;
        std::cout << "Hoc phan: [" << lhp->getMaHP() << "] " << tenHP << std::endl;
        
        std::cout << "+" << std::string(88, '-') << "+" << std::endl;
        std::cout << "| " << std::left << std::setw(10) << "MSSV"
                  << " | " << std::setw(20) << "Ho va ten"
                  << " | " << std::setw(10) << "Lop HC"
                  << " | " << std::setw(7) << "D.QTr"
                  << " | " << std::setw(7) << "D.CK"
                  << " | " << std::setw(7) << "D.HP"
                  << " | " << std::setw(7) << "D.Chu"
                  << " |" << std::endl;
        std::cout << "+" << std::string(88, '-') << "+" << std::endl;

        Node<SinhVien*>* currentSV = lhp->getDanhSachSinhVien().getHead();
        if (currentSV == nullptr) {
            std::cout << "| " << std::setw(86) << "Chua co sinh vien" << " |" << std::endl;
        }

        while (currentSV != nullptr) {
            SinhVien* sv = currentSV->data;
            // Find KQHT for this class
            KetQuaHocTap* kqTarget = nullptr;
            Node<KetQuaHocTap*>* kqNode = sv->getDanhSachDiem().getHead();
            while (kqNode != nullptr) {
                if (kqNode->data->getMaLop() == maLop) {
                    kqTarget = kqNode->data;
                    break;
                }
                kqNode = kqNode->next;
            }

            std::string hoTen = sv->getHoTen();
            if (hoTen.length() > 20) hoTen = hoTen.substr(0, 17) + "...";

            if (kqTarget) {
                std::cout << "| " << std::left << std::setw(10) << sv->getMSSV()
                          << " | " << std::setw(20) << hoTen
                          << " | " << std::setw(10) << sv->getLop()
                          << " | " << std::fixed << std::setprecision(1) << std::setw(7) << kqTarget->getDiemQTr()
                          << " | " << std::setw(7) << kqTarget->getDiemCK()
                          << " | " << std::setw(7) << kqTarget->getDiemHP()
                          << " | " << std::setw(7) << kqTarget->getDiemChu()
                          << " |" << std::endl;
            } else {
                std::cout << "| " << std::left << std::setw(10) << sv->getMSSV()
                          << " | " << std::setw(20) << hoTen
                          << " | " << std::setw(10) << sv->getLop()
                          << " | " << std::setw(7) << "N/A"
                          << " | " << std::setw(7) << "N/A"
                          << " | " << std::setw(7) << "N/A"
                          << " | " << std::setw(7) << "N/A"
                          << " |" << std::endl;
            }

            currentSV = currentSV->next;
        }
        std::cout << "+" << std::string(88, '-') << "+" << std::endl;
    }

    // === MODULE 3: THONG KE VA DANH GIA HOC LUC ===
    float calculateCPA(const std::string& mssv) const {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if (!sv) return 0.0f;

        float sumCPA = 0.0f;
        int creditsCPA = 0;

        LinkedList<KetQuaHocTap*> listCPA;
        Node<KetQuaHocTap*>* current = sv->getDanhSachDiem().getHead();

        while (current != nullptr) {
            KetQuaHocTap* kq = current->data;
            HocPhan* hp = findHocPhanByMa(kq->getMaHP());
            LopHocPhan* lhp = findLopHocPhanByMa(kq->getMaLop());

            if (hp != nullptr && lhp != nullptr) {
                float diem4 = kq->getThang4();

                bool foundInCPA = false;
                Node<KetQuaHocTap*>* cpaNode = listCPA.getHead();
                while (cpaNode != nullptr) {
                    if (cpaNode->data->getMaHP() == kq->getMaHP()) {
                        foundInCPA = true;
                        if (diem4 > cpaNode->data->getThang4()) {
                            cpaNode->data = kq;
                        }
                        break;
                    }
                    cpaNode = cpaNode->next;
                }

                if (!foundInCPA) {
                    listCPA.insertAtHead(kq);
                }
            }
            current = current->next;
        }

        Node<KetQuaHocTap*>* cpaNode = listCPA.getHead();
        while (cpaNode != nullptr) {
            KetQuaHocTap* kqCPA = cpaNode->data;
            HocPhan* hpCPA = findHocPhanByMa(kqCPA->getMaHP());
            if (hpCPA) {
                int stc = hpCPA->getSoTinChi();
                sumCPA += kqCPA->getThang4() * stc;
                creditsCPA += stc;
            }
            cpaNode = cpaNode->next;
        }

        float cpa = (creditsCPA > 0) ? (sumCPA / creditsCPA) : 0.0f;
        listCPA.clear();

        return cpa;
    }

    std::string evaluateHocLuc(float cpa) const {
        if (cpa >= 3.6f) return "Xuat sac";
        if (cpa >= 3.2f) return "Gioi";
        if (cpa >= 2.5f) return "Kha";
        if (cpa >= 2.0f) return "Trung binh";
        return "Yeu";
    }

    void displayThongKeHocLuc(const std::string& mssv) const {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if (!sv) {
            std::cout << "Khong tim thay sinh vien co MSSV: " << mssv << std::endl;
            return;
        }

        float cpa = calculateCPA(mssv);
        std::string hocLuc = evaluateHocLuc(cpa);

        std::cout << "\n=== THONG KE HOC LUC ===" << std::endl;
        std::cout << "MSSV: " << sv->getMSSV() << " | Ho ten: " << sv->getHoTen() << std::endl;
        std::cout << "Lop: " << sv->getLop() << std::endl;
        std::cout << std::string(45, '-') << std::endl;
        std::cout << "Diem trung binh tich luy (CPA): " << std::fixed << std::setprecision(2) << cpa << std::endl;
        std::cout << "Xep loai hoc luc (theo CPA): " << hocLuc << std::endl;
        std::cout << std::string(45, '-') << std::endl;
    }

    // Helpers for printing
    void printAll() const {
        LinkedList<SinhVien*>* list = danhSachSinhVien.values();
        if (list == nullptr || list->isEmpty()) {
            std::cout << "He thong chua co sinh vien nao!" << std::endl;
            if (list) delete list;
            return;
        }
        
        printTableHeader();
        Node<SinhVien*>* current = list->getHead();
        while (current != nullptr) {
            SinhVien* sv = current->data;
            std::cout << "| " << std::left << std::setw(10) << sv->getMSSV()
                      << " | " << std::setw(20) << sv->getHoTen().substr(0, 20)
                      << " | " << std::setw(10) << sv->getLop()
                      << " | " << std::setw(10) << sv->getNgaySinh()
                      << " | " << std::setw(12) << sv->getQueQuan().substr(0, 12)
                      << " |" << std::endl;
            current = current->next;
        }
        printTableFooter();
        delete list;
    }

    static void printTableHeader() {
        std::cout << "+" << std::string(73, '-') << "+" << std::endl;
        std::cout << "| " << std::left << std::setw(10) << "MSSV"
                  << " | " << std::setw(20) << "Ho va ten"
                  << " | " << std::setw(10) << "Lop"
                  << " | " << std::setw(10) << "Ngay sinh"
                  << " | " << std::setw(12) << "Que quan"
                  << " |" << std::endl;
        std::cout << "+" << std::string(73, '-') << "+" << std::endl;
    }

    static void printTableFooter() {
        std::cout << "+" << std::string(73, '-') << "+" << std::endl;
    }
};

#endif // STUDENTMANAGER_H
