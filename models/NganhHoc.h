#ifndef NGANHHOC_H
#define NGANHHOC_H

#include <string>

class NganhHoc {
private:
    std::string maNganh;
    std::string tenNganh;
    float hocPhiMotTin; 

public:
    NganhHoc() : hocPhiMotTin(0.0f) {}
    
    NganhHoc(std::string ma, std::string ten, float hocPhi) {
        maNganh = ma;
        tenNganh = ten;
        hocPhiMotTin = hocPhi;
    }

    std::string getMaNganh() const { return maNganh; }
    std::string getTenNganh() const { return tenNganh; }
    float getHocPhiMotTin() const { return hocPhiMotTin; }
    
    void setMaNganh(const std::string& ma) { maNganh = ma; }
    void setTenNganh(const std::string& ten) { tenNganh = ten; }
    void setHocPhiMotTin(float hp) { hocPhiMotTin = hp; }
};

#endif // NGANHHOC_H
