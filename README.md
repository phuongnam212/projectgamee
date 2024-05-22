# Dự Án Game Mini Golf

## Giới Thiệu
Bài tập lớn "Lập trình nâng cao" (2324II_INT2215_21)
Sinh viên : Đặng Phương Nam 
Mã sinh viên : 23020631
Đây là một dự án game mini golf sử dụng ngôn ngữ C++ được phát triển bằng thư viện SDL2.
Trong game, người chơi sẽ điều khiển một quả bóng để đạt được mục tiêu là đưa bóng vào lỗ.
Game có các yếu tố như gió, địa hình và các vật cản để tăng thêm tính thử thách.

## Mục Lục

1. [Giới Thiệu](#giới-thiệu)
2. [Điều kiện cần có ](#điều-kiện-cần-có)
3. [Cài Đặt](#cài-đặt)
4. [Hướng Dẫn Sử Dụng](#hướng-dẫn-sử-dụng)
5. [Cấu Trúc Dự Án](#cấu-trúc-dự-án)
6. [Tài Liệu Tham Khảo](#tài-liệu-tham-khảo)
7. [Liên Hệ](#liên-hệ)
  
  
## Điều kiện tiên quyết:  
Trước khi tải hoặc clone project về, hãy lưu ý:  
* Hướng dẫn sau chỉ dành cho hệ điều hành Windows và game hỗ trợ chỉ với hệ điều hành Windows
* Nếu bạn chỉ quan tâm đến việc tải game về và chơi, sẽ không có lưu ý gì cả, bạn chỉ việc tải về và trải nghiệm
* Nếu bạn quan tâm và muốn phát triển dự án hoặc đơn giản là chỉ chạy thử trên IDE, hãy đảm bảo rằng IDE của bạn có phục vụ cho ngôn ngữ C++ và
  có cài đặt thêm thư viện đồ hoạ SDL phục vụ cho C++ (Cách cài đặt SDL: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/index.php)
## Cài Đặt
### Ảnh Quả Bóng
![Quả Bóng](https://github.com/username/repository/raw/master/res/gfx/b.png)
Để cài đặt và chạy dự án, bạn cần phải cài đặt các thư viện sau:

- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer

Bạn có thể cài đặt các thư viện này bằng các lệnh sau (dành cho Ubuntu):

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
