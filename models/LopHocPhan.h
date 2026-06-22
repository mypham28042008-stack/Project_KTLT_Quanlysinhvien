#ifndef LOPHOCPHAN_H
#define LOPHOCPHAN_H

#include <string>
#include "../datastructures/LinkedList.h"

// Forward declaration to avoid circular dependencies
class SinhVien;

class LopHocPhan {
private:
    std::string maLop;
    std::string maHP;
    std::string hocKy;
    LinkedList<SinhVien*> danhSachSinhVien;

public:
    LopHocPhan() {}
    
    LopHocPhan(std::string ml, std::string mh, std::string hk) 
        : maLop(ml), maHP(mh), hocKy(hk) {}

    // Getters
    std::string getMaLop() const { return maLop; }
    std::string getMaHP() const { return maHP; }
    std::string getHocKy() const { return hocKy; }
    LinkedList<SinhVien*>& getDanhSachSinhVien() { return danhSachSinhVien; }

    // Setters
    void setMaLop(const std::string& val) { maLop = val; }
    void setMaHP(const std::string& val) { maHP = val; }
    void setHocKy(const std::string& val) { hocKy = val; }

    // Sinh Vien Management within Class
    bool addSinhVien(SinhVien* sv) {
        if (!sv) return false;
        Node<SinhVien*>* current = danhSachSinhVien.getHead();
        while (current != nullptr) {
            if (current->data == sv) return false;
            current = current->next;
        }
        danhSachSinhVien.insertAtTail(sv);
        return true;
    }

    // Removing by pointer
    bool removeSinhVien(SinhVien* sv) {
        if (sv) {
            return danhSachSinhVien.remove(sv);
        }
        return false;
    }
};

#endif // LOPHOCPHAN_H
