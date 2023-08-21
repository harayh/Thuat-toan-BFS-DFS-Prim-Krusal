#include <iostream>
#include <fstream>
#include <cstring>
#include <limits.h>
#define MAX 20

int a[MAX][MAX]; // Ma trận kề của đồ thị
int n, m;        // Số đỉnh và số cạnh của đồ thị

std::ifstream os("matranprim.txt");
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
// Khai báo tập E lưu trữ cạnh của đồ thị
int E1[MAX]; // lưu đỉnh 1
int E2[MAX]; // lưu đỉnh 2
int wE[MAX]; // lưu trọng số từ đỉnh 1 đến đỉnh 2
int nE = 0;  // Số phần tử trong tập E

// Khai báo tập T lưu trữ cây khung nhỏ nhất
int T1[MAX]; // lưu đỉnh 1
int T2[MAX]; // lưu đỉnh 2
int wT[MAX]; // lưu trọng số đỉnh 1 đến 2
int nT = 0;  // Số phần tử trong tập T
// Kiểm tra xem đỉnh d đã tồn tại trong mảng D hay chưa
int TonTai(int d, int D[], int nD)
{
    for (int i = 0; i < nD; i++)
        if (D[i] == d)
            return 1; // có đỉnh trong tập đỉnh
    return 0;         // không có đỉnh trong tập đỉnh
}

// Xóa phần tử tại vị trí i trong tập E
void XoaViTriE(int i)
{
    // Duyệt qua các phần tử từ vị trí i đến nE - 1
    for (int j = i; j < nE - 1; j++)
    {
        // Dịch chuyển các phần tử sang trái để ghi đè lên phần tử tại vị trí j
        E1[j] = E1[j + 1];
        E2[j] = E2[j + 1];
        wE[j] = wE[j + 1];
    }
    // Giảm số lượng phần tử trong tập E đi 1
    nE--;
}
// Xóa cạnh (u, v) khỏi tập E
void XoaCanhE(int u, int v)
{
    for (int i = 0; i < nE; i++)
        if (E1[i] == u && E2[i] == v)
        { // kiểm tra 2 đỉnh trong tập đỉnh có tồn tại 2 đỉnh u v không
            XoaViTriE(i);
            break;
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
// Thuật toán Prim để tìm cây khung nhỏ nhất
void prim(int s)
{
    int u = s, min, i, d1, d2;
    while (nT < n - 1)
    { // Khi nào nT == n - 1 thì dừng (đã lấy hết tất cả các phần tử trong tập Tập E)
        // Bước 1: Tìm tất cả các cạnh (u, v) kề với đỉnh u

        for (int v = 0; v < n; v++)
            if (a[u][v] != 0)
                if (TonTai(v, T2, nT) == 0)
                {
                    // Thêm cạnh (u, v) vào tập E
                    E1[nE] = u;
                    E2[nE] = v;
                    wE[nE] = a[u][v];
                    nE++;
                }
        // Bước 2: Tìm cạnh có trọng số nhỏ nhất và chưa thuộc tập T
        min = INT_MAX;
        for (i = 0; i < nE; i++)
            if (TonTai(E2[i], T2, nT) == 0 && wE[i] < min)
            {
                min = wE[i];
                d1 = E1[i];
                d2 = E2[i];
            }
        // Bước 3: Thêm cạnh (d1, d2) vào tập T và loại bỏ khỏi đồ thị
        T1[nT] = d1;
        T2[nT] = d2;
        wT[nT] = a[d1][d2];
        a[d1][d2] = 0;
        a[d2][d1] = 0;
        nT++;
        XoaCanhE(d1, d2); // Loại bỏ cạnh khỏi tập E
        u = d2;           // Chọn đỉnh d2 làm đỉnh kế tiếp để xây dựng cây khung
    }
}
int main()
{
    input_to_create_graph();                // Đọc dữ liệu đồ thị từ tập tin và tạo ma trận kề
    in_graph();                             // Hiển thị ma trận kề của đồ thị
    prim(0);                                // Áp dụng thuật toán Prim bắt đầu từ đỉnh 0
    std::cout << "\nCay khung nho nhat:\n"; // Xuất thông báo cho biết đầu ra tiếp theo sẽ là cây khung nhỏ nhất
    output();                               // Xuất cây khung nhỏ nhất và tổng trọng số
    return 0;
}
