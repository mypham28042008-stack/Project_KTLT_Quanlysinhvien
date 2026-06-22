#ifndef KETQUAHOCTAP_H
#define KETQUAHOCTAP_H

#include <string>
#include "HocPhan.h"
#include "NganhHoc.h"

class KetQuaHocTap {
private:
    std::string maLop;           
    std::string maHP;            
    float diemQTr;               
    float diemCK;                
    float diemHP;                
    std::string diemChu;         
    float thang4;                

public:
    KetQuaHocTap() : diemQTr(0.0f), diemCK(0.0f), diemHP(0.0f), thang4(0.0f) {}

    KetQuaHocTap(std::string lop, std::string hp, float qtr, float ck, float hp_diem, std::string chu, float t4) {
        maLop = lop; 
        maHP = hp; 
        diemQTr = qtr; 
        diemCK = ck; 
        diemHP = hp_diem; 
        diemChu = chu; 
        thang4 = t4;
    }

    // Logic tính học phí MỚI: Cần cả số tín (từ Học phần) và đơn giá (từ Ngành)
    float tinhTongHocPhi(HocPhan* hpInfo, NganhHoc* nganhInfo) const {
        if (hpInfo != nullptr && nganhInfo != nullptr && hpInfo->getMaHP() == this->maHP) {
            return hpInfo->getSoTinChiHocPhi() * nganhInfo->getHocPhiMotTin();
        }
        return 0.0f;
    }

    // Getters
    std::string getMaLop() const { return maLop; }
    std::string getMaHP() const { return maHP; }
    float getDiemQTr() const { return diemQTr; }
    float getDiemCK() const { return diemCK; }
    float getDiemHP() const { return diemHP; }
    std::string getDiemChu() const { return diemChu; }
    float getThang4() const { return thang4; }

    // Setters
    void setMaLop(const std::string& val) { maLop = val; }
    void setMaHP(const std::string& val) { maHP = val; }
    void setDiemQTr(float val) { diemQTr = val; }
    void setDiemCK(float val) { diemCK = val; }
    void setDiemHP(float val) { diemHP = val; }
    void setDiemChu(const std::string& val) { diemChu = val; }
    void setThang4(float val) { thang4 = val; }
};

#endif // KETQUAHOCTAP_H
