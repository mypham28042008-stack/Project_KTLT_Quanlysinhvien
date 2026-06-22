cmake_minimum_required(VERSION 3.10)
project(Final_Project_DSA CXX)

# Yêu cầu chuẩn C++11 trở lên
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Liệt kê toàn bộ các tệp nguồn và header để hiển thị trong Xcode
set(SOURCE_FILES
    main.cpp
    datastructures/Node.h
    datastructures/LinkedList.h
    datastructures/HashMap.h
    models/SinhVien.h
    models/HocPhan.h
    models/KetQuaHocTap.h
    models/NganhHoc.h
    core/StudentManager.h
    utils/FileHandler.h
    utils/DataGenerator.h
)

# Nhóm các file theo thư mục vật lý để hiển thị đẹp mắt trong Xcode Project Navigator
source_group("datastructures" FILES
    datastructures/Node.h
    datastructures/LinkedList.h
    datastructures/HashMap.h
)
source_group("models" FILES
    models/SinhVien.h
    models/HocPhan.h
    models/KetQuaHocTap.h
    models/NganhHoc.h
)
source_group("core" FILES
    core/StudentManager.h
)
source_group("utils" FILES
    utils/FileHandler.h
    utils/DataGenerator.h
)

# Tạo target thực thi chính
add_executable(Final_Project_DSA ${SOURCE_FILES})

# Sao chép tệp students.csv sang thư mục build để chạy kiểm thử debug dễ dàng
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/students.csv")
    configure_file(students.csv ${CMAKE_CURRENT_BINARY_DIR}/students.csv COPYONLY)
endif()
