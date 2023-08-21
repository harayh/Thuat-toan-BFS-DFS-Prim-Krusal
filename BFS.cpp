#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

int a[100][100];
int n, m;
int p, w;
// Đọc dữ liệu từ tập tin matran.txt để tạo ma trận
std::ifstream os("matranBFS.txt");

// Hàm để nhập dữ liệu từ tập tin và tạo ma trận kề
void input_to_creat_magic()
{
    os >> n >> m; // Đọc số đỉnh (n) và số cạnh (m)

    // Khởi tạo ma trận kề ban đầu là 0
    std::memset(a, 0, sizeof(a));

    for (int i = 0; i < m; i++)
    {
        int x, y;
        os >> x >> y; // Đọc cạnh (x, y)
        a[x][y] = 1;  // Đánh dấu cạnh (x, y) tồn tại
        a[y][x] = 1;  // Đồng thời đánh dấu cả cạnh (y, x) vì đồ thị vô hướng
    }
}

// Hàm để in ma trận kề
void in_magic()
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

int Queue[100];
int rear, front;
// Hàm để khởi tạo hàng đợi
void init_queue()
{
    rear = front = -1;
}
// Hàm để đẩy phần tử vào hàng đợi
void push(int Queue[], int x)
{
    if (rear - front == 99)
    {
        std::cout << "Queue day\n";
    }
    else
    {
        if (front == -1)
            front = 0;
        if (rear == 99)
        {
            for (int i = front; i <= rear; i++)
                Queue[i - front] = Queue[i];
            rear = 99 - 1 - front;
            front = 0;
        }
        Queue[++rear] = x;
        return;
    }
}
// Hàm để lấy phần tử ra khỏi hàng đợi
int pop()
{
    int value;
    if (front == -1)
    {
        std::cout << "Queue empty." << std::endl;
        return 0;
    }
    else
    {
        value = Queue[front++];
        if (front > rear)
        {
            front = rear = -1;
        }
        return value;
    }
}
// Hàm để in các phần tử trong hàng đợi

int C[100];   // Lưu trữ đỉnh chưa xét; 1 là chưa xét, 0 là đã xét
int bfs[100]; // Lưu danh sách phần tử đã duyệt
int nbfs = 0; // Chỉ số lưu đỉnh đã xét

// Hàm để khởi tạo mảng C với tất cả đỉnh là chưa xét
void init_C()
{
    for (int i = 0; i < n; i++)
    {
        C[i] = 1;
    }
}
// Hàm để in danh sách BFS
void inBFS()
{
    for (int i = 0; i < nbfs; i++)
    {
        std::cout << bfs[i] << " ";
    }
}
// Thuật toán BFS để duyệt đồ thị
void BFS(int v) // v là đỉnh bắt đầu
{
    push(Queue, v); // Đẩy đỉnh v vào hàng đợi (Queue) để bắt đầu BFS
    C[v] = 0;       // Đánh dấu đỉnh v đã xét (đã thêm vào hàng đợi)
    while (front != -1)
    {
        p = pop(); // Lấy ra đỉnh đầu tiên khỏi hàng đợi để xét

        bfs[nbfs] = p; // Lưu đỉnh vào mảng lưu kết quả BFS
        nbfs++;
        for (w = 0; w < n; w++)
        {
            if (C[w] && a[p][w] == 1)
            {                   // Nếu đỉnh w chưa xét và có cạnh (p, w)
                push(Queue, w); // Đẩy đỉnh w vào hàng đợi để xét sau
                C[w] = 0;       // Đánh dấu đỉnh w đã xét
            }
        }
        if (front > rear)
            front = rear = -1;
    }
}
int main()
{
    init_queue();
    input_to_creat_magic();
    in_magic();
    init_C();
    BFS(0);
    std::cout << "Danh sách BFS: ";
    inBFS();
    return 0;
}
