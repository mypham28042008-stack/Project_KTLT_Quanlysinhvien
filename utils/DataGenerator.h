#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

class DataGenerator {
public:
    static bool generateMockData(size_t recordCount) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // 1. Generate NganhHoc (NganhHoc.csv)
        std::string nhFile = "NganhHoc.csv";
        std::ofstream outNH(nhFile);
        if (!outNH.is_open()) return false;
        outNH << "MaNganh,TenNganh,HocPhiMotTin\n";
        outNH << "IT1,Khoa hoc may tinh,400\n";
        outNH << "IT2,Ky thuat may tinh,420\n";
        outNH << "IT3,An toan thong tin,400\n";
        outNH << "IT-E6,Cong nghe thong tin Chat luong cao,800\n";
        outNH.close();
        std::cout << "-> Da tao file: " << nhFile << std::endl;

        // 2. Generate HocPhan (HocPhan.csv)
        std::string hpFile = "HocPhan.csv";
        std::ofstream outHP(hpFile);
        if (!outHP.is_open()) return false;
        outHP << "MaHP,TenHP,SoTinChi,SoTinChiHocPhi\n";
        outHP << "MI1141,Dai so,3,3\n";
        outHP << "MI1111,Giai tich 1,4,4\n";
        outHP << "IT1110,Tin hoc dai cuong,4,4\n";
        outHP << "LL1111,Triet hoc Mac-Lenin,3,3\n";
        outHP.close();
        std::cout << "-> Da tao file: " << hpFile << std::endl;

        // 3. Generate SinhVien (DanhSachSinhVien.csv) - 17 fields
        std::string svFile = "DanhSachSinhVien.csv";
        std::ofstream outSV(svFile);
        if (!outSV.is_open()) return false;
        
        outSV << "MSSV,HoTen,MaNganh,Lop,TruongKhoa,KhoaHoc,NamNhapHoc,NgaySinh,GioiTinh,NoiSinh,DanToc,SDT,EmailTruong,EmailCaNhan,TrangThaiHT,PhuongThucXT,QueQuan\n";
        
        const std::string listHo[] = {"Nguyen", "Tran", "Le", "Pham", "Hoang", "Phan", "Vu", "Dang", "Bui", "Do"};
        const std::string listDem[] = {"Van", "Thi", "Quang", "Minh", "Quoc", "Anh", "Duc", "Ngoc"};
        const std::string listTen[] = {"Anh", "Binh", "Cuong", "Dung", "Dong", "Giang", "Hai", "Hung", "Huy", "Khoa", "Linh", "Long", "Mai", "Trang"};
        const std::string listTinh[] = {"Ha Noi", "Hai Phong", "Da Nang", "Quang Ninh", "Nghe An"};
        const std::string listMaNganh[] = {"IT1", "IT2", "IT3", "IT-E6"};

        long long startingMSSV = 20250001;
        for (size_t i = 0; i < recordCount; ++i) {
            std::string mssv = std::to_string(startingMSSV + i);
            std::string hoTen = listHo[std::rand() % 10] + " " + listDem[std::rand() % 8] + " " + listTen[std::rand() % 14];
            std::string gioiTinh = (std::rand() % 2 == 0) ? "Nam" : "Nu";
            std::string ngaySinh = "01/01/2005";
            std::string queQuan = listTinh[std::rand() % 5];
            std::string maNganh = listMaNganh[std::rand() % 4];
            
            outSV << mssv << "," << hoTen << "," << maNganh << ",IT-01,Truong CNTT&TT,K68,2023,"
                  << ngaySinh << "," << gioiTinh << "," << queQuan << ",Kinh,0912345678,"
                  << mssv << "@sis.hust.edu.vn," << mssv << "@gmail.com,Dang hoc,THPT," << queQuan << "\n";
        }
        outSV.close();
        std::cout << "-> Da tao file: " << svFile << " (" << recordCount << " ban ghi)" << std::endl;

        // 4. Generate Diem
        std::string diemFiles[] = {"Diem_DaiSo.csv", "Diem_GT1.csv", "Diem_NhapMon.csv", "Diem_Triet.csv"};
        std::string maHPs[] = {"MI1141", "MI1111", "IT1110", "LL1111"};
        
        for (int i = 0; i < 4; ++i) {
            std::ofstream outDiem(diemFiles[i]);
            if (!outDiem.is_open()) continue;
            outDiem << "MSSV,MaLop,MaHP,DiemQTr,DiemCK,DiemHP,DiemChu,Thang4\n";
            
            for (size_t j = 0; j < recordCount; ++j) {
                if (std::rand() % 10 < 2 && j != 0) continue; // 20% dropped the class, guarantee student 0

                std::string mssv = std::to_string(startingMSSV + j);
                std::string maLop = "14320" + std::to_string(i);
                float diemQTr = 4.0f + static_cast<float>(std::rand() % 61) / 10.0f; 
                float diemCK = 4.0f + static_cast<float>(std::rand() % 61) / 10.0f;
                
                // Cố tình cho sinh viên đầu tiên (20250001) điểm thấp để học lại
                if (j == 0) {
                    diemQTr = 3.0f;
                    diemCK = 3.0f;
                }

                float diemHP = (diemQTr * 0.3f) + (diemCK * 0.7f);
                std::string diemChu = "C";
                float thang4 = 2.0f;

                if (diemHP >= 8.5) { diemChu = "A"; thang4 = 4.0f; }
                else if (diemHP >= 8.0) { diemChu = "B+"; thang4 = 3.5f; }
                else if (diemHP >= 7.0) { diemChu = "B"; thang4 = 3.0f; }
                else if (diemHP >= 6.5) { diemChu = "C+"; thang4 = 2.5f; }
                else if (diemHP >= 5.5) { diemChu = "C"; thang4 = 2.0f; }
                else if (diemHP >= 5.0) { diemChu = "D+"; thang4 = 1.5f; }
                else if (diemHP >= 4.0) { diemChu = "D"; thang4 = 1.0f; }
                else { diemChu = "F"; thang4 = 0.0f; }

                outDiem << mssv << "," << maLop << "," << maHPs[i] << "," 
                        << diemQTr << "," << diemCK << "," << diemHP << "," 
                        << diemChu << "," << thang4 << "\n";
                        
                // TC_4.2: Khử nhiễu học lại
                // Sinh viên học lại môn cũ với mức điểm cao hơn ở lớp khác (kỳ mới)
                if (j == 0) {
                    std::string maLopHocLai = "143299" + std::to_string(i); // Lớp học lại
                    float diemQTrHL = 9.0f;
                    float diemCKHL = 9.0f;
                    float diemHPHL = 9.0f;
                    outDiem << mssv << "," << maLopHocLai << "," << maHPs[i] << "," 
                            << diemQTrHL << "," << diemCKHL << "," << diemHPHL << "," 
                            << "A" << "," << 4.0f << "\n";
                }
            }
            outDiem.close();
            std::cout << "-> Da tao file diem: " << diemFiles[i] << std::endl;
        }

        return true;
    }
};

#endif // DATAGENERATOR_H
