#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <stack>

int a[100][100];
int n, m;
std::ifstream os("matranDFS.txt");
void input_to_create_graph()
{
    if (!os.is_open())
    {
        std::cout << "Cannot open file." << std::endl;
        return;
    }
    os >> n >> m;
    std::memset(a, 0, sizeof(a));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        os >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1; // Một đồ thị vô hướng, nên cần đặt cả hai chiều.
    }
}
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
std::stack<int> Stack; // Khai báo một ngăn xếp kiểu int có tên là Stack
void init_stack()
{ // Hàm khởi tạo ngăn xếp
    while (!Stack.empty())
    {                // Kiểm tra nếu ngăn xếp không rỗng
        Stack.pop(); // Loại bỏ phần tử ở đỉnh ngăn xếp
    }
}

void push(int x)
{                  // Hàm thêm phần tử vào đỉnh ngăn xếp
    Stack.push(x); // Thêm giá trị x vào đỉnh ngăn xếp
}

int pop()
{ // Hàm loại bỏ và trả về phần tử ở đỉnh ngăn xếp
    if (Stack.empty())
    {                                             // Kiểm tra nếu ngăn xếp rỗng
        std::cout << "Stack empty." << std::endl; // In ra thông báo ngăn xếp rỗng
        return 0;                                 // Trả về giá trị không hợp lệ
    }
    else
    {
        int value = Stack.top(); // Lấy giá trị ở đỉnh ngăn xếp
        Stack.pop();             // Loại bỏ phần tử ở đỉnh ngăn xếp
        return value;            // Trả về giá trị ở đỉnh ngăn xếp
    }
}

int C[100]; // lưu trữ đỉnh chưa xét;
// 1 là chưa xét; 0 là đã xét
int dfs[100]; // lưu danh sách phần tử đã duyệt
int ndfs = 0; // chỉ số lưu đỉnh đã xét

void init_C()
{
    for (int i = 0; i < n; i++)
    {
        C[i] = 1; // Khởi tạo tất cả đỉnh là chưa xét
    }
}
void DFS(int s)
{
    push(s);       // Đẩy đỉnh bắt đầu vào ngăn xếp (Stack)
    dfs[ndfs] = s; // Lưu đỉnh vào mảng lưu kết quả DFS
    ndfs++;        // Tăng chỉ số lưu kết quả DFS
    int v = -1;    // Khởi tạo biến v là -1 để kiểm tra điều kiện kết thúc vòng lặp
    while (!Stack.empty())
    {                        // Lặp cho đến khi ngăn xếp không còn trống
        int u = Stack.top(); // Lấy phần tử đỉnh của ngăn xếp
        if (v == n)
        {          // Kiểm tra điều kiện kết thúc DFS trên đỉnh u
            pop(); // Loại bỏ đỉnh u khỏi ngăn xếp
        }
        for (v = 0; v < n; v++)
        { // Duyệt qua tất cả các đỉnh kề với đỉnh u
            if (a[u][v] != 0 && C[v] == 1)
            {                  // Nếu có cạnh (u, v) và đỉnh v chưa xét
                push(v);       // Đẩy đỉnh v vào ngăn xếp
                dfs[ndfs] = v; // Lưu đỉnh vào mảng lưu kết quả DFS
                ndfs++;        // Tăng chỉ số lưu kết quả DFS
                C[v] = 0;
                break; // Thoát khỏi vòng lặp for để tiếp tục duyệt đỉnh u
            }
        }
    }
}
void inDFS()
{
    for (int i = 0; i < ndfs; i++)
    {
        std::cout << dfs[i] << " ";
    }
    std::cout << std::endl;
}
int main()
{
    input_to_create_graph(); // Đọc dữ liệu từ tập tin và tạo ma trận kề
    in_graph();              // In ra ma trận kề
    init_stack();            // Khởi tạo ngăn xếp
    init_C();                // Khởi tạo mảng C với tất cả đỉnh là chưa xét
    DFS(0);                  // Gọi hàm DFS với đỉnh bắt đầu là 0

    std::cout << "Danh sách DFS: ";
    inDFS();

    return 0;
}
