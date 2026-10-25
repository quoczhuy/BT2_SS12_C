#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100

// 1. Dinh nghia cau truc NhanVien
typedef struct {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
} NhanVien;

// 2. Khai bao nguyen mau ham (Function Prototypes)
void hienThiMenu();
int timKiemTheoMa(int ma, NhanVien ds[], int soLuong);
void hienThiDanhSach(NhanVien ds[], int soLuong);
int themNhanVien(NhanVien ds[], int soLuong);
void suaNhanVien(NhanVien ds[], int soLuong);
int xoaNhanVien(NhanVien ds[], int soLuong);

// Ham ho tro xu ly chuoi va bo dem
void xoaBoDem();
void xoaXuongDong(char str[]);

// ================= HÀM MAIN =================
int main() {
    NhanVien danhSach[MAX_NHAN_VIEN];
    int soLuong = 0;
    int luaChon;

    do {
        hienThiMenu();
        scanf("%d", &luaChon);
        xoaBoDem(); // Xoa phim Enter con xot lai trong bo dem

        switch (luaChon) {
            case 1:
                hienThiDanhSach(danhSach, soLuong);
                break;
            case 2:
                soLuong = themNhanVien(danhSach, soLuong);
                break;
            case 3:
                suaNhanVien(danhSach, soLuong);
                break;
            case 4:
                soLuong = xoaNhanVien(danhSach, soLuong);
                break;
            case 0:
                printf("=> Thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("=> Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while (luaChon != 0);

    return 0;
}

// ================= CÁC HÀM CHỨC NĂNG =================

// Hien thi menu
void hienThiMenu() {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
    printf("Nhap lua chon: ");
}

// Tim kiem nhan vien, tra ve index hoac -1
int timKiemTheoMa(int ma, NhanVien ds[], int soLuong) {
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].maNV == ma) {
            return i;
        }
    }
    return -1;
}

// Hien thi danh sach va tinh luong
void hienThiDanhSach(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\n=> Danh sach nhan vien hien dang trong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");
    for (int i = 0; i < soLuong; i++) {
        float tienPhat = (ds[i].phutMuon > 15) ? 50000.0 : 0.0;
        float tienOT = ds[i].soGioOT * (ds[i].luongCoBan / 160.0) * 1.5;
        float luongThucNhan = ds[i].luongCoBan + tienOT - tienPhat;

        printf("Ma NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.1f\n", ds[i].soGioOT);
        printf("Tien phat: %.0f\n", tienPhat);
        printf("Tien OT: %.0f\n", tienOT);
        printf("Luong thuc nhan: %.0f\n", luongThucNhan);
        printf("---------------------------\n");
    }
    printf("Tong so nhan vien: %d\n", soLuong);
}

// Them nhan vien moi
int themNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong >= MAX_NHAN_VIEN) {
        printf("\n=> Loi: He thong da dat gioi han %d nhan vien!\n", MAX_NHAN_VIEN);
        return soLuong;
    }

    NhanVien nv;
    int viTri;

    printf("\n--- THEM NHAN VIEN ---\n");
    
    // Nhap va kiem tra ma NV (Nguyen duong, khong trung)
    do {
        printf("Ma NV: ");
        scanf("%d", &nv.maNV);
        xoaBoDem();

        if (nv.maNV <= 0) {
            printf("=> Loi: Ma nhan vien phai la so nguyen duong!\n");
            continue;
        }
        
        viTri = timKiemTheoMa(nv.maNV, ds, soLuong);
        if (viTri != -1) {
            printf("=> Loi: Ma nhan vien da ton tai!\n");
        }
    } while (nv.maNV <= 0 || viTri != -1);

    // Nhap ten
    printf("Ho ten: ");
    fgets(nv.hoTen, sizeof(nv.hoTen), stdin);
    xoaXuongDong(nv.hoTen);

    // Nhap luong co ban
    do {
        printf("Luong co ban: ");
        scanf("%f", &nv.luongCoBan);
        if (nv.luongCoBan < 0) printf("=> Loi: Luong khong duoc am!\n");
    } while (nv.luongCoBan < 0);

    // Nhap phut muon
    do {
        printf("Phut di muon: ");
        scanf("%d", &nv.phutMuon);
        if (nv.phutMuon < 0) printf("=> Loi: So phut khong duoc am!\n");
    } while (nv.phutMuon < 0);

    // Nhap so gio OT
    do {
        printf("So gio OT: ");
        scanf("%f", &nv.soGioOT);
        if (nv.soGioOT < 0) printf("=> Loi: Gio OT khong duoc am!\n");
    } while (nv.soGioOT < 0);

    ds[soLuong] = nv;
    printf("\n=> Them nhan vien thanh cong!\n");
    
    return soLuong + 1;
}

// Cap nhat thong tin nhan vien
void suaNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\n=> Danh sach dang trong!\n");
        return;
    }

    int ma, viTri;
    printf("\n--- CAP NHAT NHAN VIEN ---\n");
    printf("Nhap ma NV can cap nhat: ");
    scanf("%d", &ma);
    xoaBoDem();

    viTri = timKiemTheoMa(ma, ds, soLuong);
    if (viTri == -1) {
        printf("\n=> Loi: Khong tim thay nhan vien ma %d!\n", ma);
        return;
    }

    printf("Cap nhat thong tin cho NV: %s\n", ds[viTri].hoTen);
    
    do {
        printf("Luong co ban moi: ");
        scanf("%f", &ds[viTri].luongCoBan);
    } while (ds[viTri].luongCoBan < 0);

    do {
        printf("Phut di muon moi: ");
        scanf("%d", &ds[viTri].phutMuon);
    } while (ds[viTri].phutMuon < 0);

    do {
        printf("So gio OT moi: ");
        scanf("%f", &ds[viTri].soGioOT);
    } while (ds[viTri].soGioOT < 0);

    printf("\n=> Cap nhat thong tin thanh cong!\n");
}

// Xoa nhan vien bang cach dich mang
int xoaNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("\n=> Danh sach dang trong!\n");
        return soLuong;
    }

    int ma, viTri;
    printf("\n--- XOA NHAN VIEN ---\n");
    printf("Ma NV can xoa: ");
    scanf("%d", &ma);
    xoaBoDem();

    viTri = timKiemTheoMa(ma, ds, soLuong);
    if (viTri == -1) {
        printf("\n=> Loi: Khong tim thay nhan vien ma %d!\n", ma);
        return soLuong;
    }

    // Dich chuyen cac phan tu phia sau len de ghi de
    for (int i = viTri; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    printf("\n=> Xoa nhan vien thanh cong!\n");
    return soLuong - 1;
}

// ================= CÁC HÀM HỖ TRỢ =================
void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void xoaXuongDong(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}