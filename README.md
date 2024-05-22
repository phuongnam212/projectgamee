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
Để cài đặt và chạy dự án, bạn cần phải cài đặt các thư viện sau:

- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
## Hướng Dẫn Sử Dụng

### Chơi Game

1. Khởi động game bằng cách chạy tệp thực thi đã biên dịch.
2. Trên màn hình chính, chọn "Play Game" để bắt đầu.
3. Sử dụng chuột để điều khiển và nhấn chuột trái để bắn bóng.

### Màn Hình Chính
![Màn Hình Chính](https://user-images.githubusercontent.com/89717384/170001630-6e0aef9c-eb44-455a-8b03-0fe87cfc9b22.png)

### Màn Hình Chơi Game
![Màn hình chính](https://github.com/phuongnam212/projectgamee/assets/160800881/d802b25e-19e0-476f-9dcd-a1ca1de86e91)

## Cấu Trúc Dự Án

```plaintext
.
├── README.md                  # Tệp hướng dẫn sử dụng và thông tin dự án
├── main.cpp                   # Tệp nguồn chính của dự án
├── RenderWindows.h            # Tệp tiêu đề cho lớp RenderWindows
├── RenderWindows.cpp          # Tệp nguồn cho lớp RenderWindows
├── Entity.h                   # Tệp tiêu đề cho lớp Entity
├── Entity.cpp                 # Tệp nguồn cho lớp Entity
├── ball.h                     # Tệp tiêu đề cho lớp Ball
├── ball.cpp                   # Tệp nguồn cho lớp Ball
├── Tile.h                     # Tệp tiêu đề cho lớp Tile
├── Tile.cpp                   # Tệp nguồn cho lớp Tile
├── hole.h                     # Tệp tiêu đề cho lớp Hole
├── hole.cpp                   # Tệp nguồn cho lớp Hole
├── Wind.h                     # Tệp tiêu đề cho lớp Wind
├── Wind.cpp                   # Tệp nguồn cho lớp Wind
├── res                        # Thư mục chứa các tài nguyên (graphics, âm thanh, font chữ)
│   ├── gfx                    # Thư mục chứa các tệp hình ảnh
│   │   ├── ball.png
│   │   ├── hole.png
│   │   ├── ...
│   ├── sfx                    # Thư mục chứa các tệp âm thanh
│   │   ├── charge.mp3
│   │   ├── ...
│   ├── font                   # Thư mục chứa các tệp font chữ
│   │   ├── font.ttf
└── LICENSE                    # Tệp giấy phép (license) cho dự án

## Tài liệu tham khảo
- [Hướng dẫn sử dụng SDL của lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php)
- Ý tưởng của game có lấy một phần từ project game ["_Twini-Golf_"](https://github.com/PolyMarsDev/Twini-Golf), game sử dụng lại một số hình ảnh và sound effect của project nói trên chứ hoàn toàn không sao chép code hay modify project này.
- Xin gửi lời cảm ơn đến tác giả của project game nói trên về sự giúp đỡ về mặt tài nguyên hình ảnh và sound effect, đồng thời gửi lời cảm ơn đến hai giảng viên của Trường Đại học Công nghệ, ĐHQGHN đã cung cấp những kiến thức cần có để tôi có thể hoàn thành project này.

