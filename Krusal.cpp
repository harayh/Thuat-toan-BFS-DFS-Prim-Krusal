#include <iostream>
#include <fstream>
#include <cstring>
#define MAX 20

int a[MAX][MAX]; // Ma trận kề của đồ thị
int n, m;        // Số đỉnh và số cạnh của đồ thị
std::ifstream os("matranKrusal.txt");
std::ofstream is("kq_thuat_toan_Krusal.txt");

// Khai báo tập E lưu trữ cạnh của đồ thị
int E1[MAX]; // lưu đỉnh 1
int E2[MAX]; // lưu đỉnh 2
int wE[MAX]; // lưu trọng số đỉnh 1 đến đỉnh 2
int nE = 0;  // Số phần tử trong tập E

// Khai báo tập T lưu trữ cây khung nhỏ nhất
int T1[MAX]; // lưu đỉnh 1
int T2[MAX]; // lưu đinh 2
int wT[MAX]; // lưu trọng số đỉnh 1 đến đỉnh 2
int nT = 0;  // Số phần tử trong tập T

// Đọc dữ liệu và tạo đồ thị

void input_to_create_graph()
{
    if (!os.is_open())
    {
        std::cout << "Không thể mở tập tin." << std::endl;
        return;
    }
    os >> n >> m;                 // Đọc số đỉnh và số cạnh
    std::memset(a, 0, sizeof(a)); // Khởi tạo ma trận kề ban đầu là 0
    for (int i = 0; i < m; i++)
    {
        int x, y, trongso;
        os >> x >> y >> trongso; // Đọc cạnh (x, y)
        a[x][y] = trongso;       // Đánh dấu cạnh (x, y) tồn tại
        a[y][x] = trongso;       // Đồng thời đánh dấu cả cạnh (y, x) vì đồ thị vô hướng
    }
}

// In ma trận kề của đồ thị
void in_graph()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}
// Kiểm tra xem đỉnh d đã tồn tại trong mảng D hay chưa
int TonTai(int d, int D[], int nD)
{
    for (int i = 0; i < nD; i++)
    {
        if (D[i] == d)
        {
            return 1; // Đã tồn tại đỉnh d trong mảng D
        }
    }
    return 0; // Không tồn tại đỉnh d trong mảng D
}
// Tạo tập cạnh E từ ma trận kề
void taoE()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
            {
                E1[nE] = i;       // Lưu đỉnh 1 của cạnh vào tập E1
                E2[nE] = j;       // Lưu đỉnh 2 của cạnh vào tập E2
                wE[nE] = a[i][j]; // Lưu trọng số của cạnh vào tập wE
                a[i][j] = 0;      // Đánh dấu cạnh (i, j) đã được chọn và được lưu vào tập E, nên giá trị trong ma trận kề là 0
                a[j][i] = 0;      // Đồng thời đánh dấu cả cạnh (j, i) vì đồ thị vô hướng
                nE++;             // Tăng số phần tử trong tập E lên 1
            }
        }
    }
}

// Sắp xếp tập cạnh E theo trọng số
void SapXepE()
{
    for (int i = 0; i < nE - 1; i++)
    {
        for (int j = i + 1; j < nE; j++)
        {
            if (wE[i] > wE[j])
            {
                std::swap(wE[i], wE[j]); // Hoán đổi trọng số
                std::swap(E1[i], E1[j]); // Hoán đổi đỉnh 1
                std::swap(E2[i], E2[j]); // Hoán đổi đỉnh 2
            }
        }
    }
}
// Xuất cây khung T và tổng trọng số
void output()
{
    int tong = 0;
    for (int i = 0; i < nT; i++)
    {
        std::cout << std::endl
                  << "(" << T1[i] << "," << T2[i] << ") = " << wT[i];
        tong += wT[i];
    }
    std::cout << "\nTong trong so = " << tong;
}

// Thuật toán Kruskal để tạo cây khung nhỏ nhất
void kruskal()
{
    // Duyệt qua tất cả các cạnh trong tập E (đã được sắp xếp theo trọng số)
    for (int i = 0; i < nE; i++)
    {
        // Kiểm tra xem đỉnh E1[i] và E2[i] đã tồn tại trong tập T hay chưa
        // Nếu cả hai đỉnh đã tồn tại trong tập T, bỏ qua cạnh này để tránh tạo chu trình
        if (TonTai(E1[i], T1, nT) == 1 && TonTai(E2[i], T2, nT) == 1)
        {
            continue;
        }
        if (TonTai(E1[i], T2, nT) == 1 && TonTai(E2[i], T1, nT) == 1)
        {
            continue;
        }

        // Nếu cạnh không tạo chu trình, thêm cạnh này vào tập T (cây khung nhỏ nhất)
        T1[nT] = E1[i];
        T2[nT] = E2[i];
        wT[nT] = wE[i];
        nT++;

        // Nếu số lượng cạnh trong tập T đã đạt đủ để tạo cây khung nhỏ nhất, thoát vòng lặp
        if (nT == n - 1)
            break;
    }
}
int main()
{
    input_to_create_graph(); // Đọc dữ liệu đồ thị từ tập tin và tạo ma trận kề
    in_graph();              // Hiển thị ma trận kề của đồ thị
    taoE();                  // Tạo tập cạnh E từ ma trận kề
    SapXepE();               // Sắp xếp tập cạnh E theo trọng số
    kruskal();               // Thực hiện thuật toán Kruskal để tạo cây khung nhỏ nhất

    output(); // In cây khung nhỏ nhất T và tổng trọng số

    return 0;
}
