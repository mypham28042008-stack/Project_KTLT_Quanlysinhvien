Dự án này là một ứng dụng quản lý sinh viên chạy trên giao diện dòng lệnh (CLI), được viết bằng C++ và sử dụng CMake để quản lý biên dịch. Dự án áp dụng kiến trúc 3 lớp (3-Layer Architecture) và triển khai thủ công các cấu trúc dữ liệu nền tảng như **Bảng băm (Hash Map)** và **Danh sách liên kết (Linked List)** nhằm đạt hiệu suất O(1) trong quản lý dữ liệu lớn.

Các chức năng nổi bật (Modules)

Toàn bộ hệ thống được chia thành 4 module nghiệp vụ chính:

Module 1: Quản Lý Danh Mục & Cấu Trúc Dữ Liệu Lõi
- Cấu trúc dữ liệu tự xây dựng:
  - `HashMap<K, V>`: Sử dụng phương pháp Separate Chaining (mảng các Linked List) để xử lý đụng độ. Tích hợp thuật toán tự động cấp phát lại (Rehashing) khi tải trọng Load Factor >= 0.75, đảm bảo thời gian tra cứu luôn xấp xỉ O(1).
  - `LinkedList<T>`: Danh sách liên kết đơn cấp phát động.
- Tính năng:
  - Thêm, sửa, xóa, tìm kiếm các thực thể cốt lõi: Sinh viên, Học phần, Lớp học phần, Ngành học.
  - Mỗi thực thể đều được lưu trữ trực tiếp trên RAM thông qua các Hash Map độc lập, được quản lý tập trung tại `StudentManager`.

Module 2: Báo Cáo & Hiển Thị Thông Tin
- Tra cứu Bảng điểm cá nhân: Cho phép nhập MSSV để truy xuất ngay lập tức (O(1)) toàn bộ quá trình học tập của sinh viên. Trích xuất tên học phần, số tín chỉ, điểm thành phần và điểm tổng kết dưới định dạng bảng đẹp mắt.
- Bảng điểm Lớp học phần: Cho phép nhập Mã Lớp và in ra danh sách điểm của toàn bộ sinh viên trong lớp đó (O(K * M)) mà không làm rò rỉ bộ nhớ.

Module 3: Thống Kê & Đánh Giá Học Lực
- Tính toán GPA & CPA (Thang điểm 4):
  - Tự động đối chiếu điểm số của sinh viên với số tín chỉ học phần để tính trung bình cộng có trọng số.
  - Phân loại rõ ràng giữa GPA (Điểm của 1 học kỳ cụ thể) và CPA (Điểm tích lũy toàn khoá).
- Xếp loại học lực: Ánh xạ CPA ra các mức độ (Xuất sắc, Giỏi, Khá, Trung bình, Yếu) theo quy chế đào tạo tín chỉ tiêu chuẩn.
Module 4: Chức Năng Nền Hệ Thống (File I/O & Đánh giá thuật toán)
- Quản lý dữ liệu file (Load/Save CSV):
  - Hệ thống tự động phân tách chuỗi (parse) và nạp hàng vạn bản ghi từ file `.csv` vào RAM.
  - Khả năng Lưu dữ liệu: Trích xuất tất cả thông tin hiện có ra các file `_Export.csv` để bảo lưu trạng thái hệ thống.
- Sinh dữ liệu mẫu (Mock Data): Khởi tạo hơn 10.000 bản ghi sinh viên giả lập, tự động phân bổ điểm số ngẫu nhiên.
- Bài test Hiệu năng Tìm kiếm:
  - So sánh trực tiếp tốc độ tìm kiếm 1.000 sinh viên bằng Vòng lặp tuyến tính (O(N)) so với Tra cứu Hash Map (O(1)).
  - Tính toán thời gian thực bằng `<chrono>` (tính bằng milliseconds) nhằm minh chứng cho tính ưu việt của Bảng băm.
