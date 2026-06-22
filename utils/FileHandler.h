#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../core/StudentManager.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

class FileHandler {
private:
    // Hàm phân tách dòng CSV, bỏ qua dấu phẩy nếu nó nằm trong ngoặc kép " "
    static std::vector<std::string> parseCSVLine(const std::string& line) {
        std::vector<std::string> result;
        std::string cell = "";
        bool inQuotes = false;
        
        for (char c : line) {
            if (c == '\"') {
                inQuotes = !inQuotes; // Đảo trạng thái nếu gặp ngoặc kép
            } else if (c == ',' && !inQuotes) {
                // Trim whitespace optional
                result.push_back(cell);
                cell = "";
            } else {
                cell += c;
            }
        }
        result.push_back(cell);
        return result;
    }

    // Hàm làm sạch MSSV bị lỗi ".0" từ Excel
    static std::string cleanMSSV(std::string mssv) {
        if (mssv.length() > 2 && mssv.substr(mssv.length() - 2) == ".0") {
            return mssv.substr(0, mssv.length() - 2);
        }
        return mssv;
    }
    // Hàm làm sạch MaLop bị lỗi ".0" từ Excel
    static std::string cleanMaLop(std::string maLop) {
        if (maLop.length() > 2 && maLop.substr(maLop.length() - 2) == ".0") {
            return maLop.substr(0, maLop.length() - 2);
        }
        return maLop;
    }

public:
    static bool loadNganhHoc(const std::string& filePath, StudentManager& manager) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file NganhHoc: " << filePath << std::endl;
            return false;
        }

        std::string line;
        if (!std::getline(file, line)) return false;

        size_t loadedCount = 0;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            std::vector<std::string> fields = parseCSVLine(line);
            if (fields.size() < 3) continue;

            try {
                NganhHoc* nh = new NganhHoc(fields[0], fields[1], std::stof(fields[2]));
                if (manager.addNganhHoc(nh)) loadedCount++;
                else delete nh;
            } catch (...) {}
        }
        std::cout << "-> Da tai " << loadedCount << " Nganh Hoc tu " << filePath << std::endl;
        return true;
    }

    static bool loadHocPhan(const std::string& filePath, StudentManager& manager) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file HocPhan: " << filePath << std::endl;
            return false;
        }

        std::string line;
        if (!std::getline(file, line)) return false;

        size_t loadedCount = 0;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            std::vector<std::string> fields = parseCSVLine(line);
            if (fields.size() < 4) continue; 

            try {
                int stc = fields[2].empty() ? 0 : std::stoi(fields[2]);
                int stc_hp = fields[3].empty() ? 0 : std::stoi(fields[3]);
                HocPhan* hp = new HocPhan(fields[0], fields[1], stc, stc_hp);
                if (manager.addHocPhan(hp)) loadedCount++;
                else delete hp;
            } catch (...) {}
        }
        std::cout << "-> Da tai " << loadedCount << " Hoc Phan tu " << filePath << std::endl;
        return true;
    }

    static bool loadSinhVien(const std::string& filePath, StudentManager& manager) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file SinhVien: " << filePath << std::endl;
            return false;
        }

        std::string line;
        if (!std::getline(file, line)) return false;

        size_t loadedCount = 0;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            std::vector<std::string> fields = parseCSVLine(line);
            if (fields.size() < 17) continue;

            try {
                std::string mssv = cleanMSSV(fields[0]);
                SinhVien* sv = nullptr;

                if (fields.size() >= 18) {
                    // Format file that (co 18 cot, cot 3 la Nganh hoc bi thua)
                    int namNhapHoc = fields[7].empty() ? 0 : static_cast<int>(std::stof(fields[7]));
                    sv = new SinhVien(
                        mssv, fields[1], fields[2], fields[4], fields[5], fields[6], 
                        namNhapHoc, fields[8], fields[9], fields[10], fields[11], 
                        fields[12], fields[13], fields[14], fields[15], fields[16], fields[17]
                    );
                } else {
                    // Format file mock data (17 cot)
                    int namNhapHoc = fields[6].empty() ? 0 : std::stoi(fields[6]);
                    sv = new SinhVien(
                        mssv, fields[1], fields[2], fields[3], fields[4], fields[5], 
                        namNhapHoc, fields[7], fields[8], fields[9], fields[10], 
                        fields[11], fields[12], fields[13], fields[14], fields[15], fields[16]
                    );
                }

                if (sv != nullptr) {
                    if (manager.addSinhVien(sv)) {
                        loadedCount++;
                    } else {
                        delete sv;
                    }
                }
            } catch (...) {}
        }
        std::cout << "-> Da tai " << loadedCount << " Sinh Vien tu " << filePath << std::endl;
        return true;
    }

    // Thêm tham số defaultMaHP để cứu cánh cho file điểm bị khuyết mã HP
    static bool loadDiem(const std::string& filePath, StudentManager& manager, const std::string& defaultMaHP) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file Diem: " << filePath << std::endl;
            return false;
        }

        std::string line;
        if (!std::getline(file, line)) return false; 

        size_t loadedCount = 0;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            std::vector<std::string> fields = parseCSVLine(line);
            
            // Expected format could vary, but according to user's real data:
            // MaHP = row[0], MaLop = row[2], MSSV = row[3]
            // DiemQTr = row[7], DiemCK = row[8], DiemHP = row[9], DiemChu = row[10], Thang4 = row[11]
            // But my existing Mock Data is: MSSV,MaLop,MaHP,DiemQTr,DiemCK,DiemHP,DiemChu,Thang4
            // Wait, the user's snippet says:
            // string maHP = row[0].empty() ? defaultMaHP : row[0];
            // string maLop = row[2];
            // string mssv = cleanMSSV(row[3]);
            // float diemQTr = row[7]
            
            // Because my program also needs to load my Mock Data, I will adapt based on the number of columns.
            // If the user uses their real files, they might have 12+ columns.
            // My Mock Data has 8 columns: MSSV (0), MaLop (1), MaHP (2), DiemQTr (3), DiemCK (4), DiemHP (5), DiemChu (6), Thang4 (7)
            
            if (fields.size() >= 12) {
                // Parse user's real file format
                try {
                    std::string maHP = fields[0].empty() ? defaultMaHP : fields[0];
                    std::string maLop = cleanMaLop(fields[2]);
                    std::string mssv = cleanMSSV(fields[3]);
                    
                    float diemQTr = fields[7].empty() ? 0.0f : std::stof(fields[7]);
                    float diemCK  = fields[8].empty() ? 0.0f : std::stof(fields[8]);
                    float diemHP  = fields[9].empty() ? 0.0f : std::stof(fields[9]);
                    std::string diemChu = fields[10];
                    float thang4  = fields[11].empty() ? 0.0f : std::stof(fields[11]);
                    
                    SinhVien* sv = manager.findSinhVienByMSSV(mssv);
                    if (sv != nullptr) {
                        if (!manager.findLopHocPhanByMa(maLop)) {
                            std::string hocKy = (maLop.find("99") != std::string::npos) ? "20232" : "20231";
                            manager.addLopHocPhan(new LopHocPhan(maLop, maHP, hocKy));
                        }
                        KetQuaHocTap* kq = new KetQuaHocTap(maLop, maHP, diemQTr, diemCK, diemHP, diemChu, thang4);
                        if (sv->themKetQuaHocTap(kq)) {
                            manager.registerSinhVienToLop(mssv, maLop);
                            loadedCount++;
                        } else {
                            delete kq;
                        }
                    }
                } catch (...) {}
            } else if (fields.size() >= 8) {
                // Parse Mock Data format
                try {
                    std::string mssv = cleanMSSV(fields[0]);
                    std::string maLop = fields[1];
                    std::string maHP = fields[2].empty() ? defaultMaHP : fields[2];
                    
                    float diemQTr = fields[3].empty() ? 0.0f : std::stof(fields[3]);
                    float diemCK  = fields[4].empty() ? 0.0f : std::stof(fields[4]);
                    float diemHP  = fields[5].empty() ? 0.0f : std::stof(fields[5]);
                    std::string diemChu = fields[6];
                    float thang4  = fields[7].empty() ? 0.0f : std::stof(fields[7]);
                    
                    SinhVien* sv = manager.findSinhVienByMSSV(mssv);
                    if (sv != nullptr) {
                        if (!manager.findLopHocPhanByMa(maLop)) {
                            std::string hocKy = (maLop.find("99") != std::string::npos) ? "20232" : "20231";
                            manager.addLopHocPhan(new LopHocPhan(maLop, maHP, hocKy));
                        }
                        KetQuaHocTap* kq = new KetQuaHocTap(maLop, maHP, diemQTr, diemCK, diemHP, diemChu, thang4);
                        if (sv->themKetQuaHocTap(kq)) {
                            manager.registerSinhVienToLop(mssv, maLop);
                            loadedCount++;
                        } else {
                            delete kq;
                        }
                    }
                } catch (...) {}
            }
        }
        std::cout << "-> Da tai " << loadedCount << " ban ghi Diem tu " << filePath << std::endl;
        return true;
    }
    // ==========================================
    // SAVE FUNCTIONS
    // ==========================================
    static bool saveNganhHoc(const std::string& filePath, const StudentManager& manager) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) return false;
        file << "MaNganh,TenNganh,HocPhiMotTin\n";
        LinkedList<NganhHoc*>* list = manager.getAllNganhHoc();
        if (list) {
            Node<NganhHoc*>* current = list->getHead();
            while (current != nullptr) {
                NganhHoc* nh = current->data;
                file << nh->getMaNganh() << "," << nh->getTenNganh() << "," << nh->getHocPhiMotTin() << "\n";
                current = current->next;
            }
            delete list;
        }
        file.close();
        std::cout << "-> Da luu danh sach Nganh Hoc vao " << filePath << std::endl;
        return true;
    }

    static bool saveHocPhan(const std::string& filePath, const StudentManager& manager) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) return false;
        file << "MaHP,TenHP,SoTinChi,SoTinChiHocPhi\n";
        LinkedList<HocPhan*>* list = manager.getAllHocPhan();
        if (list) {
            Node<HocPhan*>* current = list->getHead();
            while (current != nullptr) {
                HocPhan* hp = current->data;
                file << hp->getMaHP() << "," << hp->getTenHP() << "," << hp->getSoTinChi() << "," << hp->getSoTinChiHocPhi() << "\n";
                current = current->next;
            }
            delete list;
        }
        file.close();
        std::cout << "-> Da luu danh sach Hoc Phan vao " << filePath << std::endl;
        return true;
    }

    static bool saveSinhVien(const std::string& filePath, const StudentManager& manager) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) return false;
        file << "MSSV,HoTen,MaNganh,Lop,TruongKhoa,KhoaHoc,NamNhapHoc,NgaySinh,GioiTinh,NoiSinh,DanToc,SDT,EmailTruong,EmailCaNhan,TrangThaiHT,PhuongThucXT,QueQuan\n";
        LinkedList<SinhVien*>* list = manager.getAllSinhVien();
        if (list) {
            Node<SinhVien*>* current = list->getHead();
            while (current != nullptr) {
                SinhVien* sv = current->data;
                file << sv->getMSSV() << "," << sv->getHoTen() << "," << sv->getMaNganh() << "," << sv->getLop() << ","
                     << sv->getTruongKhoa() << "," << sv->getKhoaHoc() << "," << sv->getNamNhapHoc() << "," << sv->getNgaySinh() << ","
                     << sv->getGioiTinh() << "," << sv->getNoiSinh() << "," << sv->getDanToc() << "," << sv->getSdt() << ","
                     << sv->getEmailTruong() << "," << sv->getEmailCaNhan() << "," << sv->getTrangThaiHT() << ","
                     << sv->getPhuongThucXT() << "," << sv->getQueQuan() << "\n";
                current = current->next;
            }
            delete list;
        }
        file.close();
        std::cout << "-> Da luu danh sach Sinh Vien vao " << filePath << std::endl;
        return true;
    }

    static bool saveDiem(const std::string& filePath, const StudentManager& manager) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::string altPath = (filePath.length() >= 3 && filePath.substr(0, 3) == "../") ? filePath.substr(3) : "../" + filePath;
            file.open(altPath);
        }
        if (!file.is_open()) return false;
        file << "MSSV,MaLop,MaHP,DiemQTr,DiemCK,DiemHP,DiemChu,Thang4\n";
        LinkedList<SinhVien*>* list = manager.getAllSinhVien();
        if (list) {
            Node<SinhVien*>* current = list->getHead();
            while (current != nullptr) {
                SinhVien* sv = current->data;
                Node<KetQuaHocTap*>* kqNode = sv->getDanhSachDiem().getHead();
                while (kqNode != nullptr) {
                    KetQuaHocTap* kq = kqNode->data;
                    file << sv->getMSSV() << "," << kq->getMaLop() << "," << kq->getMaHP() << ","
                         << kq->getDiemQTr() << "," << kq->getDiemCK() << "," << kq->getDiemHP() << ","
                         << kq->getDiemChu() << "," << kq->getThang4() << "\n";
                    kqNode = kqNode->next;
                }
                current = current->next;
            }
            delete list;
        }
        file.close();
        std::cout << "-> Da luu toan bo Diem vao " << filePath << std::endl;
        return true;
    }
};

#endif // FILEHANDLER_H
