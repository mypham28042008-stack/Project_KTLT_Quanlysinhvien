#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <string>
#include "../datastructures/LinkedList.h" 
#include "KetQuaHocTap.h"

class SinhVien {
private:
    std::string mssv;
    std::string hoTen;
    std::string maNganh; // Khóa ngoại dùng để tra cứu NganhHoc tương ứng
    std::string lop;
    std::string truongKhoa;
    std::string khoaHoc;
    int namNhapHoc;
    std::string ngaySinh;
    std::string gioiTinh;
    std::string noiSinh;
    std::string danToc;
    std::string sdt;
    std::string emailTruong;
    std::string emailCaNhan;
    std::string trangThaiHT;
    std::string phuongThucXT;
    std::string queQuan;

    LinkedList<KetQuaHocTap*> danhSachDiem;

public:
    SinhVien() : namNhapHoc(0) {}

    SinhVien(std::string id, std::string ten, std::string maNganh,
             std::string lop, std::string truongKhoa, std::string khoaHoc, int namNhapHoc,
             std::string ngaySinh, std::string gioiTinh, std::string noiSinh, std::string danToc,
             std::string sdt, std::string emailTruong, std::string emailCaNhan, std::string trangThaiHT,
             std::string phuongThucXT, std::string queQuan) {
        this->mssv = id;
        this->hoTen = ten;
        this->maNganh = maNganh;
        this->lop = lop;
        this->truongKhoa = truongKhoa;
        this->khoaHoc = khoaHoc;
        this->namNhapHoc = namNhapHoc;
        this->ngaySinh = ngaySinh;
        this->gioiTinh = gioiTinh;
        this->noiSinh = noiSinh;
        this->danToc = danToc;
        this->sdt = sdt;
        this->emailTruong = emailTruong;
        this->emailCaNhan = emailCaNhan;
        this->trangThaiHT = trangThaiHT;
        this->phuongThucXT = phuongThucXT;
        this->queQuan = queQuan;
    }

    ~SinhVien() {
        Node<KetQuaHocTap*>* current = danhSachDiem.getHead();
        while (current != nullptr) {
            delete current->data;
            current = current->next;
        }
    }

    bool themKetQuaHocTap(KetQuaHocTap* kq) {
        Node<KetQuaHocTap*>* current = danhSachDiem.getHead();
        while (current != nullptr) {
            if (current->data->getMaLop() == kq->getMaLop()) {
                return false;
            }
            current = current->next;
        }
        danhSachDiem.insertAtTail(kq);
        return true;
    }

    // Getters
    std::string getMSSV() const { return mssv; }
    std::string getHoTen() const { return hoTen; }
    std::string getMaNganh() const { return maNganh; }
    std::string getLop() const { return lop; }
    std::string getTruongKhoa() const { return truongKhoa; }
    std::string getKhoaHoc() const { return khoaHoc; }
    int getNamNhapHoc() const { return namNhapHoc; }
    std::string getNgaySinh() const { return ngaySinh; }
    std::string getGioiTinh() const { return gioiTinh; }
    std::string getNoiSinh() const { return noiSinh; }
    std::string getDanToc() const { return danToc; }
    std::string getSdt() const { return sdt; }
    std::string getEmailTruong() const { return emailTruong; }
    std::string getEmailCaNhan() const { return emailCaNhan; }
    std::string getTrangThaiHT() const { return trangThaiHT; }
    std::string getPhuongThucXT() const { return phuongThucXT; }
    std::string getQueQuan() const { return queQuan; }
    LinkedList<KetQuaHocTap*>& getDanhSachDiem() { return danhSachDiem; }

    // Setters
    void setMSSV(const std::string& val) { mssv = val; }
    void setHoTen(const std::string& val) { hoTen = val; }
    void setMaNganh(const std::string& val) { maNganh = val; }
    void setLop(const std::string& val) { lop = val; }
    void setTruongKhoa(const std::string& val) { truongKhoa = val; }
    void setKhoaHoc(const std::string& val) { khoaHoc = val; }
    void setNamNhapHoc(int val) { namNhapHoc = val; }
    void setNgaySinh(const std::string& val) { ngaySinh = val; }
    void setGioiTinh(const std::string& val) { gioiTinh = val; }
    void setNoiSinh(const std::string& val) { noiSinh = val; }
    void setDanToc(const std::string& val) { danToc = val; }
    void setSdt(const std::string& val) { sdt = val; }
    void setEmailTruong(const std::string& val) { emailTruong = val; }
    void setEmailCaNhan(const std::string& val) { emailCaNhan = val; }
    void setTrangThaiHT(const std::string& val) { trangThaiHT = val; }
    void setPhuongThucXT(const std::string& val) { phuongThucXT = val; }
    void setQueQuan(const std::string& val) { queQuan = val; }
    
    bool operator==(const SinhVien& other) const {
        return this->mssv == other.mssv;
    }
};

#endif // SINHVIEN_H
