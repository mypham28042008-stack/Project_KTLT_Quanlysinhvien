#ifndef HOCPHAN_H
#define HOCPHAN_H

#include <string>

class HocPhan {
private:
    std::string maHP;            
    std::string tenHP;          
    int soTinChi;              
    int soTinChiHocPhi;         

public:
    HocPhan() : soTinChi(0), soTinChiHocPhi(0) {}
    
    HocPhan(std::string ma, std::string ten, int stc, int stc_hp) {
        maHP = ma; 
        tenHP = ten; 
        soTinChi = stc; 
        soTinChiHocPhi = stc_hp; 
    }

    // Getters
    std::string getMaHP() const { return maHP; }
    std::string getTenHP() const { return tenHP; }
    int getSoTinChi() const { return soTinChi; }
    int getSoTinChiHocPhi() const { return soTinChiHocPhi; }
    
    // Setters
    void setMaHP(const std::string& val) { maHP = val; }
    void setTenHP(const std::string& val) { tenHP = val; }
    void setSoTinChi(int val) { soTinChi = val; }
    void setSoTinChiHocPhi(int val) { soTinChiHocPhi = val; }
};

#endif // HOCPHAN_H
